NAKED(BccDidntBranch) {
	FINISH(8);
}

// ---------- [6201] bhi 3 ----------
OPCODE(0x6201)
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("bne BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6301] bls 3 ----------
OPCODE(0x6301)
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("beq BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6401] bcc 3 ----------
OPCODE(0x6401)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bcs BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6501] bcs 3 ----------
OPCODE(0x6501)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bcc BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6601] bne 3 ----------
OPCODE(0x6601)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("beq BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6701] beq 3 ----------
OPCODE(0x6701)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bne BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6801] bvc 3 ----------
OPCODE(0x6801)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bvs BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6901] bvs 3 ----------
OPCODE(0x6901)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bvc BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6a01] bpl 3 ----------
OPCODE(0x6A01)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bmi BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6b01] bmi 3 ----------
OPCODE(0x6B01)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bpl BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6c01] bge 3 ----------
OPCODE(0x6C01)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("blt BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6d01] blt 3 ----------
OPCODE(0x6D01)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bge BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6e01] bgt 3 ----------
OPCODE(0x6E01)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("ble BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}

// ---------- [6f01] ble 3 ----------
OPCODE(0x6F01)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bgt BccDidntBranch ");
	u32 newPC = (s32)PC + (s8)(Opcode & 0xfe);
	SET_PC_IMM(newPC);
	FINISH(10)
}
NAKED(BccDidntBranch16) {
	PC++;
	FINISH(12);
}

// ---------- [6200] bhi 3335 ----------
OPCODE(0x6200)
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("bne BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6300] bls 3335 ----------
OPCODE(0x6300)
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("beq BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6400] bcc 3335 ----------
OPCODE(0x6400)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bcs BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6500] bcs 3335 ----------
OPCODE(0x6500)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bcc BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6600] bne 3335 ----------
OPCODE(0x6600)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("beq BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6700] beq 3335 ----------
OPCODE(0x6700)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bne BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6800] bvc 3335 ----------
OPCODE(0x6800)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bvs BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6900] bvs 3335 ----------
OPCODE(0x6900)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bvc BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6a00] bpl 3335 ----------
OPCODE(0x6A00)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bmi BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6b00] bmi 3335 ----------
OPCODE(0x6B00)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bpl BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6c00] bge 3335 ----------
OPCODE(0x6C00)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("blt BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6d00] blt 3335 ----------
OPCODE(0x6D00)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bge BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6e00] bgt 3335 ----------
OPCODE(0x6E00)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("ble BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6f00] ble 3335 ----------
OPCODE(0x6F00)
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bgt BccDidntBranch16 ");
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6001] bra 3 ----------
OPCODE(0x6001)
	u32 adr, res;
	u32 src, dst;

	u32 newPC = (s32)PC + (s32)(s8)Opcode;
	SET_PC_IMM(newPC);
	CHECK_BRANCH_EXCEPTION((s8)Opcode);
	FINISH(10)
}

// ---------- [6000] bra 3335 ----------
OPCODE(0x6000)
	u32 adr, res;
	u32 src, dst;

	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	FINISH(10)
}

// ---------- [6101] bsr 3 ----------
OPCODE(0x6101)
	u32 adr, res;
	u32 src, dst;

	PRE_IO
	PUSH_32_F(GET_PC)
	u32 newPC = (s32)PC + (s32)(s8)Opcode;
	SET_PC_IMM(newPC);
	CHECK_BRANCH_EXCEPTION((s8)Opcode);
	POST_IO
	FINISH(18)
}

// ---------- [6100] bsr 3335 ----------
OPCODE(0x6100)
	u32 adr, res;
	u32 src, dst;

	PRE_IO
	PUSH_32_F(GET_PC + 2)
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION(newPC);
	POST_IO
	FINISH(18)
}
