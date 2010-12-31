
// ---------- [2000] move.l d0, d0 ----------
OPCODE(0x2000)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [2080] move.l d0, (a0) ----------
OPCODE(0x2080)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [20c0] move.l d0, (a0)+ ----------
OPCODE(0x20C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2100] move.l d0, -(a0) ----------
OPCODE(0x2100)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2140] move.l d0, ($3333,a0) ----------
OPCODE(0x2140)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [2180] move.l d0, ($33,a0,d3.w*2) ----------
OPCODE(0x2180)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [21c0] move.l d0, $3333.w ----------
OPCODE(0x21C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [23c0] move.l d0, $33333333.l ----------
OPCODE(0x23C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2ec0] move.l d0, (a7)+ ----------
OPCODE(0x2EC0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2f00] move.l d0, -(a7) ----------
OPCODE(0x2F00)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2008] move.l a0, d0 ----------
OPCODE(0x2008)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [2088] move.l a0, (a0) ----------
OPCODE(0x2088)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [20c8] move.l a0, (a0)+ ----------
OPCODE(0x20C8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2108] move.l a0, -(a0) ----------
OPCODE(0x2108)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2148] move.l a0, ($3333,a0) ----------
OPCODE(0x2148)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [2188] move.l a0, ($33,a0,d3.w*2) ----------
OPCODE(0x2188)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [21c8] move.l a0, $3333.w ----------
OPCODE(0x21C8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [23c8] move.l a0, $33333333.l ----------
OPCODE(0x23C8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2ec8] move.l a0, (a7)+ ----------
OPCODE(0x2EC8)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2f08] move.l a0, -(a7) ----------
OPCODE(0x2F08)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [2010] move.l (a0), d0 ----------
OPCODE(0x2010)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [2090] move.l (a0), (a0) ----------
OPCODE(0x2090)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [20d0] move.l (a0), (a0)+ ----------
OPCODE(0x20D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2110] move.l (a0), -(a0) ----------
OPCODE(0x2110)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2150] move.l (a0), ($3333,a0) ----------
OPCODE(0x2150)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2190] move.l (a0), ($33,a0,d3.w*2) ----------
OPCODE(0x2190)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [21d0] move.l (a0), $3333.w ----------
OPCODE(0x21D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [23d0] move.l (a0), $33333333.l ----------
OPCODE(0x23D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [2ed0] move.l (a0), (a7)+ ----------
OPCODE(0x2ED0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2f10] move.l (a0), -(a7) ----------
OPCODE(0x2F10)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2018] move.l (a0)+, d0 ----------
OPCODE(0x2018)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [2098] move.l (a0)+, (a0) ----------
OPCODE(0x2098)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [20d8] move.l (a0)+, (a0)+ ----------
OPCODE(0x20D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2118] move.l (a0)+, -(a0) ----------
OPCODE(0x2118)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2158] move.l (a0)+, ($3333,a0) ----------
OPCODE(0x2158)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2198] move.l (a0)+, ($33,a0,d3.w*2) ----------
OPCODE(0x2198)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [21d8] move.l (a0)+, $3333.w ----------
OPCODE(0x21D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [23d8] move.l (a0)+, $33333333.l ----------
OPCODE(0x23D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [2ed8] move.l (a0)+, (a7)+ ----------
OPCODE(0x2ED8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2f18] move.l (a0)+, -(a7) ----------
OPCODE(0x2F18)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2020] move.l -(a0), d0 ----------
OPCODE(0x2020)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [20a0] move.l -(a0), (a0) ----------
OPCODE(0x20A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [20e0] move.l -(a0), (a0)+ ----------
OPCODE(0x20E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2120] move.l -(a0), -(a0) ----------
OPCODE(0x2120)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2160] move.l -(a0), ($3333,a0) ----------
OPCODE(0x2160)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [21a0] move.l -(a0), ($33,a0,d3.w*2) ----------
OPCODE(0x21A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [21e0] move.l -(a0), $3333.w ----------
OPCODE(0x21E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [23e0] move.l -(a0), $33333333.l ----------
OPCODE(0x23E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [2ee0] move.l -(a0), (a7)+ ----------
OPCODE(0x2EE0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2f20] move.l -(a0), -(a7) ----------
OPCODE(0x2F20)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2028] move.l ($3333,a0), d0 ----------
OPCODE(0x2028)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [20a8] move.l ($3333,a0), (a0) ----------
OPCODE(0x20A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [20e8] move.l ($3333,a0), (a0)+ ----------
OPCODE(0x20E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2128] move.l ($3333,a0), -(a0) ----------
OPCODE(0x2128)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2168] move.l ($3333,a0), ($3333,a0) ----------
OPCODE(0x2168)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [21a8] move.l ($3333,a0), ($33,a0,d3.w*2) ----------
OPCODE(0x21A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [21e8] move.l ($3333,a0), $3333.w ----------
OPCODE(0x21E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [23e8] move.l ($3333,a0), $33333333.l ----------
OPCODE(0x23E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(32)
}

// ---------- [2ee8] move.l ($3333,a0), (a7)+ ----------
OPCODE(0x2EE8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2f28] move.l ($3333,a0), -(a7) ----------
OPCODE(0x2F28)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2030] move.l ($33,a0,d3.w*2), d0 ----------
OPCODE(0x2030)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [20b0] move.l ($33,a0,d3.w*2), (a0) ----------
OPCODE(0x20B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [20f0] move.l ($33,a0,d3.w*2), (a0)+ ----------
OPCODE(0x20F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [2130] move.l ($33,a0,d3.w*2), -(a0) ----------
OPCODE(0x2130)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [2170] move.l ($33,a0,d3.w*2), ($3333,a0) ----------
OPCODE(0x2170)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [21b0] move.l ($33,a0,d3.w*2), ($33,a0,d3.w*2) ----------
OPCODE(0x21B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(32)
}

// ---------- [21f0] move.l ($33,a0,d3.w*2), $3333.w ----------
OPCODE(0x21F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [23f0] move.l ($33,a0,d3.w*2), $33333333.l ----------
OPCODE(0x23F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(34)
}

// ---------- [2ef0] move.l ($33,a0,d3.w*2), (a7)+ ----------
OPCODE(0x2EF0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [2f30] move.l ($33,a0,d3.w*2), -(a7) ----------
OPCODE(0x2F30)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [2038] move.l $3333.w, d0 ----------
OPCODE(0x2038)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [20b8] move.l $3333.w, (a0) ----------
OPCODE(0x20B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [20f8] move.l $3333.w, (a0)+ ----------
OPCODE(0x20F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2138] move.l $3333.w, -(a0) ----------
OPCODE(0x2138)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2178] move.l $3333.w, ($3333,a0) ----------
OPCODE(0x2178)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [21b8] move.l $3333.w, ($33,a0,d3.w*2) ----------
OPCODE(0x21B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [21f8] move.l $3333.w, $3333.w ----------
OPCODE(0x21F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [23f8] move.l $3333.w, $33333333.l ----------
OPCODE(0x23F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(32)
}

// ---------- [2ef8] move.l $3333.w, (a7)+ ----------
OPCODE(0x2EF8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2f38] move.l $3333.w, -(a7) ----------
OPCODE(0x2F38)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2039] move.l $33333333.l, d0 ----------
OPCODE(0x2039)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [20b9] move.l $33333333.l, (a0) ----------
OPCODE(0x20B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [20f9] move.l $33333333.l, (a0)+ ----------
OPCODE(0x20F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [2139] move.l $33333333.l, -(a0) ----------
OPCODE(0x2139)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [2179] move.l $33333333.l, ($3333,a0) ----------
OPCODE(0x2179)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(32)
}

// ---------- [21b9] move.l $33333333.l, ($33,a0,d3.w*2) ----------
OPCODE(0x21B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(34)
}

// ---------- [21f9] move.l $33333333.l, $3333.w ----------
OPCODE(0x21F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(32)
}

// ---------- [23f9] move.l $33333333.l, $33333333.l ----------
OPCODE(0x23F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(36)
}

// ---------- [2ef9] move.l $33333333.l, (a7)+ ----------
OPCODE(0x2EF9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [2f39] move.l $33333333.l, -(a7) ----------
OPCODE(0x2F39)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [203a] move.l ($3333,pc), d0; =3335 ----------
OPCODE(0x203A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [20ba] move.l ($3333,pc), (a0); =3335 ----------
OPCODE(0x20BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [20fa] move.l ($3333,pc), (a0)+; =3335 ----------
OPCODE(0x20FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [213a] move.l ($3333,pc), -(a0); =3335 ----------
OPCODE(0x213A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [217a] move.l ($3333,pc), ($3333,a0); =3335 ----------
OPCODE(0x217A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [21ba] move.l ($3333,pc), ($33,a0,d3.w*2); =3335 ----------
OPCODE(0x21BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [21fa] move.l ($3333,pc), $3333.w; =3335 ----------
OPCODE(0x21FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [23fa] move.l ($3333,pc), $33333333.l; =3335 ----------
OPCODE(0x23FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(32)
}

// ---------- [2efa] move.l ($3333,pc), (a7)+; =3335 ----------
OPCODE(0x2EFA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [2f3a] move.l ($3333,pc), -(a7); =3335 ----------
OPCODE(0x2F3A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [203b] move.l ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x203B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [20bb] move.l ($33,pc,d3.w*2), (a0); =35 ----------
OPCODE(0x20BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [20fb] move.l ($33,pc,d3.w*2), (a0)+; =35 ----------
OPCODE(0x20FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [213b] move.l ($33,pc,d3.w*2), -(a0); =35 ----------
OPCODE(0x213B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [217b] move.l ($33,pc,d3.w*2), ($3333,a0); =35 ----------
OPCODE(0x217B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [21bb] move.l ($33,pc,d3.w*2), ($33,a0,d3.w*2); =35 ----------
OPCODE(0x21BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(32)
}

// ---------- [21fb] move.l ($33,pc,d3.w*2), $3333.w; =35 ----------
OPCODE(0x21FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [23fb] move.l ($33,pc,d3.w*2), $33333333.l; =35 ----------
OPCODE(0x23FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(34)
}

// ---------- [2efb] move.l ($33,pc,d3.w*2), (a7)+; =35 ----------
OPCODE(0x2EFB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [2f3b] move.l ($33,pc,d3.w*2), -(a7); =35 ----------
OPCODE(0x2F3B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [203c] move.l #$33333333, d0 ----------
OPCODE(0x203C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(12)
}

// ---------- [20bc] move.l #$33333333, (a0) ----------
OPCODE(0x20BC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [20fc] move.l #$33333333, (a0)+ ----------
OPCODE(0x20FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [213c] move.l #$33333333, -(a0) ----------
OPCODE(0x213C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [217c] move.l #$33333333, ($3333,a0) ----------
OPCODE(0x217C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [21bc] move.l #$33333333, ($33,a0,d3.w*2) ----------
OPCODE(0x21BC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [21fc] move.l #$33333333, $3333.w ----------
OPCODE(0x21FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [23fc] move.l #$33333333, $33333333.l ----------
OPCODE(0x23FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [2efc] move.l #$33333333, (a7)+ ----------
OPCODE(0x2EFC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2f3c] move.l #$33333333, -(a7) ----------
OPCODE(0x2F3C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [201f] move.l (a7)+, d0 ----------
OPCODE(0x201F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [209f] move.l (a7)+, (a0) ----------
OPCODE(0x209F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [20df] move.l (a7)+, (a0)+ ----------
OPCODE(0x20DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [211f] move.l (a7)+, -(a0) ----------
OPCODE(0x211F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [215f] move.l (a7)+, ($3333,a0) ----------
OPCODE(0x215F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [219f] move.l (a7)+, ($33,a0,d3.w*2) ----------
OPCODE(0x219F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [21df] move.l (a7)+, $3333.w ----------
OPCODE(0x21DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [23df] move.l (a7)+, $33333333.l ----------
OPCODE(0x23DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [2edf] move.l (a7)+, (a7)+ ----------
OPCODE(0x2EDF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2f1f] move.l (a7)+, -(a7) ----------
OPCODE(0x2F1F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [2027] move.l -(a7), d0 ----------
OPCODE(0x2027)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [20a7] move.l -(a7), (a0) ----------
OPCODE(0x20A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [20e7] move.l -(a7), (a0)+ ----------
OPCODE(0x20E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2127] move.l -(a7), -(a0) ----------
OPCODE(0x2127)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 4;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2167] move.l -(a7), ($3333,a0) ----------
OPCODE(0x2167)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [21a7] move.l -(a7), ($33,a0,d3.w*2) ----------
OPCODE(0x21A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [21e7] move.l -(a7), $3333.w ----------
OPCODE(0x21E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [23e7] move.l -(a7), $33333333.l ----------
OPCODE(0x23E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(30)
}

// ---------- [2ee7] move.l -(a7), (a7)+ ----------
OPCODE(0x2EE7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 4;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2f27] move.l -(a7), -(a7) ----------
OPCODE(0x2F27)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	res = (s32)(s32)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 4;
	AREG(7) = adr;
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [2040] movea.l d0, a0 ----------
OPCODE(0x2040)
	u32 adr, res;
	u32 src, dst;

	res = (s32)DREGs32((Opcode >> 0) & 7);
	AREG((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [2048] movea.l a0, a0 ----------
OPCODE(0x2048)
	u32 adr, res;
	u32 src, dst;

	res = (s32)(s32)AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [2050] movea.l (a0), a0 ----------
OPCODE(0x2050)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [2058] movea.l (a0)+, a0 ----------
OPCODE(0x2058)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [2060] movea.l -(a0), a0 ----------
OPCODE(0x2060)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [2068] movea.l ($3333,a0), a0 ----------
OPCODE(0x2068)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [2070] movea.l ($33,a0,d3.w*2), a0 ----------
OPCODE(0x2070)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [2078] movea.l $3333.w, a0 ----------
OPCODE(0x2078)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [2079] movea.l $33333333.l, a0 ----------
OPCODE(0x2079)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(20)
}

// ---------- [207a] movea.l ($3333,pc), a0; =3335 ----------
OPCODE(0x207A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [207b] movea.l ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0x207B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(18)
}

// ---------- [207c] movea.l #$33333333, a0 ----------
OPCODE(0x207C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_LONG;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(12)
}

// ---------- [205f] movea.l (a7)+, a0 ----------
OPCODE(0x205F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [2067] movea.l -(a7), a0 ----------
OPCODE(0x2067)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READSX_LONG_F(adr)
	AREG((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}
