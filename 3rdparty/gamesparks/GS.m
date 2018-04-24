//
//  GS.m
//  GameSparks-IOS
//
//  Created by Gabriel Page on 28/05/2015.
//  Copyright (c) 2015 Gabriel Page. All rights reserved.
//
#import "GS.h"
#import "PreviewViewController.h"
#import <SystemConfiguration/SCNetworkReachability.h>
#import <CommonCrypto/CommonHMAC.h>
#import <sys/utsname.h>
#import <sys/types.h>
#import <sys/sysctl.h>
#import <mach/mach.h>
#import <mach/mach_host.h>
#import <mach/machine.h>

@interface GS () <JFRWebSocketDelegate>

@property(nonatomic, strong)JFRWebSocket *_socket;

@property(nonatomic)BOOL _isReachable;
@property(nonatomic)BOOL _isActive;
@property(nonatomic)BOOL _isAuthenticated;
@property(nonatomic)BOOL _isReady;

@property(nonatomic)BOOL _preview;
@property(nonatomic, strong)NSString *_apiSecret;
@property(nonatomic, strong)NSURL *_url;

@property(nonatomic, strong)NSString *_authToken;
@property(nonatomic, strong)NSString *_userId;
@property(nonatomic, strong)NSString *_sessionId;
@property (atomic, strong, retain) NSMutableDictionary* _pendingRequests;
@property (atomic, strong, retain) NSMutableArray* _durableQueue;
@property (atomic, strong, retain) NSMutableDictionary* _queuedRequests;

#if OS_OBJECT_HAVE_OBJC_SUPPORT == 1
@property (nonatomic, strong) dispatch_queue_t _processingQueue;
#else
@property (nonatomic, assign) dispatch_queue_t _processingQueue;
#endif

@property(nonatomic, strong)GSMessageListener *_messageListener;
@property(copy)void(^_availabilityBlock)(BOOL);
@property(copy)void(^_authenticatedBlock)(NSString*);
@property(copy)void(^_debugBlock)(NSString*);
@property(copy)NSString*(^_deviceIdSupplier)(void);

@end

@implementation GS

dispatch_source_t _timer;

static GS* _gs;

+ (GS*) gs {
    return _gs;
}

+ (void) setGs:(GS*)gs {
    _gs = gs;
}

- (BOOL) isAuthenticated{
    return self._isAuthenticated && self._isReady;
}
- (NSString*) currentPlayerId{
    return self._userId;
}

- (id)initWithApiKey:(NSString *)apiKey andApiSecret:(NSString *)apiSecret andCredential:(NSString *)credential andPreviewMode:(bool)previewMode
{
    NSRange index;
    NSString *url;
    NSMutableString *urlAddition = [NSMutableString stringWithString:apiKey];
    
    self = [super init];
    self._apiSecret = apiSecret;
    self._preview = previewMode;
    self._processingQueue = dispatch_queue_create("com.gamesparks.processingQueue", NULL);
    self._authToken = [[NSUserDefaults standardUserDefaults] stringForKey:@"authToken"];
    self._userId = [[NSUserDefaults standardUserDefaults] stringForKey:@"userId"];
    self._durableQueue = [self loadDurableQueue:self._userId];
    
    if (credential == nil || [credential length] == 0)
    {
        credential = @"device";
    }
    
    index = [apiSecret rangeOfString:@":"];
    if (index.location != NSNotFound)
    {
        credential = @"secure";
        
        urlAddition = [NSMutableString stringWithString:[@"/" stringByAppendingString:urlAddition]];
        urlAddition = [NSMutableString stringWithString:[[apiSecret substringToIndex:index.location] stringByAppendingString:urlAddition]];
    }
    
    if (previewMode)
    {
        url = [NSString stringWithFormat:@"wss://preview-%@.ws.gamesparks.net/ws/%@/%@?deviceOS=IOS&deviceID=%@&SDK=iOS", urlAddition, credential, urlAddition, [self getDeviceId]];
    }
    else
    {
        url = [NSString stringWithFormat:@"wss://live-%@.ws.gamesparks.net/ws/%@/%@?deviceOS=IOS&deviceID=%@&SDK=iOS", urlAddition, credential, urlAddition, [self getDeviceId]];
    }
    
    self._url = [NSURL URLWithString:url];
    
    self._pendingRequests = [[NSMutableDictionary alloc] init];
    self._queuedRequests = [[NSMutableDictionary alloc] init];
    
    [self checkReachability];
    
    if (previewMode)
    {
        self.previewWindow = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        self.previewWindow.backgroundColor = [UIColor clearColor];
        self.previewWindow.windowLevel = UIWindowLevelAlert;
        self.previewWindow.userInteractionEnabled = NO;
        self.previewWindow.rootViewController = [[PreviewViewController alloc] initWithNibName:nil bundle:nil];
        self.previewWindow.hidden = NO;
        self.previewWindow.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    }
    
    return self;
}

