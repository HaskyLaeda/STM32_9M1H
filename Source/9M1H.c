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
    #define NOBUFFSEND       (0x0080) // (BIT7) - флаг показывающий, что следующее сообщение не должно быть помещено в Main Msg Buffer
    #define SMSWAIT          (0x0100) // (BIT8) - флаг показывающий, что идет ожидание текста SMS для пересылки его в SMS буффер
    #define SENDOK           (0x0200) // (BIT9) - флаг показывающий, что GPRS пакет успешно отправлен
    #define SMSNOSEND        (0x0400) // (BIT10) - флаг показывающий, что при отправке SMS произошла ошибка
    #define CMSERROR         (0x0800) // (BIT11) - флаг показывающий, что произошла ошибка CMS ERROR: CMSErrorParam
    #define CMEERROR         (0x1000) // (BIT12) - флаг показывающий, что произошла ошибка CME ERROR: CMEErrorParam
    #define ANGBR            (0x2000) // (BIT13) - флаг показывающий, что пришол символ ">"
    #define CLOSED           (0x4000) // (BIT14) - флаг показывающий, что пришоло CLOSED
    #define RESMESS2         (0x8000) // (BIT15) - флаг показывающий, что MSP430 принял сообщение
  
    #define RET_ERROR     (1)
    #define RET_OK        (0)
    
    
    //-------- Main Msg Buffer ------------------
  char MMBuffer[MMBufferSize][MsgLength + 1];   // Главный буффер сбора сообщений
  char *MMBMsg[MMBufferSize];               // Указатели на конкретное сообщение в буффере
  volatile signed char NMMMBuffer = 0;      // Индикатор заполнености буффера
  
  char USART1_RX_MsgAr[SMSMsgLength + 1];             // Буффер входящего сообщения c USART1 модуля
  char USART1_TX_MsgAr[SMSMsgLength + 1];             // Буффер исходящего сообщения на USART1 модуль
  char *USART1_RX_Msg = &USART1_RX_MsgAr[0];  // Указатель на буффер входящего сообщения c USART1 модуля  
  char *USART1_TX_Msg = &USART1_RX_MsgAr[0];  // Указатель на буффер исходящего сообщения на USART1 модуль
  
    //---------- Переменные GSM модуля --------------
  char RXGSMMsgAr[SMSMsgLength];        // Буффер входящего сообщения c GSM модуля
  char TXGSMMsgAr[SMSMsgLength];        // Буффер исходящего сообщения на GSM модуль
  char *RXGSMMsg = &RXGSMMsgAr[0];  // Указатель на буффер входящего сообщения c GSM модуля
  char *TXGSMMsg = &TXGSMMsgAr[0];  // Указатель на буффер исходящего сообщения на GSM модуль
  
  
  //--------------------------------------------------------------------------------------------------------------------
  //------------------------------------------   Functions body   ------------------------------------------------------
  //--------------------------------------------------------------------------------------------------------------------
  void InitVar(void){        
    for (char i = 0; i <= (MMBufferSize-1); i++)
    MMBMsg[i] = &MMBuffer[i][0];        
    return;
  }  
    
  void USART1_Flow_Stop(){
    
    return;
  }
  
  void USART1_Flow_Resume(){
    
    return;
  }
  
  unsigned char* USART1_Check_Start_Msg() {
  
    return 0;    
  }  
    
  
  unsigned int USART1_FormMsg(unsigned char Data) {
    char l;
//    static bool StartMsgFound = false;
    
   
    l = strlen(USART1_RX_MsgAr);
    USART1_RX_Msg[l]=Data;    
    USART1_RX_Msg[l+1]=0x00;  
    if ( l == 0 ) return 0;    
//  if (Data == '>')
//    {
//      SetBits(GSMFC, ANGBR + RESMESS);
//      return;
//    }            
      // Если ловим признак пустой команды '>  ' обнуляем буффер и выходим
    if ((USART1_RX_Msg[l] == ' ') && (USART1_RX_Msg[l-1] == '>')) {
      USART1_RX_Msg[0] = 0x00; 
      return 0;      
    }       
      // Если ловим признак конца команды '\r\n' оно же 'CRLF', то ..
    if ((USART1_RX_Msg[l] == 0x0A) && (USART1_RX_Msg[l-1] == 0x0D) || (l == SMSMsgLength) ) {      
      if ((USART1_RX_Msg[l] == 0x0A) && (USART1_RX_Msg[l-1] == 0x0D)) USART1_RX_Msg[l-1] = 0x00;      
      USART1_Flow_Stop();     
      switch (USART1_Send_RX_Msg(USART1_RX_Msg)) {  // Пересылаем накопленное побайтно сообщение в буффер для обработки
        case RET_OK: {        
          USART1_Flow_Resume();
          break;
        }
        case RET_ERROR:{
//          SetBits(TREKSC2, MMBUFFULL); // Устанавливаем бит заполненности главного буффера
          //ErrorIndication(MainMsgBufFull, 1);
          break;
        }
      }
      USART1_RX_Msg[0] = 0x00;          // Обнуляем приемный буффер сообщений от GSM модуля
      return 0;      
    }    
    return 0;
  }   
  
  unsigned int USART1_Send_RX_Msg(char* Msg) {
    
//  SetBits(GSMFC, RESMESS);
//  if (GetSetBit(GSMFC, NOBUFFSEND))  // Если установлен бит пропуска сообщения, то не обрабатываем
//  {
//    ClearBits(GSMFC, NOBUFFSEND);
//    return RET_OK;
//  }    
//  if (GetSetBit(GSMFC, SMSWAIT))                     // Если установлен бит активности чтения SMS из ячейки SIM карты
//  {
//    SMSBuffer = strcpy(SMSBuffer, Msg);                // Копируем содержимое SMS в буффер SMS
//    SetBits(TREKSC2, SMSBF);                           // Устанавливаем флаг заполненности SMS буффера
//    ClearBits(GSMFC, SMSWAIT);                         // Очищаем бит активности чтения SMS из ячейки SIM карты
//    return RET_OK;
//  }  
//  if (strlen(Msg) >= MsgLength)
//  {
//    ErrorIndication(LongMsgRes, 1);  // если длина принятого сообщения больше длины в MMBMsg, то    // !!!!!!!!!!!!!!!!!!!!!!!!!
//    Msg[MsgLength] = 0x00;                                         // урезаем сообщение
//  }    
    
//------------------ Критическая секция ----------------------------------------
    for (char i = 0; i <= (MMBufferSize - 1); i++) // Ищем свободную строку в главном буффере
    {
      if (MMBMsg[i][0] == 0x00) // Если нашли, заносим сообщение
      {
        for (char j = 0; Msg[j] != 0x00; j++) {  
          MMBMsg[i][j] = Msg[j];
        }  
        NMMMBuffer++;
        return RET_OK;
      }
    }
//------------------------------------------------------------------------------
    return RET_ERROR; // Если произошла ошибка    
  }  
    
  
