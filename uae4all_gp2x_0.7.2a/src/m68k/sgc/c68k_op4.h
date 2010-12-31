
// ---------- [4000] negx.b d0 ----------
OPCODE(0x4000)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4010] negx.b (a0) ----------
OPCODE(0x4010)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4018] negx.b (a0)+ ----------
OPCODE(0x4018)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4020] negx.b -(a0) ----------
OPCODE(0x4020)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4028] negx.b ($3333,a0) ----------
OPCODE(0x4028)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4030] negx.b ($33,a0,d3.w*2) ----------
OPCODE(0x4030)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4038] negx.b $3333.w ----------
OPCODE(0x4038)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4039] negx.b $33333333.l ----------
OPCODE(0x4039)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [401f] negx.b (a7)+ ----------
OPCODE(0x401F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4027] negx.b -(a7) ----------
OPCODE(0x4027)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #24 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4040] negx.w d0 ----------
OPCODE(0x4040)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4050] negx.w (a0) ----------
OPCODE(0x4050)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4058] negx.w (a0)+ ----------
OPCODE(0x4058)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4060] negx.w -(a0) ----------
OPCODE(0x4060)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4068] negx.w ($3333,a0) ----------
OPCODE(0x4068)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4070] negx.w ($33,a0,d3.w*2) ----------
OPCODE(0x4070)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4078] negx.w $3333.w ----------
OPCODE(0x4078)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4079] negx.w $33333333.l ----------
OPCODE(0x4079)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [405f] negx.w (a7)+ ----------
OPCODE(0x405F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4067] negx.w -(a7) ----------
OPCODE(0x4067)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res], asr #16 \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4080] negx.l d0 ----------
OPCODE(0x4080)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [4090] negx.l (a0) ----------
OPCODE(0x4090)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [4098] negx.l (a0)+ ----------
OPCODE(0x4098)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [40a0] negx.l -(a0) ----------
OPCODE(0x40A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [40a8] negx.l ($3333,a0) ----------
OPCODE(0x40A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [40b0] negx.l ($33,a0,d3.w*2) ----------
OPCODE(0x40B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [40b8] negx.l $3333.w ----------
OPCODE(0x40B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [40b9] negx.l $33333333.l ----------
OPCODE(0x40B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [409f] negx.l (a7)+ ----------
OPCODE(0x409F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [40a7] negx.l -(a7) ----------
OPCODE(0x40A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn r2, %[xbit] \n\t"
		"msr cpsr_flg, r2 ;@ move to carry flag"
		: : [xbit] "r" (X_FLAG) : "cc", "r2");
	asm volatile("rscs %[res], %[src], #0 ;@ arithmetic \n\t"
 			 "orr r3, %[flags], #0xb0000000 ;@ create flags mask, with Z only if previously set \n\t"
 			 "mrs %[flags], cpsr \n\t"
 			 "eor %[flags], %[flags], #0x20000000 ;@ invert C flag \n\t"
 			 "movs %[res], %[res] \n\t"
 			 "orreq %[flags], %[flags], #0x40000000 ;@ record Z flag \n\t"
 			 "andeq %[flags], %[flags], r3 ;@ fix Z"
 			 : [res] "=r" (res), [flags] "+r" (flags)
 			 : [src] "r" (src)
 			 : "cc", "r3");
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [4200] clr.b d0 ----------
OPCODE(0x4200)
	u32 adr, res;
	u32 src, dst;

	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4210] clr.b (a0) ----------
OPCODE(0x4210)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4218] clr.b (a0)+ ----------
OPCODE(0x4218)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4220] clr.b -(a0) ----------
OPCODE(0x4220)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4228] clr.b ($3333,a0) ----------
OPCODE(0x4228)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4230] clr.b ($33,a0,d3.w*2) ----------
OPCODE(0x4230)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4238] clr.b $3333.w ----------
OPCODE(0x4238)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4239] clr.b $33333333.l ----------
OPCODE(0x4239)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [421f] clr.b (a7)+ ----------
OPCODE(0x421F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4227] clr.b -(a7) ----------
OPCODE(0x4227)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4240] clr.w d0 ----------
OPCODE(0x4240)
	u32 adr, res;
	u32 src, dst;

	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4250] clr.w (a0) ----------
OPCODE(0x4250)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4258] clr.w (a0)+ ----------
OPCODE(0x4258)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4260] clr.w -(a0) ----------
OPCODE(0x4260)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4268] clr.w ($3333,a0) ----------
OPCODE(0x4268)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4270] clr.w ($33,a0,d3.w*2) ----------
OPCODE(0x4270)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4278] clr.w $3333.w ----------
OPCODE(0x4278)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4279] clr.w $33333333.l ----------
OPCODE(0x4279)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [425f] clr.w (a7)+ ----------
OPCODE(0x425F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4267] clr.w -(a7) ----------
OPCODE(0x4267)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4280] clr.l d0 ----------
OPCODE(0x4280)
	u32 adr, res;
	u32 src, dst;

	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [4290] clr.l (a0) ----------
