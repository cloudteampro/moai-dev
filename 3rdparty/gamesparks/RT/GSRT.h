//
//  GSRT.h
//
//  Copyright © 2017 Game Sparks Technologies LLC. All rights reserved.
//

#ifndef GSRT_h
#define GSRT_h

#import <Foundation/Foundation.h>

@class RTPacket;

/*!
 * Register an implementation of this interface via GameSparksRTSessionBuilder::SetListener() when building the session to listen
 * for session related events.
 */
@protocol IRTSessionListener
    /// <summary>
    /// Executed when another player joins the room.
    /// </summary>
    /// <param name="peerId">The player who has just joined</param>
    - (void)onPlayerConnect: (NSNumber * _Nonnull) peerId;

    /// <summary>
    /// Executed when another player leaves the room.
    /// </summary>
    /// <param name="peerId">The player who has just left</param>
    - (void)onPlayerDisconnect: (NSNumber * _Nonnull) peerId;

    /// <summary>
    /// Executed when the SDK moves between a ready and non ready state
    /// </summary>
    /// <param name="ready">Whether the SDK is in a ready state (or not)</param>
    - (void)onReady: (BOOL) ready;

    /// <summary>
    /// Executed when the SDK recieves a message from another player via SendPacket
    /// </summary>
    /// <param name="opCode">The opCode sent by the other player</param>
    /// <param name="sender">The peerId of the other player</param>
    /// <param name="stream">The stream of bytes sent by the other player</param>
    /// <param name="length">The number of bytes in the stream that can be read</param>
    - (void)onPacket: (RTPacket* _Nonnull) packet;
@end


typedef NS_ENUM(NSInteger, RTConnectState) {
    /// <summary>
    /// Disconnected.
    /// </summary>
    RTCS_Disconnected = 0,

    /// <summary>
    /// Connecting.
    /// </summary>
    RTCS_Connecting = 1,

    /// <summary>
    /// Only a TCP connection is established.
    /// </summary>
    RTCS_ReliableOnly = 2,

    /// <summary>
    /// We've successfully send some UDP and the server has recieved it, but have not recieved any
    /// </summary>
    RTCS_ReliableAndFastSend = 3,

    /// <summary>
    /// All systems go. We can send and recieve UCP.
    /// </summary>
    RTCS_ReliableAndFast = 4

    // maintenance note: needs to match c++
};

/// <summary>
/// Log level.
/// </summary>
typedef NS_ENUM(NSInteger, RTLogLevel) {
    /// <summary>
    /// Log at DEBUG
    /// </summary>
    RTLL_DEBUG=0,
    /// <summary>
    /// Log at INFO
    /// </summary>
    RTLL_INFO=1,
    /// <summary>
    /// Log at WARN
    /// </summary>
    RTLL_WARN=2,
    /// <summary>
    /// Log at ERROR
    /// </summary>
    RTLL_ERROR=3

    // maintenance note: needs to match c++
};


/// <summary>
/// How the message should be attempted to be sent.
/// If ConnectState==ReliableOnly the message will be sent as RELIABLE
/// </summary>
typedef NS_ENUM(NSInteger, RTDeliveryIntent) {
    /// <summary>
    /// Send over TCP
    /// </summary>
    RTDI_RELIABLE = 0,

    /// <summary>
    /// Send over UDP, don't discard out of sequence packets
    /// </summary>
    RTDI_UNRELIABLE = 1,

    /// <summary>
    /// Send over UDP, discard out of sequence packets
    /// </summary>
    RTDI_UNRELIABLE_SEQUENCED = 2

    // maintenance note: needs to match c++
};




/*!
 * Can be used to represent points and directions in one to four dimensional space.
 */
@interface RTVector : NSObject
    - (instancetype _Nonnull) initWithX:(NSNumber* _Nonnull)x;
    - (instancetype _Nonnull) initWithX:(NSNumber* _Nonnull)x andY:(NSNumber* _Nonnull)y;
    - (instancetype _Nonnull) initWithX:(NSNumber* _Nonnull)x andY:(NSNumber* _Nonnull)y andZ:(NSNumber* _Nonnull)z;
    - (instancetype _Nonnull) initWithX:(NSNumber* _Nonnull)x andY:(NSNumber* _Nonnull)y andZ:(NSNumber* _Nonnull)z andW:(NSNumber* _Nonnull)w;

    + (instancetype _Nonnull) vectorWithX:(NSNumber* _Nonnull)x;
    + (instancetype _Nonnull) vectorWithX:(NSNumber* _Nonnull)x andY:(NSNumber* _Nonnull)y;
    + (instancetype _Nonnull) vectorWithX:(NSNumber* _Nonnull)x andY:(NSNumber* _Nonnull)y andZ:(NSNumber* _Nonnull)z;
    + (instancetype _Nonnull) vectorWithX:(NSNumber* _Nonnull)x andY:(NSNumber* _Nonnull)y andZ:(NSNumber* _Nonnull)z andW:(NSNumber* _Nonnull)w;

    - (NSNumber* _Nullable) getX;
    - (NSNumber* _Nullable) getY;
    - (NSNumber* _Nullable) getZ;
    - (NSNumber* _Nullable) getW;

    - (void) setX:(NSNumber* _Nonnull)x;
    - (void) setY:(NSNumber* _Nonnull)y;
    - (void) setZ:(NSNumber* _Nonnull)z;
    - (void) setW:(NSNumber* _Nonnull)w;
