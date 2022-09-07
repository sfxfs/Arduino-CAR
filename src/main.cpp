#include "Car.h"
#include "Motor.h"
#include "PID.h"
#include "Serial.h"
#include "Tracker.h"

TaskHandle_t TaskSerial_Handler;
TaskHandle_t TaskTracker_Handler;
Serial_t *Serial_car;
PID_t *PID_car;
float L, R;

void setup()
{
  Serial_Setup(Serial_car); //初始化串口和结构体
  PID_Init(PID_car);        //初始化结构体
  Motor_Setup();            //初始化电机对应引脚
  Tracker_Setup();          //初始化传感器相关引脚
  xTaskCreate(Serial_Ctrl, "Serial", 128, (void *)Serial_car, 1, &TaskSerial_Handler);
  xTaskCreate(Tracker_Get, "Tracker", 128, (void *)PID_car, 2, &TaskTracker_Handler);
}

void loop()
{
  if (Serial_car->autocl == 1)
  {
    PID_Cal(PID_car);
    L = PID_car->p * (INITIAL_MOTOR_SPEED + PID_car->PID_value + PID_car->m);
    R = PID_car->p * (INITIAL_MOTOR_SPEED - PID_car->PID_value + PID_car->m);
    Motor(L, R);
  }
  else
  {
    switch (Serial_car->cmd)
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
      break;
    }
  }
}
