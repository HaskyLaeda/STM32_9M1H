//======================================================================================================================
//  28.06.2015         ver.  0.0.1             
//  Name: GlobalError.h
//  Description: Different macros, function, types for indication and except action in case error ocur.
//  Author: Shiliakin Alexandr aka Hasky Laeda
//======================================================================================================================

#ifndef __GLOBAL_ERROR_H        // Avoid multiple inclusion
  #define __GLOBAL_ERROR_H

  #include "includes.h"         // Master file of includes

//======================================================================================================================
//                                               Macros
//======================================================================================================================

#define GLOBAL_ERROR (1)   // ���������� ������������ �� ����� ������ ���������� ������


//  #define BASE_SPI       (10)
//  #define BASE_USART     (20)
//  #define BASE_TIMER     (30)
  #define BASE_FAT_FS    (40)
  #define BASE_GNOM      (50)


    // ������ ���������� ������ Global ErrorCode
  #define FILE_SYSTEM_CREATE_ERROR    (BASE_FAT_FS  + 1)  // ������ �������� �������� �������
  #define FILE_OPEN_ERROR             (BASE_FAT_FS  + 2)  // ������ �������� �����
  #define FILE_READ_ERROR             (BASE_FAT_FS  + 3)  // ������ ������ �����
  #define FILE_WRITE_ERROR            (BASE_FAT_FS  + 4)  // ������ ������ �����

  #define SPI1_SELECT_ERROR           (BASE_GNOM  +   1)  // Selecting SPI1 device when other device stay selected
  #define DIVISION_BY_ZER0_ERROR      (BASE_GNOM  +   2)  // ������: ������� �� ����
  #define FREQUENCY_CALIBRATION_ERROR (BASE_GNOM  +   3)  // ������ ���������� �������
  #define PLL_ENABLE_ERROR            (BASE_GNOM  +   4)  // ������ ��������� PLL (������� ������������ ��� ���������) 
  #define PARAMETR_OVERRIDING_ERROR   (BASE_GNOM  +   5)  // ������ �������� ��������� ���������� ����� �� ���������� ������


//======================================================================================================================
//                                               Types
//======================================================================================================================

typedef union
{
  Int32U Param;      // �������� ���������� ������
  Int16U ErrorCode;  // ��� ���������� ������ (��� ���������� ������ = ���� + ��� ��������� ������)
  Int16U Falgs;      // ����� ���������
  
  struct
  {
    Int16U          LParam; // ������� ����� ���������
    Int16U          HParam; // ������� ����� ���������
    Int16U            : 16;  
    Int16U ShowError  :  1;  // ���� �������� ��� ������ �� �������� ���������
    Int16U DoStop:       1;  // ���� ���������� ���������� ��������� ��� ������
    Int16U            : 14;  // ...  (��� ������������ �����������)
  };  
} TGlobalError;  // ��� ����������-��������� ���������� ������ 

//======================================================================================================================
//                                               Interface
//======================================================================================================================
//                                             API functions

void RiseGlobalError(TGlobalError * pGlobalError, const Int8U ErrorCode, const Int8U ShowError, const Int8U DoStop);
void ErrorIndication(TGlobalError * pGlobalError);

//======================================================================================================================

#endif  // __GLOBAL_ERROR_H   

//=============================================  EOF  ==================================================================
