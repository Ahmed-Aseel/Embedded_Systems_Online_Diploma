.section .vectors

.word 0x20001000 			/* stack top address */ 
.word _reset				/* 1 Reset */
.word _vector_handle 		/* 2 NMI */
.word _vector_handle 		/* 3 Hard Fault */
.word _vector_handle 		/* 4 MM Fault */
.word _vector_handle 		/* 5 Bus Fault */
.word _vector_handle 		/* 6 Usage Fault */
.word _vector_handle 		/* 7 RESERVED */
.word _vector_handle 		/* 8 RESERVED */
.word _vector_handle 		/* 9 RESERVED */
.word _vector_handle 		/* 10 RESERVED */
.word _vector_handle 		/* 11 SV Call */
.word _vector_handle 		/* 12 Debug Reserved */
.word _vector_handle 		/* 13 RESERVED */
.word _vector_handle 		/* 14 PendSV */
.word _vector_handle 		/* 15 SysTick */
.word _vector_handle 		/* 16 IRQ0 */
.word _vector_handle 		/* 17 IRQ1 */
.word _vector_handle 		/* 18 IRQ2 */
.word _vector_handle 		/* 19 ... */

.section .text

_reset:
	bl main
	b .   	  /* After main function loop in yourself */
	
.thumb_func  /* For using 16 bits & 32 bits instruction if avilable */

_vector_handle:
	b _reset
