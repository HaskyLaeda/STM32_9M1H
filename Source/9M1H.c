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
    #define NOBUFFSEND       (0x0080) // (BIT7) - ���� ������������, ��� ��������� ��������� �� ������ ���� �������� � Main Msg Buffer
    #define SMSWAIT          (0x0100) // (BIT8) - ���� ������������, ��� ���� �������� ������ SMS ��� ��������� ��� � SMS ������
    #define SENDOK           (0x0200) // (BIT9) - ���� ������������, ��� GPRS ����� ������� ���������
    #define SMSNOSEND        (0x0400) // (BIT10) - ���� ������������, ��� ��� �������� SMS ��������� ������
    #define CMSERROR         (0x0800) // (BIT11) - ���� ������������, ��� ��������� ������ CMS ERROR: CMSErrorParam
    #define CMEERROR         (0x1000) // (BIT12) - ���� ������������, ��� ��������� ������ CME ERROR: CMEErrorParam
    #define ANGBR            (0x2000) // (BIT13) - ���� ������������, ��� ������ ������ ">"
    #define CLOSED           (0x4000) // (BIT14) - ���� ������������, ��� ������� CLOSED
    #define RESMESS2         (0x8000) // (BIT15) - ���� ������������, ��� MSP430 ������ ���������
  
    #define RET_ERROR     (1)
    #define RET_OK        (0)
    
    
    //-------- Main Msg Buffer ------------------
  char MMBuffer[MMBufferSize][MsgLength + 1];   // ������� ������ ����� ���������
  char *MMBMsg[MMBufferSize];               // ��������� �� ���������� ��������� � �������
  volatile signed char NMMMBuffer = 0;      // ��������� ������������ �������
  
  char USART1_RX_MsgAr[SMSMsgLength + 1];             // ������ ��������� ��������� c USART1 ������
  char USART1_TX_MsgAr[SMSMsgLength + 1];             // ������ ���������� ��������� �� USART1 ������
  char *USART1_RX_Msg = &USART1_RX_MsgAr[0];  // ��������� �� ������ ��������� ��������� c USART1 ������  
  char *USART1_TX_Msg = &USART1_RX_MsgAr[0];  // ��������� �� ������ ���������� ��������� �� USART1 ������
  
    //---------- ���������� GSM ������ --------------
  char RXGSMMsgAr[SMSMsgLength];        // ������ ��������� ��������� c GSM ������
  char TXGSMMsgAr[SMSMsgLength];        // ������ ���������� ��������� �� GSM ������
  char *RXGSMMsg = &RXGSMMsgAr[0];  // ��������� �� ������ ��������� ��������� c GSM ������
  char *TXGSMMsg = &TXGSMMsgAr[0];  // ��������� �� ������ ���������� ��������� �� GSM ������
  
  
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
      // ���� ����� ������� ������ ������� '>  ' �������� ������ � �������
    if ((USART1_RX_Msg[l] == ' ') && (USART1_RX_Msg[l-1] == '>')) {
      USART1_RX_Msg[0] = 0x00; 
      return 0;      
    }       
      // ���� ����� ������� ����� ������� '\r\n' ��� �� 'CRLF', �� ..
    if ((USART1_RX_Msg[l] == 0x0A) && (USART1_RX_Msg[l-1] == 0x0D) || (l == SMSMsgLength) ) {      
      if ((USART1_RX_Msg[l] == 0x0A) && (USART1_RX_Msg[l-1] == 0x0D)) USART1_RX_Msg[l-1] = 0x00;      
      USART1_Flow_Stop();     
      switch (USART1_Send_RX_Msg(USART1_RX_Msg)) {  // ���������� ����������� �������� ��������� � ������ ��� ���������
        case RET_OK: {        
          USART1_Flow_Resume();
          break;
        }
        case RET_ERROR:{
//          SetBits(TREKSC2, MMBUFFULL); // ������������� ��� ������������� �������� �������
          //ErrorIndication(MainMsgBufFull, 1);
          break;
        }
      }
      USART1_RX_Msg[0] = 0x00;          // �������� �������� ������ ��������� �� GSM ������
      return 0;      
    }    
    return 0;
  }   
  
  unsigned int USART1_Send_RX_Msg(char* Msg) {
    
//  SetBits(GSMFC, RESMESS);
//  if (GetSetBit(GSMFC, NOBUFFSEND))  // ���� ���������� ��� �������� ���������, �� �� ������������
//  {
//    ClearBits(GSMFC, NOBUFFSEND);
//    return RET_OK;
//  }    
//  if (GetSetBit(GSMFC, SMSWAIT))                     // ���� ���������� ��� ���������� ������ SMS �� ������ SIM �����
//  {
//    SMSBuffer = strcpy(SMSBuffer, Msg);                // �������� ���������� SMS � ������ SMS
//    SetBits(TREKSC2, SMSBF);                           // ������������� ���� ������������� SMS �������
//    ClearBits(GSMFC, SMSWAIT);                         // ������� ��� ���������� ������ SMS �� ������ SIM �����
//    return RET_OK;
//  }  
//  if (strlen(Msg) >= MsgLength)
//  {
//    ErrorIndication(LongMsgRes, 1);  // ���� ����� ��������� ��������� ������ ����� � MMBMsg, ��    // !!!!!!!!!!!!!!!!!!!!!!!!!
//    Msg[MsgLength] = 0x00;                                         // ������� ���������
//  }    
    
//------------------ ����������� ������ ----------------------------------------
    for (char i = 0; i <= (MMBufferSize - 1); i++) // ���� ��������� ������ � ������� �������
    {
      if (MMBMsg[i][0] == 0x00) // ���� �����, ������� ���������
      {
        for (char j = 0; Msg[j] != 0x00; j++) {  
          MMBMsg[i][j] = Msg[j];
        }  
        NMMMBuffer++;
        return RET_OK;
      }
    }
//------------------------------------------------------------------------------
    return RET_ERROR; // ���� ��������� ������    
  }  
    
  
