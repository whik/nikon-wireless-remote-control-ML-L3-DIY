#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

//#define KEY_IN PEin(2)

#define KEY_IN  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����0

void KEY_Init(void);//IO��ʼ��

#endif
