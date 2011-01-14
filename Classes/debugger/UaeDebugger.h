//
//  UaeDebugger.h
//  iAmiga
//
//  Created by Stuart Carnie on 1/12/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AsyncSocket;

@interface UaeDebugger : NSObject {
	AsyncSocket			*debugServer;
	NSMutableArray		*connectedClients;
	BOOL				running;
}

@property (readonly,getter=isRunning) BOOL running;

- (void) startOnPort:(int)port;
- (void) stop;

@end