- (void)startTimer
{
    if (!_timer) {
        _timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, self._processingQueue);
        if (_timer)
        {
            dispatch_source_set_timer(_timer, dispatch_time(DISPATCH_TIME_NOW, 60.000f * NSEC_PER_SEC), 60.000f * NSEC_PER_SEC, (1ull * NSEC_PER_SEC) / 10);
            dispatch_source_set_event_handler(_timer, ^{
                if([self._socket isConnected]){
                    [self GSLog:@"keepalive"];
                    [self._socket writeString:@" "];
                }
            });
            dispatch_resume(_timer);
        }
    }
}

- (void)cancelTimer
{
    if (_timer) {
        dispatch_source_cancel(_timer);
        _timer = nil;
    }
}

- (void) setMessageListener:(GSMessageListener*) messageListener{
    self._messageListener = messageListener;
}

- (void) setAvailabilityListener:(void (^)(BOOL)) availabilityListener{
    self._availabilityBlock = availabilityListener;
}

- (void) setAuthenticatedListener:(void (^)(NSString*)) authenticatedListener{
    self._authenticatedBlock = authenticatedListener;
}
- (void) setDebugLogCallback:(void (^)(NSString*)) debugListener{
    self._debugBlock = debugListener;
    
}

- (NSArray*) getDurableQueue{
    return self._durableQueue.copy;
}

- (void) removeFromDurableQueue:(GSRequest*) request{
    @synchronized (self){
        if([self._durableQueue containsObject:request]){
            [self._durableQueue removeObject:request];
            [self saveDurableQueue];
        }
    }
}

