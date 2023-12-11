/*
	Viet chuong trinh dieu khien LED 7 Thanh(don), hien thi so lan nhan nut
*/
#include <REGX51.H>

// Khai bao chan vao ra
#define a P2_0					// Khai bao chan a
#define b P2_1					// Khai bao chan b
#define c P2_2					// Khai bao chan c
#define d P2_3					// Khai bao chan d
#define e P2_4					// Khai bao chan e
#define f P2_5					// Khai bao chan f
#define g P2_6					// Khai bao chan g
#define dp P2_7

#define nutnhan P1_0
// Khai bao ma Led 7 Thanh
char ma_led[] ={0xC0,0xF9,0xA4,0xB0,
													0x99,0x92,0x82,0xF8,0x80,0x90};
int dem;							// Khoi tao bien dem ban dau = 0

void Delay(int time);								
void hienthi(unsigned char dulieu){
	a = dulieu & 0x01;							// a
	b = (dulieu >> 1) & 0x01;				// b
	c = (dulieu >> 2) & 0x01;				// c
	d = (dulieu >> 3) & 0x01;				// d
	e = (dulieu >> 4) & 0x01;				// e
	f = (dulieu >> 5) & 0x01;				// f
	g = (dulieu >> 6) & 0x01;				// g
	dp = (dulieu >> 7) & 0x01;			// dp
}

int main(){
	
	while(1){
		// Ham kiem tra nut nhan
		if(nutnhan == 0){
			while(nutnhan == 0);					// Neu moi lan nhan nut
			dem++;												// Bien dem tang len 1 don vi
		}
		if(dem > 9){										// Neu dem > 9 thi dem = 0(dem lai tu dau)
			dem = 0;
		}
		hienthi(ma_led[dem]);
		Delay(10);
	}
	return 0;
}

// Ham tao tre
void Delay(int time){
	int x, y;
	for(x = 0; x < time; x++){
		for(y = 0; y < 123; y++);				// tao tre 1ms
	}
}
