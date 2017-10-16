#include "UserConfig.h"

void InitSysTick(void)
{
  SysTick->LOAD = 72000;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                  SysTick_CTRL_TICKINT_Msk |
                  SysTick_CTRL_ENABLE_Msk  ;
  return;
}

void InitPinout(void)
{  
  //- - - - - - - - - - -   PORT A   - - - - - - - - - - - - - - - - - - - - - -
  
    // Подключаем к шине APB2 как к источнику тактирование Port A  ( все настройки должны быть после)      
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  
    // Подключаем к шине APB2 тактирование альтернативных функций GPIO 
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;    

//    // Устанавливаем Port A Pin 5 в режим Alternate (SPI1_SCK) 50MHz push-pull
//  GPIOA->CRL |= (GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0);    // MODE5 = 11 
//  GPIOA->CRL |= GPIO_CRL_CNF5_1;                          // ..
//  GPIOA->CRL &= ~GPIO_CRL_CNF5_0;                         // CNF5 = 10 
//  
//    // Устанавливаем Port A Pin 7 в режим Alternate (SPI1_MOSI) 50MHz push-pull
//  GPIOA->CRL |= (GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0);    // MODE7 = 11 
//  GPIOA->CRL |= GPIO_CRL_CNF7_1;                          // ..
//  GPIOA->CRL &= ~GPIO_CRL_CNF7_0;                         // CNF7 = 10

    // Устанавливаем Port A Pin 9 в режим Alternate (USART1 TX) 10MHz push-pull
  GPIOA->CRH |=  GPIO_CRH_MODE9_0;                        // ..
  GPIOA->CRH &= ~GPIO_CRH_MODE9_1;                        // MODE9 = 01 -- 10MHz   
  GPIOA->CRH |=  GPIO_CRH_CNF9_1;                         // ..
  GPIOA->CRH &= ~GPIO_CRH_CNF9_0;                         // CNF9 = 10  -- Alternate TX1
    
    // Устанавливаем Port A Pin 10 в режим Input (USART1 RX) Hi-Z
//  GPIOA->CRH |=  GPIO_CRH_MODE10_0;                       // ..
  GPIOA->CRH &= ~GPIO_CRH_MODE10_0;                       // ..  
  GPIOA->CRH &= ~GPIO_CRH_MODE10_1;                       // MODE10 = 00 -- for input Mode only 0
  GPIOA->CRH &= ~GPIO_CRH_CNF10_1;                        // ..
  GPIOA->CRH |=  GPIO_CRH_CNF10_0;                        // CNF10 = 01  -- Input Hi-Z
     

  
  //- - - - - - - - - - -   PORT B   - - - - - - - - - - - - - - - - - - - - - -
  
    // Подключаем к шине APB2 как к источнику тактирование Port B  (все настройки должны быть после)
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 

    // Устанавливаем Port B Pin 1 в режим GPIO Output 50MHz push-pull   (LED direct)  
  GPIOB->CRL |= GPIO_CRL_MODE1_1 | GPIO_CRL_MODE1_0;    // MODE1 = 11 
  GPIOB->CRL &= ~(GPIO_CRL_CNF1_1 + GPIO_CRL_CNF1_0);   // CNF1 = 00    
  
    // Устанавливаем Port B Pin 3 в режим GPIO Output 50MHz push-pull   (Nokia 3310 LCD ( RESET ))
  GPIOB->CRL |= GPIO_CRL_MODE3_1 | GPIO_CRL_MODE3_0;    // MODE3 = 11 
  GPIOB->CRL &= ~(GPIO_CRL_CNF3_1 + GPIO_CRL_CNF3_0);   // CNF3 = 00       
  
    // Устанавливаем Port B Pin 4 в режим GPIO Output 50MHz push-pull   (Nokia 3310 LCD ( CS ))
  GPIOB->CRL |= GPIO_CRL_MODE4_1 | GPIO_CRL_MODE4_0;    // MODE4 = 11 
  GPIOB->CRL &= ~(GPIO_CRL_CNF4_1 + GPIO_CRL_CNF4_0);   // CNF4 = 00       
  
    // Устанавливаем Port B Pin 5 в режим GPIO Output 50MHz push-pull   (Nokia 3310 LCD ( DATA_COM ))
  GPIOB->CRL |= GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0;    // MODE5 = 11 
  GPIOB->CRL &= ~(GPIO_CRL_CNF5_1 + GPIO_CRL_CNF5_0);   // CNF5 = 00
  
  
  //- - - - - - - - - - -   PORT C   - - - - - - - - - - - - - - - - - - - - - -
  
      // Подключаем к шине APB2 как к источнику тактирование Port C  ( все настройки должны быть после)      
  //RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 
  
  //- - - - - - - - - - -   PORT D   - - - - - - - - - - - - - - - - - - - - - -
  
      // Подключаем к шине APB2 как к источнику тактирование Port D  ( все настройки должны быть после)      
  //RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; 
  
  return;
}





