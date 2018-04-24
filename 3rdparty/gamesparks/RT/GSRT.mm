//
//  GSRT.m
//  GameSparksSample
//
//  Created by Benjamin Schulz on 19/01/17.
//  Copyright © 2017 GameSparks. All rights reserved.
//

#import <sstream>
#import "GSRT.h"

#if 0
#include "../../../../base/include/GameSparksRT/GameSparksRT.hpp"
#include "../../../../base/include/GameSparksRT/IRTSessionListener.hpp"
#include "../../../../base/include/GameSparksRT/IRTSession.hpp"
#include "../../../../base/include/GameSparksRT/RTData.hpp"
#else
#include "./BaseSDK/include/GameSparksRT/GameSparksRT.hpp"
#include "./BaseSDK/include/GameSparksRT/IRTSessionListener.hpp"
#include "./BaseSDK/include/GameSparksRT/IRTSession.hpp"
#include "./BaseSDK/include/GameSparksRT/RTData.hpp"
#endif


@interface RTData ()
@property(nonatomic, readonly) GameSparks::RT::RTData *pimpl;
- (instancetype)init:(GameSparks::RT::RTData *)pimpl;
@end



/*
 *                  RTPacket
 * */
@interface RTPacket ()
@property(nonatomic, readonly) const GameSparks::RT::RTPacket* pimpl;
- (instancetype)init:(const GameSparks::RT::RTPacket&) pimpl;
@end


@implementation RTPacket
- (instancetype)init:(const GameSparks::RT::RTPacket&) thePimpl {
    self = [super init];

    if (self != nil) {
        _pimpl = &thePimpl;
    }

    return self;
}

- (void)dealloc {
    // not owning !
    //delete _pimpl;
}

- (int)getOpCode {
    return self.pimpl->OpCode;
}

- (NSNumber* _Nonnull)getSender {
    return [NSNumber numberWithInt:self.pimpl->Sender];
}

- (int)getStreamLength {
    return self.pimpl->StreamLength;
}

- (RTData *_Nullable)getData {
    return [[RTData alloc] init:new GameSparks::RT::RTData(self.pimpl->Data)];
}

- (NSData *_Nullable)getPayload {
    return [NSData dataWithBytes:self.pimpl->Payload.data() length:self.pimpl->Payload.size()];
}

- (NSString *)description {
    std::stringstream ss;
    ss << *self.pimpl;
    return [NSString stringWithUTF8String:ss.str().c_str()];
}
@end


/*
 *                  IRTSessionListenerAdapter
 * */
class IRTSessionListenerAdapter : public GameSparks::RT::IRTSessionListener {
public:
    IRTSessionListenerAdapter(id <IRTSessionListener> objCListener)
            : objCListener(objCListener) {
    }

    void OnPlayerConnect(int i) override {
        // if it crashes here, make sure that you've called [IRTSession clearSessionListenerAdapter] once your SessionListener got deallocated
        [objCListener onPlayerConnect:[NSNumber numberWithInt:i]];
    }

    void OnPlayerDisconnect(int i) override {
        // if it crashes here, make sure that you've called [IRTSession clearSessionListenerAdapter] once your SessionListener got deallocated
        [objCListener onPlayerDisconnect:[NSNumber numberWithInt:i]];
    }

    void OnReady(bool b) override {
        // if it crashes here, make sure that you've called [IRTSession clearSessionListenerAdapter] once your SessionListener got deallocated
        [objCListener onReady:b];
    }

    void OnPacket(const GameSparks::RT::RTPacket &packet) override {
        // if it crashes here, make sure that you've called [IRTSession clearSessionListenerAdapter] once your SessionListener got deallocated
        [objCListener onPacket:[[RTPacket alloc] init:packet]];
    }

private:
    id <IRTSessionListener> objCListener;
};



