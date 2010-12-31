/*
 *  disassembler.m
 *  iAmiga
 *
 *  Created by Stuart Carnie on 12/23/10.
 *  Copyright 2010 Manomio LLC. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#include "disassembler.h"

#define DOCUMENTS_FOLDER [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"]

const char *getDebugFileName() {
	NSString *fileName = [DOCUMENTS_FOLDER stringByAppendingPathComponent:@"log.txt"];
	static char buffer[512];
	[fileName getCString:buffer maxLength:sizeof(buffer)/sizeof(buffer[0]) encoding:[NSString defaultCStringEncoding]];
	return buffer;
}