OPCODE(0x4290)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [4298] clr.l (a0)+ ----------
OPCODE(0x4298)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [42a0] clr.l -(a0) ----------
OPCODE(0x42A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [42a8] clr.l ($3333,a0) ----------
OPCODE(0x42A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [42b0] clr.l ($33,a0,d3.w*2) ----------
OPCODE(0x42B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [42b8] clr.l $3333.w ----------
OPCODE(0x42B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [42b9] clr.l $33333333.l ----------
OPCODE(0x42B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [429f] clr.l (a7)+ ----------
OPCODE(0x429F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [42a7] clr.l -(a7) ----------
OPCODE(0x42A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	res = 0;
	asm volatile("mov %[flags], #0x40000000 ;@ nZcv " : [flags] "=r" (flags));
	PRE_IO
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [4400] neg.b d0 ----------
OPCODE(0x4400)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4410] neg.b (a0) ----------
OPCODE(0x4410)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4418] neg.b (a0)+ ----------
OPCODE(0x4418)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4420] neg.b -(a0) ----------
OPCODE(0x4420)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4428] neg.b ($3333,a0) ----------
OPCODE(0x4428)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4430] neg.b ($33,a0,d3.w*2) ----------
OPCODE(0x4430)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4438] neg.b $3333.w ----------
OPCODE(0x4438)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4439] neg.b $33333333.l ----------
OPCODE(0x4439)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [441f] neg.b (a7)+ ----------
OPCODE(0x441F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4427] neg.b -(a7) ----------
OPCODE(0x4427)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4440] neg.w d0 ----------
OPCODE(0x4440)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4450] neg.w (a0) ----------
OPCODE(0x4450)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4458] neg.w (a0)+ ----------
OPCODE(0x4458)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4460] neg.w -(a0) ----------
OPCODE(0x4460)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4468] neg.w ($3333,a0) ----------
OPCODE(0x4468)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4470] neg.w ($33,a0,d3.w*2) ----------
OPCODE(0x4470)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4478] neg.w $3333.w ----------
OPCODE(0x4478)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4479] neg.w $33333333.l ----------
OPCODE(0x4479)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [445f] neg.w (a7)+ ----------
OPCODE(0x445F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4467] neg.w -(a7) ----------
OPCODE(0x4467)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4480] neg.l d0 ----------
OPCODE(0x4480)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [4490] neg.l (a0) ----------
OPCODE(0x4490)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [4498] neg.l (a0)+ ----------
OPCODE(0x4498)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [44a0] neg.l -(a0) ----------
OPCODE(0x44A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [44a8] neg.l ($3333,a0) ----------
OPCODE(0x44A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [44b0] neg.l ($33,a0,d3.w*2) ----------
OPCODE(0x44B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [44b8] neg.l $3333.w ----------
OPCODE(0x44B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [44b9] neg.l $33333333.l ----------
OPCODE(0x44B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [449f] neg.l (a7)+ ----------
OPCODE(0x449F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [44a7] neg.l -(a7) ----------
OPCODE(0x44A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("rsbs %[res], %[src], #0" : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ; @r9 = flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	// store X flag 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [4600] not.b d0 ----------
OPCODE(0x4600)
	u32 adr, res;
	u32 src, dst;

	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4610] not.b (a0) ----------
OPCODE(0x4610)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4618] not.b (a0)+ ----------
OPCODE(0x4618)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4620] not.b -(a0) ----------
OPCODE(0x4620)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4628] not.b ($3333,a0) ----------
OPCODE(0x4628)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4630] not.b ($33,a0,d3.w*2) ----------
OPCODE(0x4630)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4638] not.b $3333.w ----------
OPCODE(0x4638)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4639] not.b $33333333.l ----------
OPCODE(0x4639)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [461f] not.b (a7)+ ----------
OPCODE(0x461F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4627] not.b -(a7) ----------
OPCODE(0x4627)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_BYTE_F(adr);
	src <<= 24;
	asm volatile("mvn %[res], %[src], asr #24" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4640] not.w d0 ----------
OPCODE(0x4640)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4650] not.w (a0) ----------
OPCODE(0x4650)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4658] not.w (a0)+ ----------
OPCODE(0x4658)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4660] not.w -(a0) ----------
OPCODE(0x4660)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4668] not.w ($3333,a0) ----------
OPCODE(0x4668)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4670] not.w ($33,a0,d3.w*2) ----------
OPCODE(0x4670)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [4678] not.w $3333.w ----------
OPCODE(0x4678)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [4679] not.w $33333333.l ----------
OPCODE(0x4679)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [465f] not.w (a7)+ ----------
OPCODE(0x465F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [4667] not.w -(a7) ----------
OPCODE(0x4667)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("mvn %[res], %[src], asr #16" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [4680] not.l d0 ----------
OPCODE(0x4680)
	u32 adr, res;
	u32 src, dst;

	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [4690] not.l (a0) ----------
OPCODE(0x4690)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [4698] not.l (a0)+ ----------
OPCODE(0x4698)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [46a0] not.l -(a0) ----------
OPCODE(0x46A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [46a8] not.l ($3333,a0) ----------
OPCODE(0x46A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [46b0] not.l ($33,a0,d3.w*2) ----------
OPCODE(0x46B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [46b8] not.l $3333.w ----------
OPCODE(0x46B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [46b9] not.l $33333333.l ----------
OPCODE(0x46B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [469f] not.l (a7)+ ----------
OPCODE(0x469F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [46a7] not.l -(a7) ----------
OPCODE(0x46A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	src = READ_LONG_F(adr);
	asm volatile("mvn %[res], %[src]" : [res] "=r" (res) : [src] "r" (src));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [40c0] move sr, d0 ----------
OPCODE(0x40C0)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [40d0] move sr, (a0) ----------
OPCODE(0x40D0)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [40d8] move sr, (a0)+ ----------
OPCODE(0x40D8)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [40e0] move sr, -(a0) ----------
OPCODE(0x40E0)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [40e8] move sr, ($3333,a0) ----------
OPCODE(0x40E8)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [40f0] move sr, ($33,a0,d3.w*2) ----------
OPCODE(0x40F0)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [40f8] move sr, $3333.w ----------
OPCODE(0x40F8)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = FETCH_SWORD;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [40f9] move sr, $33333333.l ----------
OPCODE(0x40F9)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = FETCH_LONG;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [40df] move sr, (a7)+ ----------
OPCODE(0x40DF)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [40e7] move sr, -(a7) ----------
OPCODE(0x40E7)
	u32 adr, res;
	u32 src, dst;

	res = GET_SR;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [44c0] move d0, ccr ----------
OPCODE(0x44C0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	SET_CCR(res);
	FINISH(12)
}

// ---------- [44d0] move (a0), ccr ----------
OPCODE(0x44D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(16)
}

// ---------- [44d8] move (a0)+, ccr ----------
OPCODE(0x44D8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(16)
}

// ---------- [44e0] move -(a0), ccr ----------
OPCODE(0x44E0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(18)
}

// ---------- [44e8] move ($3333,a0), ccr ----------
OPCODE(0x44E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(20)
}

// ---------- [44f0] move ($33,a0,d3.w*2), ccr ----------
OPCODE(0x44F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(22)
}

// ---------- [44f8] move $3333.w, ccr ----------
OPCODE(0x44F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(20)
}

// ---------- [44f9] move $33333333.l, ccr ----------
OPCODE(0x44F9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(24)
}

// ---------- [44fa] move ($3333,pc), ccr; =3335 ----------
OPCODE(0x44FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(20)
}

// ---------- [44fb] move ($33,pc,d3.w*2), ccr; =35 ----------
OPCODE(0x44FB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(22)
}

// ---------- [44fc] move #$3333, ccr ----------
OPCODE(0x44FC)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	SET_CCR(res);
	FINISH(16)
}

// ---------- [44df] move (a7)+, ccr ----------
OPCODE(0x44DF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(16)
}

// ---------- [44e7] move -(a7), ccr ----------
OPCODE(0x44E7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	SET_CCR(res);
	POST_IO
	FINISH(18)
}

// ---------- [46c0] move d0, sr ----------
OPCODE(0x46C0)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	res = DREGu16((Opcode >> 0) & 7);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(12);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	FINISH(12)
}

// ---------- [46d0] move (a0), sr ----------
OPCODE(0x46D0)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(16);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(16)
}

// ---------- [46d8] move (a0)+, sr ----------
OPCODE(0x46D8)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(16);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(16)
}

// ---------- [46e0] move -(a0), sr ----------
OPCODE(0x46E0)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(18);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(18)
}

// ---------- [46e8] move ($3333,a0), sr ----------
OPCODE(0x46E8)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
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
	POST_IO
	FINISH(20)
}

// ---------- [46f0] move ($33,a0,d3.w*2), sr ----------
OPCODE(0x46F0)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(22);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(22)
}

// ---------- [46f8] move $3333.w, sr ----------
OPCODE(0x46F8)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
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
	POST_IO
	FINISH(20)
}

// ---------- [46f9] move $33333333.l, sr ----------
OPCODE(0x46F9)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(24);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(24)
}

