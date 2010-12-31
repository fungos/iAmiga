
// ---------- [0000] ori.b #$33, d0 ----------
OPCODE(0x0000)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	res = DREGu8((Opcode >> 0) & 7);
	asm("orr %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0010] ori.b #$33, (a0) ----------
OPCODE(0x0010)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0018] ori.b #$33, (a0)+ ----------
OPCODE(0x0018)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0020] ori.b #$33, -(a0) ----------
OPCODE(0x0020)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0028] ori.b #$33, ($3333,a0) ----------
OPCODE(0x0028)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0030] ori.b #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0030)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(22)
}

// ---------- [0038] ori.b #$33, $3333.w ----------
OPCODE(0x0038)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0039] ori.b #$33, $33333333.l ----------
OPCODE(0x0039)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(24)
}

// ---------- [001f] ori.b #$33, (a7)+ ----------
OPCODE(0x001F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0027] ori.b #$33, -(a7) ----------
OPCODE(0x0027)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0040] ori.w #$3333, d0 ----------
OPCODE(0x0040)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	res = DREGu16((Opcode >> 0) & 7);
	asm("orr %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0050] ori.w #$3333, (a0) ----------
OPCODE(0x0050)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0058] ori.w #$3333, (a0)+ ----------
OPCODE(0x0058)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0060] ori.w #$3333, -(a0) ----------
OPCODE(0x0060)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0068] ori.w #$3333, ($3333,a0) ----------
OPCODE(0x0068)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0070] ori.w #$3333, ($33,a0,d3.w*2) ----------
OPCODE(0x0070)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(22)
}

// ---------- [0078] ori.w #$3333, $3333.w ----------
OPCODE(0x0078)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0079] ori.w #$3333, $33333333.l ----------
OPCODE(0x0079)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(24)
}

// ---------- [005f] ori.w #$3333, (a7)+ ----------
OPCODE(0x005F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0067] ori.w #$3333, -(a7) ----------
OPCODE(0x0067)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0080] ori.l #$33333333, d0 ----------
OPCODE(0x0080)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	res = DREGu32((Opcode >> 0) & 7);
	asm("orr %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(16)
}

// ---------- [0090] ori.l #$33333333, (a0) ----------
OPCODE(0x0090)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [0098] ori.l #$33333333, (a0)+ ----------
OPCODE(0x0098)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [00a0] ori.l #$33333333, -(a0) ----------
OPCODE(0x00A0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [00a8] ori.l #$33333333, ($3333,a0) ----------
OPCODE(0x00A8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [00b0] ori.l #$33333333, ($33,a0,d3.w*2) ----------
OPCODE(0x00B0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(34)
}

// ---------- [00b8] ori.l #$33333333, $3333.w ----------
OPCODE(0x00B8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [00b9] ori.l #$33333333, $33333333.l ----------
OPCODE(0x00B9)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(36)
}

// ---------- [009f] ori.l #$33333333, (a7)+ ----------
OPCODE(0x009F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [00a7] ori.l #$33333333, -(a7) ----------
OPCODE(0x00A7)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [003c] ori.b #$33, ccr ----------
OPCODE(0x003C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = flags_swap_CV(res);
	flags |= res << 28;
	ctx->xc |= res << 25;
	FINISH(20)
}

// ---------- [007c] ori.w #$3333, sr ----------
OPCODE(0x007C)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
		u32 res = FETCH_WORD;
		SRH |= (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags |= res << 28;
		ctx->xc |= res << 25;
		CHECK_INT_TO_JUMP(20);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	FINISH(20)
}

// ---------- [0200] andi.b #$33, d0 ----------
OPCODE(0x0200)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	res = DREGu8((Opcode >> 0) & 7);
	asm("and %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0210] andi.b #$33, (a0) ----------
OPCODE(0x0210)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0218] andi.b #$33, (a0)+ ----------
OPCODE(0x0218)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0220] andi.b #$33, -(a0) ----------
OPCODE(0x0220)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0228] andi.b #$33, ($3333,a0) ----------
OPCODE(0x0228)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0230] andi.b #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0230)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(22)
}

// ---------- [0238] andi.b #$33, $3333.w ----------
OPCODE(0x0238)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0239] andi.b #$33, $33333333.l ----------
OPCODE(0x0239)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(24)
}