void ProcessingMessage(void) // "Процедура" обработки сообщений из главного буффера
{
  char i;
  char* ProcMsg;  // Сообщение которое будет обрабатываться

  ProcMsg = MMBMsg[0];                          // Выбираем очередное сообщение для обработки
  while (ProcMsg[0] != 0x00)                    // Пока главный буффер сообщениий не пуст, то выполняем цикл обработки.
  {
    AnaliseExecuteMsg(ProcMsg);                 // Производим анализ и выполнение сообщения.
    ProcMsg[0] = 0x00;
//    GSMFlowStop();                              // Здесь нужно остановить поток данных с GSM модуля
//------------------ Критическая секция ----------------------------------------
    for (i = 0; i <= (MMBufferSize - 2); i++)   //--- Циклический сдвиг указателей на строки буффера
      MMBMsg[i] = MMBMsg[i + 1];
    MMBMsg[MMBufferSize - 1] = ProcMsg;
//------------------------------------------------------------------------------
    ProcMsg = MMBMsg[0];
    NMMMBuffer--;                               // Уровень заполненности главного буфера
//    GSMFlowResume();                            // Здесь нужно восстановить поток данных с GSM модуля
  }
//  if (NMMMBuffer < 0) ErrorIndication(MainMsgBufOverEmpty, 1); // Индикация переопустошения буффера
  return;
};  


