
// ---------- [3000] move.w d0, d0 ----------
OPCODE(0x3000)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [3080] move.w d0, (a0) ----------
OPCODE(0x3080)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [30c0] move.w d0, (a0)+ ----------
OPCODE(0x30C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3100] move.w d0, -(a0) ----------
OPCODE(0x3100)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3140] move.w d0, ($3333,a0) ----------
OPCODE(0x3140)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3180] move.w d0, ($33,a0,d3.w*2) ----------
OPCODE(0x3180)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [31c0] move.w d0, $3333.w ----------
OPCODE(0x31C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [33c0] move.w d0, $33333333.l ----------
OPCODE(0x33C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3ec0] move.w d0, (a7)+ ----------
OPCODE(0x3EC0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3f00] move.w d0, -(a7) ----------
OPCODE(0x3F00)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3008] move.w a0, d0 ----------
OPCODE(0x3008)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [3088] move.w a0, (a0) ----------
OPCODE(0x3088)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [30c8] move.w a0, (a0)+ ----------
OPCODE(0x30C8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3108] move.w a0, -(a0) ----------
OPCODE(0x3108)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3148] move.w a0, ($3333,a0) ----------
OPCODE(0x3148)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3188] move.w a0, ($33,a0,d3.w*2) ----------
OPCODE(0x3188)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [31c8] move.w a0, $3333.w ----------
OPCODE(0x31C8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [33c8] move.w a0, $33333333.l ----------
OPCODE(0x33C8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3ec8] move.w a0, (a7)+ ----------
OPCODE(0x3EC8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3f08] move.w a0, -(a7) ----------
OPCODE(0x3F08)
	u32 adr, res;
	u32 src, dst;

	res = AREGu16((Opcode >> 0) & 7);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [3010] move.w (a0), d0 ----------
OPCODE(0x3010)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [3090] move.w (a0), (a0) ----------
OPCODE(0x3090)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [30d0] move.w (a0), (a0)+ ----------
OPCODE(0x30D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3110] move.w (a0), -(a0) ----------
OPCODE(0x3110)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3150] move.w (a0), ($3333,a0) ----------
OPCODE(0x3150)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3190] move.w (a0), ($33,a0,d3.w*2) ----------
OPCODE(0x3190)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [31d0] move.w (a0), $3333.w ----------
OPCODE(0x31D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [33d0] move.w (a0), $33333333.l ----------
OPCODE(0x33D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [3ed0] move.w (a0), (a7)+ ----------
OPCODE(0x3ED0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3f10] move.w (a0), -(a7) ----------
OPCODE(0x3F10)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3018] move.w (a0)+, d0 ----------
OPCODE(0x3018)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [3098] move.w (a0)+, (a0) ----------
OPCODE(0x3098)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [30d8] move.w (a0)+, (a0)+ ----------
OPCODE(0x30D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3118] move.w (a0)+, -(a0) ----------
OPCODE(0x3118)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3158] move.w (a0)+, ($3333,a0) ----------
OPCODE(0x3158)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3198] move.w (a0)+, ($33,a0,d3.w*2) ----------
OPCODE(0x3198)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [31d8] move.w (a0)+, $3333.w ----------
OPCODE(0x31D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [33d8] move.w (a0)+, $33333333.l ----------
OPCODE(0x33D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [3ed8] move.w (a0)+, (a7)+ ----------
OPCODE(0x3ED8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3f18] move.w (a0)+, -(a7) ----------
OPCODE(0x3F18)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3020] move.w -(a0), d0 ----------
OPCODE(0x3020)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [30a0] move.w -(a0), (a0) ----------
OPCODE(0x30A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [30e0] move.w -(a0), (a0)+ ----------
OPCODE(0x30E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3120] move.w -(a0), -(a0) ----------
OPCODE(0x3120)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3160] move.w -(a0), ($3333,a0) ----------
OPCODE(0x3160)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [31a0] move.w -(a0), ($33,a0,d3.w*2) ----------
OPCODE(0x31A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [31e0] move.w -(a0), $3333.w ----------
OPCODE(0x31E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [33e0] move.w -(a0), $33333333.l ----------
OPCODE(0x33E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [3ee0] move.w -(a0), (a7)+ ----------
OPCODE(0x3EE0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3f20] move.w -(a0), -(a7) ----------
OPCODE(0x3F20)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3028] move.w ($3333,a0), d0 ----------
OPCODE(0x3028)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [30a8] move.w ($3333,a0), (a0) ----------
OPCODE(0x30A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [30e8] move.w ($3333,a0), (a0)+ ----------
OPCODE(0x30E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3128] move.w ($3333,a0), -(a0) ----------
OPCODE(0x3128)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3168] move.w ($3333,a0), ($3333,a0) ----------
OPCODE(0x3168)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [31a8] move.w ($3333,a0), ($33,a0,d3.w*2) ----------
OPCODE(0x31A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [31e8] move.w ($3333,a0), $3333.w ----------
OPCODE(0x31E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [33e8] move.w ($3333,a0), $33333333.l ----------
OPCODE(0x33E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [3ee8] move.w ($3333,a0), (a7)+ ----------
OPCODE(0x3EE8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3f28] move.w ($3333,a0), -(a7) ----------
OPCODE(0x3F28)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3030] move.w ($33,a0,d3.w*2), d0 ----------
OPCODE(0x3030)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [30b0] move.w ($33,a0,d3.w*2), (a0) ----------
OPCODE(0x30B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [30f0] move.w ($33,a0,d3.w*2), (a0)+ ----------
OPCODE(0x30F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [3130] move.w ($33,a0,d3.w*2), -(a0) ----------
OPCODE(0x3130)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [3170] move.w ($33,a0,d3.w*2), ($3333,a0) ----------
OPCODE(0x3170)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [31b0] move.w ($33,a0,d3.w*2), ($33,a0,d3.w*2) ----------
OPCODE(0x31B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [31f0] move.w ($33,a0,d3.w*2), $3333.w ----------
OPCODE(0x31F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [33f0] move.w ($33,a0,d3.w*2), $33333333.l ----------
OPCODE(0x33F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [3ef0] move.w ($33,a0,d3.w*2), (a7)+ ----------
OPCODE(0x3EF0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [3f30] move.w ($33,a0,d3.w*2), -(a7) ----------
OPCODE(0x3F30)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [3038] move.w $3333.w, d0 ----------
OPCODE(0x3038)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [30b8] move.w $3333.w, (a0) ----------
OPCODE(0x30B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [30f8] move.w $3333.w, (a0)+ ----------
OPCODE(0x30F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3138] move.w $3333.w, -(a0) ----------
OPCODE(0x3138)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3178] move.w $3333.w, ($3333,a0) ----------
OPCODE(0x3178)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [31b8] move.w $3333.w, ($33,a0,d3.w*2) ----------
OPCODE(0x31B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [31f8] move.w $3333.w, $3333.w ----------
OPCODE(0x31F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [33f8] move.w $3333.w, $33333333.l ----------
OPCODE(0x33F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [3ef8] move.w $3333.w, (a7)+ ----------
OPCODE(0x3EF8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3f38] move.w $3333.w, -(a7) ----------
OPCODE(0x3F38)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3039] move.w $33333333.l, d0 ----------
OPCODE(0x3039)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [30b9] move.w $33333333.l, (a0) ----------
OPCODE(0x30B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [30f9] move.w $33333333.l, (a0)+ ----------
OPCODE(0x30F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [3139] move.w $33333333.l, -(a0) ----------
OPCODE(0x3139)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [3179] move.w $33333333.l, ($3333,a0) ----------
OPCODE(0x3179)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [31b9] move.w $33333333.l, ($33,a0,d3.w*2) ----------
OPCODE(0x31B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [31f9] move.w $33333333.l, $3333.w ----------
OPCODE(0x31F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [33f9] move.w $33333333.l, $33333333.l ----------
OPCODE(0x33F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [3ef9] move.w $33333333.l, (a7)+ ----------
OPCODE(0x3EF9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [3f39] move.w $33333333.l, -(a7) ----------
OPCODE(0x3F39)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [303a] move.w ($3333,pc), d0; =3335 ----------
OPCODE(0x303A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [30ba] move.w ($3333,pc), (a0); =3335 ----------
OPCODE(0x30BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [30fa] move.w ($3333,pc), (a0)+; =3335 ----------
OPCODE(0x30FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [313a] move.w ($3333,pc), -(a0); =3335 ----------
OPCODE(0x313A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [317a] move.w ($3333,pc), ($3333,a0); =3335 ----------
OPCODE(0x317A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [31ba] move.w ($3333,pc), ($33,a0,d3.w*2); =3335 ----------
OPCODE(0x31BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [31fa] move.w ($3333,pc), $3333.w; =3335 ----------
OPCODE(0x31FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [33fa] move.w ($3333,pc), $33333333.l; =3335 ----------
OPCODE(0x33FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [3efa] move.w ($3333,pc), (a7)+; =3335 ----------
OPCODE(0x3EFA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [3f3a] move.w ($3333,pc), -(a7); =3335 ----------
OPCODE(0x3F3A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [303b] move.w ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x303B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [30bb] move.w ($33,pc,d3.w*2), (a0); =35 ----------
OPCODE(0x30BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [30fb] move.w ($33,pc,d3.w*2), (a0)+; =35 ----------
OPCODE(0x30FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [313b] move.w ($33,pc,d3.w*2), -(a0); =35 ----------
OPCODE(0x313B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [317b] move.w ($33,pc,d3.w*2), ($3333,a0); =35 ----------
OPCODE(0x317B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [31bb] move.w ($33,pc,d3.w*2), ($33,a0,d3.w*2); =35 ----------
OPCODE(0x31BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [31fb] move.w ($33,pc,d3.w*2), $3333.w; =35 ----------
OPCODE(0x31FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [33fb] move.w ($33,pc,d3.w*2), $33333333.l; =35 ----------
OPCODE(0x33FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [3efb] move.w ($33,pc,d3.w*2), (a7)+; =35 ----------
OPCODE(0x3EFB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [3f3b] move.w ($33,pc,d3.w*2), -(a7); =35 ----------
OPCODE(0x3F3B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [303c] move.w #$3333, d0 ----------
OPCODE(0x303C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [30bc] move.w #$3333, (a0) ----------
OPCODE(0x30BC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [30fc] move.w #$3333, (a0)+ ----------
OPCODE(0x30FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [313c] move.w #$3333, -(a0) ----------
OPCODE(0x313C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [317c] move.w #$3333, ($3333,a0) ----------
OPCODE(0x317C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [31bc] move.w #$3333, ($33,a0,d3.w*2) ----------
OPCODE(0x31BC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [31fc] move.w #$3333, $3333.w ----------
OPCODE(0x31FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [33fc] move.w #$3333, $33333333.l ----------
OPCODE(0x33FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [3efc] move.w #$3333, (a7)+ ----------
OPCODE(0x3EFC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3f3c] move.w #$3333, -(a7) ----------
OPCODE(0x3F3C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [301f] move.w (a7)+, d0 ----------
OPCODE(0x301F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [309f] move.w (a7)+, (a0) ----------
OPCODE(0x309F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [30df] move.w (a7)+, (a0)+ ----------
OPCODE(0x30DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [311f] move.w (a7)+, -(a0) ----------
OPCODE(0x311F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [315f] move.w (a7)+, ($3333,a0) ----------
OPCODE(0x315F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [319f] move.w (a7)+, ($33,a0,d3.w*2) ----------
OPCODE(0x319F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [31df] move.w (a7)+, $3333.w ----------
OPCODE(0x31DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [33df] move.w (a7)+, $33333333.l ----------
OPCODE(0x33DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [3edf] move.w (a7)+, (a7)+ ----------
OPCODE(0x3EDF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3f1f] move.w (a7)+, -(a7) ----------
OPCODE(0x3F1F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [3027] move.w -(a7), d0 ----------
OPCODE(0x3027)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [30a7] move.w -(a7), (a0) ----------
OPCODE(0x30A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [30e7] move.w -(a7), (a0)+ ----------
OPCODE(0x30E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3127] move.w -(a7), -(a0) ----------
OPCODE(0x3127)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 2;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3167] move.w -(a7), ($3333,a0) ----------
OPCODE(0x3167)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [31a7] move.w -(a7), ($33,a0,d3.w*2) ----------
OPCODE(0x31A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [31e7] move.w -(a7), $3333.w ----------
OPCODE(0x31E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [33e7] move.w -(a7), $33333333.l ----------
OPCODE(0x33E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [3ee7] move.w -(a7), (a7)+ ----------
OPCODE(0x3EE7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3f27] move.w -(a7), -(a7) ----------
OPCODE(0x3F27)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	res = (s32)(s16)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [3040] movea.w d0, a0 ----------
OPCODE(0x3040)
	u32 adr, res;
	u32 src, dst;

	res = (s32)DREGs16((Opcode >> 0) & 7);
	AREG((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [3048] movea.w a0, a0 ----------
OPCODE(0x3048)
	u32 adr, res;
	u32 src, dst;

	res = (s32)(s16)AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [3050] movea.w (a0), a0 ----------
OPCODE(0x3050)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [3058] movea.w (a0)+, a0 ----------
OPCODE(0x3058)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [3060] movea.w -(a0), a0 ----------
OPCODE(0x3060)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [3068] movea.w ($3333,a0), a0 ----------
OPCODE(0x3068)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [3070] movea.w ($33,a0,d3.w*2), a0 ----------
OPCODE(0x3070)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [3078] movea.w $3333.w, a0 ----------
OPCODE(0x3078)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [3079] movea.w $33333333.l, a0 ----------
OPCODE(0x3079)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [307a] movea.w ($3333,pc), a0; =3335 ----------
OPCODE(0x307A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [307b] movea.w ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0x307B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [307c] movea.w #$3333, a0 ----------
OPCODE(0x307C)
	u32 adr, res;
	u32 src, dst;

	res = (s32)FETCH_SWORD;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [305f] movea.w (a7)+, a0 ----------
OPCODE(0x305F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [3067] movea.w -(a7), a0 ----------
OPCODE(0x3067)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READSX_WORD_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}
