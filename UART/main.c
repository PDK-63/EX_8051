/*
	Viet chuong tirnh truyen ky tu qua khung truyen, toc do Baud: 9600
	Chan ket noi:			RX - TX
										TX - RX
										GND - GND 
	Nhap ki tu thuong chuyen sang kieu In hoa, ung dung phan mem hercules
*/

#include <REGX51.H>
#include <string.h>
#include <stdio.h>

char KT;
void Uart_Init()
{
	// Khoi tao UART o mode 1, 9600 baud
	SM0 = 0; SM1 = 1;		// Chon UART mode 1
	TMOD = 0x20;            // 0010 xxxx - Timer1 hoat dong o che do 8bit tu dong nap lai
	TH1 = 0xFD;				// Toc do baud 9600
	TR1 = 1;				// Timer1 bat dau chay
	TI = 1;					// San sang gui du lieu
	REN = 1;				// Cho phep nhan du lieu
}

// ham gui ky tu qua UART
void Uart_Write_Char(char c)
{
 	while(TI == 0);
	TI = 0;
	SBUF = c;
}

// ham gui 1 chuoi ky tu
void Uart_Write_String(char * str)
{
	unsigned char i = 0;
 	while(str[i]!=0)
	{
		Uart_Write_Char(str[i]);
		i++;
	}
}
// ham kiem tra du lieu co nhan duoc hay khong
char Uart_Data_Ready()
{
	return RI;
}

// ham doc 1 ky tu TU UART
char Uart_Read()
{
	RI = 0;
	return SBUF;
}

// HAM dELAY
void Delay(long time){
	time = time * 25;
	while(time--);
}

int main(){
	Uart_Init();
	while(1){
		Uart_Write_String("Nhap ki tu thuong: ");
		while(Uart_Data_Ready()==0);
		KT = Uart_Read();
		KT -=  32;																// chuyen ki tu thuong sang kieu in hoa(ma ASCII)
		Uart_Write_String("=>");
		Uart_Write_Char(KT);
		Uart_Write_String("\r\n");
	}
}

