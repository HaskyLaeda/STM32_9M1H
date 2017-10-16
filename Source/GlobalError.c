//======================================================================================================================
//  28.06.2015         ver.  0.0.1             
//  Name: GlobalError.h
//  Description: Different macros, function, types for indication and except action in case error ocur.
//  Author: Shiliakin Alexandr aka Hasky Laeda
//======================================================================================================================

#include "GlobalError.h"

//======================================================================================================================
//                                 Macros
//======================================================================================================================



//======================================================================================================================
//                                 External variable
//======================================================================================================================


//======================================================================================================================
//                                 Global variables
//======================================================================================================================

TGlobalError GlobalError;

//======================================================================================================================
//                                 Implementations
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
// Name: ErrorIndication
// Parametr: TGlobalError GlobalError
// Description: Indication Error on display or any other indication device trought ErrorCode pass; 
// Return: void
//----------------------------------------------------------------------------------------------------------------------
void ErrorIndication(TGlobalError * pGlobalError)
{
//  switch (pGlobalError->ErrorCode)
//  {  
//    case FILE_SYSTEM_CREATE_ERROR:
//    break;
//    case FILE_OPEN_ERROR:
//    break;      
//    case FILE_READ_ERROR:
//    break;      
//    case FILE_WRITE_ERROR:
//    break;          
//  }  
  return;
};


//----------------------------------------------------------------------------------------------------------------------
// Name: RiseGlobalError
// Parametr: TGlobalError - error code.
// Description: Do infinity cycle for determine error. Use for debugging. See Error describe in GNOM_main.h
// Return:  void
//----------------------------------------------------------------------------------------------------------------------    
void RiseGlobalError(TGlobalError * pGlobalError, const Int8U ErrorCode, const Int8U ShowError, const Int8U DoStop)
{  
  pGlobalError->ErrorCode = ErrorCode;
  pGlobalError->ShowError = ShowError;
  pGlobalError->DoStop = DoStop;    
  
  if (pGlobalError->DoStop)               // Если необходимо остановить дальнейшее выполнение программы
  {
    if (pGlobalError->ShowError)            // если необходимо отобразить код ошибки индикацией
    {
      pGlobalError->ShowError = 0;     // сбрасываем флаг необходимости индикации ошибки
      ErrorIndication(pGlobalError);              // отображаем ошибку индикацией
    }  
    while (ErrorCode);  // See Error describe in GNOM_main.h
  }  
  return;
};

//=============================================  EOF  ==================================================================
