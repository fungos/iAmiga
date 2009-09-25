
// ---------- [e000] asr.b #8, d0 ----------
OPCODE(0xE000)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = (s32)DREGs8((Opcode >> 0) & 7);
	src <<= 24;
	src = ((s32)src) >> 24;
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e040] asr.w #8, d0 ----------
OPCODE(0xE040)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = (s32)DREGs16((Opcode >> 0) & 7);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e080] asr.l #8, d0 ----------
OPCODE(0xE080)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = (s32)DREGs32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e200] asr.b #1, d0 ----------
OPCODE(0xE200)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = (s32)DREGs8((Opcode >> 0) & 7);
	src <<= 24;
	src = ((s32)src) >> 24;
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e240] asr.w #1, d0 ----------
OPCODE(0xE240)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = (s32)DREGs16((Opcode >> 0) & 7);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e280] asr.l #1, d0 ----------
OPCODE(0xE280)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = (s32)DREGs32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e008] lsr.b #8, d0 ----------
OPCODE(0xE008)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	src >>= 24;
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e048] lsr.w #8, d0 ----------
OPCODE(0xE048)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e088] lsr.l #8, d0 ----------
OPCODE(0xE088)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e208] lsr.b #1, d0 ----------
OPCODE(0xE208)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	src >>= 24;
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e248] lsr.w #1, d0 ----------
OPCODE(0xE248)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e288] lsr.l #1, d0 ----------
OPCODE(0xE288)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e010] roxr.b #8, d0 ----------
OPCODE(0xE010)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	src >>= 24;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (8 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #9\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e050] roxr.w #8, d0 ----------
OPCODE(0xE050)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	src >>= 16;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (16 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #17\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e090] roxr.l #8, d0 ----------
OPCODE(0xE090)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu32((Opcode >> 0) & 7);
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (32 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #33\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e210] roxr.b #1, d0 ----------
OPCODE(0xE210)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	src >>= 24;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (8 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #9\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e250] roxr.w #1, d0 ----------
OPCODE(0xE250)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	src >>= 16;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (16 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #17\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e290] roxr.l #1, d0 ----------
OPCODE(0xE290)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (32 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #33\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e018] ror.b #8, d0 ----------
OPCODE(0xE018)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	// replicate bits across entire 32-bit word
	src |= src >> 8;
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e058] ror.w #8, d0 ----------
OPCODE(0xE058)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e098] ror.l #8, d0 ----------
OPCODE(0xE098)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu32((Opcode >> 0) & 7);
	// replicate bits across entire 32-bit word
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e218] ror.b #1, d0 ----------
OPCODE(0xE218)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	// replicate bits across entire 32-bit word
	src |= src >> 8;
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e258] ror.w #1, d0 ----------
OPCODE(0xE258)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e298] ror.l #1, d0 ----------
OPCODE(0xE298)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	// replicate bits across entire 32-bit word
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e100] asl.b #8, d0 ----------
OPCODE(0xE100)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e140] asl.w #8, d0 ----------
OPCODE(0xE140)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e180] asl.l #8, d0 ----------
OPCODE(0xE180)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e300] asl.b #1, d0 ----------
OPCODE(0xE300)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e340] asl.w #1, d0 ----------
OPCODE(0xE340)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e380] asl.l #1, d0 ----------
OPCODE(0xE380)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e108] lsl.b #8, d0 ----------
OPCODE(0xE108)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e148] lsl.w #8, d0 ----------
OPCODE(0xE148)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e188] lsl.l #8, d0 ----------
OPCODE(0xE188)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e308] lsl.b #1, d0 ----------
OPCODE(0xE308)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e348] lsl.w #1, d0 ----------
OPCODE(0xE348)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e388] lsl.l #1, d0 ----------
OPCODE(0xE388)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e110] roxl.b #8, d0 ----------
OPCODE(0xE110)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	src >>= 24;
	sft = 9 - sft;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (8 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #9\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e150] roxl.w #8, d0 ----------
OPCODE(0xE150)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	src >>= 16;
	sft = 17 - sft;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (16 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #17\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e190] roxl.l #8, d0 ----------
OPCODE(0xE190)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu32((Opcode >> 0) & 7);
	sft = 33 - sft;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (32 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #33\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e310] roxl.b #1, d0 ----------
OPCODE(0xE310)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	src >>= 24;
	sft = 9 - sft;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (8 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #9\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e350] roxl.w #1, d0 ----------
OPCODE(0xE350)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	src >>= 16;
	sft = 17 - sft;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (16 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #17\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e390] roxl.l #1, d0 ----------
OPCODE(0xE390)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	sft = 33 - sft;
	// get X bit
	u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
	xBit <<= (32 - sft);

	// shift bits
	res = (src >> sft) | xBit;
	asm volatile("rsbs %[sft], %[sft], #33\n\t"
		"orrs %[res], %[res], %[src], lsl %[sft]"
		: [sft] "+r" (sft), [res] "+r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e118] rol.b #8, d0 ----------
OPCODE(0xE118)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	// replicate bits across entire 32-bit word
	src |= src >> 8;
	src |= src >> 16;
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e158] rol.w #8, d0 ----------
OPCODE(0xE158)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(22)
}

// ---------- [e198] rol.l #8, d0 ----------
OPCODE(0xE198)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft = 8;
	src = DREGu32((Opcode >> 0) & 7);
	// replicate bits across entire 32-bit word
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(24)
}

// ---------- [e318] rol.b #1, d0 ----------
OPCODE(0xE318)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	// replicate bits across entire 32-bit word
	src |= src >> 8;
	src |= src >> 16;
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e358] rol.w #1, d0 ----------
OPCODE(0xE358)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e398] rol.l #1, d0 ----------
OPCODE(0xE398)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;

	sft = (Opcode >> 9) & 7;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	// replicate bits across entire 32-bit word
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [e020] asr.b d0, d0 ----------
OPCODE(0xE020)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = (s32)DREGs8((Opcode >> 0) & 7);
	src <<= 24;
	src = ((s32)src) >> 24;
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	res <<= 24;
	res = ((s32)res) >> 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e060] asr.w d0, d0 ----------
