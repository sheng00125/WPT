#ifndef _pwm_h_
#define _pwm_h_
#include "system.h"

void delay_init(u8 SYSCLK);
void delayus(u32 us);
void delayms(u16 ms);
void TIM1_Mode_Config(void) ;

#define FREQQQ 97951
#define FREQQQ_ARR 72000000/FREQQQ

#define FREQQQ_ARR_MAX 72000000/FREQQQ*0.4
#define FREQQQ_ARR_MIN 72000000/FREQQQ*0.1


#endif
