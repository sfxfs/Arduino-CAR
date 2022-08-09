#include <Arduino.h>

float Kp, Ki = 0, Kd;                                // pid弯道参数参数
float error = 0, P = 0, I = 0, D = 0, PID_value = 0; // pid直道参数
float previous_error = 0, previous_I = 0;            //误差值
static int initial_motor_speed = 100;                //此处值为0-255的值，受电池电压影响，需要自己调试
int A[5] = {19, 18, 17, 16, 15};
int autocl = 0;
static int spdd = 20; //两轮转速差
double L, R;
float a, b, c, d, p, m, tp;
int ena = 5;
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int enb = 10;
void trac_run();
void pid();
void trac();
void motor();
void motordir(int out1, int out2, int out3, int out4);
void serial_ctl();

void setup()
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop()
{
  serial_ctl();
  if (autocl == 1)
  {
    Kp = 5.75 + 0.125;
    Kd = 23; //此处的Kp和Kd也需根据车的结构和既定轨迹调试进行调试，
    m = 0;
    tp = 0;
    a = 3, b = 6, c = 11, d = 18, p = 1;
    trac_run();
  }
}
void trac()
{
  unsigned char temp = 0b00000; //临时变量用于新一轮采集
  for (int i = 0; i < 5; i++)
    temp |= digitalRead(A[i]) << i; //轮询5个传感器输出，并将查询结果转换为编码形式
  switch (temp)                     // 0为黑
  {
  case 0b01111:
    error = -d;
    break;
  case 0b00111:
    error = -c;
    break;
  case 0b00011:
    error = -c;
    break;
  case 0b10111:
    error = -b;
    break;
  case 0b10011:
    error = -a, m = 10;
    break;
  case 0b11001:
    error = a, m = 10;
    break;
  case 0b11101:
    error = b;
    break;
  case 0b11000:
    error = c;
    break;
  case 0b11100:
    error = c;
    break;
  case 0b11110:
    error = d;
    break;
  case 0b11111:
    tp = previous_error;
    if (tp < 0)
      error = -d;
    else
      error = d;
    break;
  case 0b00000:
    p = 0;
    break;
  default:
    error = 0;
    break;
  }
}

void pid()
{
  P = error;
  I = I + error;
  D = error - previous_error;
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
  previous_error = error;
}

void trac_run()
{
  trac();
  pid();
  L = p * (initial_motor_speed + PID_value + m);
  R = p * (initial_motor_speed - PID_value + m) + spdd;
  if (abs(L) > 255)
    L = L / abs(L) * 255;
  if (abs(R) > 255)
    R = R / abs(R) * 255;
  if (abs(L) == 0)
    L = 1;
  if (abs(R) == 0)
    R = 1;
  motor();
}

void motor()
{
  if (L > 0 && R > 0)
    analogWrite(enb, L),
        analogWrite(ena, R),
        motordir(0, 1, 1, 0);
  else if (-L > 0 && -R > 0)
    analogWrite(enb, -L),
        analogWrite(ena, -R),
        motordir(1, 0, 0, 1);
  else if (-L > 0 && R > 0)
    analogWrite(enb, -L),
        analogWrite(ena, R),
        motordir(0, 1, 0, 1);
  else if (L > 0 && -R > 0)
    analogWrite(enb, L),
        analogWrite(ena, -R),
        motordir(1, 0, 1, 0);
  else

    motordir(0, 0, 0, 0);

  Serial.print("左轮");
  Serial.print(L);
  Serial.print("右轮");
  Serial.println(R);
}

void motordir(int out1, int out2, int out3, int out4) //输入1 0，控制方向
{
  digitalWrite(in1, out1);
  digitalWrite(in2, out2);
  digitalWrite(in3, out3);
  digitalWrite(in4, out4);
}

void serial_ctl()
{
  String data = "";
  data += char(Serial.read());
  delay(2);
  if (data.length() == 1)
  {
    data.trim();
    if (data.endsWith("N")) //开启自动驾驶
    {
      autocl = 1;
    }

    if (data.endsWith("F")) //关闭自动驾驶
    {
      autocl = 0;
      motordir(0, 0, 0, 0);
    }

    if (data.endsWith("U")) //前进
    {
      analogWrite(ena, initial_motor_speed + spdd);
      analogWrite(enb, initial_motor_speed);
      motordir(0, 1, 1, 0);
    }

    if (data.endsWith("D")) //后退
    {
      analogWrite(ena, initial_motor_speed + spdd);
      analogWrite(enb, initial_motor_speed);
      motordir(1, 0, 0, 1);
    }

    if (data.endsWith("R")) //左转
    {
      analogWrite(enb, initial_motor_speed);
      analogWrite(ena, initial_motor_speed);
      motordir(0, 1, 0, 1);
    }

    if (data.endsWith("L")) //右转
    {
      analogWrite(enb, initial_motor_speed);
      analogWrite(ena, initial_motor_speed);
      motordir(1, 0, 1, 0);
    }

    if (data.endsWith("S")) //停止
    {
      motordir(0, 0, 0, 0);
    }
    data = "";
  }
}
