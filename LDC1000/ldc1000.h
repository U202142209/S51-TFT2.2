#ifndef __LDC1000_H_
#define __LDC1000_H_
#include	"config.h"


#define NN  3

sbit MISO=P1^3;
sbit MOSI=P1^2;
sbit CSN=P1^1;		 
sbit SCK=P1^0;

		 //FLOAT LDC COMMANDS
#define LDC1000_CMD_REVID               0x00
#define LDC1000_CMD_RPMAX 	        0x01
#define LDC1000_CMD_RPMIN 	        0x02
#define LDC1000_CMD_SENSORFREQ 	0x03               
#define LDC1000_CMD_LDCCONFIG 	0x04
#define LDC1000_CMD_CLKCONFIG 	0x05
#define LDC1000_CMD_THRESHILSB 	0x06
#define LDC1000_CMD_THRESHIMSB 	0x07
#define LDC1000_CMD_THRESLOLSB 	0x08
#define LDC1000_CMD_THRESLOMSB 	0x09
#define LDC1000_CMD_INTCONFIG 	0x0A
#define LDC1000_CMD_PWRCONFIG 	0x0B
#define LDC1000_CMD_STATUS	0x20
#define LDC1000_CMD_PROXLSB 	0x21
#define LDC1000_CMD_PROXMSB 	0x22
#define LDC1000_CMD_FREQCTRLSB	0x23
#define LDC1000_CMD_FREQCTRMID	0x24
#define LDC1000_CMD_FREQCTRMSB	0x25

//FLOAT LDC BITMASKS
#define LDC1000_BIT_AMPLITUDE    0x18
#define LDC1000_BIT_RESPTIME     0x07
#define LDC1000_BIT_CLKSEL       0x02
#define LDC1000_BIT_CLKPD        0x01
#define LDC1000_BIT_INTMODE      0x07
#define LDC1000_BIT_PWRMODE      0x01
#define LDC1000_BIT_STATUSOSC    0x80
#define LDC1000_BIT_STATUSDRDYB  0x40
#define LDC1000_BIT_STATUSWAKEUP 0x20
#define LDC1000_BIT_STATUSCOMP   0x10
		 




unsigned long value_buf[NN],new_value_buf[NN];
void FLOAT_LDC_init();
int ldc_read_avr();
int ldc_read();
long int filter();

void FLOAT_SPI_init();
unsigned char FLOAT_SPI_RW(unsigned char rwdata);
unsigned char FLOAT_Singal_SPI_Read(unsigned char reg);
void FLOAT_Singal_SPI_Write(unsigned char reg,unsigned char wdata);
void FLOAT_SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char len);

void delayms(unsigned int ms);
void delay10us(unsigned int i);





#endif