// ---------- [46fa] move ($3333,pc), sr; =3335 ----------
OPCODE(0x46FA)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
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
	POST_IO
	FINISH(20)
}

// ---------- [46fb] move ($33,pc,d3.w*2), sr; =35 ----------
OPCODE(0x46FB)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(22);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(22)
}

// ---------- [46fc] move #$3333, sr ----------
OPCODE(0x46FC)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	res = FETCH_WORD;
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(16);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	FINISH(16)
}

// ---------- [46df] move (a7)+, sr ----------
OPCODE(0x46DF)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(16);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(16)
}

// ---------- [46e7] move -(a7), sr ----------
OPCODE(0x46E7)
	u32 adr, res;
	u32 src, dst;

	if (GET_S_FLAG) {
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
		SRH = (res >> 8) & 0xA7;
		res = flags_swap_CV(res);
		flags  = res << 28;
		ctx->xc  = res << 25;
		if (!GET_S_FLAG) {
			res = AREG(7);
			AREG(7) = ASP;
			ASP = res;
		}
		CHECK_INT_TO_JUMP(18);
	}
	else
	{
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	POST_IO
	FINISH(18)
}

// ---------- [4800] nbcd d0 ----------
OPCODE(0x4800)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	DREGu8((Opcode >> 0) & 7) = res;
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	FINISH(6)
}

// ---------- [4810] nbcd (a0) ----------
OPCODE(0x4810)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(12)
}

// ---------- [4818] nbcd (a0)+ ----------
OPCODE(0x4818)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(12)
}

// ---------- [4820] nbcd -(a0) ----------
OPCODE(0x4820)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(14)
}

// ---------- [4828] nbcd ($3333,a0) ----------
OPCODE(0x4828)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(16)
}

// ---------- [4830] nbcd ($33,a0,d3.w*2) ----------
OPCODE(0x4830)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(18)
}

// ---------- [4838] nbcd $3333.w ----------
OPCODE(0x4838)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(16)
}

// ---------- [4839] nbcd $33333333.l ----------
OPCODE(0x4839)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(20)
}

