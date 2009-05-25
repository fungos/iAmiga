 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Interface to the graphics system (X, SVGAlib)
  *
  * Copyright 1995-1997 Bernd Schmidt
  */

typedef long int xcolnr;

extern xcolnr xcolors[4096];

extern int buttonstate[3];
extern int newmousecounters;
extern int lastmx, lastmy;
extern int ievent_alive;

extern int graphics_setup (void);
extern int graphics_init (void);
extern void graphics_leave (void);
extern void handle_events (void);

extern void flush_block (int, int);
void black_screen_now(void);

#ifndef DREAMCAST
extern int lockscr (void);
extern void unlockscr (void);
#endif

extern int needmousehack (void);
extern void togglemouse (void);

extern void alloc_colors64k (int, int, int, int, int, int);

extern char *gfx_mem;
extern unsigned gfx_rowbytes;

class host {
	
};