// ---------- [021f] andi.b #$33, (a7)+ ----------
OPCODE(0x021F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0227] andi.b #$33, -(a7) ----------
OPCODE(0x0227)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0240] andi.w #$3333, d0 ----------
OPCODE(0x0240)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	res = DREGu16((Opcode >> 0) & 7);
	asm("and %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0250] andi.w #$3333, (a0) ----------
OPCODE(0x0250)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0258] andi.w #$3333, (a0)+ ----------
OPCODE(0x0258)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0260] andi.w #$3333, -(a0) ----------
OPCODE(0x0260)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0268] andi.w #$3333, ($3333,a0) ----------
OPCODE(0x0268)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0270] andi.w #$3333, ($33,a0,d3.w*2) ----------
OPCODE(0x0270)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(22)
}

// ---------- [0278] andi.w #$3333, $3333.w ----------
OPCODE(0x0278)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0279] andi.w #$3333, $33333333.l ----------
OPCODE(0x0279)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(24)
}

// ---------- [025f] andi.w #$3333, (a7)+ ----------
OPCODE(0x025F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0267] andi.w #$3333, -(a7) ----------
OPCODE(0x0267)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0280] andi.l #$33333333, d0 ----------
OPCODE(0x0280)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	res = DREGu32((Opcode >> 0) & 7);
	asm("and %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(16)
}

// ---------- [0290] andi.l #$33333333, (a0) ----------
OPCODE(0x0290)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [0298] andi.l #$33333333, (a0)+ ----------
OPCODE(0x0298)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [02a0] andi.l #$33333333, -(a0) ----------
OPCODE(0x02A0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [02a8] andi.l #$33333333, ($3333,a0) ----------
OPCODE(0x02A8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [02b0] andi.l #$33333333, ($33,a0,d3.w*2) ----------
OPCODE(0x02B0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(34)
}

// ---------- [02b8] andi.l #$33333333, $3333.w ----------
OPCODE(0x02B8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [02b9] andi.l #$33333333, $33333333.l ----------
OPCODE(0x02B9)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(36)
}

// ---------- [029f] andi.l #$33333333, (a7)+ ----------
OPCODE(0x029F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [02a7] andi.l #$33333333, -(a7) ----------
OPCODE(0x02A7)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [023c] andi.b #$33, ccr ----------
OPCODE(0x023C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = flags_swap_CV(res);
	flags &= res << 28;
	ctx->xc &= res << 25;
	FINISH(20)
}

// ---------- [027c] andi.w #$3333, sr ----------
OPCODE(0x027C)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
		u32 res = FETCH_WORD;
		SRH &= (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags &= res << 28;
		ctx->xc &= res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(20);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	FINISH(20)
}

// ---------- [0a00] eori.b #$33, d0 ----------
OPCODE(0x0A00)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	res = DREGu8((Opcode >> 0) & 7);
	asm("eor %[res], %[src], %[res], asl #24 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0a10] eori.b #$33, (a0) ----------
OPCODE(0x0A10)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0a18] eori.b #$33, (a0)+ ----------
OPCODE(0x0A18)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0a20] eori.b #$33, -(a0) ----------
OPCODE(0x0A20)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0a28] eori.b #$33, ($3333,a0) ----------
OPCODE(0x0A28)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0a30] eori.b #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0A30)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(22)
}

// ---------- [0a38] eori.b #$33, $3333.w ----------
OPCODE(0x0A38)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0a39] eori.b #$33, $33333333.l ----------
OPCODE(0x0A39)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(24)
}

// ---------- [0a1f] eori.b #$33, (a7)+ ----------
OPCODE(0x0A1F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0a27] eori.b #$33, -(a7) ----------
OPCODE(0x0A27)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0a40] eori.w #$3333, d0 ----------
OPCODE(0x0A40)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	res = DREGu16((Opcode >> 0) & 7);
	asm("eor %[res], %[src], %[res], asl #16 " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0a50] eori.w #$3333, (a0) ----------
OPCODE(0x0A50)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0a58] eori.w #$3333, (a0)+ ----------
OPCODE(0x0A58)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0a60] eori.w #$3333, -(a0) ----------
OPCODE(0x0A60)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0a68] eori.w #$3333, ($3333,a0) ----------
OPCODE(0x0A68)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0a70] eori.w #$3333, ($33,a0,d3.w*2) ----------
OPCODE(0x0A70)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(22)
}

