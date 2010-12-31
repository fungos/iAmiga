/*
 *  i68kcore.cpp
 *  M68kTests
 *
 *  Created by Stuart Carnie on 7/2/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#import "sysconfig.h"

#ifdef USE_FAME_CORE_ARM2

#import "sysdeps.h"

#import <stdio.h>
#import <memory>
//#import <stdlib.h>

#define USE_BRANCHES 1

#pragma mark -
#pragma mark debug routines

#define NO_BREAKPOINTS	1

#if DISASSEMBLER || defined(DEBUG_CPU)

//#undef USE_BRANCHES
//#define USE_BRANCHES 0

int do_disa = 0;
int do_debug = 0;
int disa_step = 0;
int instruction_cycles;

#if NO_BREAKPOINTS
#define CHECK_BREAKPOINTS
#else
#define CHECK_BREAKPOINTS	check_breakpoints();
#endif

#define STORE_COUNTER		instruction_cycles = cycles;
#define UPDATE_COUNTER(CYC)	instruction_cycles = instruction_cycles - ((cycles-CYC)+cycles_needed)
#define INSTRUCTION_CYCLES	instruction_cycles
#else

#define CHECK_BREAKPOINTS
#define STORE_COUNTER 
#define UPDATE_COUNTER(CYC)
 
#endif

#ifdef DEBUG_CPU



#define insdebug(CYC) \
if (do_debug) \
	printf("%05i|%03i: %06x: OP_%04x (%02i) r=%08x|irq=%02i %s: \n",M68KCONTEXT.cycles_counter,cycles+cycles_needed,(u32)PC - ctx->membase,Opcode,io_cycles_before - cycles,res, ctx->irq&7,__FUNCTION__)

#else
#define insdebug(CYC)
#endif


#pragma mark -
#pragma mark options

// Options

#define FAMEC_EMULATE_TRACE
#define FAMEC_IRQ_CYCLES
#define FAMEC_CHECK_BRANCHES

#define FAMEC_ADR_BITS  24
#define FAMEC_FETCHBITS 8
#define FAMEC_DATABITS  8

/*!
 * indicates that VFP reg s16 should be used instead of ARM reg r5
 * for cycle counter
 */
//#define FAMEARM_USE_VFP_REG_FOR_CYCLES

#define INLINE_MEMORY_HANDLERS

#include "fame_arm.h"

typedef unsigned char byte;

struct M68KCONTEXT_t M68KCONTEXT;
#define m68kcontext M68KCONTEXT

m68kcontext_t m68k_context;

#pragma mark -
#pragma mark static CPU state
// ------------------------
// local statics
register u16* PC asm("r4"); 

#ifndef FAMEARM_USE_VFP_REG_FOR_CYCLES
register s32 cycles asm("r5"); 
#endif
register void** jt asm("r6");
register u16 Opcode asm("r8");
register unsigned int flags asm("r11");
register m68kcontext_t *ctx asm("r10");

s32 cycles_needed;

#ifdef FAMEARM_USE_VFP_REG_FOR_CYCLES
register float time asm("s16");

__inline__ void _vset_time(unsigned int v) {
	asm volatile("vmov %[time], %[v]"
				 : [time] "=w" (time) : [v] "r" (v));
}

__inline__ s32 _vget_time() {
	s32 res;
	asm volatile("vmov %[res], %[time]"
				 : [res] "=r" (res) : [time] "w" (time));
	return res;
}

__inline__ void _vsub_time(unsigned int v) {
	asm volatile("vmov r1, %[time] \n\t" 
				 "subs r1, r1, %[v] \n\t"
				 "vmov %[time], r1"
				 : [time] "=w" (time) : [v] "r" (v) : "r1", "cc");
}
#endif


#pragma mark -
#pragma mark helper macros

// internals core macros
/////////////////////////

#define DREG(X)         (ctx->d[(X)].D)
#define DREGu32(X)      (ctx->d[(X)].D)
#define DREGs32(X)      (ctx->d[(X)].SD)
#define DREGu16(X)      (ctx->d[(X)].W)
#define DREGs16(X)      (ctx->d[(X)].SW)
#define DREGu8(X)       (ctx->d[(X)].B)
#define DREGs8(X)       (ctx->d[(X)].SB)

//#define AREG(X)         (ctx->a[(X)].D)
#define AREG(X)			( ((u32*)ctx)[(X) | 0x08] )
#define AREGu32(X)      AREG(X)

#define AREGs32(X)      (ctx->a[(X)].SD)
#define AREGu16(X)      (ctx->a[(X)].W)
#define AREGs16(X)      (ctx->a[(X)].SW)

#define ASP				ctx->osp
#define X_FLAG			ctx->xc

#if FAMEC_ADR_BITS < 32
#define M68K_ADR_MASK  ((1 << FAMEC_ADR_BITS)-1)
#else
#define M68K_ADR_MASK  0xFFFFFFFF
#endif
#define M68K_FETCHSFT  (FAMEC_ADR_BITS - FAMEC_FETCHBITS)
#define M68K_FETCHBANK (1 << FAMEC_FETCHBITS)
#define M68K_FETCHMASK (M68K_FETCHBANK - 1)

#define M68K_DATASFT  (FAMEC_ADR_BITS - FAMEC_DATABITS)
#define M68K_DATABANK (1 << FAMEC_DATABITS)
#define M68K_DATAMASK (M68K_DATABANK - 1)

#define M68K_SRH_S_SFT   5
#define M68K_SRH_T_SFT   7

#define M68K_SRH_S       (1 << M68K_SRH_S_SFT)
#define M68K_SRH_T       (1 << M68K_SRH_T_SFT)

#define S_FLAG(X)		((X) & M68K_SRH_S)
#define GET_S_FLAG		(ctx->srh & M68K_SRH_S)
#define SET_S_FLAG		ctx->srh |= M68K_SRH_S;
#define CLR_S_FLAG		ctx->srh &= ~M68K_SRH_S;

