#include "Motor.h"

void Motor_Setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
}

void Motor(double L, double R)
{
    if (abs(L) > 255)
        L = L / abs(L) * 255;
    if (abs(R) > 255)
        R = R / abs(R) * 255;
    if (abs(L) == 0)
        L = 1;
    if (abs(R) == 0)
        R = 1;
    if (L > 0 && R > 0)
        analogWrite(ENB, L),
            analogWrite(ENA, R),
            Motor_Dir(0, 1, 1, 0);
    else if (-L > 0 && -R > 0)
        analogWrite(ENB, -L),
            analogWrite(ENA, -R),
            Motor_Dir(1, 0, 0, 1);
    else if (-L > 0 && R > 0)
        analogWrite(ENB, -L),
            analogWrite(ENA, R),
            Motor_Dir(0, 1, 0, 1);
    else if (L > 0 && -R > 0)
        analogWrite(ENB, L),
            analogWrite(ENA, -R),
            Motor_Dir(1, 0, 1, 0);
    else

        Motor_Dir(0, 0, 0, 0);

    Serial.print("左轮");
    Serial.print(L);
    Serial.print("右轮");
    Serial.println(R);
}

void Motor_Dir(char out1, char out2, char out3, char out4)
{
    digitalWrite(IN1, out1);
    digitalWrite(IN2, out2);
    digitalWrite(IN3, out3);
    digitalWrite(IN4, out4);
}
