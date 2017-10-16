//======================================================================================================================
//  31.03.2011         ver.  0.0.1             Used with IAR Embeded Worckbench for ARM v5.51
//  Name: LPC_SPI.c
//  Description: Different function for init and direct SPI0 and SPI1
//  Author: Shiliakin Alexandr aka Hasky Laeda
//======================================================================================================================

#include "includes.h"            // Master file of includes
#include "STM32F10xXX_SPI.h"   

//======================================================================================================================
//                                 Macros
//======================================================================================================================



//======================================================================================================================
//                                 External variable
//======================================================================================================================


//======================================================================================================================
//                                 Global variables
//======================================================================================================================

//TSPI0_Config SPI0_Config =
//  {Master, Positive, LatchShift, SPI0_DataSize8bit, (Int8U)10, LSB, false};							
//TSPI1_Config SPI1_Config =
//  {SPI, Master, Positive, LatchShift, SPI1_DataSize8bit, (Int16U)10, false, false, SPI1_NoneInterrupt};

//======================================================================================================================
//                                 Implementations
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
// Function Name: SPI0_Init
// Parameters: TSPI_Mode Mode - Master or Slave mode
//             TSPI_Polarity Polarity - Positive or Negative polarity
//             TSPI_CPHA CPHA - capture data mode (LatchShift or ShiftLatch)
//             TSPI0_DataSize DataSize - size of data in bits
//             Int8U Divisor - divisor of Fpclk set speed rate of SPI module
//             TSPI_OrderBit OrderBit - order bit of transmit data (LSB or MSB)
//             bool InterruptEnable - define allow interrupt or not
// Description:  Form SPI0 config struct
// Return: Int32  0: success init
//	   non-zero: error number (2: Invalid Divisor Value ��. LPC_SPI.h
//                                 3: Invalid Mode ��. LPC_SPI.h
//                                 4: Invalid CPHA ��. LPC_SPI.h
//                                 5: Invalid Polarity ��. LPC_SPI.h
//                                 6: Invalid OrderBit ��. LPC_SPI.h
//                                 7: Invalid DataSize ��. LPC_SPI.h
//----------------------------------------------------------------------------------------------------------------------

//Int32 Init_SPI(Int32 SPI_Channel, TSPI_Mode, TSPI_Polarity Polarity, TSPI_CPHA CPHA, Int8U Divisor,
//               TSPI_OrderBit OrderBit, bool InterruptEnable)

Int32 Init_SPI(Int32 SPI_Channel, TSPI_Mode Mode)
{
  switch (SPI_Channel)
  {
     case SPI_1:
     {  
       RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;  // ������������ ������ SPI1
       
       
       SPI1->CR1 |= (SPI_CR1_MSTR & (Mode << 2));  // ����� Master(Mode = 1) or Slave (Mode = 0)
       SPI1->CR1 |= SPI_CR1_BR;                  // Baud rate = Fpclk/256
//       SPI1->CR1 |= SPI_CR1_BR_0;                  // ...
//       SPI1->CR1 |= SPI_CR1_BR_1;                  // Baud rate = Fpclk/16 = 4.5 Mbit/s       
//       SPI1->CR1 |= SPI_CR1_BR_2;                  // ...

       
       
       SPI1->CR1 |= SPI_CR1_CPOL;                  // ���������� ��������� ������� (CPOL = 1) �.�. �������������
       SPI1->CR1 |= SPI_CR1_CPHA;                  // ���� ��������� ������� �.�. �� ������� ������
       SPI1->CR1 &= ~SPI_CR1_DFF;                  // ���� SPI_CR1_DFF = 0, �� 8 ��� ������, ����� 16 ��� ������
       SPI1->CR1 &= ~SPI_CR1_LSBFIRST;             // MSB ���������� ������
       SPI1->CR1 |= SPI_CR1_SSM;                   // �������� ����������� ����� ���������� NSS 
       SPI1->CR1 |= SPI_CR1_SSI;                   // ��������� ������� ������� �� NSS
       SPI1->CR1 &= ~SPI_CR1_CRCEN;                //  1- ��������, 0-��������� ������ CRC
       SPI1->CR1 &= ~SPI_CR1_CRCNEXT;              // ���� CRCNEXT = 1, �� ����� ��������� �������� ����� �������� ����������� �����
                        
       SPI1->CR2 &= ~SPI_CR2_SSOE;                 // SPI_CR2_SSOE = 0 - �� ������������ ����� NSS ()
       
       
       SPI1->CR1 |= SPI_CR1_SPE;                   // �������� SPI1    
       break;
     }  
     case SPI_2:
     {  
       RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;  // ������������ ������ SPI2
       
       SPI2->CR1 |= (SPI_CR1_MSTR & (Mode << 2));  // ����� Master(Mode = 1) or Slave (Mode = 0)
       SPI2->CR1 |= SPI_CR1_BR;                  // Baud rate = Fpclk/256
//       SPI1->CR1 |= SPI_CR1_BR_0;                  // ...
//       SPI1->CR1 |= SPI_CR1_BR_1;                  // Baud rate = Fpclk/16 = 4.5 Mbit/s       
//       SPI1->CR1 |= SPI_CR1_BR_2;                  // ...

       
       SPI2->CR1 |= SPI_CR1_CPOL;                  // ���������� ��������� ������� (CPOL = 1) �.�. �������������
       SPI2->CR1 |= SPI_CR1_CPHA;                  // ���� ��������� ������� �.�. �� ������� ������
       SPI2->CR1 &= ~SPI_CR1_DFF;                  // ���� SPI_CR1_DFF = 0, �� 8 ��� ������, ����� 16 ��� ������
       SPI2->CR1 &= ~SPI_CR1_LSBFIRST;             // MSB ���������� ������
       SPI2->CR1 |= SPI_CR1_SSM;                   // �������� ����������� ����� ���������� NSS 
       SPI2->CR1 |= SPI_CR1_SSI;                   // ��������� ������� ������� �� NSS
       SPI2->CR1 &= ~SPI_CR1_CRCEN;                //  1- ��������, 0-��������� ������ CRC
       SPI2->CR1 &= ~SPI_CR1_CRCNEXT;              // ���� CRCNEXT = 1, �� ����� ��������� �������� ����� �������� ����������� �����
                        
       SPI2->CR2 &= ~SPI_CR2_SSOE;                 // SPI_CR2_SSOE = 0 - �� ������������ ����� NSS ()
       
       
       SPI2->CR1 |= SPI_CR1_SPE;                   // �������� SPI2           
       break;
     }     
  }   
  return 0;
}


