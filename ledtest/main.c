#include<LPC17xx.h>
int main()
{
LPC_GPIO1->FIODIR=(1<<29);
LPC_GPIO1->FIOSET=(1<<29);
while(1);
}