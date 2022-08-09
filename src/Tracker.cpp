#include "Tracker.h"

static const char A[5] = {TRA5, TRA4, TRA3, TRA2, TRA1};
static const float a = 3, b = 6, c = 11, d = 18; // error

extern float p, m;
extern float error, previous_error;

void Tracker_Setup()
{
    pinMode(TRA1, INPUT);
    pinMode(TRA2, INPUT);
    pinMode(TRA3, INPUT);
    pinMode(TRA4, INPUT);
    pinMode(TRA5, INPUT);
}

void Tracker_Get()
{
    unsigned char temp = 0b00000; //临时变量用于新一轮采集
    for (int i = 0; i < 5; i++)
        temp |= digitalRead(A[i]) << i; //轮询5个传感器输出，并将查询结果转换为编码形式
    switch (temp)                       // 0为黑
    {
    case 0b11011:
        error = 0;
        break;
    case 0b10001:
        error = 0;
        break;
    case 0b01111:
        error = -d;
        break;
    case 0b00111:
        error = -c;
        break;
    case 0b00011:
        error = -c;
        break;
    case 0b10111:
        error = -b;
        break;
    case 0b10011:
        error = -a, m = 10;
        break;
    case 0b11001:
        error = a, m = 10;
        break;
    case 0b11101:
        error = b;
        break;
    case 0b11000:
        error = c;
        break;
    case 0b11100:
        error = c;
        break;
    case 0b11110:
        error = d;
        break;
    case 0b00000:
        p = 0;
        break;
    }
}
