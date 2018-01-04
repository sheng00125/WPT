#include "pid.h"
//*****************************************************
//PID参数初始化
//*****************************************************
void IncPIDInit(void)
{
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion =P_DATA; //比例常数Proportional Const
sptr->Integral =I_DATA; //积分常数Integral Const
sptr->Derivative =D_DATA; //微分常数Derivative Const
sptr->SetPoint =100;
}
//*****************************************************
//增量式PID控制设计 
//*****************************************************
int IncPIDCalc(int NextPoint)
{
   int iError, iIncpid; //当前误差 
   iError = sptr->SetPoint - NextPoint; //增量计算 
   iIncpid = sptr->Proportion * iError //E[k]项 
             - sptr->Integral * sptr->LastError //E[k－1]项 
             + sptr->Derivative * sptr->PrevError; //E[k－2]项 
    sptr->PrevError = sptr->LastError;   //存储误差，用于下次计算 
    sptr->LastError = iError;
    return(iIncpid);                         //返回增量值 
}
