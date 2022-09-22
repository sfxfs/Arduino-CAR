#include "Car.h"
#include "Motor.h"
#include "PID.h"
#include "Serial.h"
#include "Tracker.h"

TaskHandle_t *TaskSerial_Handler;
TaskHandle_t *TaskTracker_Handler;
Serial_t *Serial_car;
PID_t *PID_car;
float L, R;

void setup()
{
  Serial_Setup(Serial_car);                                                           //初始化串口和结构体
  PID_Init(PID_car);                                                                  //初始化结构体
  Motor_Setup();                                                                      //初始化电机对应引脚
  Tracker_Setup();                                                                    //初始化传感器相关引脚
  xTaskCreate(Serial_Ctrl, "Serial", 1024, (void *)Serial_car, 1, TaskSerial_Handler); //创建读取串口的线程
  xTaskCreate(Tracker_Get, "Tracker", 1024, (void *)PID_car, 2, TaskTracker_Handler);  //创建读取传感器的线程
}

void loop()
{
  if (Serial_car->autocl == true)
  {
    PID_Cal(PID_car);                                                         //根据原始传感器数据计算对应PID值
    L = PID_car->p * (INITIAL_MOTOR_SPEED + PID_car->PID_value + PID_car->m); //根据PID值计算左轮速度
    R = PID_car->p * (INITIAL_MOTOR_SPEED - PID_car->PID_value + PID_car->m);
    Motor(L, R); //驱动电机执行相应速度
  }
  else
  {
    switch (Serial_car->cmd)
    {
    case byte('u'):
      Motor(INITIAL_MOTOR_SPEED, INITIAL_MOTOR_SPEED + SPDD);
      break;

    case byte('d'):
      Motor(-INITIAL_MOTOR_SPEED, -INITIAL_MOTOR_SPEED - SPDD);
      break;

    case byte('r'):
      Motor(INITIAL_MOTOR_SPEED, INITIAL_MOTOR_SPEED + SPEEDUP);
      break;

    case byte('l'):
      Motor(INITIAL_MOTOR_SPEED + SPEEDUP, INITIAL_MOTOR_SPEED);
      break;

    case byte('s'):
      Motor(0, 0);
      break;
    }
  }
}