// ---------- [481f] nbcd (a7)+ ----------
OPCODE(0x481F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(12)
}

// ---------- [4827] nbcd -(a7) ----------
OPCODE(0x4827)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	// clear all flags, except Z
	flags &= 0x40000000;
	res = 0x9a - res;
	if (X_FLAG & 0x20000000) res--;

	if (res != 0x9a) {
		if ((res & 0x0f) == 0xa) res = (res & 0xf0) + 0x10;
	WRITE_BYTE_F(adr, res)
		asm volatile("tst %[res], %[res]\n\t"
			"orreq %[flags], %[flags], #0x20000000 @ set C\n\t"
			"movne %[flags], #0x20000000 @ C "
			:[flags] "+r" (flags):[res] "r" (res):"cc");
	}
	if (res & 0x80) flags |= 0x80000000; // N
	X_FLAG = flags;
	POST_IO
	FINISH(14)
}

// ---------- [4850] pea (a0) ----------
OPCODE(0x4850)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
	FINISH(12)
}

// ---------- [4868] pea ($3333,a0) ----------
OPCODE(0x4868)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
	FINISH(16)
}

// ---------- [4870] pea ($33,a0,d3.w*2) ----------
OPCODE(0x4870)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
	FINISH(20)
}

// ---------- [4878] pea $3333.w ----------
OPCODE(0x4878)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
	FINISH(16)
}

// ---------- [4879] pea $33333333.l ----------
OPCODE(0x4879)
	u32 adr, res;
	u32 src, dst;

	adr = (s32)FETCH_LONG;
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
	FINISH(20)
}

// ---------- [487a] pea ($3333,pc); =3335 ----------
OPCODE(0x487A)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + (GET_PC);
	PC++;
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
	FINISH(16)
}

// ---------- [487b] pea ($33,pc,d3.w*2); =35 ----------
OPCODE(0x487B)
	u32 adr, res;
	u32 src, dst;

	adr = GET_PC;
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F(adr)
	POST_IO
	FINISH(20)
}

// ---------- [4840] swap d0 ----------
OPCODE(0x4840)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	asm volatile("mov %[res], %[res], ror #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4890] movem.w d0-d1/d4-d5/a0-a1/a4-a5, (a0) ----------
OPCODE(0x4890)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(u16*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(12)
}

// ---------- [48a0] movem.w d2-d3/d6-d7/a2-a3/a6-a7, -(a0) ----------
OPCODE(0x48A0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)(&AREG(7));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 2;
			WRITE_WORD_F(adr, *(u16*)src)
		}
		src -= 4;
	} while (res >>= 1);
	AREG((Opcode >> 0) & 7) = adr;
	POST_IO
	cycles -= (dst - adr) * 2;
	FINISH(8)
}

// ---------- [48a8] movem.w d0-d1/d4-d5/a0-a1/a4-a5, ($3333,a0) ----------
OPCODE(0x48A8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(u16*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(20)
}

// ---------- [48b0] movem.w d0-d1/d4-d5/a0-a1/a4-a5, ($33,a0,d3.w*2) ----------
OPCODE(0x48B0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(u16*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(24)
}

// ---------- [48b8] movem.w d0-d1/d4-d5/a0-a1/a4-a5, $3333.w ----------
OPCODE(0x48B8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = FETCH_SWORD;
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(u16*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(20)
}

// ---------- [48b9] movem.w d0-d1/d4-d5/a0-a1/a4-a5, $33333333.l ----------
OPCODE(0x48B9)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = FETCH_LONG;
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_WORD_F(adr, *(u16*)src)
			adr += 2;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(28)
}

// ---------- [48a7] movem.w d2-d3/d6-d7/a2-a3/a6-a7, -(a7) ----------
OPCODE(0x48A7)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG(7);
	src = (u32)(&AREG(7));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 2;
			WRITE_WORD_F(adr, *(u16*)src)
		}
		src -= 4;
	} while (res >>= 1);
	AREG(7) = adr;
	POST_IO
	cycles -= (dst - adr) * 2;
	FINISH(8)
}

// ---------- [48d0] movem.l d0-d1/d4-d5/a0-a1/a4-a5, (a0) ----------
OPCODE(0x48D0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(u32*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(16)
}

// ---------- [48e0] movem.l d2-d3/d6-d7/a2-a3/a6-a7, -(a0) ----------
OPCODE(0x48E0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)(&AREG(7));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 4;
			WRITE_LONG_DEC_F(adr, *(u32*)src)
		}
		src -= 4;
	} while (res >>= 1);
	AREG((Opcode >> 0) & 7) = adr;
	POST_IO
	cycles -= (dst - adr) * 2;
	FINISH(8)
}

// ---------- [48e8] movem.l d0-d1/d4-d5/a0-a1/a4-a5, ($3333,a0) ----------
OPCODE(0x48E8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(u32*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(24)
}

// ---------- [48f0] movem.l d0-d1/d4-d5/a0-a1/a4-a5, ($33,a0,d3.w*2) ----------
OPCODE(0x48F0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(u32*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(28)
}

// ---------- [48f8] movem.l d0-d1/d4-d5/a0-a1/a4-a5, $3333.w ----------
OPCODE(0x48F8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = FETCH_SWORD;
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(u32*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(24)
}

// ---------- [48f9] movem.l d0-d1/d4-d5/a0-a1/a4-a5, $33333333.l ----------
OPCODE(0x48F9)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = FETCH_LONG;
	src = (u32)(&DREG(0));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			WRITE_LONG_F(adr, *(u32*)src)
			adr += 4;
		}
		src += 4;
	} while (res >>= 1);
	POST_IO
	cycles -= (adr - dst) * 2;
	FINISH(32)
}