- (GSData *)getDeviceStats {
    NSMutableDictionary *data = [[NSMutableDictionary alloc] init];
    struct utsname systemInfo;
    mach_port_t host_port = mach_host_self();
    mach_msg_type_number_t host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    vm_size_t pagesize;
    vm_statistics_data_t vm_stat;
    NSMutableString *cpu = [[NSMutableString alloc] init];
    size_t size;
    cpu_type_t type;
    cpu_subtype_t subtype;
    
    uname(&systemInfo);
    
    host_page_size(host_port, &pagesize);
    
    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS) {
        NSLog(@"Failed to fetch vm statistics");
    }
    
    natural_t mem_used = (vm_stat.active_count +
                          vm_stat.inactive_count +
                          vm_stat.wire_count) * pagesize;
    natural_t mem_free = vm_stat.free_count * pagesize;
    natural_t mem_total = (mem_used + mem_free) / 1024 / 1024;
    
    size = sizeof(type);
    sysctlbyname("hw.cputype", &type, &size, NULL, 0);
    
    size = sizeof(subtype);
    sysctlbyname("hw.cpusubtype", &subtype, &size, NULL, 0);
    
    if (type == CPU_TYPE_X86) {
        [cpu appendString:@"x86"];
        
    } if (type == CPU_TYPE_X86_64) {
        [cpu appendString:@"x86_64"];
    } else if (type == CPU_TYPE_ARM) {
        [cpu appendString:@"arm"];
        
        switch (subtype) {
            case CPU_SUBTYPE_ARM_V4T:
                [cpu appendString:@"v4t"];
                
                break;
                
            case CPU_SUBTYPE_ARM_V6:
                [cpu appendString:@"v6"];
                
                break;
                
            case CPU_SUBTYPE_ARM_V5TEJ:
                [cpu appendString:@"v5tej"];
                
                break;
                
            case CPU_SUBTYPE_ARM_XSCALE:
                [cpu appendString:@"xscale"];
                
                break;
                
            case CPU_SUBTYPE_ARM_V7:
                [cpu appendString:@"v7"];
                
                break;
            
            case CPU_SUBTYPE_ARM_V7F:
                [cpu appendString:@"v7f"];
                
                break;
                
            case CPU_SUBTYPE_ARM_V7S:
                [cpu appendString:@"v7s"];
                
                break;
                
            case CPU_SUBTYPE_ARM_V7K:
                [cpu appendString:@"v7k"];
                
                break;
                
            case CPU_SUBTYPE_ARM_V6M:
                [cpu appendString:@"v6m"];
                
                break;
            
            case CPU_SUBTYPE_ARM_V7M:
                [cpu appendString:@"v7m"];
                
                break;
                
            case CPU_SUBTYPE_ARM_V7EM:
                [cpu appendString:@"v7em"];
                
                break;
            
            case CPU_SUBTYPE_ARM_V8:
                [cpu appendString:@"v8"];
                
                break;
        }
    } else if (type == CPU_TYPE_ARM64) {
        [cpu appendString:@"arm64"];
        
        if (subtype == CPU_SUBTYPE_ARM64_V8) {
            [cpu appendString:@"v8"];
        }
    }
    
    [data setValue:@"Apple" forKey:@"manufacturer"];
    [data setValue:[NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding] forKey:@"model"];
    [data setValue:[NSString stringWithFormat:@"%d MB", mem_total] forKey:@"memory"];
    [data setValue:@"iPhone" forKey:@"os.name"];
    [data setValue:[[UIDevice currentDevice] systemVersion] forKey:@"os.version"];
    [data setValue:[NSString stringWithFormat:@"%lu", (unsigned long)[[NSProcessInfo processInfo] processorCount]] forKey:@"cpu.cores"];
    [data setValue:cpu forKey:@"cpu.vendor"];
    [data setValue:[NSString stringWithFormat:@"%dx%d", (int)floorf([UIScreen mainScreen].nativeBounds.size.width), (int)floorf([UIScreen mainScreen].nativeBounds.size.height)] forKey:@"resolution"];
    [data setValue:@"0.5.0" forKey:@"gssdk"];

    return [[GSData alloc] initWithData:[NSDictionary dictionaryWithDictionary:data]];
}

- (void) connect{
    //We've been asked to connect
    self._isActive = true;
    [self startTimer];
    [self connectInternal:YES];
}

- (void) connectInternal:(BOOL) force{
    if(force || self._isReachable){
        if(!self._socket){
            self._socket = [[JFRWebSocket alloc] initWithURL:self._url protocols:NULL];
            self._socket.delegate = self;
            self._socket.queue = self._processingQueue;
            self._isReady = false;
            [self._socket connect];
        }
    }
}

- (void) disconnect{
    //We've been asked to disconnect
    self._isActive = false;
    [self cancelTimer];
    if (self._socket)
    {
        [self._socket disconnect];
        self._socket = nil;
    }
}

- (void) reset{
    self._authToken = @"0";
    self._userId = nil;
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"authToken"];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"userId"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    self._sessionId = nil;
    if(self._socket){
        [self._socket disconnect];
        //self._socket = nil;
    }
}

// pragma mark: WebSocket Delegate methods.

-(void)websocketDidConnect:(JFRWebSocket*)socket {
    [self GSLog:@"websocket is connected"];
}

-(void)websocketDidDisconnect:(JFRWebSocket*)socket error:(NSError*)error {

    //This method can be called multiple times for a single close event.
    //Make sure we only deal with one by nilling the socket once we've
    //determined it's the active one.
    
    if(self._socket == socket){
        [self GSLog:@"websocket is disconnected"];
        //This is the current socket, nil it, then deal with the close.
        self._socket = nil;
        self._isAuthenticated = false;
        self._isReady = false;
        //We're active (connect has been called).
        if(self._isActive){
            
            if(self._availabilityBlock)
            {
                dispatch_async(dispatch_get_main_queue(), ^{
                    @synchronized(self){
                        self._availabilityBlock(false);
                    }
                });
            }
        
            //If it was a clean close, just reconnect straight away
            if(!error)
            {
                [self connectInternal:NO];
            } else {
                //It's a dirty close, so try to reconnect in a second.
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 1 * NSEC_PER_SEC), self._processingQueue, ^{
                        [self connectInternal:NO];
                });
            }
        }
    }
}

