/*
 *  JoyStickTypes.h
 *  C64
 *
 *  Created by Stuart Carnie on 6/15/10.
 *  Copyright 2010 Manomio LLC. All rights reserved.
 *
 */

typedef enum TouchStickDPadState {
	DPadCenter,
	DPadUp,
	DPadUpRight,
	DPadRight,
	DPadDownRight,
	DPadDown,
	DPadDownLeft,
	DPadLeft,
	DPadUpLeft,
	
	DPadNone = 1000
} TouchStickDPadState;

typedef enum FireButtonState {
	FireButtonUp,
	FireButtonDown
} FireButtonState;
