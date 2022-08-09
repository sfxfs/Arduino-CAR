#include "PID.h"

extern float Kp, Ki, Kd;
extern float p, m;
extern float error, P, I, D, PID_value; // pid直道参数
extern float previous_error, previous_I;            //误差值
extern unsigned char initial_motor_speed;

void PID_Setup()
{
    Kp = 5.75 + 0.125;
    Kd = 23; //此处的Kp和Kd也需根据车的结构和既定轨迹调试进行调试，
    m = 0;
    p = 1;
}

void PID_Get()
{
    P = error;
    I = I + error;
    D = error - previous_error;
    PID_value = (Kp * P) + (Ki * I) + (Kd * D);
    previous_error = error;
}
