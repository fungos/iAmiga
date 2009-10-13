 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Events
  * These are best for low-frequency events. Having too many of them,
  * or using them for events that occur too frequently, can cause massive
  * slowdown.
  *
  * Copyright 1995-1998 Bernd Schmidt
  */

#include "rpt.h"

#define UNROLL_EVENT_LOOP

extern frame_time_t vsynctime, vsyncmintime;
extern void reset_frame_rate_hack (void);
extern int rpt_available;

extern void compute_vsynctime (void);

extern unsigned long currcycle, nextevent;

typedef void (*evfunc)(void);

struct ev
{
    int active;
    unsigned long int evtime, oldcycles;
#ifndef UNROLL_EVENT_LOOP
    evfunc handler;
#endif
};

enum {
    ev_hsync, ev_copper, ev_audio, ev_cia, ev_blitter, ev_disk,
    ev_max
};

extern struct ev eventtab[ev_max];

static __inline__ void events_schedule (void)
{
    int i;
	
    unsigned long int mintime = ~0L;
    for (i = 0; i < ev_max; i++) {
		if (eventtab[i].active) {
			unsigned long int eventtime = eventtab[i].evtime - currcycle;
			if (eventtime < mintime)
				mintime = eventtime;
		}
    }
    nextevent = currcycle + mintime;
}

#ifdef UNROLL_EVENT_LOOP
#import "memory.h"
#import "audio.h"
extern "C" void hsync_handler(void) ;
extern "C" void copper_handler(void) ;
extern "C" void audio_evhandler(void);
extern "C" void CIA_handler(void);
extern "C" void blitter_handler(void);
extern "C" void DISK_handler(void);

#if 1 && defined(__arm__)

#define CALL_HANDLER(FN, X) \
	asm volatile("cmp %0, #1\n\t" \
				 "cmpeq %1, %2\n\t" \
				 "moveq lr, pc\n\t" \
				 "beq _" #FN \
				 :: "r" (eventtab[X].active), \
				 "r" (eventtab[X].evtime), \
				 "r" (currcycle) \
				 : "pc", "lr", "cc", "r9", "r12", "r0", "r1", "r2", "r3", "memory"); \
	//next_event++;

static __inline__ void do_cycles_slow (unsigned long cycles_to_add) {
    while ((nextevent - currcycle) <= cycles_to_add) {
		//register struct ev *next_event asm("r4") = &eventtab[0];
		PRELOAD(eventtab);
        cycles_to_add -= (nextevent - currcycle);
        currcycle = nextevent;
		
		CALL_HANDLER(hsync_handler, 0);
		CALL_HANDLER(copper_handler, 1);
		CALL_HANDLER(audio_evhandler, 2);
		CALL_HANDLER(CIA_handler, 3);
		CALL_HANDLER(blitter_handler, 4);
		CALL_HANDLER(DISK_handler, 5);
		
		events_schedule();
    }
    currcycle += cycles_to_add;
}

#else

static __inline__ void do_cycles_slow (unsigned long cycles_to_add) {
    while ((nextevent - currcycle) <= cycles_to_add) {
		register struct ev *next_event = eventtab;
		PRELOAD(next_event);
        cycles_to_add -= (nextevent - currcycle);
        currcycle = nextevent;
		
		if (next_event->active && next_event->evtime == currcycle)
			hsync_handler();
		if ((++next_event)->active && next_event->evtime == currcycle)
			copper_handler();
		if ((++next_event)->active && next_event->evtime == currcycle)
			audio_evhandler();
		PRELOAD(next_event);
		if ((++next_event)->active && next_event->evtime == currcycle)
			CIA_handler();
		if ((++next_event)->active && next_event->evtime == currcycle)
			blitter_handler();
		if ((++next_event)->active && next_event->evtime == currcycle)
			DISK_handler();

        events_schedule();
    }
    currcycle += cycles_to_add;
}

#endif

/* This is a special-case function.  Normally, all events should lie in the
 future; they should only ever be active at the current cycle during
 do_cycles.  However, a snapshot is saved during do_cycles, and so when
 restoring it, we may have other events pending.  */
static __inline__ void handle_active_events (void)
{
	if (eventtab[ev_hsync].active && eventtab[ev_hsync].evtime == currcycle) {
		hsync_handler();
	}
	if (eventtab[ev_copper].active && eventtab[ev_copper].evtime == currcycle) {
		copper_handler();
	}
	if (eventtab[ev_audio].active && eventtab[ev_audio].evtime == currcycle) {
		audio_evhandler();
	}
	if (eventtab[ev_cia].active && eventtab[ev_cia].evtime == currcycle) {
		CIA_handler();
	}
	if (eventtab[ev_blitter].active && eventtab[ev_blitter].evtime == currcycle) {
		blitter_handler();
	}
	if (eventtab[ev_disk].active && eventtab[ev_disk].evtime == currcycle) {
		DISK_handler();
	}
}


#else

static __inline__ void do_cycles_slow (unsigned long cycles_to_add)
{
    while ((nextevent - currcycle) <= cycles_to_add) {
        int i;
        cycles_to_add -= (nextevent - currcycle);
        currcycle = nextevent;
		
        for (i = 0; i < ev_max; i++) {
			if (eventtab[i].active && eventtab[i].evtime == currcycle) {
				(*eventtab[i].handler)();
			}
		}
        events_schedule();
    }
    currcycle += cycles_to_add;
}

/* This is a special-case function.  Normally, all events should lie in the
 future; they should only ever be active at the current cycle during
 do_cycles.  However, a snapshot is saved during do_cycles, and so when
 restoring it, we may have other events pending.  */
static __inline__ void handle_active_events (void)
{
    int i;
    for (i = 0; i < ev_max; i++) {
		if (eventtab[i].active && eventtab[i].evtime == currcycle) {
			(*eventtab[i].handler)();
		}
    }
}

#endif

static __inline__ unsigned long get_cycles (void)
{
    return currcycle;
}

extern void init_eventtab (void);


#define do_cycles do_cycles_slow


