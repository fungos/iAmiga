
// ---------- [b000] cmp.b d0, d0 ----------
OPCODE(0xB000)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(4)
}

// ---------- [b008] cmp.b a0, d0 ----------
OPCODE(0xB008)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
*/
	FINISH(4)
}

// ---------- [b010] cmp.b (a0), d0 ----------
OPCODE(0xB010)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [b018] cmp.b (a0)+, d0 ----------
OPCODE(0xB018)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [b020] cmp.b -(a0), d0 ----------
OPCODE(0xB020)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [b028] cmp.b ($3333,a0), d0 ----------
OPCODE(0xB028)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b030] cmp.b ($33,a0,d3.w*2), d0 ----------
OPCODE(0xB030)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b038] cmp.b $3333.w, d0 ----------
OPCODE(0xB038)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b039] cmp.b $33333333.l, d0 ----------
OPCODE(0xB039)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [b03a] cmp.b ($3333,pc), d0; =3335 ----------
OPCODE(0xB03A)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b03b] cmp.b ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xB03B)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b03c] cmp.b #$33, d0 ----------
OPCODE(0xB03C)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(8)
}

// ---------- [b01f] cmp.b (a7)+, d0 ----------
OPCODE(0xB01F)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [b027] cmp.b -(a7), d0 ----------
OPCODE(0xB027)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [b040] cmp.w d0, d0 ----------
OPCODE(0xB040)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(4)
}

// ---------- [b048] cmp.w a0, d0 ----------
OPCODE(0xB048)
{
	u32 adr, res;
	u32 src, dst;

	src = AREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(4)
}

// ---------- [b050] cmp.w (a0), d0 ----------
OPCODE(0xB050)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [b058] cmp.w (a0)+, d0 ----------
OPCODE(0xB058)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [b060] cmp.w -(a0), d0 ----------
OPCODE(0xB060)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [b068] cmp.w ($3333,a0), d0 ----------
OPCODE(0xB068)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b070] cmp.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0xB070)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b078] cmp.w $3333.w, d0 ----------
OPCODE(0xB078)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b079] cmp.w $33333333.l, d0 ----------
OPCODE(0xB079)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [b07a] cmp.w ($3333,pc), d0; =3335 ----------
OPCODE(0xB07A)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b07b] cmp.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xB07B)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b07c] cmp.w #$3333, d0 ----------
OPCODE(0xB07C)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(8)
}

// ---------- [b05f] cmp.w (a7)+, d0 ----------
OPCODE(0xB05F)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [b067] cmp.w -(a7), d0 ----------
OPCODE(0xB067)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [b080] cmp.l d0, d0 ----------
OPCODE(0xB080)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(6)
}

// ---------- [b088] cmp.l a0, d0 ----------
OPCODE(0xB088)
{
	u32 adr, res;
	u32 src, dst;

	src = AREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(6)
}

// ---------- [b090] cmp.l (a0), d0 ----------
OPCODE(0xB090)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b098] cmp.l (a0)+, d0 ----------
OPCODE(0xB098)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b0a0] cmp.l -(a0), d0 ----------
OPCODE(0xB0A0)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [b0a8] cmp.l ($3333,a0), d0 ----------
OPCODE(0xB0A8)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [b0b0] cmp.l ($33,a0,d3.w*2), d0 ----------
OPCODE(0xB0B0)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [b0b8] cmp.l $3333.w, d0 ----------
OPCODE(0xB0B8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [b0b9] cmp.l $33333333.l, d0 ----------
OPCODE(0xB0B9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(22)
}

// ---------- [b0ba] cmp.l ($3333,pc), d0; =3335 ----------
OPCODE(0xB0BA)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [b0bb] cmp.l ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xB0BB)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [b0bc] cmp.l #$33333333, d0 ----------
OPCODE(0xB0BC)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(14)
}

