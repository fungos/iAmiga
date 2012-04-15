#ifndef _UAE_H
#define _UAE_H

/*
  * UAE - The Un*x Amiga Emulator
  *
  * Prototypes for main.c
  *
  * Copyright 1996 Bernd Schmidt
  */

enum tagUAERunState {
    RunStateNotStarted = -2,
	RunStateSpecialQuit = -1,
	RunStateNormal = 0,
	RunStateExit = 1,
	RunStateReset = 2,
};

class uae {
public:
	uae();
	
	void real_main();
	void uae_reset (void);
	void uae_quit (void);
	void reset_all_systems (void);
	void uae_pause(void);
	void uae_resume(void);
	
public:
	// state
	tagUAERunState quit_program;
	bool paused;
    bool running;
	
private:
	void do_start_program (void);
	void do_leave_program (void);
	void start_program (void);
	void leave_program (void);
	void default_prefs();

};

extern uae g_emulator;

extern "C" void uae_reset();

#endif