/*
	Chuong trinh tao xung PWM
	PWM: la thay doi do rong xung nhung giu nguyen tan so
	O bai toan nay, ta su dung f = 50Hz
*/
#include "REGX51.H"

// Dinh nghia cac chan
#define PWM_PIN P2_1			// Cau hinh chan PWM chan P2_1

// Khai bao bien 
int i, T, Ton, Toff;
int Ton_h_reload, Ton_l_reload, Toff_h_reload, Toff_l_reload;

// Ham khoi tao che do PWM
void PWM_Init(int ck)
{
	PWM_PIN = 1;				// keo chan PWM len muc cao(muc 1)
	TMOD &= 0XF0;				// Thanh ghi TMOD (che do dem/ngat bo dinh thoi) bang cach xoa 4 bit thap(and 0xF)
	TMOD |= 0X01;				// Thiet lap che do 1 cua bo dinh thoi, hay che do 16-bit voi thanh ghi TH0 va TL0
	
	ET0 = 1;						// CHo phep ngat toan cuc
	EA = 1;							// CHo phep ngat bo dinh thoi timer0.
	
	T = ck-24;					// Tinh gia tri chu ky dem
	Ton = ck / 2;				
	Toff = T - Ton;			// Tinh gia tri chu ky xung
	
	Ton_h_reload = (65536 - Ton) >> 8;					// Tinh thoi gian nap lai thanh ghi dem cho thoi gian Ton
	Ton_l_reload = (65536 - Ton) & 0X00FF;
	
	Toff_h_reload = (65536 - Toff) >> 8;				// Tinh thoi gian nap lai thanh ghi cho thoi gian Toff 
	Toff_l_reload = (65536 - Toff) & 0X00FF;
	
	// Nap lai gia tri thanh ghi dem voi gia tri thoi gian on
	TH0 = Ton_h_reload;
	TL0 = Ton_l_reload;
}

// bat dau qua trinh tao xung
void PWM_Start()
{
	TR0 = 1;
}

// dung qua trinh tao xung
void PWM_Stop()
{
	TR0 = 0;
}

// Ham thiet lap do dutycycle(do rong xung)
void PWM_Set_Duty(int duty)
{
	// Voi truopng hop khong co xung PWM
	if(duty==0)
	{
		/* 
			Keo chan PWM xuong muc thap
			Tat bo dinh thoi (ET0 = 0), chan ngat sinh ra
		*/
		PWM_PIN = 0;
		ET0 = 0;
	}
		// ThL xung luon o muc cao(= 1)
	else if(duty==100)
	{
		/*
			Keo chan PWM len muc cao, baty xung PWM
		*/
		PWM_PIN = 1;
		ET0 = 0;
	}
	// Th con lai 
	else
	{
		/*
			Tinh toan gia tri Ton va Toff dua vao chu ky dem T va dutycycle
		*/
		Ton = ((unsigned long)T) * duty / 100;
		Toff = T - Ton;
		
		/*
			Tinh toawn lai gia tri nap vao thanh ghi
		*/
		Ton_h_reload = (65536 - Ton) >> 8;
		Ton_l_reload = (65536 - Ton) & 0X00FF;
		
		Toff_h_reload = (65536 - Toff) >> 8;
		Toff_l_reload = (65536 - Toff) & 0X00FF;
	}
}

// ham ngat, duoc kich hoat khi co su kien tran
void Timer0overflow() interrupt 1
{
	PWM_PIN = !PWM_PIN;				// dao lai trang thuc PWM (1 -> 0) (0 -> 1)
	/* 
		Neu chan PWM dang o muc thap( xung PWM tat)
		Gan lai gia tri thanh ghi nap ddem lai chu ky tiep theo
	*/
	if(PWM_PIN==0)
	{
		TH0 = Toff_h_reload;
		TL0 = Toff_l_reload;
	}
	else
	{
		TH0 = Ton_h_reload;
		TL0 = Ton_l_reload;
	}
}

int main(){
	// CT tinh ((1/f) * 1.000.000)		Doi sang us
	while(1){
		PWM_Init(100);					// khoi tao che do PWM voi tan so 50Hz
		PWM_Set_Duty(80);					// Ton = Toff = 50%
		PWM_Start();							// bat dau tao xung
	}
}
