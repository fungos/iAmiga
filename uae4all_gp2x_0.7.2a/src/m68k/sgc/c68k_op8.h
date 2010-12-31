
// ---------- [8000] or.b d0, d0 ----------
OPCODE(0x8000)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [8010] or.b (a0), d0 ----------
OPCODE(0x8010)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [8018] or.b (a0)+, d0 ----------
OPCODE(0x8018)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [8020] or.b -(a0), d0 ----------
OPCODE(0x8020)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [8028] or.b ($3333,a0), d0 ----------
OPCODE(0x8028)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [8030] or.b ($33,a0,d3.w*2), d0 ----------
OPCODE(0x8030)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [8038] or.b $3333.w, d0 ----------
OPCODE(0x8038)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [8039] or.b $33333333.l, d0 ----------
OPCODE(0x8039)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [803a] or.b ($3333,pc), d0; =3335 ----------
OPCODE(0x803A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [803b] or.b ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x803B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [803c] or.b #$33, d0 ----------
OPCODE(0x803C)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [801f] or.b (a7)+, d0 ----------
OPCODE(0x801F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [8027] or.b -(a7), d0 ----------
OPCODE(0x8027)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	res = DREGu8((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [8040] or.w d0, d0 ----------
OPCODE(0x8040)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [8050] or.w (a0), d0 ----------
OPCODE(0x8050)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [8058] or.w (a0)+, d0 ----------
OPCODE(0x8058)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [8060] or.w -(a0), d0 ----------
OPCODE(0x8060)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [8068] or.w ($3333,a0), d0 ----------
OPCODE(0x8068)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [8070] or.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0x8070)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [8078] or.w $3333.w, d0 ----------
OPCODE(0x8078)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [8079] or.w $33333333.l, d0 ----------
OPCODE(0x8079)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [807a] or.w ($3333,pc), d0; =3335 ----------
OPCODE(0x807A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [807b] or.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x807B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [807c] or.w #$3333, d0 ----------
OPCODE(0x807C)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [805f] or.w (a7)+, d0 ----------
OPCODE(0x805F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [8067] or.w -(a7), d0 ----------
OPCODE(0x8067)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	res = DREGu16((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [8080] or.l d0, d0 ----------
OPCODE(0x8080)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [8090] or.l (a0), d0 ----------
OPCODE(0x8090)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [8098] or.l (a0)+, d0 ----------
OPCODE(0x8098)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [80a0] or.l -(a0), d0 ----------
OPCODE(0x80A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [80a8] or.l ($3333,a0), d0 ----------
OPCODE(0x80A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [80b0] or.l ($33,a0,d3.w*2), d0 ----------
OPCODE(0x80B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [80b8] or.l $3333.w, d0 ----------
OPCODE(0x80B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [80b9] or.l $33333333.l, d0 ----------
OPCODE(0x80B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(22)
}

// ---------- [80ba] or.l ($3333,pc), d0; =3335 ----------
OPCODE(0x80BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [80bb] or.l ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x80BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [80bc] or.l #$33333333, d0 ----------
OPCODE(0x80BC)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(16)
}

// ---------- [809f] or.l (a7)+, d0 ----------
OPCODE(0x809F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [80a7] or.l -(a7), d0 ----------
OPCODE(0x80A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	res = DREGu32((Opcode >> 9) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [8110] or.b d0, (a0) ----------
OPCODE(0x8110)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [8118] or.b d0, (a0)+ ----------
OPCODE(0x8118)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [8120] or.b d0, -(a0) ----------
OPCODE(0x8120)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [8128] or.b d0, ($3333,a0) ----------
OPCODE(0x8128)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [8130] or.b d0, ($33,a0,d3.w*2) ----------
OPCODE(0x8130)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [8138] or.b d0, $3333.w ----------
OPCODE(0x8138)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [8139] or.b d0, $33333333.l ----------
OPCODE(0x8139)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [811f] or.b d0, (a7)+ ----------
OPCODE(0x811F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [8127] or.b d0, -(a7) ----------
OPCODE(0x8127)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [8150] or.w d0, (a0) ----------
OPCODE(0x8150)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [8158] or.w d0, (a0)+ ----------
OPCODE(0x8158)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [8160] or.w d0, -(a0) ----------
OPCODE(0x8160)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [8168] or.w d0, ($3333,a0) ----------
OPCODE(0x8168)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [8170] or.w d0, ($33,a0,d3.w*2) ----------
OPCODE(0x8170)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [8178] or.w d0, $3333.w ----------
OPCODE(0x8178)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [8179] or.w d0, $33333333.l ----------
OPCODE(0x8179)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [815f] or.w d0, (a7)+ ----------
OPCODE(0x815F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [8167] or.w d0, -(a7) ----------
OPCODE(0x8167)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [8190] or.l d0, (a0) ----------
OPCODE(0x8190)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [8198] or.l d0, (a0)+ ----------
OPCODE(0x8198)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [81a0] or.l d0, -(a0) ----------
OPCODE(0x81A0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [81a8] or.l d0, ($3333,a0) ----------
OPCODE(0x81A8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [81b0] or.l d0, ($33,a0,d3.w*2) ----------
OPCODE(0x81B0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [81b8] or.l d0, $3333.w ----------
OPCODE(0x81B8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [81b9] or.l d0, $33333333.l ----------
OPCODE(0x81B9)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [819f] or.l d0, (a7)+ ----------
OPCODE(0x819F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [81a7] or.l d0, -(a7) ----------
OPCODE(0x81A7)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [8100] sbcd d0, d0 ----------
OPCODE(0x8100)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	dst = DREGu8((Opcode >> 9) & 7);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = (dst & 0xF) - (src & 0xF);
	if (X_FLAG & 0x20000000) res--;
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99) {
		res += 0xA0;
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

// ---------- [8108] sbcd -(a0), -(a0) ----------
OPCODE(0x8108)
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
	res = (dst & 0xF) - (src & 0xF);
	if (X_FLAG & 0x20000000) res--;
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99) {
		res += 0xA0;
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

// ---------- [810f] sbcd -(a7), -(a0) ----------
OPCODE(0x810F)
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
	res = (dst & 0xF) - (src & 0xF);
	if (X_FLAG & 0x20000000) res--;
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99) {
		res += 0xA0;
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

// ---------- [8f08] sbcd -(a0), -(a7) ----------
OPCODE(0x8F08)
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
	res = (dst & 0xF) - (src & 0xF);
	if (X_FLAG & 0x20000000) res--;
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99) {
		res += 0xA0;
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

// ---------- [8f0f] sbcd -(a7), -(a7) ----------
OPCODE(0x8F0F)
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
	res = (dst & 0xF) - (src & 0xF);
	if (X_FLAG & 0x20000000) res--;
	if (res > 9) res -= 6;
	res += (dst & 0xF0) - (src & 0xF0);
	if (res > 0x99) {
		res += 0xA0;
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

// ---------- [80c0] divu.w d0, d0 ----------
OPCODE(0x80C0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	FINISH(10)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(70)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(90)
}

// ---------- [80d0] divu.w (a0), d0 ----------
OPCODE(0x80D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(74)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(94)
}

// ---------- [80d8] divu.w (a0)+, d0 ----------
OPCODE(0x80D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(74)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(94)
}

// ---------- [80e0] divu.w -(a0), d0 ----------
OPCODE(0x80E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(16)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(76)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(96)
}

// ---------- [80e8] divu.w ($3333,a0), d0 ----------
OPCODE(0x80E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(18)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(78)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(98)
}

// ---------- [80f0] divu.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0x80F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(20)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(80)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(100)
}

// ---------- [80f8] divu.w $3333.w, d0 ----------
OPCODE(0x80F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(18)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(78)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(98)
}

// ---------- [80f9] divu.w $33333333.l, d0 ----------
OPCODE(0x80F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(22)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(82)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(102)
}

// ---------- [80fa] divu.w ($3333,pc), d0; =3335 ----------
OPCODE(0x80FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(18)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(78)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(98)
}

// ---------- [80fb] divu.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x80FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(20)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(80)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(100)
}

// ---------- [80fc] divu.w #$3333, d0 ----------
OPCODE(0x80FC)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(74)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(94)
}

// ---------- [80df] divu.w (a7)+, d0 ----------
OPCODE(0x80DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(74)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(94)
}

// ---------- [80e7] divu.w -(a7), d0 ----------
OPCODE(0x80E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(16)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	{
		u32 q, r;

		q = dst / src;
		r = dst % src;

		if (q >> 16) {
			flags |= 0x10000000;
	FINISH(76)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(96)
}

// ---------- [81c0] divs.w d0, d0 ----------
OPCODE(0x81C0)
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs16((Opcode >> 0) & 7);
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	FINISH(10)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(50)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(80)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(108)
}

// ---------- [81d0] divs.w (a0), d0 ----------
OPCODE(0x81D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(54)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(84)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(112)
}

// ---------- [81d8] divs.w (a0)+, d0 ----------
OPCODE(0x81D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(54)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(84)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(112)
}

// ---------- [81e0] divs.w -(a0), d0 ----------
OPCODE(0x81E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(16)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(56)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(86)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(114)
}

// ---------- [81e8] divs.w ($3333,a0), d0 ----------
OPCODE(0x81E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(18)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(58)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(88)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(116)
}

// ---------- [81f0] divs.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0x81F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(20)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(60)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(90)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(118)
}

// ---------- [81f8] divs.w $3333.w, d0 ----------
OPCODE(0x81F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(18)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(58)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(88)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(116)
}

// ---------- [81f9] divs.w $33333333.l, d0 ----------
OPCODE(0x81F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(22)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(62)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(92)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(120)
}

// ---------- [81fa] divs.w ($3333,pc), d0; =3335 ----------
OPCODE(0x81FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(18)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(58)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(88)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(116)
}

// ---------- [81fb] divs.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x81FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(20)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(60)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(90)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(118)
}

// ---------- [81fc] divs.w #$3333, d0 ----------
OPCODE(0x81FC)
	u32 adr, res;
	u32 src, dst;

	src = (s32)FETCH_SWORD;
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(54)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(84)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(112)
}

// ---------- [81df] divs.w (a7)+, d0 ----------
OPCODE(0x81DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(14)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(54)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(84)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(112)
}

// ---------- [81e7] divs.w -(a7), d0 ----------
OPCODE(0x81E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	if (src == 0) {
		execute_exception(M68K_ZERO_DIVIDE_EX);
	POST_IO
	FINISH(16)
	}
	dst = DREGu32((Opcode >> 9) & 7);
	if ((dst == 0x80000000) && (src == -1)) {
		flags = 0;
		res = 0;
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(56)
	}
	{
		s32 q, r;

		q = (s32)dst / (s32)src;
		r = (s32)dst % (s32)src;

		if ((q > 0x7FFF) || (q < -0x8000)) {
			flags |= 0x10000000;
	FINISH(86)
		}
		q &= 0x0000FFFF;
		res = q << 16;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
		res = q | (r << 16);
	DREGu32((Opcode >> 9) & 7) = res;
	}
	FINISH(114)
}
