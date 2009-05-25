/*
 * UAE - The Un*x Amiga Emulator
 *
 * Common code needed by all the various graphics systems.
 *
 * (c) 1996 Bernd Schmidt, Ed Hanway, Samuel Devulder
 */

#include "sysconfig.h"
#include "sysdeps.h"

#include "config.h"
#include "uae.h"
#include "xwin.h"

unsigned long doMask (int p, int bits, int shift) {
    /* p is a value from 0 to 15 (Amiga color value)
     * scale to 0..255, shift to align msb with mask, and apply mask */
	
    register unsigned long val = p * 0x11111111UL;
    val >>= (32 - bits);
    val <<= shift;
	
    return val;
}

void alloc_colors64k (int rw, int gw, int bw, int rs, int gs, int bs) {
    int i;
    for (i = 0; i < 4096; i++) {
		int r = i >> 8;
		int g = (i >> 4) & 0xF;
		int b = i & 0xF;
		xcolors[i] = doMask(r, rw, rs) | doMask(g, gw, gs) | doMask(b, bw, bs);
    }
}