void AnaliseExecuteMsg(char* Msg) // "Процедура" анализа сообщения и выполнения
{                                  // управляющих комманд
//  unsigned int LengthMessage;
//  unsigned int i = 0;
//  unsigned int j = 0;

//  LengthMessage = strlen(Msg);     // Определяем длинну сообщения
  
  if (strcmp(Msg, "OFF") == 0) { 
    GPIOB->BSRR = GPIO_BSRR_BR1;
    return;
  }   
  if (strcmp(Msg, "ON") == 0) {
    GPIOB->BSRR = GPIO_BSRR_BS1;
    return;
  }  
  

//  if (strncmp(Msg, "+", 1) == 0)
//  {
//    if ((strcmp(Msg,"+CGATT: 0") == 0))    // Если при опросе состояния пропало соединение GPRS, то
//    {
//      if (GetSetBit(TREKSC, GPRSSC))
//      {
//        SetBits(TREKSC, GPRSRST);                       // Устанавливаем бит необходимости переинициализации GPRS
//        ClearBits(TREKSC, GPRSSC + GPRSCC + GPRSSA);          // Очищаем биты активности соединений GPRS
//        GPRSLEVEL = 0;
//        MyIP = 0;
//        Dollar_OFF;                                      // Сброс индикации активности соединения GPRS
//        TX_OFF;                                          // Сброс индикации активности клиентского соединения GPRS
//        RX_OFF;                                          // Сброс индикации активности серверного соединения GPRS
//        return;
//      }
//    }
//    if ((strcmp(Msg, "+CREG: 0,1") == 0) || (strcmp(Msg, "+CREG: 0,5") == 0)) // Если при опросе состояния есть регистрация в сети GSM, то
//    {
//      SetBits(TREKSC, GSMREG);                   // выставляем соответствующий бит
//      Antena_ANT_ON;                             // Индикация регистрации в сети
//      ClearBits(BTSC, NOGSMNET);                 // Останавливаем счетчик отсутствия GSM сети
//      NoGSMNetC = 0;                             // Сбрасываем счетчик отсутствия GSM сети
//      return;
//    }
//    if ((strcmp(Msg, "+CREG: 0,0") == 0) || (strcmp(Msg, "+CREG: 1,0") == 0))  // Если при опросе состояния нет регистрации в сети GSM, то
//    {
//      ClearBits(TREKSC, GSMREG);                                     // Очищаем соответствующий бит
//      Antena_ANT_OFF;                                                // Индикация отсутствия регистрации в сети
//      if (!GetSetBit(BTSC, GSMTIMEWAIT) && !GetSetBit(BTSC, NOGSMNET)) SetBits(BTSC, NOGSMNET);    // Запускаем счетчик отсутствия GSM сети
//      return;
//    }
//    //----------------------------  Определение уровня сигнала GSM сети  ----------------
//    if (strncmp(Msg, "+CSQ:", 5) == 0)
//    {
//      GSMSignalLevel = atoi(Msg + 5);
//      return;
//    }
//    //-----------------------------------------------------------------------------------
//    if (strncmp(Msg, "+CMS ERROR:", 11) == 0)
//    {
//      CMSErrorParam = atoi(Msg + 11);
//      SetBits(GSMFC, CMSERROR);
//      return;
//    }
//    if (strncmp(Msg, "+CME ERROR:", 11) == 0)
//    {
//      CMEErrorParam = atoi(Msg + 11);
//      SetBits(GSMFC, CMEERROR);
//      return;
//    }
//    if ((strncmp(Msg, "+CMTI:", 6) == 0) && (strstr(Msg, "\"SM\",")) != NULL)  // Определяем, что пришло SMS сообщение
//    {
//      ENV_ON;
//      switch (PutSMSNum(atoi(strstr(Msg, ",") + 1))) // Заносим в очередь обработки ячейку памяти SIM, в которой сохранилась пришедшая SMS
//      {
//        case RET_OK: break;
//        case RET_ERROR:
//        {
//          ErrorIndication(SMSBufFull, 1);
//          break;
//        }
//      }
//      return;
//    }
//    //-----------------------  Чтение номеров из телефонной книги SIM карты  -------------------------------------------
//    if (strncmp(Msg, "+CPBR:", 6) == 0)
//    {
//      GetGSMData(Msg, SDMMCBuff, 2);
//      j = strlen(SDMMCBuff);
//      for (i = 0; i < j; i++) SDMMCBuff[i] = SDMMCBuff[i + 1];
//      SDMMCBuff[j - 2]  = 0x00;
//      NumBuffer = strcpy(NumBuffer, SDMMCBuff);
//      LenNumBuff = strlen(NumBuffer);
//      DispBuffer[0] = strcpy(DispBuffer[0], NumBuffer);
//      SDMMCBuff[0] = 0x00;
//      return;
//    }
//    //----------------------------  Определение уровня громкости -------------------------------------------------------
//    if (strncmp(Msg, "+CLVL:", 6) == 0)
//    {
//      VolumeLevel = atoi(Msg + 6);
//      return;
//    }
//    //---------------------------  Проверка запроса PIN кода  ----------------------------------------------------------
//    if ((strcmp(Msg, "+CPIN: SIM PIN") == 0))
//    {
//      SetBits(GSMFC, PIN);                 // Если получили +CPIN: SIM PIN, выставили соответствующий флаг активности запроса PIN кода
//      return;
//    }
//    //------------------------------------------------------------------------------------------------------------------
//  }
//  //--------------------------------------------------------------------------------------------------------------------
//  if ((strcmp(Msg, "OK") == 0) || (strcmp(Msg, "SHUT OK") == 0))
//  {
//    SetBits(GSMFC, OK);                    // Если получили OK, выставили соответствующий флаг
//    if (GetSetBit(GSMFC, GSMNOSEND) && GetSetBit(BTSC, NOANSCON) && (strcmp(Msg, "OK") == 0))
//    {
//      NACC = 0;                                        // Сбрасываем таймер ожидания ответа
//      ClearBits(GSMFC, GSMNOSEND);                       // Сбрасываем флаг запрета передачи на GSM модуль
//      ClearBits(BTSC, NOANSCON);                         // Останавливаем таймер ожидания ответа
//      DispBuffer[0] = strcpy(DispBuffer[0], NumBuffer);
//    }
//    return;
//  }
//  if ((strcmp(Msg, "ERROR") == 0) || (strcmp(Msg, "+CMS ERROR: 517") == 0))
//  {
//    SetBits(GSMFC, ERROR);                // Если получили ошибку, выставили соответствующий флаг
//    if (GetSetBit(GSMFC, GSMNOSEND) && GetSetBit(BTSC, NOANSCON))
//    {
//      NACC = 0;                                        // Сбрасываем таймер ожидания ответа
//      ClearBits(BTSC, NOANSCON);                       // Останавливаем таймер ожидания ответа
//      ClearBits(GSMFC, GSMNOSEND);                     // Сбрасываем флаг запрета передачи на GSM модуль
//      if (GPRSLEVEL == 2) SetBits(TREKSC, GPRSRST);    // Устанавливаем флаг необходимости переинициализации GPRS
//      DispBuffer[0] = strcpy(DispBuffer[0], NumBuffer);
//    }
//    return;
//  }
//  if ((strcmp(Msg, "SEND OK") == 0))
//  {
//    SetBits(GSMFC, SENDOK);                    // Если получили SEND OK, выставили соответствующий флаг
//    return;
//  }
//  if (strcmp(Msg, ">") == 0)                // Если прислали символ ">"
//  {
//    SetBits(GSMFC, ANGBR);
//    return;
//  }
//  if (strcmp(Msg, "CLOSED") == 0)
//  {
//    SetBits(GSMFC, CLOSED);              // Устанавливаем бит, что пришло CLOSED
//    SetBits(TREKSC3, CCRST);             // Устанавливаем бит необходимости переподключения
//    ClearBits(TREKSC, GPRSCC);           // Сбрасываем флаг активности клиентского соединения
//    TX_OFF;                              // Индикация
//    F_5_OFF;                             // Индикация
//    return;
//  }
//  //--------------------------------------------------------------------------------------------------------------------
//  if (strcmp(Msg, "CONNECT OK") == 0)
//  {
//    SetBits(GSMFC, CONNECT_OK);          // Если установили, соединение выставили соответствующий флаг
//    ClearBits(BTSC, NOANSCON);           // Останавливаем таймер ожидания ответа
//    NACC = 0;                            // Сбрасываем таймер ожидания ответа
//    SetBits(TREKSC2, CONN1);             // Устанавливаем флаг переключения на клиентское соединение (+СIPCCON: 1)
//    ClearBits(TREKSC2, CONN2);           // Сбрасываем флаг переключения на серверное соединение (+СIPCCON: 2)
//    SetBits(TREKSC, GPRSCC);             // Устанавливаем флаг активности клиентского соединения
//    TX_ON;                               // Индикация
//    F_5_OFF;                             // Индикация
//    return;
//  }
//  if ((strcmp(Msg, "CONNECT FAIL") == 0))
//  {
//    SetBits(GSMFC, CONNECT_FAIL);        // Если не установили, соединение выставили соответствующий флаг
//    ClearBits(BTSC, NOANSCON);           // Останавливаем таймер ожидания ответа
//    NACC = 0;                            // Сбрасываем таймер ожидания ответа
//    ClearBits(TREKSC, GPRSCC);           // Сбрасываем флаг активности клиентского соединения
//    SetBits(TREKSC3, CCRST);             // Устанавливаем бит необходимости переинициализации клиентского соединения
//    TX_OFF;                              // Индикация
//    F_5_OFF;                             // Индикация
//    SetBits(BTSC, NOSERVCONWAIT);        // Запускаем таймер интервала между повторной попыткой соединения с сервером сбора сообщений
//    return;
//  }
//
////----------------------------  Определение IP адреса ------------------------------------------------------------------
//  if (GetSetBit(TREKSC, IP) && (MyIP == 0))  // Проверяем ожидается ли строка IP адреса
//  {
//    if ((LengthMessage >= 7) && (LengthMessage <= 15))  // Определяем является ли сообщение IP адресом
//    {
//      i = 0;
//      j = 0;
//      while ((Msg[i] != 0x00) && (((Msg[i] >= 0x30) && (Msg[i] <= 0x39)) || (Msg[i] == '.')))
//      {
//        if (Msg[i] == '.') j++;
//        i++;
//      }
//      if ((i == LengthMessage) && (j == 3))
//      {
//        StrToIP(Msg, MyIP);                  // Если сообщение является IP адресом, то сохраняем значение
//        ClearBits(BTSC, IPWAIT);             // Останавливаем таймер ожидания IP адреса
//        IPWaitC = 0;                         // Сбрасываем таймер ожидания IP адреса
//        ClearBits(TREKSC, IP);               // Очищаем бит ожидания IP адреса
//      }
//    }
//  }
////----------------------------------------------------------------------------------------------------------------------
//  if (strstr(Msg,"RING") != NULL)
//  {
//    ArrowDWN_ON;                               // Индикация входящего вызова
//    if (GetSetBit(TREKSC, CH2F)) Amp_ON();      // Включаем аудиоусилитель
//    SetBits(TREKSC2, GSMRING);                 // Устанавливаем флаг входящего вызова
//    return;
//  }
//  if ((strstr(Msg,"NO CARRIER") != NULL) || (strstr(Msg,"BUSY") != NULL))
//  {
//    ClearBits(TREKSC, GSMCINC + GSMCOTC);
//    ClearBits(TREKSC2, GSMRING);
//    Amp_OFF();                                 // Выключаем аудиоусилитель
//    ArrowUP_OFF;                               // Сброс индикации вызова(исходящего)
//    ArrowDWN_OFF;                              // Сброс индикации вызова(входящего)
//    if (strstr(Msg,"BUSY"))
//    {
//      ArrowLF_ON;                              // Индикация занятости набираемого номера
//      ArrowRT_ON;                              // Индикация занятости набираемого номера
////      DispBuffer[1] = strcpy(DispBuffer[2], "busy"); // моргание busy, если занято
////      SetBits(BTSC, SWAPDB);                         // ...
//    }
//    return;
//  }
//  if ((strcmp(Msg, "UNDERVOLTAGE POWER DOWN") == 0) || (strstr(Msg, "UNDERVOLTAGE")) != NULL)
//  {
//    GPRSLEVEL = 0 ;                      // Сбрасываем уровень GPRS подключения в 0
//    GSMSignalLevel = 0;                  // Сбрасываем уровень сигнала GSM сети в 0
//    Antena_ANT_OFF;
//    Dollar_OFF;
//    TX_OFF;
//    ClearBits(TREKSC, GSMREG + GPRSSC + GPRSCC + GPRSSA + GSMCINC + GSMCOTC +   // Очищаем флаг активности GSM модуля и GPRS
//    GPRSRST + GSMEN + IP + CH1F + CH2F + DEVBUSY);                            // соединения и др. флаги связанные с GSM
//    GSMFC = 0;
//    ClearBits(TREKSC2, GSMRING + CHECKPARAM + CIICRNA + CONN1 + CONN2 +  NOGETIP);
//    ClearBits(TREKSC3, CCRST);
//    return;
//  }
//  if (strcmp(Msg, "POWER LOW WARNNING") == 0)
//  {
//    Minus_ON;
//    return;
//  }
//  if ((strcmp(Msg, "NORMAL POWER DOWN") == 0) || (strstr(Msg, "NORMAL POWER")) != NULL)
//  {
//    GPRSLEVEL = 0 ;                      // Сбрасываем уровень GPRS подключения в 0
//    GSMSignalLevel = 0;                  // Сбрасываем уровень сигнала GSM сети в 0
//    Antena_ANT_OFF;
//    Dollar_OFF;
//    TX_OFF;
//    ClearBits(TREKSC, GSMREG + GPRSSC + GPRSCC + GPRSSA + GSMCINC + GSMCOTC +   // Очищаем флаг активности GSM модуля и GPRS
//    GPRSRST + GSMEN + IP + CH1F + CH2F + DEVBUSY);                            // соединения и др. флаги связанные с GSM
//    GSMFC = 0;
//    ClearBits(TREKSC2, GSMRING + CHECKPARAM + CIICRNA + CONN1 + CONN2 +  NOGETIP);
//    ClearBits(TREKSC3, CCRST);
//    return;
//  }
////-------------------------- Пользовательские команды -----------------------------------------------------
//  //-----------------------------------------------------------------------------------------------------------
//  if ( (strcmp(Msg, "#gps") == 0) || (strcmp(Msg, "#GPS") == 0))  // Если сообщение запрос координат, то  ...
//  {
//    SetBits(USERCOMSC, REQCOORD);
//    return;
//  }
////-----------------------------------------------------------------------------------------------------------------
  return;
};

    
    
    


  
//char SendGSMResMessage(char* Msg) // Функция переноса принятого сообщения с GSM модуля
//{                                   // в главный буффер с предварительной обработкой
//  char hMsgAr[17];
//  char* hMsg = &hMsgAr[0];
//  char i, j;
//


