
#ifndef _LCD16X02_H
#define _LCD16X02_H

// Dinh nghia chan LCD
#include <REGX51.H>
#include <string.h>
// Dinh nghia chan  hien thi LCD
#define D0 P2_0				// chan D0
#define D1 P2_1				// chan D1
#define D2 P2_2
#define D3 P2_3
#define D4 P2_4
#define D5 P2_5
#define D6 P2_6
#define D7 P2_7				// chan D7

#define RS P3_0			// chan RS
#define RW P3_1			// Chan RW
#define EN		 P3_2			// Chan E

// Khai vao cac ham cho LCD
void Lcd_Cauhinh(void);		// Khoi tao LCD
void Lcd_Dulieu(unsigned char dulieu);
void Lcd_Ghi_Lenh(char lenh);		// Ghi lenh
void LCD_Ghi_Chuoi(char *str);	// Ham ghi chuoi
void Lcd_Ghi_Dulieu(char dulieu);	// Ham Ghi du lieu

#endif
