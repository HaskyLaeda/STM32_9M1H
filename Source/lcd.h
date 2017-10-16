#include "types.h"
#ifndef LCD_HEADER_
#define LCD_HEADER_

//==============================================================================
/*  перед инициализацией LCD функцией lcd_init() необходимо настроить 
    процессор и SPI интерфейс. Максимальная скорость SPI LCD 4 мегабита/c.
    функция hard_init() - расчитана на микроконтроллеры семейства MSP430F22xx
*/
void LcdInit (void);         // инициализация LCD (+spi_init, hard_init)
void LcdSendCom (uint8);     // отправка комманды на LCD
void LcdSendData (uint8);    // отправка фрагмента изображения(8 бит) на LCD
void LcdClearScreen(void);   // очистка экрана и текстового буффера
void LcdClearMemory(void);   // очиста видеопамяти
void LcdSetTemperatureCoef(uint8); // установка температурного коэффициента
void LcdSetBias(uint8);      // установка bias system
void LcdSetMode(uint8);      // установка режима работы экрана
void LcdDrawChar(char);      // рисование на экране одного символа в текущей позиции в графическом режиме, т.е. без занесения в буффер
void LcdPrintChar(char);     // вывод одного символа на экран с использованием буффера
void LcdPrintString (char*, uint8);  //вывод строки текста на экран с использованием буффера
void LcdShiftText(void);     // смещение экрарана на строку вверх при заполненииd
void LcdSetCursorX(uint8);  // установка Х координаты курсора экрана 
void LcdSetCursorY(uint8);  // установка Y координаты курсора экрана или выбор банка

//==============================================================================
#define LCD_nRES BIT0 // port 2
#define LCD_nSCE BIT1 // port 2
#define LCD_Dc BIT2   // port 2

/*  команды и управляющие биты */
/*   при любом режиме команд   */
#define LCD_FUNCTION_SET 0x20
#define LCD_H 0x01  // 1:расширенный набор команд / 0:стандартный набор
#define LCD_V 0x02  // 1:горизонтальная адресация / 0:вертикальная
#define LCD_PD 0x04 // 1:спящий режим / 0:режим вкл

/* стандартный набор команд H = 0 */
#define LCD_SET_X_RAM 0x80 // установить Х позицию 0 <= Y < 6
#define LCD_SET_Y_RAM 0x40 // устfновить У позицию 0 <= X < 84
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_E 0x01 // режимы отображения
#define LCD_D 0x04 // режимы отображения

/* расширенный набор команд H = 1 */
#define LCD_TEMPERATURE_CONTROL 0x04
#define LCD_TC0 0x01 // температурный коэффициент бит0
#define LCD_TC1 0x02 // температурный коэффициент бит1
#define LCD_BIAS_SYSTEM 0x10
#define LCD_BS0 0x01 // напряжение смещения бит0
#define LCD_BS1 0x02 // напряжение смещения бит0
#define LCD_BS2 0x04 // напряжение смещения бит0
//------------------------------------------------------------------------------
#define LCD_TEMP_COEF_0 0x00
#define LCD_TEMP_COEF_1 0x01
#define LCD_TEMP_COEF_2 0x02
#define LCD_TEMP_COEF_3 0x03.

#define LCD_MODE_0 0x00 // пустой экран
#define LCD_MODE_1 0x04 // обычный режим отображения
#define LCD_MODE_2 0x01 // заливка экрана
#define LCD_MODE_3 0x05 // инверсивный режим

#define LCD_BIAS_0 0x07 // 1:100
#define LCD_BIAS_1 0x06 // 1:80
#define LCD_BIAS_2 0x05 // 1:65
#define LCD_BIAS_3 0x04 // 1:48
#define LCD_BIAS_4 0x03 // 1:40
#define LCD_BIAS_5 0x02 // 1:24
#define LCD_BIAS_6 0x01 // 1:18
#define LCD_BIAS_7 0x00 // 1:10
//==============================================================================
#endif // LCD_HEADER_