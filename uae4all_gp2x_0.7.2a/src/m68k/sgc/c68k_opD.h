
// ---------- [d000] add.b d0, d0 ----------
OPCODE(0xD000)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [d008] add.b a0, d0 ----------
OPCODE(0xD008)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
*/
	FINISH(4)
}

// ---------- [d010] add.b (a0), d0 ----------
OPCODE(0xD010)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [d018] add.b (a0)+, d0 ----------
OPCODE(0xD018)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [d020] add.b -(a0), d0 ----------
OPCODE(0xD020)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [d028] add.b ($3333,a0), d0 ----------
OPCODE(0xD028)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d030] add.b ($33,a0,d3.w*2), d0 ----------
OPCODE(0xD030)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d038] add.b $3333.w, d0 ----------
OPCODE(0xD038)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d039] add.b $33333333.l, d0 ----------
OPCODE(0xD039)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [d03a] add.b ($3333,pc), d0; =3335 ----------
OPCODE(0xD03A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d03b] add.b ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xD03B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d03c] add.b #$33, d0 ----------
OPCODE(0xD03C)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [d01f] add.b (a7)+, d0 ----------
OPCODE(0xD01F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [d027] add.b -(a7), d0 ----------
OPCODE(0xD027)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [d040] add.w d0, d0 ----------
OPCODE(0xD040)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [d048] add.w a0, d0 ----------
OPCODE(0xD048)
	u32 adr, res;
	u32 src, dst;

	src = AREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [d050] add.w (a0), d0 ----------
OPCODE(0xD050)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [d058] add.w (a0)+, d0 ----------
OPCODE(0xD058)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [d060] add.w -(a0), d0 ----------
OPCODE(0xD060)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [d068] add.w ($3333,a0), d0 ----------
OPCODE(0xD068)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d070] add.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0xD070)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d078] add.w $3333.w, d0 ----------
OPCODE(0xD078)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d079] add.w $33333333.l, d0 ----------
OPCODE(0xD079)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [d07a] add.w ($3333,pc), d0; =3335 ----------
OPCODE(0xD07A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d07b] add.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xD07B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d07c] add.w #$3333, d0 ----------
OPCODE(0xD07C)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [d05f] add.w (a7)+, d0 ----------
OPCODE(0xD05F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [d067] add.w -(a7), d0 ----------
OPCODE(0xD067)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [d080] add.l d0, d0 ----------
OPCODE(0xD080)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [d088] add.l a0, d0 ----------
OPCODE(0xD088)
	u32 adr, res;
	u32 src, dst;

	src = AREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [d090] add.l (a0), d0 ----------
OPCODE(0xD090)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d098] add.l (a0)+, d0 ----------
OPCODE(0xD098)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d0a0] add.l -(a0), d0 ----------
OPCODE(0xD0A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [d0a8] add.l ($3333,a0), d0 ----------
OPCODE(0xD0A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [d0b0] add.l ($33,a0,d3.w*2), d0 ----------
OPCODE(0xD0B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [d0b8] add.l $3333.w, d0 ----------
OPCODE(0xD0B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [d0b9] add.l $33333333.l, d0 ----------
OPCODE(0xD0B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(22)
}

// ---------- [d0ba] add.l ($3333,pc), d0; =3335 ----------
OPCODE(0xD0BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [d0bb] add.l ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0xD0BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [d0bc] add.l #$33333333, d0 ----------
OPCODE(0xD0BC)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(16)
}

// ---------- [d09f] add.l (a7)+, d0 ----------
OPCODE(0xD09F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d0a7] add.l -(a7), d0 ----------
OPCODE(0xD0A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [d110] add.b d0, (a0) ----------
OPCODE(0xD110)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [d118] add.b d0, (a0)+ ----------
OPCODE(0xD118)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [d120] add.b d0, -(a0) ----------
OPCODE(0xD120)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [d128] add.b d0, ($3333,a0) ----------
OPCODE(0xD128)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [d130] add.b d0, ($33,a0,d3.w*2) ----------
OPCODE(0xD130)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [d138] add.b d0, $3333.w ----------
OPCODE(0xD138)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [d139] add.b d0, $33333333.l ----------
OPCODE(0xD139)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [d11f] add.b d0, (a7)+ ----------
OPCODE(0xD11F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [d127] add.b d0, -(a7) ----------
OPCODE(0xD127)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [d150] add.w d0, (a0) ----------
OPCODE(0xD150)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [d158] add.w d0, (a0)+ ----------
OPCODE(0xD158)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [d160] add.w d0, -(a0) ----------
OPCODE(0xD160)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [d168] add.w d0, ($3333,a0) ----------
OPCODE(0xD168)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [d170] add.w d0, ($33,a0,d3.w*2) ----------
OPCODE(0xD170)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [d178] add.w d0, $3333.w ----------
OPCODE(0xD178)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [d179] add.w d0, $33333333.l ----------
OPCODE(0xD179)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [d15f] add.w d0, (a7)+ ----------
OPCODE(0xD15F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [d167] add.w d0, -(a7) ----------
OPCODE(0xD167)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 9) & 7);
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [d190] add.l d0, (a0) ----------
OPCODE(0xD190)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [d198] add.l d0, (a0)+ ----------
OPCODE(0xD198)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [d1a0] add.l d0, -(a0) ----------
OPCODE(0xD1A0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [d1a8] add.l d0, ($3333,a0) ----------
OPCODE(0xD1A8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [d1b0] add.l d0, ($33,a0,d3.w*2) ----------
OPCODE(0xD1B0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [d1b8] add.l d0, $3333.w ----------
OPCODE(0xD1B8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [d1b9] add.l d0, $33333333.l ----------
OPCODE(0xD1B9)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [d19f] add.l d0, (a7)+ ----------
OPCODE(0xD19F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [d1a7] add.l d0, -(a7) ----------
OPCODE(0xD1A7)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [d100] addx.b d0, d0 ----------
OPCODE(0xD100)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	dst = DREGu8((Opcode >> 9) & 7);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #8  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("adcs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d140] addx.w d0, d0 ----------
OPCODE(0xD140)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	dst = DREGu16((Opcode >> 9) & 7);
	u32 mask = ~0;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"orr %[src], %[src], %[mask], lsr #16  @ pad with F's to ensure carry is used"
		: [src] "+r" (src) : [x_flag] "r" (X_FLAG), [mask] "r" (mask) : "cc");
	asm volatile("adcs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d180] addx.l d0, d0 ----------
OPCODE(0xD180)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	dst = DREGu32((Opcode >> 9) & 7);
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		:: [x_flag] "r" (X_FLAG) : "cc");
	asm volatile("adcs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	u32 tmp2;
	asm volatile("movs %[tmp2], %[res]\n\t"
		"orreq %[flags], %[flags], #0x40000000\n\t"
		"andeq %[flags], %[flags], %[save_z]"
		:[tmp2] "=r" (tmp2), [flags] "+r" (flags): [save_z] "r" (save_z), [res] "r" (res): "cc");
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [d108] addx.b -(a0), -(a0) ----------
OPCODE(0xD108)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d148] addx.w -(a0), -(a0) ----------
OPCODE(0xD148)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d188] addx.l -(a0), -(a0) ----------
OPCODE(0xD188)
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
	asm volatile("adcs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d10f] addx.b -(a7), -(a0) ----------
OPCODE(0xD10F)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d14f] addx.w -(a7), -(a0) ----------
OPCODE(0xD14F)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d18f] addx.l -(a7), -(a0) ----------
OPCODE(0xD18F)
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
	asm volatile("adcs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [df08] addx.b -(a0), -(a7) ----------
OPCODE(0xDF08)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [df48] addx.w -(a0), -(a7) ----------
OPCODE(0xDF48)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [df88] addx.l -(a0), -(a7) ----------
OPCODE(0xDF88)
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
	asm volatile("adcs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [df0f] addx.b -(a7), -(a7) ----------
OPCODE(0xDF0F)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [df4f] addx.w -(a7), -(a7) ----------
OPCODE(0xDF4F)
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
	asm volatile("adcs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [df8f] addx.l -(a7), -(a7) ----------
OPCODE(0xDF8F)
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
	asm volatile("adcs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	u32 save_z = flags | 0xb0000000;
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
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

// ---------- [d0c0] adda.w d0, a0 ----------
OPCODE(0xD0C0)
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs16((Opcode >> 0) & 7);
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [d0c8] adda.w a0, a0 ----------
OPCODE(0xD0C8)
	u32 adr, res;
	u32 src, dst;

	src = (s32)(s16)AREG((Opcode >> 0) & 7);
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [d0d0] adda.w (a0), a0 ----------
OPCODE(0xD0D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [d0d8] adda.w (a0)+, a0 ----------
OPCODE(0xD0D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [d0e0] adda.w -(a0), a0 ----------
OPCODE(0xD0E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d0e8] adda.w ($3333,a0), a0 ----------
OPCODE(0xD0E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d0f0] adda.w ($33,a0,d3.w*2), a0 ----------
OPCODE(0xD0F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [d0f8] adda.w $3333.w, a0 ----------
OPCODE(0xD0F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d0f9] adda.w $33333333.l, a0 ----------
OPCODE(0xD0F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [d0fa] adda.w ($3333,pc), a0; =3335 ----------
OPCODE(0xD0FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d0fb] adda.w ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0xD0FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [d0fc] adda.w #$3333, a0 ----------
OPCODE(0xD0FC)
	u32 adr, res;
	u32 src, dst;

	src = (s32)FETCH_SWORD;
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(12)
}

// ---------- [d0df] adda.w (a7)+, a0 ----------
OPCODE(0xD0DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [d0e7] adda.w -(a7), a0 ----------
OPCODE(0xD0E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READSX_WORD_F(adr)
	src <<= 16;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src], asr #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [d1c0] adda.l d0, a0 ----------
OPCODE(0xD1C0)
	u32 adr, res;
	u32 src, dst;

	src = (s32)DREGs32((Opcode >> 0) & 7);
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(6)
}

// ---------- [d1c8] adda.l a0, a0 ----------
OPCODE(0xD1C8)
	u32 adr, res;
	u32 src, dst;

	src = (s32)(s32)AREG((Opcode >> 0) & 7);
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(6)
}

// ---------- [d1d0] adda.l (a0), a0 ----------
OPCODE(0xD1D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d1d8] adda.l (a0)+, a0 ----------
OPCODE(0xD1D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d1e0] adda.l -(a0), a0 ----------
OPCODE(0xD1E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [d1e8] adda.l ($3333,a0), a0 ----------
OPCODE(0xD1E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [d1f0] adda.l ($33,a0,d3.w*2), a0 ----------
OPCODE(0xD1F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [d1f8] adda.l $3333.w, a0 ----------
OPCODE(0xD1F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [d1f9] adda.l $33333333.l, a0 ----------
OPCODE(0xD1F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(22)
}

// ---------- [d1fa] adda.l ($3333,pc), a0; =3335 ----------
OPCODE(0xD1FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [d1fb] adda.l ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0xD1FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [d1fc] adda.l #$33333333, a0 ----------
OPCODE(0xD1FC)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_LONG;
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	FINISH(14)
}

// ---------- [d1df] adda.l (a7)+, a0 ----------
OPCODE(0xD1DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [d1e7] adda.l -(a7), a0 ----------
OPCODE(0xD1E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READSX_LONG_F(adr)
	dst = AREGu32((Opcode >> 9) & 7);
	asm volatile("add %[res], %[dst], %[src] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}