// ---------- [0a78] eori.w #$3333, $3333.w ----------
OPCODE(0x0A78)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0a79] eori.w #$3333, $33333333.l ----------
OPCODE(0x0A79)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(24)
}

// ---------- [0a5f] eori.w #$3333, (a7)+ ----------
OPCODE(0x0A5F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0a67] eori.w #$3333, -(a7) ----------
OPCODE(0x0A67)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0a80] eori.l #$33333333, d0 ----------
OPCODE(0x0A80)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	res = DREGu32((Opcode >> 0) & 7);
	asm("eor %[res], %[src], %[res] " : [res] "+r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(16)
}

// ---------- [0a90] eori.l #$33333333, (a0) ----------
OPCODE(0x0A90)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [0a98] eori.l #$33333333, (a0)+ ----------
OPCODE(0x0A98)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [0aa0] eori.l #$33333333, -(a0) ----------
OPCODE(0x0AA0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [0aa8] eori.l #$33333333, ($3333,a0) ----------
OPCODE(0x0AA8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [0ab0] eori.l #$33333333, ($33,a0,d3.w*2) ----------
OPCODE(0x0AB0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(34)
}

// ---------- [0ab8] eori.l #$33333333, $3333.w ----------
OPCODE(0x0AB8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [0ab9] eori.l #$33333333, $33333333.l ----------
OPCODE(0x0AB9)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(36)
}

// ---------- [0a9f] eori.l #$33333333, (a7)+ ----------
OPCODE(0x0A9F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [0aa7] eori.l #$33333333, -(a7) ----------
OPCODE(0x0AA7)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [0a3c] eori.b #$33, ccr ----------
OPCODE(0x0A3C)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_BYTE;
	res = flags_swap_CV(res);
	flags ^= res << 28;
	ctx->xc ^= res << 25;
	FINISH(20)
}

// ---------- [0a7c] eori.w #$3333, sr ----------
OPCODE(0x0A7C)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
		u32 res = FETCH_WORD;
		SRH ^= (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags ^= res << 28;
		ctx->xc ^= res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(20);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	FINISH(20)
}

// ---------- [0400] subi.b #$33, d0 ----------
OPCODE(0x0400)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	dst = DREGu8((Opcode >> 0) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0410] subi.b #$33, (a0) ----------
OPCODE(0x0410)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0418] subi.b #$33, (a0)+ ----------
OPCODE(0x0418)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0420] subi.b #$33, -(a0) ----------
OPCODE(0x0420)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0428] subi.b #$33, ($3333,a0) ----------
OPCODE(0x0428)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0430] subi.b #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0430)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(22)
}

// ---------- [0438] subi.b #$33, $3333.w ----------
OPCODE(0x0438)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0439] subi.b #$33, $33333333.l ----------
OPCODE(0x0439)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(24)
}

// ---------- [041f] subi.b #$33, (a7)+ ----------
OPCODE(0x041F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0427] subi.b #$33, -(a7) ----------
OPCODE(0x0427)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0440] subi.w #$3333, d0 ----------
OPCODE(0x0440)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	dst = DREGu16((Opcode >> 0) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0450] subi.w #$3333, (a0) ----------
OPCODE(0x0450)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0458] subi.w #$3333, (a0)+ ----------
OPCODE(0x0458)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0460] subi.w #$3333, -(a0) ----------
OPCODE(0x0460)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0468] subi.w #$3333, ($3333,a0) ----------
OPCODE(0x0468)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0470] subi.w #$3333, ($33,a0,d3.w*2) ----------
OPCODE(0x0470)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(22)
}

// ---------- [0478] subi.w #$3333, $3333.w ----------
OPCODE(0x0478)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0479] subi.w #$3333, $33333333.l ----------
OPCODE(0x0479)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(24)
}

// ---------- [045f] subi.w #$3333, (a7)+ ----------
OPCODE(0x045F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0467] subi.w #$3333, -(a7) ----------
OPCODE(0x0467)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0480] subi.l #$33333333, d0 ----------
OPCODE(0x0480)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	dst = DREGu32((Opcode >> 0) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(16)
}