// ---------- [48e7] movem.l d2-d3/d6-d7/a2-a3/a6-a7, -(a7) ----------
OPCODE(0x48E7)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	adr = AREG(7);
	src = (u32)(&AREG(7));
	dst = adr;
	PRE_IO
	do
	{
		if (res & 1)
		{
			adr -= 4;
			WRITE_LONG_DEC_F(adr, *(u32*)src)
		}
		src -= 4;
	} while (res >>= 1);
	AREG(7) = adr;
	POST_IO
	cycles -= (dst - adr) * 2;
	FINISH(8)
}

// ---------- [4880] ext.w d0 ----------
OPCODE(0x4880)
	u32 adr, res;
	u32 src, dst;

	res = (s32)DREGs8((Opcode >> 0) & 7);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [48c0] ext.l d0 ----------
OPCODE(0x48C0)
	u32 adr, res;
	u32 src, dst;

	res = (s32)DREGs16((Opcode >> 0) & 7);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4a00] tst.b d0 ----------
OPCODE(0x4A00)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(4)
}

// ---------- [4a10] tst.b (a0) ----------
OPCODE(0x4A10)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4a18] tst.b (a0)+ ----------
OPCODE(0x4A18)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4a20] tst.b -(a0) ----------
OPCODE(0x4A20)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [4a28] tst.b ($3333,a0) ----------
OPCODE(0x4A28)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4a30] tst.b ($33,a0,d3.w*2) ----------
OPCODE(0x4A30)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [4a38] tst.b $3333.w ----------
OPCODE(0x4A38)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4a39] tst.b $33333333.l ----------
OPCODE(0x4A39)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [4a1f] tst.b (a7)+ ----------
OPCODE(0x4A1F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4a27] tst.b -(a7) ----------
OPCODE(0x4A27)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	asm volatile("mov %[res], %[res], asl #24" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [4a40] tst.w d0 ----------
OPCODE(0x4A40)
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(4)
}

// ---------- [4a50] tst.w (a0) ----------
OPCODE(0x4A50)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4a58] tst.w (a0)+ ----------
OPCODE(0x4A58)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4a60] tst.w -(a0) ----------
OPCODE(0x4A60)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [4a68] tst.w ($3333,a0) ----------
OPCODE(0x4A68)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4a70] tst.w ($33,a0,d3.w*2) ----------
OPCODE(0x4A70)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [4a78] tst.w $3333.w ----------
OPCODE(0x4A78)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4a79] tst.w $33333333.l ----------
OPCODE(0x4A79)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [4a5f] tst.w (a7)+ ----------
OPCODE(0x4A5F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4a67] tst.w -(a7) ----------
OPCODE(0x4A67)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_WORD_F(adr);
	asm volatile("mov %[res], %[res], asl #16" : [res] "+r" (res));
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [4a80] tst.l d0 ----------
OPCODE(0x4A80)
	u32 adr, res;
	u32 src, dst;

	res = DREGu32((Opcode >> 0) & 7);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	FINISH(4)
}

// ---------- [4a90] tst.l (a0) ----------
OPCODE(0x4A90)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4a98] tst.l (a0)+ ----------
OPCODE(0x4A98)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4aa0] tst.l -(a0) ----------
OPCODE(0x4AA0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [4aa8] tst.l ($3333,a0) ----------
OPCODE(0x4AA8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [4ab0] tst.l ($33,a0,d3.w*2) ----------
OPCODE(0x4AB0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(18)
}

// ---------- [4ab8] tst.l $3333.w ----------
OPCODE(0x4AB8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [4ab9] tst.l $33333333.l ----------
OPCODE(0x4AB9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(20)
}

// ---------- [4a9f] tst.l (a7)+ ----------
OPCODE(0x4A9F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4aa7] tst.l -(a7) ----------
OPCODE(0x4AA7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	res = READ_LONG_F(adr);
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [4ac0] tas d0 ----------
OPCODE(0x4AC0)
	u32 adr, res;
	u32 src, dst;

	res = DREGu8((Opcode >> 0) & 7);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	res |= 0x80000000;
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4ad0] tas (a0) ----------
OPCODE(0x4AD0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4ad8] tas (a0)+ ----------
OPCODE(0x4AD8)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4ae0] tas -(a0) ----------
OPCODE(0x4AE0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [4ae8] tas ($3333,a0) ----------
OPCODE(0x4AE8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4af0] tas ($33,a0,d3.w*2) ----------
OPCODE(0x4AF0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(14)
}

// ---------- [4af8] tas $3333.w ----------
OPCODE(0x4AF8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(12)
}

// ---------- [4af9] tas $33333333.l ----------
OPCODE(0x4AF9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(16)
}

// ---------- [4adf] tas (a7)+ ----------
OPCODE(0x4ADF)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(8)
}

// ---------- [4ae7] tas -(a7) ----------
OPCODE(0x4AE7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	res = READ_BYTE_F(adr);
	res <<= 24;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	POST_IO
	FINISH(10)
}

// ---------- [4afc] tas #$33 ----------
OPCODE(0x4AFC)
	u32 adr, res;
	u32 src, dst;

	PC--;
	execute_exception(M68K_ILLEGAL_INSTRUCTION_EX);
	FINISH(4)
}

// ---------- [4c90] movem.w (a0), d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4C90)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(16)
}

