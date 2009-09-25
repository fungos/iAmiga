
// ---------- [50c0] st d0 ----------
OPCODE(0x50C0)
{
	u32 adr, res;
	u32 src, dst;

	res = ~0;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(6)
}

// ---------- [51c0] sf d0 ----------
OPCODE(0x51C0)
{
	u32 adr, res;
	u32 src, dst;

	res = 0;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [52c0] shi d0 ----------
OPCODE(0x52C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [53c0] sls d0 ----------
OPCODE(0x53C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [54c0] scc d0 ----------
OPCODE(0x54C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [55c0] scs d0 ----------
OPCODE(0x55C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [56c0] sne d0 ----------
OPCODE(0x56C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [57c0] seq d0 ----------
OPCODE(0x57C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [58c0] svc d0 ----------
OPCODE(0x58C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [59c0] svs d0 ----------
OPCODE(0x59C0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5ac0] spl d0 ----------
OPCODE(0x5AC0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5bc0] smi d0 ----------
OPCODE(0x5BC0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5cc0] sge d0 ----------
OPCODE(0x5CC0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5dc0] slt d0 ----------
OPCODE(0x5DC0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5ec0] sgt d0 ----------
OPCODE(0x5EC0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5fc0] sle d0 ----------
OPCODE(0x5FC0)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [50d0] st (a0) ----------
OPCODE(0x50D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51d0] sf (a0) ----------
OPCODE(0x51D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [52d0] shi (a0) ----------
OPCODE(0x52D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [53d0] sls (a0) ----------
OPCODE(0x53D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [54d0] scc (a0) ----------
OPCODE(0x54D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [55d0] scs (a0) ----------
OPCODE(0x55D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [56d0] sne (a0) ----------
OPCODE(0x56D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [57d0] seq (a0) ----------
OPCODE(0x57D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [58d0] svc (a0) ----------
OPCODE(0x58D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [59d0] svs (a0) ----------
OPCODE(0x59D0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5ad0] spl (a0) ----------
OPCODE(0x5AD0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5bd0] smi (a0) ----------
OPCODE(0x5BD0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5cd0] sge (a0) ----------
OPCODE(0x5CD0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5dd0] slt (a0) ----------
OPCODE(0x5DD0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5ed0] sgt (a0) ----------
OPCODE(0x5ED0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5fd0] sle (a0) ----------
OPCODE(0x5FD0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [50d8] st (a0)+ ----------
OPCODE(0x50D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51d8] sf (a0)+ ----------
OPCODE(0x51D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [52d8] shi (a0)+ ----------
OPCODE(0x52D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [53d8] sls (a0)+ ----------
OPCODE(0x53D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [54d8] scc (a0)+ ----------
OPCODE(0x54D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [55d8] scs (a0)+ ----------
OPCODE(0x55D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [56d8] sne (a0)+ ----------
OPCODE(0x56D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [57d8] seq (a0)+ ----------
OPCODE(0x57D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [58d8] svc (a0)+ ----------
OPCODE(0x58D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [59d8] svs (a0)+ ----------
OPCODE(0x59D8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5ad8] spl (a0)+ ----------
OPCODE(0x5AD8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5bd8] smi (a0)+ ----------
OPCODE(0x5BD8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5cd8] sge (a0)+ ----------
OPCODE(0x5CD8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5dd8] slt (a0)+ ----------
OPCODE(0x5DD8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5ed8] sgt (a0)+ ----------
OPCODE(0x5ED8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5fd8] sle (a0)+ ----------
OPCODE(0x5FD8)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [50e0] st -(a0) ----------
OPCODE(0x50E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51e0] sf -(a0) ----------
OPCODE(0x51E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [52e0] shi -(a0) ----------
OPCODE(0x52E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [53e0] sls -(a0) ----------
OPCODE(0x53E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [54e0] scc -(a0) ----------
OPCODE(0x54E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [55e0] scs -(a0) ----------
OPCODE(0x55E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [56e0] sne -(a0) ----------
OPCODE(0x56E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [57e0] seq -(a0) ----------
OPCODE(0x57E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [58e0] svc -(a0) ----------
OPCODE(0x58E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [59e0] svs -(a0) ----------
OPCODE(0x59E0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5ae0] spl -(a0) ----------
OPCODE(0x5AE0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5be0] smi -(a0) ----------
OPCODE(0x5BE0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5ce0] sge -(a0) ----------
OPCODE(0x5CE0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5de0] slt -(a0) ----------
OPCODE(0x5DE0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5ee0] sgt -(a0) ----------
OPCODE(0x5EE0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5fe0] sle -(a0) ----------
OPCODE(0x5FE0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [50e8] st ($3333,a0) ----------
OPCODE(0x50E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51e8] sf ($3333,a0) ----------
OPCODE(0x51E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [52e8] shi ($3333,a0) ----------
OPCODE(0x52E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [53e8] sls ($3333,a0) ----------
OPCODE(0x53E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [54e8] scc ($3333,a0) ----------
OPCODE(0x54E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [55e8] scs ($3333,a0) ----------
OPCODE(0x55E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [56e8] sne ($3333,a0) ----------
OPCODE(0x56E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [57e8] seq ($3333,a0) ----------
OPCODE(0x57E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [58e8] svc ($3333,a0) ----------
OPCODE(0x58E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [59e8] svs ($3333,a0) ----------
OPCODE(0x59E8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5ae8] spl ($3333,a0) ----------
OPCODE(0x5AE8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5be8] smi ($3333,a0) ----------
OPCODE(0x5BE8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5ce8] sge ($3333,a0) ----------
OPCODE(0x5CE8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5de8] slt ($3333,a0) ----------
OPCODE(0x5DE8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5ee8] sgt ($3333,a0) ----------
OPCODE(0x5EE8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5fe8] sle ($3333,a0) ----------
OPCODE(0x5FE8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [50f0] st ($33,a0,d3.w*2) ----------
OPCODE(0x50F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51f0] sf ($33,a0,d3.w*2) ----------
OPCODE(0x51F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [52f0] shi ($33,a0,d3.w*2) ----------
OPCODE(0x52F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [53f0] sls ($33,a0,d3.w*2) ----------
OPCODE(0x53F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [54f0] scc ($33,a0,d3.w*2) ----------
OPCODE(0x54F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [55f0] scs ($33,a0,d3.w*2) ----------
OPCODE(0x55F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [56f0] sne ($33,a0,d3.w*2) ----------
OPCODE(0x56F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [57f0] seq ($33,a0,d3.w*2) ----------
OPCODE(0x57F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [58f0] svc ($33,a0,d3.w*2) ----------
OPCODE(0x58F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [59f0] svs ($33,a0,d3.w*2) ----------
OPCODE(0x59F0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5af0] spl ($33,a0,d3.w*2) ----------
OPCODE(0x5AF0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5bf0] smi ($33,a0,d3.w*2) ----------
OPCODE(0x5BF0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5cf0] sge ($33,a0,d3.w*2) ----------
OPCODE(0x5CF0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5df0] slt ($33,a0,d3.w*2) ----------
OPCODE(0x5DF0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5ef0] sgt ($33,a0,d3.w*2) ----------
OPCODE(0x5EF0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5ff0] sle ($33,a0,d3.w*2) ----------
OPCODE(0x5FF0)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [50f8] st $3333.w ----------
OPCODE(0x50F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51f8] sf $3333.w ----------
OPCODE(0x51F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [52f8] shi $3333.w ----------
OPCODE(0x52F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [53f8] sls $3333.w ----------
OPCODE(0x53F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [54f8] scc $3333.w ----------
OPCODE(0x54F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [55f8] scs $3333.w ----------
OPCODE(0x55F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [56f8] sne $3333.w ----------
OPCODE(0x56F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [57f8] seq $3333.w ----------
OPCODE(0x57F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [58f8] svc $3333.w ----------
OPCODE(0x58F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [59f8] svs $3333.w ----------
OPCODE(0x59F8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5af8] spl $3333.w ----------
OPCODE(0x5AF8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5bf8] smi $3333.w ----------
OPCODE(0x5BF8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5cf8] sge $3333.w ----------
OPCODE(0x5CF8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5df8] slt $3333.w ----------
OPCODE(0x5DF8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5ef8] sgt $3333.w ----------
OPCODE(0x5EF8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5ff8] sle $3333.w ----------
OPCODE(0x5FF8)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_SWORD;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [50f9] st $33333333.l ----------
OPCODE(0x50F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51f9] sf $33333333.l ----------
OPCODE(0x51F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [52f9] shi $33333333.l ----------
OPCODE(0x52F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [53f9] sls $33333333.l ----------
OPCODE(0x53F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [54f9] scc $33333333.l ----------
OPCODE(0x54F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [55f9] scs $33333333.l ----------
OPCODE(0x55F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [56f9] sne $33333333.l ----------
OPCODE(0x56F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [57f9] seq $33333333.l ----------
OPCODE(0x57F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [58f9] svc $33333333.l ----------
OPCODE(0x58F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [59f9] svs $33333333.l ----------
OPCODE(0x59F9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5af9] spl $33333333.l ----------
OPCODE(0x5AF9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5bf9] smi $33333333.l ----------
OPCODE(0x5BF9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5cf9] sge $33333333.l ----------
OPCODE(0x5CF9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5df9] slt $33333333.l ----------
OPCODE(0x5DF9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5ef9] sgt $33333333.l ----------
OPCODE(0x5EF9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5ff9] sle $33333333.l ----------
OPCODE(0x5FF9)
{
	u32 adr, res;
	u32 src, dst;

	adr = FETCH_LONG;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [50df] st (a7)+ ----------
OPCODE(0x50DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51df] sf (a7)+ ----------
OPCODE(0x51DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [52df] shi (a7)+ ----------
OPCODE(0x52DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [53df] sls (a7)+ ----------
OPCODE(0x53DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [54df] scc (a7)+ ----------
OPCODE(0x54DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [55df] scs (a7)+ ----------
OPCODE(0x55DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [56df] sne (a7)+ ----------
OPCODE(0x56DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [57df] seq (a7)+ ----------
OPCODE(0x57DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [58df] svc (a7)+ ----------
OPCODE(0x58DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [59df] svs (a7)+ ----------
OPCODE(0x59DF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5adf] spl (a7)+ ----------
OPCODE(0x5ADF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5bdf] smi (a7)+ ----------
OPCODE(0x5BDF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5cdf] sge (a7)+ ----------
OPCODE(0x5CDF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5ddf] slt (a7)+ ----------
OPCODE(0x5DDF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5edf] sgt (a7)+ ----------
OPCODE(0x5EDF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5fdf] sle (a7)+ ----------
OPCODE(0x5FDF)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7);
	AREG(7) += 2;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [50e7] st -(a7) ----------
OPCODE(0x50E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	res = ~0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(6)
}

// ---------- [51e7] sf -(a7) ----------
OPCODE(0x51E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	res = 0;
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [52e7] shi -(a7) ----------
OPCODE(0x52E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [53e7] sls -(a7) ----------
OPCODE(0x53E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [54e7] scc -(a7) ----------
OPCODE(0x54E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcs %[res], #0\n\t"
			"mvncc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [55e7] scs -(a7) ----------
OPCODE(0x55E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movcc %[res], #0\n\t"
			"mvncs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subcs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [56e7] sne -(a7) ----------
OPCODE(0x56E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("moveq %[res], #0\n\t"
			"mvnne %[res], #0"
			: [res] "=r" (res));
	asm volatile("subne %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [57e7] seq -(a7) ----------
OPCODE(0x57E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movne %[res], #0\n\t"
			"mvneq %[res], #0"
			: [res] "=r" (res));
	asm volatile("subeq %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [58e7] svc -(a7) ----------
OPCODE(0x58E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvs %[res], #0\n\t"
			"mvnvc %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvc %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [59e7] svs -(a7) ----------
OPCODE(0x59E7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movvc %[res], #0\n\t"
			"mvnvs %[res], #0"
			: [res] "=r" (res));
	asm volatile("subvs %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5ae7] spl -(a7) ----------
OPCODE(0x5AE7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movmi %[res], #0\n\t"
			"mvnpl %[res], #0"
			: [res] "=r" (res));
	asm volatile("subpl %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5be7] smi -(a7) ----------
OPCODE(0x5BE7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movpl %[res], #0\n\t"
			"mvnmi %[res], #0"
			: [res] "=r" (res));
	asm volatile("submi %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5ce7] sge -(a7) ----------
OPCODE(0x5CE7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movlt %[res], #0\n\t"
			"mvnge %[res], #0"
			: [res] "=r" (res));
	asm volatile("subge %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5de7] slt -(a7) ----------
OPCODE(0x5DE7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movge %[res], #0\n\t"
			"mvnlt %[res], #0"
			: [res] "=r" (res));
	asm volatile("sublt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5ee7] sgt -(a7) ----------
OPCODE(0x5EE7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movle %[res], #0\n\t"
			"mvngt %[res], #0"
			: [res] "=r" (res));
	asm volatile("subgt %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5fe7] sle -(a7) ----------
OPCODE(0x5FE7)
{
	u32 adr, res;
	u32 src, dst;

	adr = AREG(7) - 2;
	AREG(7) = adr;
	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("movgt %[res], #0\n\t"
			"mvnle %[res], #0"
			: [res] "=r" (res));
	asm volatile("suble %[cycles], #2": [cycles] "=r" (cycles));
	PRE_IO
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}
// used by dbcc instructions, to keep code size down 
NAKED(DbraMin1) {
	PC++;
	FINISH(14);
}

// ---------- [50c8] dbt d0, 3335 ----------
OPCODE(0x50C8)
{
	u32 adr, res;
	u32 src, dst;

	PC++;
	FINISH(12)
}

// ---------- [51c8] dbra d0, 3335 ----------
OPCODE(0x51C8)
{
	u32 adr, res;
	u32 src, dst;

	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [52c8] dbhi d0, 3335 ----------
OPCODE(0x52C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("beq OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [53c8] dbls d0, 3335 ----------
OPCODE(0x53C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("tst %[flags], #0x60000000" :: [flags] "r" (flags) : "cc"); // C || V
	asm volatile("bne OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [54c8] dbcc d0, 3335 ----------
OPCODE(0x54C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bcc OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [55c8] dbcs d0, 3335 ----------
OPCODE(0x55C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bcs OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [56c8] dbne d0, 3335 ----------
OPCODE(0x56C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bne OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [57c8] dbeq d0, 3335 ----------
OPCODE(0x57C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("beq OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [58c8] dbvc d0, 3335 ----------
OPCODE(0x58C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bvc OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [59c8] dbvs d0, 3335 ----------
OPCODE(0x59C8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bvs OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [5ac8] dbpl d0, 3335 ----------
OPCODE(0x5AC8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bpl OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [5bc8] dbmi d0, 3335 ----------
OPCODE(0x5BC8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bmi OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [5cc8] dbge d0, 3335 ----------
OPCODE(0x5CC8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bge OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [5dc8] dblt d0, 3335 ----------
OPCODE(0x5DC8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("blt OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [5ec8] dbgt d0, 3335 ----------
OPCODE(0x5EC8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("bgt OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [5fc8] dble d0, 3335 ----------
OPCODE(0x5FC8)
{
	u32 adr, res;
	u32 src, dst;

	asm volatile("msr cpsr_flg, %[flags]" :: [flags] "r" (flags) : "cc");
	asm volatile("ble OP0x50C8 ");
	res = DREGu16((Opcode >> 0) & 7);
	res--;
	DREGu16((Opcode >> 0) & 7) = res;
	asm volatile("cmn %[res], #1 \n"
		"\tbeq DbraMin1":: [res] "r" (res)); 
	u32 newPC = (s32)PC + GET_SWORD;
	SET_PC(newPC);
	CHECK_BRANCH_EXCEPTION((s32)PC);
	FINISH(10)
}

// ---------- [5000] addq.b #8, d0 ----------
OPCODE(0x5000)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	dst = DREGu8((Opcode >> 0) & 7);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5010] addq.b #8, (a0) ----------
OPCODE(0x5010)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5018] addq.b #8, (a0)+ ----------
OPCODE(0x5018)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5020] addq.b #8, -(a0) ----------
OPCODE(0x5020)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5028] addq.b #8, ($3333,a0) ----------
OPCODE(0x5028)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5030] addq.b #8, ($33,a0,d3.w*2) ----------
OPCODE(0x5030)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5038] addq.b #8, $3333.w ----------
OPCODE(0x5038)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5039] addq.b #8, $33333333.l ----------
OPCODE(0x5039)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [501f] addq.b #8, (a7)+ ----------
OPCODE(0x501F)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5027] addq.b #8, -(a7) ----------
OPCODE(0x5027)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5040] addq.w #8, d0 ----------
OPCODE(0x5040)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	dst = DREGu16((Opcode >> 0) & 7);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5048] addq.w #8, a0 ----------
OPCODE(0x5048)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5050] addq.w #8, (a0) ----------
OPCODE(0x5050)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5058] addq.w #8, (a0)+ ----------
OPCODE(0x5058)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5060] addq.w #8, -(a0) ----------
OPCODE(0x5060)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5068] addq.w #8, ($3333,a0) ----------
OPCODE(0x5068)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5070] addq.w #8, ($33,a0,d3.w*2) ----------
OPCODE(0x5070)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5078] addq.w #8, $3333.w ----------
OPCODE(0x5078)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5079] addq.w #8, $33333333.l ----------
OPCODE(0x5079)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [505f] addq.w #8, (a7)+ ----------
OPCODE(0x505F)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5067] addq.w #8, -(a7) ----------
OPCODE(0x5067)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5080] addq.l #8, d0 ----------
OPCODE(0x5080)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	dst = DREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5088] addq.l #8, a0 ----------
OPCODE(0x5088)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5090] addq.l #8, (a0) ----------
OPCODE(0x5090)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5098] addq.l #8, (a0)+ ----------
OPCODE(0x5098)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [50a0] addq.l #8, -(a0) ----------
OPCODE(0x50A0)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [50a8] addq.l #8, ($3333,a0) ----------
OPCODE(0x50A8)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [50b0] addq.l #8, ($33,a0,d3.w*2) ----------
OPCODE(0x50B0)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [50b8] addq.l #8, $3333.w ----------
OPCODE(0x50B8)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [50b9] addq.l #8, $33333333.l ----------
OPCODE(0x50B9)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [509f] addq.l #8, (a7)+ ----------
OPCODE(0x509F)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [50a7] addq.l #8, -(a7) ----------
OPCODE(0x50A7)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [5200] addq.b #1, d0 ----------
OPCODE(0x5200)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = DREGu8((Opcode >> 0) & 7);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5210] addq.b #1, (a0) ----------
OPCODE(0x5210)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5218] addq.b #1, (a0)+ ----------
OPCODE(0x5218)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5220] addq.b #1, -(a0) ----------
OPCODE(0x5220)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5228] addq.b #1, ($3333,a0) ----------
OPCODE(0x5228)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5230] addq.b #1, ($33,a0,d3.w*2) ----------
OPCODE(0x5230)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5238] addq.b #1, $3333.w ----------
OPCODE(0x5238)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5239] addq.b #1, $33333333.l ----------
OPCODE(0x5239)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [521f] addq.b #1, (a7)+ ----------
OPCODE(0x521F)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5227] addq.b #1, -(a7) ----------
OPCODE(0x5227)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5240] addq.w #1, d0 ----------
OPCODE(0x5240)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = DREGu16((Opcode >> 0) & 7);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5248] addq.w #1, a0 ----------
OPCODE(0x5248)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5250] addq.w #1, (a0) ----------
OPCODE(0x5250)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5258] addq.w #1, (a0)+ ----------
OPCODE(0x5258)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5260] addq.w #1, -(a0) ----------
OPCODE(0x5260)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5268] addq.w #1, ($3333,a0) ----------
OPCODE(0x5268)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5270] addq.w #1, ($33,a0,d3.w*2) ----------
OPCODE(0x5270)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(18)
}

// ---------- [5278] addq.w #1, $3333.w ----------
OPCODE(0x5278)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(16)
}

// ---------- [5279] addq.w #1, $33333333.l ----------
OPCODE(0x5279)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [525f] addq.w #1, (a7)+ ----------
OPCODE(0x525F)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5267] addq.w #1, -(a7) ----------
OPCODE(0x5267)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "adds %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5280] addq.l #1, d0 ----------
OPCODE(0x5280)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = DREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5288] addq.l #1, a0 ----------
OPCODE(0x5288)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5290] addq.l #1, (a0) ----------
OPCODE(0x5290)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5298] addq.l #1, (a0)+ ----------
OPCODE(0x5298)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [52a0] addq.l #1, -(a0) ----------
OPCODE(0x52A0)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [52a8] addq.l #1, ($3333,a0) ----------
OPCODE(0x52A8)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [52b0] addq.l #1, ($33,a0,d3.w*2) ----------
OPCODE(0x52B0)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [52b8] addq.l #1, $3333.w ----------
OPCODE(0x52B8)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [52b9] addq.l #1, $33333333.l ----------
OPCODE(0x52B9)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [529f] addq.l #1, (a7)+ ----------
OPCODE(0x529F)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [52a7] addq.l #1, -(a7) ----------
OPCODE(0x52A7)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "adds %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags "
	     : "=r" (flags)); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [5100] subq.b #8, d0 ----------
OPCODE(0x5100)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	dst = DREGu8((Opcode >> 0) & 7);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5110] subq.b #8, (a0) ----------
OPCODE(0x5110)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5118] subq.b #8, (a0)+ ----------
OPCODE(0x5118)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5120] subq.b #8, -(a0) ----------
OPCODE(0x5120)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5128] subq.b #8, ($3333,a0) ----------
OPCODE(0x5128)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5130] subq.b #8, ($33,a0,d3.w*2) ----------
OPCODE(0x5130)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5138] subq.b #8, $3333.w ----------
OPCODE(0x5138)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5139] subq.b #8, $33333333.l ----------
OPCODE(0x5139)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [511f] subq.b #8, (a7)+ ----------
OPCODE(0x511F)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5127] subq.b #8, -(a7) ----------
OPCODE(0x5127)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 24;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5140] subq.w #8, d0 ----------
OPCODE(0x5140)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	dst = DREGu16((Opcode >> 0) & 7);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5148] subq.w #8, a0 ----------
OPCODE(0x5148)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5150] subq.w #8, (a0) ----------
OPCODE(0x5150)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5158] subq.w #8, (a0)+ ----------
OPCODE(0x5158)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5160] subq.w #8, -(a0) ----------
OPCODE(0x5160)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5168] subq.w #8, ($3333,a0) ----------
OPCODE(0x5168)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5170] subq.w #8, ($33,a0,d3.w*2) ----------
OPCODE(0x5170)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5178] subq.w #8, $3333.w ----------
OPCODE(0x5178)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5179] subq.w #8, $33333333.l ----------
OPCODE(0x5179)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [515f] subq.w #8, (a7)+ ----------
OPCODE(0x515F)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5167] subq.w #8, -(a7) ----------
OPCODE(0x5167)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	src <<= 16;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5180] subq.l #8, d0 ----------
OPCODE(0x5180)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	dst = DREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5188] subq.l #8, a0 ----------
OPCODE(0x5188)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5190] subq.l #8, (a0) ----------
OPCODE(0x5190)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5198] subq.l #8, (a0)+ ----------
OPCODE(0x5198)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [51a0] subq.l #8, -(a0) ----------
OPCODE(0x51A0)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [51a8] subq.l #8, ($3333,a0) ----------
OPCODE(0x51A8)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [51b0] subq.l #8, ($33,a0,d3.w*2) ----------
OPCODE(0x51B0)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [51b8] subq.l #8, $3333.w ----------
OPCODE(0x51B8)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [51b9] subq.l #8, $33333333.l ----------
OPCODE(0x51B9)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [519f] subq.l #8, (a7)+ ----------
OPCODE(0x519F)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [51a7] subq.l #8, -(a7) ----------
OPCODE(0x51A7)
{
	u32 adr, res;
	u32 src, dst;

	src = 0x08;
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src]"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [5300] subq.b #1, d0 ----------
OPCODE(0x5300)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = DREGu8((Opcode >> 0) & 7);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	DREGu8((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5310] subq.b #1, (a0) ----------
OPCODE(0x5310)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5318] subq.b #1, (a0)+ ----------
OPCODE(0x5318)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 1;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5320] subq.b #1, -(a0) ----------
OPCODE(0x5320)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7) - 1;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5328] subq.b #1, ($3333,a0) ----------
OPCODE(0x5328)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5330] subq.b #1, ($33,a0,d3.w*2) ----------
OPCODE(0x5330)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5338] subq.b #1, $3333.w ----------
OPCODE(0x5338)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5339] subq.b #1, $33333333.l ----------
OPCODE(0x5339)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [531f] subq.b #1, (a7)+ ----------
OPCODE(0x531F)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5327] subq.b #1, -(a7) ----------
OPCODE(0x5327)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_BYTE_F(adr);
	dst <<= 24;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #15"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 24;
	WRITE_BYTE_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5340] subq.w #1, d0 ----------
OPCODE(0x5340)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = DREGu16((Opcode >> 0) & 7);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	DREGu16((Opcode >> 0) & 7) = res;
	FINISH(4)
}

// ---------- [5348] subq.w #1, a0 ----------
OPCODE(0x5348)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5350] subq.w #1, (a0) ----------
OPCODE(0x5350)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5358] subq.w #1, (a0)+ ----------
OPCODE(0x5358)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5360] subq.w #1, -(a0) ----------
OPCODE(0x5360)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7) - 2;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5368] subq.w #1, ($3333,a0) ----------
OPCODE(0x5368)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5370] subq.w #1, ($33,a0,d3.w*2) ----------
OPCODE(0x5370)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5378] subq.w #1, $3333.w ----------
OPCODE(0x5378)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [5379] subq.w #1, $33333333.l ----------
OPCODE(0x5379)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
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

// ---------- [535f] subq.w #1, (a7)+ ----------
OPCODE(0x535F)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7);
	AREG(7) += 2;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(12)
}

// ---------- [5367] subq.w #1, -(a7) ----------
OPCODE(0x5367)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7) - 2;
	AREG(7) = adr;
	PRE_IO
	dst = READ_WORD_F(adr);
	dst <<= 16;
	asm volatile(
		 "subs %[res], %[dst], %[src],lsl #7"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	res >>= 16;
	WRITE_WORD_F(adr, res)
	POST_IO
	FINISH(14)
}

// ---------- [5380] subq.l #1, d0 ----------
OPCODE(0x5380)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = DREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	DREGu32((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5388] subq.l #1, a0 ----------
OPCODE(0x5388)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	dst = AREGu32((Opcode >> 0) & 7);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	AREG((Opcode >> 0) & 7) = res;
	FINISH(8)
}

// ---------- [5390] subq.l #1, (a0) ----------
OPCODE(0x5390)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [5398] subq.l #1, (a0)+ ----------
OPCODE(0x5398)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	AREG((Opcode >> 0) & 7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [53a0] subq.l #1, -(a0) ----------
OPCODE(0x53A0)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7) - 4;
	AREG((Opcode >> 0) & 7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}

// ---------- [53a8] subq.l #1, ($3333,a0) ----------
OPCODE(0x53A8)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	adr += AREG((Opcode >> 0) & 7);
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [53b0] subq.l #1, ($33,a0,d3.w*2) ----------
OPCODE(0x53B0)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG((Opcode >> 0) & 7);
	DECODE_EXT_WORD
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(26)
}

// ---------- [53b8] subq.l #1, $3333.w ----------
OPCODE(0x53B8)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_SWORD;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(24)
}

// ---------- [53b9] subq.l #1, $33333333.l ----------
OPCODE(0x53B9)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = FETCH_LONG;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(28)
}

// ---------- [539f] subq.l #1, (a7)+ ----------
OPCODE(0x539F)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7);
	AREG(7) += 4;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(20)
}

// ---------- [53a7] subq.l #1, -(a7) ----------
OPCODE(0x53A7)
{
	u32 adr, res;
	u32 src, dst;

	src = Opcode & 0x0e00;
	adr = AREG(7) - 4;
	AREG(7) = adr;
	PRE_IO
	dst = READ_LONG_F(adr);
	asm volatile(
		 "subs %[res], %[dst], %[src],lsr #9"
		 : [res] "=r" (res)
		 : [dst] "r" (dst), [src] "r" (src)
		 : "cc");
	// get flags
	asm volatile("mrs %0, cpsr ;@ flags \n"
	     "\teor %0,%0,#0x20000000 ;@ Invert carry \n"
	     : "=r" (flags) : [res] "r" (res) : "cc"); 
	X_FLAG = flags; 
	WRITE_LONG_F(adr, res)
	POST_IO
	FINISH(22)
}
