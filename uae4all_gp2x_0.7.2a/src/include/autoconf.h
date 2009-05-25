 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Autoconfig device support
  *
  * (c) 1996 Ed Hanway
  */


typedef uae_u32 (*TrapFunction) (void);

extern int lasttrap;
extern void do_emultrap (int nr);

extern uae_u32 addr (int);
extern void db (uae_u8);
extern void dw (uae_u16);
extern void dl (uae_u32);
extern uae_u32 ds (char *);
extern void calltrap (uae_u32);
extern void org (uae_u32);
extern uae_u32 here (void);
extern int deftrap2 (TrapFunction func, int mode, const char *str);
extern int deftrap (TrapFunction);
extern void align (int);
extern uae_u32 CallLib (uaecptr base, uae_s16 offset);
extern void call_calltrap (int nr) REGPARAM;

extern volatile int uae_int_requested;
extern void set_uae_int_flag (void);

#define RTS 0x4e75
#define RTE 0x4e73

extern uaecptr EXPANSION_explibname, EXPANSION_doslibname, EXPANSION_uaeversion;
extern uaecptr EXPANSION_explibbase, EXPANSION_uaedevname, EXPANSION_haveV36;
extern uaecptr EXPANSION_bootcode, EXPANSION_nullfunc;

extern uaecptr ROM_filesys_resname, ROM_filesys_resid;
extern uaecptr ROM_filesys_diagentry;
extern uaecptr ROM_hardfile_resname, ROM_hardfile_resid;
extern uaecptr ROM_hardfile_init;
extern uaecptr filesys_initcode;

#define TRAPFLAG_NO_REGSAVE 1
#define TRAPFLAG_NO_RETVAL 2
#define TRAPFLAG_EXTRA_STACK 4
#define TRAPFLAG_DORET 8

extern uaecptr libemu_InstallFunction (TrapFunction, uaecptr, int, const char *);
extern uaecptr libemu_InstallFunctionFlags (TrapFunction, uaecptr, int, int, const char *);

#define RTAREA_BASE 0xF00000
