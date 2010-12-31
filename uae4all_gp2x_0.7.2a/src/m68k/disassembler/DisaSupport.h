/*
 *  DisaSupport.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 12/27/10.
 *  Copyright 2010 Manomio LLC. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdint.h>

#if __cplusplus
extern "C" {
#endif


extern int kLogMagic;
extern int kLogMagic2;
extern FILE *g_logOutput;


extern void DisaCreateFile(int overwrite);
extern void DisaCloseFile();

#if __cplusplus
}
#endif