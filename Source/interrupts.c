#include "interrupts.h"

extern Int8U Flag1;


  //------------- System timer IRQ --------------------
void SysTick_Handler(void)
{
  static unsigned int volatile i;
//  static unsigned int volatile j;  
  i++;
//  j++;
  if (i == 1000)
  {
    i = 0;
    Flag1 = 0;
  }  
  return;
}

  //------------- USART1_IRQ IRQ --------------------
void USART1_IRQHandler(void)
{
  volatile unsigned long DataByte;
////    if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
////    {
////        USART_SendData(USART1, usartData[usartCounter]);
////        usartCounter++;
////    }
////    USART_ClearITPendingBit(USART1, USART_IT_TC);
   
  if (USART1->SR & USART_SR_RXNE) {
    DataByte = USART1->DR;
    USART1->DR = (unsigned char) DataByte;
  }     
}

