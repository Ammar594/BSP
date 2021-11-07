
build/kernel.elf:     file format elf32-littlearm
architecture: armv7, flags 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
start address 0x00008000

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .init         00000064  00008000  00008000  00008000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .text         0000096c  00008064  00008064  00008064  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .rodata.str1.4 00000334  000089d0  000089d0  000089d0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .text.startup 00000008  00008d04  00008d04  00008d04  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  4 .bss          00000004  00008d0c  00008d0c  00008d0c  2**2
                  ALLOC
  5 .debug_info   00000d4f  00000000  00000000  00008d0c  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
  6 .debug_abbrev 00000476  00000000  00000000  00009a5b  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
  7 .debug_loc    00001031  00000000  00000000  00009ed1  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
  8 .debug_aranges 000000a0  00000000  00000000  0000af08  2**3
                  CONTENTS, READONLY, DEBUGGING, OCTETS
  9 .debug_ranges 00000358  00000000  00000000  0000afa8  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 10 .debug_line   00000b8b  00000000  00000000  0000b300  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 11 .debug_str    0000021a  00000000  00000000  0000be8b  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 12 .comment      00000012  00000000  00000000  0000c0a5  2**0
                  CONTENTS, READONLY
 13 .ARM.attributes 00000033  00000000  00000000  0000c0b7  2**0
                  CONTENTS, READONLY
 14 .debug_frame  00000110  00000000  00000000  0000c0ec  2**2
                  CONTENTS, READONLY, DEBUGGING, OCTETS

Disassembly of section .init:

00008000 <_start>:
    8000:	e10f0000 	mrs	r0, CPSR
    8004:	e200001f 	and	r0, r0, #31
    8008:	e3a0101a 	mov	r1, #26
    800c:	e1500001 	cmp	r0, r1
    8010:	0a00000b 	beq	8044 <_exitHyper>

00008014 <_checkCores>:
    8014:	ee100fb0 	mrc	15, 0, r0, cr0, cr0, {5}
    8018:	e3100003 	tst	r0, #3
    801c:	1a000006 	bne	803c <_parkCore>

00008020 <_enableAlignCheck>:
    8020:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
    8024:	e3800002 	orr	r0, r0, #2
    8028:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}

0000802c <_bsprak>:
    802c:	e3a0d802 	mov	sp, #131072	; 0x20000
    8030:	eb000011 	bl	807c <start_kernel>
    8034:	e320f003 	wfi
    8038:	eafffffd 	b	8034 <_bsprak+0x8>

0000803c <_parkCore>:
    803c:	f10c00c0 	cpsid	if
    8040:	eafffffb 	b	8034 <_bsprak+0x8>

