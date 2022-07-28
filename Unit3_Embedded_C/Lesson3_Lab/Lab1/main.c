#include "uart.h"
unsigned char str_buffer[] = "Learn-in-depth: Aseel";

void main(void)
{
	Uart_Send_String (str_buffer);
}