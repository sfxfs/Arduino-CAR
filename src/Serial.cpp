#include "Serial.h"

extern char autocl;
extern unsigned char initial_motor_speed;
extern int spdd;

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
            Motor((double)(initial_motor_speed), (double)(initial_motor_speed + spdd));
        }

        if (data.endsWith("D")) //后退
        {
            Motor((double)(-initial_motor_speed), (double)(-initial_motor_speed - spdd));
        }

        if (data.endsWith("R")) //左转
        {
            Motor((double)(initial_motor_speed), (double)(-initial_motor_speed));
        }

        if (data.endsWith("L")) //右转
        {
            Motor((double)(-initial_motor_speed), (double)(initial_motor_speed));
        }

        if (data.endsWith("S")) //停止
        {
            Motor_Dir(0, 0, 0, 0);
        }
        data = "";
    }
}
