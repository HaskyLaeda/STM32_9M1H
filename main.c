#include "main.h"

Int8U Flag1 = 0;
Int8U Order = 0;
Int8U i = 0;

int main()
{
  InitSysTick();
  InitPinout();
  InitUSART1(); 
  NVIC_EnableIRQ (USART1_IRQn);  
  USART_SendStringPolling(USART_1, (pInt8U)"Hellow, world! ");           
  GPIOB->BSRR = GPIO_BSRR_BS1;  // Устанавливаем на выходе PB1 значение 1    
  InitVar();  
  
  
  while(1)
  {  
//    if (!Flag1)
//    {        
//      if (Order) {        
//        GPIOB->BSRR = GPIO_BSRR_BS1;  // Устанавливаем на выходе PB1 значение 1    
////        USART_SendCharPolling(USART_1, 0x41);
////        USART_SendStringPolling(USART_1, "Hellow, world! ");         
//      }
//      else      
////        GPIOB->BRR = GPIO_BRR_BR1;    // Устанавливаем на выходе PB1 значение 0    or
//        GPIOB->BSRR = GPIO_BSRR_BR1;    // Устанавливаем на выходе PB1 значение 0      
//      Order = !Order;
//     
//      Flag1 = 1;
//    }    
    {
       ProcessingMessage();        
    }  
    
  }    
  return 0;
};



