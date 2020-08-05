#include<LPC17xx.h>
//#define VTOR (*(volatile uint32_t *) 0xE000ED08)
#define CoreClock 100000000
void TIMER0_IRQHandler(void)
{
volatile uint8_t int_flag;
int_flag=LPC_TIM0->IR;
if((int_flag&0x01)==1)
{
	LPC_TIM0->IR|=0x01;
	if((LPC_GPIO1->FIOPIN)==(1<<29))
		LPC_GPIO1->FIOCLR|=(1<<29);
	else
		LPC_GPIO1->FIOSET|=(1<<29);
}
else if((int_flag &0x02)==2)
{
	LPC_TIM0->IR|=0x02;
	LPC_GPIO1->FIOSET|=(1<<29);
	LPC_TIM0->TCR|=0x01;
}
}
void main()
{
SCB->VTOR=(uint32_t) 0x2000;
NVIC_EnableIRQ(1);
LPC_GPIO1->FIODIR=(1<<29);
LPC_GPIO1->FIOMASK=(0xFFFFFFFF^(1<<29));
LPC_SC->PCLKSEL0&=~(3<<2);

LPC_TIM0 -> TCR = 0x02;
LPC_TIM0->PR  = 0x00;
LPC_TIM0->MR0 =(uint32_t) (CoreClock / 4) /2;
LPC_TIM0 -> MCR= (1<<0)|(1<<1);
LPC_TIM0 -> TCR = 0x01;

while(1);
}
