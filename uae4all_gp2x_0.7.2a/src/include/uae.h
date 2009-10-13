 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Prototypes for main.c
  *
  * Copyright 1996 Bernd Schmidt
  */

class uae {
public:
	uae();
	
	void real_main();
	void uae_reset (void);
	void uae_quit (void);
	void reset_all_systems (void);
	
public:
	// state
	int quit_program;
	
private:
	void do_start_program (void);
	void do_leave_program (void);
	void start_program (void);
	void leave_program (void);
	void default_prefs();

};

extern uae g_emulator;

extern "C" void uae_reset();