// ---------- [0490] subi.l #$33333333, (a0) ----------
OPCODE(0x0490)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [0498] subi.l #$33333333, (a0)+ ----------
OPCODE(0x0498)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [04a0] subi.l #$33333333, -(a0) ----------
OPCODE(0x04A0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [04a8] subi.l #$33333333, ($3333,a0) ----------
OPCODE(0x04A8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [04b0] subi.l #$33333333, ($33,a0,d3.w*2) ----------
OPCODE(0x04B0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(34)
}

// ---------- [04b8] subi.l #$33333333, $3333.w ----------
OPCODE(0x04B8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [04b9] subi.l #$33333333, $33333333.l ----------
OPCODE(0x04B9)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(36)
}

// ---------- [049f] subi.l #$33333333, (a7)+ ----------
OPCODE(0x049F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [04a7] subi.l #$33333333, -(a7) ----------
OPCODE(0x04A7)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [0600] addi.b #$33, d0 ----------
OPCODE(0x0600)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	dst = DREGu8((Opcode >> 0) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0610] addi.b #$33, (a0) ----------
OPCODE(0x0610)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0618] addi.b #$33, (a0)+ ----------
OPCODE(0x0618)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0620] addi.b #$33, -(a0) ----------
OPCODE(0x0620)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0628] addi.b #$33, ($3333,a0) ----------
OPCODE(0x0628)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0630] addi.b #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0630)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(22)
}

// ---------- [0638] addi.b #$33, $3333.w ----------
OPCODE(0x0638)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(20)
}

// ---------- [0639] addi.b #$33, $33333333.l ----------
OPCODE(0x0639)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(24)
}

// ---------- [061f] addi.b #$33, (a7)+ ----------
OPCODE(0x061F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(16)
}

// ---------- [0627] addi.b #$33, -(a7) ----------
OPCODE(0x0627)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
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
	FINISH(18)
}

// ---------- [0640] addi.w #$3333, d0 ----------
OPCODE(0x0640)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	dst = DREGu16((Opcode >> 0) & 7);
	asm volatile("adds %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0650] addi.w #$3333, (a0) ----------
OPCODE(0x0650)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0658] addi.w #$3333, (a0)+ ----------
OPCODE(0x0658)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0660] addi.w #$3333, -(a0) ----------
OPCODE(0x0660)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0668] addi.w #$3333, ($3333,a0) ----------
OPCODE(0x0668)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0670] addi.w #$3333, ($33,a0,d3.w*2) ----------
OPCODE(0x0670)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(22)
}

// ---------- [0678] addi.w #$3333, $3333.w ----------
OPCODE(0x0678)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(20)
}

// ---------- [0679] addi.w #$3333, $33333333.l ----------
OPCODE(0x0679)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(24)
}

// ---------- [065f] addi.w #$3333, (a7)+ ----------
OPCODE(0x065F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(16)
}

// ---------- [0667] addi.w #$3333, -(a7) ----------
OPCODE(0x0667)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
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
	FINISH(18)
}

// ---------- [0680] addi.l #$33333333, d0 ----------
OPCODE(0x0680)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	dst = DREGu32((Opcode >> 0) & 7);
	asm volatile("adds %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(16)
}

// ---------- [0690] addi.l #$33333333, (a0) ----------
OPCODE(0x0690)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [0698] addi.l #$33333333, (a0)+ ----------
OPCODE(0x0698)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [06a0] addi.l #$33333333, -(a0) ----------
OPCODE(0x06A0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [06a8] addi.l #$33333333, ($3333,a0) ----------
OPCODE(0x06A8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [06b0] addi.l #$33333333, ($33,a0,d3.w*2) ----------
OPCODE(0x06B0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(34)
}

// ---------- [06b8] addi.l #$33333333, $3333.w ----------
OPCODE(0x06B8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(32)
}

// ---------- [06b9] addi.l #$33333333, $33333333.l ----------
OPCODE(0x06B9)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(36)
}

// ---------- [069f] addi.l #$33333333, (a7)+ ----------
OPCODE(0x069F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(28)
}

// ---------- [06a7] addi.l #$33333333, -(a7) ----------
OPCODE(0x06A7)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
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
	FINISH(30)
}

// ---------- [0c00] cmpi.b #$33, d0 ----------
OPCODE(0x0C00)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	dst = DREGu8((Opcode >> 0) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(8)
}