#define SRH				ctx->srh
#define SET_SRH(X)		ctx->srh = ((X >> 8) & 0xA7)

#define M68K_SR_S_SFT   13
#define M68K_SR_T_SFT   15

#define M68K_SR_S       (1 << M68K_SR_S_SFT)
#define M68K_SR_T       (1 << M68K_SR_T_SFT)

#define SET_SR(X)		set_sr(X);

#define M68K_CCR_MASK   0x1F

#ifdef FAMEC_EMULATE_TRACE
#define M68K_SR_MASK    (M68K_SR_T | M68K_SR_S | 0x0700 | M68K_CCR_MASK)
#else
#define M68K_SR_MASK    (M68K_SR_S | 0x0700 | M68K_CCR_MASK)
#endif

#define flag_T			(ctx->srh & (1 << 7))
#define set_flag_T		ctx->srh |= (1 << 7)
#define clr_flag_T		ctx->srh &= ~(1 << 7)

#define flag_I			(ctx->srh & 7)
#define set_flag_I(X)	ctx->srh = (ctx->srh & 0xf8) | ((X) & 7);

#if !defined(INLINE_MEMORY_HANDLERS)

#define Read_Byte(A)	ctx->read8(A)
#define Read_Word(A)	ctx->read16(A)
#define Read_Long(A)	ctx->read32(A)

#define Write_Byte(A,V) ctx->write8(A,V)
#define Write_Word(A,V)	ctx->write16(A,V)
#define Write_Long(A,V)	ctx->write32(A,V)

#else

#include "memory.h"

#define STORE_CYCLES	m68k_context.cycles = cycles;
#define LOAD_CYCLES		cycles = m68k_context.cycles;

static unsigned int Read_Byte(unsigned int a) __attribute__((always_inline));

static __inline__ unsigned int Read_Byte(unsigned int a) {
	a &= ~0xff000000;
	uae_u8 *p = baseaddr[a>>16];
	if ((int)p & 1)	{
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		uae_u32 ret = ab->bget(a);
		return ret;
	} else {
		return p[a^1];
	}
}

static __inline__ unsigned int Read_Word(unsigned int a) {
	a &= ~0xff000000;
	uae_u16 *p = (uae_u16 *) baseaddr[a>>16];
	if ((int)p & 1)	{
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		uae_u32 ret = ab->wget(a);
		return ret;
	} else {
		return p[a>>1];
	}
}

static __inline__ unsigned int Read_Long(unsigned int a) {
	return (Read_Word(a)<<16) | Read_Word(a+2);
}

static __inline__ void Write_Byte(unsigned int a, unsigned char d) {
	a &= ~0xff000000;
	uae_u8 *p = baseaddr[a>>16];
	if ((int)p & 1) {
		STORE_CYCLES
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		ab->bput(a, d&0xff);
		LOAD_CYCLES
	} else {
		p[a^1] = d;
	}
}

static __inline__ void Write_Word(unsigned int a,unsigned short d) {
	a &= ~0xff000000;
	uae_u16 *p = (uae_u16 *) baseaddr[a>>16];
	if ((int)p & 1) {
		STORE_CYCLES
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		ab->wput(a, d&0xffff);
		LOAD_CYCLES
	} else {
		p[a>>1] = d;
	}
}

static __inline__ void Write_Long(unsigned int a,unsigned int d) {
	Write_Word(a, d>>16);
	Write_Word(a+2, d);
}

#endif

#define READ_BYTE_F(A)  Read_Byte(A);

#define READ_WORD_F(A)	Read_Word(A);

#define READ_LONG_F(A)	Read_Long(A);

#define READ_LONG_DEC_F(A, D)           \
	D = Read_Word((A) + 2) & 0xFFFF;   \
	D |= Read_Word((A)) << 16;

#define READSX_LONG_F(A) Read_Long(A);
/*
#define READSX_LONG_F(A, D)             \
	D = Read_Word((A)) << 16;          \
	D |= Read_Word((A) + 2) & 0xFFFF;
*/
#define READSX_LONG_DEC_F(A, D)         \
	D |= Read_Word((A)) << 16; \
	D = Read_Word((A) + 2) & 0xFFFF; 

#define WRITE_LONG_F(A, D)              \
	Write_Long(A,D);

#define WRITE_LONG_DEC_F(A, D)          \
	Write_Word((A), (D) >> 16); \
	Write_Word((A) + 2, (D) & 0xFFFF); 


#define FETCH_BYTE ((famec_union16*)(PC++))->B

#define FETCH_WORD ((famec_union16*)(PC++))->W

#define FETCH_SWORD ((famec_union16*)(PC++))->SW

#define GET_SWORD ((famec_union16*)(PC))->SW

#define DREGs32o(X)		( ((s32*)ctx)[(X)] )
#define DECODE_EXT_WORD     \
{                           \
	u32 ext;                \
							\
	ext = FETCH_WORD;       \
	u32 idx = (ext >> 12);	\
	s32 disp;										\
													\
	adr += (s8)(ext);                               \
	if (ext & 0x0800) disp = DREGs32o(idx);			\
	else disp = (s16)DREGs32o(idx);                 \
	adr += disp;									\
}

/*
#define DECODE_EXT_WORD     \
{                           \
	u32 ext;                \
							\
	ext = FETCH_WORD;       \
													\
	adr += (s8)(ext);                               \
	if (ext & 0x0800) adr += DREGs32(ext >> 12);    \
	else adr += DREGs16(ext >> 12);                 \
}
*/

#define FETCH_LONG fetch_long()

#define PUSH_32_F(D)                            \
	AREG(7) -= 4;                                   \
	Write_Word(AREG(7), (D) >> 16); 	\
	Write_Word(AREG(7) + 2, (D) & 0xFFFF);    

