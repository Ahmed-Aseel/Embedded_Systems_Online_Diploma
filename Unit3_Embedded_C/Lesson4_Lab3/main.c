#include<stdint.h>

#define SYSCTL_RCGC2_R    *((volatile uint32_t*)(0x400FE108))
#define GPIO_PORTF_DATA_R *((volatile uint32_t*)(0x400253FC))
#define GPIO_PORTF_DIR_R  *((volatile uint32_t*)(0x40025400))
#define GPIO_PORTF_DEN_R  *((volatile uint32_t*)(0x4002551C))

int main(void)
{
	volatile uint32_t i;
	SYSCTL_RCGC2_R = 0X00000020;
	for(i = 0; i < 200; i++);
	GPIO_PORTF_DIR_R |= 1<<3;
	GPIO_PORTF_DEN_R |= 1<<3;

	while(1)
	{
		GPIO_PORTF_DATA_R |= 1<<3;
		for(i = 0; i < 10000; i++);  // delay
		GPIO_PORTF_DATA_R &= ~(1<<3);
		for(i = 0; i < 10000; i++);  // delay
	}

	return 0;
}
