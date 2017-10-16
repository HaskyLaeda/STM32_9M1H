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

#define GLOBAL_ERROR (1)   // Определяем использовать ли вызов модуль глобальных ошибок


//  #define BASE_SPI       (10)
//  #define BASE_USART     (20)
//  #define BASE_TIMER     (30)
  #define BASE_FAT_FS    (40)
  #define BASE_GNOM      (50)


    // Список глобальных ошибок Global ErrorCode
  #define FILE_SYSTEM_CREATE_ERROR    (BASE_FAT_FS  + 1)  // Ошибка создания файловой системы
  #define FILE_OPEN_ERROR             (BASE_FAT_FS  + 2)  // Ошибка открытия файла
  #define FILE_READ_ERROR             (BASE_FAT_FS  + 3)  // Ошибка чтения файла
  #define FILE_WRITE_ERROR            (BASE_FAT_FS  + 4)  // Ошибка записи файла

  #define SPI1_SELECT_ERROR           (BASE_GNOM  +   1)  // Selecting SPI1 device when other device stay selected
  #define DIVISION_BY_ZER0_ERROR      (BASE_GNOM  +   2)  // Ошибка: Деление на ноль
  #define FREQUENCY_CALIBRATION_ERROR (BASE_GNOM  +   3)  // Ошибка калибровки частоты
  #define PLL_ENABLE_ERROR            (BASE_GNOM  +   4)  // Ошибка включения PLL (частота тактирования вне диапозона) 
  #define PARAMETR_OVERRIDING_ERROR   (BASE_GNOM  +   5)  // Ошибка большого параметра переменная вышла за допустимый предел


//======================================================================================================================
//                                               Types
//======================================================================================================================

typedef union
{
  Int32U Param;      // Параметр глобальной ошибки
  Int16U ErrorCode;  // Код глобальной ошибки (Код глобальной ошибки = База + Код локальной ошибки)
  Int16U Falgs;      // Флаги состояния
  
  struct
  {
    Int16U          LParam; // Младшее слово параметра
    Int16U          HParam; // Старшее слово параметра
    Int16U            : 16;  
    Int16U ShowError  :  1;  // Флаг показать код ошибки на средстве индикации
    Int16U DoStop:       1;  // Флаг остановить выполнение программы при ошибке
    Int16U            : 14;  // ...  (для выравнивания объединения)
  };  
} TGlobalError;  // Тип обединения-структуры глобальной ошибки 

//======================================================================================================================
//                                               Interface
//======================================================================================================================
//                                             API functions

void RiseGlobalError(TGlobalError * pGlobalError, const Int8U ErrorCode, const Int8U ShowError, const Int8U DoStop);
void ErrorIndication(TGlobalError * pGlobalError);

//======================================================================================================================

#endif  // __GLOBAL_ERROR_H   

//=============================================  EOF  ==================================================================
