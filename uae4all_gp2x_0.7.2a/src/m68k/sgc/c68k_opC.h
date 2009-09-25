
// ---------- [c000] and.b d0, d0 ----------
OPCODE(0xC000)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [c010] and.b (a0), d0 ----------
OPCODE(0xC010)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [c018] and.b (a0)+, d0 ----------
OPCODE(0xC018)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [c020] and.b -(a0), d0 ----------
OPCODE(0xC020)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [c028] and.b ($3333,a0), d0 ----------
OPCODE(0xC028)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [c030] and.b ($33,a0,d3.w*2), d0 ----------
OPCODE(0xC030)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [c038] and.b $3333.w, d0 ----------
OPCODE(0xC038)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [c039] and.b $33333333.l, d0 ----------
OPCODE(0xC039)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [c03a] and.b ($3333,pc), d0; =3335 ----------
OPCODE(0xC03A)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [c03b] and.b ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xC03B)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [c03c] and.b #$33, d0 ----------
OPCODE(0xC03C)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [c01f] and.b (a7)+, d0 ----------
OPCODE(0xC01F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [c027] and.b -(a7), d0 ----------
OPCODE(0xC027)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [c040] and.w d0, d0 ----------
OPCODE(0xC040)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [c050] and.w (a0), d0 ----------
OPCODE(0xC050)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [c058] and.w (a0)+, d0 ----------
OPCODE(0xC058)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [c060] and.w -(a0), d0 ----------
OPCODE(0xC060)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [c068] and.w ($3333,a0), d0 ----------
OPCODE(0xC068)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [c070] and.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0xC070)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [c078] and.w $3333.w, d0 ----------
OPCODE(0xC078)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [c079] and.w $33333333.l, d0 ----------
OPCODE(0xC079)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [c07a] and.w ($3333,pc), d0; =3335 ----------
OPCODE(0xC07A)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [c07b] and.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xC07B)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [c07c] and.w #$3333, d0 ----------
OPCODE(0xC07C)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [c05f] and.w (a7)+, d0 ----------
OPCODE(0xC05F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [c067] and.w -(a7), d0 ----------
OPCODE(0xC067)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [c080] and.l d0, d0 ----------
OPCODE(0xC080)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [c090] and.l (a0), d0 ----------
OPCODE(0xC090)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [c098] and.l (a0)+, d0 ----------
OPCODE(0xC098)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [c0a0] and.l -(a0), d0 ----------
OPCODE(0xC0A0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [c0a8] and.l ($3333,a0), d0 ----------
OPCODE(0xC0A8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [c0b0] and.l ($33,a0,d3.w*2), d0 ----------
OPCODE(0xC0B0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [c0b8] and.l $3333.w, d0 ----------
OPCODE(0xC0B8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [c0b9] and.l $33333333.l, d0 ----------
OPCODE(0xC0B9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(22)
}

// ---------- [c0ba] and.l ($3333,pc), d0; =3335 ----------
OPCODE(0xC0BA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [c0bb] and.l ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xC0BB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [c0bc] and.l #$33333333, d0 ----------
OPCODE(0xC0BC)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(16)
}

// ---------- [c09f] and.l (a7)+, d0 ----------
OPCODE(0xC09F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [c0a7] and.l -(a7), d0 ----------
OPCODE(0xC0A7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [c110] and.b d0, (a0) ----------
OPCODE(0xC110)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [c118] and.b d0, (a0)+ ----------
OPCODE(0xC118)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [c120] and.b d0, -(a0) ----------
OPCODE(0xC120)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [c128] and.b d0, ($3333,a0) ----------
OPCODE(0xC128)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [c130] and.b d0, ($33,a0,d3.w*2) ----------
OPCODE(0xC130)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [c138] and.b d0, $3333.w ----------
OPCODE(0xC138)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [c139] and.b d0, $33333333.l ----------
OPCODE(0xC139)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [c11f] and.b d0, (a7)+ ----------
OPCODE(0xC11F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [c127] and.b d0, -(a7) ----------
OPCODE(0xC127)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [c150] and.w d0, (a0) ----------
OPCODE(0xC150)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [c158] and.w d0, (a0)+ ----------
OPCODE(0xC158)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [c160] and.w d0, -(a0) ----------
OPCODE(0xC160)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [c168] and.w d0, ($3333,a0) ----------
OPCODE(0xC168)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [c170] and.w d0, ($33,a0,d3.w*2) ----------
OPCODE(0xC170)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [c178] and.w d0, $3333.w ----------
OPCODE(0xC178)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [c179] and.w d0, $33333333.l ----------
OPCODE(0xC179)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [c15f] and.w d0, (a7)+ ----------
OPCODE(0xC15F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [c167] and.w d0, -(a7) ----------
OPCODE(0xC167)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [c190] and.l d0, (a0) ----------
OPCODE(0xC190)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [c198] and.l d0, (a0)+ ----------
OPCODE(0xC198)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [c1a0] and.l d0, -(a0) ----------
OPCODE(0xC1A0)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [c1a8] and.l d0, ($3333,a0) ----------
OPCODE(0xC1A8)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [c1b0] and.l d0, ($33,a0,d3.w*2) ----------
OPCODE(0xC1B0)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [c1b8] and.l d0, $3333.w ----------
OPCODE(0xC1B8)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [c1b9] and.l d0, $33333333.l ----------
OPCODE(0xC1B9)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [c19f] and.l d0, (a7)+ ----------
OPCODE(0xC19F)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [c1a7] and.l d0, -(a7) ----------
OPCODE(0xC1A7)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [c100] abcd d0, d0 ----------
OPCODE(0xC100)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	dst = DREGu8((Opcode >> 9) & 7);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = (dst & 0xF) + (src & 0xF);
	if (X_FLAG & 0x20000000) res++;
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99) {
		res -= 0xA0;
		flags |= 0x20000000;
	}
	u32 tmp;
	asm volatile("movs %[tmp], %[res], lsl #24\n\t"
		"bicne %[flags], #0x40000000 @ clear Z\n\t"
		"orrmi %[flags], #0x80000000 @ set N"
		:[tmp] "=r" (tmp),[flags] "+r" (flags):[res] "r" (res):"cc");
	X_FLAG = flags;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(6)
}

// ---------- [c108] abcd -(a0), -(a0) ----------
OPCODE(0xC108)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = (dst & 0xF) + (src & 0xF);
	if (X_FLAG & 0x20000000) res++;
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99) {
		res -= 0xA0;
		flags |= 0x20000000;
	}
	u32 tmp;
	asm volatile("movs %[tmp], %[res], lsl #24\n\t"
		"bicne %[flags], #0x40000000 @ clear Z\n\t"
		"orrmi %[flags], #0x80000000 @ set N"
		:[tmp] "=r" (tmp),[flags] "+r" (flags):[res] "r" (res):"cc");
	X_FLAG = flags;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [c10f] abcd -(a7), -(a0) ----------
OPCODE(0xC10F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	dst = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = (dst & 0xF) + (src & 0xF);
	if (X_FLAG & 0x20000000) res++;
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99) {
		res -= 0xA0;
		flags |= 0x20000000;
	}
	u32 tmp;
	asm volatile("movs %[tmp], %[res], lsl #24\n\t"
		"bicne %[flags], #0x40000000 @ clear Z\n\t"
		"orrmi %[flags], #0x80000000 @ set N"
		:[tmp] "=r" (tmp),[flags] "+r" (flags):[res] "r" (res):"cc");
	X_FLAG = flags;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [cf08] abcd -(a0), -(a7) ----------
OPCODE(0xCF08)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	dst = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = (dst & 0xF) + (src & 0xF);
	if (X_FLAG & 0x20000000) res++;
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99) {
		res -= 0xA0;
		flags |= 0x20000000;
	}
	u32 tmp;
	asm volatile("movs %[tmp], %[res], lsl #24\n\t"
		"bicne %[flags], #0x40000000 @ clear Z\n\t"
		"orrmi %[flags], #0x80000000 @ set N"
		:[tmp] "=r" (tmp),[flags] "+r" (flags):[res] "r" (res):"cc");
	X_FLAG = flags;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [cf0f] abcd -(a7), -(a7) ----------
OPCODE(0xCF0F)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	dst = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = (dst & 0xF) + (src & 0xF);
	if (X_FLAG & 0x20000000) res++;
	if (res > 9) res += 6;
	res += (dst & 0xF0) + (src & 0xF0);
	if (res > 0x99) {
		res -= 0xA0;
		flags |= 0x20000000;
	}
	u32 tmp;
	asm volatile("movs %[tmp], %[res], lsl #24\n\t"
		"bicne %[flags], #0x40000000 @ clear Z\n\t"
		"orrmi %[flags], #0x80000000 @ set N"
		:[tmp] "=r" (tmp),[flags] "+r" (flags):[res] "r" (res):"cc");
	X_FLAG = flags;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [c0c0] mulu.w d0, d0 ----------
OPCODE(0xC0C0)
{
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(50)
}

// ---------- [c0d0] mulu.w (a0), d0 ----------
OPCODE(0xC0D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(54)
}

// ---------- [c0d8] mulu.w (a0)+, d0 ----------
OPCODE(0xC0D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(54)
}

// ---------- [c0e0] mulu.w -(a0), d0 ----------
OPCODE(0xC0E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(56)
}

// ---------- [c0e8] mulu.w ($3333,a0), d0 ----------
OPCODE(0xC0E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(58)
}

// ---------- [c0f0] mulu.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0xC0F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(60)
}

// ---------- [c0f8] mulu.w $3333.w, d0 ----------
OPCODE(0xC0F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(58)
}

// ---------- [c0f9] mulu.w $33333333.l, d0 ----------
OPCODE(0xC0F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(62)
}

// ---------- [c0fa] mulu.w ($3333,pc), d0; =3335 ----------
OPCODE(0xC0FA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(58)
}

// ---------- [c0fb] mulu.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xC0FB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(60)
}

// ---------- [c0fc] mulu.w #$3333, d0 ----------
OPCODE(0xC0FC)
{
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(54)
}

// ---------- [c0df] mulu.w (a7)+, d0 ----------
OPCODE(0xC0DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(54)
}

// ---------- [c0e7] mulu.w -(a7), d0 ----------
OPCODE(0xC0E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res *= src;
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(56)
}

// ---------- [c1c0] muls.w d0, d0 ----------
OPCODE(0xC1C0)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs16((Opcode >> 0) & 7);
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(50)
}

// ---------- [c1d0] muls.w (a0), d0 ----------
OPCODE(0xC1D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(54)
}

// ---------- [c1d8] muls.w (a0)+, d0 ----------
OPCODE(0xC1D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(54)
}

// ---------- [c1e0] muls.w -(a0), d0 ----------
OPCODE(0xC1E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(56)
}

// ---------- [c1e8] muls.w ($3333,a0), d0 ----------
OPCODE(0xC1E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(58)
}

// ---------- [c1f0] muls.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0xC1F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(60)
}

// ---------- [c1f8] muls.w $3333.w, d0 ----------
OPCODE(0xC1F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(58)
}

// ---------- [c1f9] muls.w $33333333.l, d0 ----------
OPCODE(0xC1F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(62)
}

// ---------- [c1fa] muls.w ($3333,pc), d0; =3335 ----------
OPCODE(0xC1FA)
{
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(58)
}

// ---------- [c1fb] muls.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xC1FB)
{
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(60)
}

// ---------- [c1fc] muls.w #$3333, d0 ----------
OPCODE(0xC1FC)
{
	u32 adr, res;
	u32 src, dst;

	src = (s32)FETCH_SWORD;
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(54)
}

// ---------- [c1df] muls.w (a7)+, d0 ----------
OPCODE(0xC1DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(54)
}

// ---------- [c1e7] muls.w -(a7), d0 ----------
OPCODE(0xC1E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	res = (s32)DREGs16((Opcode >> 9) & 7);
	res = ((s32)res) * ((s32)src);
	DREGu32((Opcode >> 9) & 7) = res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(56)
}

// ---------- [c140] exg d0, d0 ----------
OPCODE(0xC140)
{
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	src = DREGu32((Opcode >> 9) & 7);
	DREGu32((Opcode >> 9) & 7) = res;
	res = src;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [c148] exg a0, a0 ----------
OPCODE(0xC148)
{
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	src = AREGu32((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) = res;
	res = src;
	AREG((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [c188] exg a0, d0 ----------
OPCODE(0xC188)
{
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	src = DREGu32((Opcode >> 9) & 7);
	DREGu32((Opcode >> 9) & 7) = res;
	res = src;
	AREG((Opcode >> 0) & 7) = res;
	FINISH(6)
}
