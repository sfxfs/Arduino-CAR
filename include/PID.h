#ifndef __PID_H
#define __PID_H

#include <Arduino.h>

float Kp, Ki = 0, Kd;
float p, m, tp;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0; // pid直道参数
float previous_error = 0, previous_I = 0;            //误差值
static int initial_motor_speed = 100;

#endif
