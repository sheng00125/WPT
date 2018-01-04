#ifndef  _pid_h_
#define  _pid_h_
#include <stm32f10x.h>


typedef struct PID
{
    int SetPoint; //�趨Ŀ��Desired Value
    double Proportion; //��������Proportional Const
    double Integral; //���ֳ���Integral Const
    double Derivative; //΢�ֳ���Derivative Const
    int LastError; //Error[-1]
    int PrevError; //Error[-2]
} PID;

//*****************************************************
//������غ�
//*****************************************************
#define P_DATA 0.06
#define I_DATA 0
#define D_DATA 1
#define HAVE_NEW_VELOCITY 0X01
//*****************************************************
//����PIDʵ��
//*****************************************************
static PID sPID;
static PID *sptr = &sPID;
int IncPIDCalc(int NextPoint);
void IncPIDInit(void);

#endif
