#include "Car.h"
#include "Motor.h"
#include "PID.h"
#include "Serial.h"
#include "Tracker.h"

Serial_t Serial_car;
PID_t PID_car;
float L, R;

void setup()
{
  Serial_Setup(Serial_car); //初始化串口和结构体
  PID_Init(PID_car);        //初始化结构体
  Motor_Setup();            //初始化电机对应引脚
  Tracker_Setup();          //初始化传感器相关引脚
}

void loop()
{
  Serial_Ctrl(Serial_car);
  if (Serial_car.autocl == 1)
  {
    Tracker_Get(PID_car);
    PID_Cal(PID_car);
    L = PID_car.p * (INITIAL_MOTOR_SPEED + PID_car.PID_value + PID_car.m);
    R = PID_car.p * (INITIAL_MOTOR_SPEED - PID_car.PID_value + PID_car.m);
    Motor(L, R);
  }
  else
  {
    switch (Serial_car.cmd)
    {
    case 'u':
      Motor(INITIAL_MOTOR_SPEED, INITIAL_MOTOR_SPEED + SPDD);
      break;

    case 'd':
      Motor(-INITIAL_MOTOR_SPEED, -INITIAL_MOTOR_SPEED - SPDD);
      break;

    case 'r':
      Motor(INITIAL_MOTOR_SPEED, INITIAL_MOTOR_SPEED + SPEEDUP);
      break;

    case 'l':
      Motor(INITIAL_MOTOR_SPEED + SPEEDUP, INITIAL_MOTOR_SPEED);
      break;

    case 's':
      Motor(0, 0);
      break;

    default:
      Serial.print("输入的命令有误！");
      break;
    }
  }
}