OPCODE(0xE060)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = (s32)DREGs16((Opcode >> 0) & 7);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	res <<= 16;
	res = ((s32)res) >> 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e0a0] asr.l d0, d0 ----------
OPCODE(0xE0A0)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = (s32)DREGs32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], asr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e028] lsr.b d0, d0 ----------
OPCODE(0xE028)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	src >>= 24;
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e068] lsr.w d0, d0 ----------
OPCODE(0xE068)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e0a8] lsr.l d0, d0 ----------
OPCODE(0xE0A8)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], lsr %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e030] roxr.b d0, d0 ----------
OPCODE(0xE030)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	if (sft) {
	src <<= 24;
	src >>= 24;
		sft %= 9;
		// get X bit
		u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
		xBit <<= (8 - sft);

		// shift bits
		res = (src >> sft) | xBit;
		asm volatile("rsbs %[sft], %[sft], #9\n\t"
			"orrs %[res], %[res], %[src], lsl %[sft]"
			: [sft] "+r" (sft), [res] "+r" (res)
			: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	} else {
		asm volatile("adds %[res], %[src], #0"
						 : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
		flags |= (X_FLAG & 0x20000000);
	}
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e070] roxr.w d0, d0 ----------
OPCODE(0xE070)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	if (sft) {
	src <<= 16;
	src >>= 16;
		sft %= 17;
		// get X bit
		u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
		xBit <<= (16 - sft);

		// shift bits
		res = (src >> sft) | xBit;
		asm volatile("rsbs %[sft], %[sft], #17\n\t"
			"orrs %[res], %[res], %[src], lsl %[sft]"
			: [sft] "+r" (sft), [res] "+r" (res)
			: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	} else {
		asm volatile("adds %[res], %[src], #0"
						 : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
		flags |= (X_FLAG & 0x20000000);
	}
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e0b0] roxr.l d0, d0 ----------
OPCODE(0xE0B0)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	if (sft) {
		sft %= 33;
		// get X bit
		u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
		xBit <<= (32 - sft);

		// shift bits
		res = (src >> sft) | xBit;
		asm volatile("rsbs %[sft], %[sft], #33\n\t"
			"orrs %[res], %[res], %[src], lsl %[sft]"
			: [sft] "+r" (sft), [res] "+r" (res)
			: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	} else {
		asm volatile("adds %[res], %[src], #0"
						 : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
		flags |= (X_FLAG & 0x20000000);
	}
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e038] ror.b d0, d0 ----------
OPCODE(0xE038)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	// replicate bits across entire 32-bit word
	src |= src >> 8;
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e078] ror.w d0, d0 ----------
OPCODE(0xE078)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e0b8] ror.l d0, d0 ----------
OPCODE(0xE0B8)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	// replicate bits across entire 32-bit word
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e120] asl.b d0, d0 ----------
OPCODE(0xE120)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e160] asl.w d0, d0 ----------
OPCODE(0xE160)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e1a0] asl.l d0, d0 ----------
OPCODE(0xE1A0)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl %[sft]"
		: [res] "=r" (res), [src] "+r" (src)
		: [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr %[sft]\n\t"
			"cmpne	%[src], %[msk], asr %[sft]\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk), [sft] "r" (sft)
			: "cc");
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e128] lsl.b d0, d0 ----------
OPCODE(0xE128)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e168] lsl.w d0, d0 ----------
OPCODE(0xE168)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e1a8] lsl.l d0, d0 ----------
OPCODE(0xE1A8)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	asm volatile("movs %[res], %[src], lsl %[sft]"
		: [res] "=r" (res) : [src] "r" (src), [sft] "r" (sft) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	if (!sft) flags &= ~0x20000000; // clear C if no shift
	else X_FLAG = flags;
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e130] roxl.b d0, d0 ----------
OPCODE(0xE130)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	if (sft) {
	src <<= 24;
	src >>= 24;
		sft %= 9;
	sft = 9 - sft;
		// get X bit
		u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
		xBit <<= (8 - sft);

		// shift bits
		res = (src >> sft) | xBit;
		asm volatile("rsbs %[sft], %[sft], #9\n\t"
			"orrs %[res], %[res], %[src], lsl %[sft]"
			: [sft] "+r" (sft), [res] "+r" (res)
			: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #24"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	} else {
		asm volatile("adds %[res], %[src], #0"
						 : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
		flags |= (X_FLAG & 0x20000000);
	}
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e170] roxl.w d0, d0 ----------
OPCODE(0xE170)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	if (sft) {
	src <<= 16;
	src >>= 16;
		sft %= 17;
	sft = 17 - sft;
		// get X bit
		u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
		xBit <<= (16 - sft);

		// shift bits
		res = (src >> sft) | xBit;
		asm volatile("rsbs %[sft], %[sft], #17\n\t"
			"orrs %[res], %[res], %[src], lsl %[sft]"
			: [sft] "+r" (sft), [res] "+r" (res)
			: [src] "r" (src) : "cc");
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	} else {
		asm volatile("adds %[res], %[src], #0"
						 : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
		flags |= (X_FLAG & 0x20000000);
	}
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e1b0] roxl.l d0, d0 ----------
OPCODE(0xE1B0)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	if (sft) {
		sft %= 33;
	sft = 33 - sft;
		// get X bit
		u32 xBit = (X_FLAG & 0x20000000) ? 1 : 0;
		xBit <<= (32 - sft);

		// shift bits
		res = (src >> sft) | xBit;
		asm volatile("rsbs %[sft], %[sft], #33\n\t"
			"orrs %[res], %[res], %[src], lsl %[sft]"
			: [sft] "+r" (sft), [res] "+r" (res)
			: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	} else {
		asm volatile("adds %[res], %[src], #0"
						 : [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
		flags |= (X_FLAG & 0x20000000);
	}
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e138] rol.b d0, d0 ----------
OPCODE(0xE138)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu8((Opcode >> 0) & 7);
	src <<= 24;
	// replicate bits across entire 32-bit word
	src |= src >> 8;
	src |= src >> 16;
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e178] rol.w d0, d0 ----------
OPCODE(0xE178)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu16((Opcode >> 0) & 7);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e1b8] rol.l d0, d0 ----------
OPCODE(0xE1B8)
{
	u32 adr, res;
	u32 src, dst;

	u32 sft;
	sft = DREG((Opcode >> 9) & 7) & 0x3F;
	cycles -= sft * 2;
	src = DREGu32((Opcode >> 0) & 7);
	// replicate bits across entire 32-bit word
	sft = 32 - sft;
	asm volatile("movs %[res], %[src], ror %[sft]"
		: [res] "=r" (res)
		: [sft] "r" (sft), [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [e0d0] asr.w (a0) ----------
OPCODE(0xE0D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e0d8] asr.w (a0)+ ----------
OPCODE(0xE0D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e0e0] asr.w -(a0) ----------
OPCODE(0xE0E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e0e8] asr.w ($3333,a0) ----------
OPCODE(0xE0E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e0f0] asr.w ($33,a0,d3.w*2) ----------
OPCODE(0xE0F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e0f8] asr.w $3333.w ----------
OPCODE(0xE0F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e0f9] asr.w $33333333.l ----------
OPCODE(0xE0F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e0df] asr.w (a7)+ ----------
OPCODE(0xE0DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e0e7] asr.w -(a7) ----------
OPCODE(0xE0E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src = ((s32)src) >> 16;
	asm volatile("movs %[res], %[src], asr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e2d0] lsr.w (a0) ----------
OPCODE(0xE2D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e2d8] lsr.w (a0)+ ----------
OPCODE(0xE2D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e2e0] lsr.w -(a0) ----------
OPCODE(0xE2E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e2e8] lsr.w ($3333,a0) ----------
OPCODE(0xE2E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e2f0] lsr.w ($33,a0,d3.w*2) ----------
OPCODE(0xE2F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e2f8] lsr.w $3333.w ----------
OPCODE(0xE2F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e2f9] lsr.w $33333333.l ----------
OPCODE(0xE2F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e2df] lsr.w (a7)+ ----------
OPCODE(0xE2DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e2e7] lsr.w -(a7) ----------
OPCODE(0xE2E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	asm volatile("movs %[res], %[src], lsr #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	asm volatile("movs %[res], %[res], lsl #16"
		: [res] "+r" (res) : : "cc");
	asm volatile("orrmi %[flags], %[flags], #0x80000000"
		: [flags] "+r" (flags) : "r" (res) : "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e4d0] roxr.w (a0) ----------
OPCODE(0xE4D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e4d8] roxr.w (a0)+ ----------
OPCODE(0xE4D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e4e0] roxr.w -(a0) ----------
OPCODE(0xE4E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e4e8] roxr.w ($3333,a0) ----------
OPCODE(0xE4E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e4f0] roxr.w ($33,a0,d3.w*2) ----------
OPCODE(0xE4F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e4f8] roxr.w $3333.w ----------
OPCODE(0xE4F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e4f9] roxr.w $33333333.l ----------
OPCODE(0xE4F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e4df] roxr.w (a7)+ ----------
OPCODE(0xE4DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e4e7] roxr.w -(a7) ----------
OPCODE(0xE4E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	src &= 0x10000;
	asm volatile("msr cpsr_flg, %[x_flag]\n\t"
		"movs %[res], %[src], rrx ;@ rotate right, with eXtend"
		:[res] "=r" (res): [src] "r" (src), [x_flag] "r" (X_FLAG) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	flags &= ~0x10000000; // clear V flag
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e6d0] ror.w (a0) ----------
OPCODE(0xE6D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e6d8] ror.w (a0)+ ----------
OPCODE(0xE6D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e6e0] ror.w -(a0) ----------
OPCODE(0xE6E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e6e8] ror.w ($3333,a0) ----------
OPCODE(0xE6E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e6f0] ror.w ($33,a0,d3.w*2) ----------
OPCODE(0xE6F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e6f8] ror.w $3333.w ----------
OPCODE(0xE6F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e6f9] ror.w $33333333.l ----------
OPCODE(0xE6F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e6df] ror.w (a7)+ ----------
OPCODE(0xE6DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e6e7] ror.w -(a7) ----------
OPCODE(0xE6E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	src >>= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], ror #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e1d0] asl.w (a0) ----------
OPCODE(0xE1D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e1d8] asl.w (a0)+ ----------
OPCODE(0xE1D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e1e0] asl.w -(a0) ----------
OPCODE(0xE1E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e1e8] asl.w ($3333,a0) ----------
OPCODE(0xE1E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e1f0] asl.w ($33,a0,d3.w*2) ----------
OPCODE(0xE1F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e1f8] asl.w $3333.w ----------
OPCODE(0xE1F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e1f9] asl.w $33333333.l ----------
OPCODE(0xE1F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e1df] asl.w (a7)+ ----------
OPCODE(0xE1DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e1e7] asl.w -(a7) ----------
OPCODE(0xE1E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("adds %[src], %[src], #0 ;@ saves V and clears C first\n\t"
		"movs %[res], %[src], asl #1"
		: [res] "=r" (res), [src] "+r" (src)
		: : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	// calculate V flag
	u32 msk = 0x80000000;
	asm("ands	%[src], %[src], %[msk], asr #1\n\t"
			"cmpne	%[src], %[msk], asr #1\n\t"
			"eoreq	%[src], %[res], %[src]\n\t"
			"tsteq	%[src], #0x80000000\n\t"
			"orrne	%[flags], %[flags], #0x10000000"
			: [src] "+r" (src), [flags] "+r" (flags)
			: [res] "r" (res), [msk] "r" (msk)
			: "cc");
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e3d0] lsl.w (a0) ----------
OPCODE(0xE3D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e3d8] lsl.w (a0)+ ----------
OPCODE(0xE3D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e3e0] lsl.w -(a0) ----------
OPCODE(0xE3E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e3e8] lsl.w ($3333,a0) ----------
OPCODE(0xE3E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e3f0] lsl.w ($33,a0,d3.w*2) ----------
OPCODE(0xE3F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e3f8] lsl.w $3333.w ----------
OPCODE(0xE3F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e3f9] lsl.w $33333333.l ----------
OPCODE(0xE3F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e3df] lsl.w (a7)+ ----------
OPCODE(0xE3DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e3e7] lsl.w -(a7) ----------
OPCODE(0xE3E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e5d0] roxl.w (a0) ----------
OPCODE(0xE5D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e5d8] roxl.w (a0)+ ----------
OPCODE(0xE5D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e5e0] roxl.w -(a0) ----------
OPCODE(0xE5E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e5e8] roxl.w ($3333,a0) ----------
OPCODE(0xE5E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e5f0] roxl.w ($33,a0,d3.w*2) ----------
OPCODE(0xE5F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e5f8] roxl.w $3333.w ----------
OPCODE(0xE5F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e5f9] roxl.w $33333333.l ----------
OPCODE(0xE5F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e5df] roxl.w (a7)+ ----------
OPCODE(0xE5DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e5e7] roxl.w -(a7) ----------
OPCODE(0xE5E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
u32 old_x = X_FLAG;
	asm volatile("movs %[res], %[src], lsl #1"
		: [res] "=r" (res) : [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
// add old X
	if (old_x & 0x20000000) {
		res |= 0x10000;
		flags &= ~0x40000000; // clear Z and V
	}
	flags &= ~0x10000000; // clear V
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e7d0] rol.w (a0) ----------
OPCODE(0xE7D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e7d8] rol.w (a0)+ ----------
OPCODE(0xE7D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e7e0] rol.w -(a0) ----------
OPCODE(0xE7E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [e7e8] rol.w ($3333,a0) ----------
OPCODE(0xE7E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e7f0] rol.w ($33,a0,d3.w*2) ----------
OPCODE(0xE7F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [e7f8] rol.w $3333.w ----------
OPCODE(0xE7F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [e7f9] rol.w $33333333.l ----------
OPCODE(0xE7F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [e7df] rol.w (a7)+ ----------
OPCODE(0xE7DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [e7e7] rol.w -(a7) ----------
OPCODE(0xE7E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	src = READ_WORD_F(adr);
	src <<= 16;
	// replicate bits across entire 32-bit word
	src |= src >> 16;
	asm volatile("movs %[res], %[src], ror #31"
		: [res] "=r" (res)
		: [src] "r" (src) : "cc");
	// get flags
	asm volatile("mrs %[flags], cpsr ;@ flags "
	     : [flags] "=r" (flags)); 
	flags &= ~0x30000000; // clears C & V
	if (res & 1) flags |= 0x20000000; // set C from bit 0
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}