GameSparks::RT::GameSparksRT::DeliveryIntent convertEnum(RTDeliveryIntent e)
{
    switch(e)
    {
        case RTDI_RELIABLE: return GameSparks::RT::GameSparksRT::DeliveryIntent::RELIABLE;
        case RTDI_UNRELIABLE: return GameSparks::RT::GameSparksRT::DeliveryIntent::UNRELIABLE;
        case RTDI_UNRELIABLE_SEQUENCED: return GameSparks::RT::GameSparksRT::DeliveryIntent::UNRELIABLE_SEQUENCED;
        default: assert(false && "Unhandled RTDeliveryIntent. Are enums out of sync?");
    }
    return GameSparks::RT::GameSparksRT::DeliveryIntent::RELIABLE;
}

GameSparks::RT::GameSparksRT::LogLevel convertEnum(RTLogLevel level)
{
    GameSparks::RT::GameSparksRT::LogLevel lvl = GameSparks::RT::GameSparksRT::LogLevel::LL_DEBUG;
    switch(level)
    {
        case RTLL_DEBUG: lvl = GameSparks::RT::GameSparksRT::LogLevel::LL_DEBUG; break;
        case RTLL_INFO : lvl = GameSparks::RT::GameSparksRT::LogLevel::LL_INFO ; break;
        case RTLL_WARN : lvl = GameSparks::RT::GameSparksRT::LogLevel::LL_WARN ; break;
        case RTLL_ERROR: lvl = GameSparks::RT::GameSparksRT::LogLevel::LL_ERROR; break;
        default: assert(false && "Unhandled RTLogLevel. Are enums out of sync?");
    }
    return lvl;
}

std::vector<int> convertPlayerArray(NSArray* players)
{
    std::vector<int> ret;
    for (NSNumber* playerId in players) {
        ret.push_back([playerId intValue]);
    }
    return ret;
}


std::vector<System::Byte> convertNSData(NSData* data)
{
    System::Byte* begin = (System::Byte*)[data bytes];
    System::Byte* end_ = begin + [data length];
    std::vector<System::Byte> ret(begin, end_);
    return ret;
}


@interface IRTSession ()
@property(nonatomic, readonly) GameSparks::RT::IRTSession *pimpl;
@property(nonatomic) IRTSessionListenerAdapter *rawSessionListenerAdapter;
- (instancetype)init:(GameSparks::RT::IRTSession *)pimpl;
@end


/*
 *                           RTVector
 * */

@interface RTVector ()
@property(nonatomic, readonly) GameSparks::RT::RTVector *pimpl;
- (instancetype)initWithVector:(GameSparks::RT::RTVector *)v;
+ (instancetype)vectorWithVector:(GameSparks::RT::RTVector *)v;
@end


@implementation RTVector


- (instancetype)initWithVector:(GameSparks::RT::RTVector *)v {
    self = [super init];

    if (self != nil) {
        _pimpl = v;
    }

    return self;
}

+ (instancetype)vectorWithVector:(GameSparks::RT::RTVector *)v {
    return [[RTVector alloc] initWithVector:v];
}

- (instancetype)initWithX:(NSNumber *)x {
    self = [super init];

    if (self != nil) {
        _pimpl = new GameSparks::RT::RTVector([x floatValue]);
    }

    return self;
}

- (instancetype)initWithX:(NSNumber *)x andY:(NSNumber *)y {
    self = [super init];

    if (self != nil) {
        _pimpl = new GameSparks::RT::RTVector([x floatValue], [y floatValue]);
    }

    return self;
}

- (instancetype)initWithX:(NSNumber *)x andY:(NSNumber *)y andZ:(NSNumber *)z {
    self = [super init];

    if (self != nil) {
        _pimpl = new GameSparks::RT::RTVector([x floatValue], [y floatValue], [z floatValue]);
    }

    return self;
}

- (instancetype)initWithX:(NSNumber *)x andY:(NSNumber *)y andZ:(NSNumber *)z andW:(NSNumber *)w {
    self = [super init];

    if (self != nil) {
        _pimpl = new GameSparks::RT::RTVector([x floatValue], [y floatValue], [z floatValue], [w floatValue]);
    }

    return self;
}

