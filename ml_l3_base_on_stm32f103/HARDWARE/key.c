#include "key.h"
#include "delay.h"
							    
//PE2-上拉输入，按下为0
void KEY_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
    
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

