#include"ldc1000.h"
int LDC_val=0;
unsigned char orgVal[12]={0};
//unsigned char RPMAX =0x07; 
//unsigned char RPMIN =0x2f;
//unsigned char RFREQ =0xA9;

unsigned char RPMAX =0x0C; //
unsigned char RPMIN =0x33; //
unsigned char RFREQ =0xB8;//
unsigned char rpi_max=3;
unsigned char proximtyData[2]={0};
unsigned long proximtyDataTEMP=0,proximtyDataMAX,proximtyDataMIN,proximtyDataSUM,proximtyDataAVE,proximtyDataAVE_LAS;
void delayms(unsigned int ms)
{
	unsigned char i=100,j;
	for(;ms;ms--)
	{
		while(--i)
		{
			j=10;
			while(--j);
		}
	}
}
void delay10us(unsigned int i)
{
	while(i--);	
}
void FLOAT_LDC_init()
{
      while(orgVal[1]!=RPMAX||orgVal[2]!=RPMIN||orgVal[3]!=RFREQ)//
      {  
         FLOAT_SPI_init();   
         delayms(30);
         FLOAT_Singal_SPI_Write(LDC1000_CMD_RPMAX, RPMAX);//
         FLOAT_Singal_SPI_Write(LDC1000_CMD_RPMIN, RPMIN);//
         FLOAT_Singal_SPI_Write(LDC1000_CMD_SENSORFREQ,  RFREQ);  //Sensor Frequency  N = 68.94 * log10(F/2000);F=935 kHz	,N=184
         FLOAT_Singal_SPI_Write(LDC1000_CMD_LDCCONFIG,   0x17);  //	设定振荡幅度4V,响应时间3072
         FLOAT_Singal_SPI_Write(LDC1000_CMD_CLKCONFIG,   0x00);  //使用外部时基时钟，并启用
         FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESHILSB,  0x50); // 
	       FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESHIMSB,  0x14);//
	       FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESLOLSB,  0xC0);//
	       FLOAT_Singal_SPI_Write(LDC1000_CMD_THRESLOMSB,  0x12);//
         FLOAT_Singal_SPI_Write(LDC1000_CMD_INTCONFIG,   0x02);	 //INTB引脚表示比较器输出的状态
         FLOAT_Singal_SPI_Write(LDC1000_CMD_PWRCONFIG,   0x01);// 活动模式。启用转换
         FLOAT_SPI_Read_Buf(LDC1000_CMD_REVID,&orgVal[0],12);//orgVal[]
       
      }
} 

int ldc_read()//LDC1000 数据读取
{
      FLOAT_SPI_Read_Buf(0x20,&proximtyData[0],1);
//  	   FLOAT_SPI_Read_Buf(LDC1000_CMD_REVID,&proximtyData[0],1);
      proximtyDataTEMP = proximtyData [0]; 
  	  
    return   proximtyDataTEMP; 

}
int ldc_read_avr()//均值滤波
{

    char rpi=0;  //
    for (rpi=0;rpi<rpi_max;rpi++)
    {

      FLOAT_SPI_Read_Buf(LDC1000_CMD_PROXLSB,&proximtyData[0],2);  
      proximtyDataTEMP = ((unsigned char)proximtyData[1]<<8) + proximtyData [0]; 
      proximtyDataSUM += proximtyDataTEMP;
      if (proximtyDataTEMP < proximtyDataMIN)   //?100?proximtyDataTEMP????,??
        proximtyDataMIN = proximtyDataTEMP;
      if (proximtyDataTEMP > proximtyDataMAX)
        proximtyDataMAX = proximtyDataTEMP;
    }
     proximtyDataAVE = proximtyDataSUM /rpi_max;
     proximtyDataSUM=0;
     proximtyDataAVE_LAS=proximtyDataAVE;
  
    return   proximtyDataAVE; 

}
long int filter()//窗口滤波
{
   char count,i,j,count1;
   char count2=0;
 
   long int temp;
   long int sum=0;
   for(count=0;count<NN;count++)
   {
      value_buf[count] = ldc_read_avr();
   }
   
   for(count1=0;count1<NN;count1++)
   {  
   if(value_buf[count1]<32768)
   {
   new_value_buf[count2]=value_buf[count1];
   count2++;
   }  
   }
   
   
   for (j=0;j<count2-1;j++)
   {
      for (i=0;i<count2-j;i++)
      {
        if ( new_value_buf[i]>new_value_buf[i+1] )
         {
            temp = new_value_buf[i];
            new_value_buf[i] = new_value_buf[i+1];
            new_value_buf[i+1] = temp;
         }
      }
   }

   for(count=1;count<count2-1;count++)
   {
      sum += new_value_buf[count];
   }
  
     
   return (long int)(sum/(count2-2));


}

void FLOAT_SPI_init()
{  


         MISO=1;
         CSN=1;
         SCK=0;
         MOSI=1;
         
  
}

unsigned char FLOAT_SPI_RW(unsigned char rwdata)
{  
    
	unsigned char spi_rw_i=0;	
        unsigned char temp=0;
        for(spi_rw_i=0;spi_rw_i<8;spi_rw_i++)   	// output 8-bit
   	{
   	        /*** prepare the write data of read before the coming of rising up******/
	          if(rwdata & 0x80)
                    MOSI=1;
   		  else 
                    MOSI=0;
   		  rwdata<<=1;           		// shift next bit to MSB
                  temp<<=1;
		SCK=1;             //Set SCK high    Rising up 
               
   		if(MISO) 
                  temp|=1;
   		SCK=0;            //set  SCK low     Falling down
                
   	}
    return(temp);           		  		// return read byte
    
 
}

unsigned char FLOAT_Singal_SPI_Read(unsigned char reg)
{
	unsigned char rdata;
	
	CSN=0;                        // CSN low, initialize SPI communication...
       
        delay10us(1);
         
         reg=reg|0x80;         //read com
	FLOAT_SPI_RW(reg);            // Select register to read from..
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
       
	rdata = FLOAT_SPI_RW(0);    // then read registervalue
  delay10us(170);
	CSN=1;                 // CSN high, terminate SPI communication
	
	return rdata;         // return register value
}

void FLOAT_Singal_SPI_Write(unsigned char reg,unsigned char wdata)
{
	
	CSN=0;                // CSN low, initialize SPI communication...
  delay10us(1);//2us
  reg=reg&~0x80;
	FLOAT_SPI_RW(reg);            // Select register to read from..
			 
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();
_nop_();        
	FLOAT_SPI_RW(wdata);    // ..then read registervalue
        delay10us(170);//875us
	CSN=1;              // CSN high, terminate SPI communication
       
	
}
void FLOAT_SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char len)
{
	unsigned char spi_rw_i;
	
	CSN=0;                   		// Set CSN low, init SPI tranaction
       
        reg=reg|0x80;                            //read
	FLOAT_SPI_RW(reg);       		// Select register to write to and read status unsigned char
	
	for(spi_rw_i=0;spi_rw_i<len;spi_rw_i++)
        {  
	pBuf[spi_rw_i] = FLOAT_SPI_RW(0);    
	 }
	CSN=1;     
       

}