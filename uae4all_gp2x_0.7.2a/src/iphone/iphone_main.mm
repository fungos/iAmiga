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
#include "debug_uae4all.h"

char launchDir[300];

int mainMenu_showStatus=0;
int mainMenu_mouseMultiplier = 1;
int mainMenu_sound=1;
int mainMenu_case=-1;
int mainMenu_autosave=1;
int mainMenu_ntsc=0;
int drawfinished=0;

extern int vkbd_mode;

int gui_init() {
	vkbd_mode = 0;
	
#ifdef PROFILER_UAE4ALL
	uae4all_prof_init();
	uae4all_prof_add("M68K");			// 0
	uae4all_prof_add("EVENTS");			// 1
	uae4all_prof_add("HSync");			// 2
	uae4all_prof_add("Copper");			// 3
	uae4all_prof_add("Audio");			// 4
	uae4all_prof_add("CIA");			// 5
	uae4all_prof_add("Blitter");			// 6
	uae4all_prof_add("Vsync");			// 7
	uae4all_prof_add("update_fetch");		// 8
	uae4all_prof_add("linetoscr");			// 9
	uae4all_prof_add("do_long_fetch");		// 10
	uae4all_prof_add("pfield_doline");		// 11
	uae4all_prof_add("draw_sprites_ecs");		// 12
	uae4all_prof_add("flush_block");		// 13
	uae4all_prof_add("SET_INTERRUPT");		// 14
	/*
	 uae4all_prof_add("15");		// 15
	 uae4all_prof_add("16");		// 16
	 uae4all_prof_add("17");		// 17
	 uae4all_prof_add("18");		// 18
	 uae4all_prof_add("19");		// 19
	 uae4all_prof_add("20");		// 20
	 uae4all_prof_add("21");		// 21
	 uae4all_prof_add("22");		// 22
	 */
#endif
    
    NSString *documents = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
    [documents getCString:launchDir maxLength:sizeof(launchDir) encoding:[NSString defaultCStringEncoding]];
    [[NSFileManager defaultManager] createDirectoryAtPath:[documents stringByAppendingPathComponent:@"saves"] withIntermediateDirectories:YES attributes:nil error:NULL];
	
	return 0;
}

int gui_update() {
    return 0;
}

void gui_handle_events() {
}

void gui_set_message(const char *msg, int t) {}
void gui_show_window_bar(int per, int max, int case_title) {}

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

extern "C" char changed_df[1][256];;

char* get_df_path(int drive) {
	NSString *bp = [[NSBundle mainBundle] bundlePath];
	
	static char df0Path[500];
	if (drive == 0) {
		bp = [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"IK+.adf"];
	} else if (drive == 1) {
		bp = [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"DEF2.ADF"];
	}
	
	[bp getCString:df0Path maxLength:sizeof(df0Path) encoding:[NSString defaultCStringEncoding]];
	return df0Path;
}

#ifdef PROFILER_UAE4ALL

static unsigned uae4all_prof_total_initial=0;
unsigned uae4all_prof_total=0;
static const char *uae4all_prof_msg[UAE4ALL_PROFILER_MAX];

unsigned long long uae4all_prof_initial[UAE4ALL_PROFILER_MAX];
unsigned long long uae4all_prof_sum[UAE4ALL_PROFILER_MAX];
unsigned long long uae4all_prof_executed[UAE4ALL_PROFILER_MAX];

void uae4all_prof_init(void) {
	unsigned i;
	unsigned long long s=SDL_GetTicks();

	for(i=0;i<UAE4ALL_PROFILER_MAX;i++) {
		uae4all_prof_initial[i]=s;
		uae4all_prof_sum[i]=0;
		uae4all_prof_executed[i]=0;
		if (!uae4all_prof_total)
			uae4all_prof_msg[i]=NULL;
	}
	uae4all_prof_total_initial=s;
}

void uae4all_prof_add(const char *msg) {
	if (uae4all_prof_total<UAE4ALL_PROFILER_MAX) {
		uae4all_prof_msg[uae4all_prof_total]=msg;	
		uae4all_prof_total++;
	}
}

void uae4all_prof_show(void) {
	unsigned i;
	double toper=0;

	unsigned long long to=SDL_GetTicks()-uae4all_prof_total_initial;
	
	puts("\n\n\n\n");
	puts("--------------------------------------------");
	for(i=0;i<uae4all_prof_total;i++)
	{
		switch (i) {
			case 1:
			case 2:
			case 7:
				continue;
		}
		unsigned long long t0=uae4all_prof_sum[i];
		double percent=(double)t0;
		percent*=100.0;
		percent/=(double)to;
		toper+=percent;
		printf("%s: %.2f%% -> Ticks=%i -> %iK calls\n",uae4all_prof_msg[i],percent,((unsigned)t0),(unsigned)(uae4all_prof_executed[i]>>10));
	}
	printf("TOTAL: %.2f%% -> Ticks=%i\n",toper,to);
	puts("--------------------------------------------"); fflush(stdout);
}

void uae4all_prof_show_statistics(void) {
	static Uint32 timer = SDL_GetTicks();

	Uint32 now = SDL_GetTicks();
	if (now - timer > 1000) {
		uae4all_prof_show();
		timer = now;
	}
}

int getDisplayIsNTSC() {
	return mainMenu_ntsc;
}

void setDisplayIsNTSC(int isNTSC) {
	mainMenu_ntsc = isNTSC;
}

#endif