/*
 *  AmigaOptions.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/23/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#import "uae.h"

class Prefs {
public:
	int produce_sound;
	int changed_produce_sound;
	char prefs_df[NUM_DRIVES][256];
	char changed_df[NUM_DRIVES][256];
	int real_changed_df[NUM_DRIVES];
	char romfile[256];
	unsigned prefs_chipmem_size;
	int prefs_gfx_framerate, changed_gfx_framerate;
	int m68k_speed;
	int timeslice_mode;
	
	Prefs();
};