/*
	Chuong trinh doc gia tri ADC, hien thi len LED 7 thanh
	Do Chip 8051 khong co ADC, nen ta dung chip ben ngoai, VD: ADC0804, ADC0805,...
	Voi bai toan nay ta su dung chip ADC0804 la bo ADC 8 bit(0 -5V)
	D0 - D7: la chan du lieu(D0: chan du lieu thap nhat
													 D7: chan du lieu cao nhat
													 CS:(chip select) chon chip lam viec
													 RD(read): doc gia tri analog
													 WR(write): o muc cao bat dau chuyen doi du lieu 
													 INTR(interupt): keo len muc cao yeu cau ngat
													 CLK 
													 
	LM35: cam bien nhiet do
	10mV / 1*C
	ADC0804 (8bit). do phan giai 
	D = 2^n * Vin/Vref          n: do phan giai bo adc(8 bit)
	  = 2^8 * Vin/5
		= 51.2 * Vin					    Vin: gia tri doc duoc tu cam bien
	
*/
#include "REGX51.H"

// Dinh nghia chan ADC
#define CS P3_0					// chon che do chip lam viec(neu dung 2 Bo ADC tro len thi CS = 1, nguoc lai CS =0)
#define RD P3_1						// Doc gia tri Analog
#define WR P3_2						// Chan ghi du lieu(o muc cao bat dau chuyen doi du lieu )
#define INTR P3_3					// keo len muc cao yeu cau ngat

// Dinh nghia chan LED 7 thanh
// Dinh nghia chan Led 7 thanh
#define a P2_0					// Khai bao chan a
#define b P2_1					// Khai bao chan b
#define c P2_2					// Khai bao chan c
#define d P2_3					// Khai bao chan d
#define e P2_4					// Khai bao chan e
#define f P2_5					// Khai bao chan f
#define g P2_6					// Khai bao chan g
#define dp P2_7

#define Hangnghin P0_0				// Dinh nghia hang nghin	
#define Hangtram  P0_1				// Dinh nghia hang tram
#define Hangchuc  P0_2				// Dinh nghia hang chuc
#define	Hangdonvi P0_3 				// Dinh nghia hang don vi

char ma_led[] ={0xC0,0xF9,0xA4,0xB0,
					0x99,0x92,0x82,0xF8,0x80,0x90};
void Delay(int time);
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

// Ham doc gia tri ADC
int Doc_ADC(void){
	int kq;
	CS = 0;					// vi chi su dung 1 bo ADC
	// Tao xung bat dau chuyen doi
	WR = 0;					// Yeu cau chuyen doi gia tri
	WR = 1;
	// CHuyen doi cho den luc chuyen doi xong
	while(INTR);	
	RD = 0;
	kq = P1;					// DOc  gia tri PORT2
	RD = 1;
	return kq;
}

int main(){
	int adc;																	// Khai bao bien adc
	char nhietdo;															// Khai bao bien nhiet do
	while(1){
		adc = Doc_ADC();
		nhietdo = (adc*100) / 51.2f;
		Hangnghin = 1;													// Muon hien thi LED nao, thi cho LED day sang
		hien_thi(ma_led[nhietdo /1000]);
		Delay(10);
		Hangnghin = 0;
		
		// Su dung phuong phap quet LED hien thi len LED 7 thanh
		// Hien thi hang tram
		Hangtram = 1;
		hien_thi(ma_led[(nhietdo % 1000) / 100]);
		Delay(10);
		Hangtram = 0;
		
		// Hien thi hang chuc
		Hangchuc = 1;
		hien_thi(ma_led[(nhietdo % 1000 % 100) / 10]);
		Delay(10);
		Hangchuc = 0;
		
		// Hien thi hang don vi
		Hangdonvi = 1;
		hien_thi(ma_led[nhietdo % 1000 % 100 % 10]);
		Delay(10);
		Hangdonvi = 0;
	}
}

void Delay(int time){
	int x, y;
	for(x = 0; x < time; x++){
		for(y = 0; y < 123; y++);
	}
}