void ProcessingMessage(void) // "���������" ��������� ��������� �� �������� �������
{
  char i;
  char* ProcMsg;  // ��������� ������� ����� ��������������

  ProcMsg = MMBMsg[0];                          // �������� ��������� ��������� ��� ���������
  while (ProcMsg[0] != 0x00)                    // ���� ������� ������ ���������� �� ����, �� ��������� ���� ���������.
  {
    AnaliseExecuteMsg(ProcMsg);                 // ���������� ������ � ���������� ���������.
    ProcMsg[0] = 0x00;
//    GSMFlowStop();                              // ����� ����� ���������� ����� ������ � GSM ������
//------------------ ����������� ������ ----------------------------------------
    for (i = 0; i <= (MMBufferSize - 2); i++)   //--- ����������� ����� ���������� �� ������ �������
      MMBMsg[i] = MMBMsg[i + 1];
    MMBMsg[MMBufferSize - 1] = ProcMsg;
//------------------------------------------------------------------------------
    ProcMsg = MMBMsg[0];
    NMMMBuffer--;                               // ������� ������������� �������� ������
//    GSMFlowResume();                            // ����� ����� ������������ ����� ������ � GSM ������
  }
//  if (NMMMBuffer < 0) ErrorIndication(MainMsgBufOverEmpty, 1); // ��������� ��������������� �������
  return;
};  


