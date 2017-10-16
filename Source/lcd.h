#include "types.h"
#ifndef LCD_HEADER_
#define LCD_HEADER_

//==============================================================================
/*  ����� �������������� LCD �������� lcd_init() ���������� ��������� 
    ��������� � SPI ���������. ������������ �������� SPI LCD 4 ��������/c.
    ������� hard_init() - ��������� �� ���������������� ��������� MSP430F22xx
*/
void LcdInit (void);         // ������������� LCD (+spi_init, hard_init)
void LcdSendCom (uint8);     // �������� �������� �� LCD
void LcdSendData (uint8);    // �������� ��������� �����������(8 ���) �� LCD
void LcdClearScreen(void);   // ������� ������ � ���������� �������
void LcdClearMemory(void);   // ������ �����������
void LcdSetTemperatureCoef(uint8); // ��������� �������������� ������������
void LcdSetBias(uint8);      // ��������� bias system
void LcdSetMode(uint8);      // ��������� ������ ������ ������
void LcdDrawChar(char);      // ��������� �� ������ ������ ������� � ������� ������� � ����������� ������, �.�. ��� ��������� � ������
void LcdPrintChar(char);     // ����� ������ ������� �� ����� � �������������� �������
void LcdPrintString (char*, uint8);  //����� ������ ������ �� ����� � �������������� �������
void LcdShiftText(void);     // �������� �������� �� ������ ����� ��� ����������d
void LcdSetCursorX(uint8);  // ��������� � ���������� ������� ������ 
void LcdSetCursorY(uint8);  // ��������� Y ���������� ������� ������ ��� ����� �����

//==============================================================================
#define LCD_nRES BIT0 // port 2
#define LCD_nSCE BIT1 // port 2
#define LCD_Dc BIT2   // port 2

/*  ������� � ����������� ���� */
/*   ��� ����� ������ ������   */
#define LCD_FUNCTION_SET 0x20
#define LCD_H 0x01  // 1:����������� ����� ������ / 0:����������� �����
#define LCD_V 0x02  // 1:�������������� ��������� / 0:������������
#define LCD_PD 0x04 // 1:������ ����� / 0:����� ���

/* ����������� ����� ������ H = 0 */
#define LCD_SET_X_RAM 0x80 // ���������� � ������� 0 <= Y < 6
#define LCD_SET_Y_RAM 0x40 // ���f������ � ������� 0 <= X < 84
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_E 0x01 // ������ �����������
#define LCD_D 0x04 // ������ �����������

/* ����������� ����� ������ H = 1 */
#define LCD_TEMPERATURE_CONTROL 0x04
#define LCD_TC0 0x01 // ������������� ����������� ���0
#define LCD_TC1 0x02 // ������������� ����������� ���1
#define LCD_BIAS_SYSTEM 0x10
#define LCD_BS0 0x01 // ���������� �������� ���0
#define LCD_BS1 0x02 // ���������� �������� ���0
#define LCD_BS2 0x04 // ���������� �������� ���0
//------------------------------------------------------------------------------
#define LCD_TEMP_COEF_0 0x00
#define LCD_TEMP_COEF_1 0x01
#define LCD_TEMP_COEF_2 0x02
#define LCD_TEMP_COEF_3 0x03.

#define LCD_MODE_0 0x00 // ������ �����
#define LCD_MODE_1 0x04 // ������� ����� �����������
#define LCD_MODE_2 0x01 // ������� ������
#define LCD_MODE_3 0x05 // ����������� �����

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