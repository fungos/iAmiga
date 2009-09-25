/*
 *  c68k_misc.h
 *  M68kTests
 *
 *  Created by Stuart Carnie on 7/26/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

/*
#define MOVEMaR(SIZE, MEM_READ)	\
	do { \
		if (res & 1) { \
			*(s32*)src = MEM_READ(adr) \
			adr += SIZE; \
		} \
		src += 4; \
	} while (res >>= 1);
*/
#define MOVEMaR(SIZE, MEM_READ)				\
	src -= 4;								\
	regloop:								\
	asm volatile("\n"						\
		"1: \n\t"							\
		"add %[src], %[src], #4 \n\t"		\
		"movs %[res], %[res], lsr #1 \n\t"	\
		"bcc 1b \n\t"						\
		";@ copy data from memory to register" \
		: [src] "+r" (src), [res] "+r" (res)\
		:: "cc"); \
											\
	*(s32*)src = MEM_READ(adr);				\
	adr+=SIZE;									\
	if (res) goto regloop;					
