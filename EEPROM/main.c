/*
	Viet chuong trinh giao tiep voi EEPROM
	Su dung 25LC256.
	+, Giao tiep theo chuan SPI, hoat dong 2 che do: mode(0, 0) va mode(1, 1)
	+, Dien ap: 2.5 - 5.5V
	+, tan so xung Clock 5V - 10MHz
	+, Ghi du lieu theo byte hoac theo trang(64 byte)
	+, Dung luong bo nho: 256Kbits = 32Kbytes
	+, Thoi gian luu tru du lieu > 200 nam
	+, Kha nang ghi xoa 1000000 ghi/xoa
	
	Chuc nang chan
	CS:  Chip slect
	SCK; cLOCK
	MISO: Serial Data Out
	MOSI: Serial Data In
	WP  : Write Protect
	HOLD: Hold Input
	VSS, GND: Power Supply
*/

#include "REGX51.H"

// Dinh nghia cac chan IC '
#define SPI_CLK P2_0
#define SPI_MOSI P2_1
#define SPI_MISO P2_2
#define SPI_CS   P2_3

int main(){
	
	while(1){
	
	}
	return 0;
}