-(void)websocket:(JFRWebSocket*)socket didReceiveMessage:(NSString*)string {

    [self GSLog:[NSString stringWithFormat: @"Received \"%@\"", string]];

    NSError* error;
    NSDictionary *jsonDictionary = [NSJSONSerialization JSONObjectWithData:[string dataUsingEncoding:NSUTF8StringEncoding] options:0 error:&error];
    
    NSString *recievedType = [jsonDictionary objectForKey:@"@class"];
    
    NSString *recievedAuthToken = [jsonDictionary objectForKey:@"authToken"];
    
    if (recievedAuthToken && ![recievedAuthToken isEqualToString:@"0" ]){
        self._authToken = recievedAuthToken;
        [[NSUserDefaults standardUserDefaults] setObject:self._authToken forKey:@"authToken"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
    
    @synchronized(self){
    
        if([recievedType isEqualToString:@".AuthenticatedConnectResponse"]){
            [self processAuthenticatedConnectResponse:jsonDictionary withSocket:socket];
        } else if ([recievedType hasSuffix:@"Response"]){
            [self processResponse:jsonDictionary responseType:recievedType];
        } else if ([recievedType hasSuffix:@"Message"]){
            if(self._messageListener){
                dispatch_async(dispatch_get_main_queue(), ^{
                    [self._messageListener processMessage:jsonDictionary withType:recievedType];
                });
            }
        }
    }
    
}

-(void)processResponse:(NSDictionary *)data responseType:(NSString*)responseType;
{
    NSString* requestId = [data objectForKey:@"requestId"];
    if(requestId){
        GSRequest* request = [self._pendingRequests objectForKey:requestId];
        
        if(request){
            [self._pendingRequests removeObjectForKey:requestId];
        }
        
        if([self._durableQueue containsObject:request]){
            //We've got a durable response, remove it from the durable queue.
            [self._durableQueue removeObject:request ];
            [self saveDurableQueue];
        }
        
        if([responseType isEqualToString:@".AuthenticationResponse"]){
            NSString* userId = [data objectForKey:@"userId"];
            if(userId){
                [self setUserId:userId];
            }
        }
        
        if(request && request._callback){
            [self._pendingRequests removeObjectForKey:requestId];
            dispatch_async(dispatch_get_main_queue(), ^{
                [self GSLog:[NSString stringWithFormat: @"Executing callback for RequestId %@", requestId]];
                request._callback(data);
            });
        }
    }
}

-(void)processAuthenticatedConnectResponse:(NSDictionary *) data withSocket:(JFRWebSocket*)socket
{

    NSString * connectUrl = [data objectForKey:@"connectUrl"];
    
    if(connectUrl != (id)[NSNull null] && connectUrl.length > 0){
        self._url = [NSURL URLWithString:connectUrl];
        //We are going to intentionally disconnect and reconnect here.
        //null the socket so the availabilityHandlers to not fire
        self._socket = nil;
        [socket disconnect];
        [self connect];
    } else {
        NSString * nonce = [data objectForKey:@"nonce"];
        if(nonce != (id)[NSNull null] && nonce.length > 0){
            
            NSString * nonce = [data objectForKey:@"nonce"];
            
            const char *cKey = [self._apiSecret cStringUsingEncoding:NSASCIIStringEncoding];
            const char *cData = [nonce cStringUsingEncoding:NSASCIIStringEncoding];

            unsigned char cHMAC[CC_SHA256_DIGEST_LENGTH];
            CCHmac(kCCHmacAlgSHA256, cKey, strlen(cKey), cData, strlen(cData), cHMAC);
            NSData *hash = [[NSData alloc] initWithBytes:cHMAC length:sizeof(cHMAC)];
            NSString* base64Hash = [hash base64EncodedStringWithOptions:0];
            
            NSMutableDictionary *request = [[NSMutableDictionary alloc]init];
            [request setObject:@".AuthenticatedConnectRequest" forKey:@"@class"];
            [request setObject:base64Hash forKey:@"hmac"];
            [request setObject:@"IOS" forKey:@"os"];
            [request setObject:[self getDeviceId] forKey:@"deviceId"];
            [request setObject:@"iOS" forKey:@"platform"];
            if(self._sessionId){
                [request setObject:self._sessionId forKey:@"sessionId"];
            }
            if(self._authToken){
                [request setObject:self._authToken forKey:@"authToken"];
            }
            
            [self sendInternal:request];
            
        } else {
            if([data objectForKey:@"sessionId"]!= (id)[NSNull null]){
                self._sessionId = [data objectForKey:@"sessionId"];
                self._isReady = true;

                if(self._availabilityBlock)
                {
                    dispatch_async(dispatch_get_main_queue(), ^{
                        @synchronized(self){
                            self._availabilityBlock(true);
                        }
                    });
                }

                NSString* userId = [data objectForKey:@"userId"];
                if(userId){
                    [self setUserId:userId];
                } else {
                    [self sendDurableQueue];
                }

                [self._queuedRequests enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
                    [self send:obj];
                }];
                
            }
        }
    }
}

- (void) sendDurableQueue {
    if(self._isReady){
        [self._durableQueue enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            [self send:obj];
        }];
    };
}

