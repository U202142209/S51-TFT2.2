#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h>
#include <font\font.h>

// #include"ldc1000.h"

/*
程序默认IO连接方式：
sbit LCD_CS     =P0^0;     //片选
sbit LCD_DC     =P0^2;	  //数据/命令切换
sbit LCD_SDI    =P1^3;	  //数据
sbit LCD_SCK    =P1^5;	  //时钟
sbit LCD_REST   =P0^1;	  //复位
sd0 P1^4
*/
void xianshi()//显示信息
{
    BACK_COLOR = WHITE;
    POINT_COLOR = BLACK;
    showhanzi(10, 10, 0); //晶
    showhanzi(45, 10, 1); //耀

    LCD_ShowString(10, 50, "2.2 inch TFT 240*320");
    LCD_ShowString(10, 80, "Zhao Wei Jia");

    LCD_ShowNum(10, 110, 12345, 1);
    LCD_ShowString(10, 150, "Zhao Wei Jia");
    LCD_ShowString(10, 180, "Zhao Wei Jia");
}


void mytest()
{
    LCD_Clear(WHITE); //清屏
    BACK_COLOR = BLACK;;
    POINT_COLOR = WHITE;
    while(1)
    {
        xianshi(); //显示信息
        delayms(2000);
    }
}


int i, j, m;
u8* p;
void iKunMain()
{
    LCD_Clear(WHITE); //清屏
    BACK_COLOR = BLACK;;
    POINT_COLOR = WHITE;
    while(1)
    {
        BACK_COLOR = WHITE;
        POINT_COLOR = BLACK;

        for(i = 0; i < 28; i++)
        {
            p = "* * * * * * * * * * * * * *";
            LCD_ShowString(10, 20 + 10 * i, p);
        }

        LCD_ShowString(10, 60, "* * * **********");
        LCD_ShowString(10, 70, " * * * * * * * *");

        delayms(2000);
    }
}


void showimage() //显示40*40图片
{
    int i, j, k;
    int size = 160;
    int smallsize = 40;
    int x = 40;
    int y = 40;
    for(k = 0; k < 1; k++)
    {
        for(j = 0; j < 1; j++)
        {
            Address_set(x, y, x + size - 1, x + size - 1);		//坐标设置
            for(i = 0; i < 51208 / 2; i++)
            {
                // LCD_WR_DATA8(image[i * 2 + 1]);	 //发送颜色数据
                // LCD_WR_DATA8(image[i * 2]);
                LCD_WR_DATA8(imageikun[i * 2 + 1]);	  //发送颜色数据
                LCD_WR_DATA8(imageikun[i * 2]);
            }

            Address_set(0, 0, 0 + smallsize - 1, 0 + smallsize - 1);		//坐标设置
            for(i = 0; i < 1600; i++)
            {
                LCD_WR_DATA8(image[i * 2 + 1]);	 //发送颜色数据
                LCD_WR_DATA8(image[i * 2]);
                // LCD_WR_DATA8(gImage_1[i * 2 + 1]);	 //发送颜色数据
                // LCD_WR_DATA8(gImage_1[i * 2]);							
            }
        }
    }
}

int main()
{
    Lcd_Init();   //tft初始化
    // iKunMain();
    LCD_Clear(WHITE); //清屏
    while(1)
    {
        showimage();
    }
    return 0;
}


