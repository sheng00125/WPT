#ifndef  _pid_h_
#define  _pid_h_
#include <stm32f10x.h>


typedef struct PID
{
    int SetPoint; //设定目标Desired Value
    double Proportion; //比例常数Proportional Const
    double Integral; //积分常数Integral Const
    double Derivative; //微分常数Derivative Const
    int LastError; //Error[-1]
    int PrevError; //Error[-2]
} PID;

//*****************************************************
//定义相关宏
//*****************************************************
#define P_DATA 0.06
#define I_DATA 0
#define D_DATA 1
#define HAVE_NEW_VELOCITY 0X01
//*****************************************************
//声明PID实体
//*****************************************************
static PID sPID;
static PID *sptr = &sPID;
int IncPIDCalc(int NextPoint);
void IncPIDInit(void);

#endif