@end


/*!
     * This is used to represent strucutred data to be send to the session peers via IRTSession::SendData().
     * Be aware, that RTData indices start at one - not at zero.
     */
@interface RTData : NSObject
    - (NSNumber* _Nullable) getInt     :(unsigned int) index;
    - (NSNumber* _Nullable) getLong    :(unsigned int) index;
    - (NSNumber* _Nullable) getFloat   :(unsigned int) index;
    - (NSNumber* _Nullable) getDouble  :(unsigned int) index;
    - (RTVector* _Nullable) getRTVector:(unsigned int) index;
    - (NSString* _Nullable) getString  :(unsigned int) index;
    - (RTData  * _Nullable) getData    :(unsigned int) index;

    - (instancetype _Nonnull) setInt     : (unsigned int) index value: (NSNumber* _Nonnull) value;
    - (instancetype _Nonnull) setLong    : (unsigned int) index value: (NSNumber* _Nonnull) value;
    - (instancetype _Nonnull) setFloat   : (unsigned int) index value: (NSNumber* _Nonnull) value;
    - (instancetype _Nonnull) setDouble  : (unsigned int) index value: (NSNumber* _Nonnull) value;
    - (instancetype _Nonnull) setRTVector: (unsigned int) index value: (RTVector* _Nonnull) value;
    - (instancetype _Nonnull) setString  : (unsigned int) index value: (NSString* _Nonnull) value;
    - (instancetype _Nonnull) setData    : (unsigned int) index value: (RTData  * _Nonnull) value;
@end



/*!
 * When you data arrives, an instance of this class is passed to your IRTSessionListener::OnPacket() method.
 */
@interface RTPacket : NSObject
    - (int) getOpCode; ///< the same value that was passed to send when sending the packet. OpCodes must be greater than zero.
    - (NSNumber* _Nonnull) getSender; ///< Who send this packet.
    - (int) getStreamLength;
    - (RTData * _Nullable) getData; ///< The RTData object that was send. might be empty if IRTSession::SendBytes() was used.
    - (NSData * _Nullable) getPayload; ///< Use this if you want to use your own data-serialization format.
@end

/*!
 * Sessions are created via a GameSparksRTSessionBuilder. IRTSession objects are used to send data
 * to the peers. Make sure to call Update() every frame. To listen for session related
 * events inherit from IRTSessionListener.
 */
