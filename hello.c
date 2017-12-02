
#include "stm32f10x_conf.h"


#include "system.h"
#include "delay.h"
#include "nokia_5110.h"
#include "NRF24L01.H"
#include "pwm.h"

//#define TX_Machine 1
u8 num = 0;
unsigned char temp = 2;
u8 Rx_Buf[]={0};
u8 Tx_Buf1[]={0x25};
//=============================
//主函数
//=============================
int main(void)
{	

	Clock_Init(9);
	delay_init(72);
	delayms(500);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);   
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE); 

	NRF_GPIO_Config(); 

	temp = NRF24L01_Check();   

	LCD_init(); //初始化液晶    
	LCD_clear();

	RX_Mode();
	TIM1_Mode_Config() ;
	while(temp == 1)
	{}
	while(1)
	{

		temp=NRF24L01_RxPacket(Rx_Buf);
		LCD_clear();
		LCD_set_XY(0,0);
		LCD_write_char(Rx_Buf[0]/100%10 + '0');
		LCD_write_char(Rx_Buf[0]/10%10 + '0');
		LCD_write_char(Rx_Buf[0]%10 + '0');		

	}
}









