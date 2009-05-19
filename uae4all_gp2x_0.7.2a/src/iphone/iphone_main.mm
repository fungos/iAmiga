/*
 *  iphone_main.c
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#include "iphone_main.h"

char launchDir[300];

int mainMenu_showStatus=0;
int mainMenu_mouseMultiplier = 1;
int mainMenu_sound=1;
int mainMenu_case=-1;
int mainMenu_autosave=1;
int mainMenu_ntsc=0;
int drawfinished=0;

int gui_init() {
	return 0;
}

void gui_update() {
}

void gui_handle_events() {
}

void sound_default_evtime(void) {
}

char* get_rom_path() {
	NSString *bp = [[NSBundle mainBundle] bundlePath];
	bp = [bp stringByAppendingPathComponent:@"kick.rom"];
	
	static char bundlePath[500];
	
	[bp getCString:bundlePath maxLength:sizeof(bundlePath) encoding:[NSString defaultCStringEncoding]];
	
	return bundlePath;
}