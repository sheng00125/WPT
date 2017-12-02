
#include "stm32f10x_conf.h"


#include "system.h"
#include "delay.h"
#include "nokia_5110.h"
#include "NRF24L01.H"
#include "pwm.h"
#include "Adc_Timer.h"

//#define TX_Machine 1
u8 num = 0;
unsigned char temp = 2;
u8 Rx_Buf[]={0};
u8 Tx_Buf1[]={0x25};
//=============================
//������
//=============================
int main(void)
{	

	Clock_Init(9);
	delay_init(72);
	delayms(500);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);   
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE); 

	NRF_GPIO_Config(); 

	while(temp == 1)
	{
			temp = NRF24L01_Check();  
	}
	RX_Mode();
	TIM1_Mode_Config() ;
	Adc_Init();
	LCD_init(); //��ʼ��Һ��    
	LCD_clear();
	Timerx_Init(0,0);

	while(1)
	{

		NRF24L01_RxPacket(Rx_Buf);

	}
}



void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		LCD_set_XY(0,0);
		LCD_write_char(Rx_Buf[0]/100%10 + '0');
		LCD_write_char(Rx_Buf[0]/10%10 + '0');
		LCD_write_char(Rx_Buf[0]%10 + '0');	
		LCD_set_XY(0,1);
		LCD_write_char(temp/100%10 + '0');
		LCD_write_char(temp/10%10 + '0');
		LCD_write_char(temp%10 + '0');	
		temp=Get_Adc(0);
		}
}






