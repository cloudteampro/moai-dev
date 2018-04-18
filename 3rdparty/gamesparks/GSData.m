//
//  GSData.m
//  GameSparks-IOS
//
//  Created by Gabriel Page on 29/05/2015.
//  Copyright (c) 2015 Gabriel Page. All rights reserved.
//

#import "GSData.h"

@implementation GSData

@synthesize _data;

-(id)initWithData:(NSDictionary *)dataIn{
    self = [super init];
    self._data= dataIn;
    return self;
}

-(id) getAttribute:(NSString *)attributeName {
    return [self._data objectForKey:attributeName];
}

-(NSDate*) getDateFromString:(NSString *) theString{
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyy-MM-dd'T'HH:mm'Z'"];
    [formatter setTimeZone:[NSTimeZone timeZoneWithName:@"UTC"]];
    NSLocale *posix = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"];
    [formatter setLocale:posix];
    return [formatter dateFromString:theString];
}

@end



@implementation GSMessage

-(NSDictionary*) getScriptData{
    return [self._data objectForKey:@"scriptData"];
}

@end



@implementation GSResponse

-(NSDictionary*) getErrors{
    return [self._data objectForKey:@"error"];
}

@end


#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wincomplete-implementation"
@implementation GSRequest

-(id)initWithType:(NSString*)type{
    self._data = [[NSMutableDictionary alloc]init];
    [self._data setObject:type forKey:@"@class"];
    self.timeout = 5;
    return self;
}

-(id)initWithData:(NSDictionary *)dataIn{
    self = [super init];
    self._data= [[NSMutableDictionary alloc] initWithDictionary:dataIn];
    return self;
}

-(void)setScriptData:(NSDictionary*)scriptData{
    [self._data setValue:scriptData forKey:@"scriptData"];
}

-(void)setDurable:(BOOL)durable{
    self._durable = durable;
}

- (BOOL)isEqual:(id)other {
    if (other == self)
        return YES;
    if (!other || ![other isKindOfClass:[self class]])
        return NO;
    if ([self._data objectForKey:@"requestId"] != [((GSRequest*)other)._data objectForKey:@"requestId"])
        return NO;
    return YES;
}

-(NSString*) getStringFromDate:(NSDate *) theDate{
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    NSLocale *enUSPOSIXLocale = [NSLocale localeWithLocaleIdentifier:@"en_US_POSIX"];
    [dateFormatter setLocale:enUSPOSIXLocale];
    [dateFormatter setTimeZone:[NSTimeZone timeZoneWithName:@"UTC"]];
    [dateFormatter setDateFormat:@"yyyy-MM-dd'T'HH:mm'Z'"];
    return [dateFormatter stringFromDate:theDate];
}

@end
#pragma clang diagnostic pop