- (void)dealloc {
    delete _pimpl;
}

+ (instancetype)vectorWithX:(NSNumber *)x {
    return [[RTVector alloc] initWithX:x];
}

+ (instancetype)vectorWithX:(NSNumber *)x andY:(NSNumber *)y {
    return [[RTVector alloc] initWithX:x andY:y];
}

+ (instancetype)vectorWithX:(NSNumber *)x andY:(NSNumber *)y andZ:(NSNumber *)z {
    return [[RTVector alloc] initWithX:x andY:y andZ:z];
}

+ (instancetype)vectorWithX:(NSNumber *)x andY:(NSNumber *)y andZ:(NSNumber *)z andW:(NSNumber *)w {
    return [[RTVector alloc] initWithX:x andY:y andZ:z andW:w];
}

- (NSNumber *)getX {
    return self.pimpl->x.HasValue()?[NSNumber numberWithFloat:self.pimpl->x.Value()]:nil;
}

- (NSNumber *)getY {
    return self.pimpl->y.HasValue()?[NSNumber numberWithFloat:self.pimpl->y.Value()]:nil;
}

- (NSNumber *)getZ {
    return self.pimpl->z.HasValue()?[NSNumber numberWithFloat:self.pimpl->z.Value()]:nil;
}

- (NSNumber *)getW {
    return self.pimpl->w.HasValue()?[NSNumber numberWithFloat:self.pimpl->w.Value()]:nil;
}

- (void)setX:(NSNumber *)x {
    self.pimpl->x = [x floatValue];
}

- (void)setY:(NSNumber *)y {
    self.pimpl->y = [y floatValue];
}

- (void)setZ:(NSNumber *)z {
    self.pimpl->z = [z floatValue];
}

- (void)setW:(NSNumber *)w {
    self.pimpl->w = [w floatValue];
}

- (NSString *)description {
    std::stringstream ss;
    ss << *self.pimpl;
    return [NSString stringWithUTF8String:ss.str().c_str()];
}
@end


/*
 *                           RTData
 * */

@implementation RTData

- (instancetype)init {
    self = [super init];

    if (self != nil) {
        _pimpl = new GameSparks::RT::RTData();
    }

    return self;
}

- (instancetype)init:(GameSparks::RT::RTData *)thePimpl {
    self = [super init];

    if (self != nil) {
        _pimpl = thePimpl;
    }

    return self;
}

- (void)dealloc {
    delete _pimpl;
}

- (NSNumber *_Nullable)getInt:(unsigned int)index {
    return self.pimpl->GetInt(index).HasValue()?[NSNumber numberWithInt:self.pimpl->GetInt(index).Value()]:nil;
}

- (NSNumber *_Nullable)getLong:(unsigned int)index {
    return self.pimpl->GetLong(index).HasValue()? [NSNumber numberWithLongLong: self.pimpl->GetLong(index).Value()]:nil;
}

- (NSNumber *_Nullable)getFloat:(unsigned int)index {
    return self.pimpl->GetFloat(index).HasValue()? [NSNumber numberWithFloat:self.pimpl->GetFloat(index).Value()]:nil;
}

- (NSNumber *_Nullable)getDouble:(unsigned int)index {
    return self.pimpl->GetDouble(index).HasValue()? [NSNumber numberWithDouble:self.pimpl->GetDouble(index).Value()]:nil;
}

- (RTVector *_Nullable)getRTVector:(unsigned int)index {
    return self.pimpl->GetRTVector(index).HasValue()? [RTVector vectorWithVector:new GameSparks::RT::RTVector(self.pimpl->GetRTVector(index).Value())]:nil;
}

- (NSString *_Nullable)getString:(unsigned int)index {
    return self.pimpl->GetString(index).HasValue()? [NSString stringWithUTF8String:self.pimpl->GetString(index).Value().c_str()]:nil;
}

