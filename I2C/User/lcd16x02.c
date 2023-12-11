#include "lcd16x02.h"
#include "REGX51.H"

// Dinh nghia chan  hien thi LCD
sbit D0 = P2^0;				// chan D0
sbit D1 = P2^1;				// chan D1
sbit D2 = P2^2;
sbit D3 = P2^3;
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;				// chan D7

sbit RS = P3^0;			// chan RS
sbit RW = P3^1;			// Chan RW
sbit EN	=	 P3^2;			// Chan E

void Delay(int time){
	int x, y;
	for(x = 0; x < time; x++){
		for(y = 0; y , 123; y++);
	}
}

void Lcd_Dulieu(unsigned char dulieu){
	D0 = dulieu & 0x01;
	D1 = (dulieu >> 1) & 0x01;
	D2 = (dulieu >> 2) & 0x01;
	D3 = (dulieu >> 3) & 0x01;
	D4 = (dulieu >> 4) & 0x01;
	D5 = (dulieu >> 5) & 0x01;
	D6 = (dulieu >> 6) & 0x01;
	D7 = (dulieu >> 7) & 0x01;
}

void Lcd_Ghi_Lenh(char lenh){
	RS = 0;											// muc thap, chon che do ghi lenh
	RW = 0;											// muc thap, chon che do thanh ghi	
	EN = 1;											// muc cao, chuan bi tao su chuyen muc logic tu "1" -> "0" tao tin hieu cho phep ghi
	Lcd_Dulieu(lenh);
	EN = 0;											// muc thap, hoan tat su tao chuyen muc logic "1" sang "0"
	Delay(10);
}

// Ham, ghi du lieu
void Lcd_Ghi_Dulieu(char dulieu){
	RS = 1;								
	RW = 0;
	EN = 1;
	Lcd_Dulieu(dulieu);
	EN = 0;
	Delay(10);
}

// Ham ghi chuoi
void LCD_Ghi_Chuoi(char *str){
	while(*str){
		Lcd_Ghi_Dulieu(*str);
		str++;
	}
}

void Lcd_Cauhinh(void){
	Lcd_Ghi_Lenh(0x03);
	Lcd_Ghi_Lenh(0x38);					// Giao tiep voi XL 8 chan(D0 - D7)
	// Lcd_Ghi_Lenh(0x28);			// Giao tiep voi VXL 4 chan(D4 - D7)
	Lcd_Ghi_Lenh(0x06);					// Tu dong dua con tro den tri tri tiep theo (trai -> phai)
	Lcd_Ghi_Lenh(0x0c);					// Bat hien thi con tro
	Lcd_Ghi_Lenh(0x01);					// Xoa man hinh
}

