/*
 *  DisaSupport.cpp
 *  iAmiga
 *
 *  Created by Stuart Carnie on 12/27/10.
 *  Copyright 2010 Manomio LLC. All rights reserved.
 *
 */

#include "sysconfig.h"

#if DISASSEMBLER

#include "Disa.h"
#include "DisaSupport.h"
#include "disassembler.h"

int kLogMagic = 'gima';
int kLogMagic2 = '100v';
FILE *g_logFile = NULL;

void DisaCreateFile(int overwrite) {
	g_logFile = fopen(getDebugFileName(), overwrite ? "w" : "a");
	g_logOutput = g_logFile;
	
	// magic
	fwrite(&kLogMagic, sizeof(kLogMagic), 1, g_logFile);
	fwrite(&kLogMagic2, sizeof(kLogMagic2), 1, g_logFile);
	
	printf("log file open : %s\n", getDebugFileName());
}

void DisaCloseFile() {
	if (g_logFile) {
		fclose(g_logFile);
		g_logFile = NULL;
		g_logOutput = stdout;
		
		printf("log file closed\n");
	}
}

#endif