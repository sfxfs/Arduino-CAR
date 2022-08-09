#include "Car.h"

float Kp, Ki = 0, Kd;                                // pid弯道参数参数
float error = 0, P = 0, I = 0, D = 0, PID_value = 0; // pid直道参数
float previous_error = 0, previous_I = 0;            //误差值
unsigned char initial_motor_speed = 100;                //此处值为0-255的值，受电池电压影响，需要自己调试
char autocl = 0;
int spdd = 20; //两轮转速差
double L, R;
float p, m;

void setup()
{
    Serial_Setup();
    Motor_Setup();
    Tracker_Setup();
}

void loop()
{
    Serial_Ctrl();
    if(autocl == 1)
    {
        PID_Setup();
        Tracker_Get();
        PID_Get();
        Motor(p * (initial_motor_speed + PID_value + m), p * (initial_motor_speed - PID_value + m) + spdd);
    }
}
