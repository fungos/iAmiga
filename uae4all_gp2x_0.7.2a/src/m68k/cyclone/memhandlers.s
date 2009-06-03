#if 0
.set device, 0
.set device, __arm__

.if device

@ vim:filetype=armasm
@ memory handlers for uae4all and Cyclone
@ (c) notaz, 2007

.globl cyclone_read8
.globl cyclone_read16
.globl cyclone_read32
.globl cyclone_write8
.globl cyclone_write16
.globl cyclone_write32


.macro get_base
	ldr	r2,baseaddr
	bic	r0,r0,#0xff000000
	mov	r3,r0,lsr #16
	ldr	r3,[r2,r3,lsl #2]
.endm


.text
.align 4


cyclone_read8:
	get_base
	eor	r2,r0,#1
	tst	r3,#1
	ldreqb	r0,[r3,r2]
	bxeq	lr
	ldr	pc,[r3,#7]	@ bget


cyclone_read16:
	get_base
	bic	r0,r0,#1
	tst	r3,#1
	ldreqh	r0,[r3,r0]
	bxeq	lr
	ldr	pc,[r3,#3]	@ wget


cyclone_read32:
	get_base
	bic	r0,r0,#1
	tst	r3,#1
	ldrne	pc,[r3,#-1]	@ lget
	ldrh	r0,[r3,r0]!
	ldrh	r2,[r3,#2]
	orr	r0,r2,r0,lsl #16
	bx	lr


cyclone_write8:
	get_base
	eor	r2,r0,#1
	tst	r3,#1
	streqb	r1,[r3,r2]
	bxeq	lr
	and	r1,r1,#0xff
	ldr	pc,[r3,#0x13]	@ bput


cyclone_write16:
	get_base
	bic	r0,r0,#1
	tst	r3,#1
	streqh	r1,[r3,r0]
	bxeq	lr
	mov	r1,r1,lsl #16
	mov	r1,r1,lsr #16
	ldr	pc,[r3,#0x0f]	@ wput


cyclone_write32:
	get_base
	bic	r0,r0,#1
	tst	r3,#1
	ldrne	pc,[r3,#0x0b]	@ lput
	mov	r2,r1,lsr #16
	strh	r2,[r3,r0]!
	strh	r1,[r3,#2]
	bx	lr

	.non_lazy_symbol_pointer
baseaddr:
	.indirect_symbol _baseaddr
	.long	0

.endif
#endif