#define POP_32_F(D)                         \
	D = Read_Word(AREG(7)) << 16;          \
	D |= Read_Word(AREG(7) + 2) & 0xFFFF;  \
	AREG(7) += 4;

#define READSX_BYTE_F(A, D)             \
    D = (s8)Read_Byte(A);

#define READSX_WORD_F(A) (s16)Read_Word(A);
    
#define WRITE_BYTE_F(A, D)      \
    Write_Byte(A, D);

#define WRITE_WORD_F(A, D)      \
    Write_Word(A, D);

#define PUSH_16_F(D)                    \
    Write_Word(AREG(7) -= 2, D);   \

#define POP_16_F(D)                     \
    D = (u16)Read_Word(AREG(7));   \
    AREG(7) += 2;

#ifdef FAMEARM_USE_VFP_REG_FOR_CYCLES

#define FINISH(cycle_count) \
	asm volatile("ldrh %[opcode], [%[pc]], #2 ;@ fetch opcode" \
		: [opcode] "=r" (Opcode), [pc] "+r" (PC)); \
	_vsub_time(cycle_count); \
	asm volatile("ldrge pc, [%[jt], %[opcode], asl #2] ;@ jump to next opcode handler \n" \
				 "\tb EmulateEnd" \
				 : : [jt] "r" (jt), [opcode] "r" (Opcode)); 

#else

#if USE_BRANCHES

#define FINISH(cycle_count) \
	UPDATE_COUNTER(cycle_count); \
	DISA_POST_STEP(); \
	CHECK_BREAKPOINTS; \
	DISA_STEP(); \
	Opcode = FETCH_WORD; \
	asm volatile("subs %[cycles], %[cycles], #" #cycle_count \
		: [cycles] "+r" (cycles) \
		: : "cc"); \
	asm volatile("ldrgt pc, [%[jt], %[opcode], asl #2] ;@ jump to next opcode handler \n" \
				 "\tb EmulateEnd" \
				 : : [jt] "r" (jt), [opcode] "r" (Opcode), "r" (cycles)); 

#define NEXT \
	DISA_START() \
	STORE_COUNTER; \
	DISA_STEP(); \
	Opcode = FETCH_WORD; \
	asm volatile("ldr pc, [%[jt], %[opcode], asl #2] ;@ jump to next opcode handler" \
				 : : [jt] "r" (jt), [opcode] "r" (Opcode), "r" (cycles));

#else

#define FINISH(cycle_count) \
	cycles -= cycle_count; \
	insdebug(cycle_count); \
	return;

#define NEXT do { \
	CHECK_BREAKPOINTS; \
	DISA_STEP(); \
	Opcode = FETCH_WORD; \
	typedef void (*opcode_func)(void); \
	STORE_COUNTER; \
	opcode_func fn = (opcode_func)jt[Opcode]; \
	fn(); \
	DISA_POST_STEP(); \
	} while (cycles > 0)

#endif

#endif

#define PRE_IO

#define POST_IO

#define EXECINFO	M68KCONTEXT.execinfo

#define CHECK_INT_TO_JUMP(CLK) \
	if (interrupt_chk__()) { \
		cycles_needed=cycles-(CLK); \
		cycles= (CLK);  \
	}

#ifdef FAMEC_CHECK_BRANCHES

#if USE_BRANCHES

#define CHECK_BRANCH_EXCEPTION(_PC_) \
	if ((_PC_)&1) \
	{ \
		u32 pr_PC=GET_PC; \
		EXECINFO |= M68K_EMULATE_GROUP_0; \
		execute_exception_group_0(M68K_ADDRESS_ERROR_EX, 0, pr_PC, 0x12 ); \
		PC++; \
		asm volatile("b EmulateEnd"); \
	}

#else

#define CHECK_BRANCH_EXCEPTION(_PC_) \
	if ((_PC_)&1) \
	{ \
		u32 pr_PC=GET_PC; \
		EXECINFO |= M68K_EMULATE_GROUP_0; \
		execute_exception_group_0(M68K_ADDRESS_ERROR_EX, 0, pr_PC, 0x12 ); \
		return; \
	}

#endif


#else
#define CHECK_BRANCH_EXCEPTION(_PC_)
#endif

// swaps the CV bits to toggle between M68k CCR or ARM CPSR 
__inline__ u32 flags_swap_CV(register u32 ccr) {
	u32 tmp = ccr ^ (ccr >> 1);
	if (tmp & 1) ccr ^= 0x03;
	return ccr;
}

__inline__ void set_ccr(u32 val) {
	val = flags_swap_CV(val);
	flags = val << 28;
	X_FLAG = val << 25;
}

// sets the flags, xc and srh ARM core state from an M68k CCR word
__inline__ void set_sr(u32 val) {
	SET_SRH(val);
	set_ccr(val);
}

// returns the flags, xc and srh ARM core state as an M68k CCR word
__inline__ u32 get_sr() {
	u32 res = flags_swap_CV(flags >> 28);
	
	if (ctx->xc & 0x20000000)
		res |= 0x10;
	
	res |= ctx->srh << 8;
	
	return res;
}

#define GET_SR			get_sr()

#define GET_CCR			get_sr()

#define SET_CCR(V)		set_ccr(V);

#define BasePC			ctx->membase

#define SET_PC(A)		PC = (u16*)ctx->checkpc((s32)A);
#define SET_PC_BASE(A)	PC = (u16*)ctx->checkpc((A) + BasePC);
#define SET_PC_IMM(A)	PC = (u16*)(A)

#define GET_PC			((u32)PC - (u32)ctx->membase)

