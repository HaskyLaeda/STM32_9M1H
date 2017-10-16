///======================================================================================================================
//  28.06.2015         ver.  0.0.1             Name: STM32F10xXX_USART.h
//  Name: STM32F10xXX_SPI.h
//  Description: Different function for init and direct USARTx of STM32F10xXX Series
//  Author: Shiliakin Alexandr aka Hasky Laeda
//======================================================================================================================

#ifndef __STM32F10xXX_SPI_H          // Avoid multiple inclusion
  #define __STM32F10xXX_SPI_H
  
  #include "includes.h"                  // Master file of includes
  #include "DataTypes.h"

  #ifdef __cplusplus
    extern "C"
    {
  #endif

//======================================================================================================================
//                                               Macros
//======================================================================================================================




//======================================================================================================================
//                                               Types
//======================================================================================================================

#define SPI_1   (1) 
#define SPI_2   (2)

  // Тип модуля SPI
//typedef enum
//{
//    SPI0 = 0,
//    SSP  = 1,
//    SPI1 = 1
//} TSPI_Channel;

  // Тип режима SPI
typedef enum
{
    Slave = 0,	
    Master = 1
} TSPI_Mode;

  // Тип полярности SPI
typedef enum
{
    Positive = 0,	
    Negative = 1
} TSPI_Polarity;

  // Тип захвата данных SPI
typedef enum
{
    LatchShift = 0,	
    ShiftLatch = 1
} TSPI_CPHA;

  // Тип порядка передачи данных через SPI
typedef enum
{
    MSB = 0,
    LSB = 1
} TSPI_OrderBit;

  // Тип размера передачи данных через SPI0
typedef enum
{
    SPI0_DataSize8bit  =  8,
    SPI0_DataSize9bit  =  9,
    SPI0_DataSize10bit = 10,
    SPI0_DataSize11bit = 11,
    SPI0_DataSize12bit = 12,
    SPI0_DataSize13bit = 13,
    SPI0_DataSize14bit = 14,
    SPI0_DataSize15bit = 15,
    SPI0_DataSize16bit =  0
} TSPI0_DataSize;

  // Тип размера передачи данных через SPI1
typedef enum
{
    SPI1_DataSize4bit  =  3,
    SPI1_DataSize5bit  =  4,
    SPI1_DataSize6bit  =  5,
    SPI1_DataSize7bit  =  6,
    SPI1_DataSize8bit  =  7,
    SPI1_DataSize9bit  =  8,
    SPI1_DataSize10bit =  9,
    SPI1_DataSize11bit = 10,
    SPI1_DataSize12bit = 11,
    SPI1_DataSize13bit = 12,
    SPI1_DataSize14bit = 13,
    SPI1_DataSize15bit = 14,
    SPI1_DataSize16bit = 15
} TSPI1_DataSize;

  // Тип режима работы модуля SPI1 (SSP)
typedef enum
{
    SPI       = 0,
    SSI       = 1,
    Microwire = 2
} TSPI1_FrameFormat;

    // Type of SPI1 Interrupts
typedef enum
{
    SPI1_NoneInterrupt = (0 << 0),
    SPI1_ROR_Interrupt = (1 << 0),
    SPI1_RT_Interrupt  = (1 << 1),
    SPI1_RX_Interrupt  = (1 << 2),
    SPI1_TX_Interrupt  = (1 << 3)
} TSPI1_Interrupts;

  // Тип настроек SPI0
typedef struct
{
    TSPI_Mode Mode;            // Режим работы SPI (Master or Slave)
    TSPI_Polarity Polarity;    // Тип полярности SPI (Positive or Negative = 1)
    TSPI_CPHA CPHA;            // Тип захвата данных (LatchShift = 0, ShiftLatch = 1)
    TSPI0_DataSize DataSize;   // Размер передаваемых данных за раз
    INT8U Divisor;             // Делитель частоты pclk (от 8 до 254, только четные значения)
    TSPI_OrderBit OrderBit;    // Порядок передачи бит данных (MSB or LSB)
    bool InterruptEnable;      // Разрешить прерываня от SPI0 ?
} TSPI0_Config;

  // Тип настроек SPI1
typedef struct
{
    TSPI1_FrameFormat FrameFormat; // Режим работы модуля SPI (SPI, SSI, Microwire)
    TSPI_Mode Mode;                // Режим работы (Master, Slave)
    TSPI_Polarity Polarity;        // (This field is used only in SPI mode)
    TSPI_CPHA CPHA;                // (This field is used only in SPI mode)
    TSPI1_DataSize DataSize;       // Размер передаваемых данных за раз
    INT16U Divisor;                // Делитель частоты pclk (от 2 до 65024 only event, SSP slave mode: pclk/Divisor < pclk/12)
    bool LoopBackMode;             // Включить LoopBackMode ?(LoopBackMode: when MISO connect with MOSI )
    bool SlaveOutputDisable;       // Выключить MISO ?
    INT8U InterruptMask;      // Маска разрешенных прерываний
} TSPI1_Config;

//======================================================================================================================
//                                               Interface
//======================================================================================================================
//                                             API functions

Int32 Init_SPI(Int32 SPI_Channel, TSPI_Mode Mode);
Int32 SPI_TransmitData (Int32 SPI_Channel, const INT16U TX_data, INT16U *RX_data);

//Int32 Init_SPI(Int32 SPI_Channel, TSPI_Mode, TSPI_Polarity Polarity, TSPI_CPHA CPHA,
//               Int8U Divisor, TSPI_OrderBit OrderBit, bool InterruptEnable);


               
//Int32 SPI0_Init(TSPI_Mode Mode, TSPI_Polarity Polarity, TSPI_CPHA CPHA, TSPI0_DataSize DataSize,
//                Int8U Divisor, TSPI_OrderBit OrderBit, bool InterruptEnable);
//Int32 SPI1_Init(TSPI1_FrameFormat FrameFormat, TSPI_Mode Mode, TSPI_Polarity Polarity, TSPI_CPHA CPHA,
//                TSPI1_DataSize DataSize, Int16U Divisor,bool LoopBackMode, bool SlaveOutputDisable, Int8U InterruptMask);
//Int32 SPI_SetConfig(TSPI_Channel SPI_Num);
//  //Transmit data by SPI (data may be not only 8 bit, max data size 16 bit)
//Int32 SPI_TransmitData (TSPI_Channel SPI_Num, const INT16U TX_data, INT16U *RX_data);
//  //Receive data by SPI (data may be not only 8 bit, max data size 16 bit)
//Int32 SPI_ReceiveData (TSPI_Channel SPI_Num, const INT16U TX_data, INT16U *RX_data);
//
//void SPI0_ISR (void);
//void SPI1_ISR (void);

//======================================================================================================================

  #ifdef __cplusplus
   }
  #endif

//======================================================================================================================
#endif  // __STM32F10xXX_SPI_H    // Avoid multiple inclusion

//=============================================  EOF  ==================================================================
