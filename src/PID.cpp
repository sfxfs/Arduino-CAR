#include "PID.h"

void PID_Init(PID_t &PID)
{
    PID.Kp = KP;
    PID.Ki = KI;
    PID.Kd = KD;

    PID.error = 0;
    PID.P = 0;
    PID.I = 0;
    PID.D = 0;
    PID.PID_value = 0;

    PID.previous_error = 0;
    PID.previous_I = 0;

    PID.p = 1;
    PID.m = 0;
}

void PID_Cal(PID_t &PID)
{
    PID.P = PID.error;
    PID.I = PID.I + PID.error;
    PID.D = PID.error - PID.previous_error;
    PID.PID_value = (PID.Kp * PID.P) + (PID.Ki * PID.I) + (PID.Kd * PID.D);
    PID.previous_error = PID.error;
}
