#include "Serial.h"

void Serial_Setup(Serial_t *Stemp)
{
    Stemp->autocl = 0;
    Stemp->cmd = 0;
    Serial.begin(SERIAL_RATE);
    delay(100);
    Serial.print("UART STARTED!");
}

void Serial_Ctrl(Serial_t *Stemp)
{
    String data = "";
    data += char(Serial.read());
    delay(2);
    if (data.length() == 1)
    {
        data.trim();
        if (data.endsWith("n")) //开启自动驾驶
        {
            Stemp->autocl = 1;
        }

        if (data.endsWith("f")) //关闭自动驾驶
        {
            Stemp->autocl = 0;
            Stemp->cmd = 's';
        }

        if (data.endsWith("u")) //前进
        {
            Stemp->cmd = 'u';
        }

        if (data.endsWith("d")) //后退
        {
            Stemp->cmd = 'd';
        }

        if (data.endsWith("r")) //左转
        {
            Stemp->cmd = 'r';
        }

        if (data.endsWith("l")) //右转
        {
            Stemp->cmd = 'l';
        }

        if (data.endsWith("s")) //停止
        {
            Stemp->cmd = 's';
        }
        data = "";
    }
}
