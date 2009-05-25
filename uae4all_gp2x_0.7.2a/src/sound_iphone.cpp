/* 
 * Minimalistic sound.c implementation for gp2x
 * (c) notaz, 2007
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"
#include "uae.h"
#include "options.h"
#include "memory.h"
#include "debug_uae4all.h"
#include "audio.h"
#include "gensound.h"
#include "sound.h"
#include "custom.h"


extern unsigned long next_sample_evtime;

int produce_sound=0;
int changed_produce_sound=0;

unsigned int sound_rate=DEFAULT_SOUND_FREQ;

static uae_u16 sndbuffer[4][SNDBUFFER_LEN+32] UAE4ALL_ALIGN;
unsigned n_callback_sndbuff, n_render_sndbuff;
uae_u16 *sndbufpt = sndbuffer[0];
uae_u16 *render_sndbuff = sndbuffer[0];

#ifndef PROFILER_UAE4ALL

int tablas_ajuste[8][9]=
{
	{ 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 },	// 0
	{ 3 , 4 , 3 , 4 , 3 , 4 , 3 , 4 , 3 },	// 1 
	{ 1 , 2 , 1 , 2 , 1 , 2 , 1 , 2 , 1 },	// 2 
	{ 1 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 },	// 3 
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },	// 4 
	{ 0 ,-1 , 0 ,-1 , 0 ,-1 , 0 ,-1 , 0 },	// 5 
	{-2 ,-1 ,-2 ,-1 ,-2 ,-1 ,-2 ,-1 ,-2 },	// 6 
	{-4 ,-3 ,-4 ,-3 ,-4 ,-3 ,-4 ,-3 ,-4 },	// 7
};

#else

int tablas_ajuste[8][9]=
{
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
};

#endif


int *tabla_ajuste=(int *)&tablas_ajuste[4];

#ifdef NO_SOUND


void finish_sound_buffer (void) {  }

int setup_sound (void) { sound_available = 0; return 0; }

void close_sound (void) { }

int init_sound (void) { return 0; }

void pause_sound (void) { }

void resume_sound (void) { }

void uae4all_init_sound(void) { }

void uae4all_play_click(void) { }

void uae4all_pause_music(void) { }

void uae4all_resume_music(void) { }

#else

#import "AudioQueueManager.h"

static CAudioQueueManager *g_audioQueue;

static int have_sound = 0;

void sound_default_evtime(void)
{
	int pal = beamcon0 & 0x20;
	switch(m68k_speed)
	{
		case 6:
			scaled_sample_evtime=(unsigned)(MAXHPOS_PAL*MAXVPOS_PAL*VBLANK_HZ_PAL*CYCLE_UNIT/1.86)/sound_rate;
			break;
			
		case 5:
		case 4: // ~4/3 234
			if (pal)
				scaled_sample_evtime=(MAXHPOS_PAL*244*VBLANK_HZ_PAL*CYCLE_UNIT)/sound_rate; // ???
			else
				scaled_sample_evtime=(MAXHPOS_NTSC*255*VBLANK_HZ_NTSC*CYCLE_UNIT)/sound_rate;
			break;
			
		case 3:
		case 2: // ~8/7 273
			if (pal)
				scaled_sample_evtime=(MAXHPOS_PAL*270*VBLANK_HZ_PAL*CYCLE_UNIT)/sound_rate;
			else
				scaled_sample_evtime=(MAXHPOS_NTSC*255*VBLANK_HZ_NTSC*CYCLE_UNIT)/sound_rate;
			break;
			
		case 1:
		default: // MAXVPOS_PAL?
			if (pal)
				scaled_sample_evtime=(MAXHPOS_PAL*313*VBLANK_HZ_PAL*CYCLE_UNIT)/sound_rate;
			else
				scaled_sample_evtime=(MAXHPOS_NTSC*MAXVPOS_NTSC*VBLANK_HZ_NTSC*CYCLE_UNIT)/sound_rate + 1;
			break;
	}
	
	schedule_audio();
}


void finish_sound_buffer (void)
{
	static int usingTemp = 0;
#ifdef DEBUG_SOUND
	dbg("sound.c : finish_sound_buffer");
#endif
	
	if (!usingTemp)
		g_audioQueue->queueBuffer((short int*)render_sndbuff);
	
	sndbufpt = render_sndbuff = (uae_u16*)g_audioQueue->getNextBuffer();
	if (sndbufpt)
		usingTemp = 0;
	else {
		usingTemp = 1;
		sndbufpt = render_sndbuff = sndbuffer[0];
	}
	
#ifdef DEBUG_SOUND
	dbg(" sound.c : ! finish_sound_buffer");
#endif
}


/* Try to determine whether sound is available.  This is only for GUI purposes.  */
int setup_sound (void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : setup_sound");
#endif
	
    //if (gp2x_start_sound(sound_rate, 16, 0) != 0)
	//    return 0;
	
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! setup_sound");
#endif
    return 1;
}

static int open_sound (void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : open_sound");
#endif
	
	g_audioQueue = new CAudioQueueManager(sound_rate, SNDBUFFER_LEN>>1, MonoSound);
	g_audioQueue->start();
	sndbufpt = render_sndbuff = (uae_u16*)g_audioQueue->getNextBuffer();
    //if (gp2x_start_sound(sound_rate, 16, 0) != 0)
	//    return 0;
	
    sound_default_evtime();
	
    have_sound = 1;
    sound_available = 1;
	
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! open_sound");
#endif
    return 1;
}

void close_sound (void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : close_sound");
#endif
    if (!have_sound)
		return;
	
    // testing shows that reopenning sound device is not a good idea on gp2x (causes random sound driver crashes)
    // we will close it on real exit instead
    //gp2x_stop_sound();
	g_audioQueue->stop();
	
    have_sound = 0;
	
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! close_sound");
#endif
}

int init_sound (void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : init_sound");
#endif
	
    have_sound=open_sound();
	
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! init_sound");
#endif
    return have_sound;
}

void pause_sound (void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : pause_sound");
#endif
	
	g_audioQueue->pause();
	
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! pause_sound");
#endif
}

void resume_sound (void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : resume_sound");
#endif
	
    g_audioQueue->resume();
	
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! resume_sound");
#endif
}

void uae4all_init_sound(void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : uae4all_init_sound");
#endif
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! uae4all_init_sound");
#endif
}

void uae4all_pause_music(void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : pause_music");
#endif
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! pause_music");
#endif
}

void uae4all_resume_music(void)
{
#ifdef DEBUG_SOUND
    dbg("sound.c : resume_music");
#endif
#ifdef DEBUG_SOUND
    dbg(" sound.c : ! resume_music");
#endif
}

void uae4all_play_click(void)
{
}
#endif