// ---------- [0c10] cmpi.b #$33, (a0) ----------
OPCODE(0x0C10)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [0c18] cmpi.b #$33, (a0)+ ----------
OPCODE(0x0C18)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [0c20] cmpi.b #$33, -(a0) ----------
OPCODE(0x0C20)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [0c28] cmpi.b #$33, ($3333,a0) ----------
OPCODE(0x0C28)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [0c30] cmpi.b #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0C30)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [0c38] cmpi.b #$33, $3333.w ----------
OPCODE(0x0C38)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [0c39] cmpi.b #$33, $33333333.l ----------
OPCODE(0x0C39)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [0c1f] cmpi.b #$33, (a7)+ ----------
OPCODE(0x0C1F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [0c27] cmpi.b #$33, -(a7) ----------
OPCODE(0x0C27)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_BYTE << 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #24 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [0c40] cmpi.w #$3333, d0 ----------
OPCODE(0x0C40)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	dst = DREGu16((Opcode >> 0) & 7);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(8)
}

// ---------- [0c50] cmpi.w #$3333, (a0) ----------
OPCODE(0x0C50)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [0c58] cmpi.w #$3333, (a0)+ ----------
OPCODE(0x0C58)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [0c60] cmpi.w #$3333, -(a0) ----------
OPCODE(0x0C60)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [0c68] cmpi.w #$3333, ($3333,a0) ----------
OPCODE(0x0C68)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [0c70] cmpi.w #$3333, ($33,a0,d3.w*2) ----------
OPCODE(0x0C70)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [0c78] cmpi.w #$3333, $3333.w ----------
OPCODE(0x0C78)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [0c79] cmpi.w #$3333, $33333333.l ----------
OPCODE(0x0C79)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [0c5f] cmpi.w #$3333, (a7)+ ----------
OPCODE(0x0C5F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [0c67] cmpi.w #$3333, -(a7) ----------
OPCODE(0x0C67)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_WORD << 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst], asl #16 " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [0c80] cmpi.l #$33333333, d0 ----------
OPCODE(0x0C80)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	dst = DREGu32((Opcode >> 0) & 7);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(14)
}

// ---------- [0c90] cmpi.l #$33333333, (a0) ----------
OPCODE(0x0C90)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [0c98] cmpi.l #$33333333, (a0)+ ----------
OPCODE(0x0C98)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [0ca0] cmpi.l #$33333333, -(a0) ----------
OPCODE(0x0CA0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(22)
}

// ---------- [0ca8] cmpi.l #$33333333, ($3333,a0) ----------
OPCODE(0x0CA8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(24)
}

// ---------- [0cb0] cmpi.l #$33333333, ($33,a0,d3.w*2) ----------
OPCODE(0x0CB0)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(26)
}

// ---------- [0cb8] cmpi.l #$33333333, $3333.w ----------
OPCODE(0x0CB8)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(24)
}

// ---------- [0cb9] cmpi.l #$33333333, $33333333.l ----------
OPCODE(0x0CB9)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(28)
}

// ---------- [0c9f] cmpi.l #$33333333, (a7)+ ----------
OPCODE(0x0C9F)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [0ca7] cmpi.l #$33333333, -(a7) ----------
OPCODE(0x0CA7)
	u32 adr, res;
	u32 src, dst;

	src = (u32)FETCH_LONG;
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], %[dst] " : [res] "=r" (res) : [src] "r" (src), [dst] "r" (dst) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(22)
}

// ---------- [0800] btst #$33, d0 ----------
OPCODE(0x0800)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	FINISH(10)
}

// ---------- [0810] btst #$33, (a0) ----------
OPCODE(0x0810)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(12)
}

// ---------- [0818] btst #$33, (a0)+ ----------
OPCODE(0x0818)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(12)
}

// ---------- [0820] btst #$33, -(a0) ----------
OPCODE(0x0820)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(14)
}

// ---------- [0828] btst #$33, ($3333,a0) ----------
OPCODE(0x0828)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(16)
}

// ---------- [0830] btst #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0830)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(18)
}

// ---------- [0838] btst #$33, $3333.w ----------
OPCODE(0x0838)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(16)
}

// ---------- [0839] btst #$33, $33333333.l ----------
OPCODE(0x0839)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(20)
}

// ---------- [083a] btst #$33, ($3333,pc); =3337 ----------
OPCODE(0x083A)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(16)
}

// ---------- [083b] btst #$33, ($33,pc,d3.w*2); =37 ----------
OPCODE(0x083B)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(18)
}

