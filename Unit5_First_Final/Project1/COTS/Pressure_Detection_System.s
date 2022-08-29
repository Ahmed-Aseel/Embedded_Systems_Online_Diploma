
Pressure_Detection_System.elf:     file format elf32-littlearm


Disassembly of section .text:

08000000 <vectors>:
 8000000:	20001000 	andcs	r1, r0, r0
 8000004:	08000139 	stmdaeq	r0, {r0, r3, r4, r5, r8}
 8000008:	08000139 	stmdaeq	r0, {r0, r3, r4, r5, r8}
 800000c:	08000139 	stmdaeq	r0, {r0, r3, r4, r5, r8}
 8000010:	08000139 	stmdaeq	r0, {r0, r3, r4, r5, r8}
 8000014:	08000139 	stmdaeq	r0, {r0, r3, r4, r5, r8}

08000018 <Set_Alarm_Actuator>:
 8000018:	b580      	push	{r7, lr}
 800001a:	b082      	sub	sp, #8
 800001c:	af00      	add	r7, sp, #0
 800001e:	4603      	mov	r3, r0
 8000020:	71fb      	strb	r3, [r7, #7]
 8000022:	79fb      	ldrb	r3, [r7, #7]
 8000024:	2b01      	cmp	r3, #1
 8000026:	d102      	bne.n	800002e <Set_Alarm_Actuator+0x16>
 8000028:	f000 f80a 	bl	8000040 <Start_Alarm>
 800002c:	e004      	b.n	8000038 <Set_Alarm_Actuator+0x20>
 800002e:	79fb      	ldrb	r3, [r7, #7]
 8000030:	2b00      	cmp	r3, #0
 8000032:	d101      	bne.n	8000038 <Set_Alarm_Actuator+0x20>
 8000034:	f000 f816 	bl	8000064 <Stop_Alarm>
 8000038:	f107 0708 	add.w	r7, r7, #8
 800003c:	46bd      	mov	sp, r7
 800003e:	bd80      	pop	{r7, pc}

08000040 <Start_Alarm>:
 8000040:	b480      	push	{r7}
 8000042:	af00      	add	r7, sp, #0
 8000044:	f640 030c 	movw	r3, #2060	; 0x80c
 8000048:	f2c4 0301 	movt	r3, #16385	; 0x4001
 800004c:	f640 020c 	movw	r2, #2060	; 0x80c
 8000050:	f2c4 0201 	movt	r2, #16385	; 0x4001
 8000054:	6812      	ldr	r2, [r2, #0]
 8000056:	f422 5200 	bic.w	r2, r2, #8192	; 0x2000
 800005a:	601a      	str	r2, [r3, #0]
 800005c:	46bd      	mov	sp, r7
 800005e:	bc80      	pop	{r7}
 8000060:	4770      	bx	lr
 8000062:	bf00      	nop

08000064 <Stop_Alarm>:
 8000064:	b480      	push	{r7}
 8000066:	af00      	add	r7, sp, #0
 8000068:	f640 030c 	movw	r3, #2060	; 0x80c
 800006c:	f2c4 0301 	movt	r3, #16385	; 0x4001
 8000070:	f640 020c 	movw	r2, #2060	; 0x80c
 8000074:	f2c4 0201 	movt	r2, #16385	; 0x4001
 8000078:	6812      	ldr	r2, [r2, #0]
 800007a:	f442 5200 	orr.w	r2, r2, #8192	; 0x2000
 800007e:	601a      	str	r2, [r3, #0]
 8000080:	46bd      	mov	sp, r7
 8000082:	bc80      	pop	{r7}
 8000084:	4770      	bx	lr
 8000086:	bf00      	nop

08000088 <reset_handler>:
 8000088:	b580      	push	{r7, lr}
 800008a:	b086      	sub	sp, #24
 800008c:	af00      	add	r7, sp, #0
 800008e:	f240 0200 	movw	r2, #0
 8000092:	f2c2 0200 	movt	r2, #8192	; 0x2000
 8000096:	f240 0300 	movw	r3, #0
 800009a:	f2c2 0300 	movt	r3, #8192	; 0x2000
 800009e:	1ad3      	subs	r3, r2, r3
 80000a0:	60bb      	str	r3, [r7, #8]
 80000a2:	f240 2364 	movw	r3, #612	; 0x264
 80000a6:	f6c0 0300 	movt	r3, #2048	; 0x800
 80000aa:	613b      	str	r3, [r7, #16]
 80000ac:	f240 0300 	movw	r3, #0
 80000b0:	f2c2 0300 	movt	r3, #8192	; 0x2000
 80000b4:	60fb      	str	r3, [r7, #12]
 80000b6:	f04f 0300 	mov.w	r3, #0
 80000ba:	617b      	str	r3, [r7, #20]
 80000bc:	e00f      	b.n	80000de <reset_handler+0x56>
 80000be:	693b      	ldr	r3, [r7, #16]
 80000c0:	781a      	ldrb	r2, [r3, #0]
 80000c2:	68fb      	ldr	r3, [r7, #12]
 80000c4:	701a      	strb	r2, [r3, #0]
 80000c6:	693b      	ldr	r3, [r7, #16]
 80000c8:	f103 0301 	add.w	r3, r3, #1
 80000cc:	613b      	str	r3, [r7, #16]
 80000ce:	68fb      	ldr	r3, [r7, #12]
 80000d0:	f103 0301 	add.w	r3, r3, #1
 80000d4:	60fb      	str	r3, [r7, #12]
 80000d6:	697b      	ldr	r3, [r7, #20]
 80000d8:	f103 0301 	add.w	r3, r3, #1
 80000dc:	617b      	str	r3, [r7, #20]
 80000de:	697a      	ldr	r2, [r7, #20]
 80000e0:	68bb      	ldr	r3, [r7, #8]
 80000e2:	429a      	cmp	r2, r3
 80000e4:	d3eb      	bcc.n	80000be <reset_handler+0x36>
 80000e6:	f240 0200 	movw	r2, #0
 80000ea:	f2c2 0200 	movt	r2, #8192	; 0x2000
 80000ee:	f240 0300 	movw	r3, #0
 80000f2:	f2c2 0300 	movt	r3, #8192	; 0x2000
 80000f6:	1ad3      	subs	r3, r2, r3
 80000f8:	607b      	str	r3, [r7, #4]
 80000fa:	f240 0300 	movw	r3, #0
 80000fe:	f2c2 0300 	movt	r3, #8192	; 0x2000
 8000102:	60fb      	str	r3, [r7, #12]
 8000104:	f04f 0300 	mov.w	r3, #0
 8000108:	617b      	str	r3, [r7, #20]
 800010a:	e00b      	b.n	8000124 <reset_handler+0x9c>
 800010c:	68fb      	ldr	r3, [r7, #12]
 800010e:	f04f 0200 	mov.w	r2, #0
 8000112:	701a      	strb	r2, [r3, #0]
 8000114:	68fb      	ldr	r3, [r7, #12]
 8000116:	f103 0301 	add.w	r3, r3, #1
 800011a:	60fb      	str	r3, [r7, #12]
 800011c:	697b      	ldr	r3, [r7, #20]
 800011e:	f103 0301 	add.w	r3, r3, #1
 8000122:	617b      	str	r3, [r7, #20]
 8000124:	697a      	ldr	r2, [r7, #20]
 8000126:	687b      	ldr	r3, [r7, #4]
 8000128:	429a      	cmp	r2, r3
 800012a:	d3ef      	bcc.n	800010c <reset_handler+0x84>
 800012c:	f000 f80a 	bl	8000144 <main>
 8000130:	f107 0718 	add.w	r7, r7, #24
 8000134:	46bd      	mov	sp, r7
 8000136:	bd80      	pop	{r7, pc}

08000138 <default_handler>:
 8000138:	b580      	push	{r7, lr}
 800013a:	af00      	add	r7, sp, #0
 800013c:	f7ff ffa4 	bl	8000088 <reset_handler>
 8000140:	bd80      	pop	{r7, pc}
 8000142:	bf00      	nop

08000144 <main>:
 8000144:	b580      	push	{r7, lr}
 8000146:	b082      	sub	sp, #8
 8000148:	af00      	add	r7, sp, #0
 800014a:	f000 f813 	bl	8000174 <GPIO_INITIALIZATION>
 800014e:	f000 f851 	bl	80001f4 <ALARM_INITIALIZATION>
 8000152:	f000 f87b 	bl	800024c <Get_Pressure_Val>
 8000156:	4603      	mov	r3, r0
 8000158:	607b      	str	r3, [r7, #4]
 800015a:	687b      	ldr	r3, [r7, #4]
 800015c:	2b14      	cmp	r3, #20
 800015e:	dd01      	ble.n	8000164 <main+0x20>
 8000160:	f000 f850 	bl	8000204 <High_Pressure_Detected>
 8000164:	f249 30e0 	movw	r0, #37856	; 0x93e0
 8000168:	f2c0 0004 	movt	r0, #4
 800016c:	f000 f85c 	bl	8000228 <Delay>
 8000170:	e7ef      	b.n	8000152 <main+0xe>
 8000172:	bf00      	nop

08000174 <GPIO_INITIALIZATION>:
 8000174:	b480      	push	{r7}
 8000176:	af00      	add	r7, sp, #0
 8000178:	f241 0318 	movw	r3, #4120	; 0x1018
 800017c:	f2c4 0302 	movt	r3, #16386	; 0x4002
 8000180:	f241 0218 	movw	r2, #4120	; 0x1018
 8000184:	f2c4 0202 	movt	r2, #16386	; 0x4002
 8000188:	6812      	ldr	r2, [r2, #0]
 800018a:	f042 0204 	orr.w	r2, r2, #4
 800018e:	601a      	str	r2, [r3, #0]
 8000190:	f44f 6300 	mov.w	r3, #2048	; 0x800
 8000194:	f2c4 0301 	movt	r3, #16385	; 0x4001
 8000198:	f44f 6200 	mov.w	r2, #2048	; 0x800
 800019c:	f2c4 0201 	movt	r2, #16385	; 0x4001
 80001a0:	6812      	ldr	r2, [r2, #0]
 80001a2:	f422 0270 	bic.w	r2, r2, #15728640	; 0xf00000
 80001a6:	601a      	str	r2, [r3, #0]
 80001a8:	f44f 6300 	mov.w	r3, #2048	; 0x800
 80001ac:	f2c4 0301 	movt	r3, #16385	; 0x4001
 80001b0:	f44f 6200 	mov.w	r2, #2048	; 0x800
 80001b4:	f2c4 0201 	movt	r2, #16385	; 0x4001
 80001b8:	6812      	ldr	r2, [r2, #0]
 80001ba:	601a      	str	r2, [r3, #0]
 80001bc:	f640 0304 	movw	r3, #2052	; 0x804
 80001c0:	f2c4 0301 	movt	r3, #16385	; 0x4001
 80001c4:	f640 0204 	movw	r2, #2052	; 0x804
 80001c8:	f2c4 0201 	movt	r2, #16385	; 0x4001
 80001cc:	6812      	ldr	r2, [r2, #0]
 80001ce:	f422 0270 	bic.w	r2, r2, #15728640	; 0xf00000
 80001d2:	601a      	str	r2, [r3, #0]
 80001d4:	f640 0304 	movw	r3, #2052	; 0x804
 80001d8:	f2c4 0301 	movt	r3, #16385	; 0x4001
 80001dc:	f640 0204 	movw	r2, #2052	; 0x804
 80001e0:	f2c4 0201 	movt	r2, #16385	; 0x4001
 80001e4:	6812      	ldr	r2, [r2, #0]
 80001e6:	f042 3222 	orr.w	r2, r2, #572662306	; 0x22222222
 80001ea:	601a      	str	r2, [r3, #0]
 80001ec:	46bd      	mov	sp, r7
 80001ee:	bc80      	pop	{r7}
 80001f0:	4770      	bx	lr
 80001f2:	bf00      	nop

080001f4 <ALARM_INITIALIZATION>:
 80001f4:	b580      	push	{r7, lr}
 80001f6:	af00      	add	r7, sp, #0
 80001f8:	f04f 0000 	mov.w	r0, #0
 80001fc:	f7ff ff0c 	bl	8000018 <Set_Alarm_Actuator>
 8000200:	bd80      	pop	{r7, pc}
 8000202:	bf00      	nop

08000204 <High_Pressure_Detected>:
 8000204:	b580      	push	{r7, lr}
 8000206:	af00      	add	r7, sp, #0
 8000208:	f04f 0001 	mov.w	r0, #1
 800020c:	f7ff ff04 	bl	8000018 <Set_Alarm_Actuator>
 8000210:	f44f 6054 	mov.w	r0, #3392	; 0xd40
 8000214:	f2c0 0003 	movt	r0, #3
 8000218:	f000 f806 	bl	8000228 <Delay>
 800021c:	f04f 0000 	mov.w	r0, #0
 8000220:	f7ff fefa 	bl	8000018 <Set_Alarm_Actuator>
 8000224:	bd80      	pop	{r7, pc}
 8000226:	bf00      	nop

08000228 <Delay>:
 8000228:	b480      	push	{r7}
 800022a:	b083      	sub	sp, #12
 800022c:	af00      	add	r7, sp, #0
 800022e:	6078      	str	r0, [r7, #4]
 8000230:	e003      	b.n	800023a <Delay+0x12>
 8000232:	687b      	ldr	r3, [r7, #4]
 8000234:	f103 33ff 	add.w	r3, r3, #4294967295
 8000238:	607b      	str	r3, [r7, #4]
 800023a:	687b      	ldr	r3, [r7, #4]
 800023c:	2b00      	cmp	r3, #0
 800023e:	d1f8      	bne.n	8000232 <Delay+0xa>
 8000240:	f107 070c 	add.w	r7, r7, #12
 8000244:	46bd      	mov	sp, r7
 8000246:	bc80      	pop	{r7}
 8000248:	4770      	bx	lr
 800024a:	bf00      	nop

0800024c <Get_Pressure_Val>:
 800024c:	b480      	push	{r7}
 800024e:	af00      	add	r7, sp, #0
 8000250:	f640 0308 	movw	r3, #2056	; 0x808
 8000254:	f2c4 0301 	movt	r3, #16385	; 0x4001
 8000258:	681b      	ldr	r3, [r3, #0]
 800025a:	b2db      	uxtb	r3, r3
 800025c:	4618      	mov	r0, r3
 800025e:	46bd      	mov	sp, r7
 8000260:	bc80      	pop	{r7}
 8000262:	4770      	bx	lr

Disassembly of section .bss:

20000000 <_E_bss>:
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	000000d6 	ldrdeq	r0, [r0], -r6
   4:	00000002 	andeq	r0, r0, r2
   8:	01040000 	mrseq	r0, (UNDEF: 4)
   c:	0000001a 	andeq	r0, r0, sl, lsl r0
  10:	0000c401 	andeq	ip, r0, r1, lsl #8
  14:	00005900 	andeq	r5, r0, r0, lsl #18
  18:	00001800 	andeq	r1, r0, r0, lsl #16
  1c:	00008608 	andeq	r8, r0, r8, lsl #12
  20:	00000008 	andeq	r0, r0, r8
  24:	08010200 	stmdaeq	r1, {r9}
  28:	0000004b 	andeq	r0, r0, fp, asr #32
  2c:	54080102 	strpl	r0, [r8], #-258	; 0x102
  30:	02000000 	andeq	r0, r0, #0
  34:	004d0601 	subeq	r0, sp, r1, lsl #12
  38:	43030000 	movwmi	r0, #12288	; 0x3000
  3c:	02000000 	andeq	r0, r0, #0
  40:	0000251f 	andeq	r2, r0, pc, lsl r5
  44:	05020200 	streq	r0, [r2, #-512]	; 0x200
  48:	000000d5 	ldrdeq	r0, [r0], -r5
  4c:	b1070202 	tstlt	r7, r2, lsl #4
  50:	04000000 	streq	r0, [r0], #-0
  54:	6e690504 	cdpvs	5, 6, cr0, cr9, cr4, {0}
  58:	a1030074 	tstge	r3, r4, ror r0
  5c:	02000000 	andeq	r0, r0, #0
  60:	00006523 	andeq	r6, r0, r3, lsr #10
  64:	07040200 	streq	r0, [r4, -r0, lsl #4]
  68:	00000030 	andeq	r0, r0, r0, lsr r0
  6c:	00050802 	andeq	r0, r5, r2, lsl #16
  70:	02000000 	andeq	r0, r0, #0
  74:	00260708 	eoreq	r0, r6, r8, lsl #14
  78:	04020000 	streq	r0, [r2], #-0
  7c:	00003d04 	andeq	r3, r0, r4, lsl #26
  80:	04080200 	streq	r0, [r8], #-512	; 0x200
  84:	000000aa 	andeq	r0, r0, sl, lsr #1
  88:	00ea0105 	rsceq	r0, sl, r5, lsl #2
  8c:	11010000 	mrsne	r0, (UNDEF: 1)
  90:	00001801 	andeq	r1, r0, r1, lsl #16
  94:	00004008 	andeq	r4, r0, r8
  98:	00000008 	andeq	r0, r0, r8
  9c:	00af0100 	adceq	r0, pc, r0, lsl #2
  a0:	69060000 	stmdbvs	r6, {}	; <UNPREDICTABLE>
  a4:	3a110100 	bcc	4404ac <vectors-0x7bbfb54>
  a8:	02000000 	andeq	r0, r0, #0
  ac:	07007791 			; <UNDEFINED> instruction: 0x07007791
  b0:	00000e01 	andeq	r0, r0, r1, lsl #28
  b4:	401e0100 	andsmi	r0, lr, r0, lsl #2
  b8:	62080000 	andvs	r0, r8, #0
  bc:	38080000 	stmdacc	r8, {}	; <UNPREDICTABLE>
  c0:	01000000 	mrseq	r0, (UNDEF: 0)
  c4:	00df0107 	sbcseq	r0, pc, r7, lsl #2
  c8:	24010000 	strcs	r0, [r1], #-0
  cc:	08000064 	stmdaeq	r0, {r2, r5, r6}
  d0:	08000086 	stmdaeq	r0, {r1, r2, r7}
  d4:	00000064 	andeq	r0, r0, r4, rrx
  d8:	01700001 	cmneq	r0, r1
  dc:	00020000 	andeq	r0, r2, r0
  e0:	00000076 	andeq	r0, r0, r6, ror r0
  e4:	001a0104 	andseq	r0, sl, r4, lsl #2
  e8:	fd010000 	stc2	0, cr0, [r1, #-0]
  ec:	59000000 	stmdbpl	r0, {}	; <UNPREDICTABLE>
  f0:	88000000 	stmdahi	r0, {}	; <UNPREDICTABLE>
  f4:	42080000 	andmi	r0, r8, #0
  f8:	5f080001 	svcpl	0x00080001
  fc:	02000000 	andeq	r0, r0, #0
 100:	004d0601 	subeq	r0, sp, r1, lsl #12
 104:	43030000 	movwmi	r0, #12288	; 0x3000
 108:	02000000 	andeq	r0, r0, #0
 10c:	0000372a 	andeq	r3, r0, sl, lsr #14
 110:	08010200 	stmdaeq	r1, {r9}
 114:	0000004b 	andeq	r0, r0, fp, asr #32
 118:	d5050202 	strle	r0, [r5, #-514]	; 0x202
 11c:	02000000 	andeq	r0, r0, #0
 120:	00b10702 	adcseq	r0, r1, r2, lsl #14
 124:	04020000 	streq	r0, [r2], #-0
 128:	00000505 	andeq	r0, r0, r5, lsl #10
 12c:	00a10300 	adceq	r0, r1, r0, lsl #6
 130:	50020000 	andpl	r0, r2, r0
 134:	0000005e 	andeq	r0, r0, lr, asr r0
 138:	2b070402 	blcs	1c1148 <vectors-0x7e3eeb8>
 13c:	02000000 	andeq	r0, r0, #0
 140:	00000508 	andeq	r0, r0, r8, lsl #10
 144:	08020000 	stmdaeq	r2, {}	; <UNPREDICTABLE>
 148:	00002607 	andeq	r2, r0, r7, lsl #12
 14c:	05040400 	streq	r0, [r4, #-1024]	; 0x400
 150:	00746e69 	rsbseq	r6, r4, r9, ror #28
 154:	30070402 	andcc	r0, r7, r2, lsl #8
 158:	05000000 	streq	r0, [r0, #-0]
 15c:	00016701 	andeq	r6, r1, r1, lsl #14
 160:	011d0100 	tsteq	sp, r0, lsl #2
 164:	08000088 	stmdaeq	r0, {r3, r7}
 168:	08000138 	stmdaeq	r0, {r3, r4, r5, r8}
 16c:	00000090 	muleq	r0, r0, r0
 170:	0000e001 	andeq	lr, r0, r1
 174:	00690600 	rsbeq	r0, r9, r0, lsl #12
 178:	00731f01 	rsbseq	r1, r3, r1, lsl #30
 17c:	91020000 	mrsls	r0, (UNDEF: 2)
 180:	010e0774 	tsteq	lr, r4, ror r7
 184:	20010000 	andcs	r0, r1, r0
 188:	00000053 	andeq	r0, r0, r3, asr r0
 18c:	07689102 	strbeq	r9, [r8, -r2, lsl #2]!
 190:	00000118 	andeq	r0, r0, r8, lsl r1
 194:	00e02101 	rsceq	r2, r0, r1, lsl #2
 198:	91020000 	mrsls	r0, (UNDEF: 2)
 19c:	01480770 	hvceq	32880	; 0x8070
 1a0:	22010000 	andcs	r0, r1, #0
 1a4:	000000e0 	andeq	r0, r0, r0, ror #1
 1a8:	076c9102 	strbeq	r9, [ip, -r2, lsl #2]!
 1ac:	0000015e 	andeq	r0, r0, lr, asr r1
 1b0:	00532b01 	subseq	r2, r3, r1, lsl #22
 1b4:	91020000 	mrsls	r0, (UNDEF: 2)
 1b8:	04080064 	streq	r0, [r8], #-100	; 0x64
 1bc:	0000002c 	andeq	r0, r0, ip, lsr #32
 1c0:	014e0109 	cmpeq	lr, r9, lsl #2
 1c4:	37010000 	strcc	r0, [r1, -r0]
 1c8:	00013801 	andeq	r3, r1, r1, lsl #16
 1cc:	00014208 	andeq	r4, r1, r8, lsl #4
 1d0:	0000c808 	andeq	ip, r0, r8, lsl #16
 1d4:	1e0a0100 	adfnee	f0, f2, f0
 1d8:	01000001 	tsteq	r0, r1
 1dc:	0000530c 	andeq	r5, r0, ip, lsl #6
 1e0:	0b010100 	bleq	405e8 <vectors-0x7fbfa18>
 1e4:	00000053 	andeq	r0, r0, r3, asr r0
 1e8:	00000119 	andeq	r0, r0, r9, lsl r1
 1ec:	0001190c 	andeq	r1, r1, ip, lsl #18
 1f0:	02000500 	andeq	r0, r0, #0, 10
 1f4:	01750704 	cmneq	r5, r4, lsl #14
 1f8:	290d0000 	stmdbcs	sp, {}	; <UNPREDICTABLE>
 1fc:	01000001 	tsteq	r0, r1
 200:	0001090d 	andeq	r0, r1, sp, lsl #18
 204:	03050100 	movweq	r0, #20736	; 0x5100
 208:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
 20c:	0001400a 	andeq	r4, r1, sl
 210:	53170100 	tstpl	r7, #0, 2
 214:	01000000 	mrseq	r0, (UNDEF: 0)
 218:	017e0a01 	cmneq	lr, r1, lsl #20
 21c:	18010000 	stmdane	r1, {}	; <UNPREDICTABLE>
 220:	00000053 	andeq	r0, r0, r3, asr r0
 224:	380a0101 	stmdacc	sl, {r0, r8}
 228:	01000001 	tsteq	r0, r1
 22c:	00005319 	andeq	r5, r0, r9, lsl r3
 230:	0a010100 	beq	40638 <vectors-0x7fbf9c8>
 234:	00000107 	andeq	r0, r0, r7, lsl #2
 238:	00531a01 	subseq	r1, r3, r1, lsl #20
 23c:	01010000 	mrseq	r0, (UNDEF: 1)
 240:	0001310a 	andeq	r3, r1, sl, lsl #2
 244:	531b0100 	tstpl	fp, #0, 2
 248:	01000000 	mrseq	r0, (UNDEF: 0)
 24c:	00970001 	addseq	r0, r7, r1
 250:	00020000 	andeq	r0, r2, r0
 254:	0000013a 	andeq	r0, r0, sl, lsr r1
 258:	001a0104 	andseq	r0, sl, r4, lsl #2
 25c:	86010000 	strhi	r0, [r1], -r0
 260:	59000001 	stmdbpl	r0, {r0}
 264:	44000000 	strmi	r0, [r0], #-0
 268:	72080001 	andvc	r0, r8, #1
 26c:	1a080001 	bne	200278 <vectors-0x7dffd88>
 270:	02000001 	andeq	r0, r0, #1
 274:	004b0801 	subeq	r0, fp, r1, lsl #16
 278:	01020000 	mrseq	r0, (UNDEF: 2)
 27c:	00005408 	andeq	r5, r0, r8, lsl #8
 280:	06010200 	streq	r0, [r1], -r0, lsl #4
 284:	0000004d 	andeq	r0, r0, sp, asr #32
 288:	d5050202 	strle	r0, [r5, #-514]	; 0x202
 28c:	02000000 	andeq	r0, r0, #0
 290:	00b10702 	adcseq	r0, r1, r2, lsl #14
 294:	04030000 	streq	r0, [r3], #-0
 298:	746e6905 	strbtvc	r6, [lr], #-2309	; 0x905
 29c:	07040200 	streq	r0, [r4, -r0, lsl #4]
 2a0:	00000030 	andeq	r0, r0, r0, lsr r0
 2a4:	00050802 	andeq	r0, r5, r2, lsl #16
 2a8:	02000000 	andeq	r0, r0, #0
 2ac:	00260708 	eoreq	r0, r6, r8, lsl #14
 2b0:	04020000 	streq	r0, [r2], #-0
 2b4:	00003d04 	andeq	r3, r0, r4, lsl #26
 2b8:	04080200 	streq	r0, [r8], #-512	; 0x200
 2bc:	000000aa 	andeq	r0, r0, sl, lsr #1
 2c0:	018d0104 	orreq	r0, sp, r4, lsl #2
 2c4:	0e010000 	cdpeq	0, 0, cr0, cr1, cr0, {0}
 2c8:	00000048 	andeq	r0, r0, r8, asr #32
 2cc:	08000144 	stmdaeq	r0, {r2, r6, r8}
 2d0:	08000172 	stmdaeq	r0, {r1, r4, r5, r6, r8}
 2d4:	000000f4 	strdeq	r0, [r0], -r4
 2d8:	01920501 	orrseq	r0, r2, r1, lsl #10
 2dc:	10010000 	andne	r0, r1, r0
 2e0:	00000048 	andeq	r0, r0, r8, asr #32
 2e4:	00749102 	rsbseq	r9, r4, r2, lsl #2
 2e8:	00008f00 	andeq	r8, r0, r0, lsl #30
 2ec:	8b000200 	blhi	af4 <vectors-0x7fff50c>
 2f0:	04000001 	streq	r0, [r0], #-1
 2f4:	00001a01 	andeq	r1, r0, r1, lsl #20
 2f8:	01990100 	orrseq	r0, r9, r0, lsl #2
 2fc:	00590000 	subseq	r0, r9, r0
 300:	01740000 	cmneq	r4, r0
 304:	01f20800 	mvnseq	r0, r0, lsl #16
 308:	01570800 	cmpeq	r7, r0, lsl #16
 30c:	01020000 	mrseq	r0, (UNDEF: 2)
 310:	00004b08 	andeq	r4, r0, r8, lsl #22
 314:	08010200 	stmdaeq	r1, {r9}
 318:	00000054 	andeq	r0, r0, r4, asr r0
 31c:	4d060102 	stfmis	f0, [r6, #-8]
 320:	02000000 	andeq	r0, r0, #0
 324:	00d50502 	sbcseq	r0, r5, r2, lsl #10
 328:	02020000 	andeq	r0, r2, #0
 32c:	0000b107 	andeq	fp, r0, r7, lsl #2
 330:	05040300 	streq	r0, [r4, #-768]	; 0x300
 334:	00746e69 	rsbseq	r6, r4, r9, ror #28
 338:	0000a104 	andeq	sl, r0, r4, lsl #2
 33c:	5a230200 	bpl	8c0b44 <vectors-0x773f4bc>
 340:	02000000 	andeq	r0, r0, #0
 344:	00300704 	eorseq	r0, r0, r4, lsl #14
 348:	08020000 	stmdaeq	r2, {}	; <UNPREDICTABLE>
 34c:	00000005 	andeq	r0, r0, r5
 350:	07080200 	streq	r0, [r8, -r0, lsl #4]
 354:	00000026 	andeq	r0, r0, r6, lsr #32
 358:	3d040402 	cfstrscc	mvf0, [r4, #-8]
 35c:	02000000 	andeq	r0, r0, #0
 360:	00aa0408 	adceq	r0, sl, r8, lsl #8
 364:	01050000 	mrseq	r0, (UNDEF: 5)
 368:	000001a8 	andeq	r0, r0, r8, lsr #3
 36c:	01741001 	cmneq	r4, r1
 370:	01f20800 	mvnseq	r0, r0, lsl #16
 374:	012c0800 	teqeq	ip, r0, lsl #16
 378:	00010000 	andeq	r0, r1, r0
 37c:	000000c9 	andeq	r0, r0, r9, asr #1
 380:	01d80002 	bicseq	r0, r8, r2
 384:	01040000 	mrseq	r0, (UNDEF: 4)
 388:	0000001a 	andeq	r0, r0, sl, lsl r0
 38c:	0001ef01 	andeq	lr, r1, r1, lsl #30
 390:	00005900 	andeq	r5, r0, r0, lsl #18
 394:	0001f400 	andeq	pc, r1, r0, lsl #8
 398:	00024a08 	andeq	r4, r2, r8, lsl #20
 39c:	0001af08 	andeq	sl, r1, r8, lsl #30
 3a0:	08010200 	stmdaeq	r1, {r9}
 3a4:	0000004b 	andeq	r0, r0, fp, asr #32
 3a8:	54080102 	strpl	r0, [r8], #-258	; 0x102
 3ac:	02000000 	andeq	r0, r0, #0
 3b0:	004d0601 	subeq	r0, sp, r1, lsl #12
 3b4:	02020000 	andeq	r0, r2, #0
 3b8:	0000d505 	andeq	sp, r0, r5, lsl #10
 3bc:	07020200 	streq	r0, [r2, -r0, lsl #4]
 3c0:	000000b1 	strheq	r0, [r0], -r1
 3c4:	69050403 	stmdbvs	r5, {r0, r1, sl}
 3c8:	0400746e 	streq	r7, [r0], #-1134	; 0x46e
 3cc:	000000a1 	andeq	r0, r0, r1, lsr #1
 3d0:	005a2302 	subseq	r2, sl, r2, lsl #6
 3d4:	04020000 	streq	r0, [r2], #-0
 3d8:	00003007 	andeq	r3, r0, r7
 3dc:	05080200 	streq	r0, [r8, #-512]	; 0x200
 3e0:	00000000 	andeq	r0, r0, r0
 3e4:	26070802 	strcs	r0, [r7], -r2, lsl #16
 3e8:	02000000 	andeq	r0, r0, #0
 3ec:	003d0404 	eorseq	r0, sp, r4, lsl #8
 3f0:	08020000 	stmdaeq	r2, {}	; <UNPREDICTABLE>
 3f4:	0000aa04 	andeq	sl, r0, r4, lsl #20
 3f8:	da010500 	ble	41800 <vectors-0x7fbe800>
 3fc:	01000001 	tsteq	r0, r1
 400:	0001f40f 	andeq	pc, r1, pc, lsl #8
 404:	00020208 	andeq	r0, r2, r8, lsl #4
 408:	00015808 	andeq	r5, r1, r8, lsl #16
 40c:	01050100 	mrseq	r0, (UNDEF: 21)
 410:	000001bc 			; <UNDEFINED> instruction: 0x000001bc
 414:	02041601 	andeq	r1, r4, #1048576	; 0x100000
 418:	02260800 	eoreq	r0, r6, #0, 16
 41c:	01840800 	orreq	r0, r4, r0, lsl #16
 420:	06010000 	streq	r0, [r1], -r0
 424:	00020001 	andeq	r0, r2, r1
 428:	01210100 	teqeq	r1, r0, lsl #2
 42c:	08000228 	stmdaeq	r0, {r3, r5, r9}
 430:	0800024a 	stmdaeq	r0, {r1, r3, r6, r9}
 434:	000001b0 			; <UNDEFINED> instruction: 0x000001b0
 438:	01d30701 	bicseq	r0, r3, r1, lsl #14
 43c:	21010000 	mrscs	r0, (UNDEF: 1)
 440:	0000004f 	andeq	r0, r0, pc, asr #32
 444:	00749102 	rsbseq	r9, r4, r2, lsl #2
 448:	00009300 	andeq	r9, r0, r0, lsl #6
 44c:	4c000200 	sfmmi	f0, 4, [r0], {-0}
 450:	04000002 	streq	r0, [r0], #-2
 454:	00001a01 	andeq	r1, r0, r1, lsl #20
 458:	02060100 	andeq	r0, r6, #0, 2
 45c:	00590000 	subseq	r0, r9, r0
 460:	024c0000 	subeq	r0, ip, #0
 464:	02640800 	rsbeq	r0, r4, #0, 16
 468:	02190800 	andseq	r0, r9, #0, 16
 46c:	01020000 	mrseq	r0, (UNDEF: 2)
 470:	00004b08 	andeq	r4, r0, r8, lsl #22
 474:	08010200 	stmdaeq	r1, {r9}
 478:	00000054 	andeq	r0, r0, r4, asr r0
 47c:	4d060102 	stfmis	f0, [r6, #-8]
 480:	02000000 	andeq	r0, r0, #0
 484:	00d50502 	sbcseq	r0, r5, r2, lsl #10
 488:	02020000 	andeq	r0, r2, #0
 48c:	0000b107 	andeq	fp, r0, r7, lsl #2
 490:	05040300 	streq	r0, [r4, #-768]	; 0x300
 494:	00746e69 	rsbseq	r6, r4, r9, ror #28
 498:	0000a104 	andeq	sl, r0, r4, lsl #2
 49c:	5a230200 	bpl	8c0ca4 <vectors-0x773f35c>
 4a0:	02000000 	andeq	r0, r0, #0
 4a4:	00300704 	eorseq	r0, r0, r4, lsl #14
 4a8:	08020000 	stmdaeq	r2, {}	; <UNPREDICTABLE>
 4ac:	00000005 	andeq	r0, r0, r5
 4b0:	07080200 	streq	r0, [r8, -r0, lsl #4]
 4b4:	00000026 	andeq	r0, r0, r6, lsr #32
 4b8:	3d040402 	cfstrscc	mvf0, [r4, #-8]
 4bc:	02000000 	andeq	r0, r0, #0
 4c0:	00aa0408 	adceq	r0, sl, r8, lsl #8
 4c4:	01050000 	mrseq	r0, (UNDEF: 5)
 4c8:	00000217 	andeq	r0, r0, r7, lsl r2
 4cc:	004f1001 	subeq	r1, pc, r1
 4d0:	024c0000 	subeq	r0, ip, #0
 4d4:	02640800 	rsbeq	r0, r4, #0, 16
 4d8:	01e80800 	mvneq	r0, r0, lsl #16
 4dc:	00010000 	andeq	r0, r1, r0

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0x101
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10011201 	andne	r1, r1, r1, lsl #4
  10:	02000006 	andeq	r0, r0, #6
  14:	0b0b0024 	bleq	2c00ac <vectors-0x7d3ff54>
  18:	0e030b3e 	vmoveq.16	d3[0], r0
  1c:	16030000 	strne	r0, [r3], -r0
  20:	3a0e0300 	bcc	380c28 <vectors-0x7c7f3d8>
  24:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
  28:	04000013 	streq	r0, [r0], #-19
  2c:	0b0b0024 	bleq	2c00c4 <vectors-0x7d3ff3c>
  30:	08030b3e 	stmdaeq	r3, {r1, r2, r3, r4, r5, r8, r9, fp}
  34:	2e050000 	cdpcs	0, 0, cr0, cr5, cr0, {0}
  38:	030c3f01 	movweq	r3, #52993	; 0xcf01
  3c:	3b0b3a0e 	blcc	2ce87c <vectors-0x7d31784>
  40:	110c270b 	tstne	ip, fp, lsl #14
  44:	40011201 	andmi	r1, r1, r1, lsl #4
  48:	0c429606 	mcrreq	6, 0, r9, r2, cr6
  4c:	00001301 	andeq	r1, r0, r1, lsl #6
  50:	03000506 	movweq	r0, #1286	; 0x506
  54:	3b0b3a08 	blcc	2ce87c <vectors-0x7d31784>
  58:	0213490b 	andseq	r4, r3, #180224	; 0x2c000
  5c:	0700000a 	streq	r0, [r0, -sl]
  60:	0c3f002e 	ldceq	0, cr0, [pc], #-184	; ffffffb0 <_stack_top+0xdfffefb0>
  64:	0b3a0e03 	bleq	e83878 <vectors-0x717c788>
  68:	01110b3b 	tsteq	r1, fp, lsr fp
  6c:	06400112 			; <UNDEFINED> instruction: 0x06400112
  70:	000c4297 	muleq	ip, r7, r2
  74:	11010000 	mrsne	r0, (UNDEF: 1)
  78:	130e2501 	movwne	r2, #58625	; 0xe501
  7c:	1b0e030b 	blne	380cb0 <vectors-0x7c7f350>
  80:	1201110e 	andne	r1, r1, #-2147483645	; 0x80000003
  84:	00061001 	andeq	r1, r6, r1
  88:	00240200 	eoreq	r0, r4, r0, lsl #4
  8c:	0b3e0b0b 	bleq	f82cc0 <vectors-0x707d340>
  90:	00000e03 	andeq	r0, r0, r3, lsl #28
  94:	03001603 	movweq	r1, #1539	; 0x603
  98:	3b0b3a0e 	blcc	2ce8d8 <vectors-0x7d31728>
  9c:	0013490b 	andseq	r4, r3, fp, lsl #18
  a0:	00240400 	eoreq	r0, r4, r0, lsl #8
  a4:	0b3e0b0b 	bleq	f82cd8 <vectors-0x707d328>
  a8:	00000803 	andeq	r0, r0, r3, lsl #16
  ac:	3f012e05 	svccc	0x00012e05
  b0:	3a0e030c 	bcc	380ce8 <vectors-0x7c7f318>
  b4:	270b3b0b 	strcs	r3, [fp, -fp, lsl #22]
  b8:	1201110c 	andne	r1, r1, #12, 2
  bc:	96064001 	strls	r4, [r6], -r1
  c0:	13010c42 	movwne	r0, #7234	; 0x1c42
  c4:	34060000 	strcc	r0, [r6], #-0
  c8:	3a080300 	bcc	200cd0 <vectors-0x7dff330>
  cc:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
  d0:	000a0213 	andeq	r0, sl, r3, lsl r2
  d4:	00340700 	eorseq	r0, r4, r0, lsl #14
  d8:	0b3a0e03 	bleq	e838ec <vectors-0x717c714>
  dc:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  e0:	00000a02 	andeq	r0, r0, r2, lsl #20
  e4:	0b000f08 	bleq	3d0c <vectors-0x7ffc2f4>
  e8:	0013490b 	andseq	r4, r3, fp, lsl #18
  ec:	002e0900 	eoreq	r0, lr, r0, lsl #18
  f0:	0e030c3f 	mcreq	12, 0, r0, cr3, cr15, {1}
  f4:	0b3b0b3a 	bleq	ec2de4 <vectors-0x713d21c>
  f8:	01110c27 	tsteq	r1, r7, lsr #24
  fc:	06400112 			; <UNDEFINED> instruction: 0x06400112
 100:	000c4296 	muleq	ip, r6, r2
 104:	00340a00 	eorseq	r0, r4, r0, lsl #20
 108:	0b3a0e03 	bleq	e8391c <vectors-0x717c6e4>
 10c:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 110:	0c3c0c3f 	ldceq	12, cr0, [ip], #-252	; 0xffffff04
 114:	010b0000 	mrseq	r0, (UNDEF: 11)
 118:	01134901 	tsteq	r3, r1, lsl #18
 11c:	0c000013 	stceq	0, cr0, [r0], {19}
 120:	13490021 	movtne	r0, #36897	; 0x9021
 124:	00000b2f 	andeq	r0, r0, pc, lsr #22
 128:	0300340d 	movweq	r3, #1037	; 0x40d
 12c:	3b0b3a0e 	blcc	2ce96c <vectors-0x7d31694>
 130:	3f13490b 	svccc	0x0013490b
 134:	000a020c 	andeq	r0, sl, ip, lsl #4
 138:	11010000 	mrsne	r0, (UNDEF: 1)
 13c:	130e2501 	movwne	r2, #58625	; 0xe501
 140:	1b0e030b 	blne	380d74 <vectors-0x7c7f28c>
 144:	1201110e 	andne	r1, r1, #-2147483645	; 0x80000003
 148:	00061001 	andeq	r1, r6, r1
 14c:	00240200 	eoreq	r0, r4, r0, lsl #4
 150:	0b3e0b0b 	bleq	f82d84 <vectors-0x707d27c>
 154:	00000e03 	andeq	r0, r0, r3, lsl #28
 158:	0b002403 	bleq	916c <vectors-0x7ff6e94>
 15c:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
 160:	04000008 	streq	r0, [r0], #-8
 164:	0c3f012e 	ldfeqs	f0, [pc], #-184	; b4 <vectors-0x7ffff4c>
 168:	0b3a0e03 	bleq	e8397c <vectors-0x717c684>
 16c:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 170:	01120111 	tsteq	r2, r1, lsl r1
 174:	42960640 	addsmi	r0, r6, #64, 12	; 0x4000000
 178:	0500000c 	streq	r0, [r0, #-12]
 17c:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 180:	0b3b0b3a 	bleq	ec2e70 <vectors-0x713d190>
 184:	0a021349 	beq	84eb0 <vectors-0x7f7b150>
 188:	01000000 	mrseq	r0, (UNDEF: 0)
 18c:	0e250111 	mcreq	1, 1, r0, cr5, cr1, {0}
 190:	0e030b13 	vmoveq.32	d3[0], r0
 194:	01110e1b 	tsteq	r1, fp, lsl lr
 198:	06100112 			; <UNDEFINED> instruction: 0x06100112
 19c:	24020000 	strcs	r0, [r2], #-0
 1a0:	3e0b0b00 	vmlacc.f64	d0, d11, d0
 1a4:	000e030b 	andeq	r0, lr, fp, lsl #6
 1a8:	00240300 	eoreq	r0, r4, r0, lsl #6
 1ac:	0b3e0b0b 	bleq	f82de0 <vectors-0x707d220>
 1b0:	00000803 	andeq	r0, r0, r3, lsl #16
 1b4:	03001604 	movweq	r1, #1540	; 0x604
 1b8:	3b0b3a0e 	blcc	2ce9f8 <vectors-0x7d31608>
 1bc:	0013490b 	andseq	r4, r3, fp, lsl #18
 1c0:	002e0500 	eoreq	r0, lr, r0, lsl #10
 1c4:	0e030c3f 	mcreq	12, 0, r0, cr3, cr15, {1}
 1c8:	0b3b0b3a 	bleq	ec2eb8 <vectors-0x713d148>
 1cc:	01120111 	tsteq	r2, r1, lsl r1
 1d0:	42970640 	addsmi	r0, r7, #64, 12	; 0x4000000
 1d4:	0000000c 	andeq	r0, r0, ip
 1d8:	25011101 	strcs	r1, [r1, #-257]	; 0x101
 1dc:	030b130e 	movweq	r1, #45838	; 0xb30e
 1e0:	110e1b0e 	tstne	lr, lr, lsl #22
 1e4:	10011201 	andne	r1, r1, r1, lsl #4
 1e8:	02000006 	andeq	r0, r0, #6
 1ec:	0b0b0024 	bleq	2c0284 <vectors-0x7d3fd7c>
 1f0:	0e030b3e 	vmoveq.16	d3[0], r0
 1f4:	24030000 	strcs	r0, [r3], #-0
 1f8:	3e0b0b00 	vmlacc.f64	d0, d11, d0
 1fc:	0008030b 	andeq	r0, r8, fp, lsl #6
 200:	00160400 	andseq	r0, r6, r0, lsl #8
 204:	0b3a0e03 	bleq	e83a18 <vectors-0x717c5e8>
 208:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 20c:	2e050000 	cdpcs	0, 0, cr0, cr5, cr0, {0}
 210:	030c3f00 	movweq	r3, #52992	; 0xcf00
 214:	3b0b3a0e 	blcc	2cea54 <vectors-0x7d315ac>
 218:	1201110b 	andne	r1, r1, #-1073741822	; 0xc0000002
 21c:	96064001 	strls	r4, [r6], -r1
 220:	00000c42 	andeq	r0, r0, r2, asr #24
 224:	3f012e06 	svccc	0x00012e06
 228:	3a0e030c 	bcc	380e60 <vectors-0x7c7f1a0>
 22c:	270b3b0b 	strcs	r3, [fp, -fp, lsl #22]
 230:	1201110c 	andne	r1, r1, #12, 2
 234:	97064001 	strls	r4, [r6, -r1]
 238:	00000c42 	andeq	r0, r0, r2, asr #24
 23c:	03000507 	movweq	r0, #1287	; 0x507
 240:	3b0b3a0e 	blcc	2cea80 <vectors-0x7d31580>
 244:	0213490b 	andseq	r4, r3, #180224	; 0x2c000
 248:	0000000a 	andeq	r0, r0, sl
 24c:	25011101 	strcs	r1, [r1, #-257]	; 0x101
 250:	030b130e 	movweq	r1, #45838	; 0xb30e
 254:	110e1b0e 	tstne	lr, lr, lsl #22
 258:	10011201 	andne	r1, r1, r1, lsl #4
 25c:	02000006 	andeq	r0, r0, #6
 260:	0b0b0024 	bleq	2c02f8 <vectors-0x7d3fd08>
 264:	0e030b3e 	vmoveq.16	d3[0], r0
 268:	24030000 	strcs	r0, [r3], #-0
 26c:	3e0b0b00 	vmlacc.f64	d0, d11, d0
 270:	0008030b 	andeq	r0, r8, fp, lsl #6
 274:	00160400 	andseq	r0, r6, r0, lsl #8
 278:	0b3a0e03 	bleq	e83a8c <vectors-0x717c574>
 27c:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 280:	2e050000 	cdpcs	0, 0, cr0, cr5, cr0, {0}
 284:	030c3f00 	movweq	r3, #52992	; 0xcf00
 288:	3b0b3a0e 	blcc	2ceac8 <vectors-0x7d31538>
 28c:	1113490b 	tstne	r3, fp, lsl #18
 290:	40011201 	andmi	r1, r1, r1, lsl #4
 294:	0c429706 	mcrreq	7, 0, r9, r2, cr6
 298:	Address 0x00000298 is out of bounds.


Disassembly of section .debug_loc:

00000000 <.debug_loc>:
   0:	00000000 	andeq	r0, r0, r0
   4:	00000002 	andeq	r0, r0, r2
   8:	007d0002 	rsbseq	r0, sp, r2
   c:	00000002 	andeq	r0, r0, r2
  10:	00000004 	andeq	r0, r0, r4
  14:	087d0002 	ldmdaeq	sp!, {r1}^
  18:	00000004 	andeq	r0, r0, r4
  1c:	00000006 	andeq	r0, r0, r6
  20:	107d0002 	rsbsne	r0, sp, r2
  24:	00000006 	andeq	r0, r0, r6
  28:	00000028 	andeq	r0, r0, r8, lsr #32
  2c:	10770002 	rsbsne	r0, r7, r2
	...
  38:	00000028 	andeq	r0, r0, r8, lsr #32
  3c:	0000002a 	andeq	r0, r0, sl, lsr #32
  40:	007d0002 	rsbseq	r0, sp, r2
  44:	0000002a 	andeq	r0, r0, sl, lsr #32
  48:	0000002c 	andeq	r0, r0, ip, lsr #32
  4c:	047d0002 	ldrbteq	r0, [sp], #-2
  50:	0000002c 	andeq	r0, r0, ip, lsr #32
  54:	0000004a 	andeq	r0, r0, sl, asr #32
  58:	04770002 	ldrbteq	r0, [r7], #-2
	...
  64:	0000004c 	andeq	r0, r0, ip, asr #32
  68:	0000004e 	andeq	r0, r0, lr, asr #32
  6c:	007d0002 	rsbseq	r0, sp, r2
  70:	0000004e 	andeq	r0, r0, lr, asr #32
  74:	00000050 	andeq	r0, r0, r0, asr r0
  78:	047d0002 	ldrbteq	r0, [sp], #-2
  7c:	00000050 	andeq	r0, r0, r0, asr r0
  80:	0000006e 	andeq	r0, r0, lr, rrx
  84:	04770002 	ldrbteq	r0, [r7], #-2
	...
  94:	00000002 	andeq	r0, r0, r2
  98:	007d0002 	rsbseq	r0, sp, r2
  9c:	00000002 	andeq	r0, r0, r2
  a0:	00000004 	andeq	r0, r0, r4
  a4:	087d0002 	ldmdaeq	sp!, {r1}^
  a8:	00000004 	andeq	r0, r0, r4
  ac:	00000006 	andeq	r0, r0, r6
  b0:	207d0002 	rsbscs	r0, sp, r2
  b4:	00000006 	andeq	r0, r0, r6
  b8:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  bc:	20770002 	rsbscs	r0, r7, r2
	...
  c8:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  cc:	000000b2 	strheq	r0, [r0], -r2
  d0:	007d0002 	rsbseq	r0, sp, r2
  d4:	000000b2 	strheq	r0, [r0], -r2
  d8:	000000b4 	strheq	r0, [r0], -r4
  dc:	087d0002 	ldmdaeq	sp!, {r1}^
  e0:	000000b4 	strheq	r0, [r0], -r4
  e4:	000000ba 	strheq	r0, [r0], -sl
  e8:	08770002 	ldmdaeq	r7!, {r1}^
	...
  f8:	00000002 	andeq	r0, r0, r2
  fc:	007d0002 	rsbseq	r0, sp, r2
 100:	00000002 	andeq	r0, r0, r2
 104:	00000004 	andeq	r0, r0, r4
 108:	087d0002 	ldmdaeq	sp!, {r1}^
 10c:	00000004 	andeq	r0, r0, r4
 110:	00000006 	andeq	r0, r0, r6
 114:	107d0002 	rsbsne	r0, sp, r2
 118:	00000006 	andeq	r0, r0, r6
 11c:	0000002e 	andeq	r0, r0, lr, lsr #32
 120:	10770002 	rsbsne	r0, r7, r2
	...
 130:	00000002 	andeq	r0, r0, r2
 134:	007d0002 	rsbseq	r0, sp, r2
 138:	00000002 	andeq	r0, r0, r2
 13c:	00000004 	andeq	r0, r0, r4
 140:	047d0002 	ldrbteq	r0, [sp], #-2
 144:	00000004 	andeq	r0, r0, r4
 148:	0000007e 	andeq	r0, r0, lr, ror r0
 14c:	04770002 	ldrbteq	r0, [r7], #-2
	...
 15c:	00000002 	andeq	r0, r0, r2
 160:	007d0002 	rsbseq	r0, sp, r2
 164:	00000002 	andeq	r0, r0, r2
 168:	00000004 	andeq	r0, r0, r4
 16c:	087d0002 	ldmdaeq	sp!, {r1}^
 170:	00000004 	andeq	r0, r0, r4
 174:	0000000e 	andeq	r0, r0, lr
 178:	08770002 	ldmdaeq	r7!, {r1}^
	...
 184:	00000010 	andeq	r0, r0, r0, lsl r0
 188:	00000012 	andeq	r0, r0, r2, lsl r0
 18c:	007d0002 	rsbseq	r0, sp, r2
 190:	00000012 	andeq	r0, r0, r2, lsl r0
 194:	00000014 	andeq	r0, r0, r4, lsl r0
 198:	087d0002 	ldmdaeq	sp!, {r1}^
 19c:	00000014 	andeq	r0, r0, r4, lsl r0
 1a0:	00000032 	andeq	r0, r0, r2, lsr r0
 1a4:	08770002 	ldmdaeq	r7!, {r1}^
	...
 1b0:	00000034 	andeq	r0, r0, r4, lsr r0
 1b4:	00000036 	andeq	r0, r0, r6, lsr r0
 1b8:	007d0002 	rsbseq	r0, sp, r2
 1bc:	00000036 	andeq	r0, r0, r6, lsr r0
 1c0:	00000038 	andeq	r0, r0, r8, lsr r0
 1c4:	047d0002 	ldrbteq	r0, [sp], #-2
 1c8:	00000038 	andeq	r0, r0, r8, lsr r0
 1cc:	0000003a 	andeq	r0, r0, sl, lsr r0
 1d0:	107d0002 	rsbsne	r0, sp, r2
 1d4:	0000003a 	andeq	r0, r0, sl, lsr r0
 1d8:	00000056 	andeq	r0, r0, r6, asr r0
 1dc:	10770002 	rsbsne	r0, r7, r2
	...
 1ec:	00000002 	andeq	r0, r0, r2
 1f0:	007d0002 	rsbseq	r0, sp, r2
 1f4:	00000002 	andeq	r0, r0, r2
 1f8:	00000004 	andeq	r0, r0, r4
 1fc:	047d0002 	ldrbteq	r0, [sp], #-2
 200:	00000004 	andeq	r0, r0, r4
 204:	00000018 	andeq	r0, r0, r8, lsl r0
 208:	04770002 	ldrbteq	r0, [r7], #-2
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
   c:	00000000 	andeq	r0, r0, r0
  10:	08000018 	stmdaeq	r0, {r3, r4}
  14:	0000006e 	andeq	r0, r0, lr, rrx
	...
  20:	0000001c 	andeq	r0, r0, ip, lsl r0
  24:	00da0002 	sbcseq	r0, sl, r2
  28:	00040000 	andeq	r0, r4, r0
  2c:	00000000 	andeq	r0, r0, r0
  30:	08000088 	stmdaeq	r0, {r3, r7}
  34:	000000ba 	strheq	r0, [r0], -sl
	...
  40:	0000001c 	andeq	r0, r0, ip, lsl r0
  44:	024e0002 	subeq	r0, lr, #2
  48:	00040000 	andeq	r0, r4, r0
  4c:	00000000 	andeq	r0, r0, r0
  50:	08000144 	stmdaeq	r0, {r2, r6, r8}
  54:	0000002e 	andeq	r0, r0, lr, lsr #32
	...
  60:	0000001c 	andeq	r0, r0, ip, lsl r0
  64:	02e90002 	rsceq	r0, r9, #2
  68:	00040000 	andeq	r0, r4, r0
  6c:	00000000 	andeq	r0, r0, r0
  70:	08000174 	stmdaeq	r0, {r2, r4, r5, r6, r8}
  74:	0000007e 	andeq	r0, r0, lr, ror r0
	...
  80:	0000001c 	andeq	r0, r0, ip, lsl r0
  84:	037c0002 	cmneq	ip, #2
  88:	00040000 	andeq	r0, r4, r0
  8c:	00000000 	andeq	r0, r0, r0
  90:	080001f4 	stmdaeq	r0, {r2, r4, r5, r6, r7, r8}
  94:	00000056 	andeq	r0, r0, r6, asr r0
	...
  a0:	0000001c 	andeq	r0, r0, ip, lsl r0
  a4:	04490002 	strbeq	r0, [r9], #-2
  a8:	00040000 	andeq	r0, r4, r0
  ac:	00000000 	andeq	r0, r0, r0
  b0:	0800024c 	stmdaeq	r0, {r2, r3, r6, r9}
  b4:	00000018 	andeq	r0, r0, r8, lsl r0
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	0000005b 	andeq	r0, r0, fp, asr r0
   4:	003b0002 	eorseq	r0, fp, r2
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	00010000 	andeq	r0, r1, r0
  1c:	416d6c41 	cmnmi	sp, r1, asr #24
  20:	505f7463 	subspl	r7, pc, r3, ror #8
  24:	72676f72 	rsbvc	r6, r7, #456	; 0x1c8
  28:	632e6d61 	teqvs	lr, #6208	; 0x1840
  2c:	00000000 	andeq	r0, r0, r0
  30:	74616c50 	strbtvc	r6, [r1], #-3152	; 0xc50
  34:	6d726f66 	ldclvs	15, cr6, [r2, #-408]!	; 0xfffffe68
  38:	7079545f 	rsbsvc	r5, r9, pc, asr r4
  3c:	682e7365 	stmdavs	lr!, {r0, r2, r5, r6, r8, r9, ip, sp, lr}
  40:	00000000 	andeq	r0, r0, r0
  44:	02050000 	andeq	r0, r5, #0
  48:	08000018 	stmdaeq	r0, {r3, r4}
  4c:	59011103 	stmdbpl	r1, {r0, r1, r8, ip}
  50:	303e3e3e 	eorscc	r3, lr, lr, lsr lr
  54:	4ebb2f4e 	cdpmi	15, 11, cr2, cr11, cr14, {2}
  58:	0302bb2f 	movweq	fp, #11055	; 0x2b2f
  5c:	b7010100 	strlt	r0, [r1, -r0, lsl #2]
  60:	02000000 	andeq	r0, r0, #0
  64:	00006500 	andeq	r6, r0, r0, lsl #10
  68:	fb010200 	blx	40872 <vectors-0x7fbf78e>
  6c:	01000d0e 	tsteq	r0, lr, lsl #26
  70:	00010101 	andeq	r0, r1, r1, lsl #2
  74:	00010000 	andeq	r0, r1, r0
  78:	3a630100 	bcc	18c0480 <vectors-0x673fb80>
  7c:	6d72612f 	ldfvse	f6, [r2, #-188]!	; 0xffffff44
  80:	6f6f745f 	svcvs	0x006f745f
  84:	6168636c 	cmnvs	r8, ip, ror #6
  88:	6c2f6e69 	stcvs	14, cr6, [pc], #-420	; fffffeec <_stack_top+0xdfffeeec>
  8c:	672f6269 	strvs	r6, [pc, -r9, ror #4]!
  90:	2e2f6363 	cdpcs	3, 2, cr6, cr15, cr3, {3}
  94:	2e2e2f2e 	cdpcs	15, 2, cr2, cr14, cr14, {1}
  98:	6d72612f 	ldfvse	f6, [r2, #-188]!	; 0xffffff44
  9c:	6e6f6e2d 	cdpvs	14, 6, cr6, cr15, cr13, {1}
  a0:	61652d65 	cmnvs	r5, r5, ror #26
  a4:	732f6962 	teqvc	pc, #1605632	; 0x188000
  a8:	692d7379 	pushvs	{r0, r3, r4, r5, r6, r8, r9, ip, sp, lr}
  ac:	756c636e 	strbvc	r6, [ip, #-878]!	; 0x36e
  b0:	00006564 	andeq	r6, r0, r4, ror #10
  b4:	72617473 	rsbvc	r7, r1, #1929379840	; 0x73000000
  b8:	2e707574 	mrccs	5, 3, r7, cr0, cr4, {3}
  bc:	00000063 	andeq	r0, r0, r3, rrx
  c0:	64747300 	ldrbtvs	r7, [r4], #-768	; 0x300
  c4:	2e746e69 	cdpcs	14, 7, cr6, cr4, cr9, {3}
  c8:	00010068 	andeq	r0, r1, r8, rrx
  cc:	05000000 	streq	r0, [r0, #-0]
  d0:	00008802 	andeq	r8, r0, r2, lsl #16
  d4:	011d0308 	tsteq	sp, r8, lsl #6
  d8:	5a599f3e 	bpl	1667dd8 <vectors-0x6998228>
  dc:	02040200 	andeq	r0, r4, #0, 4
  e0:	0402004c 	streq	r0, [r2], #-76	; 0x4c
  e4:	02004b02 	andeq	r4, r0, #2048	; 0x800
  e8:	004b0204 	subeq	r0, fp, r4, lsl #4
  ec:	46020402 	strmi	r0, [r2], -r2, lsl #8
  f0:	01040200 	mrseq	r0, R12_usr
  f4:	51064a06 	tstpl	r6, r6, lsl #20
  f8:	02005a9f 	andeq	r5, r0, #651264	; 0x9f000
  fc:	004c0204 	subeq	r0, ip, r4, lsl #4
 100:	4b020402 	blmi	81110 <vectors-0x7f7eef0>
 104:	02040200 	andeq	r0, r4, #0, 4
 108:	04020047 	streq	r0, [r2], #-71	; 0x47
 10c:	064a0601 	strbeq	r0, [sl], -r1, lsl #12
 110:	2f4d2f50 	svccs	0x004d2f50
 114:	0001022f 	andeq	r0, r1, pc, lsr #4
 118:	00390101 	eorseq	r0, r9, r1, lsl #2
 11c:	00020000 	andeq	r0, r2, r0
 120:	0000001d 	andeq	r0, r0, sp, lsl r0
 124:	0efb0102 	cdpeq	1, 15, cr0, cr11, cr2, {0}
 128:	0101000d 	tsteq	r1, sp
 12c:	00000101 	andeq	r0, r0, r1, lsl #2
 130:	00000100 	andeq	r0, r0, r0, lsl #2
 134:	616d0001 	cmnvs	sp, r1
 138:	632e6e69 	teqvs	lr, #1680	; 0x690
 13c:	00000000 	andeq	r0, r0, r0
 140:	02050000 	andeq	r0, r5, #0
 144:	08000144 	stmdaeq	r0, {r2, r6, r8}
 148:	3f010e03 	svccc	0x00010e03
 14c:	3e4c3330 	mcrcc	3, 2, r3, cr12, cr0, {1}
 150:	01026732 	tsteq	r2, r2, lsr r7
 154:	54010100 	strpl	r0, [r1], #-256	; 0x100
 158:	02000000 	andeq	r0, r0, #0
 15c:	00003900 	andeq	r3, r0, r0, lsl #18
 160:	fb010200 	blx	4096a <vectors-0x7fbf696>
 164:	01000d0e 	tsteq	r0, lr, lsl #26
 168:	00010101 	andeq	r0, r1, r1, lsl #2
 16c:	00010000 	andeq	r0, r1, r0
 170:	47000100 	strmi	r0, [r0, -r0, lsl #2]
 174:	5f4f4950 	svcpl	0x004f4950
 178:	676f7250 			; <UNDEFINED> instruction: 0x676f7250
 17c:	2e6d6172 	mcrcs	1, 3, r6, cr13, cr2, {3}
 180:	00000063 	andeq	r0, r0, r3, rrx
 184:	616c5000 	cmnvs	ip, r0
 188:	726f6674 	rsbvc	r6, pc, #116, 12	; 0x7400000
 18c:	79545f6d 	ldmdbvc	r4, {r0, r2, r3, r5, r6, r8, r9, sl, fp, ip, lr}^
 190:	2e736570 	mrccs	5, 3, r6, cr3, cr0, {3}
 194:	00000068 	andeq	r0, r0, r8, rrx
 198:	05000000 	streq	r0, [r0, #-0]
 19c:	00017402 	andeq	r7, r1, r2, lsl #8
 1a0:	01100308 	tsteq	r0, r8, lsl #6
 1a4:	9fbbbb2f 	svcls	0x00bbbb2f
 1a8:	0302bbbb 	movweq	fp, #11195	; 0x2bbb
 1ac:	66010100 	strvs	r0, [r1], -r0, lsl #2
 1b0:	02000000 	andeq	r0, r0, #0
 1b4:	00003b00 	andeq	r3, r0, r0, lsl #22
 1b8:	fb010200 	blx	409c2 <vectors-0x7fbf63e>
 1bc:	01000d0e 	tsteq	r0, lr, lsl #26
 1c0:	00010101 	andeq	r0, r1, r1, lsl #2
 1c4:	00010000 	andeq	r0, r1, r0
 1c8:	41000100 	mrsmi	r0, (UNDEF: 16)
 1cc:	6f4d6d6c 	svcvs	0x004d6d6c
 1d0:	72505f6e 	subsvc	r5, r0, #440	; 0x1b8
 1d4:	6172676f 	cmnvs	r2, pc, ror #14
 1d8:	00632e6d 	rsbeq	r2, r3, sp, ror #28
 1dc:	50000000 	andpl	r0, r0, r0
 1e0:	6674616c 	ldrbtvs	r6, [r4], -ip, ror #2
 1e4:	5f6d726f 	svcpl	0x006d726f
 1e8:	65707954 	ldrbvs	r7, [r0, #-2388]!	; 0x954
 1ec:	00682e73 	rsbeq	r2, r8, r3, ror lr
 1f0:	00000000 	andeq	r0, r0, r0
 1f4:	f4020500 	vst3.8	{d0,d2,d4}, [r2], r0
 1f8:	03080001 	movweq	r0, #32769	; 0x8001
 1fc:	4b30010f 	blmi	c00640 <vectors-0x73ff9c0>
 200:	684c3032 	stmdavs	ip, {r1, r4, r5, ip, sp}^
 204:	004b324b 	subeq	r3, fp, fp, asr #4
 208:	06020402 	streq	r0, [r2], -r2, lsl #8
 20c:	04020020 	streq	r0, [r2], #-32
 210:	3d064a01 	vstrcc	s8, [r6, #-4]
 214:	01000502 	tsteq	r0, r2, lsl #10
 218:	00005201 	andeq	r5, r0, r1, lsl #4
 21c:	3b000200 	blcc	a24 <vectors-0x7fff5dc>
 220:	02000000 	andeq	r0, r0, #0
 224:	0d0efb01 	vstreq	d15, [lr, #-4]
 228:	01010100 	mrseq	r0, (UNDEF: 17)
 22c:	00000001 	andeq	r0, r0, r1
 230:	01000001 	tsteq	r0, r1
 234:	65725000 	ldrbvs	r5, [r2, #-0]!
 238:	5f6e6553 	svcpl	0x006e6553
 23c:	676f7250 			; <UNDEFINED> instruction: 0x676f7250
 240:	2e6d6172 	mcrcs	1, 3, r6, cr13, cr2, {3}
 244:	00000063 	andeq	r0, r0, r3, rrx
 248:	616c5000 	cmnvs	ip, r0
 24c:	726f6674 	rsbvc	r6, pc, #116, 12	; 0x7400000
 250:	79545f6d 	ldmdbvc	r4, {r0, r2, r3, r5, r6, r8, r9, sl, fp, ip, lr}^
 254:	2e736570 	mrccs	5, 3, r6, cr3, cr0, {3}
 258:	00000068 	andeq	r0, r0, r8, rrx
 25c:	05000000 	streq	r0, [r0, #-0]
 260:	00024c02 	andeq	r4, r2, r2, lsl #24
 264:	01100308 	tsteq	r0, r8, lsl #6
 268:	0402672f 	streq	r6, [r2], #-1839	; 0x72f
 26c:	Address 0x0000026c is out of bounds.


Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	676e6f6c 	strbvs	r6, [lr, -ip, ror #30]!
   4:	6e6f6c20 	cdpvs	12, 6, cr6, cr15, cr0, {1}
   8:	6e692067 	cdpvs	0, 6, cr2, cr9, cr7, {3}
   c:	74530074 	ldrbvc	r0, [r3], #-116	; 0x74
  10:	5f747261 	svcpl	0x00747261
  14:	72616c41 	rsbvc	r6, r1, #16640	; 0x4100
  18:	4e47006d 	cdpmi	0, 4, cr0, cr7, cr13, {3}
  1c:	20432055 	subcs	r2, r3, r5, asr r0
  20:	2e372e34 	mrccs	14, 1, r2, cr7, cr4, {1}
  24:	6f6c0032 	svcvs	0x006c0032
  28:	6c20676e 	stcvs	7, cr6, [r0], #-440	; 0xfffffe48
  2c:	20676e6f 	rsbcs	r6, r7, pc, ror #28
  30:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
  34:	64656e67 	strbtvs	r6, [r5], #-3687	; 0xe67
  38:	746e6920 	strbtvc	r6, [lr], #-2336	; 0x920
  3c:	6f6c6600 	svcvs	0x006c6600
  40:	75007461 	strvc	r7, [r0, #-1121]	; 0x461
  44:	38746e69 	ldmdacc	r4!, {r0, r3, r5, r6, r9, sl, fp, sp, lr}^
  48:	7500745f 	strvc	r7, [r0, #-1119]	; 0x45f
  4c:	6769736e 	strbvs	r7, [r9, -lr, ror #6]!
  50:	2064656e 	rsbcs	r6, r4, lr, ror #10
  54:	72616863 	rsbvc	r6, r1, #6488064	; 0x630000
  58:	5c3a4700 	ldcpl	7, cr4, [sl], #-0
  5c:	65626d45 	strbvs	r6, [r2, #-3397]!	; 0xd45
  60:	64656464 	strbtvs	r6, [r5], #-1124	; 0x464
  64:	72654b5c 	rsbvc	r4, r5, #92, 22	; 0x17000
  68:	73656c6f 	cmnvc	r5, #28416	; 0x6f00
  6c:	69687320 	stmdbvs	r8!, {r5, r8, r9, ip, sp, lr}^
  70:	64756f6e 	ldrbtvs	r6, [r5], #-3950	; 0xf6e
  74:	6e555c61 	cdpvs	12, 5, cr5, cr5, cr1, {3}
  78:	20357469 	eorscs	r7, r5, r9, ror #8
  7c:	73726946 	cmnvc	r2, #1146880	; 0x118000
  80:	69465f74 	stmdbvs	r6, {r2, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
  84:	5c6c616e 	stfple	f6, [ip], #-440	; 0xfffffe48
  88:	53524946 	cmppl	r2, #1146880	; 0x118000
  8c:	45545f54 	ldrbmi	r5, [r4, #-3924]	; 0xf54
  90:	705f4d52 	subsvc	r4, pc, r2, asr sp	; <UNPREDICTABLE>
  94:	656a6f72 	strbvs	r6, [sl, #-3954]!	; 0xf72
  98:	5c317463 	cfldrspl	mvf7, [r1], #-396	; 0xfffffe74
  9c:	53544f43 	cmppl	r4, #268	; 0x10c
  a0:	6e697500 	cdpvs	5, 6, cr7, cr9, cr0, {0}
  a4:	5f323374 	svcpl	0x00323374
  a8:	6f640074 	svcvs	0x00640074
  ac:	656c6275 	strbvs	r6, [ip, #-629]!	; 0x275
  b0:	6f687300 	svcvs	0x00687300
  b4:	75207472 	strvc	r7, [r0, #-1138]!	; 0x472
  b8:	6769736e 	strbvs	r7, [r9, -lr, ror #6]!
  bc:	2064656e 	rsbcs	r6, r4, lr, ror #10
  c0:	00746e69 	rsbseq	r6, r4, r9, ror #28
  c4:	416d6c41 	cmnmi	sp, r1, asr #24
  c8:	505f7463 	subspl	r7, pc, r3, ror #8
  cc:	72676f72 	rsbvc	r6, r7, #456	; 0x1c8
  d0:	632e6d61 	teqvs	lr, #6208	; 0x1840
  d4:	6f687300 	svcvs	0x00687300
  d8:	69207472 	stmdbvs	r0!, {r1, r4, r5, r6, sl, ip, sp, lr}
  dc:	5300746e 	movwpl	r7, #1134	; 0x46e
  e0:	5f706f74 	svcpl	0x00706f74
  e4:	72616c41 	rsbvc	r6, r1, #16640	; 0x4100
  e8:	6553006d 	ldrbvs	r0, [r3, #-109]	; 0x6d
  ec:	6c415f74 	mcrrvs	15, 7, r5, r1, cr4
  f0:	5f6d7261 	svcpl	0x006d7261
  f4:	75746341 	ldrbvc	r6, [r4, #-833]!	; 0x341
  f8:	726f7461 	rsbvc	r7, pc, #1627389952	; 0x61000000
  fc:	61747300 	cmnvs	r4, r0, lsl #6
 100:	70757472 	rsbsvc	r7, r5, r2, ror r4
 104:	5f00632e 	svcpl	0x0000632e
 108:	73625f53 	cmnvc	r2, #332	; 0x14c
 10c:	61640073 	smcvs	16387	; 0x4003
 110:	735f6174 	cmpvc	pc, #116, 2
 114:	00657a69 	rsbeq	r7, r5, r9, ror #20
 118:	63735f70 	cmnvs	r3, #112, 30	; 0x1c0
 11c:	735f0072 	cmpvc	pc, #114	; 0x72
 120:	6b636174 	blvs	18d86f8 <vectors-0x6727908>
 124:	706f745f 	rsbvc	r7, pc, pc, asr r4	; <UNPREDICTABLE>
 128:	63657600 	cmnvs	r5, #0, 12
 12c:	73726f74 	cmnvc	r2, #116, 30	; 0x1d0
 130:	5f455f00 	svcpl	0x00455f00
 134:	00737362 	rsbseq	r7, r3, r2, ror #6
 138:	645f455f 	ldrbvs	r4, [pc], #-1375	; 140 <vectors-0x7fffec0>
 13c:	00617461 	rsbeq	r7, r1, r1, ror #8
 140:	745f455f 	ldrbvc	r4, [pc], #-1375	; 148 <vectors-0x7fffeb8>
 144:	00747865 	rsbseq	r7, r4, r5, ror #16
 148:	73645f70 	cmnvc	r4, #112, 30	; 0x1c0
 14c:	65640074 	strbvs	r0, [r4, #-116]!	; 0x74
 150:	6c756166 	ldfvse	f6, [r5], #-408	; 0xfffffe68
 154:	61685f74 	smcvs	34292	; 0x85f4
 158:	656c646e 	strbvs	r6, [ip, #-1134]!	; 0x46e
 15c:	73620072 	cmnvc	r2, #114	; 0x72
 160:	69735f73 	ldmdbvs	r3!, {r0, r1, r4, r5, r6, r8, r9, sl, fp, ip, lr}^
 164:	7200657a 	andvc	r6, r0, #511705088	; 0x1e800000
 168:	74657365 	strbtvc	r7, [r5], #-869	; 0x365
 16c:	6e61685f 	mcrvs	8, 3, r6, cr1, cr15, {2}
 170:	72656c64 	rsbvc	r6, r5, #100, 24	; 0x6400
 174:	7a697300 	bvc	1a5cd7c <vectors-0x65a3284>
 178:	70797465 	rsbsvc	r7, r9, r5, ror #8
 17c:	535f0065 	cmppl	pc, #101	; 0x65
 180:	7461645f 	strbtvc	r6, [r1], #-1119	; 0x45f
 184:	616d0061 	cmnvs	sp, r1, rrx
 188:	632e6e69 	teqvs	lr, #1680	; 0x690
 18c:	69616d00 	stmdbvs	r1!, {r8, sl, fp, sp, lr}^
 190:	7250006e 	subsvc	r0, r0, #110	; 0x6e
 194:	6c615665 	stclvs	6, cr5, [r1], #-404	; 0xfffffe6c
 198:	49504700 	ldmdbmi	r0, {r8, r9, sl, lr}^
 19c:	72505f4f 	subsvc	r5, r0, #316	; 0x13c
 1a0:	6172676f 	cmnvs	r2, pc, ror #14
 1a4:	00632e6d 	rsbeq	r2, r3, sp, ror #28
 1a8:	4f495047 	svcmi	0x00495047
 1ac:	494e495f 	stmdbmi	lr, {r0, r1, r2, r3, r4, r6, r8, fp, lr}^
 1b0:	4c414954 	mcrrmi	9, 5, r4, r1, cr4
 1b4:	54415a49 	strbpl	r5, [r1], #-2633	; 0xa49
 1b8:	004e4f49 	subeq	r4, lr, r9, asr #30
 1bc:	68676948 	stmdavs	r7!, {r3, r6, r8, fp, sp, lr}^
 1c0:	6572505f 	ldrbvs	r5, [r2, #-95]!	; 0x5f
 1c4:	72757373 	rsbsvc	r7, r5, #-872415231	; 0xcc000001
 1c8:	65445f65 	strbvs	r5, [r4, #-3941]	; 0xf65
 1cc:	74636574 	strbtvc	r6, [r3], #-1396	; 0x574
 1d0:	6e006465 	cdpvs	4, 0, cr6, cr0, cr5, {3}
 1d4:	6e756f43 	cdpvs	15, 7, cr6, cr5, cr3, {2}
 1d8:	4c410074 	mcrrmi	0, 7, r0, r1, cr4
 1dc:	5f4d5241 	svcpl	0x004d5241
 1e0:	54494e49 	strbpl	r4, [r9], #-3657	; 0xe49
 1e4:	494c4149 	stmdbmi	ip, {r0, r3, r6, r8, lr}^
 1e8:	4954415a 	ldmdbmi	r4, {r1, r3, r4, r6, r8, lr}^
 1ec:	41004e4f 	tstmi	r0, pc, asr #28
 1f0:	6f4d6d6c 	svcvs	0x004d6d6c
 1f4:	72505f6e 	subsvc	r5, r0, #440	; 0x1b8
 1f8:	6172676f 	cmnvs	r2, pc, ror #14
 1fc:	00632e6d 	rsbeq	r2, r3, sp, ror #28
 200:	616c6544 	cmnvs	ip, r4, asr #10
 204:	72500079 	subsvc	r0, r0, #121	; 0x79
 208:	6e655365 	cdpvs	3, 6, cr5, cr5, cr5, {3}
 20c:	6f72505f 	svcvs	0x0072505f
 210:	6d617267 	sfmvs	f7, 2, [r1, #-412]!	; 0xfffffe64
 214:	4700632e 	strmi	r6, [r0, -lr, lsr #6]
 218:	505f7465 	subspl	r7, pc, r5, ror #8
 21c:	73736572 	cmnvc	r3, #478150656	; 0x1c800000
 220:	5f657275 	svcpl	0x00657275
 224:	006c6156 	rsbeq	r6, ip, r6, asr r1

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <vectors-0x6f2f2dc>
   4:	4e472820 	cdpmi	8, 4, cr2, cr7, cr0, {1}
   8:	34202955 	strtcc	r2, [r0], #-2389	; 0x955
   c:	322e372e 	eorcc	r3, lr, #12058624	; 0xb80000
	...

Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00003241 	andeq	r3, r0, r1, asr #4
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000028 	andeq	r0, r0, r8, lsr #32
  10:	726f4305 	rsbvc	r4, pc, #335544320	; 0x14000000
  14:	2d786574 	cfldr64cs	mvdx6, [r8, #-464]!	; 0xfffffe30
  18:	0600344d 	streq	r3, [r0], -sp, asr #8
  1c:	094d070d 	stmdbeq	sp, {r0, r2, r3, r8, r9, sl}^
  20:	14041202 	strne	r1, [r4], #-514	; 0x202
  24:	17011501 	strne	r1, [r1, -r1, lsl #10]
  28:	19011803 	stmdbne	r1, {r0, r1, fp, ip}
  2c:	1e011a01 	vmlane.f32	s2, s2, s2
  30:	Address 0x00000030 is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	0000001c 	andeq	r0, r0, ip, lsl r0
  14:	00000000 	andeq	r0, r0, r0
  18:	08000018 	stmdaeq	r0, {r3, r4}
  1c:	00000028 	andeq	r0, r0, r8, lsr #32
  20:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  24:	41018e02 	tstmi	r1, r2, lsl #28
  28:	0d41100e 	stcleq	0, cr1, [r1, #-56]	; 0xffffffc8
  2c:	00000007 	andeq	r0, r0, r7
  30:	00000014 	andeq	r0, r0, r4, lsl r0
  34:	00000000 	andeq	r0, r0, r0
  38:	08000040 	stmdaeq	r0, {r6}
  3c:	00000022 	andeq	r0, r0, r2, lsr #32
  40:	87040e41 	strhi	r0, [r4, -r1, asr #28]
  44:	070d4101 	streq	r4, [sp, -r1, lsl #2]
  48:	00000014 	andeq	r0, r0, r4, lsl r0
  4c:	00000000 	andeq	r0, r0, r0
  50:	08000064 	stmdaeq	r0, {r2, r5, r6}
  54:	00000022 	andeq	r0, r0, r2, lsr #32
  58:	87040e41 	strhi	r0, [r4, -r1, asr #28]
  5c:	070d4101 	streq	r4, [sp, -r1, lsl #2]
  60:	0000000c 	andeq	r0, r0, ip
  64:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  68:	7c020001 	stcvc	0, cr0, [r2], {1}
  6c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  70:	0000001c 	andeq	r0, r0, ip, lsl r0
  74:	00000060 	andeq	r0, r0, r0, rrx
  78:	08000088 	stmdaeq	r0, {r3, r7}
  7c:	000000b0 	strheq	r0, [r0], -r0	; <UNPREDICTABLE>
  80:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  84:	41018e02 	tstmi	r1, r2, lsl #28
  88:	0d41200e 	stcleq	0, cr2, [r1, #-56]	; 0xffffffc8
  8c:	00000007 	andeq	r0, r0, r7
  90:	00000018 	andeq	r0, r0, r8, lsl r0
  94:	00000060 	andeq	r0, r0, r0, rrx
  98:	08000138 	stmdaeq	r0, {r3, r4, r5, r8}
  9c:	0000000a 	andeq	r0, r0, sl
  a0:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  a4:	41018e02 	tstmi	r1, r2, lsl #28
  a8:	0000070d 	andeq	r0, r0, sp, lsl #14
  ac:	0000000c 	andeq	r0, r0, ip
  b0:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  b4:	7c020001 	stcvc	0, cr0, [r2], {1}
  b8:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  bc:	0000001c 	andeq	r0, r0, ip, lsl r0
  c0:	000000ac 	andeq	r0, r0, ip, lsr #1
  c4:	08000144 	stmdaeq	r0, {r2, r6, r8}
  c8:	0000002e 	andeq	r0, r0, lr, lsr #32
  cc:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  d0:	41018e02 	tstmi	r1, r2, lsl #28
  d4:	0d41100e 	stcleq	0, cr1, [r1, #-56]	; 0xffffffc8
  d8:	00000007 	andeq	r0, r0, r7
  dc:	0000000c 	andeq	r0, r0, ip
  e0:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  e4:	7c020001 	stcvc	0, cr0, [r2], {1}
  e8:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  ec:	00000014 	andeq	r0, r0, r4, lsl r0
  f0:	000000dc 	ldrdeq	r0, [r0], -ip
  f4:	08000174 	stmdaeq	r0, {r2, r4, r5, r6, r8}
  f8:	0000007e 	andeq	r0, r0, lr, ror r0
  fc:	87040e41 	strhi	r0, [r4, -r1, asr #28]
 100:	070d4101 	streq	r4, [sp, -r1, lsl #2]
 104:	0000000c 	andeq	r0, r0, ip
 108:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 10c:	7c020001 	stcvc	0, cr0, [r2], {1}
 110:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 114:	00000018 	andeq	r0, r0, r8, lsl r0
 118:	00000104 	andeq	r0, r0, r4, lsl #2
 11c:	080001f4 	stmdaeq	r0, {r2, r4, r5, r6, r7, r8}
 120:	0000000e 	andeq	r0, r0, lr
 124:	87080e41 	strhi	r0, [r8, -r1, asr #28]
 128:	41018e02 	tstmi	r1, r2, lsl #28
 12c:	0000070d 	andeq	r0, r0, sp, lsl #14
 130:	00000018 	andeq	r0, r0, r8, lsl r0
 134:	00000104 	andeq	r0, r0, r4, lsl #2
 138:	08000204 	stmdaeq	r0, {r2, r9}
 13c:	00000022 	andeq	r0, r0, r2, lsr #32
 140:	87080e41 	strhi	r0, [r8, -r1, asr #28]
 144:	41018e02 	tstmi	r1, r2, lsl #28
 148:	0000070d 	andeq	r0, r0, sp, lsl #14
 14c:	00000018 	andeq	r0, r0, r8, lsl r0
 150:	00000104 	andeq	r0, r0, r4, lsl #2
 154:	08000228 	stmdaeq	r0, {r3, r5, r9}
 158:	00000022 	andeq	r0, r0, r2, lsr #32
 15c:	87040e41 	strhi	r0, [r4, -r1, asr #28]
 160:	100e4101 	andne	r4, lr, r1, lsl #2
 164:	00070d41 	andeq	r0, r7, r1, asr #26
 168:	0000000c 	andeq	r0, r0, ip
 16c:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 170:	7c020001 	stcvc	0, cr0, [r2], {1}
 174:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 178:	00000014 	andeq	r0, r0, r4, lsl r0
 17c:	00000168 	andeq	r0, r0, r8, ror #2
 180:	0800024c 	stmdaeq	r0, {r2, r3, r6, r9}
 184:	00000018 	andeq	r0, r0, r8, lsl r0
 188:	87040e41 	strhi	r0, [r4, -r1, asr #28]
 18c:	070d4101 	streq	r4, [sp, -r1, lsl #2]