// exception defines taken from musashi core
#define M68K_RESET_EX                   1
#define M68K_BUS_ERROR_EX               2
#define M68K_ADDRESS_ERROR_EX           3
#define M68K_ILLEGAL_INSTRUCTION_EX     4
#define M68K_ZERO_DIVIDE_EX             5
#define M68K_CHK_EX                     6
#define M68K_TRAPV_EX                   7
#define M68K_PRIVILEGE_VIOLATION_EX     8
#define M68K_TRACE_EX                   9
#define M68K_1010_EX                    10
#define M68K_1111_EX                    11
#define M68K_FORMAT_ERROR_EX            14
#define M68K_UNINITIALIZED_INTERRUPT_EX 15
#define M68K_SPURIOUS_INTERRUPT_EX      24
#define M68K_INTERRUPT_AUTOVECTOR_EX    24
#define M68K_TRAP_BASE_EX               32

#define M68K_INT_ACK_AUTOVECTOR         -1

#if !defined(M68K_RUNNING)
#define M68K_RUNNING    0x01
#endif
#define M68K_HALTED     0x80
#define M68K_WAITING    0x04
#define M68K_DISABLE    0x20
#define M68K_FAULTED    0x40
#define M68K_EMULATE_GROUP_0  0x02
#define M68K_EMULATE_TRACE    0x08
#define M68K_DO_TRACE    0x10

#pragma mark -
#pragma mark Flags and condition codes

#define flag_c	(flags & 0x20000000)
#define flag_v	(flags & 0x10000000)
#define flag_z	(flags & 0x40000000)
#define flag_n	(flags & 0x80000000)
#define flag_x	(ctx->xc & 0x20000000)

#define n_xor_v			((flag_n >> 3) ^ (flag_v))

// condition codes
#define cond_true		(!flag_z)
#define cond_false		( flag_z)
#define cond_hi			(!flag_c && !flag_z)
#define cond_ls			(flag_c || flag_z)
#define cond_cc			(!flag_c)
#define cond_cs			(flag_c)
#define cond_ne			(!flag_z)
#define cond_eq			( flag_z)
#define cond_vc			(!flag_v)
#define cond_vs			(flag_v)
#define cond_pl			(!flag_n)
#define cond_mi			(flag_n)
#define cond_ge			!(n_xor_v)
#define cond_lt			n_xor_v
#define cond_gt			(!flag_z && !n_xor_v)
#define cond_le			(flag_z || n_xor_v)

#pragma mark -
#pragma mark Helper Functions

#if 0
__inline__ u32 fetch_long() {
	u32 result;
	asm("ldrh r2, [%[pc]], #2 \n"
		"\tldrh r3, [%[pc]], #2 \n"
		"\torr %[result], r3, r2, lsl #16"
		: [result] "=r" (result), [pc] "+r" (PC) : : "r2", "r3");
	return result;
}
#else
__inline__ u32 fetch_long() {
	u32 result;
	asm("ldr %[result], [%[pc]], #4 \n\t"
		"ror %[result], #16"
		: [result] "=r" (result), [pc] "+r" (PC));
	return result;
}
#endif

#pragma mark -
#pragma mark handlers

// exception cycle table (taken from musashi core)
static const s32 exception_cycle_table[256] =
{
	  4, //  0: Reset - Initial Stack Pointer
	  4, //  1: Reset - Initial Program Counter
	 50, //  2: Bus Error
	 50, //  3: Address Error
	 34, //  4: Illegal Instruction
	 38, //  5: Divide by Zero
	 40, //  6: CHK
	 34, //  7: TRAPV
	 34, //  8: Privilege Violation
	 34, //  9: Trace
	  4, // 10:
	  4, // 11:
	  4, // 12: RESERVED
	  4, // 13: Coprocessor Protocol Violation
	  4, // 14: Format Error
	 44, // 15: Uninitialized Interrupt
	  4, // 16: RESERVED
	  4, // 17: RESERVED
	  4, // 18: RESERVED
	  4, // 19: RESERVED
	  4, // 20: RESERVED
	  4, // 21: RESERVED
	  4, // 22: RESERVED
	  4, // 23: RESERVED
	 44, // 24: Spurious Interrupt
	 44, // 25: Level 1 Interrupt Autovector
	 44, // 26: Level 2 Interrupt Autovector
	 44, // 27: Level 3 Interrupt Autovector
	 44, // 28: Level 4 Interrupt Autovector
	 44, // 29: Level 5 Interrupt Autovector
	 44, // 30: Level 6 Interrupt Autovector
	 44, // 31: Level 7 Interrupt Autovector
	 34, // 32: TRAP #0
	 34, // 33: TRAP #1
	 34, // 34: TRAP #2
	 34, // 35: TRAP #3
	 34, // 36: TRAP #4
	 34, // 37: TRAP #5
	 34, // 38: TRAP #6
	 34, // 39: TRAP #7
	 34, // 40: TRAP #8
	 34, // 41: TRAP #9
	 34, // 42: TRAP #10
	 34, // 43: TRAP #11
	 34, // 44: TRAP #12
	 34, // 45: TRAP #13
	 34, // 46: TRAP #14
	 34, // 47: TRAP #15
	  4, // 48: FP Branch or Set on Unknown Condition
	  4, // 49: FP Inexact Result
	  4, // 50: FP Divide by Zero
	  4, // 51: FP Underflow
	  4, // 52: FP Operand Error
	  4, // 53: FP Overflow
	  4, // 54: FP Signaling NAN
	  4, // 55: FP Unimplemented Data Type
	  4, // 56: MMU Configuration Error
	  4, // 57: MMU Illegal Operation Error
	  4, // 58: MMU Access Level Violation Error
	  4, // 59: RESERVED
	  4, // 60: RESERVED
	  4, // 61: RESERVED
	  4, // 62: RESERVED
	  4, // 63: RESERVED
	     // 64-255: User Defined
	  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};


