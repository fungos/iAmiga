
// ---------- [9000] sub.b d0, d0 ----------
OPCODE(0x9000)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [9008] sub.b a0, d0 ----------
OPCODE(0x9008)
{
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
*/
	FINISH(4)
}

// ---------- [9010] sub.b (a0), d0 ----------
OPCODE(0x9010)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [9018] sub.b (a0)+, d0 ----------
OPCODE(0x9018)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [9020] sub.b -(a0), d0 ----------
OPCODE(0x9020)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [9028] sub.b ($3333,a0), d0 ----------
OPCODE(0x9028)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [9030] sub.b ($33,a0,d3.w*2), d0 ----------
OPCODE(0x9030)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [9038] sub.b $3333.w, d0 ----------
OPCODE(0x9038)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [9039] sub.b $33333333.l, d0 ----------
OPCODE(0x9039)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [903a] sub.b ($3333,pc), d0; =3335 ----------
OPCODE(0x903A)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [903b] sub.b ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x903B)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [903c] sub.b #$33, d0 ----------
OPCODE(0x903C)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [901f] sub.b (a7)+, d0 ----------
OPCODE(0x901F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [9027] sub.b -(a7), d0 ----------
OPCODE(0x9027)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [9040] sub.w d0, d0 ----------
OPCODE(0x9040)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [9048] sub.w a0, d0 ----------
OPCODE(0x9048)
{
	u32 adr, res;
	u32 src, dst;

	src = AREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [9050] sub.w (a0), d0 ----------
OPCODE(0x9050)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [9058] sub.w (a0)+, d0 ----------
OPCODE(0x9058)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [9060] sub.w -(a0), d0 ----------
OPCODE(0x9060)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [9068] sub.w ($3333,a0), d0 ----------
OPCODE(0x9068)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [9070] sub.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0x9070)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [9078] sub.w $3333.w, d0 ----------
OPCODE(0x9078)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [9079] sub.w $33333333.l, d0 ----------
OPCODE(0x9079)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [907a] sub.w ($3333,pc), d0; =3335 ----------
OPCODE(0x907A)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [907b] sub.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x907B)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [907c] sub.w #$3333, d0 ----------
OPCODE(0x907C)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [905f] sub.w (a7)+, d0 ----------
OPCODE(0x905F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [9067] sub.w -(a7), d0 ----------
OPCODE(0x9067)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [9080] sub.l d0, d0 ----------
OPCODE(0x9080)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [9088] sub.l a0, d0 ----------
OPCODE(0x9088)
{
	u32 adr, res;
	u32 src, dst;

	src = AREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [9090] sub.l (a0), d0 ----------
OPCODE(0x9090)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [9098] sub.l (a0)+, d0 ----------
OPCODE(0x9098)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [90a0] sub.l -(a0), d0 ----------
OPCODE(0x90A0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [90a8] sub.l ($3333,a0), d0 ----------
OPCODE(0x90A8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [90b0] sub.l ($33,a0,d3.w*2), d0 ----------
OPCODE(0x90B0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [90b8] sub.l $3333.w, d0 ----------
OPCODE(0x90B8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [90b9] sub.l $33333333.l, d0 ----------
OPCODE(0x90B9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(22)
}

// ---------- [90ba] sub.l ($3333,pc), d0; =3335 ----------
OPCODE(0x90BA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [90bb] sub.l ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x90BB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [90bc] sub.l #$33333333, d0 ----------
OPCODE(0x90BC)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(16)
}

// ---------- [909f] sub.l (a7)+, d0 ----------
OPCODE(0x909F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [90a7] sub.l -(a7), d0 ----------
OPCODE(0x90A7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [9110] sub.b d0, (a0) ----------
OPCODE(0x9110)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [9118] sub.b d0, (a0)+ ----------
OPCODE(0x9118)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [9120] sub.b d0, -(a0) ----------
OPCODE(0x9120)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [9128] sub.b d0, ($3333,a0) ----------
OPCODE(0x9128)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [9130] sub.b d0, ($33,a0,d3.w*2) ----------
OPCODE(0x9130)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9138] sub.b d0, $3333.w ----------
OPCODE(0x9138)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [9139] sub.b d0, $33333333.l ----------
OPCODE(0x9139)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [911f] sub.b d0, (a7)+ ----------
OPCODE(0x911F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [9127] sub.b d0, -(a7) ----------
OPCODE(0x9127)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [9150] sub.w d0, (a0) ----------
OPCODE(0x9150)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [9158] sub.w d0, (a0)+ ----------
OPCODE(0x9158)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [9160] sub.w d0, -(a0) ----------
OPCODE(0x9160)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [9168] sub.w d0, ($3333,a0) ----------
OPCODE(0x9168)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [9170] sub.w d0, ($33,a0,d3.w*2) ----------
OPCODE(0x9170)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9178] sub.w d0, $3333.w ----------
OPCODE(0x9178)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [9179] sub.w d0, $33333333.l ----------
OPCODE(0x9179)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [915f] sub.w d0, (a7)+ ----------
OPCODE(0x915F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [9167] sub.w d0, -(a7) ----------
OPCODE(0x9167)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [9190] sub.l d0, (a0) ----------
OPCODE(0x9190)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [9198] sub.l d0, (a0)+ ----------
OPCODE(0x9198)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [91a0] sub.l d0, -(a0) ----------
OPCODE(0x91A0)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [91a8] sub.l d0, ($3333,a0) ----------
OPCODE(0x91A8)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [91b0] sub.l d0, ($33,a0,d3.w*2) ----------
OPCODE(0x91B0)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [91b8] sub.l d0, $3333.w ----------
OPCODE(0x91B8)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [91b9] sub.l d0, $33333333.l ----------
OPCODE(0x91B9)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [919f] sub.l d0, (a7)+ ----------
OPCODE(0x919F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [91a7] sub.l d0, -(a7) ----------
OPCODE(0x91A7)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [9100] subx.b d0, d0 ----------
OPCODE(0x9100)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #8  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #24\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [9140] subx.w d0, d0 ----------
OPCODE(0x9140)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #16  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #16\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [9180] subx.l d0, d0 ----------
OPCODE(0x9180)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		:: [x_flag] "r" (X_FLAG) : "cc");
	asm volatile("rscs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res]\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [9108] subx.b -(a0), -(a0) ----------
OPCODE(0x9108)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_BYTE_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #8  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #24\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9148] subx.w -(a0), -(a0) ----------
OPCODE(0x9148)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_WORD_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #16  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #16\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9188] subx.l -(a0), -(a0) ----------
OPCODE(0x9188)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_LONG_F(adr);
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		:: [x_flag] "r" (X_FLAG) : "cc");
	asm volatile("rscs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res]\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [910f] subx.b -(a7), -(a0) ----------
OPCODE(0x910F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_BYTE_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #8  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #24\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [914f] subx.w -(a7), -(a0) ----------
OPCODE(0x914F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_WORD_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #16  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #16\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [918f] subx.l -(a7), -(a0) ----------
OPCODE(0x918F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_LONG_F(adr);
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		:: [x_flag] "r" (X_FLAG) : "cc");
	asm volatile("rscs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res]\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [9f08] subx.b -(a0), -(a7) ----------
OPCODE(0x9F08)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	dst = READ_BYTE_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #8  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #24\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9f48] subx.w -(a0), -(a7) ----------
OPCODE(0x9F48)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	dst = READ_WORD_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #16  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #16\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9f88] subx.l -(a0), -(a7) ----------
OPCODE(0x9F88)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG(7) - 4;
	AREG(7) = adr;
	dst = READ_LONG_F(adr);
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		:: [x_flag] "r" (X_FLAG) : "cc");
	asm volatile("rscs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res]\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [9f0f] subx.b -(a7), -(a7) ----------
OPCODE(0x9F0F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	dst = READ_BYTE_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #8  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #24\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9f4f] subx.w -(a7), -(a7) ----------
OPCODE(0x9F4F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	dst = READ_WORD_F(adr);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #16  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("rscs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res],lsr #16\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [9f8f] subx.l -(a7), -(a7) ----------
OPCODE(0x9F8F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG(7) - 4;
	AREG(7) = adr;
	dst = READ_LONG_F(adr);
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		:: [x_flag] "r" (X_FLAG) : "cc");
	asm volatile("rscs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res]\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [90c0] suba.w d0, a0 ----------
OPCODE(0x90C0)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs16((Opcode >> 0) & 7);
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [90c8] suba.w a0, a0 ----------
OPCODE(0x90C8)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)(s16)AREG((Opcode >> 0) & 7);
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [90d0] suba.w (a0), a0 ----------
OPCODE(0x90D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [90d8] suba.w (a0)+, a0 ----------
OPCODE(0x90D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [90e0] suba.w -(a0), a0 ----------
OPCODE(0x90E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [90e8] suba.w ($3333,a0), a0 ----------
OPCODE(0x90E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [90f0] suba.w ($33,a0,d3.w*2), a0 ----------
OPCODE(0x90F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [90f8] suba.w $3333.w, a0 ----------
OPCODE(0x90F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [90f9] suba.w $33333333.l, a0 ----------
OPCODE(0x90F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [90fa] suba.w ($3333,pc), a0; =3335 ----------
OPCODE(0x90FA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [90fb] suba.w ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0x90FB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [90fc] suba.w #$3333, a0 ----------
OPCODE(0x90FC)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)FETCH_SWORD;
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(12)
}

// ---------- [90df] suba.w (a7)+, a0 ----------
OPCODE(0x90DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [90e7] suba.w -(a7), a0 ----------
OPCODE(0x90E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [91c0] suba.l d0, a0 ----------
OPCODE(0x91C0)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs32((Opcode >> 0) & 7);
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(6)
}

// ---------- [91c8] suba.l a0, a0 ----------
OPCODE(0x91C8)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)(s32)AREG((Opcode >> 0) & 7);
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(6)
}

// ---------- [91d0] suba.l (a0), a0 ----------
OPCODE(0x91D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [91d8] suba.l (a0)+, a0 ----------
OPCODE(0x91D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [91e0] suba.l -(a0), a0 ----------
OPCODE(0x91E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [91e8] suba.l ($3333,a0), a0 ----------
OPCODE(0x91E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [91f0] suba.l ($33,a0,d3.w*2), a0 ----------
OPCODE(0x91F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [91f8] suba.l $3333.w, a0 ----------
OPCODE(0x91F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [91f9] suba.l $33333333.l, a0 ----------
OPCODE(0x91F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(22)
}

// ---------- [91fa] suba.l ($3333,pc), a0; =3335 ----------
OPCODE(0x91FA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [91fb] suba.l ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0x91FB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [91fc] suba.l #$33333333, a0 ----------
OPCODE(0x91FC)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(14)
}

// ---------- [91df] suba.l (a7)+, a0 ----------
OPCODE(0x91DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [91e7] suba.l -(a7), a0 ----------
OPCODE(0x91E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("sub %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}