//  if (strlen(Msg) >= MsgLength)
//  {
//    ErrorIndication(LongMsgRes, 1);  // если длина принятого сообщения больше длины в MMBMsg, то    // !!!!!!!!!!!!!!!!!!!!!!!!!
//    Msg[MsgLength] = 0x00;                                         // урезаем сообщение
//  }
//  if (strcmp(Msg, "") == 0) return RET_OK; // Если сообщение пустое, то не обрабатываем
//  if (strncmp(Msg, "+CMGR", 5) == 0) // Если сообщение заголовок SMS сообщения, то копируем номер, с которого пришло сообщение
//  {
//    GetGSMData(Msg, hMsg, 2);
//    j = strlen(hMsg);
//    for(i = 0; i < j; i++)
//    {
//      hMsg[i]  = hMsg[i + 1];
//    }
//    hMsg[j - 2] = 0x00;
//       //   Verification, здесь должна происходить верификация и (выставление)XOR(очистка)
//       //     бита недопустимости передачи текста SMS в главный буффер
//    if (strcmp(hMsg, MDispPhone) == 0) SetBits(GSMFC, SMSWAIT);  // Если сообщение пришло с номера диспетчера, то выставляем бит ожидания SMS
//    else SetBits(GSMFC, NOBUFFSEND);                             // , а если нет то выставляем бит недопустимости передачи текста SMS
//    return RET_OK;
//  }
//  if (strncmp(Msg, "+CMGL:", 6) == 0)
//  {
//    hMsg = strncpy(hMsg, Msg + 6, 3);
//    Msg = strcpy(Msg, "+CMTI: \"SM\",");
//    Msg = strcat(Msg, hMsg);
//    SetBits(GSMFC, NOBUFFSEND);
//  }
////------------------ Критическая секция ----------------------------------------
//  for (char i = 0; i <= (MMBufferSize-1); i++) // Ищем свободную строку в главном буффере
//  {
//    if (MMBMsg[i][0] == 0x00) // Если нашли, заносим сообщение
//    {
//      MMBMsg[i] = strcpy(MMBMsg[i], Msg);
//      NMMMBuffer++;
//      return RET_OK;
//    }
//  }
////------------------------------------------------------------------------------
//  return RET_ERROR; // Если произошла ошибка
//};  
  
  
//   unsigned short int l = 0;
//
//  if (GetSetBit(IFG2, UCA0RXIFG))              // Если данные пришли с GSM модуля ...
//  {
//    l = strlen(RXGSMMsg);
//    RXGSMMsg[l] = UCA0RXBUF;
//    RXGSMMsg[l+1] = 0x00;
//    if (RXGSMMsg[l] == '>')
//    {
//      SetBits(GSMFC, ANGBR + RESMESS);
//      return;
//    }
//    if ((RXGSMMsg[l] == ' ') && (RXGSMMsg[l-1] == '>') && (l == 1))
//    {
//      RXGSMMsg[0] = 0x00;
//      return;
//    }
//    l++;
//    RXGSMMsg[l] = 0x00;
//    if (l >= 2)
//    {
//      if (((RXGSMMsg[l-2] == 0x0D) && (RXGSMMsg[l-1] == 0x0A)) || (l == SMSMsgLength - 1)) // Если признак конца строки или строка слишком длинная
//      {
//        if (l == SMSMsgLength - 1) l = l + 3;   // Если строка слищком длинная обрезаем ее символом 0x00
//        RXGSMMsg[l-2] = 0x00;
//        l = strlen(RXGSMMsg);
//        if (l != 0)
//        {
//          GSMFlowStop();                 // Останавливаем поток сообщений с GSM модуля
//          switch (SendGSMResMsg(RXGSMMsg))  // Пересылаем накопленное побайтно сообщение в главный буффер
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
//        RXGSMMsg[0] = 0x00;          // Обнуляем приемный буффер сообщений от GSM модуля
//        return;
//      }
//    }
//  }
//
//  if (GetSetBit(IFG2, UCB0RXIFG))          // Если данные пришли с SD/MMC карты, то ...
//  {
////    F_4_ON;
//  }