- (RTData *_Nullable)getData:(unsigned int)index {
    return nil;
}

- (instancetype)setInt:(unsigned int)index value:(NSNumber *_Nonnull)value {
    self.pimpl->SetInt(index, [value intValue]);
    return self;
}

- (instancetype)setLong:(unsigned int)index value:(NSNumber *_Nonnull)value {
    self.pimpl->SetLong(index, [value longValue]);
    return self;
}

- (instancetype)setFloat:(unsigned int)index value:(NSNumber *_Nonnull)value {
    self.pimpl->SetFloat(index, [value floatValue]);
    return self;
}

- (instancetype)setDouble:(unsigned int)index value:(NSNumber *_Nonnull)value {
    self.pimpl->SetDouble(index, [value doubleValue]);
    return self;
}

- (instancetype)setRTVector:(unsigned int)index value:(RTVector *_Nonnull)value {
    self.pimpl->SetRTVector(index, *[value pimpl]);
    return self;
}

- (instancetype)setString:(unsigned int)index value:(NSString *_Nonnull)value {
    self.pimpl->SetString(index, [value UTF8String]);
    return self;
}

- (instancetype)setData:(unsigned int)index value:(RTData *_Nonnull)value {
    self.pimpl->SetData(index, *[value pimpl]);
    return self;
}

- (NSString *)description {
    std::stringstream ss;
    ss << *self.pimpl;
    return [NSString stringWithUTF8String:ss.str().c_str()];
}
@end


/*
 *                           GameSparksRTSessionBuilder
 * */

@interface GameSparksRTSessionBuilder ()
@property(nonatomic, readonly) GameSparks::RT::GameSparksRTSessionBuilder *pimpl;
@property(nonatomic, readonly) IRTSessionListenerAdapter *rawSessionListenerAdapter;
@end


@implementation GameSparksRTSessionBuilder

- (instancetype)init {
    self = [super init];

    if (self != nil) {
        _pimpl = new GameSparks::RT::GameSparksRTSessionBuilder();
    }

    return self;
}

- (void)dealloc {
    delete _pimpl;
}

- (instancetype)setConnectToken:(NSString *)connectToken {
    self.pimpl->SetConnectToken(connectToken.UTF8String);
    return self;
}

- (instancetype)setHost:(NSString *)host {
    self.pimpl->SetHost(host.UTF8String);
    return self;
}

- (instancetype)setPort:(NSNumber *)port {
    self.pimpl->SetPort(port.intValue);
    return self;
}

- (instancetype)setListener:(id <IRTSessionListener>)listener {
    // TODO: is there a better way to go about this ?
    _rawSessionListenerAdapter = new IRTSessionListenerAdapter(listener);
    self.pimpl->SetListener(self.rawSessionListenerAdapter);
    return self;
}

- (IRTSession *)build {
    auto session = [[IRTSession alloc] init:self.pimpl->Build()];
    session.rawSessionListenerAdapter = self.rawSessionListenerAdapter;
    return session;
}

@end


/*
 *                           IRTSession
 * */

@implementation IRTSession

- (instancetype)init:(GameSparks::RT::IRTSession *)thePimpl {
    self = [super init];

    if (self != nil) {
        _pimpl = thePimpl;
    }

    return self;
}

- (void)dealloc {
    delete _pimpl;
}

- (void)start {
    self.pimpl->Start();
}

- (void)stop {
    self.pimpl->Stop();
}

- (NSNumber *)getPeerId {
    if (self.pimpl->PeerId.HasValue()) {
        return [NSNumber numberWithInt:self.pimpl->PeerId.Value()];
    } else {
        return nil;
    }
}

- (BOOL)getReady {
    return self.pimpl->Ready;
}

- (NSArray *)getActivePeers {
    NSMutableArray *ret = [NSMutableArray arrayWithCapacity:self.pimpl->ActivePeers.size()];

    for (const auto &x : self.pimpl->ActivePeers) {
        [ret addObject:[NSNumber numberWithInt:x]];
    }

    return ret;
}