// ---------- [b09f] cmp.l (a7)+, d0 ----------
OPCODE(0xB09F)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b0a7] cmp.l -(a7), d0 ----------
OPCODE(0xB0A7)
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
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [b108] cmpm.b (a0)+, (a0)+ ----------
OPCODE(0xB108)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b148] cmpm.w (a0)+, (a0)+ ----------
OPCODE(0xB148)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b188] cmpm.l (a0)+, (a0)+ ----------
OPCODE(0xB188)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [b10f] cmpm.b (a7)+, (a0)+ ----------
OPCODE(0xB10F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b14f] cmpm.w (a7)+, (a0)+ ----------
OPCODE(0xB14F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b18f] cmpm.l (a7)+, (a0)+ ----------
OPCODE(0xB18F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [bf08] cmpm.b (a0)+, (a7)+ ----------
OPCODE(0xBF08)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [bf48] cmpm.w (a0)+, (a7)+ ----------
OPCODE(0xBF48)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [bf88] cmpm.l (a0)+, (a7)+ ----------
OPCODE(0xBF88)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG(7);
	AREG(7) += 4;
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [bf0f] cmpm.b (a7)+, (a7)+ ----------
OPCODE(0xBF0F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [bf4f] cmpm.w (a7)+, (a7)+ ----------
OPCODE(0xBF4F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [bf8f] cmpm.l (a7)+, (a7)+ ----------
OPCODE(0xBF8F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	adr = AREG(7);
	AREG(7) += 4;
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [b100] eor.b d0, d0 ----------
OPCODE(0xB100)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	res = DREGu8((Opcode >> 0) & 7);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [b110] eor.b d0, (a0) ----------
OPCODE(0xB110)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [b118] eor.b d0, (a0)+ ----------
OPCODE(0xB118)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [b120] eor.b d0, -(a0) ----------
OPCODE(0xB120)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [b128] eor.b d0, ($3333,a0) ----------
OPCODE(0xB128)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [b130] eor.b d0, ($33,a0,d3.w*2) ----------
OPCODE(0xB130)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [b138] eor.b d0, $3333.w ----------
OPCODE(0xB138)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [b139] eor.b d0, $33333333.l ----------
OPCODE(0xB139)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [b11f] eor.b d0, (a7)+ ----------
OPCODE(0xB11F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [b127] eor.b d0, -(a7) ----------
OPCODE(0xB127)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [b140] eor.w d0, d0 ----------
OPCODE(0xB140)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	res = DREGu16((Opcode >> 0) & 7);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [b150] eor.w d0, (a0) ----------
OPCODE(0xB150)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [b158] eor.w d0, (a0)+ ----------
OPCODE(0xB158)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [b160] eor.w d0, -(a0) ----------
OPCODE(0xB160)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [b168] eor.w d0, ($3333,a0) ----------
OPCODE(0xB168)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [b170] eor.w d0, ($33,a0,d3.w*2) ----------
OPCODE(0xB170)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [b178] eor.w d0, $3333.w ----------
OPCODE(0xB178)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [b179] eor.w d0, $33333333.l ----------
OPCODE(0xB179)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [b15f] eor.w d0, (a7)+ ----------
OPCODE(0xB15F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [b167] eor.w d0, -(a7) ----------
OPCODE(0xB167)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [b180] eor.l d0, d0 ----------
OPCODE(0xB180)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	res = DREGu32((Opcode >> 0) & 7);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [b190] eor.l d0, (a0) ----------
OPCODE(0xB190)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [b198] eor.l d0, (a0)+ ----------
OPCODE(0xB198)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [b1a0] eor.l d0, -(a0) ----------
OPCODE(0xB1A0)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [b1a8] eor.l d0, ($3333,a0) ----------
OPCODE(0xB1A8)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [b1b0] eor.l d0, ($33,a0,d3.w*2) ----------
OPCODE(0xB1B0)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [b1b8] eor.l d0, $3333.w ----------
OPCODE(0xB1B8)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [b1b9] eor.l d0, $33333333.l ----------
OPCODE(0xB1B9)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [b19f] eor.l d0, (a7)+ ----------
OPCODE(0xB19F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [b1a7] eor.l d0, -(a7) ----------
OPCODE(0xB1A7)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [b0c0] cmpa.w d0, a0 ----------
OPCODE(0xB0C0)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs16((Opcode >> 0) & 7);
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(6)
}

// ---------- [b0c8] cmpa.w a0, a0 ----------
OPCODE(0xB0C8)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)(s16)AREG((Opcode >> 0) & 7);
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(6)
}

// ---------- [b0d0] cmpa.w (a0), a0 ----------
OPCODE(0xB0D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [b0d8] cmpa.w (a0)+, a0 ----------
OPCODE(0xB0D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [b0e0] cmpa.w -(a0), a0 ----------
OPCODE(0xB0E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b0e8] cmpa.w ($3333,a0), a0 ----------
OPCODE(0xB0E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b0f0] cmpa.w ($33,a0,d3.w*2), a0 ----------
OPCODE(0xB0F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [b0f8] cmpa.w $3333.w, a0 ----------
OPCODE(0xB0F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b0f9] cmpa.w $33333333.l, a0 ----------
OPCODE(0xB0F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [b0fa] cmpa.w ($3333,pc), a0; =3335 ----------
OPCODE(0xB0FA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b0fb] cmpa.w ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0xB0FB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [b0fc] cmpa.w #$3333, a0 ----------
OPCODE(0xB0FC)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)FETCH_SWORD;
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(10)
}

// ---------- [b0df] cmpa.w (a7)+, a0 ----------
OPCODE(0xB0DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [b0e7] cmpa.w -(a7), a0 ----------
OPCODE(0xB0E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src], asr #16 " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [b1c0] cmpa.l d0, a0 ----------
OPCODE(0xB1C0)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs32((Opcode >> 0) & 7);
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(6)
}

// ---------- [b1c8] cmpa.l a0, a0 ----------
OPCODE(0xB1C8)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)(s32)AREG((Opcode >> 0) & 7);
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(6)
}

// ---------- [b1d0] cmpa.l (a0), a0 ----------
OPCODE(0xB1D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b1d8] cmpa.l (a0)+, a0 ----------
OPCODE(0xB1D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b1e0] cmpa.l -(a0), a0 ----------
OPCODE(0xB1E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [b1e8] cmpa.l ($3333,a0), a0 ----------
OPCODE(0xB1E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [b1f0] cmpa.l ($33,a0,d3.w*2), a0 ----------
OPCODE(0xB1F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [b1f8] cmpa.l $3333.w, a0 ----------
OPCODE(0xB1F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [b1f9] cmpa.l $33333333.l, a0 ----------
OPCODE(0xB1F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(22)
}

// ---------- [b1fa] cmpa.l ($3333,pc), a0; =3335 ----------
OPCODE(0xB1FA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [b1fb] cmpa.l ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0xB1FB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [b1fc] cmpa.l #$33333333, a0 ----------
OPCODE(0xB1FC)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(14)
}

// ---------- [b1df] cmpa.l (a7)+, a0 ----------
OPCODE(0xB1DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [b1e7] cmpa.l -(a7), a0 ----------
OPCODE(0xB1E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("cmp %[dst], %[src] " : : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}
