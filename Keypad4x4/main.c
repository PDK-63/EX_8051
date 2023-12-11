#include <REGX51.H>

// Cau hinh Cot
#define C1 P1_7
#define C2 P1_6
#define C3 P1_5
#define C4 P1_4

// Cau hinh Hang
#define H1 P1_0
#define H2 P1_1
#define H3 P1_2
#define H4 P1_3

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

// Dinh nghia Ban Phim [H] [C]
unsigned char KEYPAD4X4 [4][4] = { '1', '2', '3', 'A', // (H 1, COT 1) so 3, (H 1, COT 2) so 2,
																   '4', '5', '6', 'B',
																   '7', '8', '9',	'C',
																	 '*', '0', '#', 'D'};
unsigned char ketqua = 0;
																	 
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

void Delay(int t){
	int x, y;
	for(x = 0; x < t; x++){
		for(y = 0; y < 123; y++);
	}
}

/* 
	Kiem tra phim co duoc nhan hay khong
	1: Phim duoc nhan
	0: Phim k duoc nhan
																	 
*/
unsigned char KEY4X4_Nhan(void){
	if((H1 == 0)|(H2 == 0)|(H3 == 0)|(H4 == 0))
		return 1;
	else 
		return 0;
}
/*
	Quet tung cot tren Keypad
	C: Cot can quet
*/
void Ktr_KEY4X4(unsigned char Cot){
	C1 = 1;
	C2 = 1;
	C3 = 1;
	C4 = 1;
	
	if(Cot == 0){
		C1 = 0;
	}
	else if(Cot == 1){
		C2 = 0;
	}
	else if(Cot == 2){
		C3 = 0;
	}
	else if(Cot == 3){
		C4 = 0;
	}
}

/*
	Doc va tra ve gia tri nut nhan
*/

unsigned char KEY4X4_KQ(void){
	unsigned char i;
	// Cho Cot 1 den Cot 4
	C1 = 0;
	C2 = 0;
	C3 = 0;
	C4 = 0;
	
	// Kiem tra nhan phim
	if(KEY4X4_Nhan() == 1){
		Delay(1);
		if(KEY4X4_Nhan() == 1){					// Kiem tra chinh xac nut co duoc nhan hay  khong
			for(i = 0; i < 4; i++){
				Ktr_KEY4X4(i);
				if(H1 == 0){								// Neu hang 1 duoc nhan
					return KEYPAD4X4[0][i];		// tra ve ky tu nhan duoc o hang 1 va quet cot tu cot 1 den 4
				}
				else if(H2 == 0){								// Neu hang 1 duoc nhan
					return KEYPAD4X4[1][i];		// tra ve ky tu nhan duoc o hang 2 va quet cot tu cot 1 den 4
				}
				else if(H3 == 0){								// Neu hang 1 duoc nhan
					return KEYPAD4X4[2][i];		// tra ve ky tu nhan duoc o hang 3 va quet cot tu cot 1 den 4
				}
				else if(H4 == 0){								// Neu hang 1 duoc nhan
					return KEYPAD4X4[3][i];		// tra ve ky tu nhan duoc o hang 4 va quet cot tu cot 1 den 4
				}
			}
		}
	}
	return 0;
}

void Keypad_init(){
	// Dau tien gan cot = 0;
	C1 = 0;
	C2 = 0;
	C3 = 0;
	C4 = 0;
	
	// Dau tien gan cho hang = 0;
	H1 = 1;
	H2 = 1;
	H3 = 1;
	H4 = 1;
}

int main(){
	Lcd_Cauhinh();							 //Thiet lap cau hinh cho LCD 
	Keypad_init();							 //goi ham khai bao ma tran phim 4x4
	Lcd_Ghi_Lenh(0X81);					//hien thi cot thu 2, LCD 16x02
	LCD_Ghi_Chuoi("KEYPAD 4X4");
	while(1){
		ketqua = KEY4X4_KQ();
		if(key != 0){
			Lcd_Ghi_Lenh(0XC0);
			Lcd_Ghi_Dulieu(key);
		}
	}
}

