/*
 *  m68k_interface.cpp
 *  M68kTests
 *
 *  Created by Stuart Carnie on 7/3/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#import "sysconfig.h"

#ifdef USE_FAME_CORE_ARM2

#import <stdlib.h>
#import <memory>
#import "sysdeps.h"
#include "memory.h"
#include "m68k_intrf.h"
#import "fame_arm.h"


extern m68kcontext_t m68k_context;

#ifdef USE_CYCLONE_MEMHANDLERS
#define MH_STATIC extern "C"
#else
#define MH_STATIC static
#endif

#define SPLIT_32_2_16

MH_STATIC unsigned int cyclone_read8 (unsigned int a);
MH_STATIC unsigned int cyclone_read16(unsigned int a);
MH_STATIC unsigned int cyclone_read32(unsigned int a);
MH_STATIC void cyclone_write8 (unsigned int a,unsigned int d);
MH_STATIC void cyclone_write16(unsigned int a,unsigned int d);
MH_STATIC void cyclone_write32(unsigned int a,unsigned int d);

static unsigned int check_pc(unsigned int pc);
static int irq_ack(int level);
static int unrecognized_callback(void);

static unsigned custom_handlers[256];

int end_emulator(register m68kcontext_t *cpu, u32 vector) {
	cpu->cycles = -cpu->cycles;
	return 1;	// modified CPU state
}

static int m68k_exception(m68kcontext_t *cpu, unsigned n)
{
	u32 pc = cpu->pc - cpu->membase;
	u32 sr = cpu->srh << 8;
	u32 sp = cpu->a[7].D;
	if (!(sr&0x2000))
	{
		unsigned asp=cpu->osp;
		//m68k_set_register(M68K_REG_SR,(sr&0x7FF)|0x2000);
		//m68k_set_register(M68K_REG_ASP,sp);
		//m68k_set_register(M68K_REG_A7,asp-6);
		sp=asp;
	}
	else
		//m68k_set_register(M68K_REG_A7,sp-6);
		cpu->a[7].D = sp-6;
	
	put_long(sp-4, pc);
	put_word(sp-6, sr);
	
	u32 newPC = (cpu->fetch16((n*4)+2)) + (cpu->fetch16(n*4) << 16);
	newPC += cpu->membase;
	cpu->pc = cpu->checkpc(newPC);
	
	
	if (n==4) IO_CYCLE+=4;
	M68KCONTEXT.execinfo&=0x65;
	/*
	unsigned pc=m68k_get_pc();
	unsigned sr=m68k_get_register(M68K_REG_SR);
	unsigned sp=m68k_get_register(M68K_REG_A7);
	
	if (!(sr&0x2000))
	{
		unsigned asp=m68k_get_register(M68K_REG_ASP);
		m68k_set_register(M68K_REG_SR,(sr&0x7FF)|0x2000);
		m68k_set_register(M68K_REG_ASP,sp);
		m68k_set_register(M68K_REG_A7,asp-6);
		sp=asp;
	}
	else
		m68k_set_register(M68K_REG_A7,sp-6);
	
	put_long(sp-4,pc);
	put_word(sp-6,sr);
	
	m68k_set_register(M68K_REG_PC,m68k_fetch((n*4)+2,0)+(m68k_fetch(n*4,0)<<16));
	
	//m68k_release_timeslice();
	if (n==4) IO_CYCLE+=4; // adjust for cyclone
	M68KCONTEXT.execinfo&=0x65;
	 */
	return 1;
}

int uae_chk_handler(register m68kcontext_t *cpu, unsigned vector) {
	// handling invalid opcode
	u32 pc = cpu->pc - cpu->membase;
	unsigned opcode=cpu->fetch16(pc);
	
	return m68k_exception(cpu, 0x04);
}

void init_m68k() {
	bzero(&custom_handlers, sizeof(unsigned)*256);
	bzero(&M68KCONTEXT, sizeof M68KCONTEXT);
	M68KCONTEXT.exception_handlers = custom_handlers;
	custom_handlers[0x04] = (unsigned)&uae_chk_handler;
	custom_handlers[32 + 15] = (unsigned)&end_emulator;
	
	//m68k_init();
	bzero(&m68k_context, sizeof m68k_context);
	m68k_context.checkpc = check_pc;
	m68k_context.read8   = m68k_context.fetch8  = cyclone_read8;
	m68k_context.read16  = m68k_context.fetch16 = cyclone_read16;
	m68k_context.read32  = m68k_context.fetch32 = cyclone_read32;
	m68k_context.write8  = cyclone_write8;
	m68k_context.write16 = cyclone_write16;
	m68k_context.write32 = cyclone_write32;
	
}

void map_zone(unsigned addr, addrbank* banco, unsigned realstart) {
}

void init_memmaps(addrbank* bank) {
}

static unsigned int check_pc(unsigned int pc) {
	static int loopcode = 0x60fe60fe;
	pc -= m68k_context.membase;
	// pc &= ~1; // leave it for address error emulation
	
	// do we really need to do this? I've seen some cores never clearing the upper bits
	// and pushing them, etc. But in that case kickstart 1.3 hangs because cmp @ fc090e fails.
	pc &= ~0xff000000;
	
	uae_u8 *p = baseaddr[pc >> 16];
	
	if ((int)p & 1) {
		printf("FAME ARM problem: branched to unknown memory location: %06x\n", pc);
		p = (uae_u8 *)&loopcode - pc;
	}
	
	m68k_context.membase = (unsigned)p;
	return (unsigned)p + pc;
}

static unsigned int cyclone_read8(unsigned int a) {
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

static unsigned int cyclone_read16(unsigned int a) {
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

static unsigned int cyclone_read32(unsigned int a) {
#ifdef SPLIT_32_2_16
	return (cyclone_read16(a)<<16) | cyclone_read16(a+2);
#else
	a &= ~0xff000000;
	uae_u16 *p = (uae_u16 *) baseaddr[a>>16];
	if ((int)p & 1)	{
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		uae_u32 ret = ab->lget(a);
		return ret;
	} else {
		a >>= 1;
		return (p[a]<<16)|p[a+1];
	}
#endif
}

static void cyclone_write8(unsigned int a, unsigned int d) {
	a &= ~0xff000000;
	uae_u8 *p = baseaddr[a>>16];
	if ((int)p & 1) {
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		ab->bput(a, d&0xff);
	} else {
		p[a^1] = d;
	}
}

static void cyclone_write16(unsigned int a,unsigned int d) {
	a &= ~0xff000000;
	uae_u16 *p = (uae_u16 *) baseaddr[a>>16];
	if ((int)p & 1) {
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		ab->wput(a, d&0xffff);
	} else {
		p[a>>1] = d;
	}
}

static void cyclone_write32(unsigned int a,unsigned int d) {
#ifdef SPLIT_32_2_16
	cyclone_write16(a, d>>16);
	cyclone_write16(a+2, d);
#else
	a &= ~0xff000000;
	uae_u16 *p = (uae_u16 *) baseaddr[a>>16];
	if ((int)p & 1) {
		addrbank *ab = (addrbank *) ((unsigned)p & ~1);
		ab->lput(a, d);
	} else {
		a >>= 1;
		p[a] = d >> 16;
		p[a+1] = d;
	}
#endif
}

void clear_fame_mem_dummy(void) {
}

#endif