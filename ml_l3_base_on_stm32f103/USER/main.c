#include "main.h"
/*
- Github: https://github.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Gitee : https://gitee.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Blog  : www.wangchaochao.top
*/
int main(void)
{
    delay_init();	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);	 //串口初始化为115200
    IR_Init();			     //LED端口初始化
    KEY_Init();          //初始化与按键连接的硬件接口
   
    while(1)
    {
        if(!KEY_IN)
        {
            delay_ms(10);
            if(!KEY_IN)
                OneShot();
        }
        while(!KEY_IN);
    }
}

//根据Nikon ML-L3红外遥控器编码协议，产生快门指令
void OneShot(void)
{
    int i = 0;
    for(i = 76; i > 0; i--)   //2100ms
    {
        IR_ON;      //13.5
        delay_us(12);
        IR_OFF;     //13.7
        delay_us(12);
    }
    IR_OFF;
    delay_ms(28);  //2803us
    for(i = 15; i > 0; i--)  //393us
    {
        IR_ON;
        delay_us(12);
        IR_OFF;
        delay_us(12);
    }
    IR_OFF;
    delay_us(1580);    //1611us

    for(i = 15; i > 0; i--)
    {
        IR_ON;
        delay_us(12);
        IR_OFF;
        delay_us(12);
    }
    delay_us(3580);
    for(i = 15; i > 0; i--)
    {
        IR_ON;
        delay_us(12);
        IR_OFF;
        delay_us(12);
    }
    IR_OFF;
}
