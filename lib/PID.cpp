#include "PID.h"

void PID_Setup()
{
    Kp = 5.75 + 0.125;
    Kd = 23; //此处的Kp和Kd也需根据车的结构和既定轨迹调试进行调试，
    m = 0;
    tp = 0;
    p = 1;
}