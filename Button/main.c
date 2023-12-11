/*
	Chuong trinh dieu khien LED bang nut nhan
	Nut nhan chan: P1_0
	Led:           P2_0
*/
#include <REGX51.H>

// Khi bao chan
#define BT P1_0				// Khai bao chan Nut nhan
#define Led P2_0			// Khai bao chan LED

// Ham tao tre
void Delay(int time){
	int x, y;
	for(x = 0; x < time; x++){
		for(y = 0; y < 123; y++);
	}
}

int main(){
	while(1){
		// Kiem tra trang thai nut nhan
		if(BT == 0){										// Neu nut nhan(BT) nhan thi ==> LED(P2_0) sang
			Delay();											// Thoi gian cho nhan nut
			Led = 1;
		}
		else{														// Nguoc lai thi LED tat
			Delay();
			Led = 0;
		}
	}
	return 0;
}