void AnaliseExecuteMsg(char* Msg) // "���������" ������� ��������� � ����������
{                                  // ����������� �������
//  unsigned int LengthMessage;
//  unsigned int i = 0;
//  unsigned int j = 0;

//  LengthMessage = strlen(Msg);     // ���������� ������ ���������
  
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
//    if ((strcmp(Msg,"+CGATT: 0") == 0))    // ���� ��� ������ ��������� ������� ���������� GPRS, ��
//    {
//      if (GetSetBit(TREKSC, GPRSSC))
//      {
//        SetBits(TREKSC, GPRSRST);                       // ������������� ��� ������������� ����������������� GPRS
//        ClearBits(TREKSC, GPRSSC + GPRSCC + GPRSSA);          // ������� ���� ���������� ���������� GPRS
//        GPRSLEVEL = 0;
//        MyIP = 0;
//        Dollar_OFF;                                      // ����� ��������� ���������� ���������� GPRS
//        TX_OFF;                                          // ����� ��������� ���������� ����������� ���������� GPRS
//        RX_OFF;                                          // ����� ��������� ���������� ���������� ���������� GPRS
//        return;
//      }
//    }
//    if ((strcmp(Msg, "+CREG: 0,1") == 0) || (strcmp(Msg, "+CREG: 0,5") == 0)) // ���� ��� ������ ��������� ���� ����������� � ���� GSM, ��
//    {
//      SetBits(TREKSC, GSMREG);                   // ���������� ��������������� ���
//      Antena_ANT_ON;                             // ��������� ����������� � ����
//      ClearBits(BTSC, NOGSMNET);                 // ������������� ������� ���������� GSM ����
//      NoGSMNetC = 0;                             // ���������� ������� ���������� GSM ����
//      return;
//    }
//    if ((strcmp(Msg, "+CREG: 0,0") == 0) || (strcmp(Msg, "+CREG: 1,0") == 0))  // ���� ��� ������ ��������� ��� ����������� � ���� GSM, ��
//    {
//      ClearBits(TREKSC, GSMREG);                                     // ������� ��������������� ���
//      Antena_ANT_OFF;                                                // ��������� ���������� ����������� � ����
//      if (!GetSetBit(BTSC, GSMTIMEWAIT) && !GetSetBit(BTSC, NOGSMNET)) SetBits(BTSC, NOGSMNET);    // ��������� ������� ���������� GSM ����
//      return;
//    }
//    //----------------------------  ����������� ������ ������� GSM ����  ----------------
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
//    if ((strncmp(Msg, "+CMTI:", 6) == 0) && (strstr(Msg, "\"SM\",")) != NULL)  // ����������, ��� ������ SMS ���������
//    {
//      ENV_ON;
//      switch (PutSMSNum(atoi(strstr(Msg, ",") + 1))) // ������� � ������� ��������� ������ ������ SIM, � ������� ����������� ��������� SMS
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
//    //-----------------------  ������ ������� �� ���������� ����� SIM �����  -------------------------------------------
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
//    //----------------------------  ����������� ������ ��������� -------------------------------------------------------
//    if (strncmp(Msg, "+CLVL:", 6) == 0)
//    {
//      VolumeLevel = atoi(Msg + 6);
//      return;
//    }
//    //---------------------------  �������� ������� PIN ����  ----------------------------------------------------------
//    if ((strcmp(Msg, "+CPIN: SIM PIN") == 0))
//    {
//      SetBits(GSMFC, PIN);                 // ���� �������� +CPIN: SIM PIN, ��������� ��������������� ���� ���������� ������� PIN ����
//      return;
//    }
//    //------------------------------------------------------------------------------------------------------------------
//  }
//  //--------------------------------------------------------------------------------------------------------------------
//  if ((strcmp(Msg, "OK") == 0) || (strcmp(Msg, "SHUT OK") == 0))
//  {
//    SetBits(GSMFC, OK);                    // ���� �������� OK, ��������� ��������������� ����
//    if (GetSetBit(GSMFC, GSMNOSEND) && GetSetBit(BTSC, NOANSCON) && (strcmp(Msg, "OK") == 0))
//    {
//      NACC = 0;                                        // ���������� ������ �������� ������
//      ClearBits(GSMFC, GSMNOSEND);                       // ���������� ���� ������� �������� �� GSM ������
//      ClearBits(BTSC, NOANSCON);                         // ������������� ������ �������� ������
//      DispBuffer[0] = strcpy(DispBuffer[0], NumBuffer);
//    }
//    return;
//  }
//  if ((strcmp(Msg, "ERROR") == 0) || (strcmp(Msg, "+CMS ERROR: 517") == 0))
//  {
//    SetBits(GSMFC, ERROR);                // ���� �������� ������, ��������� ��������������� ����
//    if (GetSetBit(GSMFC, GSMNOSEND) && GetSetBit(BTSC, NOANSCON))
//    {
//      NACC = 0;                                        // ���������� ������ �������� ������
//      ClearBits(BTSC, NOANSCON);                       // ������������� ������ �������� ������
//      ClearBits(GSMFC, GSMNOSEND);                     // ���������� ���� ������� �������� �� GSM ������
//      if (GPRSLEVEL == 2) SetBits(TREKSC, GPRSRST);    // ������������� ���� ������������� ����������������� GPRS
//      DispBuffer[0] = strcpy(DispBuffer[0], NumBuffer);
//    }
//    return;
//  }
//  if ((strcmp(Msg, "SEND OK") == 0))
//  {
//    SetBits(GSMFC, SENDOK);                    // ���� �������� SEND OK, ��������� ��������������� ����
//    return;
//  }
//  if (strcmp(Msg, ">") == 0)                // ���� �������� ������ ">"
//  {
//    SetBits(GSMFC, ANGBR);
//    return;
//  }
//  if (strcmp(Msg, "CLOSED") == 0)
//  {
//    SetBits(GSMFC, CLOSED);              // ������������� ���, ��� ������ CLOSED
//    SetBits(TREKSC3, CCRST);             // ������������� ��� ������������� ���������������
//    ClearBits(TREKSC, GPRSCC);           // ���������� ���� ���������� ����������� ����������
//    TX_OFF;                              // ���������
//    F_5_OFF;                             // ���������
//    return;
//  }
//  //--------------------------------------------------------------------------------------------------------------------
//  if (strcmp(Msg, "CONNECT OK") == 0)
//  {
//    SetBits(GSMFC, CONNECT_OK);          // ���� ����������, ���������� ��������� ��������������� ����
//    ClearBits(BTSC, NOANSCON);           // ������������� ������ �������� ������
//    NACC = 0;                            // ���������� ������ �������� ������
//    SetBits(TREKSC2, CONN1);             // ������������� ���� ������������ �� ���������� ���������� (+�IPCCON: 1)
//    ClearBits(TREKSC2, CONN2);           // ���������� ���� ������������ �� ��������� ���������� (+�IPCCON: 2)
//    SetBits(TREKSC, GPRSCC);             // ������������� ���� ���������� ����������� ����������
//    TX_ON;                               // ���������
//    F_5_OFF;                             // ���������
//    return;
//  }
//  if ((strcmp(Msg, "CONNECT FAIL") == 0))
//  {
//    SetBits(GSMFC, CONNECT_FAIL);        // ���� �� ����������, ���������� ��������� ��������������� ����
//    ClearBits(BTSC, NOANSCON);           // ������������� ������ �������� ������
//    NACC = 0;                            // ���������� ������ �������� ������
//    ClearBits(TREKSC, GPRSCC);           // ���������� ���� ���������� ����������� ����������
//    SetBits(TREKSC3, CCRST);             // ������������� ��� ������������� ����������������� ����������� ����������
//    TX_OFF;                              // ���������
//    F_5_OFF;                             // ���������
//    SetBits(BTSC, NOSERVCONWAIT);        // ��������� ������ ��������� ����� ��������� �������� ���������� � �������� ����� ���������
//    return;
//  }
//
////----------------------------  ����������� IP ������ ------------------------------------------------------------------
//  if (GetSetBit(TREKSC, IP) && (MyIP == 0))  // ��������� ��������� �� ������ IP ������
//  {
//    if ((LengthMessage >= 7) && (LengthMessage <= 15))  // ���������� �������� �� ��������� IP �������
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
//        StrToIP(Msg, MyIP);                  // ���� ��������� �������� IP �������, �� ��������� ��������
//        ClearBits(BTSC, IPWAIT);             // ������������� ������ �������� IP ������
//        IPWaitC = 0;                         // ���������� ������ �������� IP ������
//        ClearBits(TREKSC, IP);               // ������� ��� �������� IP ������
//      }
//    }
//  }
////----------------------------------------------------------------------------------------------------------------------
//  if (strstr(Msg,"RING") != NULL)
//  {
//    ArrowDWN_ON;                               // ��������� ��������� ������
//    if (GetSetBit(TREKSC, CH2F)) Amp_ON();      // �������� ��������������
//    SetBits(TREKSC2, GSMRING);                 // ������������� ���� ��������� ������
//    return;
//  }
//  if ((strstr(Msg,"NO CARRIER") != NULL) || (strstr(Msg,"BUSY") != NULL))
//  {
//    ClearBits(TREKSC, GSMCINC + GSMCOTC);
//    ClearBits(TREKSC2, GSMRING);
//    Amp_OFF();                                 // ��������� ��������������
//    ArrowUP_OFF;                               // ����� ��������� ������(����������)
//    ArrowDWN_OFF;                              // ����� ��������� ������(���������)
//    if (strstr(Msg,"BUSY"))
//    {
//      ArrowLF_ON;                              // ��������� ��������� ����������� ������
//      ArrowRT_ON;                              // ��������� ��������� ����������� ������
////      DispBuffer[1] = strcpy(DispBuffer[2], "busy"); // �������� busy, ���� ������
////      SetBits(BTSC, SWAPDB);                         // ...
//    }
//    return;
//  }
//  if ((strcmp(Msg, "UNDERVOLTAGE POWER DOWN") == 0) || (strstr(Msg, "UNDERVOLTAGE")) != NULL)
//  {
//    GPRSLEVEL = 0 ;                      // ���������� ������� GPRS ����������� � 0
//    GSMSignalLevel = 0;                  // ���������� ������� ������� GSM ���� � 0
//    Antena_ANT_OFF;
//    Dollar_OFF;
//    TX_OFF;
//    ClearBits(TREKSC, GSMREG + GPRSSC + GPRSCC + GPRSSA + GSMCINC + GSMCOTC +   // ������� ���� ���������� GSM ������ � GPRS
//    GPRSRST + GSMEN + IP + CH1F + CH2F + DEVBUSY);                            // ���������� � ��. ����� ��������� � GSM
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
//    GPRSLEVEL = 0 ;                      // ���������� ������� GPRS ����������� � 0
//    GSMSignalLevel = 0;                  // ���������� ������� ������� GSM ���� � 0
//    Antena_ANT_OFF;
//    Dollar_OFF;
//    TX_OFF;
//    ClearBits(TREKSC, GSMREG + GPRSSC + GPRSCC + GPRSSA + GSMCINC + GSMCOTC +   // ������� ���� ���������� GSM ������ � GPRS
//    GPRSRST + GSMEN + IP + CH1F + CH2F + DEVBUSY);                            // ���������� � ��. ����� ��������� � GSM
//    GSMFC = 0;
//    ClearBits(TREKSC2, GSMRING + CHECKPARAM + CIICRNA + CONN1 + CONN2 +  NOGETIP);
//    ClearBits(TREKSC3, CCRST);
//    return;
//  }
////-------------------------- ���������������� ������� -----------------------------------------------------
//  //-----------------------------------------------------------------------------------------------------------
//  if ( (strcmp(Msg, "#gps") == 0) || (strcmp(Msg, "#GPS") == 0))  // ���� ��������� ������ ���������, ��  ...
//  {
//    SetBits(USERCOMSC, REQCOORD);
//    return;
//  }
////-----------------------------------------------------------------------------------------------------------------
  return;
};

    
    
    


  
//char SendGSMResMessage(char* Msg) // ������� �������� ��������� ��������� � GSM ������
//{                                   // � ������� ������ � ��������������� ����������
//  char hMsgAr[17];
//  char* hMsg = &hMsgAr[0];
//  char i, j;
//


