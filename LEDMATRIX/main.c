/*
	Chuong trinh dieu khien LED ma tran 8x8 su dung Cathot chung
	Voi bai toan nay chung ta su dung phuong phap quet Led
		+, Muon hien thi led nao thi ta cho sang Led do, tuong ung voi hang va cot va viet theo 8 bit
		sang: 0
		tat: 1
		
		0000 -> 0							1001 -> 9
		0001 -> 1							1010 -> A
		0010 -> 2							1011 -> B
		0011 -> 3							1100 -> C
		0100 -> 4							1101 -> D
		0101 -> 5							1110 -> E
		0110 -> 6							1111 -> F
		0111 -> 7
		1000 -> 8
		
			Doi chu thanh so la Anot chung(Proteus)
*/
#include <REGX51.H>

unsigned char maled[8] = {0XFF,0X01,0X00,0XEE,0XEE,0X00,0X01,0XFF};		// Ma chu A voi LED sang muc 1(hang muc 0, cot muc 1)
unsigned char ma[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};			// ma quet COT: C1 den C8, cot nao o gia tri 1 thi COT do sang
unsigned char i = 0;

void Delay(int time);				// Ham tao tre
int main(){
	while(1){
		for(i = 0; i < 8; i++){			// Quet Cot 1 -> 8, cho COT = 1 va gui du lieu ra cot
			P3 = maled[i];						// Goi du lieu tai vi tri ma tran meled[] ra cot 1->8 (Quet tu cot 1 -> 8)
			P2 = ma[i];								// Goi ma quet = 1 tra ve ma[] ra cot 1 -> 8
			Delay(1);								// thoi gian quet 1 ms
			P2 = 0x00;								// Cho ma quet tu hang 0, cot 8 den het
		}
		
	}
	return 0;
}

void Delay(int time){
	int x, y;
	for(x = 0; x < time; x++){
		for(y = 0; y < 123; y++);
	}
}