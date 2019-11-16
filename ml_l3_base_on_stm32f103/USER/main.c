#include "main.h"
/*
- Github: https://github.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Gitee : https://gitee.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Blog  : www.wangchaochao.top
*/
int main(void)
{
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
    IR_Init();			     //LED�˿ڳ�ʼ��
    KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
   
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

//����Nikon ML-L3����ң��������Э�飬��������ָ��
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
