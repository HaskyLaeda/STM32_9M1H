//======================================================================================================================
//  28.06.2015         ver.  0.0.1             Name: STM32F10xXX_USART.h
//  Name: STM32F10xXX_USART.h
//  Description: Different function for init and direct USARTx of STM32F10xXX Series
//  Author: Shiliakin Alexandr aka Hasky Laeda
//======================================================================================================================

#ifndef __STM32F10xXX_USART_H          // Avoid multiple inclusion
  #define __STM32F10xXX_USART_H
  
  #include "includes.h"                  // Master file of includes
  #include "DataTypes.h"

  #ifdef __cplusplus
    extern "C"
    {
  #endif


//======================================================================================================================
//                                               Macros
//======================================================================================================================

    // USART/UART channel
  #define USART_1                 (0x1)
  #define USART_2                 (0x2)
  #define USART_3                 (0x3)
  #define UART_4                  (0x4)
  #define UART_5                  (0x5)
  

  #define RX_BUFFER_SIZE          (256)     // ������ ������ ������ ������� USART
  #define TX_BUFFER_SIZE          (256)     // ������ ������ �������� ������� USART
//  #define FIFODEEP                (16)      // ������ ���������� ������� �������� � ������

    // Standart Baudrate
  #define BR_115200               (115200)  // C������� 115200 ���
  #define BR_57600                (57600)   // C������� 57600 ���
  #define BR_38400                (38400)   // C������� 38400 ���
  #define BR_19200                (19200)   // C������� 19200 ���
  #define BR_9600                 (9600)    // C������� 9600 ���

    // Uart Interrupt Identification
  #define IIR_RSL                 (0x3)
  #define IIR_RDA                 (0x2)
  #define IIR_CTI                 (0x6)
  #define IIR_THRE                (0x1)





//======================================================================================================================
//                                               Types
//======================================================================================================================
   
   // Word Length type
typedef enum
{
    WordLength5 = 0,   // ����� ������ � ������� 5 bit
    WordLength6 = 1,   // ����� ������ � ������� 6 bit
    WordLength7 = 2,   // ����� ������ � ������� 7 bit
    WordLength8 = 3    // ����� ������ � ������� 8 bit
} TUSART_WordLength;

  // Parity Select type
typedef enum
{
    StopBitOne = 0,    // ���� �������� ���
    StopBitTwo = 1,    // ��� �������� ����
} TStopBitNum;

  // Parity Select type
typedef enum
{
    ParityOdd       = 0,  // �������� �� ����������
    ParityEven      = 1,  // �������� �� ��������
    ParityStickHigh = 2,  // ��������������� ���������� 1 � ���� ��������
    ParityEvenLow   = 3,  // ��������������� ���������� 0 � ���� ��������
    ParityNone      = 4   // ��� �������� �� ��������
} TUSART_Parity;

  // FIFO Rx Trigger Level type ( ������� ������������ �������(����������(RDA) ��� ������))
typedef enum
{
    FIFO_RX_Level0 = 0,   // 0x1    1 ����
    FIFO_RX_Level1 = 1,   // 0x4    4 ����
    FIFO_RX_Level2 = 2,   // 0x8    8 ����
    FIFO_RX_Level3 = 3    // 0xe   14 ����
} TUSART_FIFO_RxTriggerLevel;

  // USART Interrupt type
typedef enum
{
    NoneInterrupt = 0,
    RBR       = (1 << 0),  // RDA, CRT/CTI
    THRE      = (1 << 1),  // THRE
    RLS       = (1 << 2),  // OE, PE, FE, RXFE
    ABTOIntEn = (1 << 8),  //
    ABEOIntEn = (1 << 9),
} TUSART_InterruptEnable;

typedef struct
{
    Int8U RxBuffer[RX_BUFFER_SIZE];  // ������ ������
    Int8U TxBuffer[TX_BUFFER_SIZE];  // ������ ��������
    Int32U RxHeadPoint;              // ��������� �� ������ ������� ������
    Int32U RxTailPoint;              // ��������� �� ����� ������� ��������
    Int32U TxHeadPoint;              // ��������� �� ������ ������� ������
    Int32U TxTailPoint;              // ��������� �� ����� ������� ��������
    Int32U RxCount;                  // ���������� ���� � ������� ������
    Int32U TxCount;                  // ���������� ���� � ������� ��������
    union
    {
      Int32U ErrorFlags;             // ����� ������
      struct
      {
        Int32U FIFO_OverrunError : 1;
        Int32U OverrunError      : 1;
        Int32U ParityError       : 1;
        Int32U FramingError      : 1;
        Int32U BreakIndication   : 1;
      };
    };
} TUSART_Buffer;

typedef struct
{
    Int32U BaudRate;              // Baud Rate (�������� max 115200 ���)
    TUSART_WordLength WordLength; // ����� ������������ ������ (WordLength5 ... WordLength8)
    TStopBitNum StopBitNum;       // ���������� �������� ����� (StopBitOne or StopBitTwo)
    TUSART_Parity USART_Parity;   // Parity mode (������ �������� ParityOdd, ParityEven, ParityStickHigh, ParityEvenLow or ParityNone)
    bool BreakEnable;             // (��������� �������� �������� ?)
    bool FIFO_Enable;             // (������������ ��  FIFO ����� ?)
    TUSART_FIFO_RxTriggerLevel FIFO_RxTriggerLevel;  // (������� ���������� ����������� ������� ��� ������������� ����������)
    Int32U InterruptEnable ;      // Interrupt Type: RBR, THRE, RLS
    TUSART_Buffer USART_Buffer;   // ������ ������ � ��������
} TUSART_Config;

//======================================================================================================================
//                                               Interface
//======================================================================================================================

void InitUSART1(void);


//Int32 USART_Init(TSUSART_Channel USART_Num, Int32U Fpclk, Int32U BaudRate, TSUSART_WordLength WordLength,
//                TStopBitNum StopBitNum, TSUSART_Parity USART_Parity, bool BreakEnable, bool FIFO_Enable,
//                TSUSART_FIFO_RxTriggerLevel FIFO_RxTriggerLevel, Int32U InterruptEnable);
//Int32  USART_SetConfig(TSUSART_Channel USART_Num, Int32U Fpclk);

Int32  USART_SendCharPolling(Int32U USART_Channel, Int8U DataChar);
Int32U USART_SendStringPolling(Int32U USART_Channel, pInt8U pString);
Int32U USART_SendDataPolling(Int32U USART_Channel, pInt8U pDataBlock, Int32U SizeDataBlock);
//Int32  USART_GetCharPolling(Int32U USART_Channel, Int8U *Buf);
//
//Int32U USART_SendString(TUSART_Channel USART_Num, Int8U *Buf);
//Int32  USART_SendChar( TUSART_Channel USART_Num, Int8U DataChar);
//Int32  USART_GetChar(TUSART_Channel USART_Num, Int8U *ch);
//
//void ISR_USART0(void);
//void ISR_USART1(void);


//======================================================================================================================
  #ifdef __cplusplus
   }
  #endif
//======================================================================================================================
#endif //__STM32F10xXX_USART_H
//=============================================  EOF  ==================================================================