
// ---------- [1000] move.b d0, d0 ----------
OPCODE(0x1000)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [1080] move.b d0, (a0) ----------
OPCODE(0x1080)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [10c0] move.b d0, (a0)+ ----------
OPCODE(0x10C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [1100] move.b d0, -(a0) ----------
OPCODE(0x1100)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [1140] move.b d0, ($3333,a0) ----------
OPCODE(0x1140)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1180] move.b d0, ($33,a0,d3.w*2) ----------
OPCODE(0x1180)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [11c0] move.b d0, $3333.w ----------
OPCODE(0x11C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [13c0] move.b d0, $33333333.l ----------
OPCODE(0x13C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1ec0] move.b d0, (a7)+ ----------
OPCODE(0x1EC0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [1f00] move.b d0, -(a7) ----------
OPCODE(0x1F00)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(8)
}

// ---------- [1008] move.b a0, d0 ----------
OPCODE(0x1008)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
*/
	FINISH(4)
}

// ---------- [1088] move.b a0, (a0) ----------
OPCODE(0x1088)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(8)
}

// ---------- [10c8] move.b a0, (a0)+ ----------
OPCODE(0x10C8)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(8)
}

// ---------- [1108] move.b a0, -(a0) ----------
OPCODE(0x1108)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(8)
}

// ---------- [1148] move.b a0, ($3333,a0) ----------
OPCODE(0x1148)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(12)
}

// ---------- [1188] move.b a0, ($33,a0,d3.w*2) ----------
OPCODE(0x1188)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(14)
}

// ---------- [11c8] move.b a0, $3333.w ----------
OPCODE(0x11C8)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(12)
}

// ---------- [13c8] move.b a0, $33333333.l ----------
OPCODE(0x13C8)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(16)
}

// ---------- [1ec8] move.b a0, (a7)+ ----------
OPCODE(0x1EC8)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(8)
}

// ---------- [1f08] move.b a0, -(a7) ----------
OPCODE(0x1F08)
	u32 adr, res;
	u32 src, dst;

	// can't read byte from Ax registers !
	EXECINFO |= M68K_FAULTED;
	cycles = 0;
/*
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
*/
	FINISH(8)
}

