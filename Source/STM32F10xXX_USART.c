#include "STM32F10xXX_USART.h"

void InitUSART1(void)
{   
  RCC->APB2ENR |= (RCC_APB2ENR_USART1EN);      // Включаем тактирование USART1 
  USART1->CR1 |= USART_CR1_UE;                 // Включаем USART1   
  USART1->CR1 &= ~USART_CR1_M;                 // Размерность слова данных - 8 бит
//  USART1->CR1 &= ~USART_PS;                    // Задаём тип контроля чётности (USART_CR1_PS = 0 ( 0 - чёт, 1 - нечет.))
  USART1->CR1 &= ~USART_CR1_PCE;               // Отключаем проверку чётности (USART_CR1_PCE = 0)
  USART1->CR2 &= ~USART_CR2_STOP;              // 1 стоп-бит  (USART_CR2_STOP = 00)
  USART1->BRR = 0x1D40;                        // Скорость обмена 9600 бод
//  USART1->BRR = 0x271;                         // Скорость обмена 115200 бод
   // т.е. в итоге получаем 115200 8N1
  USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;  // Включаем передачу и приём по USART1  
  USART1->CR1 |= USART_CR1_RXNEIE;             // Включаем прерывание при получении данных по USART1    
}



Int32  USART_SendCharPolling(Int32U UART_Channel, Int8U DataChar)
{
  switch (UART_Channel) 
  {  
    case USART_1:   
      while(!(USART1->SR & USART_SR_TC));    // Проверка завершения передачи предыдущих данных
      USART1->DR = DataChar;                 // Передача данных 
    break;
    case USART_2:   
      while(!(USART2->SR & USART_SR_TC));    // Проверка завершения передачи предыдущих данных
      USART2->DR = DataChar;                 // Передача данных 
    break;
    case USART_3:   
      while(!(USART3->SR & USART_SR_TC));    // Проверка завершения передачи предыдущих данных
      USART3->DR = DataChar;                 // Передача данных 
    break;
    case UART_4:   
      while(!(UART4->SR & USART_SR_TC));    // Проверка завершения передачи предыдущих данных
      UART4->DR = DataChar;                 // Передача данных 
    break;            
    case UART_5:   
      while(!(UART5->SR & USART_SR_TC));    // Проверка завершения передачи предыдущих данных
      UART5->DR = DataChar;                 // Передача данных 
    break;                
    default:
      return 1;    
  }  
  return 0;
} 

Int32U USART_SendStringPolling(Int32U UART_Channel, pInt8U pString)
{
  Int32U SendCount = 0;  
  
  while (*pString)
  {  
    switch (UART_Channel)
    {
      case USART_1:
        while(!(USART1->SR & USART_SR_TC));
        USART1->DR = *pString++;
      break;
      case USART_2:
        while(!(USART2->SR & USART_SR_TC));
        USART2->DR = *pString++;
      break;
      case USART_3:
        while(!(USART3->SR & USART_SR_TC));
        USART3->DR = *pString++;
      break;
      case UART_4:
        while(!(UART4->SR & USART_SR_TC));
        UART4->DR = *pString++;
      break;
      case UART_5:
        while(!(UART5->SR & USART_SR_TC));
        UART5->DR = *pString++;
      break;
      default:
        return 0;      
    }
    ++SendCount; 
  }
  
  return (SendCount);
};


Int32U USART_SendDataPolling(Int32U UART_Channel, pInt8U pDataBlock, Int32U SizeDataBlock)
{
  Int32U SendCount = 0;
    
  while (SizeDataBlock)
  {  
    switch (UART_Channel)
    {
      case USART_1:
        while(!(USART1->SR & USART_SR_TC));
        USART1->DR = *pDataBlock++;
      break;
      case USART_2:
        while(!(USART2->SR & USART_SR_TC));
        USART2->DR = *pDataBlock++;     
      break;
      case USART_3:
        while(!(USART3->SR & USART_SR_TC));
        USART3->DR = *pDataBlock++;
      break;
      case UART_4:
        while(!(UART4->SR & USART_SR_TC));
        UART4->DR = *pDataBlock++;
      break;
      case UART_5:
        while(!(UART5->SR & USART_SR_TC));
        UART5->DR = *pDataBlock++;
      break;
      default:
        return 1;      
    }
    ++SendCount;
    --SizeDataBlock;          
  }
  return (SendCount);
};
