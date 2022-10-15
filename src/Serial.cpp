#include "Serial.h"

void Serial_Setup(volatile Serial_t *Stemp)
{
    Stemp->autocl = 0;
    Stemp->cmd = 0;
    Serial.begin(SERIAL_RATE);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Serial.print("UART STARTED!");
}

void Serial_Ctrl(void *pvParameters)
{
    while (1)
    {
        Serial_t *Stemp;
        Stemp = (Serial_t *)pvParameters;
        byte data = 0;
        data = byte(Serial.read());
        switch (data)
        {
        case byte('n'): //开启自动驾驶

            Stemp->autocl = true;
            break;

        case byte('f'): //关闭自动驾驶

            Stemp->autocl = false;
            Stemp->cmd = byte('f');
            break;

        case byte('u'): //前进

            Stemp->cmd = byte('u');
            break;

        case byte('d'): //后退

            Stemp->cmd = byte('d');
            break;

        case byte('r'): //右转

            Stemp->cmd = byte('d');
            break;

        case byte('l'): //左转

            Stemp->cmd = byte('l');
            break;

        case byte('s'): //停止

            Stemp->cmd = byte('s');
            break;

        default:
            Serial.print("输入的命令有误！");
            break;
        }
        data = 0x00;
    }
}
