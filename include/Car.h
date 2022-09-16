#ifndef _CAR_H
#define _CAR_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define SERIAL_RATE 9600

//传感器和电机驱动模块引脚定义
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENA 5
#define ENB 10

#define TRA1 15
#define TRA2 16
#define TRA3 17
#define TRA4 18
#define TRA5 19

const float INITIAL_MOTOR_SPEED = 100;
const float SPDD = 20;
const float SPEEDUP = 50;

const float ER_A = 3;
const float ER_B = 6;
const float ER_C = 11;
const float ER_D = 18;

const float KP = 5.825;
const float KI = 0;
const float KD = 23;

struct Serial_t
{
    bool autocl;
    char cmd;
};

struct PID_t
{
    float Kp;
    float Ki;
    float Kd;

    float error;
    float P;
    float I;
    float D;
    float PID_value;

    float previous_error;
    float previous_I;

    float p;
    float m;
};

#endif
