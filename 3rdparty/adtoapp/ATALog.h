//
//  Created by  on 06.06.13.
//  Copyright (c) 2013 . All rights reserved.
//

#ifndef header_ATALog_h
#define header_ATALog_h

#include <stdio.h>
#include <sys/time.h>

typedef NS_OPTIONS(NSInteger, ATALogLevel) {
	ATALogOff		= 0,
	ATALogFatal		= 1 << 0,
	ATALogError		= 1 << 1,
	ATALogWarn		= 1 << 2,
	ATALogDebug		= 1 << 3,
	ATALogVerbose	= 1 << 4
};

extern ATALogLevel ataloglevel;

#define ATALog(type, fmt, ...) {\
								NSString* mainString = [NSString stringWithFormat:fmt, ##__VA_ARGS__];\
								NSString* newBody = [mainString stringByReplacingOccurrencesOfString:@"\n" withString:@"\n\t\t"];\
								NSLog(@"<%@> %@ (%s)", type, newBody, __PRETTY_FUNCTION__);\
}

#ifndef ATALogF
#define ATALogF(fmt, ...)     if (ataloglevel & ATALogFatal) { ATALog(@"fatal", fmt, ##__VA_ARGS__); }
#define ATALogE(fmt, ...)     if (ataloglevel & ATALogError) { ATALog(@"error", fmt, ##__VA_ARGS__); }
#define ATALogW(fmt, ...)     if (ataloglevel & ATALogWarn) { ATALog(@"warn ", fmt, ##__VA_ARGS__); }
#define ATALogD(fmt, ...)     if (ataloglevel & ATALogDebug) { ATALog(@"debug", fmt, ##__VA_ARGS__); }
#define ATALogV(fmt, ...)     if (ataloglevel & ATALogVerbose) { ATALog(@"verbose", fmt, ##__VA_ARGS__); }
#endif

#endif
