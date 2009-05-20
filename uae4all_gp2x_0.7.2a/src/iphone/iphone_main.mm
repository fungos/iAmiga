/*
 *  iphone_main.c
 *  iAmiga
 *
 *  Created by Stuart Carnie on 5/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import "sysconfig.h"
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

#if defined(NO_SOUND)
void sound_default_evtime(void) {
}
#endif

char* get_rom_path() {
	NSString *bp = [[NSBundle mainBundle] bundlePath];
	bp = [bp stringByAppendingPathComponent:@"kick13.rom"];
	
	static char bundlePath[500];
	
	[bp getCString:bundlePath maxLength:sizeof(bundlePath) encoding:[NSString defaultCStringEncoding]];
	
	return bundlePath;
}

char* get_df0_path() {
	NSString *bp = [[NSBundle mainBundle] bundlePath];
	bp = [bp stringByAppendingPathComponent:@"BEAST1-1.ADF"];
	
	static char df0Path[500];
	
	[bp getCString:df0Path maxLength:sizeof(df0Path) encoding:[NSString defaultCStringEncoding]];
	
	return df0Path;
}