// helpers
//////////////////////////

__inline__ void cpu_state_to_registers(register m68kcontext_t *cpu) {
	// set up registers
	ctx = cpu;
	PC = (u16*)ctx->pc;
	flags = ctx->flags;
	flags <<= 28;
#ifdef FAMEARM_USE_VFP_REG_FOR_CYCLES
	_vset_time(ctx->cycles);
#else
	cycles = ctx->cycles;
#endif
	cycles_needed = 0;
}

__inline__ void cpu_state_from_registers() {
	ctx->pc = (unsigned int)PC;
#ifdef FAMEARM_USE_VFP_REG_FOR_CYCLES
	ctx->cycles = _vget_time();
#else
	ctx->cycles = cycles;
#endif
	flags >>= 28;
	ctx->flags = flags;
}

// Check interrupts and starts
static s32 interrupt_chk__(void) {
	if ((M68KCONTEXT.interrupts[0]>>1))
	{
		if (M68KCONTEXT.interrupts[0]&0x80)
			return 7;
		else if (M68KCONTEXT.interrupts[0]&0x40) {
			if (6 > flag_I)
				return 6;
		}
		else
		if (M68KCONTEXT.interrupts[0]&0x20)
		{
			if (5 > flag_I)
				return 5;
		}
		else
		if (M68KCONTEXT.interrupts[0]&0x10)
		{
			if (4 > flag_I)
				return 4;
		}
		else
		if (M68KCONTEXT.interrupts[0]&0x08)
		{
			if (3 > flag_I)
				return 3;
		}
		else
		if (M68KCONTEXT.interrupts[0]&0x04)
		{
			if (2 > flag_I)
				return 2;
		}
		else
		if (M68KCONTEXT.interrupts[0]&0x02)
		{
			if (1 > flag_I)
				return 1;
		}
	}

#ifdef FAMEC_EMULATE_TRACE
	if (flag_T)
	{
/*
		EXECINFO |= M68K_EMULATE_TRACE;
		cycles_needed= io_cycle_counter;
		io_cycle_counter=0;	
*/
		return -1;
	}
#endif
	return 0;
}

#pragma mark -
#pragma mark DISASSEMBLER / BREAKPOINTS

/***********************/
/* disassembler code   */
/***********************/

#if DISASSEMBLER
# include "Disa.h"
# include "disassembler.h"
# include "DisaLogging.h"

FILE *g_logOutput = stdout;

//#define flag_x	(ctx->xc & 0x20000000)
//#define flag_n	(flags & (0x1 << 31))
//#define flag_z	(flags & (0x1 << 30))
//#define flag_v	(flags & (0x1 << 28))
//#define flag_c	(flags & (0x1 << 29))

#define flag_Xx			(flag_x ? 'X' : 'x')
#define flag_Nn			(flag_n ? 'N' : 'n')
#define flag_Zz			(flag_z ? 'Z' : 'z')
#define flag_Vv			(flag_v ? 'V' : 'v')
#define flag_Cc			(flag_c ? 'C' : 'c')

#define _68k_areg(X) AREG(X)
#define _68k_dreg(X) DREGu32(X)

int g_disastep=0;

void check_breakpoints() {
	u32 cPC = GET_PC;
	
	static int count = 0;
	
	switch (cPC) {
		case 0x53d0:
			count++;
			if (count == 1) {
				do_disa = 1;
			}
			break;
	}
}

unsigned short DisaGetWord(unsigned int a) {
	return Read_Word(a);
}

#define MODE_BINARY				1
#define MODE_TEXT_TABS			2
#define MODE_TEXT_SPACES		3

#define DISASSEMBLER_OUTPUT		MODE_BINARY

#define DISASSEMBLER_LIMIT		1000000

#define INSTRUCTION_LOGLEVEL	2

u16 *DPC;

void DisaStep() {
	g_disastep=1;

	DisaPc = GET_PC;
#if DISASSEMBLER_OUTPUT != MODE_BINARY
	DisaGet();
	DisaPc = GET_PC;
#else
	DPC = PC;
#endif
}

void DisaPostStep() {
	if (!g_disastep) return;
	
	g_disastep=0;
	
#if DISASSEMBLER_LIMIT
	disa_step++;
#endif

	
#if DISASSEMBLER_OUTPUT == MODE_BINARY

#if INSTRUCTION_LOGLEVEL == 0
	const uint8_t rType = EntryTypeInstructionL0;
#elif INSTRUCTION_LOGLEVEL == 1
	const uint8_t rType = EntryTypeInstructionL1;
#else
	const uint8_t rType = EntryTypeInstructionL2;
#endif
	fwrite(&rType, sizeof(rType), 1, g_logOutput);
	
	fwrite(&DisaPc, 4, 1, g_logOutput);
	fwrite(DPC, 4, 3, g_logOutput);
	uint8_t ccr = GET_CCR;
	fwrite(&ccr, 1, 1, g_logOutput);
	
#if INSTRUCTION_LOGLEVEL > 0
	u8 inscycles = INSTRUCTION_CYCLES; 
	fwrite(&inscycles, 1, 1, g_logOutput);
#endif
	
#if INSTRUCTION_LOGLEVEL > 1
	fwrite(&DREG(0), 4, 16, g_logOutput);
#endif
	
#elif DISASSEMBLER_OUTPUT == MODE_TEXT_TABS
	fprintf(g_logOutput, "%06x:\t%s\t%c%c%c%c%c", DisaPc, DisaText, 
		   flag_Xx, flag_Nn, flag_Zz, flag_Vv, flag_Cc);
	
	fprintf(g_logOutput, "\tA0=%.8X\tA1=%.8X\tA2=%.8X\tA3=%.8X",_68k_areg(0),_68k_areg(1),_68k_areg(2),_68k_areg(3));
	fprintf(g_logOutput, "\tA4=%.8X\tA5=%.8X\tA6=%.8X\tA7=%.8X",_68k_areg(4),_68k_areg(5),_68k_areg(6),_68k_areg(7));
	fprintf(g_logOutput, "\tD0=%.8X\tD1=%.8X\tD2=%.8X\tD3=%.8X",_68k_dreg(0),_68k_dreg(1),_68k_dreg(2),_68k_dreg(3));
	fprintf(g_logOutput, "\tD4=%.8X\tD5=%.8X\tD6=%.8X\tD7=%.8X",_68k_dreg(4),_68k_dreg(5),_68k_dreg(6),_68k_dreg(7));
	
	fprintf(g_logOutput, "\n");
	
#else
	fprintf(g_logOutput, "%06x %06x: %-35s  %c%c%c%c%c\n", disa_step, DisaPc, DisaText, 
		   flag_Xx, flag_Nn, flag_Zz, flag_Vv, flag_Cc);
#endif
	
#if DISASSEMBLER_LIMIT
	// limit
	if (disa_step > DISASSEMBLER_LIMIT) {
		do_disa = 0;
		DisaCloseFile();
	}
#endif
}

