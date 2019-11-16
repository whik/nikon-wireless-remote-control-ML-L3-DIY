#include <Adafruit_CircuitPlayground.h>  
/*
- Github: https://github.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Gitee : https://gitee.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Blog  : www.wangchaochao.top
*/

#define IR_Pin      25
#define Led_Pin     13
#define ButtonA_Pin  4
#define ButtonB_Pin  5

#define LED_ON      digitalWrite(Led_Pin, LOW)
#define LED_OFF     digitalWrite(Led_Pin, HIGH)
#define LED_SET(x)  digitalWrite(Led_Pin, x)

#define IR_ON     digitalWrite(IR_Pin, HIGH)
#define IR_OFF    digitalWrite(IR_Pin, LOW)

#define GET_BUTTONA()  digitalRead(ButtonA_Pin)
#define GET_BUTTONB()  digitalRead(ButtonB_Pin)

int sts = 0;

void setup()   
{
  pinMode(IR_Pin, OUTPUT);
  pinMode(Led_Pin, OUTPUT);
  pinMode(ButtonA_Pin, INPUT_PULLDOWN);
  pinMode(ButtonB_Pin, INPUT_PULLDOWN);
  
  Serial.begin(9600);
}

//Nikon ML-L3 红外遥控器快门编码:38KHz=26us
void loop()
{
  if (GET_BUTTONA())
  {
    delay(10);
    if (GET_BUTTONA())
    {
      sts = !sts;
      LED_SET(sts);
      Serial.println("Right button pressed!");
      OneShot();
    }
  }
  while (GET_BUTTONA());  //等待松开
}

void OneShot()
{
  int i = 0;
  for (i = 76; i > 0; i--)  //2100ms
  {
    IR_ON;      //13.5
    delayMicroseconds(12);
    IR_OFF;     //13.7
    delayMicroseconds(12);
  }
  IR_OFF;
  delay(28);  //2803us
  for (i = 15; i > 0; i--) //393us
  {
    IR_ON;
    delayMicroseconds(12);
    IR_OFF;
    delayMicroseconds(12);
  }
  IR_OFF;
  delayMicroseconds(1580);    //1611us

  for (i = 15; i > 0; i--)
  {
    IR_ON;
    delayMicroseconds(12);
    IR_OFF;
    delayMicroseconds(12);
  }
  delayMicroseconds(3580);   
  for (i = 15; i > 0; i--)
  {
    IR_ON;
    delayMicroseconds(12);
    IR_OFF;
    delayMicroseconds(12);
  }
  IR_OFF;
}
