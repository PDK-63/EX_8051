/*
	Chuong trinh hien thi so lan nhat LED 7  Thanh,
	Su dung phuong phap quet LED
*/
#include <REGX51.h>

// Dinh nghia chan Led 7 thanh
#define a P2_0					// Khai bao chan a
#define b P2_1					// Khai bao chan b
#define c P2_2					// Khai bao chan c
#define d P2_3					// Khai bao chan d
#define e P2_4					// Khai bao chan e
#define f P2_5					// Khai bao chan f
#define g P2_6					// Khai bao chan g
#define dp P2_7

#define Hangdonvi P3_0		// Dinh nghia hang don vi
#define Hangchuc P3_1		// Dinh nghia hang chuc

#define Nutnhan P1_0
// Khai bao ma led
char ma_led[] ={0xC0,0xF9,0xA4,0xB0,
							0x99,0x92,0x82,0xF8,0x80,0x90};
int dem;

void hien_thi(unsigned char dulieu){
	a = dulieu & 0x01;						// a
	b = (dulieu >> 1) & 0x01;			// b
	c = (dulieu >> 2) & 0x01;			// c
	d = (dulieu >> 3) & 0x01;			// d
	e = (dulieu >> 4) & 0x01;			// e
	f = (dulieu >> 5) & 0x01;			// f
	g = (dulieu >> 6) & 0x01;			// g
	dp = (dulieu >> 7) & 0x01;			// dp
}

void Delay(int time);

int main(){
	while(1){
		// Kiem tra trang thai nut nhan
		if(Nutnhan == 0){
			while(Nutnhan == 0);
			dem++;
		}
		if(dem > 99){
			dem = 0;
		}
		
		// Hien thi hang don vi
		Hangdonvi = 1;											// Bat Led hang don vi hien thi bien dem hang don vi
		hien_thi(ma_led[dem % 10]);					// Chia lay phan du cua gia tri dem
		Delay(2);
		Hangchuc = 0;
		
		// Hien thi hang chuc
		Hangchuc = 1;
		hien_thi(ma_led[dem / 10]);
		Delay(2);
		Hangdonvi = 0;
	}
	return 0;
}

void Delay(int time){
	int x, y;
	for(x = 0; x < time; x++){
		for(y = 0; y < 123; y++);
	}
}