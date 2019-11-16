#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

//#define KEY_IN PEin(2)

#define KEY_IN  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键0

void KEY_Init(void);//IO初始化

#endif
