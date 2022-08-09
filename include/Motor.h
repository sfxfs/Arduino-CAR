#ifndef __MOTOR_H
#define __MOTOR_H

#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENA 5
#define ENB 10

#include <Arduino.h>

void Motor_Setup();
void Motor(double L, double R);
void Motor_Dir(char out1, char out2, char out3, char out4);

#endif
