#ifndef _CAR_H
#define _CAR_H

#include <Arduino.h>

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

#define INITIAL_MOTOR_SPEED 100
#define SPDD 20
#define SPEEDUP 50
#define SERIAL_RATE 9600

#define ER_A 3
#define ER_B 6
#define ER_C 11
#define ER_D 18

#define KP 5.825
#define KI 0
#define KD 23

typedef struct
{
    bool autocl;
    char cmd;
} Serial_t;

typedef struct
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
} PID_t;

#endif
