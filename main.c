
#include <avr/io.h>
#include <avr/interrupt.h>
#define  F_CPU 16000000UL  //����ϵͳʱ��
#include <util/delay.h>
void TC0_init(void);
void TC1_init(void);
void  wakeupb(int h,int j);
void  wakeupa(int h,int j);
int timefa=0;// ��������for a
int timefb=0;// ��������for b
int cofa=0;//�������������� a
int cofb=0;//�������������� b
int stfa=0;//�趨����  a
int stfb=0;//�趨����  b



void wakeupa(int h,int j)  // ������ȥ��a �����趨�ٶ� ����������   
//h �� timefa j �� stfa
{TIMSK=(1<<OCIE1A);//˫�Ƚ�ƥ��ʹ�� �ٴ�����
 OCR1A=h;     //��ʼ��0.005s  һ������
 stfa=j;
	
}
void wakeupb(int h,int j)  // ������ȥ��b �����趨�ٶ� ����������
//h �� timefa j �� stfa
{TIMSK=(1<<OCIE1B);//˫�Ƚ�ƥ��ʹ�� �ٴ�����
	OCR1B=h;     //��ʼ��0.005s  һ������
	stfb=j;
	
}
void TC1_init()
{ asm("sei");// ȫ���ж�ʹ��
 TIMSK=(1<<OCIE1A)|(1<<OCIE1B);//˫�Ƚ�ƥ��ʹ��
 TCCR1A=(1<<COM1A0)|(1<<COM1B0);//ƥ��ʱ��ƽȡ��
 TCCR1B=(1<<WGM12)|(1<<CS11);//1/8��Ƶ��
 OCR1A=50000;//��ʼ��0.005sһ������
 OCR1B=50000;//��ʼ��0.005sһ������
}
ISR(TIMER1_COMPA_vect)
{   cofa++;
      if(cofa>stfa)
    {TCCR1A=0x00;//ֹͣ��ת
     cofa=0;//count ����
    }
}

ISR(TIMER1_COMPB_vect)
{   cofb++;
	if(cofb>stfb)
	{TCCR1B=0x00;//ֹͣ��ת
		cofb=0;//count ����
	}
	
}
int main(void)
{
	TC1_init();
    wakeupa(50000,800);
    wakeupb(50000,800);
	while (1) 
    { 
		
    }
}