- (void) setUserId:(NSString*) userId {
    
    self._isAuthenticated = true;
    
    //Only load the durable queue if the userId has changed
    if (![userId isEqualToString:self._userId]){
        self._durableQueue = [self loadDurableQueue:userId];
        self._userId = userId;
        [[NSUserDefaults standardUserDefaults] setObject:self._userId forKey:@"userId"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
    
    if(userId && self._authenticatedBlock){
        dispatch_async(dispatch_get_main_queue(), ^{
            @synchronized(self){
                self._authenticatedBlock(userId);
            }
            [self sendDurableQueue];
        });
    } else {
        [self sendDurableQueue];
    }
    
}

- (void) send:(GSRequest *)request{
    
    @synchronized(self){

        NSString* requestId = [request._data objectForKey:@"requestId"];
        
        if(!requestId){
            if(request._durable){
                requestId = [NSString stringWithFormat:@"d_%f", [[NSDate date] timeIntervalSince1970]];
            } else {
                requestId = [NSString stringWithFormat:@"%f", [[NSDate date] timeIntervalSince1970]];
            }
            [request._data setObject:requestId forKey:@"requestId"];
            if(request._durable){
                [self._durableQueue addObject:request];
                [self saveDurableQueue];
            }
        }

        if([self._socket isConnected] && self._isReady){
            [self._queuedRequests removeObjectForKey:requestId];
            [self._pendingRequests setObject:request forKey:requestId];
            [self sendInternal:request._data ];
        } else {
            if(!request._durable){
                [self._queuedRequests setObject:request forKey:requestId];
            }
        }

        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, request.timeout * NSEC_PER_SEC), self._processingQueue, ^{
            [self cancelRequest:requestId];
        });
    }
    
}

- (void) sendInternal:(NSMutableDictionary*)request
{
    NSError* error;
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:request options:0 error:&error];
    NSString* msg = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    [self GSLog:[NSString stringWithFormat: @"Send \"%@\"", msg]];
    [self._socket writeString:msg];
}

- (void) cancelRequest:(NSString *)requestId{
    
    @synchronized(self){

        GSRequest* request = [self._pendingRequests objectForKey:requestId];
        
        if(!request){
            request = [self._queuedRequests objectForKey:requestId];
        }
        
        if(request){
            if([self._durableQueue containsObject:request]){
                //It's a durable request, retry sending it
                if(self._isReady){
                    [self send:request];
                }
            } else {
                [self._pendingRequests removeObjectForKey:requestId];
                [self._queuedRequests removeObjectForKey:requestId];
                if(request._callback){
                    NSMutableDictionary* timeoutResponse = [[NSMutableDictionary alloc] init ];
                    NSMutableDictionary* errorResponse = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"timeout", @"error", nil ];
                    [timeoutResponse setObject:errorResponse forKey:@"error"];
                    [timeoutResponse setObject:requestId forKey:@"requestId"];
                    dispatch_async(dispatch_get_main_queue(), ^{
                        request._callback(timeoutResponse);
                    });
                }
                [self GSLog:@"Request timeout"];
            }
        }
    }
}

