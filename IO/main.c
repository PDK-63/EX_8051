/*
	Chuong trinh nhap nhay LED
	Cau hinh chan P2_0
*/
#include "REGX51.H"
// Ham tao tre
void Delay_ms(int t){
	int x, y;
	for(x = 0; x < t; x++){
		for(y = 0; y < 123; y++);		
	}
}

// Ham chinh chuong trinh
int main(){
	
	while(1){
		P2_0 = 0;					// Tat Led chân P2_0
		Delay_ms(500);
		P2_0 = 1;					// Bat led chân P2_0
		Delay_ms(500);
	}
	return 0;
}