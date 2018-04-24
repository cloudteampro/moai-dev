//
//  GS.h
//  GameSparks-IOS
//
//  Created by Gabriel Page on 28/05/2015.
//  Copyright (c) 2015 Gabriel Page. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "JFRWebSocket.h"
#import "GSAPI.h"
#import <SystemConfiguration/SCNetworkReachability.h>
#import <UIKit/UIKit.h>

@interface GS : NSObject<JFRWebSocketDelegate>

@property (strong, nonatomic) UIWindow *previewWindow;

+ (GS*) gs;
+ (void) setGs:(GS*)value;

//Creates an instance of GS targetting the gaame details provoded
- (instancetype)initWithApiKey:(NSString *)apiKey andApiSecret:(NSString *)apiSecret andCredential:(NSString *)credential andPreviewMode:(bool)previewMode;
//Connects the SDK
- (void) connect;
//Disconnects the SDK
- (void) disconnect;
//Resets the SDK (forgets auth tokens and previus userIds
- (void) reset;
//Sends (or queues a message to be sent the next time a connection is established)
- (void) send:(GSRequest*) request;
//Sets the GSMessageListener that listens for specific messages. This should really be set before connect
- (void) setMessageListener:(GSMessageListener*) messageListener;
//Sets  block that will be executed when the SDK is ready
- (void) setAvailabilityListener:(void (^)(BOOL)) availabilityListener;
//Sets  block that will be executed when the SDK is authenticated as a player
- (void) setAuthenticatedListener:(void (^)(NSString*)) authenticatedListener;
//Sets whether to output debug messages from the SDK with NSLog
- (void) setDebugLogCallback:(void (^)(NSString*)) debugListener;
//Returns whether the SDk is currently conneccted and authenticated
- (BOOL) isAuthenticated;
//Gets the current player id the SDK is bound to, this can return a value when the SDK is not connected.
- (NSString*) currentPlayerId;
//Returns the durable queue of the current player
- (NSArray*) getDurableQueue;
//Removes an item from the durable queue
- (void) removeFromDurableQueue:(GSRequest*) request;
//Gets hw&sw info of the current device
- (GSData *)getDeviceStats;

//WORK IN PROGRESS
+ (NSString *)obfuscate:(NSString *)string withKey:(NSString *)key;

@end
