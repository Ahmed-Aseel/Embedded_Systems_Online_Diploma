#include <stdint.h>

extern int main(void);
void reset_handler(void);
void default_handler(void);
void NMI_handler(void) __attribute__((weak,alias("default_handler")));
void H_fault_handler(void) __attribute__((weak,alias("default_handler")));
void MM_fault_handler(void) __attribute__((weak,alias("default_handler")));
void Bus_fault_handler(void) __attribute__((weak,alias("default_handler")));
void Usage_fault_handler(void) __attribute__((weak,alias("default_handler")));

extern uint32_t _stack_top;
uint32_t vectors[] __attribute__((section(".vectors"))) = {

	(uint32_t) &_stack_top,
	(uint32_t) &NMI_handler,
	(uint32_t) &H_fault_handler,
	(uint32_t) &MM_fault_handler,
	(uint32_t) &Bus_fault_handler,
	(uint32_t) &Usage_fault_handler,
};

extern uint32_t _E_text;
extern uint32_t _S_data;
extern uint32_t _E_data;
extern uint32_t _S_bss;
extern uint32_t _E_bss;

void reset_handler(void)
{
	int i;
	uint32_t data_size = (uint8_t*)&_E_data - (uint8_t*)&_S_data;
	uint8_t* p_scr = (uint8_t*)&_E_text;
	uint8_t* p_dst = (uint8_t*)&_S_data;

	for (i = 0; i < data_size; ++i)
	{
		*((uint8_t*)p_dst) = *((uint8_t*)p_scr);
		p_scr++;
		p_dst++;
	}

	uint32_t bss_size = (uint8_t*)&_E_bss - (uint8_t*)&_S_bss;
	p_dst = (uint8_t*)&_S_bss;

	for (i = 0; i < bss_size; ++i)
	{
		*((uint8_t*)p_dst) = (uint8_t)0;
		p_dst++;
	}

	main();
}

void default_handler(void)
{
	reset_handler();
}