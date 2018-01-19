
#include "stm32f10x_conf.h"


#include "system.h"
#include "delay.h"
#include "nokia_5110.h"
#include "NRF24L01.H"
#include "pwm.h"
#include "Adc_Timer.h"
#include "pid.h"
//#define TX_Machine 1
u8 num = 0;
unsigned char temp = 2;
u8 Rx_Buf[10]={0};
u8 Tx_Buf1[]={0x25};
//=============================
//主函数
//=============================
vu16 adc_ch1,adc_ch2,adc_ch3;
double adcval_ch1,adcval_ch2,adcval_ch3;
int main(void)
{	

	Clock_Init(9);
	delay_init(72);
	delayms(500);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);   
	//RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE); 

	NRF_GPIO_Config(); 

	//while(temp != 0)
	{
			temp = NRF24L01_Check();  
	}
	RX_Mode();
	TIM1_Mode_Config() ;
	Adc_Init();
	LCD_init(); //初始化液晶    
	LCD_clear();
	IncPIDInit();
	Timerx_Init(0,0);
	
	while(1)
	{

		NRF24L01_RxPacket(Rx_Buf);
	
	}
}



void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
			
	//	TIM1->CCR1+= IncPIDCalc(adc_ch1);
		LCD_set_XY(0,0);
		LCD_write_chinese_string(8,0,12,6,0,0);
			TIM1->CCR1=FREQQQ_ARR*0.4;
			if(TIM1->CCR1>FREQQQ_ARR_MAX)
				TIM1->CCR1=FREQQQ_ARR_MAX;
				
			if(TIM1->CCR1<FREQQQ_ARR_MIN)
				TIM1->CCR1=FREQQQ_ARR_MIN;
			
		adc_ch3=Get_Adc(0);
		adc_ch3=adc_ch3*6.4453;
		LCD_write_english_string(0,2,"pri");
		LCD_set_XY(18,2);
		LCD_write_char(adc_ch3/1000%10 + '0');
		LCD_write_char(adc_ch3/100%10 + '0');
		LCD_write_char(adc_ch3/10%10 + '0');
		LCD_write_char(adc_ch3%10 + '0');	
		LCD_write_char('A');

			
		LCD_write_english_string(0,3,"sec");
		LCD_set_XY(18,3);
		adc_ch1=Rx_Buf[0]+(Rx_Buf[1]<<8);
		adc_ch1=adc_ch1*6.4453;
		LCD_write_char(adc_ch1/1000%10 + '0');
		LCD_write_char(adc_ch1/100%10 + '0');
		LCD_write_char(adc_ch1/10%10 + '0');
		LCD_write_char(adc_ch1%10 + '0');	
		LCD_write_char('V');	
		LCD_write_char('-');
		adc_ch2=Rx_Buf[2]+(Rx_Buf[3]<<8);
		LCD_write_char(adc_ch2/1000%10 + '0');
		LCD_write_char(adc_ch2/100%10 + '0');
		LCD_write_char(adc_ch2/10%10 + '0');
		LCD_write_char(adc_ch2%10 + '0');	
		LCD_write_char('A');
			
			
			
		}
}