static void DisaLogException(s32 vect, u32 oldPC, u32 newPC) {
	uint8_t rType = EntryTypeException;
	fwrite(&rType, sizeof(rType), 1, g_logOutput);
	
	tagExceptionRecord rec = {
		vect, oldPC, newPC
	};
	fwrite(&rec, sizeof(rec), 1, g_logOutput);
}

void DisaInitialize() {
	static char buffer[512];
	DisaWord = &DisaGetWord;
	DisaText = buffer;
	DisaText[0] = '\0';
	
	DisaCreateFile(1);
}

void DisaLogEmulateStart(s32 cycles, u32 total_cycles) {
	uint8_t rType = EntryTypeEmulateStart;
	fwrite(&rType, sizeof(rType), 1, g_logOutput);
	
	tagEmulateStart rec = {
		cycles, total_cycles
	};
	fwrite(&rec, sizeof(rec), 1, g_logOutput);
}

#define DISA_STEP()			if (do_disa) DisaStep();
#define DISA_POST_STEP()	if (do_disa) DisaPostStep();
#define DISA_LOGEXCEPTION()	if (do_disa) DisaLogException(vect, oldPC, newPC);
#define DISA_EMULATE_START(cycles, total_cycles) if (do_disa) DisaLogEmulateStart(cycles, total_cycles);

#define DISA_START()		if (do_disa) g_disastep=0;

#else

#define DISA_STEP()
#define DISA_POST_STEP()
#define DISA_LOGEXCEPTION()
#define DISA_EMULATE_START(cycles, total_cycles)

#define DISA_START()

#endif

void m68k_init() {
#if DISASSEMBLER
	DisaInitialize();
#endif
}

unsigned m68k_reset() {
	u32 save_r11;
	u32 save_r10;
	
	asm volatile("mov %[save_r11], r11\n\t"
				 "mov %[save_r10], r10"
				 : [save_r10] "=r" (save_r10), [save_r11] "=r" (save_r11));
	
	ctx = &m68k_context;
	
	if (M68KCONTEXT.execinfo & M68K_RUNNING)
		return M68K_RUNNING;
	
	// Resetear registros
	bzero(&m68k_context.d[0], 16*4);
	
	// Resetear interrupts, execinfo y ASP
	M68KCONTEXT.interrupts[0] = 0;
	for(int i=1;i<8;i++)
		M68KCONTEXT.interrupts[i]=i+0x18;
	M68KCONTEXT.execinfo = 0;
	ASP = 0;
	
	// Fijar registro de estado
	SET_SR(0x2700);
	
	ctx->flags = flags >> 28;
	
	// Obtener puntero de pila inicial y PC
	AREG(7) = Read_Long(0);
	m68k_context.membase = 0;
	m68k_context.pc = m68k_context.checkpc(Read_Long(4));
	m68k_context.cycles = 0;
	
#if DISASSEMBLER
	DisaCloseFile();
	DisaCreateFile(1);
#endif
	
	asm volatile("mov r11, %[save_r11]\n\t"
				 "mov r10, %[save_r10]"
				 :: [save_r10] "r" (save_r10), [save_r11] "r" (save_r11));

	return 0;
}

void m68k_release_timeslice(void) {
	m68k_context.cycles = -1;
}

/******************************************************************************/
/* m68k_raise_irq(level,vector)			                                      */
/* Parametros: level = nivel de interrupcion                                  */
/*             vector = puntero a la direccion de la rutina de atencion       */
/*                      -1 auto, -2 interrupcion espuria                      */
/* Retorno: Exito de la operacion                                             */
/*         0  La interrupcion se ha habilitado satisfactoriamente             */
/*        -1  No se ha podido habilitar porque ya existe otra interrupcion    */
/*            en ese nivel.                                                   */
/*        -2  No se ha podido habilitar porque el vector no es valido o       */
/*	                 el nivel es igual a 0.                                   */
/******************************************************************************/
s32 m68k_raise_irq(s32 level, s32 vector)
{
	/* Enmascarar nivel de interrupcion */
	level &=7;
	
	/* Nivel de interrupcion = 0 no es valido */
	if (!level) return M68K_IRQ_INV_PARAMS;
	
	/* Comprobar si existe una interrupcion activada en ese nivel */
	if (m68kcontext.interrupts[0] & (1 << level))
		return M68K_IRQ_LEVEL_ERROR;
	
	/* El vector de interrupcion no puede ser > 255 ni menor que -2 */
	if ((vector > 255) || (vector < M68K_SPURIOUS_IRQ))
	{
		return M68K_IRQ_INV_PARAMS;
	}
	
	/* Dar de alta la interrupcion en interrupts */
	m68kcontext.interrupts[0] |= (1 << level);
	
	switch(vector)
	{
		case M68K_SPURIOUS_IRQ:
			m68kcontext.interrupts[level] = 0x18;
			break;
		case M68K_AUTOVECTORED_IRQ:
			m68kcontext.interrupts[level] = level + 0x18;
			break;
		default:
			m68kcontext.interrupts[level] = vector;
			break;
	}
#ifdef FAMEC_DEBUG
	printf("RAISE interrupts[%i]=0x%X\n",level,m68kcontext.interrupts[level]);
#endif
	
	/* Testear si la CPU esta detenida (mediante STOP) */
	if (m68kcontext.execinfo & M68K_HALTED)
	{
		/* Si la IRQ es NMI o si supera la mascara de interrupcion, */
		/* salir de estado parado                                   */
		if ((level == 7) || (level > ((m68k_context.srh) & 0x7)))
		{
			m68kcontext.execinfo &= ~M68K_HALTED;
		}
	}
    
    return M68K_OK;
}