////----------------------------------------------------------------------------------------------------------------------
//// Function Name: SPI_TransmitData
//// Parameters: TSPI_Channel SPI_Num - SPI module type
////             Int16U TX_Data - transmiting data
////             pInt16U RX_Data - pointer on bufer for reciving data (NULL - mean that data will not be return)
//// Description: Transmit data by SPI
//// Return: Int32  0: success init
////	       non-zero: error number (1: Invalid SPI_Num (��. LPC_SPI.h)
////                                 2: ������ ����������� (����������)
////                                 3: ������ ��������� ����������� ������ ABRT (��.UserManual)
////                                 4: ������ ������ MODF (��.UserManual)
////                                 5: ������ ������ WCOL (��.UserManual))
////----------------------------------------------------------------------------------------------------------------------

//Int32 SPI_TransmitData (TSPI_Channel SPI_Num, Int16U TX_Data, pInt16U RX_Data)
//{
//  Int8U hbait;
//  volatile Int16U h2bait;
//
//  switch (SPI_Num)
//  {
//    case SPI0:
//    {
//      S0SPDR = TX_Data;                               // ���������� ���� �� ����� ��������
//      hbait = S0SPSR;                                 // ��������� ���� �������
//      while (!(hbait & (S0SPSR_SPIF | S0SPSR_WCOL)))  // ���� �� ����� ���������� ��� S0SPSR_SPIF ��� S0SPSR_WCOL
//      {
//        if (hbait & S0SPSR_ABRT)            // ���� �� ����� �������� ��������� ABRT
//          return S0SPSR_ABRT;                 // ������� � �������
//        if (hbait & S0SPSR_MODF)            // ���� �� ����� �������� ��������� MODF
//        {
//          if (SPI0_Config.Mode == Master)     //  ���� � ��������� ������������ ��� ����� Maste, �� ...
//            S0SPCR |= (INT8U)(1 << 5);          // ������ ������ � ������� ����������
//
//          return S0SPSR_MODF;                 // ������� � ������� MODF
//        }
//        hbait = S0SPSR;                     // ��������� ���������� �� �������� �������
//      }
//      if (hbait & S0SPSR_WCOL)              // ���� �� ����� �������� ��������� WCOL
//      {
//        if (RX_Data != NULL)                  // clear WCOL bit by fiction read data register S0SPDR
//          *RX_Data = S0SPDR;                  // c���������� ��� WCOL ��������� ������� �������� ������
//        else
//          h2bait = S0SPDR;
//        return S0SPSR_WCOL;                   // ������� � ������� WCOL
//      }
//      if (hbait & S0SPSR_SPIF)              // ���� �� ����� �������� ������ �� ���������
//      {
//        if (RX_Data != NULL)                  // c���������� ��� SPIF ������� �������� ������
//          *RX_Data = S0SPDR;
//        else
//          h2bait = S0SPDR;
//        return 0;                             // ������� � �������
//      }
//      return 2;
//    }

//// *************************************************************************
//// * Function Name: SPI0_ISR
//// * Parameters: void
//// * Return: void
//// * Description:SPI0 interrupt subroutine
//// *************************************************************************/
//void SPI0_ISR (void)
//{
////  LPC_INT8U hbyte;
//
//  S0SPINT_bit.SPIINT = 1;   // Clear Interrupt flag in registr
//
//
////  hbyte = (LPC_INT8U)S0SPSR;
////  if (hbyte & SPSR_WCOL)
////  {
////    // Add code of processing this situation
////    return;
////  }
////  if (hbyte & SPSR_SPIF)
////  {
////    // Add code of processing this situation
////    return;
////  }
//
//  VICVectAddr = 0;    // Clear interrupt in VIC.
//  return;
//}
//
/////*************************************************************************
//// * Function Name: SPI1_ISR
//// * Parameters: void
//// * Return: void
//// * Description:SPI1 interrupt subroutine
//// *************************************************************************/
//
//void SPI1_ISR (void)
//{
//  switch (SSPMIS & 0x0f)
//  {
//    case SPI1_NoneInterrupt:
//    {
//      return;
//    }
//    case SPI1_ROR_Interrupt:
//    {
//        // yet not support
//
//      SSPICR |= SPI1_ROR_Interrupt; // Clear interrupt flag
//      break;
//    }
//    case SPI1_RT_Interrupt:
//    {
//      // yet not support
//
//      SSPICR |= SPI1_RT_Interrupt; // Clear interrupt flag
//      break;
//    }
//    case SPI1_RX_Interrupt:
//    {
//      // yet not support
//      break;
//    }
//    case SPI1_TX_Interrupt:
//    {
//      // yet not support
//      break;
//    }
//  }                        // Clear Interrupt flag in registr
//  VICVectAddr = 0;         // Clear interrupt in VIC.
//  return;
//}



