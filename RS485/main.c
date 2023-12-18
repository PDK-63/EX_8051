/*
	Chuong trinh dieu khien 8 led don, gui so 1-led 1 sang,... 8-led 8 sang, tren PORT2
	Su dung chuan gioa tiep RS232.
*/

#include <REGX51.H>               //Khai b�o thu vi?n cho 89c51
char c;
int main()                                                            //Chuong tr�nh ch�nh
{
  TMOD=0x20;                       //Ch?n Timer1, ch? d? 2
  TH1=0xFD;                           //C�i d?t t?c d? 9600 baud
  SCON=0x50;                                    //0101 0000: Ch?n ch? d? 1, Cho ph�p nh?n
  TR1=1;                                   //Kh?i d?ng Timer1
           
  while(1)                                 //V�ng l?p v� h?n
  {
    while(RI==1)                        //V�ng l?p ki?m tra c? nh?n RI
    {                                  //N?u RI=1 t?c l� d� nh?n d? 1 byte.
      c = SBUF;        //luu d? li?u nh?n du?c v�o bi?n c
      RI=0;              //X�a c? nh?n RI.
    }                     
    switch(c)                    //Ki?m tra k� t? v?a nh?n du?c: tuong ?ng
    {                                  //tru?ng h?p n�o th� th?c thi l?nh tuong?ng.
      case '1':
        P2=0xFE;
        break;
			
      case '2':
        P2=0xFC;
        break;
      case '3':
        P2=0xF8;
        break;
      case '4':
        P2=0xF0;
        break;
      case '5':
        P2=0xE0;
        break;
      case '6':
        P2=0xC0;
        break;
      case '7':
        P2=0x80;
        break;
      case '8':
        P2=0x00;
        break;
      default:                     
        P2=0xFF;
        break;
      }
   }
}