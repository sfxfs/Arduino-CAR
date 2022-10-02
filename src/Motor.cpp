#include "Motor.h"

void Motor_Setup(void)
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
}

void Motor_Dir(bool out1, bool out2, bool out3, bool out4)
{
    digitalWrite(IN1, out1);
    digitalWrite(IN2, out2);
    digitalWrite(IN3, out3);
    digitalWrite(IN4, out4);
}

void Motor(float L, float R)
{
    L = constrain(L, -255, 255);
    R = constrain(R, -255, 255);
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

    Serial.print("左轮:");
    Serial.print(L);
    Serial.print("右轮:");
    Serial.println(R);
}