/* Custom function handler */
typedef int (*icust_handler_func)(m68kcontext_t *cpu, u32 vector);

static void execute_exception(s32 vect) {
	
#ifndef FAMEC_IRQ_CYCLES
	//if ((vect<24)||(vect>31))
#endif
        cycles -= exception_cycle_table[vect];
	/* comprobar si hay tabla funciones manejadoras */
	if (M68KCONTEXT.exception_handlers && M68KCONTEXT.exception_handlers[vect]) {
		icust_handler_func handler=(icust_handler_func)M68KCONTEXT.exception_handlers[vect];
		cpu_state_from_registers();
		if (handler(ctx, vect))
			cpu_state_to_registers(ctx);
		
	} else {
		u32 newPC;
		u32 oldPC;
		u32 oldSR = get_sr();
		
		PRE_IO
		
		newPC = READ_LONG_F(vect * 4);
		
		/* swap A7 and USP */
		if (!GET_S_FLAG) {
			u32 tmpSP;
			
			tmpSP = ASP;
			ASP = AREG(7);
			AREG(7) = tmpSP;
		}
		
		oldPC = (u32)(PC) - BasePC;
		PUSH_32_F(oldPC)
		PUSH_16_F(oldSR)
		
		/* enable adjust SR */
		SET_S_FLAG;
		
		newPC &= M68K_ADR_MASK;
		
		SET_PC_BASE(newPC)
		
		DISA_LOGEXCEPTION();
		
		POST_IO
	}
	
}

static void execute_exception_group_0(s32 vect, u16 inst_reg, s32 addr, u16 spec_info)
{
	execute_exception(vect);
	if (!(M68KCONTEXT.exception_handlers && M68KCONTEXT.exception_handlers[vect])) {
		PUSH_16_F(inst_reg);
		PUSH_32_F(addr);
		PUSH_16_F(spec_info);
	}
}

#if USE_BRANCHES
// *************************************************
// PROLOG and EPILOG for opcodes and emulate methods

#ifdef DEBUG
// the prolog is only necessary for debug builds, and should be the first line
// of any functions declared naked.  Essentially, it dresses them again :)

// These two lines keep gdb happy.
// I can only put it down to that gdb inspects the stack when entering a new function
// after the first push, to grab the frame.
// The code is simply pushing r7 and lr, and then moving the 
// sp right back again, which for every opcode is the SAME values!
#define PROLOG	\
	__asm__ volatile("stmfd sp!, {r7, lr} \n\t" \
					 "add r7, sp, #0\n\t" \
					 "sub sp, sp, #100"::: "sp");

#define EPILOGUE \
	__asm__ volatile("add sp, sp, #100\n\t" \
					 "ldmfd sp!, {r7, lr}"::: "sp");

#define EMULATE_PROLOG \
	__asm__ volatile("stmfd sp!,{r4-r7,lr} \n\t" \
					 "add r7, sp, #12"::: "sp", "r7");	\
	__asm__ volatile("stmfd sp!,{r8-r11}"::: "sp");	\
	__asm__ volatile("sub sp, sp, #0x100":::"sp");

#define EMULATEEND_EPILOGUE \
	__asm__ volatile("add sp, sp, #0x100" ::: "sp"); \
	__asm__ volatile("ldmfd sp!,{r8-r11}"); \
	__asm__ volatile("ldmfd sp!,{r4-r7,pc}"); \

#else

#define PROLOG

#define EPILOGUE 

#define EMULATE_PROLOG \
	asm volatile("stmdb sp!,{r4-r11,lr}"); \
	asm volatile("sub sp, sp, #0x100"::: "sp");

#define EMULATEEND_EPILOGUE \
	asm volatile("add sp, sp, #0x100" ::: "sp"); \
	asm volatile("ldmia sp!,{r4-r11,pc}");

#endif

#else

#if DEBUG

#define PROLOG
#define EPILOGUE

#define EMULATE_PROLOG \
	__asm__ volatile("stmfd sp!,{r4-r7,lr} \n\t" \
					 "add r7, sp, #12"::: "sp", "r7");	\
	__asm__ volatile("stmfd sp!,{r8-r11}"::: "sp");	\
	__asm__ volatile("sub sp, sp, #0x100":::"sp");

#define EMULATEEND_EPILOGUE \
	__asm__ volatile("add sp, sp, #0x100" ::: "sp"); \
	__asm__ volatile("ldmfd sp!,{r8-r11}"); \
	__asm__ volatile("ldmfd sp!,{r4-r7,pc}"); \

