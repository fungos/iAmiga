/*
 *  AmigaOptions.cpp
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/23/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#import <string>
#include "Prefs.h"
#import "iphone_main.h"

Prefs::Prefs() {
#ifdef NO_SOUND
    produce_sound = 0;
#else
    produce_sound = 2;
#endif
	
    prefs_gfx_framerate = 2;
	
	strcpy (prefs_df[0], get_df0_path());
    strcpy (prefs_df[1], ROM_PATH_PREFIX "df1.adf");
	
	strcpy(romfile, get_rom_path());
	
    //prefs_chipmem_size=0x00100000;
	prefs_chipmem_size=0x00080000;		// 512kb
	
	// emu bias -> system clock | sync threshold
	// X O O O O -> 100 | 50
	// O X O O O -> 83 | 100
	// O O X O O -> 83 | 50
	// O O O X O -> 75 | 50
	// O O O O X -> 75 | 25
	// o "System clock" (m68k_speed), which allows you to underclock the whole system to improve emulation performance, but breaks sound pitch. 
	// o "Sync threshold" (timeslice_mode), which allows to reduce amount of synchronization between 68k and other chips to also improve performance. 
	// Set both to 100 for best compatibility
	
	// 0 = 100%
	// 1 = 75%
	// 2 = 50%
	// 3 = 25%
	timeslice_mode = 0;
	
	// 0 = 100%
	// 2 = 83%
	// 4 = 75%
	m68k_speed = 0;
}