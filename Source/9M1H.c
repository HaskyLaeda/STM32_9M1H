#include "9M1H.h"

//======================================================================================================================
//------------------------------------           Implementation            ---------------------------------------------
//======================================================================================================================    

  //--------------------------------------------------------------------------------------------------------------------
  //-----------------------------------------   Variables & Const   ----------------------------------------------------
  //--------------------------------------------------------------------------------------------------------------------
  
    //------------------------- Memory array sizes  ------------------------------

  #ifdef __cplusplus  
    const char MsgLength = 81;         // Размер буферов сообщений в MMBuffer
    const char MMBufferSize = 10;      // Количество буферов сообщений в MMBuffer
    const char SMSMsgLength = 165;     // Размер буфера SMS сообщения
    const char GPSMsgLength = 81;      // Размер буферов хранения NMEA сообщений (байт)
    const char NumberLenght = 16;      // Размер буферов хранения телефонных номеров (байт)
    const char SerNameLenght = 48;     // Размер буферов хранения интернет адресов
    const char PINPASSLOGLenght = 16;  // Размер буферов хранения паролей  
  #else
    #define MsgLength           81     // Размер буферов сообщений в MMBuffer
    #define MMBufferSize        10     // Количество буферов сообщений в MMBuffer
    #define SMSMsgLength       165     // Размер буфера SMS сообщения
    #define GPSMsgLength        81     // Размер буферов хранения NMEA сообщений (байт)
    #define NumberLenght        16     // Размер буферов хранения телефонных номеров (байт)
    #define SerNameLenght       48     // Размер буферов хранения интернет адресов
    #define PINPASSLOGLenght    16     // Размер буферов хранения паролей        
  #endif
    
  //------------------------ Управляющие переменные  ---------------------------
  volatile unsigned short int GSMFC = 0; // Регистр флагов управления для работы с GSM модулем
    #define OK               (0x0001) // (BIT0) - флаг показывающий, что GSM модуль ответил OK
    #define ERROR            (0x0002) // (BIT1) - флаг показывающий, что GSM модуль ответил ERROR
    #define PIN              (0x0004) // (BIT2) - флаг показывающий, что GSM модуль запрашивает PIN код
    #define CONNECT_OK       (0x0008) // (BIT3) - флаг показывающий, что GSM модуль УСТАНОВИЛ СОЕДИНЕНИЕ
    #define CONNECT_FAIL     (0x0010) // (BIT4) - флаг показывающий, что GSM модуль НЕУстановил СОЕДИНЕНИЕ
    #define GSMNOSEND        (0x0020) // (BIT5) - флаг запрета передачи на GSM модуль чего либо
    #define RESMESS          (0x0040) // (BIT6) - флаг показывающий, что MSP430 принял сообщение
    #define NOBUFFSEND       (0x0080) // (BIT7) - флаг показывающий, что следующее сообщение не должно быть помещено в Main Message Buffer
    #define SMSWAIT          (0x0100) // (BIT8) - флаг показывающий, что идет ожидание текста SMS для пересылки его в SMS буффер
    #define SENDOK           (0x0200) // (BIT9) - флаг показывающий, что GPRS пакет успешно отправлен
    #define SMSNOSEND        (0x0400) // (BIT10) - флаг показывающий, что при отправке SMS произошла ошибка
    #define CMSERROR         (0x0800) // (BIT11) - флаг показывающий, что произошла ошибка CMS ERROR: CMSErrorParam
    #define CMEERROR         (0x1000) // (BIT12) - флаг показывающий, что произошла ошибка CME ERROR: CMEErrorParam
    #define ANGBR            (0x2000) // (BIT13) - флаг показывающий, что пришол символ ">"
    #define CLOSED           (0x4000) // (BIT14) - флаг показывающий, что пришоло CLOSED
    #define RESMESS2         (0x8000) // (BIT15) - флаг показывающий, что MSP430 принял сообщение
    
    
    //-------- Main Message Buffer ------------------
  char MMBuffer[MMBufferSize][MsgLength];   // Главный буффер сбора сообщений
  char *MMBMsg[MMBufferSize];               // Указатели на конкретное сообщение в буффере
  volatile signed char NMMMBuffer = 0;      // Индикатор заполнености буффера
  
    //---------- Переменные GSM модуля --------------
  char RXGSMMessageAr[SMSMsgLength];        // Буффер входящего сообщения c GSM модуля
  char TXGSMMessageAr[SMSMsgLength];        // Буффер исходящего сообщения на GSM модуль
  char *RXGSMMessage = &RXGSMMessageAr[0];  // Указатель на буффер входящего сообщения c GSM модуля
  char *TXGSMMessage = &TXGSMMessageAr[0];  // Указатель на буффер исходящего сообщения на GSM модуль
  
  
  unsigned int function FormGSM_Message(unsigned char Byte)
  {
    
    return 0;
  }
  

//   unsigned short int l = 0;
//
//  if (GetSetBit(IFG2, UCA0RXIFG))              // Если данные пришли с GSM модуля ...
//  {
//    l = strlen(RXGSMMessage);
//    RXGSMMessage[l] = UCA0RXBUF;
//    RXGSMMessage[l+1] = 0x00;
//    if (RXGSMMessage[l] == '>')
//    {
//      SetBits(GSMFC, ANGBR + RESMESS);
//      return;
//    }
//    if ((RXGSMMessage[l] == ' ') && (RXGSMMessage[l-1] == '>') && (l == 1))
//    {
//      RXGSMMessage[0] = 0x00;
//      return;
//    }
//    l++;
//    RXGSMMessage[l] = 0x00;
//    if (l >= 2)
//    {
//      if (((RXGSMMessage[l-2] == 0x0D) && (RXGSMMessage[l-1] == 0x0A)) || (l == SMSMsgLength - 1)) // Если признак конца строки или строка слишком длинная
//      {
//        if (l == SMSMsgLength - 1) l = l + 3;   // Если строка слищком длинная обрезаем ее символом 0x00
//        RXGSMMessage[l-2] = 0x00;
//        l = strlen(RXGSMMessage);
//        if (l != 0)
//        {
//          GSMFlowStop();                 // Останавливаем поток сообщений с GSM модуля
//          switch (SendGSMResMessage(RXGSMMessage))  // Пересылаем накопленное побайтно сообщение в главный буффер
//          {
//            case RET_OK:
//            {
//              GSMFlowResume();
//              break;
//            }
//            case RET_ERROR:
//            {
//              SetBits(TREKSC2, MMBUFFULL); // Устанавливаем бит заполненности главного буффера
//              ErrorIndication(MainMsgBufFull, 1);
//              break;
//            }
//          }
//        }
//        RXGSMMessage[0] = 0x00;          // Обнуляем приемный буффер сообщений от GSM модуля
//        return;
//      }
//    }
//  }
//
//  if (GetSetBit(IFG2, UCB0RXIFG))          // Если данные пришли с SD/MMC карты, то ...
//  {
////    F_4_ON;
//  }