00008044 <_exitHyper>:
    8044:	e59fe014 	ldr	lr, [pc, #20]	; 8060 <_exitHyper+0x1c>
    8048:	e12ef30e 	msr	ELR_hyp, lr
    804c:	e10f0000 	mrs	r0, CPSR
    8050:	e3c0001f 	bic	r0, r0, #31
    8054:	e3800013 	orr	r0, r0, #19
    8058:	e16ef300 	msr	SPSR_hyp, r0
    805c:	e160006e 	eret
    8060:	00008014 	.word	0x00008014

Disassembly of section .text:

00008064 <increment_counter>:
    8064:	e3083d0c 	movw	r3, #36108	; 0x8d0c
    8068:	e3403000 	movt	r3, #0
    806c:	e5932000 	ldr	r2, [r3]
    8070:	e2822001 	add	r2, r2, #1
    8074:	e5832000 	str	r2, [r3]
    8078:	e12fff1e 	bx	lr

0000807c <start_kernel>:
    807c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    8080:	e24dd00c 	sub	sp, sp, #12
    8084:	e3084c88 	movw	r4, #35976	; 0x8c88
    8088:	eb00021f 	bl	890c <uart_init>
    808c:	e3404000 	movt	r4, #0
    8090:	e30809d0 	movw	r0, #35280	; 0x89d0
    8094:	e3400000 	movt	r0, #0
    8098:	eb000055 	bl	81f4 <kprintf>
    809c:	e30809e0 	movw	r0, #35296	; 0x89e0
    80a0:	e3a0200b 	mov	r2, #11
    80a4:	e3400000 	movt	r0, #0
    80a8:	e30014d2 	movw	r1, #1234	; 0x4d2
    80ac:	eb000050 	bl	81f4 <kprintf>
    80b0:	e3080a08 	movw	r0, #35336	; 0x8a08
    80b4:	e3a0300a 	mov	r3, #10
    80b8:	e3400000 	movt	r0, #0
    80bc:	e3a0103c 	mov	r1, #60	; 0x3c
    80c0:	e58d3004 	str	r3, [sp, #4]
    80c4:	eb00004a 	bl	81f4 <kprintf>
    80c8:	e3080a24 	movw	r0, #35364	; 0x8a24
    80cc:	e3a0103c 	mov	r1, #60	; 0x3c
    80d0:	e3400000 	movt	r0, #0
    80d4:	eb000046 	bl	81f4 <kprintf>
    80d8:	e3080a54 	movw	r0, #35412	; 0x8a54
    80dc:	e3a0103c 	mov	r1, #60	; 0x3c
    80e0:	e3400000 	movt	r0, #0
    80e4:	eb000042 	bl	81f4 <kprintf>
    80e8:	e3080a88 	movw	r0, #35464	; 0x8a88
    80ec:	e3e01f53 	mvn	r1, #332	; 0x14c
    80f0:	e3400000 	movt	r0, #0
    80f4:	eb00003e 	bl	81f4 <kprintf>
    80f8:	e3080aa4 	movw	r0, #35492	; 0x8aa4
    80fc:	e3e01f53 	mvn	r1, #332	; 0x14c
    8100:	e3400000 	movt	r0, #0
    8104:	eb00003a 	bl	81f4 <kprintf>
    8108:	e3080ad4 	movw	r0, #35540	; 0x8ad4
    810c:	e3e01f53 	mvn	r1, #332	; 0x14c
    8110:	e3400000 	movt	r0, #0
    8114:	eb000036 	bl	81f4 <kprintf>
    8118:	e3080aa4 	movw	r0, #35492	; 0x8aa4
    811c:	e3a01000 	mov	r1, #0
    8120:	e3400000 	movt	r0, #0
    8124:	eb000032 	bl	81f4 <kprintf>
    8128:	e3080ad4 	movw	r0, #35540	; 0x8ad4
    812c:	e3a01000 	mov	r1, #0
    8130:	e3400000 	movt	r0, #0
    8134:	eb00002e 	bl	81f4 <kprintf>
    8138:	e3080b04 	movw	r0, #35588	; 0x8b04
    813c:	e3a01003 	mov	r1, #3
    8140:	e3400000 	movt	r0, #0
    8144:	eb00002a 	bl	81f4 <kprintf>
    8148:	e3080b20 	movw	r0, #35616	; 0x8b20
    814c:	e28d1004 	add	r1, sp, #4
    8150:	e3400000 	movt	r0, #0
    8154:	eb000026 	bl	81f4 <kprintf>
    8158:	e3080b38 	movw	r0, #35640	; 0x8b38
    815c:	e28d1004 	add	r1, sp, #4
    8160:	e3400000 	movt	r0, #0
    8164:	eb000022 	bl	81f4 <kprintf>
    8168:	e3081b54 	movw	r1, #35668	; 0x8b54
    816c:	e3080b68 	movw	r0, #35688	; 0x8b68
    8170:	e3401000 	movt	r1, #0
    8174:	e3400000 	movt	r0, #0
    8178:	eb00001d 	bl	81f4 <kprintf>
    817c:	e3080b80 	movw	r0, #35712	; 0x8b80
    8180:	e3a01057 	mov	r1, #87	; 0x57
    8184:	e3400000 	movt	r0, #0
    8188:	eb000019 	bl	81f4 <kprintf>
    818c:	e3080b9c 	movw	r0, #35740	; 0x8b9c
    8190:	e3a01000 	mov	r1, #0
    8194:	e3400000 	movt	r0, #0
    8198:	eb000015 	bl	81f4 <kprintf>
    819c:	e3080bb0 	movw	r0, #35760	; 0x8bb0
    81a0:	e3a01000 	mov	r1, #0
    81a4:	e3400000 	movt	r0, #0
    81a8:	eb000011 	bl	81f4 <kprintf>
    81ac:	e3080bd0 	movw	r0, #35792	; 0x8bd0
    81b0:	e3a01000 	mov	r1, #0
    81b4:	e3400000 	movt	r0, #0
    81b8:	eb00000d 	bl	81f4 <kprintf>
    81bc:	e3080c04 	movw	r0, #35844	; 0x8c04
    81c0:	e3a010ff 	mov	r1, #255	; 0xff
    81c4:	e3400000 	movt	r0, #0
    81c8:	eb000009 	bl	81f4 <kprintf>
    81cc:	e3080c40 	movw	r0, #35904	; 0x8c40
    81d0:	e3400000 	movt	r0, #0
    81d4:	eb000006 	bl	81f4 <kprintf>
    81d8:	eb0001e1 	bl	8964 <uart_getc>
    81dc:	e1a03000 	mov	r3, r0
    81e0:	e1a00004 	mov	r0, r4
    81e4:	e1a02003 	mov	r2, r3
    81e8:	e1a01003 	mov	r1, r3
    81ec:	eb000000 	bl	81f4 <kprintf>
    81f0:	eafffff8 	b	81d8 <start_kernel+0x15c>

000081f4 <kprintf>:
    81f4:	e92d000f 	push	{r0, r1, r2, r3}
    81f8:	e92d4ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
    81fc:	e24ddf8d 	sub	sp, sp, #564	; 0x234
    8200:	e28d3f97 	add	r3, sp, #604	; 0x25c
    8204:	e59d2258 	ldr	r2, [sp, #600]	; 0x258
    8208:	e58d300c 	str	r3, [sp, #12]
    820c:	e5d21000 	ldrb	r1, [r2]
    8210:	e3510000 	cmp	r1, #0
    8214:	0a0001a4 	beq	88ac <kprintf+0x6b8>
    8218:	e3a0b000 	mov	fp, #0
    821c:	e28de010 	add	lr, sp, #16
    8220:	e58db000 	str	fp, [sp]
    8224:	e30c7ccd 	movw	r7, #52429	; 0xcccd
    8228:	e34c7ccc 	movt	r7, #52428	; 0xcccc
    822c:	e1a0400b 	mov	r4, fp
    8230:	e28e600a 	add	r6, lr, #10
    8234:	ea000007 	b	8258 <kprintf+0x64>
    8238:	e28d2e23 	add	r2, sp, #560	; 0x230
    823c:	e0820004 	add	r0, r2, r4
    8240:	e1a02003 	mov	r2, r3
    8244:	e2844001 	add	r4, r4, #1
    8248:	e5401200 	strb	r1, [r0, #-512]	; 0xfffffe00
    824c:	e1a0100c 	mov	r1, ip
    8250:	e3510000 	cmp	r1, #0
    8254:	0a00002f 	beq	8318 <kprintf+0x124>
    8258:	e1a03002 	mov	r3, r2
    825c:	e3510025 	cmp	r1, #37	; 0x25
    8260:	e5f3c001 	ldrb	ip, [r3, #1]!
    8264:	1afffff3 	bne	8238 <kprintf+0x44>
    8268:	e35c0073 	cmp	ip, #115	; 0x73
    826c:	0a00006f 	beq	8430 <kprintf+0x23c>
    8270:	e35c0025 	cmp	ip, #37	; 0x25
    8274:	0a000066 	beq	8414 <kprintf+0x220>
    8278:	e35c0063 	cmp	ip, #99	; 0x63
    827c:	0a0000a5 	beq	8518 <kprintf+0x324>
    8280:	e35c0030 	cmp	ip, #48	; 0x30
    8284:	0a00002b 	beq	8338 <kprintf+0x144>
    8288:	e35c0038 	cmp	ip, #56	; 0x38
    828c:	e28d5030 	add	r5, sp, #48	; 0x30
    8290:	02823002 	addeq	r3, r2, #2
    8294:	05d2c002 	ldrbeq	ip, [r2, #2]
    8298:	03a02001 	moveq	r2, #1
    829c:	058d2000 	streq	r2, [sp]
    82a0:	e35c0070 	cmp	ip, #112	; 0x70
    82a4:	e2832001 	add	r2, r3, #1
    82a8:	0a00002c 	beq	8360 <kprintf+0x16c>
    82ac:	e35c0069 	cmp	ip, #105	; 0x69
    82b0:	0a0000a3 	beq	8544 <kprintf+0x350>
    82b4:	e35c0075 	cmp	ip, #117	; 0x75
    82b8:	0a0000dc 	beq	8630 <kprintf+0x43c>
    82bc:	e35c0078 	cmp	ip, #120	; 0x78
    82c0:	0a00006f 	beq	8484 <kprintf+0x290>
    82c4:	e59f163c 	ldr	r1, [pc, #1596]	; 8908 <kprintf+0x714>
    82c8:	e2440001 	sub	r0, r4, #1
    82cc:	e0855000 	add	r5, r5, r0
    82d0:	e3a00045 	mov	r0, #69	; 0x45
    82d4:	e2818016 	add	r8, r1, #22
    82d8:	ea000000 	b	82e0 <kprintf+0xec>
    82dc:	e4d10001 	ldrb	r0, [r1], #1
    82e0:	e1510008 	cmp	r1, r8
    82e4:	e5e50001 	strb	r0, [r5, #1]!
    82e8:	1afffffb 	bne	82dc <kprintf+0xe8>
    82ec:	e5d31001 	ldrb	r1, [r3, #1]
    82f0:	e28d0e23 	add	r0, sp, #560	; 0x230
    82f4:	e2843018 	add	r3, r4, #24
    82f8:	e3a05025 	mov	r5, #37	; 0x25
    82fc:	e0803003 	add	r3, r0, r3
    8300:	e3510000 	cmp	r1, #0
    8304:	e0800004 	add	r0, r0, r4
    8308:	e2844019 	add	r4, r4, #25
    830c:	e54051e9 	strb	r5, [r0, #-489]	; 0xfffffe17
    8310:	e543c200 	strb	ip, [r3, #-512]	; 0xfffffe00
    8314:	1affffcf 	bne	8258 <kprintf+0x64>
    8318:	e1a01004 	mov	r1, r4
    831c:	e28d0030 	add	r0, sp, #48	; 0x30
    8320:	eb000199 	bl	898c <uart_write>
    8324:	e1a00004 	mov	r0, r4
    8328:	e28ddf8d 	add	sp, sp, #564	; 0x234
    832c:	e8bd4ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
    8330:	e28dd010 	add	sp, sp, #16
    8334:	e12fff1e 	bx	lr
    8338:	e5d23002 	ldrb	r3, [r2, #2]
    833c:	e3530038 	cmp	r3, #56	; 0x38
    8340:	1a000154 	bne	8898 <kprintf+0x6a4>
    8344:	e5d2c003 	ldrb	ip, [r2, #3]
    8348:	e2823003 	add	r3, r2, #3
    834c:	e3a0b001 	mov	fp, #1
    8350:	e28d5030 	add	r5, sp, #48	; 0x30
    8354:	e35c0070 	cmp	ip, #112	; 0x70
    8358:	e2832001 	add	r2, r3, #1
    835c:	1affffd2 	bne	82ac <kprintf+0xb8>
    8360:	e59d000c 	ldr	r0, [sp, #12]
    8364:	e5901000 	ldr	r1, [r0]
    8368:	e2800004 	add	r0, r0, #4
    836c:	e58d000c 	str	r0, [sp, #12]
    8370:	e3510000 	cmp	r1, #0
    8374:	0a00013c 	beq	886c <kprintf+0x678>
    8378:	e1a0900e 	mov	r9, lr
    837c:	e3a0c000 	mov	ip, #0
    8380:	ea000000 	b	8388 <kprintf+0x194>
    8384:	e1a0c000 	mov	ip, r0
    8388:	e201000f 	and	r0, r1, #15
    838c:	e3500009 	cmp	r0, #9
    8390:	e2808030 	add	r8, r0, #48	; 0x30
    8394:	82808037 	addhi	r8, r0, #55	; 0x37
    8398:	e28c0001 	add	r0, ip, #1
    839c:	e1b01221 	lsrs	r1, r1, #4
    83a0:	e4c98001 	strb	r8, [r9], #1
    83a4:	1afffff6 	bne	8384 <kprintf+0x190>
    83a8:	e28d1e23 	add	r1, sp, #560	; 0x230
    83ac:	e28cc002 	add	ip, ip, #2
    83b0:	e0810000 	add	r0, r1, r0
    83b4:	e59d1000 	ldr	r1, [sp]
    83b8:	e3510001 	cmp	r1, #1
    83bc:	e3a01078 	mov	r1, #120	; 0x78
    83c0:	e5401220 	strb	r1, [r0, #-544]	; 0xfffffde0
    83c4:	e28d1e23 	add	r1, sp, #560	; 0x230
    83c8:	e081100c 	add	r1, r1, ip
    83cc:	e3a00030 	mov	r0, #48	; 0x30
    83d0:	e5410220 	strb	r0, [r1, #-544]	; 0xfffffde0
    83d4:	0a000108 	beq	87fc <kprintf+0x608>
    83d8:	e08e100c 	add	r1, lr, ip
    83dc:	e2440001 	sub	r0, r4, #1
    83e0:	e0855000 	add	r5, r5, r0
    83e4:	e3a00030 	mov	r0, #48	; 0x30
    83e8:	ea000000 	b	83f0 <kprintf+0x1fc>
    83ec:	e5710001 	ldrb	r0, [r1, #-1]!
    83f0:	e15e0001 	cmp	lr, r1
    83f4:	e5e50001 	strb	r0, [r5, #1]!
    83f8:	1afffffb 	bne	83ec <kprintf+0x1f8>
    83fc:	e5d31001 	ldrb	r1, [r3, #1]
    8400:	e2844001 	add	r4, r4, #1
    8404:	e084400c 	add	r4, r4, ip
    8408:	e3a03000 	mov	r3, #0
    840c:	e58d3000 	str	r3, [sp]
    8410:	eaffff8e 	b	8250 <kprintf+0x5c>
    8414:	e28d3e23 	add	r3, sp, #560	; 0x230
    8418:	e2822002 	add	r2, r2, #2
    841c:	e0833004 	add	r3, r3, r4
    8420:	e2844001 	add	r4, r4, #1
    8424:	e5431200 	strb	r1, [r3, #-512]	; 0xfffffe00
    8428:	e5d21000 	ldrb	r1, [r2]
    842c:	eaffff87 	b	8250 <kprintf+0x5c>
    8430:	e59d100c 	ldr	r1, [sp, #12]
    8434:	e5913000 	ldr	r3, [r1]
    8438:	e2811004 	add	r1, r1, #4
    843c:	e58d100c 	str	r1, [sp, #12]
    8440:	e5d31000 	ldrb	r1, [r3]
    8444:	e3510000 	cmp	r1, #0
    8448:	028d5030 	addeq	r5, sp, #48	; 0x30
    844c:	0a000009 	beq	8478 <kprintf+0x284>
    8450:	e044c003 	sub	ip, r4, r3
    8454:	e2440001 	sub	r0, r4, #1
    8458:	e28d5030 	add	r5, sp, #48	; 0x30
    845c:	e2833001 	add	r3, r3, #1
    8460:	e0850000 	add	r0, r5, r0
    8464:	e08c4003 	add	r4, ip, r3
    8468:	e5e01001 	strb	r1, [r0, #1]!
    846c:	e4d31001 	ldrb	r1, [r3], #1
    8470:	e3510000 	cmp	r1, #0
    8474:	1afffffa 	bne	8464 <kprintf+0x270>
    8478:	e5d2c002 	ldrb	ip, [r2, #2]
    847c:	e2823002 	add	r3, r2, #2
    8480:	eaffff86 	b	82a0 <kprintf+0xac>
    8484:	e59d100c 	ldr	r1, [sp, #12]
    8488:	e28e900a 	add	r9, lr, #10
    848c:	e3a00009 	mov	r0, #9
    8490:	e5918000 	ldr	r8, [r1]
    8494:	e2811004 	add	r1, r1, #4
    8498:	e58d100c 	str	r1, [sp, #12]
    849c:	ea000000 	b	84a4 <kprintf+0x2b0>
    84a0:	e1a0000c 	mov	r0, ip
    84a4:	e208c00f 	and	ip, r8, #15
    84a8:	e35c0009 	cmp	ip, #9
    84ac:	e28c1030 	add	r1, ip, #48	; 0x30
    84b0:	828c1057 	addhi	r1, ip, #87	; 0x57
    84b4:	e358000f 	cmp	r8, #15
    84b8:	e5691001 	strb	r1, [r9, #-1]!
    84bc:	e240c001 	sub	ip, r0, #1
    84c0:	e1a08228 	lsr	r8, r8, #4
    84c4:	8afffff5 	bhi	84a0 <kprintf+0x2ac>
    84c8:	e59d8000 	ldr	r8, [sp]
    84cc:	e3580000 	cmp	r8, #0
    84d0:	1a000098 	bne	8738 <kprintf+0x544>
    84d4:	e35b0000 	cmp	fp, #0
    84d8:	1a0000a8 	bne	8780 <kprintf+0x58c>
    84dc:	e244c001 	sub	ip, r4, #1
    84e0:	e085500c 	add	r5, r5, ip
    84e4:	e280c001 	add	ip, r0, #1
    84e8:	e08ec00c 	add	ip, lr, ip
    84ec:	ea000000 	b	84f4 <kprintf+0x300>
    84f0:	e4dc1001 	ldrb	r1, [ip], #1
    84f4:	e15c0006 	cmp	ip, r6
    84f8:	e5e51001 	strb	r1, [r5, #1]!
    84fc:	1afffffb 	bne	84f0 <kprintf+0x2fc>
    8500:	e5d31001 	ldrb	r1, [r3, #1]
    8504:	e284400a 	add	r4, r4, #10
    8508:	e0444000 	sub	r4, r4, r0
    850c:	e3a0b000 	mov	fp, #0
    8510:	e58db000 	str	fp, [sp]
    8514:	eaffff4d 	b	8250 <kprintf+0x5c>
    8518:	e59d300c 	ldr	r3, [sp, #12]
    851c:	e28d0e23 	add	r0, sp, #560	; 0x230
    8520:	e0800004 	add	r0, r0, r4
    8524:	e2822002 	add	r2, r2, #2
    8528:	e593c000 	ldr	ip, [r3]
    852c:	e2833004 	add	r3, r3, #4
    8530:	e5d21000 	ldrb	r1, [r2]
    8534:	e2844001 	add	r4, r4, #1
    8538:	e540c200 	strb	ip, [r0, #-512]	; 0xfffffe00
    853c:	e58d300c 	str	r3, [sp, #12]
    8540:	eaffff42 	b	8250 <kprintf+0x5c>
    8544:	e59d100c 	ldr	r1, [sp, #12]
    8548:	e3a0a00a 	mov	sl, #10
    854c:	e5910000 	ldr	r0, [r1]
    8550:	e2811004 	add	r1, r1, #4
    8554:	e58d100c 	str	r1, [sp, #12]
    8558:	e0201fc0 	eor	r1, r0, r0, asr #31
    855c:	e0411fc0 	sub	r1, r1, r0, asr #31
    8560:	e58d0004 	str	r0, [sp, #4]
    8564:	e080c197 	umull	ip, r0, r7, r1
    8568:	e1a001a0 	lsr	r0, r0, #3
    856c:	e061109a 	mls	r1, sl, r0, r1
    8570:	e2508000 	subs	r8, r0, #0
    8574:	e2811030 	add	r1, r1, #48	; 0x30
    8578:	e5cd1010 	strb	r1, [sp, #16]
    857c:	0a0000aa 	beq	882c <kprintf+0x638>
    8580:	e1a0900e 	mov	r9, lr
    8584:	e3a00000 	mov	r0, #0
    8588:	e081c897 	umull	ip, r1, r7, r8
    858c:	e1a011a1 	lsr	r1, r1, #3
    8590:	e06c819a 	mls	ip, sl, r1, r8
    8594:	e2518000 	subs	r8, r1, #0
    8598:	e28c1030 	add	r1, ip, #48	; 0x30
    859c:	e5e91001 	strb	r1, [r9, #1]!
    85a0:	e1a01000 	mov	r1, r0
    85a4:	e2800001 	add	r0, r0, #1
    85a8:	1afffff6 	bne	8588 <kprintf+0x394>
    85ac:	e2811002 	add	r1, r1, #2
    85b0:	e59dc004 	ldr	ip, [sp, #4]
    85b4:	e35b0000 	cmp	fp, #0
    85b8:	0a000042 	beq	86c8 <kprintf+0x4d4>
    85bc:	e35c0000 	cmp	ip, #0
    85c0:	ba00007b 	blt	87b4 <kprintf+0x5c0>
    85c4:	e261c008 	rsb	ip, r1, #8
    85c8:	e35c0000 	cmp	ip, #0
    85cc:	da0000c7 	ble	88f0 <kprintf+0x6fc>
    85d0:	e08e1001 	add	r1, lr, r1
    85d4:	e081000c 	add	r0, r1, ip
    85d8:	e3a0c030 	mov	ip, #48	; 0x30
    85dc:	e4c1c001 	strb	ip, [r1], #1
    85e0:	e1510000 	cmp	r1, r0
    85e4:	1afffffb 	bne	85d8 <kprintf+0x3e4>
    85e8:	e59dc000 	ldr	ip, [sp]
    85ec:	e3a08030 	mov	r8, #48	; 0x30
    85f0:	e3a00007 	mov	r0, #7
    85f4:	e3a01008 	mov	r1, #8
    85f8:	e35c0000 	cmp	ip, #0
    85fc:	0a00003f 	beq	8700 <kprintf+0x50c>
    8600:	e2619008 	rsb	r9, r1, #8
    8604:	e3590000 	cmp	r9, #0
    8608:	da00003c 	ble	8700 <kprintf+0x50c>
    860c:	e085c004 	add	ip, r5, r4
    8610:	e3a0a020 	mov	sl, #32
    8614:	e08c9009 	add	r9, ip, r9
    8618:	e4cca001 	strb	sl, [ip], #1
    861c:	e15c0009 	cmp	ip, r9
    8620:	1afffffc 	bne	8618 <kprintf+0x424>
    8624:	e0441001 	sub	r1, r4, r1
    8628:	e2814008 	add	r4, r1, #8
    862c:	ea000033 	b	8700 <kprintf+0x50c>
    8630:	e59d100c 	ldr	r1, [sp, #12]
    8634:	e28e800a 	add	r8, lr, #10
    8638:	e3a0a009 	mov	sl, #9
    863c:	e3a0900a 	mov	r9, #10
    8640:	e5910000 	ldr	r0, [r1]
    8644:	e2811004 	add	r1, r1, #4
    8648:	e58d100c 	str	r1, [sp, #12]
    864c:	e1a0c00a 	mov	ip, sl
    8650:	e3500009 	cmp	r0, #9
    8654:	e08a1097 	umull	r1, sl, r7, r0
    8658:	e1a0a1aa 	lsr	sl, sl, #3
    865c:	e0610a99 	mls	r1, r9, sl, r0
    8660:	e1a0000a 	mov	r0, sl
    8664:	e24ca001 	sub	sl, ip, #1
    8668:	e2811030 	add	r1, r1, #48	; 0x30
    866c:	e6ef1071 	uxtb	r1, r1
    8670:	e5681001 	strb	r1, [r8, #-1]!
    8674:	8afffff4 	bhi	864c <kprintf+0x458>
    8678:	e59d0000 	ldr	r0, [sp]
    867c:	e3500000 	cmp	r0, #0
    8680:	1a00006b 	bne	8834 <kprintf+0x640>
    8684:	e35b0001 	cmp	fp, #1
    8688:	0a000089 	beq	88b4 <kprintf+0x6c0>
    868c:	e2440001 	sub	r0, r4, #1
    8690:	e0855000 	add	r5, r5, r0
    8694:	e28c0001 	add	r0, ip, #1
    8698:	e08e0000 	add	r0, lr, r0
    869c:	ea000000 	b	86a4 <kprintf+0x4b0>
    86a0:	e4d01001 	ldrb	r1, [r0], #1
    86a4:	e1500006 	cmp	r0, r6
    86a8:	e5e51001 	strb	r1, [r5, #1]!
    86ac:	1afffffb 	bne	86a0 <kprintf+0x4ac>
    86b0:	e5d31001 	ldrb	r1, [r3, #1]
    86b4:	e26cc00a 	rsb	ip, ip, #10
    86b8:	e08c4004 	add	r4, ip, r4
    86bc:	e3a03000 	mov	r3, #0
    86c0:	e58d3000 	str	r3, [sp]
    86c4:	eafffee1 	b	8250 <kprintf+0x5c>
    86c8:	e35c0000 	cmp	ip, #0
    86cc:	e28dce23 	add	ip, sp, #560	; 0x230
    86d0:	b08cc001 	addlt	ip, ip, r1
    86d4:	b3a0802d 	movlt	r8, #45	; 0x2d
    86d8:	a08cc000 	addge	ip, ip, r0
    86dc:	b54c8220 	strblt	r8, [ip, #-544]	; 0xfffffde0
    86e0:	b280c002 	addlt	ip, r0, #2
    86e4:	a55c8220 	ldrbge	r8, [ip, #-544]	; 0xfffffde0
    86e8:	b1a00001 	movlt	r0, r1
    86ec:	b3a0802d 	movlt	r8, #45	; 0x2d
    86f0:	b1a0100c 	movlt	r1, ip
    86f4:	e59dc000 	ldr	ip, [sp]
    86f8:	e35c0000 	cmp	ip, #0
    86fc:	1affffbf 	bne	8600 <kprintf+0x40c>
    8700:	e08e1000 	add	r1, lr, r0
    8704:	e244c001 	sub	ip, r4, #1
    8708:	e085500c 	add	r5, r5, ip
    870c:	ea000000 	b	8714 <kprintf+0x520>
    8710:	e5718001 	ldrb	r8, [r1, #-1]!
    8714:	e151000e 	cmp	r1, lr
    8718:	e5e58001 	strb	r8, [r5, #1]!
    871c:	1afffffb 	bne	8710 <kprintf+0x51c>
    8720:	e5d31001 	ldrb	r1, [r3, #1]
    8724:	e2844001 	add	r4, r4, #1
    8728:	e0804004 	add	r4, r0, r4
    872c:	e3a0b000 	mov	fp, #0
    8730:	e58db000 	str	fp, [sp]
    8734:	eafffec5 	b	8250 <kprintf+0x5c>
    8738:	e2408003 	sub	r8, r0, #3
    873c:	e58d8000 	str	r8, [sp]
    8740:	e3580000 	cmp	r8, #0
    8744:	daffff62 	ble	84d4 <kprintf+0x2e0>
    8748:	e28d802c 	add	r8, sp, #44	; 0x2c
    874c:	e3a0a020 	mov	sl, #32
    8750:	e0889004 	add	r9, r8, r4
    8754:	e2448001 	sub	r8, r4, #1
    8758:	e0899000 	add	r9, r9, r0
    875c:	e0858008 	add	r8, r5, r8
    8760:	e5e8a001 	strb	sl, [r8, #1]!
    8764:	e1580009 	cmp	r8, r9
    8768:	1afffffc 	bne	8760 <kprintf+0x56c>
    876c:	e0804004 	add	r4, r0, r4
    8770:	e35b0000 	cmp	fp, #0
    8774:	e2444003 	sub	r4, r4, #3
    8778:	0affff57 	beq	84dc <kprintf+0x2e8>
    877c:	ea000002 	b	878c <kprintf+0x598>
    8780:	e2508003 	subs	r8, r0, #3
    8784:	e58d8000 	str	r8, [sp]
    8788:	4affff53 	bmi	84dc <kprintf+0x2e8>
    878c:	e08e000c 	add	r0, lr, ip
    8790:	e59d1000 	ldr	r1, [sp]
    8794:	e2511001 	subs	r1, r1, #1
    8798:	e3a08030 	mov	r8, #48	; 0x30
    879c:	e4408001 	strb	r8, [r0], #-1
    87a0:	2afffffb 	bcs	8794 <kprintf+0x5a0>
    87a4:	e59d1000 	ldr	r1, [sp]
    87a8:	e04c0001 	sub	r0, ip, r1
    87ac:	e3a01030 	mov	r1, #48	; 0x30
    87b0:	eaffff49 	b	84dc <kprintf+0x2e8>
    87b4:	e2610007 	rsb	r0, r1, #7
    87b8:	e3500000 	cmp	r0, #0
    87bc:	d1a00001 	movle	r0, r1
    87c0:	da000006 	ble	87e0 <kprintf+0x5ec>
    87c4:	e08e1001 	add	r1, lr, r1
    87c8:	e0810000 	add	r0, r1, r0
    87cc:	e3a0c030 	mov	ip, #48	; 0x30
    87d0:	e4c1c001 	strb	ip, [r1], #1
    87d4:	e1510000 	cmp	r1, r0
    87d8:	1afffffb 	bne	87cc <kprintf+0x5d8>
    87dc:	e3a00007 	mov	r0, #7
    87e0:	e28d1e23 	add	r1, sp, #560	; 0x230
    87e4:	e3a0c02d 	mov	ip, #45	; 0x2d
    87e8:	e0811000 	add	r1, r1, r0
    87ec:	e3a0802d 	mov	r8, #45	; 0x2d
    87f0:	e541c220 	strb	ip, [r1, #-544]	; 0xfffffde0
    87f4:	e2801001 	add	r1, r0, #1
    87f8:	eaffffbd 	b	86f4 <kprintf+0x500>
    87fc:	e26c9007 	rsb	r9, ip, #7
    8800:	e3590000 	cmp	r9, #0
    8804:	dafffef3 	ble	83d8 <kprintf+0x1e4>
    8808:	e2440001 	sub	r0, r4, #1
    880c:	e1a01009 	mov	r1, r9
    8810:	e0850000 	add	r0, r5, r0
    8814:	e3a08020 	mov	r8, #32
    8818:	e5e08001 	strb	r8, [r0, #1]!
    881c:	e2511001 	subs	r1, r1, #1
    8820:	1afffffc 	bne	8818 <kprintf+0x624>
    8824:	e0894004 	add	r4, r9, r4
    8828:	eafffeea 	b	83d8 <kprintf+0x1e4>
    882c:	e3a01001 	mov	r1, #1
    8830:	eaffff5e 	b	85b0 <kprintf+0x3bc>
    8834:	e35c0003 	cmp	ip, #3
    8838:	daffff93 	ble	868c <kprintf+0x498>
    883c:	e28d002c 	add	r0, sp, #44	; 0x2c
    8840:	e3a09020 	mov	r9, #32
    8844:	e0808004 	add	r8, r0, r4
    8848:	e2440001 	sub	r0, r4, #1
    884c:	e088800c 	add	r8, r8, ip
    8850:	e0850000 	add	r0, r5, r0
    8854:	e5e09001 	strb	r9, [r0, #1]!
    8858:	e1500008 	cmp	r0, r8
    885c:	1afffffc 	bne	8854 <kprintf+0x660>
    8860:	e08c4004 	add	r4, ip, r4
    8864:	e2444003 	sub	r4, r4, #3
    8868:	eaffff87 	b	868c <kprintf+0x498>
    886c:	e3a01030 	mov	r1, #48	; 0x30
    8870:	e5cd1011 	strb	r1, [sp, #17]
    8874:	e59d1000 	ldr	r1, [sp]
    8878:	e3510001 	cmp	r1, #1
    887c:	e3a01078 	mov	r1, #120	; 0x78
    8880:	e5cd1010 	strb	r1, [sp, #16]
    8884:	13a0c001 	movne	ip, #1
    8888:	1afffed2 	bne	83d8 <kprintf+0x1e4>
    888c:	e59dc000 	ldr	ip, [sp]
    8890:	e3a09006 	mov	r9, #6
    8894:	eaffffdb 	b	8808 <kprintf+0x614>
    8898:	e3080cdc 	movw	r0, #36060	; 0x8cdc
    889c:	e3a04000 	mov	r4, #0
    88a0:	e3400000 	movt	r0, #0
    88a4:	ebfffe52 	bl	81f4 <kprintf>
    88a8:	eafffe9d 	b	8324 <kprintf+0x130>
    88ac:	e1a04001 	mov	r4, r1
    88b0:	eafffe98 	b	8318 <kprintf+0x124>
    88b4:	e35c0003 	cmp	ip, #3
    88b8:	da000010 	ble	8900 <kprintf+0x70c>
    88bc:	e28d002c 	add	r0, sp, #44	; 0x2c
    88c0:	e0808004 	add	r8, r0, r4
    88c4:	e2440001 	sub	r0, r4, #1
    88c8:	e088800c 	add	r8, r8, ip
    88cc:	e0850000 	add	r0, r5, r0
    88d0:	e3a09030 	mov	r9, #48	; 0x30
    88d4:	e5e09001 	strb	r9, [r0, #1]!
    88d8:	e1500008 	cmp	r0, r8
    88dc:	1afffffb 	bne	88d0 <kprintf+0x6dc>
    88e0:	e08c4004 	add	r4, ip, r4
    88e4:	e3a0b000 	mov	fp, #0
    88e8:	e2444003 	sub	r4, r4, #3
    88ec:	eaffff66 	b	868c <kprintf+0x498>
    88f0:	e28d1e23 	add	r1, sp, #560	; 0x230
    88f4:	e0811000 	add	r1, r1, r0
    88f8:	e5518220 	ldrb	r8, [r1, #-544]	; 0xfffffde0
    88fc:	eaffff7f 	b	8700 <kprintf+0x50c>
    8900:	e59db000 	ldr	fp, [sp]
    8904:	eaffff60 	b	868c <kprintf+0x498>
    8908:	00008ced 	.word	0x00008ced

0000890c <uart_init>:
    890c:	e3013030 	movw	r3, #4144	; 0x1030
    8910:	e3a02000 	mov	r2, #0
    8914:	e3433f20 	movt	r3, #16160	; 0x3f20
    8918:	e5832000 	str	r2, [r3]
    891c:	e3a01010 	mov	r1, #16
    8920:	e5812000 	str	r2, [r1]
    8924:	e3a01c01 	mov	r1, #256	; 0x100
    8928:	e3a02001 	mov	r2, #1
    892c:	e5812000 	str	r2, [r1]
    8930:	e3a01c02 	mov	r1, #512	; 0x200
    8934:	e5812000 	str	r2, [r1]
    8938:	e5832000 	str	r2, [r3]
    893c:	e12fff1e 	bx	lr

00008940 <uart_putc>:
    8940:	e3012018 	movw	r2, #4120	; 0x1018
    8944:	e3432f20 	movt	r2, #16160	; 0x3f20
    8948:	e5923000 	ldr	r3, [r2]
    894c:	e3130020 	tst	r3, #32
    8950:	1afffffc 	bne	8948 <uart_putc+0x8>
    8954:	e3a03a01 	mov	r3, #4096	; 0x1000
    8958:	e3433f20 	movt	r3, #16160	; 0x3f20
    895c:	e5830000 	str	r0, [r3]
    8960:	e12fff1e 	bx	lr

00008964 <uart_getc>:
    8964:	e3012018 	movw	r2, #4120	; 0x1018
    8968:	e3432f20 	movt	r2, #16160	; 0x3f20
    896c:	e5923000 	ldr	r3, [r2]
    8970:	e3130010 	tst	r3, #16
    8974:	1afffffc 	bne	896c <uart_getc+0x8>
    8978:	e3a00a01 	mov	r0, #4096	; 0x1000
    897c:	e3430f20 	movt	r0, #16160	; 0x3f20
    8980:	e5900000 	ldr	r0, [r0]
    8984:	e6ef0070 	uxtb	r0, r0
    8988:	e12fff1e 	bx	lr

0000898c <uart_write>:
    898c:	e251c000 	subs	ip, r1, #0
    8990:	d12fff1e 	bxle	lr
    8994:	e2401001 	sub	r1, r0, #1
    8998:	e3012018 	movw	r2, #4120	; 0x1018
    899c:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    89a0:	e3a0ea01 	mov	lr, #4096	; 0x1000
    89a4:	e081c00c 	add	ip, r1, ip
    89a8:	e3432f20 	movt	r2, #16160	; 0x3f20
    89ac:	e343ef20 	movt	lr, #16160	; 0x3f20
    89b0:	e5f10001 	ldrb	r0, [r1, #1]!
    89b4:	e5923000 	ldr	r3, [r2]
    89b8:	e3130020 	tst	r3, #32
    89bc:	1afffffc 	bne	89b4 <uart_write+0x28>
    89c0:	e58e0000 	str	r0, [lr]
    89c4:	e151000c 	cmp	r1, ip
    89c8:	1afffff8 	bne	89b0 <uart_write+0x24>
    89cc:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

Disassembly of section .text.startup:

00008d04 <main>:
    8d04:	e3a00000 	mov	r0, #0
    8d08:	e12fff1e 	bx	lr