// ---------- [4c98] movem.w (a0)+, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4C98)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	AREG((Opcode >> 0) & 7) = adr;
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(12)
}

// ---------- [4ca8] movem.w ($3333,a0), d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CA8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(24)
}

// ---------- [4cb0] movem.w ($33,a0,d3.w*2), d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CB0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(28)
}

// ---------- [4cb8] movem.w $3333.w, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CB8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = FETCH_SWORD;
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(24)
}

// ---------- [4cb9] movem.w $33333333.l, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CB9)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = FETCH_LONG;
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(32)
}

// ---------- [4cba] movem.w ($3333,pc), d0-d1/d4-d5/a0-a1/a4-a5; =3337 ----------
OPCODE(0x4CBA)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(24)
}

// ---------- [4cbb] movem.w ($33,pc,d3.w*2), d0-d1/d4-d5/a0-a1/a4-a5; =37 ----------
OPCODE(0x4CBB)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(28)
}

// ---------- [4c9f] movem.w (a7)+, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4C9F)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG(7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(2, READSX_WORD_F)
	AREG(7) = adr;
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(12)
}

// ---------- [4cd0] movem.l (a0), d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CD0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(20)
}

// ---------- [4cd8] movem.l (a0)+, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CD8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG((Opcode >> 0) & 7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	AREG((Opcode >> 0) & 7) = adr;
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(12)
}

// ---------- [4ce8] movem.l ($3333,a0), d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CE8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(28)
}

// ---------- [4cf0] movem.l ($33,a0,d3.w*2), d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CF0)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(32)
}

// ---------- [4cf8] movem.l $3333.w, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CF8)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = FETCH_SWORD;
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(28)
}

// ---------- [4cf9] movem.l $33333333.l, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CF9)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = FETCH_LONG;
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(36)
}

// ---------- [4cfa] movem.l ($3333,pc), d0-d1/d4-d5/a0-a1/a4-a5; =3337 ----------
OPCODE(0x4CFA)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(28)
}

// ---------- [4cfb] movem.l ($33,pc,d3.w*2), d0-d1/d4-d5/a0-a1/a4-a5; =37 ----------
OPCODE(0x4CFB)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(32)
}

// ---------- [4cdf] movem.l (a7)+, d0-d1/d4-d5/a0-a1/a4-a5 ----------
OPCODE(0x4CDF)
	u32 adr, res;
	u32 src, dst;

	res = FETCH_WORD;
	if (!res) goto no_registers; 
	adr = AREG(7);
	src = (u32)&DREG(0);
	dst = adr;
	PRE_IO
	MOVEMaR(4, READ_LONG_F)
	AREG(7) = adr;
	POST_IO
	cycles -= (adr - dst) * 2;
no_registers:
	FINISH(12)
}

// ---------- [4e40] trap #0 ----------
OPCODE(0x4E40)
	u32 adr, res;
	u32 src, dst;

	execute_exception(M68K_TRAP_BASE_EX + (Opcode & 0xF));
	FINISH(4)
}

// ---------- [4e50] link a0,#$3333 ----------
OPCODE(0x4E50)
	u32 adr, res;
	u32 src, dst;

	res = AREGu32((Opcode >> 0) & 7);
	PRE_IO
	PUSH_32_F(res)
	res = AREG(7);
	AREG((Opcode >> 0) & 7) = res;
	AREG(7) += (s32)(s16)FETCH_WORD;
	POST_IO
	FINISH(16)
}

// ---------- [4e57] link a7,#$3333 ----------
OPCODE(0x4E57)
	u32 adr, res;
	u32 src, dst;

	AREG(7) -= 4;
	PRE_IO
	WRITE_LONG_DEC_F(AREG(7), AREG(7))
	AREG(7) += (s32)(s16)FETCH_WORD;
	POST_IO
	FINISH(16)
}

// ---------- [4e58] unlk a0 ----------
OPCODE(0x4E58)
	u32 adr, res;
	u32 src, dst;

	src = AREGu32((Opcode >> 0) & 7);
	AREG(7) = src + 4;
	PRE_IO
	res = READ_LONG_F(src)
	AREG((Opcode >> 0) & 7) = res;
	POST_IO
	FINISH(12)
}

// ---------- [4e5f] unlk a7 ----------
OPCODE(0x4E5F)
	u32 adr, res;
	u32 src, dst;

	PRE_IO
	AREG(7) = READ_LONG_F(AREG(7))
	POST_IO
	FINISH(12)
}

// ---------- [4e60] move a0, usp ----------
OPCODE(0x4E60)
	u32 adr, res;
	u32 src, dst;

	if (!GET_S_FLAG) {
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	res = AREGu32((Opcode >> 0) & 7);
	ASP = res;
	FINISH(4)
}

