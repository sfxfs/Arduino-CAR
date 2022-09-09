#include "Tracker.h"

static const char A[5] = {TRA5, TRA4, TRA3, TRA2, TRA1};

void Tracker_Setup(void)
{
    for (size_t i = 0; i < 5; i++)
    {
        pinMode(A[i], INPUT);
    }
}

void Tracker_Get(void *pvParameters)
{
    while (1)
    {
        PID_t *PID;
        PID = (PID_t *)pvParameters;
        unsigned char temp = 0b00000; //临时变量用于新一轮采集
        for (int i = 0; i < 5; i++)
            temp |= digitalRead(A[i]) << i; //轮询5个传感器输出，并将查询结果转换为编码形式
        switch (temp)                       // 0为黑
        {
        case 0b11011:
            PID->error = 0;
            break;
        case 0b10001:
            PID->error = 0;
            break;
        case 0b01111:
            PID->error = -ER_D;
            break;
        case 0b00111:
            PID->error = -ER_C;
            break;
        case 0b00011:
            PID->error = -ER_C;
            break;
        case 0b10111:
            PID->error = -ER_B;
            break;
        case 0b10011:
            PID->error = -ER_A, PID->m = 10;
            break;
        case 0b11001:
            PID->error = ER_A, PID->m = 10;
            break;
        case 0b11101:
            PID->error = ER_B;
            break;
        case 0b11000:
            PID->error = ER_C;
            break;
        case 0b11100:
            PID->error = ER_C;
            break;
        case 0b11110:
            PID->error = ER_D;
            break;
        case 0b00000:
            PID->p = 0;
            break;
        }
    }
}