@interface IRTSession : NSObject
    /// <summary>
    /// Starts the session and connects to the real time services.
    /// </summary>
    - (void)start;

    /// <summary>
    /// Starts the session and disconnects from the real time services.
    /// </summary>
    - (void)stop;

    /// <summary>
    /// This needs to be called when your SessionListener is deallocated. Only call this once for each SessionListener!
    /// </summary>
    - (void) clearListenerAdapter;

    /// <summary>
    /// The peerId of the current player.
    /// </summary>
    - (NSNumber* _Nullable) getPeerId;

    /// <summary>
    /// Indicates if the SDK is Ready and connected
    /// </summary>
    - (BOOL) getReady;

    /// <summary>
    /// The list of peers who are currently connected.
    /// </summary>
    - (NSArray* _Nullable) getActivePeers;

    /// <summary>
    /// The connection state of the session.
    /// </summary>
    - (RTConnectState)getConnectState;

    /// <summary>
    /// Sends a message to other players
    /// </summary>
    /// <param name="opCode">The opCode to send</param>
    /// <param name="deliveryIntent">How this message should be sent.</param>
    /// <param name="payload">Th byte array to send</param>
    /// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
    //virtual int SendData(int opCode, GameSparksRT::DeliveryIntent intent, const System::Bytes &payload,
    //        const RTData &data, const std::vector<int> &targetPlayers) = 0;


    /// <summary>
    /// Sends a strucured message to other players
    /// </summary>
    /// <param name="opCode">The opCode to send</param>
    /// <param name="deliveryIntent">How this message should be sent.</param>
    /// <param name="data">The RTData object to send</param>
    /// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
    //virtual int SendRTData(int opCode, GameSparksRT::DeliveryIntent deliveryIntent, const RTData &data,
    //        const std::vector<int> &targetPlayer) =0;
    - (int) send:(RTData* _Nonnull) data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent) deliveryIntent;
    - (int) send:(RTData* _Nonnull) data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent) deliveryIntent toPlayers:(NSArray* _Nonnull)players;

    /// <summary>
    /// Sends a byte[] to other players
    /// </summary>
    /// <param name="opCode">The opCode to send</param>
    /// <param name="deliveryIntent">How this message should be sent.</param>
    /// <param name="payload">bytes to send, as an ArraySegment<c> struct</c></param>
    /// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
    //virtual int SendBytes(int opCode, GameSparksRT::DeliveryIntent deliveryIntent,
    //        const System::ArraySegment<System::Byte> &payload,
    //        const std::vector<int> &targetPlayer) =0;
    - (int) sendBytes:(NSData* _Nonnull) data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent) deliveryIntent;
    - (int) sendBytes:(NSData* _Nonnull) data withOpcode:(int)opCode andDeliveryIntent:(RTDeliveryIntent) deliveryIntent toPlayers:(NSArray* _Nonnull)players;

    /// <summary>
    /// Sends both RTData and bytes to other players
    /// </summary>
    /// <param name="opCode">The opCode to send</param>
    /// <param name="deliveryIntent">How this message should be sent.</param>
    /// <param name="payload">bytes to send, as an ArraySegment<c> struct</c></param>
    /// <param name="targetPlayers">The list of players to send to (empty to send to all)</param>
    //virtual int SendRTDataAndBytes(int opCode, GameSparksRT::DeliveryIntent intent,
    //        const System::ArraySegment<System::Byte> &payload, const RTData &data,
    //        const std::vector<int> &targetPlayer) =0;
    - (int) send:(RTData* _Nonnull) data withOpcode:(int)opCode andBytes:(NSData* _Nonnull)bytes andDeliveryIntent:(RTDeliveryIntent) deliveryIntent;
    - (int) send:(RTData* _Nonnull) data withOpcode:(int)opCode andBytes:(NSData* _Nonnull)bytes andDeliveryIntent:(RTDeliveryIntent) deliveryIntent toPlayers:(NSArray* _Nonnull)players;

    /// <summary>
    /// This method should be called as frequently as possible by the thread you want
    /// Your callbacks to execute on. In unity, you should call this from an Update
    /// method in a MonoBehaviour
    /// </summary>
    - (void)update;

@end


/*!
 * Use this to build an RTSession with tokens obtained via an GameSparks::Api::Requests::MatchmakingRequest.
 * \include sample07Realtime.cpp
 */
@interface GameSparksRTSessionBuilder : NSObject
    /// Constructor
    - (instancetype _Nonnull) init;

    /// sets the connect token to use for the session. obtained via  MatchmakingRequest::GetAccessToken().GetValue().
    - (instancetype _Nonnull) setConnectToken:(NSString * _Nonnull)connectToken;

    /// sets the host to use for the session. obtained via  MatchmakingRequest::GetHost().GetValue().
    - (instancetype _Nonnull) setHost:(NSString* _Nonnull) host;

    /// sets the port to use for the session. obtained via  MatchmakingRequest::GetPort().GetValue().
    - (instancetype _Nonnull) setPort:(NSNumber* _Nonnull) port;

    /// sets the session listener to listen for session related events.
    - (instancetype _Nonnull) setListener:(id<IRTSessionListener> _Nonnull) listener;

    /// Build the IRTSession. caller owns the return value. make sure to put it into a std::unique_ptr or std::shared_ptr (or delete it manually).
    - (IRTSession*  _Nonnull) build;

@end


/*!
 * Used for settings related to the RT SDK.
 */
@interface GameSparksRT : NSObject
    +(void) setRootLogLevel:(RTLogLevel) level;
    +(void) setLogLevel:(NSString* _Nonnull) tag andLevel:(RTLogLevel) level;
    +(void) setLogger:(void (^ _Nonnull)(NSString* _Nonnull)) logger;
    +(void) setTCPConnectTimeout:(NSNumber* _Nonnull) seconds;
@end

#endif /* GSRT_h */
