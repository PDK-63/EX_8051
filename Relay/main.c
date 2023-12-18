/*
	Chuong trinh Dieu khien Relay
	*Neu muon dieu khien nhieu Kenh Relay can IC cong suat mo rong Vd: ULN2003N, dieu  khien toi da 7 kenh
*/
#include <REGX51.H>
sbit Relay = P2^0;

void Delay(int t);
int main(){
	Relay = 0;
	while(1){
		Relay = 1;					// Kich trang thai Relay
		Delay(1000);
		Relay = 0;					// Tat trang thai Relay
		Delay(1000);
	}
}

void Delay(int t){
	unsigned x, y;
	for(x = 0; x < t; x++){
		for(y = 0; y < 123; y++);
	}
}