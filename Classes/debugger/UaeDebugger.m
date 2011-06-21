//
//  UaeDebugger.m
//  iAmiga
//
//  Created by Stuart Carnie on 1/12/11.
//  Copyright 2011 Manomio LLC. All rights reserved.
//

#import "UaeDebugger.h"
#import "AsyncSocket.h"
//#include <arpa/telnet.h>

/*
 * Definitions for the TELNET protocol.
 */
#define	IAC	255		/* interpret as command: */
#define	DONT	254		/* you are not to use option */
#define	DO	253		/* please, you use option */
#define	WONT	252		/* I won't use option */
#define	WILL	251		/* I will use option */
#define	SB	250		/* interpret as subnegotiation */
#define	GA	249		/* you may reverse the line */
#define	EL	248		/* erase the current line */
#define	EC	247		/* erase the current character */
#define	AYT	246		/* are you there */
#define	AO	245		/* abort output--but let prog finish */
#define	IP	244		/* interrupt process--permanently */
#define	BREAK	243		/* break */
#define	DM	242		/* data mark--for connect. cleaning */
#define	NOP	241		/* nop */
#define	SE	240		/* end sub negotiation */
#define EOR     239             /* end of record (transparent mode) */
#define	ABORT	238		/* Abort process */
#define	SUSP	237		/* Suspend process */
#define	xEOF	236		/* End of file: EOF is already used... */

#define SYNCH	242		/* for telfunc calls */

/* telnet options */
#define TELOPT_BINARY	0	/* 8-bit data path */
#define TELOPT_ECHO	1	/* echo */
#define	TELOPT_RCP	2	/* prepare to reconnect */
#define	TELOPT_SGA	3	/* suppress go ahead */
#define	TELOPT_NAMS	4	/* approximate message size */
#define	TELOPT_STATUS	5	/* give status */
#define	TELOPT_TM	6	/* timing mark */
#define	TELOPT_RCTE	7	/* remote controlled transmission and echo */
#define TELOPT_NAOL 	8	/* negotiate about output line width */
#define TELOPT_NAOP 	9	/* negotiate about output page size */
#define TELOPT_NAOCRD	10	/* negotiate about CR disposition */
#define TELOPT_NAOHTS	11	/* negotiate about horizontal tabstops */
#define TELOPT_NAOHTD	12	/* negotiate about horizontal tab disposition */
#define TELOPT_NAOFFD	13	/* negotiate about formfeed disposition */
#define TELOPT_NAOVTS	14	/* negotiate about vertical tab stops */
#define TELOPT_NAOVTD	15	/* negotiate about vertical tab disposition */
#define TELOPT_NAOLFD	16	/* negotiate about output LF disposition */
#define TELOPT_XASCII	17	/* extended ascic character set */
#define	TELOPT_LOGOUT	18	/* force logout */
#define	TELOPT_BM	19	/* byte macro */
#define	TELOPT_DET	20	/* data entry terminal */
#define	TELOPT_SUPDUP	21	/* supdup protocol */
#define	TELOPT_SUPDUPOUTPUT 22	/* supdup output */
#define	TELOPT_SNDLOC	23	/* send location */
#define	TELOPT_TTYPE	24	/* terminal type */
#define	TELOPT_EOR	25	/* end or record */
#define	TELOPT_TUID	26	/* TACACS user identification */
#define	TELOPT_OUTMRK	27	/* output marking */
#define	TELOPT_TTYLOC	28	/* terminal location number */
#define	TELOPT_3270REGIME 29	/* 3270 regime */
#define	TELOPT_X3PAD	30	/* X.3 PAD */
#define	TELOPT_NAWS	31	/* window size */
#define	TELOPT_TSPEED	32	/* terminal speed */
#define	TELOPT_LFLOW	33	/* remote flow control */
#define TELOPT_LINEMODE	34	/* Linemode option */
#define TELOPT_XDISPLOC	35	/* X Display Location */
#define TELOPT_OLD_ENVIRON 36	/* Old - Environment variables */
#define	TELOPT_AUTHENTICATION 37/* Authenticate */
#define	TELOPT_ENCRYPT	38	/* Encryption option */
#define TELOPT_NEW_ENVIRON 39	/* New - Environment variables */
#define	TELOPT_EXOPL	255	/* extended-options-list */


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
