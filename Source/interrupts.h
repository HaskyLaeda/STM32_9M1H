#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H
//==============================================================================
#include "includes.h"

  #ifdef __cplusplus
    extern "C"
    {
  #endif
  //============================================================================
      
    void SysTick_Handler(void);
    void USART1_IRQHandler(void);
    
        
  //============================================================================   
  #ifdef __cplusplus
   }
  #endif
//==============================================================================
#endif //__INTERRUPTS_H
//=============================================  EOF  ==================================================================