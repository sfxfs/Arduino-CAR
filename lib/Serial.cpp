#include "Serial.h"
#include "Motor.h"

extern char autocl;
extern const int INITIAL_MOTOR_SPEED;
extern const int SPDD;

void Serial_Setup()
{
    Serial.begin(9600);
    Serial.print("UART BOOTING....");
}

void Serial_Ctrl()
{
    String data = "";
    data += char(Serial.read());
    delay(2);
    if (data.length() == 1)
    {
        data.trim();
        if (data.endsWith("N")) //开启自动驾驶
        {
            autocl = 1;
        }

        if (data.endsWith("F")) //关闭自动驾驶
        {
            autocl = 0;
            Motor_Dir(0, 0, 0, 0);
        }

        if (data.endsWith("U")) //前进
        {
            Motor((double)(INITIAL_MOTOR_SPEED), (double)(INITIAL_MOTOR_SPEED + SPDD));
        }

        if (data.endsWith("D")) //后退
        {
            Motor((double)(-INITIAL_MOTOR_SPEED), (double)(-INITIAL_MOTOR_SPEED - SPDD));
        }

        if (data.endsWith("R")) //左转
        {
            Motor((double)(INITIAL_MOTOR_SPEED), (double)(-INITIAL_MOTOR_SPEED));
        }

        if (data.endsWith("L")) //右转
        {
            Motor((double)(-INITIAL_MOTOR_SPEED), (double)(INITIAL_MOTOR_SPEED));
        }

        if (data.endsWith("S")) //停止
        {
            Motor_Dir(0, 0, 0, 0);
        }
        data = "";
    }
}