// ---------- [4e68] move usp, a0 ----------
OPCODE(0x4E68)
	u32 adr, res;
	u32 src, dst;

	if (!GET_S_FLAG) {
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	res = ASP;
	AREG((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [4e70] reset ----------
OPCODE(0x4E70)
	u32 adr, res;
	u32 src, dst;

	if (!GET_S_FLAG) {
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	if (ctx->ResetCallback)
		ctx->ResetCallback();
	FINISH(132)
}

// ---------- [4e71] nop ----------
OPCODE(0x4E71)
	u32 adr, res;
	u32 src, dst;

	FINISH(4)
}

// ---------- [4e72] stop ----------
OPCODE(0x4E72)
	u32 adr, res;
	u32 src, dst;

	if (!GET_S_FLAG) {
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	res = FETCH_WORD & M68K_SR_MASK;
	SET_SR(res);
	if (!GET_S_FLAG) {
		res = AREG(7);
		AREG(7) = ASP;
		ASP = res;
	}
	EXECINFO |= M68K_HALTED;
	cycles = 0;
FINISH(4);
}

// ---------- [4e73] rte ----------
OPCODE(0x4E73)
	u32 adr, res;
	u32 src, dst;

	if (!GET_S_FLAG) {
		PC--;
		execute_exception(M68K_PRIVILEGE_VIOLATION_EX);
		FINISH(4)
	}
	PRE_IO
	POP_16_F(res)
	SRH = (res >> 8) & 0xA7;
	res = flags_swap_CV(res);
	flags  = res << 28;
	ctx->xc  = res << 25;
	POP_32_F(res)
	SET_PC_BASE(res)
	if (!GET_S_FLAG)
	{
		res = AREG(7);
		AREG(7) = ASP;
		ASP = res;
	}
	m68kcontext.execinfo &= ~(M68K_EMULATE_GROUP_0|M68K_EMULATE_TRACE|M68K_DO_TRACE);
		CHECK_INT_TO_JUMP(20);
POST_IO
FINISH(20);
}

// ---------- [4e75] rts ----------
OPCODE(0x4E75)
	u32 adr, res;
	u32 src, dst;

	PRE_IO
	POP_32_F(res)
	SET_PC_BASE(res)
	CHECK_BRANCH_EXCEPTION(res);
	POST_IO
	FINISH(16)
}

// ---------- [4e76] trapv ----------
OPCODE(0x4E76)
	u32 adr, res;
	u32 src, dst;

	if cond_vs {
		execute_exception(M68K_TRAPV_EX);
	}
	FINISH(4)
}

// ---------- [4e77] rtr ----------
OPCODE(0x4E77)
	u32 adr, res;
	u32 src, dst;

	PRE_IO
	POP_16_F(res)
	SET_CCR(res)
	POP_32_F(res)
	SET_PC_BASE(res)
	CHECK_BRANCH_EXCEPTION(res);
	POST_IO
	FINISH(20)
}

// ---------- [4e90] jsr (a0) ----------
OPCODE(0x4E90)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	PUSH_32_F(GET_PC)
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	POST_IO
	FINISH(16)
}

// ---------- [4ea8] jsr ($3333,a0) ----------
OPCODE(0x4EA8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	PUSH_32_F(GET_PC)
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	POST_IO
	FINISH(18)
}

// ---------- [4eb0] jsr ($33,a0,d3.w*2) ----------
OPCODE(0x4EB0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F(GET_PC)
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	POST_IO
	FINISH(22)
}

// ---------- [4eb8] jsr $3333.w ----------
OPCODE(0x4EB8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	PUSH_32_F(GET_PC)
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	POST_IO
	FINISH(18)
}

// ---------- [4eb9] jsr $33333333.l ----------
OPCODE(0x4EB9)
	u32 adr, res;
	u32 src, dst;

	adr = (s32)FETCH_LONG;
	PRE_IO
	PUSH_32_F(GET_PC)
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	POST_IO
	FINISH(20)
}

// ---------- [4eba] jsr ($3333,pc); =3335 ----------
OPCODE(0x4EBA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + (GET_PC);
	PC++;
	PRE_IO
	PUSH_32_F(GET_PC)
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	POST_IO
	FINISH(18)
}

// ---------- [4ebb] jsr ($33,pc,d3.w*2); =35 ----------
OPCODE(0x4EBB)
	u32 adr, res;
	u32 src, dst;

	adr = GET_PC;
	DECODE_EXT_WORD
	PRE_IO
	PUSH_32_F(GET_PC)
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	POST_IO
	FINISH(22)
}

// ---------- [4ed0] jmp (a0) ----------
OPCODE(0x4ED0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	FINISH(8)
}

// ---------- [4ee8] jmp ($3333,a0) ----------
OPCODE(0x4EE8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	FINISH(10)
}

// ---------- [4ef0] jmp ($33,a0,d3.w*2) ----------
OPCODE(0x4EF0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	FINISH(14)
}

// ---------- [4ef8] jmp $3333.w ----------
OPCODE(0x4EF8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	FINISH(10)
}

// ---------- [4ef9] jmp $33333333.l ----------
OPCODE(0x4EF9)
	u32 adr, res;
	u32 src, dst;

	adr = (s32)FETCH_LONG;
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	FINISH(12)
}

// ---------- [4efa] jmp ($3333,pc); =3335 ----------
OPCODE(0x4EFA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + (GET_PC);
	PC++;
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	FINISH(10)
}

// ---------- [4efb] jmp ($33,pc,d3.w*2); =35 ----------
OPCODE(0x4EFB)
	u32 adr, res;
	u32 src, dst;

	adr = GET_PC;
	DECODE_EXT_WORD
	SET_PC_BASE(adr)
	CHECK_BRANCH_EXCEPTION(adr);
	FINISH(14)
}

