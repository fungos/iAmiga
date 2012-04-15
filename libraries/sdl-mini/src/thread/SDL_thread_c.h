#include "SDL_config.h"

#ifndef _SDL_thread_c_h
#define _SDL_thread_c_h

/* Need the definitions of SYS_ThreadHandle */
#if SDL_THREADS_DISABLED
#include "generic/SDL_systhread_c.h"
#elif SDL_THREAD_BEOS
#include "beos/SDL_systhread_c.h"
#elif SDL_THREAD_EPOC
#include "epoc/SDL_systhread_c.h"
#elif SDL_THREAD_PTHREAD
#include "pthread/SDL_systhread_c.h"
#elif SDL_THREAD_SPROC
#include "irix/SDL_systhread_c.h"
#elif SDL_THREAD_WIN32
#include "win32/SDL_systhread_c.h"
#elif SDL_THREAD_NDS
#include "nds/SDL_systhread_c.h"
#else
#error Need thread implementation for this platform
#include "generic/SDL_systhread_c.h"
#endif
#include "../SDL_error_c.h"

/* This is the system-independent thread info structure */
struct SDL_Thread
{
    SDL_threadID threadid;
    SYS_ThreadHandle handle;
    int status;
    SDL_error errbuf;
    void *data;
};

/* This is the function called to run a thread */
extern void SDL_RunThread(void *data);


#endif