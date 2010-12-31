
// ---------- [7000] moveq #$0, d0 ----------
OPCODE(0x7000)
	u32 adr, res;
	u32 src, dst;

	asm volatile("movs %[res], %[opcode], asl #24 " : [res] "=r" (res) : [opcode] "r" (Opcode) : "cc");
	asm volatile("mov %[res], %[res], asr #24 " : [res] "+r" (res));
	asm volatile("mrs %[flags], cpsr ;@ r11 = NZ " : [flags] "=r" (flags));
	DREGu32((Opcode >> 9) & 7) = res;
	FINISH(4)
}
