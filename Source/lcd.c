#include "types.h"
#include "font.h"
#include "lcd.h"
#include "includes.h"

#define NUM_OF_BANKS 6 // количество строчек текста и кол-во банков видеопам€ти

#ifdef FONT_7x8
  #define MAX_TEXT_LINE_LENGTH 12
#else
  #define MAX_TEXT_LINE_LENGTH 14
#endif 

#define LCD_RESET_0 (GPIOB->BRR = GPIO_BRR_BR3)   // ”станавливаем на линии LCD RESET    логический "0"
#define LCD_RESET_1 (GPIOB->BSRR = GPIO_BSRR_BS3) // ”станавливаем на линии LCD RESET    логическую "1"
#define LCD_CS      (GPIOB->BRR = GPIO_BRR_BR4)   // ”станавливаем на линии LCD CS       логический "0"
#define LCD_nCS     (GPIOB->BSRR = GPIO_BSRR_BS4) // ”станавливаем на линии LCD CS       логическую "1"
#define LCD_COM     (GPIOB->BRR = GPIO_BRR_BR5)   // ”станавливаем на линии LCD DATA_COM логический "0" (режим COMMAND)
#define LCD_DATA    (GPIOB->BSRR = GPIO_BSRR_BS5) // ”станавливаем на линии LCD DATA_COM логическую "1" (режим DATA)

Int8U Flag2;


static Int8U lcd_text_buffer[NUM_OF_BANKS][MAX_TEXT_LINE_LENGTH];
static Int8U lcd_current_text_position_x = 0, lcd_current_text_position_y = 0;
//==============================================================================
void LcdInit (void)
{ 
  LCD_nCS;
  LCD_RESET_1;     
  for (volatile unsigned int i=0; i<7200000; i++);        
//  delay_ms(100);
  LCD_CS;
  LCD_RESET_0;       
  for (volatile unsigned int i=0; i<720000; i++);      
//  delay_ms(10);  
  LCD_RESET_1;
   
  LcdSendCom(LCD_FUNCTION_SET);                   // обычный набор инструкций
  LcdSendCom(LCD_DISPLAY_CONTROL + LCD_MODE_1);   // нормальный режим отображени€ D=1 E=0 (0x0C)
  LcdClearMemory();    
};
//------------------------------------------------------------------------------
void LcdClearMemory(void)
{ 
  for(Int16U i = 0; i < 504; i++)
  {
    LcdSendData(0x55);
  }
  return;
}
//------------------------------------------------------------------------------
void LcdClearScreen(void)
{
    for(Int8U x = 0; x < MAX_TEXT_LINE_LENGTH; x++)
    {
        for(Int8U y = 0; y<NUM_OF_BANKS; y++)
        {
            lcd_text_buffer[y][x] = 0x00;
        }
    }
    LcdClearMemory();
    lcd_current_text_position_x = 0;
    lcd_current_text_position_y = 0;    
}
//------------------------------------------------------------------------------
void LcdSendCom(Int8U byte)
{
//  LCD_CS;
  LCD_COM;
  SPI1->DR = byte;  
  while(!(SPI1->SR & SPI_SR_TXE)); 
//  LCD_nCS;
  return;
}
//------------------------------------------------------------------------------
void LcdSendData(Int8U byte)
{
//  LCD_CS;
  LCD_DATA;
  SPI1->DR = byte;
  while(!(SPI1->SR & SPI_SR_TXE));
//  LCD_nCS;
  return;    
}
//------------------------------------------------------------------------------
void LcdSetTemperatureCoef(Int8U temp_coef)
{
  LcdSendCom(LCD_FUNCTION_SET + LCD_H);
  LcdSendCom(LCD_TEMPERATURE_CONTROL + temp_coef);
  LcdSendCom(LCD_FUNCTION_SET);
  return;    
}
//------------------------------------------------------------------------------
void LcdSetBias(Int8U b_system)
{
  LcdSendCom(LCD_FUNCTION_SET + LCD_H);
  LcdSendCom(LCD_BIAS_SYSTEM + b_system);
  LcdSendCom(LCD_FUNCTION_SET);
}
//------------------------------------------------------------------------------
void LcdSetMode(Int8U mode)
{
  LcdSendCom(LCD_FUNCTION_SET + mode);
}
//------------------------------------------------------------------------------
void LcdDrawChar(char _char)
{
  LcdSendData(font_6x8[6*_char]);
  LcdSendData(font_6x8[6*_char+1]);
  LcdSendData(font_6x8[6*_char+2]);
  LcdSendData(font_6x8[6*_char+3]);
  LcdSendData(font_6x8[6*_char+4]);
  LcdSendData(font_6x8[6*_char+5]);
#ifdef FONT_7x8
  LcdSendData(0x00);
#endif
  return;  
}
//------------------------------------------------------------------------------
void LcdPrintChar(char char_to_print)
{
    if (lcd_current_text_position_x < (MAX_TEXT_LINE_LENGTH-1))
    {        
        lcd_text_buffer[lcd_current_text_position_y][lcd_current_text_position_x] = char_to_print;
        LcdDrawChar(char_to_print);
        lcd_current_text_position_x++;
    } else
    {
        if(lcd_current_text_position_y < (NUM_OF_BANKS-1))
        {
            lcd_text_buffer[lcd_current_text_position_y][lcd_current_text_position_x] = char_to_print;
            LcdDrawChar(char_to_print);
            lcd_current_text_position_x = 0;
            lcd_current_text_position_y++;
        }else
        {
            lcd_text_buffer[lcd_current_text_position_y][lcd_current_text_position_x] = char_to_print;
            LcdDrawChar(char_to_print);
            LcdShiftText();
            lcd_current_text_position_x = 0;
            lcd_current_text_position_y = (NUM_OF_BANKS-1);
        }
    }
  return;    
}
//------------------------------------------------------------------------------
void LcdShiftText(void)
{
    for(Int8U y = 1; y < NUM_OF_BANKS; y++)
    {
        for(Int8U x = 0; x < MAX_TEXT_LINE_LENGTH; x++)
        {
            lcd_text_buffer[y-1][x] = lcd_text_buffer[y][x];
        }
    }
    for(Int8U x = 0; x < MAX_TEXT_LINE_LENGTH; x++)
    {
        lcd_text_buffer[NUM_OF_BANKS-1][x] = 0x00;
    }
    LcdSetCursorX(0);
    LcdSetCursorY(0);
    //-----------------------
    for(Int8U y = 0; y < NUM_OF_BANKS; y++)
    {
        for(Int8U x = 0; x < MAX_TEXT_LINE_LENGTH; x++)
        {
            LcdDrawChar(lcd_text_buffer[y][x]);
        }
    }
    LcdSetCursorX(0);
    LcdSetCursorY(NUM_OF_BANKS - 1);
}
//------------------------------------------------------------------------------
void LcdSetCursorX(Int8U cursor_x)
{
    LcdSendCom(LCD_SET_X_RAM + cursor_x);
}
//------------------------------------------------------------------------------
void LcdSetCursorY(Int8U cursor_y)
{
    LcdSendCom(LCD_SET_Y_RAM + cursor_y);
}
//------------------------------------------------------------------------------
void LcdPrintString (char* string, Int8U size_of_string)
{
    for(Int8U i = 0; i < size_of_string; i++)
    {
        LcdPrintChar(string[i]);
    }
}
//==============================================================================