// ---------- [081f] btst #$33, (a7)+ ----------
OPCODE(0x081F)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(12)
}

// ---------- [0827] btst #$33, -(a7) ----------
OPCODE(0x0827)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(14)
}

// ---------- [0840] bchg #$33, d0 ----------
OPCODE(0x0840)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(12)
}

// ---------- [0850] bchg #$33, (a0) ----------
OPCODE(0x0850)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [0858] bchg #$33, (a0)+ ----------
OPCODE(0x0858)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [0860] bchg #$33, -(a0) ----------
OPCODE(0x0860)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [0868] bchg #$33, ($3333,a0) ----------
OPCODE(0x0868)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [0870] bchg #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x0870)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [0878] bchg #$33, $3333.w ----------
OPCODE(0x0878)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [0879] bchg #$33, $33333333.l ----------
OPCODE(0x0879)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [085f] bchg #$33, (a7)+ ----------
OPCODE(0x085F)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [0867] bchg #$33, -(a7) ----------
OPCODE(0x0867)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [0880] bclr #$33, d0 ----------
OPCODE(0x0880)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(14)
}

// ---------- [0890] bclr #$33, (a0) ----------
OPCODE(0x0890)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [0898] bclr #$33, (a0)+ ----------
OPCODE(0x0898)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [08a0] bclr #$33, -(a0) ----------
OPCODE(0x08A0)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [08a8] bclr #$33, ($3333,a0) ----------
OPCODE(0x08A8)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [08b0] bclr #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x08B0)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [08b8] bclr #$33, $3333.w ----------
OPCODE(0x08B8)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [08b9] bclr #$33, $33333333.l ----------
OPCODE(0x08B9)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [089f] bclr #$33, (a7)+ ----------
OPCODE(0x089F)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [08a7] bclr #$33, -(a7) ----------
OPCODE(0x08A7)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [08c0] bset #$33, d0 ----------
OPCODE(0x08C0)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(12)
}

// ---------- [08d0] bset #$33, (a0) ----------
OPCODE(0x08D0)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [08d8] bset #$33, (a0)+ ----------
OPCODE(0x08D8)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [08e0] bset #$33, -(a0) ----------
OPCODE(0x08E0)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [08e8] bset #$33, ($3333,a0) ----------
OPCODE(0x08E8)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [08f0] bset #$33, ($33,a0,d3.w*2) ----------
OPCODE(0x08F0)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [08f8] bset #$33, $3333.w ----------
OPCODE(0x08F8)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [08f9] bset #$33, $33333333.l ----------
OPCODE(0x08F9)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [08df] bset #$33, (a7)+ ----------
OPCODE(0x08DF)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [08e7] bset #$33, -(a7) ----------
OPCODE(0x08E7)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_BYTE;
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [0100] btst d0, d0 ----------
OPCODE(0x0100)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	FINISH(6)
}

// ---------- [0110] btst d0, (a0) ----------
OPCODE(0x0110)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(8)
}

// ---------- [0118] btst d0, (a0)+ ----------
OPCODE(0x0118)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(8)
}

// ---------- [0120] btst d0, -(a0) ----------
OPCODE(0x0120)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(10)
}

// ---------- [0128] btst d0, ($3333,a0) ----------
OPCODE(0x0128)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(12)
}

// ---------- [0130] btst d0, ($33,a0,d3.w*2) ----------
OPCODE(0x0130)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(14)
}

// ---------- [0138] btst d0, $3333.w ----------
OPCODE(0x0138)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(12)
}

// ---------- [0139] btst d0, $33333333.l ----------
OPCODE(0x0139)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(16)
}

// ---------- [013a] btst d0, ($3333,pc); =3335 ----------
OPCODE(0x013A)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(12)
}

// ---------- [013b] btst d0, ($33,pc,d3.w*2); =35 ----------
OPCODE(0x013B)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(14)
}

// ---------- [013c] btst d0, #$33 ----------
OPCODE(0x013C)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	res = FETCH_BYTE;
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	FINISH(8)
}

// ---------- [011f] btst d0, (a7)+ ----------
OPCODE(0x011F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(8)
}

// ---------- [0127] btst d0, -(a7) ----------
OPCODE(0x0127)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	POST_IO
	FINISH(10)
}