// ---------- [1010] move.b (a0), d0 ----------
OPCODE(0x1010)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [1090] move.b (a0), (a0) ----------
OPCODE(0x1090)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [10d0] move.b (a0), (a0)+ ----------
OPCODE(0x10D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1110] move.b (a0), -(a0) ----------
OPCODE(0x1110)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1150] move.b (a0), ($3333,a0) ----------
OPCODE(0x1150)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1190] move.b (a0), ($33,a0,d3.w*2) ----------
OPCODE(0x1190)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [11d0] move.b (a0), $3333.w ----------
OPCODE(0x11D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [13d0] move.b (a0), $33333333.l ----------
OPCODE(0x13D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [1ed0] move.b (a0), (a7)+ ----------
OPCODE(0x1ED0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1f10] move.b (a0), -(a7) ----------
OPCODE(0x1F10)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1018] move.b (a0)+, d0 ----------
OPCODE(0x1018)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [1098] move.b (a0)+, (a0) ----------
OPCODE(0x1098)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [10d8] move.b (a0)+, (a0)+ ----------
OPCODE(0x10D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1118] move.b (a0)+, -(a0) ----------
OPCODE(0x1118)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1158] move.b (a0)+, ($3333,a0) ----------
OPCODE(0x1158)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1198] move.b (a0)+, ($33,a0,d3.w*2) ----------
OPCODE(0x1198)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [11d8] move.b (a0)+, $3333.w ----------
OPCODE(0x11D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [13d8] move.b (a0)+, $33333333.l ----------
OPCODE(0x13D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [1ed8] move.b (a0)+, (a7)+ ----------
OPCODE(0x1ED8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1f18] move.b (a0)+, -(a7) ----------
OPCODE(0x1F18)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1020] move.b -(a0), d0 ----------
OPCODE(0x1020)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [10a0] move.b -(a0), (a0) ----------
OPCODE(0x10A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [10e0] move.b -(a0), (a0)+ ----------
OPCODE(0x10E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [1120] move.b -(a0), -(a0) ----------
OPCODE(0x1120)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [1160] move.b -(a0), ($3333,a0) ----------
OPCODE(0x1160)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [11a0] move.b -(a0), ($33,a0,d3.w*2) ----------
OPCODE(0x11A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [11e0] move.b -(a0), $3333.w ----------
OPCODE(0x11E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [13e0] move.b -(a0), $33333333.l ----------
OPCODE(0x13E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [1ee0] move.b -(a0), (a7)+ ----------
OPCODE(0x1EE0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [1f20] move.b -(a0), -(a7) ----------
OPCODE(0x1F20)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [1028] move.b ($3333,a0), d0 ----------
OPCODE(0x1028)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [10a8] move.b ($3333,a0), (a0) ----------
OPCODE(0x10A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [10e8] move.b ($3333,a0), (a0)+ ----------
OPCODE(0x10E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1128] move.b ($3333,a0), -(a0) ----------
OPCODE(0x1128)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1168] move.b ($3333,a0), ($3333,a0) ----------
OPCODE(0x1168)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [11a8] move.b ($3333,a0), ($33,a0,d3.w*2) ----------
OPCODE(0x11A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [11e8] move.b ($3333,a0), $3333.w ----------
OPCODE(0x11E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [13e8] move.b ($3333,a0), $33333333.l ----------
OPCODE(0x13E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [1ee8] move.b ($3333,a0), (a7)+ ----------
OPCODE(0x1EE8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1f28] move.b ($3333,a0), -(a7) ----------
OPCODE(0x1F28)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1030] move.b ($33,a0,d3.w*2), d0 ----------
OPCODE(0x1030)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [10b0] move.b ($33,a0,d3.w*2), (a0) ----------
OPCODE(0x10B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [10f0] move.b ($33,a0,d3.w*2), (a0)+ ----------
OPCODE(0x10F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [1130] move.b ($33,a0,d3.w*2), -(a0) ----------
OPCODE(0x1130)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [1170] move.b ($33,a0,d3.w*2), ($3333,a0) ----------
OPCODE(0x1170)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [11b0] move.b ($33,a0,d3.w*2), ($33,a0,d3.w*2) ----------
OPCODE(0x11B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [11f0] move.b ($33,a0,d3.w*2), $3333.w ----------
OPCODE(0x11F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [13f0] move.b ($33,a0,d3.w*2), $33333333.l ----------
OPCODE(0x13F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [1ef0] move.b ($33,a0,d3.w*2), (a7)+ ----------
OPCODE(0x1EF0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [1f30] move.b ($33,a0,d3.w*2), -(a7) ----------
OPCODE(0x1F30)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [1038] move.b $3333.w, d0 ----------
OPCODE(0x1038)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [10b8] move.b $3333.w, (a0) ----------
OPCODE(0x10B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [10f8] move.b $3333.w, (a0)+ ----------
OPCODE(0x10F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1138] move.b $3333.w, -(a0) ----------
OPCODE(0x1138)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1178] move.b $3333.w, ($3333,a0) ----------
OPCODE(0x1178)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [11b8] move.b $3333.w, ($33,a0,d3.w*2) ----------
OPCODE(0x11B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [11f8] move.b $3333.w, $3333.w ----------
OPCODE(0x11F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [13f8] move.b $3333.w, $33333333.l ----------
OPCODE(0x13F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [1ef8] move.b $3333.w, (a7)+ ----------
OPCODE(0x1EF8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1f38] move.b $3333.w, -(a7) ----------
OPCODE(0x1F38)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1039] move.b $33333333.l, d0 ----------
OPCODE(0x1039)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(16)
}

// ---------- [10b9] move.b $33333333.l, (a0) ----------
OPCODE(0x10B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [10f9] move.b $33333333.l, (a0)+ ----------
OPCODE(0x10F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [1139] move.b $33333333.l, -(a0) ----------
OPCODE(0x1139)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [1179] move.b $33333333.l, ($3333,a0) ----------
OPCODE(0x1179)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [11b9] move.b $33333333.l, ($33,a0,d3.w*2) ----------
OPCODE(0x11B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [11f9] move.b $33333333.l, $3333.w ----------
OPCODE(0x11F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [13f9] move.b $33333333.l, $33333333.l ----------
OPCODE(0x13F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [1ef9] move.b $33333333.l, (a7)+ ----------
OPCODE(0x1EF9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [1f39] move.b $33333333.l, -(a7) ----------
OPCODE(0x1F39)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [103a] move.b ($3333,pc), d0; =3335 ----------
OPCODE(0x103A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [10ba] move.b ($3333,pc), (a0); =3335 ----------
OPCODE(0x10BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [10fa] move.b ($3333,pc), (a0)+; =3335 ----------
OPCODE(0x10FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [113a] move.b ($3333,pc), -(a0); =3335 ----------
OPCODE(0x113A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [117a] move.b ($3333,pc), ($3333,a0); =3335 ----------
OPCODE(0x117A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [11ba] move.b ($3333,pc), ($33,a0,d3.w*2); =3335 ----------
OPCODE(0x11BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [11fa] move.b ($3333,pc), $3333.w; =3335 ----------
OPCODE(0x11FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [13fa] move.b ($3333,pc), $33333333.l; =3335 ----------
OPCODE(0x13FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [1efa] move.b ($3333,pc), (a7)+; =3335 ----------
OPCODE(0x1EFA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [1f3a] move.b ($3333,pc), -(a7); =3335 ----------
OPCODE(0x1F3A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [103b] move.b ($33,pc,d3.w*2), d0; =35 ----------
OPCODE(0x103B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(14)
}

// ---------- [10bb] move.b ($33,pc,d3.w*2), (a0); =35 ----------
OPCODE(0x10BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [10fb] move.b ($33,pc,d3.w*2), (a0)+; =35 ----------
OPCODE(0x10FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [113b] move.b ($33,pc,d3.w*2), -(a0); =35 ----------
OPCODE(0x113B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [117b] move.b ($33,pc,d3.w*2), ($3333,a0); =35 ----------
OPCODE(0x117B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [11bb] move.b ($33,pc,d3.w*2), ($33,a0,d3.w*2); =35 ----------
OPCODE(0x11BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [11fb] move.b ($33,pc,d3.w*2), $3333.w; =35 ----------
OPCODE(0x11FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [13fb] move.b ($33,pc,d3.w*2), $33333333.l; =35 ----------
OPCODE(0x13FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [1efb] move.b ($33,pc,d3.w*2), (a7)+; =35 ----------
OPCODE(0x1EFB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [1f3b] move.b ($33,pc,d3.w*2), -(a7); =35 ----------
OPCODE(0x1F3B)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [103c] move.b #$33, d0 ----------
OPCODE(0x103C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [10bc] move.b #$33, (a0) ----------
OPCODE(0x10BC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [10fc] move.b #$33, (a0)+ ----------
OPCODE(0x10FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [113c] move.b #$33, -(a0) ----------
OPCODE(0x113C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [117c] move.b #$33, ($3333,a0) ----------
OPCODE(0x117C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [11bc] move.b #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x11BC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [11fc] move.b #$33, $3333.w ----------
OPCODE(0x11FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [13fc] move.b #$33, $33333333.l ----------
OPCODE(0x13FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [1efc] move.b #$33, (a7)+ ----------
OPCODE(0x1EFC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1f3c] move.b #$33, -(a7) ----------
OPCODE(0x1F3C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [101f] move.b (a7)+, d0 ----------
OPCODE(0x101F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(8)
}

// ---------- [109f] move.b (a7)+, (a0) ----------
OPCODE(0x109F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [10df] move.b (a7)+, (a0)+ ----------
OPCODE(0x10DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [111f] move.b (a7)+, -(a0) ----------
OPCODE(0x111F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [115f] move.b (a7)+, ($3333,a0) ----------
OPCODE(0x115F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [119f] move.b (a7)+, ($33,a0,d3.w*2) ----------
OPCODE(0x119F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [11df] move.b (a7)+, $3333.w ----------
OPCODE(0x11DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [13df] move.b (a7)+, $33333333.l ----------
OPCODE(0x13DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [1edf] move.b (a7)+, (a7)+ ----------
OPCODE(0x1EDF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1f1f] move.b (a7)+, -(a7) ----------
OPCODE(0x1F1F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [1027] move.b -(a7), d0 ----------
OPCODE(0x1027)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 9) & 7) = res;
	POST_IO
	FINISH(10)
}

// ---------- [10a7] move.b -(a7), (a0) ----------
OPCODE(0x10A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [10e7] move.b -(a7), (a0)+ ----------
OPCODE(0x10E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	AREG((Opcode >> 9) & 7) += 1;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [1127] move.b -(a7), -(a0) ----------
OPCODE(0x1127)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7) - 1;
	AREG((Opcode >> 9) & 7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [1167] move.b -(a7), ($3333,a0) ----------
OPCODE(0x1167)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 9) & 7);
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [11a7] move.b -(a7), ($33,a0,d3.w*2) ----------
OPCODE(0x11A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG((Opcode >> 9) & 7);
	DECODE_EXT_WORD
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [11e7] move.b -(a7), $3333.w ----------
OPCODE(0x11E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_SWORD;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [13e7] move.b -(a7), $33333333.l ----------
OPCODE(0x13E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = FETCH_LONG;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [1ee7] move.b -(a7), (a7)+ ----------
OPCODE(0x1EE7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7);
	AREG(7) += 2;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [1f27] move.b -(a7), -(a7) ----------
OPCODE(0x1F27)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res = (s32)(s8)res;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	adr = AREG(7) - 2;
	AREG(7) = adr;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}