// ---------- [4180] chk d0, a0 ----------
OPCODE(0x4180)
	u32 adr, res;
	u32 src, dst;

	src = DREGu16((Opcode >> 0) & 7);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap4180");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap4180" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	FINISH(10)
}
NAKED(chktrap4180) {
	execute_exception(M68K_CHK_EX);
	FINISH(10)
}

// ---------- [4190] chk (a0), a0 ----------
OPCODE(0x4190)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap4190");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap4190" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(14)
}
NAKED(chktrap4190) {
	execute_exception(M68K_CHK_EX);
	FINISH(14)
}

// ---------- [4198] chk (a0)+, a0 ----------
OPCODE(0x4198)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap4198");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap4198" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(14)
}
NAKED(chktrap4198) {
	execute_exception(M68K_CHK_EX);
	FINISH(14)
}

// ---------- [41a0] chk -(a0), a0 ----------
OPCODE(0x41A0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41A0");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41A0" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(16)
}
NAKED(chktrap41A0) {
	execute_exception(M68K_CHK_EX);
	FINISH(16)
}

// ---------- [41a8] chk ($3333,a0), a0 ----------
OPCODE(0x41A8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41A8");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41A8" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(18)
}
NAKED(chktrap41A8) {
	execute_exception(M68K_CHK_EX);
	FINISH(18)
}

// ---------- [41b0] chk ($33,a0,d3.w*2), a0 ----------
OPCODE(0x41B0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41B0");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41B0" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(20)
}
NAKED(chktrap41B0) {
	execute_exception(M68K_CHK_EX);
	FINISH(20)
}

// ---------- [41b8] chk $3333.w, a0 ----------
OPCODE(0x41B8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41B8");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41B8" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(18)
}
NAKED(chktrap41B8) {
	execute_exception(M68K_CHK_EX);
	FINISH(18)
}

// ---------- [41b9] chk $33333333.l, a0 ----------
OPCODE(0x41B9)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41B9");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41B9" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(22)
}
NAKED(chktrap41B9) {
	execute_exception(M68K_CHK_EX);
	FINISH(22)
}

// ---------- [41ba] chk ($3333,pc), a0; =3335 ----------
OPCODE(0x41BA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + ((u32)(PC) - BasePC);
	PC++;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41BA");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41BA" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(18)
}
NAKED(chktrap41BA) {
	execute_exception(M68K_CHK_EX);
	FINISH(18)
}

// ---------- [41bb] chk ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0x41BB)
	u32 adr, res;
	u32 src, dst;

	adr = (u32)(PC) - BasePC;
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41BB");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41BB" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(20)
}
NAKED(chktrap41BB) {
	execute_exception(M68K_CHK_EX);
	FINISH(20)
}

// ---------- [41bc] chk #$33, a0 ----------
OPCODE(0x41BC)
	u32 adr, res;
	u32 src, dst;

	src = FETCH_WORD;
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41BC");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41BC" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	FINISH(14)
}
NAKED(chktrap41BC) {
	execute_exception(M68K_CHK_EX);
	FINISH(14)
}

// ---------- [419f] chk (a7)+, a0 ----------
OPCODE(0x419F)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap419F");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap419F" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(14)
}
NAKED(chktrap419F) {
	execute_exception(M68K_CHK_EX);
	FINISH(14)
}

// ---------- [41a7] chk -(a7), a0 ----------
OPCODE(0x41A7)
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	res = DREGu16((Opcode >> 9) & 7);
	res <<= 16;
	src <<= 16;
	u32 oldN = 0x80000000 & flags;
	// get flags
	asm ("adds %[res], %[res], #0 ;@ defines NZ and clears CV \n"
	     "\tmrs %0, cpsr "
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	asm volatile("bmi chktrap41A7");
	flags &= ~0x80000000;
	asm volatile("cmp %[res], %[src]\n\t"
		"bgt chktrap41A7" :: [src] "r" (src), [res] "r" (res) : "cc");
	// retain old N flag
	flags |= oldN;
	POST_IO
	FINISH(16)
}
NAKED(chktrap41A7) {
	execute_exception(M68K_CHK_EX);
	FINISH(16)
}

// ---------- [41d0] lea (a0), a0 ----------
OPCODE(0x41D0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	res = adr;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(4)
}

// ---------- [41e8] lea ($3333,a0), a0 ----------
OPCODE(0x41E8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	res = adr;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [41f0] lea ($33,a0,d3.w*2), a0 ----------
OPCODE(0x41F0)
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	res = adr;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(12)
}

// ---------- [41f8] lea $3333.w, a0 ----------
OPCODE(0x41F8)
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	res = adr;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [41f9] lea $33333333.l, a0 ----------
OPCODE(0x41F9)
	u32 adr, res;
	u32 src, dst;

	adr = (s32)FETCH_LONG;
	res = adr;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(12)
}

// ---------- [41fa] lea ($3333,pc), a0; =3335 ----------
OPCODE(0x41FA)
	u32 adr, res;
	u32 src, dst;

	adr = GET_SWORD + (GET_PC);
	PC++;
	res = adr;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(8)
}

// ---------- [41fb] lea ($33,pc,d3.w*2), a0; =35 ----------
OPCODE(0x41FB)
	u32 adr, res;
	u32 src, dst;

	adr = GET_PC;
	DECODE_EXT_WORD
	res = adr;
	AREG((Opcode >> 9) & 7) = res;
	FINISH(12)
}