/*
#define PROLOG
#define EPILOGUE 
#define EMULATE_PROLOG \
	__asm__ volatile("stmfd sp!,{r4-r7,lr} \n\t" \
					 "add r7, sp, #12"::: "sp", "r7");	\
	__asm__ volatile("stmfd sp!,{r8-r11}"::: "sp");	\
	__asm__ volatile("sub sp, sp, #0x200":::"sp");

#define EMULATEEND_EPILOGUE \
	__asm__ volatile("add sp, sp, #0x200" ::: "sp"); \
	__asm__ volatile("ldmfd sp!,{r8-r11}"); \
	__asm__ volatile("ldmfd sp!,{r4-r7,pc}"); \
*/
#else

#define PROLOG
#define EPILOGUE 
#define EMULATE_PROLOG \
	asm volatile("stmdb sp!,{r4-r11,lr}"); \
	asm volatile("sub sp, sp, #0x200"::: "sp");

#define EMULATEEND_EPILOGUE \
	asm volatile("add sp, sp, #0x200" ::: "sp"); \
	asm volatile("ldmia sp!,{r4-r11,pc}");

#endif

#endif

#if USE_BRANCHES

#define OPCODE(A)	\
static void OP_##A() __asm__("OP" #A) __attribute__((naked));	\
\
void OP_##A() { \
	STORE_COUNTER; 


#define NAKED(FN)	\
void FN() __asm__(#FN) __attribute__((naked));	\
\
void FN()

#else

#define OPCODE(A)	\
static void OP_##A() __asm__("OP" #A);	\
\
void OP_##A() {

#define NAKED(FN)	\
void FN() __asm__(#FN);	\
\
void FN()

#endif


#include "c68k_misc.h"
#include "c68k_op0.h"
#include "c68k_op1.h"
#include "c68k_op2.h"
#include "c68k_op3.h"
#include "c68k_op4.h"
#include "c68k_op5.h"
#include "c68k_op6.h"
#include "c68k_op7.h"
#include "c68k_op8.h"
#include "c68k_op9.h"
#include "c68k_opA.h"
#include "c68k_opB.h"
#include "c68k_opC.h"
#include "c68k_opD.h"
#include "c68k_opE.h"
#include "c68k_opF.h"

#include "c68k_ini.h"

void emulate() __attribute__((naked));

#if USE_BRANCHES

void emulate_end() asm("EmulateEnd") __attribute__((naked));

#define RETURN_EMULATE \
	{ \
		EMULATEEND_EPILOGUE \
		return; \
	}

#else

#define RETURN_EMULATE \
	{ \
		EMULATEEND_EPILOGUE \
		return; \
	}

#endif

void emulate() {
	EMULATE_PROLOG
	
	DISA_EMULATE_START(m68k_context.cycles_to_execute, M68KCONTEXT.cycles_counter);
		
	/* Comprobar si la CPU esta detenida debido a un doble error de bus */
	if (EXECINFO & M68K_FAULTED) RETURN_EMULATE;
	
	if (EXECINFO & M68K_HALTED)
	{
		ctx = &m68k_context;
		if (interrupt_chk__() <= 0) {
			/* La CPU esta detenida mediante la instruccion STOP */
			/* Agregar ciclos de reloj requeridos */
			M68KCONTEXT.cycles_counter += m68k_context.cycles_to_execute;
			RETURN_EMULATE;
		}
		EXECINFO &= ~M68K_HALTED;
	}

	jt = (void**)JumpTable;
	
	// set up registers
	m68k_context.cycles = m68k_context.cycles_to_execute;
	m68k_context.irq = m68k_context.srh;
	cpu_state_to_registers(&m68k_context);
	
	EXECINFO |= M68K_RUNNING;
	
#ifdef FAMEC_EMULATE_TRACE
	if (!(EXECINFO & M68K_EMULATE_TRACE))
#endif
	{
		s32 line=interrupt_chk__();
		if (line>0) {
			/* Desactivar interrupcion */
			m68kcontext.interrupts[0] &= ~(1 << ((u32)line));
			
			/* comprobar si hay rutina de acknowledge */
			if (ctx->IrqCallback != NULL)
				ctx->IrqCallback(line);
			
			execute_exception(m68kcontext.interrupts[(u32)line]);
			set_flag_I((u32)line);
		}
#ifdef FAMEC_EMULATE_TRACE
		else {
			if  (flag_T) {
				EXECINFO |= M68K_EMULATE_TRACE;
				cycles_needed=cycles;
				cycles=0;	
			}
		}
#endif
	}
	
	NEXT;

#if USE_BRANCHES
}

void emulate_end() {
	PROLOG
	
	PC--;
#endif
	
#ifdef FAMEC_EMULATE_TRACE
	if (EXECINFO & M68K_EMULATE_TRACE)
	{
		cycles = cycles_needed;
		EXECINFO &= ~M68K_EMULATE_TRACE;
		EXECINFO |= M68K_DO_TRACE;
		execute_exception(M68K_TRACE_EX);
		clr_flag_T;
		if (cycles > 0) {
			EPILOGUE
			NEXT;
		}
	}
	else
#endif
	if (cycles_needed>0)
	{
		s32 line=interrupt_chk__();
		cycles = cycles_needed;
		if (line>0) {
       		 	/* Desactivar interrupcion */
			m68kcontext.interrupts[0] &= ~(1 << ((u32)line));

			/* comprobar si hay rutina de acknowledge */
			if (ctx->IrqCallback != NULL)
				ctx->IrqCallback(line);

			execute_exception(m68kcontext.interrupts[(u32)line]);
			set_flag_I((u32)line);
		}
#ifdef FAMEC_EMULATE_TRACE
		else if (!(flag_T))
#endif
		if (cycles > 0) {
			EPILOGUE
			NEXT;
		}
	}
	
	cpu_state_from_registers();
	
	EXECINFO &= ~M68K_RUNNING;
	
	M68KCONTEXT.cycles_counter += (ctx->cycles_to_execute - m68k_context.cycles);
	
	EPILOGUE
	EMULATEEND_EPILOGUE
}

#endif