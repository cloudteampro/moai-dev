//
//  GSData.h
//  GameSparks-IOS
//
//  Created by Gabriel Page on 29/05/2015.
//  Copyright (c) 2015 Gabriel Page. All rights reserved.
//

#ifndef GameSparks_IOS_GSData_h
#define GameSparks_IOS_GSData_h

#import <Foundation/Foundation.h>

@interface GSData : NSObject

@property(nonatomic, strong)NSDictionary *_data;

-(id) initWithData:(NSDictionary*) data;

-(id) getAttribute:(NSString *)attributeName;

//Used internally
-(NSDate*) getDateFromString:(NSString *) theString;

@end

@interface GSMessage : GSData
-(NSDictionary*) getScriptData;
@end

@interface GSResponse : GSMessage
-(NSDictionary*) getErrors;
@end


@interface GSRequest : NSObject

@property(copy)void(^_callback)(NSDictionary*);
@property(nonatomic, strong)NSMutableDictionary *_data;
@property(nonatomic)int timeout;
@property(nonatomic)BOOL _durable;

//Used internally
-(id)initWithType:(NSString*)type;
//Used internally
-(id)initWithData:(NSDictionary *)dataIn;
//Used internally
-(NSString*) getStringFromDate:(NSDate *) theDate;

//Sets a NSDictionary to be passed as scriptData
-(void)setScriptData:(NSDictionary*)scriptData;
//Configures how long the SDK should try to send this request for before giving up
-(void) setTimeout:(int)timeout;
-(void) setDurable:(BOOL)durable;
-(BOOL)isEqual:(id)other;
-(BOOL)hasCallback;
@end

#endif
