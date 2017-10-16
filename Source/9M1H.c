#include "9M1H.h"

//======================================================================================================================
//------------------------------------           Implementation            ---------------------------------------------
//======================================================================================================================    

  //--------------------------------------------------------------------------------------------------------------------
  //-----------------------------------------   Variables & Const   ----------------------------------------------------
  //--------------------------------------------------------------------------------------------------------------------
  
    //------------------------- Memory array sizes  ------------------------------

  #ifdef __cplusplus  
    const char MsgLength = 81;         // ������ ������� ��������� � MMBuffer
    const char MMBufferSize = 10;      // ���������� ������� ��������� � MMBuffer
    const char SMSMsgLength = 165;     // ������ ������ SMS ���������
    const char GPSMsgLength = 81;      // ������ ������� �������� NMEA ��������� (����)
    const char NumberLenght = 16;      // ������ ������� �������� ���������� ������� (����)
    const char SerNameLenght = 48;     // ������ ������� �������� �������� �������
    const char PINPASSLOGLenght = 16;  // ������ ������� �������� �������  
  #else
    #define MsgLength           81     // ������ ������� ��������� � MMBuffer
    #define MMBufferSize        10     // ���������� ������� ��������� � MMBuffer
    #define SMSMsgLength       165     // ������ ������ SMS ���������
    #define GPSMsgLength        81     // ������ ������� �������� NMEA ��������� (����)
    #define NumberLenght        16     // ������ ������� �������� ���������� ������� (����)
    #define SerNameLenght       48     // ������ ������� �������� �������� �������
    #define PINPASSLOGLenght    16     // ������ ������� �������� �������        
  #endif
    
  //------------------------ ����������� ����������  ---------------------------
  volatile unsigned short int GSMFC = 0; // ������� ������ ���������� ��� ������ � GSM �������
    #define OK               (0x0001) // (BIT0) - ���� ������������, ��� GSM ������ ������� OK
    #define ERROR            (0x0002) // (BIT1) - ���� ������������, ��� GSM ������ ������� ERROR
    #define PIN              (0x0004) // (BIT2) - ���� ������������, ��� GSM ������ ����������� PIN ���
    #define CONNECT_OK       (0x0008) // (BIT3) - ���� ������������, ��� GSM ������ ��������� ����������
    #define CONNECT_FAIL     (0x0010) // (BIT4) - ���� ������������, ��� GSM ������ ����������� ����������
    #define GSMNOSEND        (0x0020) // (BIT5) - ���� ������� �������� �� GSM ������ ���� ����
    #define RESMESS          (0x0040) // (BIT6) - ���� ������������, ��� MSP430 ������ ���������
    #define NOBUFFSEND       (0x0080) // (BIT7) - ���� ������������, ��� ��������� ��������� �� ������ ���� �������� � Main Message Buffer
    #define SMSWAIT          (0x0100) // (BIT8) - ���� ������������, ��� ���� �������� ������ SMS ��� ��������� ��� � SMS ������
    #define SENDOK           (0x0200) // (BIT9) - ���� ������������, ��� GPRS ����� ������� ���������
    #define SMSNOSEND        (0x0400) // (BIT10) - ���� ������������, ��� ��� �������� SMS ��������� ������
    #define CMSERROR         (0x0800) // (BIT11) - ���� ������������, ��� ��������� ������ CMS ERROR: CMSErrorParam
    #define CMEERROR         (0x1000) // (BIT12) - ���� ������������, ��� ��������� ������ CME ERROR: CMEErrorParam
    #define ANGBR            (0x2000) // (BIT13) - ���� ������������, ��� ������ ������ ">"
    #define CLOSED           (0x4000) // (BIT14) - ���� ������������, ��� ������� CLOSED
    #define RESMESS2         (0x8000) // (BIT15) - ���� ������������, ��� MSP430 ������ ���������
    
    
    //-------- Main Message Buffer ------------------
  char MMBuffer[MMBufferSize][MsgLength];   // ������� ������ ����� ���������
  char *MMBMsg[MMBufferSize];               // ��������� �� ���������� ��������� � �������
  volatile signed char NMMMBuffer = 0;      // ��������� ������������ �������
  
    //---------- ���������� GSM ������ --------------
  char RXGSMMessageAr[SMSMsgLength];        // ������ ��������� ��������� c GSM ������
  char TXGSMMessageAr[SMSMsgLength];        // ������ ���������� ��������� �� GSM ������
  char *RXGSMMessage = &RXGSMMessageAr[0];  // ��������� �� ������ ��������� ��������� c GSM ������
  char *TXGSMMessage = &TXGSMMessageAr[0];  // ��������� �� ������ ���������� ��������� �� GSM ������
  
  
  unsigned int function FormGSM_Message(unsigned char Byte)
  {
    
    return 0;
  }
  

//   unsigned short int l = 0;
//
//  if (GetSetBit(IFG2, UCA0RXIFG))              // ���� ������ ������ � GSM ������ ...
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
//      if (((RXGSMMessage[l-2] == 0x0D) && (RXGSMMessage[l-1] == 0x0A)) || (l == SMSMsgLength - 1)) // ���� ������� ����� ������ ��� ������ ������� �������
//      {
//        if (l == SMSMsgLength - 1) l = l + 3;   // ���� ������ ������� ������� �������� �� �������� 0x00
//        RXGSMMessage[l-2] = 0x00;
//        l = strlen(RXGSMMessage);
//        if (l != 0)
//        {
//          GSMFlowStop();                 // ������������� ����� ��������� � GSM ������
//          switch (SendGSMResMessage(RXGSMMessage))  // ���������� ����������� �������� ��������� � ������� ������
//          {
//            case RET_OK:
//            {
//              GSMFlowResume();
//              break;
//            }
//            case RET_ERROR:
//            {
//              SetBits(TREKSC2, MMBUFFULL); // ������������� ��� ������������� �������� �������
//              ErrorIndication(MainMsgBufFull, 1);
//              break;
//            }
//          }
//        }
//        RXGSMMessage[0] = 0x00;          // �������� �������� ������ ��������� �� GSM ������
//        return;
//      }
//    }
//  }
//
//  if (GetSetBit(IFG2, UCB0RXIFG))          // ���� ������ ������ � SD/MMC �����, �� ...
//  {
////    F_4_ON;
//  }