- (RTConnectState)getConnectState {
    switch (self.pimpl->GetConnectState()) {
        case GameSparks::RT::GameSparksRT::ConnectState::Disconnected       :
            return RTCS_Disconnected;
        case GameSparks::RT::GameSparksRT::ConnectState::Connecting         :
            return RTCS_Connecting;
        case GameSparks::RT::GameSparksRT::ConnectState::ReliableOnly       :
            return RTCS_ReliableOnly;
        case GameSparks::RT::GameSparksRT::ConnectState::ReliableAndFastSend:
            return RTCS_ReliableAndFastSend;
        case GameSparks::RT::GameSparksRT::ConnectState::ReliableAndFast    :
            return RTCS_ReliableAndFast;
        default:
            assert(false && "Unhandled ConnectState. Are enums out of sync?");
            return RTCS_Disconnected;
    }
}

- (void)update {
    self.pimpl->Update();
}

- (void) clearListenerAdapter{
    delete self.rawSessionListenerAdapter;
    self.rawSessionListenerAdapter = nil;
}

- (int)send:(RTData *_Nonnull)data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent)deliveryIntent {
    return self.pimpl->SendRTData(opCode, convertEnum(deliveryIntent), *[data pimpl], {});
}

- (int)send:(RTData *_Nonnull)data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent)deliveryIntent toPlayers:(NSArray *_Nonnull)players {
    return self.pimpl->SendRTData(opCode, convertEnum(deliveryIntent), *[data pimpl], convertPlayerArray(players));
}

- (int)sendBytes:(NSData *_Nonnull)data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent)deliveryIntent {
    return self.pimpl->SendBytes(opCode, convertEnum(deliveryIntent), convertNSData(data), {});
}

- (int)sendBytes:(NSData *_Nonnull)data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent)deliveryIntent toPlayers:(NSArray *_Nonnull)players {
    return self.pimpl->SendBytes(opCode, convertEnum(deliveryIntent), convertNSData(data), convertPlayerArray(players));
}

- (int)send:(RTData *_Nonnull)data withOpcode:(int)opCode andBytes:(NSData *_Nonnull)bytes andDeliveryIntent:(RTDeliveryIntent)deliveryIntent {
    return self.pimpl->SendRTDataAndBytes(opCode, convertEnum(deliveryIntent), convertNSData(bytes), *[data pimpl], {});
}

- (int)send:(RTData *_Nonnull)data withOpcode:(int)opCode andBytes:(NSData *_Nonnull)bytes andDeliveryIntent:(RTDeliveryIntent)deliveryIntent toPlayers:(NSArray *_Nonnull)players {
    return self.pimpl->SendRTDataAndBytes(opCode, convertEnum(deliveryIntent), convertNSData(bytes), *[data pimpl], convertPlayerArray(players));
}


@end

@implementation GameSparksRT

+ (void)setRootLogLevel:(RTLogLevel)level {
    GameSparks::RT::GameSparksRT::SetRootLogLevel(convertEnum(level));
}

+ (void)setLogLevel:(NSString *_Nonnull)tag andLevel:(RTLogLevel)level {
    GameSparks::RT::GameSparksRT::SetLogLevel([tag UTF8String], convertEnum(level));
}

+ (void)setLogger:(void (^ _Nonnull)(NSString *_Nonnull))logger {
    auto loggerHolder = logger;
    GameSparks::RT::GameSparksRT::Logger = [loggerHolder](const std::string& message)
    {
        loggerHolder([NSString stringWithUTF8String:message.c_str()]);
    };
}

+ (void)setTCPConnectTimeout:(NSNumber *_Nonnull)seconds {
    GameSparks::RT::GameSparksRT::TCP_CONNECT_TIMEOUT_SECONDS = [seconds intValue];
}

@end
