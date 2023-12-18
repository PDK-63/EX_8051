/*
	Bai toan hien thi thoi gian thuc DS1307 len man hinh LCD
	LCD su dung 16x02, 4bit(D4 - D7)
	Su dung DS1307, giao tiep qua chuan I2C, 2 chan SCL va SDA phai co tro keo len duong nguon( thuong 4.7K)
	
*/
#include "REGX51.H"
#include "string.h"
#include "stdio.h"

// Dinh nghia cac chan LCD
sbit D0 = P2^0;						// Chan D0 LCD
sbit D1 = P2^1;						// Chan D1 LCD
sbit D2 = P2^2;						// Chan D2 LCD
sbit D3 = P2^3;
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;						// Chan D7 LCD

sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

// Dinh nghia chan I2C cua DS1307
sbit SCL = P1^0;
sbit SDA = P1^1;

char day[7][3] = {"CN", "T2", "T3", "T4", "T5", "T6", "T7"};
void Lcd_Cauhinh(void);		// Khoi tao LCD
void Lcd_Ghi_Lenh(char lenh);		// Ghi lenh
void Lcd_Ghi_Dulieu(char dulieu);	// Ham Ghi du lieu
void LCD_Ghi_Chuoi(char *str);
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

// Bat dau che I2C
void I2C_Start(void){
	/* \
		XUng Clock chuyen tu muc thap len muc ca0 SCL: 0 -> 1
		Dong thoi chan du lieu chuyen tu muc cao xuong thap: 1 -> 0
	*/
	SCL = 0;
	SDA = 1;
	SCL = 1;
	SDA = 0;
}

void I2C_Stop(void){
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
}
void I2C_Restart(void){
	SCL = 0;
	SDA = 1;
	SCL = 1;
	SDA = 0;
}
/* 
bit ACK/NACK: Moi khung trong 1 tin nhan theo sau boi 1 bit xaac nhan/ khong xac nhan
				Neu khung dia chi hoac du lieu nhan thanh cong, bit ACK tra lai lai bi master

*/
void I2C_ACK(){
	SCL = 0;
	SDA = 1;
	SCL = 1;
	while(SDA == 1);
}

void I2C_NOACK(){
	SCL = 0;
	SDA = 1;
	SCL = 1;
}

// Write
void I2C_Write(unsigned char dulieu){
	unsigned char i;
	for(i = 0; i < 8; i++){
		SCL = 0;							// keo chan SCL ve muc thap(xac dinh bat dau 1 bit du lieu)
		SDA = (dulieu & (0x80 >> i)) ? 1 : 0;			// Ghi gia tri tuong ung tu dulieu vao chan SDA
		SCL = 1;							// Keo chan SCL len muc cao xâc nhan bit du lieu
	}
}

// Read
unsigned char I2C_Read(void){
		unsigned char i, tmp = 0;
		for(i = 0; i < 8; i++){
			SCL = 0;					// Bat dau doc chu ky 
			SCL = 1;					// keo chan SCL len cao doc bit tiep theo
			if(SDA){					// kiem tra chan SDA neu dang o muc cao
				tmp = tmp | (0x80 >> i);			// tra ve bit tuong ung trong bien 'tmp' neu chan SDA = 1
			}
		}
		return tmp;
}

unsigned char I2C_Data_Write(unsigned char tm, unsigned char buf, unsigned dulieu){
	I2C_Start();							//   Bat daua che do I2C
	I2C_Write(tm & 0XFE);			//		Thiet bi master gui 8bit (0xfe = 11111110)
	I2C_ACK();								// Thiet bi master nhan tin hieu tu slave
	I2C_Write(buf);						//  Thiet bi Master gui 8 bit
	I2C_ACK();								// Thiet bi master nhan tin hieu tu slave
	I2C_Write(dulieu);				// du lieu tu master ghi vao dia chi
	I2C_ACK();
	I2C_Stop();
	Delay(10);
}

unsigned char I2C_Data_Read(unsigned char tm, unsigned char bufAdd){
	unsigned char buf;
	I2C_Start();	
	I2C_Write(tm & 0XFE);	
	I2C_ACK();	
	I2C_Write(bufAdd);		
	I2C_ACK();
	I2CRestart();
	I2C_Write(tm | 1);
	I2C_ACK();
	buf = I2C_Read();
	I2C_NOACK();
	I2C_Stop();
	return buf;
}

void Clock(void){
	unsigned char t;
	char day1[3] = {0};
	Lcd_Ghi_Lenh(0x81);
	t = I2C_Data_Read(0xd0, 0x02);				// Thanh ghi dia chi 02 cho Gio
	Lcd_Ghi_Dulieu((t / 16) + 48);
	Lcd_Ghi_Dulieu((t % 16) + 48);
	Lcd_Ghi_Dulieu(':');
	
	t = I2C_Data_Read(0xd0, 0x01);				// Thanh ghi dia chi 01 cho phut	
	Lcd_Ghi_Dulieu((t / 16) + 48);
	Lcd_Ghi_Dulieu((t % 16) + 48);
	Lcd_Ghi_Dulieu(':');
	
	t = I2C_Data_Read(0xd0, 0x00);				// Thanh ghi dia chi 00 cho giay
	Lcd_Ghi_Dulieu((t / 16) + 48);
	Lcd_Ghi_Dulieu((t % 16) + 48);
	Lcd_Ghi_Dulieu(':');
	
	Lcd_Ghi_Lenh(0x8C);
	t = I2C_Data_Read(0xD0, 0x03);				// Thanh ghi dia chi 00 cho giay
	sprintf(day1, "s", day[t]);
	LCD_Ghi_Chuoi(day1);
	
	Lcd_Ghi_Lenh(0xC1);
	t = I2C_Data_Read(0xd0, 0x04);				// Thanh ghi dia chi 00 cho giay
	Lcd_Ghi_Dulieu((t / 16) + 48);
	Lcd_Ghi_Dulieu((t % 16) + 48);
	Lcd_Ghi_Dulieu('/');
	
	t = I2C_Data_Read(0xd0, 0x05);				// Thanh ghi dia chi 00 cho giay
	Lcd_Ghi_Dulieu((t / 16) + 48);
	Lcd_Ghi_Dulieu((t % 16) + 48);
	Lcd_Ghi_Dulieu('/');
	
	t = I2C_Data_Read(0xD0, 0x06);				// Thanh ghi dia chi 00 cho giay
	LCD_Ghi_Chuoi("20");
	Lcd_Ghi_Dulieu((t / 16) + 48);
	Lcd_Ghi_Dulieu((t % 16) + 48);
}

int main(){
	Lcd_Cauhinh();
	Lcd_Ghi_Lenh(0x01);
	Lcd_Ghi_Lenh(0x80);
	LCD_Ghi_Chuoi("Xin chao");
	Delay(200);
	Lcd_Ghi_Lenh(0x01);
	while(1){
		Clock();
		Delay(300);
	}
	return 0;
}

void Delay(int t){
	int x, y;
	for(x = 0; x < t; x++){
		for(y = 0; y < 123; y++);
	}
}

