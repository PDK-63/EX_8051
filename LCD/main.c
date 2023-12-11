/*
	Chuong trinh dieu khien hien thi tren LED 7 thanh
	Va hien thi so nguyen, so thuc

*/
#include <main.h>
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

void Lcd_Cauhinh(void);		// Khoi tao LCD
void Lcd_Ghi_Lenh(char lenh);		// Ghi lenh
void Lcd_Ghi_Dulieu(char dulieu);	// Ham Ghi du lieu
void Delay(int t);

// ham xuat du lieu
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

void Lcd_Cauhinh(void){
	Lcd_Ghi_Lenh(0x03);
	Lcd_Ghi_Lenh(0x38);					// Giao tiep voi XL 8 chan(D0 - D7)
	// Lcd_Ghi_Lenh(0x28);			// Giao tiep voi VXL 4 chan(D4 - D7)
	Lcd_Ghi_Lenh(0x06);					// Tu dong dua con tro den tri tri tiep theo (trai -> phai)
	Lcd_Ghi_Lenh(0x0c);					// Bat hien thi con tro
	Lcd_Ghi_Lenh(0x01);					// Xoa man hinh
}

void Lcd_Ghi_Lenh(char lenh){
	RS = 0;											// muc thap, chon che do ghi lenh
	RW = 0;											// muc thap, chon che do thanh ghi	
	EN = 1;											// muc cao, chuan bi tao su chuyen muc logic tu "1" -> "0" tao tin hieu cho phep ghi
	Lcd_Dulieu(lenh);
	Delay(10);
	EN = 0;											// muc thap, hoan tat su tao chuyen muc logic "1" sang "0"
	Delay(10);
}


void Lcd_Ghi_Dulieu(char dulieu){
	RS = 1;								
	RW = 0;
	EN = 1;
	Lcd_Dulieu(dulieu);
	Delay(10);
	EN = 0;
	Delay(10);
}

void LCD_Ghi_Chuoi(char *str){
	while(*str){
		Lcd_Ghi_Dulieu(*str);
		str++;
	}
}
int main(){
	Lcd_Cauhinh();
	while(1){
		Lcd_Ghi_Lenh(0X80);					//dau dong 1 
		LCD_Ghi_Chuoi("Xin chao"); 
		Lcd_Ghi_Lenh(0XC0);					//dau dong 2 
		LCD_Ghi_Chuoi("Lewlew"); 
	}
	return 0;
}

void Delay(int t){
	int x, y;
	for(x = 0; x < t; x++){
		for(y = 0; y < 123; y++);
	}
}