//  if (strlen(Msg) >= MsgLength)
//  {
//    ErrorIndication(LongMsgRes, 1);  // ���� ����� ��������� ��������� ������ ����� � MMBMsg, ��    // !!!!!!!!!!!!!!!!!!!!!!!!!
//    Msg[MsgLength] = 0x00;                                         // ������� ���������
//  }
//  if (strcmp(Msg, "") == 0) return RET_OK; // ���� ��������� ������, �� �� ������������
//  if (strncmp(Msg, "+CMGR", 5) == 0) // ���� ��������� ��������� SMS ���������, �� �������� �����, � �������� ������ ���������
//  {
//    GetGSMData(Msg, hMsg, 2);
//    j = strlen(hMsg);
//    for(i = 0; i < j; i++)
//    {
//      hMsg[i]  = hMsg[i + 1];
//    }
//    hMsg[j - 2] = 0x00;
//       //   Verification, ����� ������ ����������� ����������� � (�����������)XOR(�������)
//       //     ���� �������������� �������� ������ SMS � ������� ������
//    if (strcmp(hMsg, MDispPhone) == 0) SetBits(GSMFC, SMSWAIT);  // ���� ��������� ������ � ������ ����������, �� ���������� ��� �������� SMS
//    else SetBits(GSMFC, NOBUFFSEND);                             // , � ���� ��� �� ���������� ��� �������������� �������� ������ SMS
//    return RET_OK;
//  }
//  if (strncmp(Msg, "+CMGL:", 6) == 0)
//  {
//    hMsg = strncpy(hMsg, Msg + 6, 3);
//    Msg = strcpy(Msg, "+CMTI: \"SM\",");
//    Msg = strcat(Msg, hMsg);
//    SetBits(GSMFC, NOBUFFSEND);
//  }
////------------------ ����������� ������ ----------------------------------------
//  for (char i = 0; i <= (MMBufferSize-1); i++) // ���� ��������� ������ � ������� �������
//  {
//    if (MMBMsg[i][0] == 0x00) // ���� �����, ������� ���������
//    {
//      MMBMsg[i] = strcpy(MMBMsg[i], Msg);
//      NMMMBuffer++;
//      return RET_OK;
//    }
//  }
////------------------------------------------------------------------------------
//  return RET_ERROR; // ���� ��������� ������
//};  
  
  
//   unsigned short int l = 0;
//
//  if (GetSetBit(IFG2, UCA0RXIFG))              // ���� ������ ������ � GSM ������ ...
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
//      if (((RXGSMMsg[l-2] == 0x0D) && (RXGSMMsg[l-1] == 0x0A)) || (l == SMSMsgLength - 1)) // ���� ������� ����� ������ ��� ������ ������� �������
//      {
//        if (l == SMSMsgLength - 1) l = l + 3;   // ���� ������ ������� ������� �������� �� �������� 0x00
//        RXGSMMsg[l-2] = 0x00;
//        l = strlen(RXGSMMsg);
//        if (l != 0)
//        {
//          GSMFlowStop();                 // ������������� ����� ��������� � GSM ������
//          switch (SendGSMResMsg(RXGSMMsg))  // ���������� ����������� �������� ��������� � ������� ������
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
//        RXGSMMsg[0] = 0x00;          // �������� �������� ������ ��������� �� GSM ������
//        return;
//      }
//    }
//  }
//
//  if (GetSetBit(IFG2, UCB0RXIFG))          // ���� ������ ������ � SD/MMC �����, �� ...
//  {
////    F_4_ON;
//  }