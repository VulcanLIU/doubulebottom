
#include <avr/io.h>
#include <avr/interrupt.h>
#define  F_CPU 16000000UL  //定义系统时钟
#include <util/delay.h>
void TC0_init(void);
void TC1_init(void);
void  wakeupb(int h,int j);
void  wakeupa(int h,int j);
int timefa=0;// 脉冲速率for a
int timefb=0;// 脉冲速率for b
int cofa=0;//对脉冲数计数的 a
int cofb=0;//对脉冲数计数的 b
int stfa=0;//设定脉冲  a
int stfb=0;//设定脉冲  b



void wakeupa(int h,int j)  // 激活死去的a 并且设定速度 和脉冲数量
//h 给 timefa j 给 stfa
{TIMSK=(1<<OCIE1A);//双比较匹配使能 再次启动
	OCR1A=h;     //初始化0.005s  一个脉冲
	stfa=j;
	
}
void wakeupb(int h,int j)  // 激活死去的b 并且设定速度 和脉冲数量
//h 给 timefa j 给 stfa
{TIMSK=(1<<OCIE1B);//双比较匹配使能 再次启动
	OCR1B=h;     //初始化0.005s  一个脉冲
	stfb=j;
	
}
void TC1_init()
{
	asm("sei");// 全局中断使能
	
	DDRD = 0xff;
	TIMSK=(1<<OCIE1A)|(1<<OCIE1B);//双比较匹配使能
	TCCR1A=(1<<COM1A0)|(1<<COM1B0);//匹配时电平取反
	TCCR1B=(1<<WGM12)|(1<<CS11);//1/8分频器
	OCR1A=5000;//初始化0.005s一个脉冲
	OCR1B=5000;//初始化0.005s一个脉冲
}
ISR(TIMER1_COMPA_vect)
{
	//cofa++;
	//if(cofa>stfa)
	//{TCCR1A=0x00;//停止翻转
	//cofa=0;//count 归零
	//}
	DDRB |= 0XFF;
	PORTB |=0XFF;
}

ISR(TIMER1_COMPB_vect)
{   
	//cofb++;
	//if(cofb>stfb)
	//{TCCR1B=0x00;//停止翻转
		//cofb=0;//count 归零
	//}
	DDRB |= 0XFF;
	PORTB |=0XFF;
}
int main(void)
{
	TC1_init();
	//wakeupa(50000,800);
	//wakeupb(50000,800);
	while (1)
	{
		
	}
}

