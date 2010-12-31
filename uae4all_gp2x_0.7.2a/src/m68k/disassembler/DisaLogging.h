/*
 *  DisaLogging.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 12/28/10.
 *  Copyright 2010 Manomio LLC. All rights reserved.
 *
 */
#include "DisaSupport.h"

enum tagInterruptBits {
	DSKBLKInterrupt = (1 << 1),				// bit 1
	CopperInterrupt = (1 << 4),				// bit 4
	VerticalBlankingInterrupt = (1 << 5),	// bit 5
	BlitterInterrupt = (1 << 6),			// bit 6
	AUD0Interrupt = (1 << 7),				// bit 7
	AUD1Interrupt = (1 << 8),				// bit 8
	AUD2Interrupt = (1 << 9),				// bit 9
	AUD3Interrupt = (1 << 10),				// bit 10
	DSKSYNInterrupt = (1 << 12),			// bit 12
	MasterInterruptEnable = (1 << 14)		// bit 14
};

enum tagDisaEntryType {
	EntryTypeInstructionL0,
	EntryTypeInstructionL1,
	EntryTypeInstructionL2,
	EntryTypeException,
	EntryTypeEmulateStart,
} __attribute__((__packed__));

struct tagInstructionL0 {
	uint32_t	pc;
	uint16_t	opcodes[6];
	unsigned char ccr;
} __attribute__((__packed__));

struct tagInstructionL1 : tagInstructionL0 {
	uint8_t		inscycles;
} __attribute__((__packed__));


struct tagInstructionL2 : public tagInstructionL1 {
	uint32_t	dreg[8];
	uint32_t	areg[8];
} __attribute__((__packed__));

struct tagEmulateStart {
	uint16_t	cycles_to_execute;
	uint32_t	total_cycles;
} __attribute__((__packed__));

struct tagExceptionRecord {
	uint8_t		vector;
	uint32_t	oldPC, newPC;
} __attribute__((__packed__));