// ---------- [0140] bchg d0, d0 ----------
OPCODE(0x0140)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [0150] bchg d0, (a0) ----------
OPCODE(0x0150)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [0158] bchg d0, (a0)+ ----------
OPCODE(0x0158)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [0160] bchg d0, -(a0) ----------
OPCODE(0x0160)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [0168] bchg d0, ($3333,a0) ----------
OPCODE(0x0168)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [0170] bchg d0, ($33,a0,d3.w*2) ----------
OPCODE(0x0170)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [0178] bchg d0, $3333.w ----------
OPCODE(0x0178)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [0179] bchg d0, $33333333.l ----------
OPCODE(0x0179)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [015f] bchg d0, (a7)+ ----------
OPCODE(0x015F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [0167] bchg d0, -(a7) ----------
OPCODE(0x0167)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res ^= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [0180] bclr d0, d0 ----------
OPCODE(0x0180)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(10)
}

// ---------- [0190] bclr d0, (a0) ----------
OPCODE(0x0190)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [0198] bclr d0, (a0)+ ----------
OPCODE(0x0198)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [01a0] bclr d0, -(a0) ----------
OPCODE(0x01A0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [01a8] bclr d0, ($3333,a0) ----------
OPCODE(0x01A8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [01b0] bclr d0, ($33,a0,d3.w*2) ----------
OPCODE(0x01B0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [01b8] bclr d0, $3333.w ----------
OPCODE(0x01B8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [01b9] bclr d0, $33333333.l ----------
OPCODE(0x01B9)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [019f] bclr d0, (a7)+ ----------
OPCODE(0x019F)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [01a7] bclr d0, -(a7) ----------
OPCODE(0x01A7)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res &= ~src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [01c0] bset d0, d0 ----------
OPCODE(0x01C0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 9) & 7);
	src = 1 << (src & 31);
	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [01d0] bset d0, (a0) ----------
OPCODE(0x01D0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [01d8] bset d0, (a0)+ ----------
OPCODE(0x01D8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [01e0] bset d0, -(a0) ----------
OPCODE(0x01E0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [01e8] bset d0, ($3333,a0) ----------
OPCODE(0x01E8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [01f0] bset d0, ($33,a0,d3.w*2) ----------
OPCODE(0x01F0)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [01f8] bset d0, $3333.w ----------
OPCODE(0x01F8)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [01f9] bset d0, $33333333.l ----------
OPCODE(0x01F9)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [01df] bset d0, (a7)+ ----------
OPCODE(0x01DF)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [01e7] bset d0, -(a7) ----------
OPCODE(0x01E7)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 9) & 7);
	src = 1 << (src & 7);
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("tst %[res], %[src] \n"
		"\tbicne %[flags], %[flags], #0x40000000 \n"
		"\torreq %[flags], %[flags], #0x40000000 "
		: [flags] "+r" (flags) : [res] "r" (res), [src] "r" (src) : "cc");
	res |= src;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [0108] movep.w ($3333,a0), d0 ----------
OPCODE(0x0108)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr + 0);
	src = READ_BYTE_F(adr + 2);
	DREGu16((Opcode >> 9) & 7) = (res << 8) | src;
	POST_IO
	FINISH(24)
}

// ---------- [0148] movep.l ($3333,a0), d0 ----------
OPCODE(0x0148)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr)
	res <<= 24;
	adr += 2;
	src = READ_BYTE_F(adr)
	res |= src << 16;
	adr += 2;
	src = READ_BYTE_F(adr)
	res |= src << 8;
	adr += 2;
	src = READ_BYTE_F(adr)
	DREG((Opcode >> 9) & 7) = res | src;
	POST_IO
	FINISH(32)
}

// ---------- [0188] movep.w d0, ($3333,a0) ----------
OPCODE(0x0188)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	WRITE_BYTE_F(adr + 0, res >> 8)
	WRITE_BYTE_F(adr + 2, res >> 0)
	POST_IO
	FINISH(24)
}

// ---------- [01c8] movep.l d0, ($3333,a0) ----------
OPCODE(0x01C8)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 9) & 7);
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	WRITE_BYTE_F(adr, res >> 24)
	adr += 2;
	WRITE_BYTE_F(adr, res >> 16)
	adr += 2;
	WRITE_BYTE_F(adr, res >> 8)
	adr += 2;
	WRITE_BYTE_F(adr, res >> 0)
	POST_IO
	FINISH(32)
}
