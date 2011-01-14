//
//  UaeDebugger.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/12/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "UaeDebugger.h"
#import "AsyncSocket.h"
#include <arpa/telnet.h>

typedef enum {
	WelcomeMsgTag,
	GenericMsgTag
} MessageTags;

@implementation UaeDebugger

@synthesize running;

- (id) init;
{
    self = [super init];
    if (self != nil)
    {
        debugServer = [[AsyncSocket alloc] initWithDelegate:self];
        connectedClients = [[NSMutableArray alloc] initWithCapacity:1];
        running = false;
    }
    return self;
}

- (void) dealloc;
{
    [self stop];
    [connectedClients release];
    [debugServer release];
    [super dealloc];
}

- (void) startOnPort:(int)port;
{
    if (running) return;
    
    if (port < 0 || port > 65535)
        port = 0;
    
    NSError *error = nil;
    if (![debugServer acceptOnPort:port error:&error])
        return;
    
    NSLog(@"My Awesome Debug Server has started on port %hu", [debugServer localPort]);
    
    running = true;
}


- (void) stop;
{
    if (!running) return;
    
    [debugServer disconnect];
    for (AsyncSocket* socket in connectedClients)
        [socket disconnect]; 
    
    running = false;
}

- (void)onSocket:(AsyncSocket *)socket didAcceptNewSocket:(AsyncSocket *)newSocket;
{
    [connectedClients addObject:newSocket];
}


- (void)onSocketDidDisconnect:(AsyncSocket *)socket;
{
    [connectedClients removeObject:socket];
}

-(void)sendOptWithCode:(int)code andOption:(int)option toSocket:(AsyncSocket *)socket {
	uint8_t buf[3];
	buf[0] = IAC;
	buf[1] = (uint8_t)code;
	buf[2] = (uint8_t)option;
	NSData *d = [NSData dataWithBytes:buf length:3];
	[socket writeData:d withTimeout:-1 tag:GenericMsgTag];
}

- (void)onSocket:(AsyncSocket *)socket didConnectToHost:(NSString *)host port:(UInt16)port;
{
    NSLog(@"Accepted client %@:%hu", host, port);
	
    NSData *welcomeData = [@"Welcome to my Awesome Debug Server\r\n" 
						   dataUsingEncoding:NSUTF8StringEncoding];
    [socket writeData:welcomeData withTimeout:-1 tag:WelcomeMsgTag];

	[self sendOptWithCode:DO andOption:TELOPT_ECHO toSocket:socket];	
	[self sendOptWithCode:DO andOption:TELOPT_NAWS toSocket:socket];
	[self sendOptWithCode:DO andOption:TELOPT_LFLOW toSocket:socket];
	[self sendOptWithCode:WILL andOption:TELOPT_ECHO toSocket:socket];	
	[self sendOptWithCode:WILL andOption:TELOPT_SGA toSocket:socket];	
	
    [socket readDataWithTimeout:-1 tag:GenericMsgTag];
}


- (void)onSocket:(AsyncSocket *)socket didReadData:(NSData *)data withTag:(long)tag;
{
    NSString *tmp = [NSString stringWithUTF8String:[data bytes]];
    NSString *input = [tmp stringByTrimmingCharactersInSet:
					   [NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
	uint8_t *bytes = (uint8_t*)[data bytes];
	if (bytes[0] == '\b') {
		//uint8_t ec[] = {IAC, DO, EC};
		//[socket writeData:[NSData dataWithBytes:&ec length:3] withTimeout:-1 tag:0];
		[socket writeData:data withTimeout:-1 tag:0];
	} else if (bytes[0] == 0x0d) {
		NSData *d = [@"\r\n" dataUsingEncoding:NSUTF8StringEncoding];
		[socket writeData:d withTimeout:-1 tag:GenericMsgTag];
	} else if (bytes[0] != IAC) {
		[socket writeData:data withTimeout:-1 tag:0];
	}

	
    if ([input isEqualToString:@"exit"])
    {
        NSData *byeData = [@"Bye!\r\n" dataUsingEncoding:NSUTF8StringEncoding];
        [socket writeData:byeData withTimeout:-1 tag:GenericMsgTag];
        [socket disconnectAfterWriting];
        return;
    }
    
    [socket readDataWithTimeout:-1 tag:GenericMsgTag];
}

@end
