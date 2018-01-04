#include "pid.h"
//*****************************************************
//PID������ʼ��
//*****************************************************
void IncPIDInit(void)
{
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion =P_DATA; //��������Proportional Const
sptr->Integral =I_DATA; //���ֳ���Integral Const
sptr->Derivative =D_DATA; //΢�ֳ���Derivative Const
sptr->SetPoint =100;
}
//*****************************************************
//����ʽPID������� 
//*****************************************************
int IncPIDCalc(int NextPoint)
{
   int iError, iIncpid; //��ǰ��� 
   iError = sptr->SetPoint - NextPoint; //�������� 
   iIncpid = sptr->Proportion * iError //E[k]�� 
             - sptr->Integral * sptr->LastError //E[k��1]�� 
             + sptr->Derivative * sptr->PrevError; //E[k��2]�� 
    sptr->PrevError = sptr->LastError;   //�洢�������´μ��� 
    sptr->LastError = iError;
    return(iIncpid);                         //��������ֵ 
}