-(void)websocket:(JFRWebSocket*)socket didReceiveData:(NSData*)data {
    [self GSLog:@"Received data:"];
}
// pragma end: WebSocket Delegate methods.

- (NSURL*)applicationDataDirectory {
    NSFileManager* sharedFM = [NSFileManager defaultManager];
    NSArray* possibleURLs = [sharedFM URLsForDirectory:NSApplicationSupportDirectory inDomains:NSUserDomainMask];
    NSURL* appSupportDir = nil;
    NSURL* appDirectory = nil;
    
    if ([possibleURLs count] >= 1) {
        // Use the first directory (if multiple are returned)
        appSupportDir = [possibleURLs objectAtIndex:0];
    }
    
    // If a valid app support directory exists, add the
    // app's bundle ID to it to specify the final directory.
    if (appSupportDir) {
        NSString* appBundleID = [[NSBundle mainBundle] bundleIdentifier];
        appDirectory = [appSupportDir URLByAppendingPathComponent:appBundleID];
    }
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:[[appDirectory absoluteString] stringByRemovingPercentEncoding] isDirectory:NULL]) {
        NSError *error = nil;
        //Create one
        if (![[NSFileManager defaultManager] createDirectoryAtURL:appDirectory withIntermediateDirectories:YES attributes:nil error:&error]) {
#if defined(DEBUG)
            NSLog(@"%@", error.localizedDescription);
#endif
        }
        else {
            // *** OPTIONAL *** Mark the directory as excluded from iCloud backups
            if (![appDirectory setResourceValue:@YES forKey:NSURLIsExcludedFromBackupKey error:&error]) {
#if defined(DEBUG)
                NSLog(@"Error excluding %@ from backup %@", appDirectory.lastPathComponent, error.localizedDescription);
#endif
            }
        }
    }
    
    return appDirectory;
}

- (void) saveDurableQueue {

    @synchronized(self){
    
        NSError* error;
        
        NSURL* path = [[self applicationDataDirectory] URLByAppendingPathComponent:@"gs_"];
        if(self._userId){
            path = [[self applicationDataDirectory] URLByAppendingPathComponent:[NSString stringWithFormat:@"gs_%@", self._userId]];
        } else {
            path = [[self applicationDataDirectory] URLByAppendingPathComponent:[NSString stringWithFormat:@"gs_nouserid"]];
        }
        
        NSMutableArray* contents = [[NSMutableArray alloc] init];
        
        for (id object in self._durableQueue) {
            if ([object isKindOfClass:[GSRequest class]])
            {
                GSRequest* request = object;
                if([request._data objectForKey:@"requestId"] != nil)
                    [contents addObject:request._data];
            }
        }

        NSData* jsonData = [NSJSONSerialization dataWithJSONObject:contents options:0 error:&error];
        NSString* content = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        content = [GS obfuscate:content withKey:self._apiSecret];
        [content writeToURL:path atomically:true encoding:NSUTF8StringEncoding error:&error];
    }
}

- (NSMutableArray *) loadDurableQueue:(NSString *) playerId {

#if defined(DEBUG)
    NSLog(@"Loading durable queue for player %@", playerId);
#endif
    NSURL* path = [[self applicationDataDirectory] URLByAppendingPathComponent:@"gs_"];
    if(self._userId){
        path = [[self applicationDataDirectory] URLByAppendingPathComponent:[NSString stringWithFormat:@"gs_%@", playerId]];
    } else {
        path = [[self applicationDataDirectory] URLByAppendingPathComponent:[NSString stringWithFormat:@"gs_nouserid"]];
    }

    NSMutableArray* newArray = [[NSMutableArray alloc] init];
    
    NSString* content = [NSString stringWithContentsOfURL:path encoding:NSUTF8StringEncoding error:nil];
    
    if(content != nil){
        content = [GS obfuscate:content withKey:self._apiSecret];
        NSArray* savedData = [NSJSONSerialization JSONObjectWithData:[content dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];

        if(savedData){
            for (id object in savedData) {
                GSRequest* request = [GSRequestBuilder buildRequest:object];
                [request setDurable:true];
                [newArray addObject:request];
            }
        }
    }
    return newArray;
}

+ (NSString *)obfuscate:(NSString *)string withKey:(NSString *)key
{
    NSData *data = [string dataUsingEncoding:NSUTF8StringEncoding];
    char *dataPtr = (char *) [data bytes];
    char *keyData = (char *) [[key dataUsingEncoding:NSUTF8StringEncoding] bytes];
    char *keyPtr = keyData;
    int keyIndex = 0;

    for (int x = 0; x < [data length]; x++){
        *dataPtr = *dataPtr ^ *keyPtr;
        dataPtr++;
        keyPtr++;
        
        if (++keyIndex == [key length])
            keyIndex = 0, keyPtr = keyData;
    }
    
    NSString* ret = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    return ret;
}

// Get the device id on iOS6.0 and previous versions
- (NSString *) getDeviceId {
    UIDevice *device = [UIDevice currentDevice];
    return [[device identifierForVendor] UUIDString];
}

-(void) GSLog:(NSString* )msg{
    if(self._debugBlock){
        dispatch_async(dispatch_get_main_queue(), ^{
            self._debugBlock(msg);
        });
    } else {
#if defined(DEBUG)
        NSLog(@"GS:%f - %@", [[NSDate date] timeIntervalSince1970], msg);
#endif
    }
}

static void networkReachabilityCallback(SCNetworkReachabilityRef target,
                                        SCNetworkConnectionFlags flags,
                                        void* object) {
    // Observed flags:
    // - nearly gone: kSCNetworkFlagsReachable alone (ignored)
    // - gone: kSCNetworkFlagsTransientConnection | kSCNetworkFlagsReachable | kSCNetworkFlagsConnectionRequired
    // - connected: kSCNetworkFlagsIsDirect | kSCNetworkFlagsReachable
    NSObject* obj = (__bridge NSObject*) object;
    
    if(![obj isKindOfClass: [GS class]]){
        return;
    };
    
    GS* gs = (__bridge GS *)object;

    if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0)
    {
        gs._isReachable = YES;
        if(gs._isActive){
            [gs connectInternal:NO];
        }
        return;
    }
    
    if ((((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) ||
         (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0))
    {
        if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0)
        {
            gs._isReachable = YES;
            if(gs._isActive){
                [gs connectInternal:NO];
            }
            return;
        }
    }
    
    if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN)
    {
        gs._isReachable = YES;
        if(gs._isActive){
            [gs connectInternal:NO];
        }
        return;
    }
    
    gs._isReachable = NO;

}

- (void) checkReachability {
    
    //    SCNetworkReachabilityContext context = {0, (__bridge void *)(self), NULL, NULL, NULL};
    SCNetworkReachabilityRef networkReachability = SCNetworkReachabilityCreateWithName(NULL, [@"google.com" UTF8String]);
    
    // If reachability information is available now, we don't get a callback later
    SCNetworkConnectionFlags flags;
    
    if (SCNetworkReachabilityGetFlags(networkReachability, &flags))
        networkReachabilityCallback(networkReachability, flags, (void*)CFBridgingRetain(self));
    
    SCNetworkReachabilityContext context = {0, (__bridge void *)(self), NULL, NULL, NULL};
    
    if (!SCNetworkReachabilitySetCallback(networkReachability, networkReachabilityCallback, &context))
        goto fail;
    
    if (!SCNetworkReachabilityScheduleWithRunLoop(networkReachability, [[NSRunLoop currentRunLoop] getCFRunLoop], kCFRunLoopCommonModes))
        goto fail;
    return;
    
fail:
    if (networkReachability != NULL)
        CFRelease(networkReachability);
    
    networkReachability = NULL; //-- ivar representing current reachability
    
}

@end
