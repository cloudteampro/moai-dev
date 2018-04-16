//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios/headers.h>
#import <moai-ios-facebook/MOAIFacebookIOS.h>

// This is for gameRequest callback support
#import <objc/runtime.h>

// Key for objc_setAssociatedObject
static const char kGameRequestCallbackRef = 0;


//================================================================//
// MOAIFacebookLuaCallbackRef
//================================================================//
//
// This class is for use with async objective-C block callbacks.
// It should be retained by block and will ensure that Lua callback ref
// will have the same lifetime as enclosing obj-C block.
//
@interface MOAIFacebookLuaCallbackRef : NSObject {
@protected
	int mRef;
}

//----------------------------------------------------------------//
-( id )	initWithRef :( int )ref;
-( int ) ref;

@end


//================================================================//
// MOAIFBSDKDelegate
//================================================================//
@interface MOAIFBSDKDelegate : NSObject < FBSDKGameRequestDialogDelegate > {
@private
}

//----------------------------------------------------------------//
- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didCompleteWithResults:( NSDictionary* ) results;
- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didFailWithError:( NSError* ) error;
- ( void ) gameRequestDialogDidCancel:( FBSDKGameRequestDialog* ) gameRequestDialog;

//----------------------------------------------------------------//
- ( void ) onProfileChanged:( NSNotification* ) notification;

@end




//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/** @lua	createTestUser
	@text	Create test user for given facebook app
	
	@in		string	appId
	@in		string	appToken
	@opt	boolean	installed	install app for created user
	@opt	boolean	login		login as test user
	@opt	string	name		leave blank to generate random name
*/
int MOAIFacebookIOS::_createTestUser ( lua_State *L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	cc8* appId		= state.GetValue < cc8* >( 1, 0 );
	cc8* token		= state.GetValue < cc8* >( 2, 0 );
	bool installed	= state.GetValue < bool >( 3, true );
	bool login		= state.GetValue < bool >( 4, true );
	cc8* name		= state.GetValue < cc8* >( 5, 0 );
	
	if ( !appId || !token ) {
		return 0;
	}
	
	NSMutableDictionary *params = [[ NSMutableDictionary alloc ] init ];
	[ params setObject: ( installed ? @"true" : @"false" ) forKey:@"installed" ];
	
	if ( installed ) {
		[ params setObject:@"public_profile,user_friends" forKey:@"permissions" ];
	}
	
	if ( name ) {
		[ params setObject:[ NSString stringWithUTF8String:name ] forKey:@"name" ];
	}
	
	NSString* appIdStr = [ NSString stringWithUTF8String:appId ];
	NSString* graphPath = [ NSString stringWithFormat:@"/%@/accounts/test-users", appIdStr ];
	
	FBSDKGraphRequest *request = [[ FBSDKGraphRequest alloc ]
		initWithGraphPath: graphPath
		parameters: params
		tokenString: [ NSString stringWithUTF8String:token ]
		version: nil
		HTTPMethod: @"POST"
	];
	
	[ request startWithCompletionHandler:^( FBSDKGraphRequestConnection *connection, id result, NSError *error ) {
		
		if ( !error ) {
			
			NSString* tokenString = [ result objectForKey:@"access_token" ];
			
			if ( login && tokenString ) {
				
				FBSDKAccessToken* accessToken = [[ FBSDKAccessToken alloc ]
					initWithTokenString: tokenString
					permissions: @[ @"public_profile", @"user_friends" ]
					declinedPermissions:nil
					appID:appIdStr
					userID:[ result objectForKey:@"id" ]
					expirationDate:nil
					refreshDate:nil
				];
				
				[ FBSDKAccessToken setCurrentAccessToken:accessToken ];
			}
		}
	}];
	
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3rdparty doxygen
int	MOAIFacebookIOS::_declinedPermissions ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	if ( ![ FBSDKAccessToken currentAccessToken ]) {
		return 0;
	}
	
	NSArray* permissions = [[[ FBSDKAccessToken currentAccessToken ] declinedPermissions ] allObjects ];
	[ permissions toLua: L ];
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	getExpirationDate
	@text	Retrieve the Facebook login token expiration date.
 
	@in		nil
	@out	string	token expiration date
*/
int MOAIFacebookIOS::_getExpirationDate ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	NSDateFormatter *formatter = [[ NSDateFormatter alloc ] init ];
	[ formatter setDateFormat:@"dd-MM-yyyy HH:mm:ss" ];
	
	NSString* dateString = [ formatter stringFromDate:[[ FBSDKAccessToken currentAccessToken ] expirationDate ]];
	lua_pushstring ( L, [ dateString UTF8String ]);
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	getToken
	@text	Retrieve the Facebook login token.
	
	@in		nil
	@out	string	token
*/
int MOAIFacebookIOS::_getToken ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	NSString* token = [[ FBSDKAccessToken currentAccessToken ] tokenString ];
	
	if ( token ) {
		lua_pushstring ( L, [ token UTF8String ]);
	} else {
		lua_pushnil ( L );
	}
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	getProfile
	@text	Retrieve the current public profile info
	
	@in		nil
	@out	table	Table with user info. Keys
*/
int MOAIFacebookIOS::_getProfile ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	self->PushProfile ( state, [ FBSDKProfile currentProfile ]);
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	graphRequest
	@text	Make a request on Facebook's Graph API
	
	@in 	string 		method, "GET" or "POST"
	@in		string		path
	@opt	table		parameters
	@opt	function 	callback
	@out	nil
*/
int MOAIFacebookIOS::_graphRequest ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	cc8* method = state.GetValue < cc8* >( 1, "GET" );
	cc8* path   = state.GetValue < cc8* >( 2, "" );
	
	NSMutableDictionary* paramsDict = [[[ NSMutableDictionary alloc ] init ] autorelease ];
	if ( state.IsTableOrUserdata ( 3 )) {
		[ paramsDict initWithLua:state stackIndex:3 ];
	}
	
	int ref = LUA_NOREF;
	if ( state.IsType ( 4, LUA_TFUNCTION )) {
		ref = self->mRefs.Ref ( state, 4 );
	}
	MOAIFacebookLuaCallbackRef* callback = [[[ MOAIFacebookLuaCallbackRef alloc ] initWithRef:ref ] autorelease ];
	
	NSString* nsMethod 	= [[[ NSString alloc ] initWithUTF8String:method ] autorelease ];
	NSString* nsPath 	= [[[ NSString alloc ] initWithUTF8String:path ] autorelease ];
	
	FBSDKGraphRequest *request = [[[ FBSDKGraphRequest alloc] initWithGraphPath:nsPath parameters:paramsDict HTTPMethod:nsMethod ] autorelease ];
	[ request startWithCompletionHandler:^( FBSDKGraphRequestConnection *connection, id result, NSError *error ) {
		
		UNUSED ( connection );
		
		if ( error ) {
			MOAIFacebookIOS::Get ().GraphRequestResponseFailure ( error, [ callback ref ]);
		}
		else {
			MOAIFacebookIOS::Get ().GraphRequestResponse ( result, [ callback ref ]);
		}
	}];
	
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3rdparty doxygen
int MOAIFacebookIOS::_hasGranted ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )

	cc8* permission = state.GetValue < cc8* >( 1, 0 );
	
	if ( permission ) {
		
		bool result = [[ FBSDKAccessToken currentAccessToken ] hasGranted:[ NSString stringWithUTF8String:permission ]];
		state.Push ( result );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Facebook.

	@in		string		loginAppId			Available in Facebook developer settings.
	@out 	nil
*/
int MOAIFacebookIOS::_init ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	[ FBSDKSettings setAppID:[ NSString stringWithUTF8String:state.GetValue < cc8* >( 1, "" )]];	
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3rdparty doxygen
int MOAIFacebookIOS::_logEvent ( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	NSString* 	eventName 	= [[ NSString alloc ] initWithLua: state stackIndex: 1 ];
	double 		valueToSum 	= state.GetValue < double >( 2, 0.0 );
	
	NSMutableDictionary* paramsDict = [[ NSMutableDictionary alloc ] init ];
	if ( state.IsType( 3, LUA_TTABLE )) {
		[ paramsDict initWithLua:state stackIndex:3 ];
	}
	
	if ( !eventName ) {
		return 0;
	}
	
	[ FBSDKAppEvents logEvent:eventName valueToSum:valueToSum parameters:paramsDict ];
	[ paramsDict release ];
	[ eventName release ];
	
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3rdparty doxygen
int MOAIFacebookIOS::_logPurchase ( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	double amount = state.GetValue < double >( 1, 0.0f );
	cc8* currency = state.GetValue < cc8* >( 2, "USD" );
	
	NSMutableDictionary* params = [[ NSMutableDictionary alloc ] init ];
	if ( state.IsType( 3, LUA_TTABLE )) {
		[ params initWithLua:state stackIndex:3 ];
	}
	
	[ FBSDKAppEvents logPurchase:amount currency:[ NSString stringWithUTF8String:currency ] parameters:params ];
	[ params release ];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	login
	@text	Prompt the user to login to Facebook.
	
	@opt	table	permissions		Optional set of read permissions. See Facebook documentation for a full list. Default is nil.
	@opt	number	loginBehavior	See Facebook documentation. Default is LOGIN_NATIVE
	@out 	nil
*/
int MOAIFacebookIOS::_login ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	FBSDKLoginBehavior loginBehavior = state.GetValue < u32 >( 2, FBSDKLoginBehaviorNative );
	
	NSMutableDictionary* paramsDict = [[ NSMutableDictionary alloc ] init ];
	if ( state.IsType ( 1, LUA_TTABLE )) {
		[ paramsDict initWithLua:state stackIndex:1 ];
	}
	NSArray* paramsArray = [ paramsDict allValues ];
	
	FBSDKLoginManager* login = [[ FBSDKLoginManager alloc] init ];
	login.loginBehavior = loginBehavior;
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	
	[ login logInWithReadPermissions:paramsArray fromViewController:rootVC handler:^( FBSDKLoginManagerLoginResult *result, NSError *error ) {
	
		if ( error ) {
			// clear old token and profile. In case user have switched profiles
			[ login logOut ];
			self->SessionDidNotLogin ();
		}
		else if ( result.isCancelled ) {
		
			self->SessionDidNotLogin ();
		}
		else {
		
			self->SessionDidLogin ();
		
			// If you ask for multiple permissions at once, you
			// should check if specific permissions missing
			//if ([ result.grantedPermissions containsObject:@"email" ]) {
			//	// Do work
			//}
		}
	}];
	
	[ login release ];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	logout
	 @text	Log the user out of Facebook.
	 
	 @in	nil
	 @out 	nil
 */
int MOAIFacebookIOS::_logout ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	[ FBSDKAccessToken setCurrentAccessToken:nil ];
	[ FBSDKProfile setCurrentProfile:nil ];
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3rdparty doxygen
int MOAIFacebookIOS::_sendAppInvite ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )

	FBSDKAppInviteContent *content =[[FBSDKAppInviteContent alloc] init];

	if ( state.IsType ( 1, LUA_TTABLE )) {
		cc8* linkUrl			= state.GetField < cc8* >( 1, "linkUrl", "" );
		cc8* previewImageUrl	= state.GetField < cc8* >( 1, "previewImageUrl", "" );

		content.appLinkURL = [ NSURL URLWithString:[ NSString stringWithUTF8String:linkUrl ]];
	    content.appInvitePreviewImageURL = [ NSURL URLWithString:[ NSString stringWithUTF8String:previewImageUrl ]];
	}

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
        
    // present the dialog.
    [FBSDKAppInviteDialog showFromViewController:rootVC withContent:content delegate:nil];

    [content release];
	
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3rdparty doxygen
int MOAIFacebookIOS::_postToFeed ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
//	FBSDKShareLinkContent *content = [[FBSDKShareLinkContent alloc] init];
//	content.contentURL = [NSURL URLWithString:@"https://developers.facebook.com"];
//	
//	content.contentURL				= [ NSURL URLWithString:[ NSString stringWithUTF8String:state.GetValue < cc8* >( 1, "" )]];
//	content.imageURL				= [ NSURL URLWithString:[ NSString stringWithUTF8String:state.GetValue < cc8* >( 2, "" )]];
//	content.contentTitle			= [ NSString stringWithUTF8String:state.GetValue < cc8* >( 3, "" )];
//	content.contentDescription		= [ NSString stringWithUTF8String:state.GetValue < cc8* >( 4, "" )];
//
//	[ FBDialogs presentShareDialogWithParams:shareParams
//		clientState:nil
//		handler:^( FBAppCall* call, NSDictionary *results, NSError *error ) {
//			UNUSED ( call );
//			
//			if ( error ) {
//				MOAIFacebookIOS::Get ().DialogDidNotComplete ();
//			}
//			else if ( results [ @"completionGesture" ] && [ results [ @"completionGesture" ] isEqualToString:@"cancel" ]) {
//				MOAIFacebookIOS::Get ().DialogDidNotComplete ();
//			}
//			else {
//				MOAIFacebookIOS::Get ().DialogDidNotComplete ();
//			}
//	}];
	
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFacebookIOS::_requestPublishPermissions( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	if ( ![ FBSDKAccessToken currentAccessToken ]) {
		MOAILogF ( state, ZLLog::LOG_WARNING, "MOAIFacebookIOS: session is not initialized\n" );
		return 0;
	}
	
	NSMutableDictionary* permissions = nil;
	
	if ( state.IsType ( 1, LUA_TTABLE )) {
		
		permissions = [[[ NSMutableDictionary alloc ] init ] autorelease ];
		[ permissions initWithLua:state stackIndex:1 ];
	}
	
	if ( permissions ) {
		NSArray* granted = [[[ FBSDKAccessToken currentAccessToken ] permissions ] allObjects ];
		NSMutableArray* requested = [ NSMutableArray arrayWithArray:[ permissions allValues ]];
		[ requested removeObjectsInArray:granted];
		
		if ([ requested count ] > 0 ) {
			UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
			UIViewController* rootVC = [ window rootViewController ];
			
			FBSDKLoginManager* login = [[ FBSDKLoginManager alloc] init ];
			[ login logInWithPublishPermissions:requested fromViewController:rootVC handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
				
				if ( !error && [[ result declinedPermissions ] count ] == 0 ) {
					MOAIFacebookIOS::Get ().PermissionsGranted ();
				}
				else {
					MOAIFacebookIOS::Get ().PermissionsDenied ([ error localizedDescription ]);
				}
			}];
			[ login release ];
		}
	}
	
	return 0;
}


//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFacebookIOS::_requestReadPermissions( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	if ( ![ FBSDKAccessToken currentAccessToken ]) {
		MOAILogF ( state, ZLLog::LOG_WARNING, "MOAIFacebookIOS: session is not initialized\n" );
		return 0;
	}

	NSMutableDictionary* permissions = nil;
	
	if ( state.IsType( 1, LUA_TTABLE )) {
		
		permissions = [[[ NSMutableDictionary alloc ] init ] autorelease ];
		[ permissions initWithLua:state stackIndex:1 ];
	}
	
	if ( permissions ) {
		NSArray* granted = [[[ FBSDKAccessToken currentAccessToken ] permissions ] allObjects ];
		NSMutableArray* requested = [ NSMutableArray arrayWithArray:[ permissions allValues ]];
		[ requested removeObjectsInArray:granted];
		
		if ([ requested count ] > 0 ) {
			UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
			UIViewController* rootVC = [ window rootViewController ];
			
			FBSDKLoginManager* login = [[ FBSDKLoginManager alloc] init ];
			[ login logInWithReadPermissions:requested fromViewController:rootVC handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
				
				if ( !error && [[ result declinedPermissions ] count ] == 0 ) {
					MOAIFacebookIOS::Get ().PermissionsGranted ();
				}
				else {
					MOAIFacebookIOS::Get ().PermissionsDenied ([ error localizedDescription ]);
				}
			}];
			[ login release ];
		}
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	sendGameRequest
	@text	Show game requests dialog.

	@in		string		message			The message for the request.
	@opt	table		parameters
	@opt	function	callback		Signature function(boolean success, table results or error)
										If not present, then REQUEST_DIALOG events are dispatched
	
	TODO: howto describe table fields in doc?
		actionType				number	None, Send, Ask, Turn
		data 					string 	255 characters limit
		filters 				number	None, AppUsers, AppNonUsers
		objectID 				string 	Opengraph objectId
		recipients 				table 	Array of userIDs
		recipientSuggestions 	table 	Array of userIDs
		title 					string 	Title for the dialog
		frictionless 			boolean	Enable frictionless requests

	@out 	nil
*/
int MOAIFacebookIOS::_sendGameRequest ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "S" )
	
	NSString* message = [ NSString stringWithUTF8String:state.GetValue < cc8* >( 1, "" )];

	FBSDKGameRequestContent* content = [[ FBSDKGameRequestContent alloc ] init ];
	content.message = message;

	BOOL frictionless = NO;
	if ( state.IsType ( 2, LUA_TTABLE )) {
		
		frictionless		= ( BOOL ) state.GetValue < bool >( 2, "frictionless" );
		
		cc8* data			= state.GetField < cc8* >( 2, "data", "" );
		cc8* title			= state.GetField < cc8* >( 2, "title", "" );
		cc8* objectID		= state.GetField < cc8* >( 2, "objectID", "" );
		
		content.actionType	= ( FBSDKGameRequestActionType )state.GetField < u32 >( 2, "actionType",	FBSDKGameRequestActionTypeNone );
		content.filters		= ( FBSDKGameRequestFilter )	state.GetField < u32 >( 2, "filters",		FBSDKGameRequestFilterNone );
		
		content.data		= [ NSString stringWithUTF8String:data ];
		content.title		= [ NSString stringWithUTF8String:title ];
		content.objectID	= [ NSString stringWithUTF8String:objectID ];
		
		if ( state.GetFieldWithType ( 2, "recipients", LUA_TTABLE )) {
			// TODO:	implement NSMutableArray+MOAILib initWithLua:
			//			I recall my failed attempt
			NSMutableDictionary* recipients = [[ NSMutableDictionary alloc ] init ];
			[ recipients initWithLua:state stackIndex:-1 ];
			content.recipients = [ recipients allValues ];
			state.Pop ( 1 );
			[ recipients release ];
		}
		
		if ( state.GetFieldWithType ( 2, "recipientSuggestions", LUA_TTABLE )) {
			NSMutableDictionary* recipients = [[ NSMutableDictionary alloc ] init ];
			[ recipients initWithLua:state stackIndex:-1 ];
			content.recipientSuggestions = [ recipients allValues ];
			state.Pop ( 1 );
			[ recipients release ];
		}
	}
	
	int ref = LUA_NOREF;
	if ( state.IsType ( 3, LUA_TFUNCTION )) {
		ref = self->mRefs.Ref ( state, 3 );
	}
	MOAIFacebookLuaCallbackRef* callbackRef = [[[ MOAIFacebookLuaCallbackRef alloc ] initWithRef:ref ] autorelease ];
	
	FBSDKGameRequestDialog* dialog = [[[ FBSDKGameRequestDialog alloc ] init ] autorelease ];
	[ dialog setDelegate: self->mDelegate ];
	[ dialog setContent: content ];
	[ dialog setFrictionlessRequestsEnabled: frictionless ];
	
	[ content release ];
	
	// Remember reference to lua callback ref.
	// It will be released automatically in dialog destructor.
	objc_setAssociatedObject ( dialog, kGameRequestCallbackRef, callbackRef, OBJC_ASSOCIATION_RETAIN_NONATOMIC );
	
	NSError* error = nil;
	if ([ dialog validateWithError:&error ]) {
		state.Push (( bool )[ dialog show ]);
		return 1;
	}
	else {
		state.Push ( false );
		OBJC_TO_LUA ( error, state );
		return 2;
	}
}

//----------------------------------------------------------------//
/**	@lua	sessionValid
	@text	Determine whether or not the current Facebook session is valid.
 
	@in		nil
	@out 	boolean	valid
*/
int MOAIFacebookIOS::_sessionValid ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	lua_pushboolean ( state, [ FBSDKAccessToken currentAccessToken ] != nil );
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	setProfileAutoUpdate
	@text	FB SDK will issue graph request for public profile data when
			access token changes and dispatch PROFILE_UPDATED with new profile.
 
	@in		boolean		enabled		default if false
	@out 	nil
*/
int MOAIFacebookIOS::_setProfileAutoUpdate ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	BOOL enable = state.GetValue < bool >( 1, false );
	[ FBSDKProfile enableUpdatesOnAccessTokenChange: enable ];
	return 0;
}
	
//================================================================//
// MOAIFacebookIOS
//================================================================//

//----------------------------------------------------------------//
MOAIFacebookIOS::MOAIFacebookIOS () {
	
	RTTI_SINGLE ( MOAIGlobalEventSource )

	mRefs.InitStrong ();
	mDelegate = [[ MOAIFBSDKDelegate alloc ] init ];
	
	[[ NSNotificationCenter defaultCenter ] addObserver:mDelegate
											   selector:@selector ( onProfileChanged: )
												   name:FBSDKProfileDidChangeNotification
												 object:nil ];
}

//----------------------------------------------------------------//
MOAIFacebookIOS::~MOAIFacebookIOS () {
	
	if ( MOAILuaRuntime::IsValid ()) {
		mRefs.Clear ();
	}
	
	[[ NSNotificationCenter defaultCenter ] removeObserver:mDelegate ];
	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	// Events
	state.SetField ( -1, "PERMISSIONS_DENIED",			( u32 )PERMISSIONS_DENIED );
	state.SetField ( -1, "PERMISSIONS_GRANTED",			( u32 )PERMISSIONS_GRANTED );
	state.SetField ( -1, "PROFILE_UPDATED",				( u32 )PROFILE_UPDATED );
	state.SetField ( -1, "REQUEST_RESPONSE", 			( u32 )REQUEST_RESPONSE );
	state.SetField ( -1, "REQUEST_DIALOG_RESPONSE",		( u32 )REQUEST_DIALOG_RESPONSE );
	state.SetField ( -1, "SESSION_DID_LOGIN", 			( u32 )SESSION_DID_LOGIN );
	state.SetField ( -1, "SESSION_DID_NOT_LOGIN", 		( u32 )SESSION_DID_NOT_LOGIN );
	state.SetField ( -1, "SESSION_EXTENDED",			( u32 )SESSION_EXTENDED );
	
	// Login behaviors
	state.SetField ( -1, "LOGIN_NATIVE",				( u32 )FBSDKLoginBehaviorNative );
	state.SetField ( -1, "LOGIN_BROWSER",				( u32 )FBSDKLoginBehaviorBrowser );
	state.SetField ( -1, "LOGIN_SYSTEM_ACCOUNT",		( u32 )FBSDKLoginBehaviorSystemAccount );
	state.SetField ( -1, "LOGIN_WEB",					( u32 )FBSDKLoginBehaviorWeb );
	
	// Game request action types
	state.SetField ( -1, "ACTION_NONE", 				( u32 )FBSDKGameRequestActionTypeNone );
	state.SetField ( -1, "ACTION_SEND", 				( u32 )FBSDKGameRequestActionTypeSend );
	state.SetField ( -1, "ACTION_ASK_FOR", 				( u32 )FBSDKGameRequestActionTypeAskFor );
	state.SetField ( -1, "ACTION_TURN", 				( u32 )FBSDKGameRequestActionTypeTurn );
	
	// Game request filters
	state.SetField ( -1, "FILTER_NONE", 				( u32 )FBSDKGameRequestFilterNone );
	state.SetField ( -1, "FILTER_APP_USERS", 			( u32 )FBSDKGameRequestFilterAppUsers );
	state.SetField ( -1, "FILTER_APP_NON_USERS", 		( u32 )FBSDKGameRequestFilterAppNonUsers );
	
	// Analytics predefined event names
	state.SetField ( -1, "EVENT_ACHIEVED_LEVEL",				[ FBSDKAppEventNameAchievedLevel 			UTF8String ]);
	state.SetField ( -1, "EVENT_ADDED_PAYMENT_INFO",			[ FBSDKAppEventNameAddedPaymentInfo 		UTF8String ]);
	state.SetField ( -1, "EVENT_ADDED_TO_CART",					[ FBSDKAppEventNameAddedToCart 				UTF8String ]);
	state.SetField ( -1, "EVENT_ADDED_TO_WISHLIST",				[ FBSDKAppEventNameAddedToWishlist 			UTF8String ]);
	state.SetField ( -1, "EVENT_COMPLETED_REGISTRATION", 		[ FBSDKAppEventNameCompletedRegistration 	UTF8String ]);
	state.SetField ( -1, "EVENT_COMPLETED_TUTORIAL",			[ FBSDKAppEventNameCompletedTutorial 		UTF8String ]);
	state.SetField ( -1, "EVENT_INITIATED_CHECKOUT",			[ FBSDKAppEventNameInitiatedCheckout 		UTF8String ]);
	state.SetField ( -1, "EVENT_RATED",							[ FBSDKAppEventNameRated 					UTF8String ]);
	state.SetField ( -1, "EVENT_SEARCHED",						[ FBSDKAppEventNameSearched 				UTF8String ]);
	state.SetField ( -1, "EVENT_SPENT_CREDITS",					[ FBSDKAppEventNameSpentCredits 			UTF8String ]);
	state.SetField ( -1, "EVENT_UNLOCKED_ACHIEVEMENT",			[ FBSDKAppEventNameUnlockedAchievement 		UTF8String ]);
	state.SetField ( -1, "EVENT_VIEWED_CONTENT",				[ FBSDKAppEventNameViewedContent 			UTF8String ]);

	// Analytics predefined event parameters names
	state.SetField ( -1, "PARAM_NAME_CONTENT_ID",				[ FBSDKAppEventParameterNameContentID 				UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_CONTENT_TYPE",				[ FBSDKAppEventParameterNameContentType 			UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_CURRENCY",					[ FBSDKAppEventParameterNameCurrency 				UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_DESCRIPTION",				[ FBSDKAppEventParameterNameDescription 			UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_LEVEL",					[ FBSDKAppEventParameterNameLevel 					UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_MAX_RATING_VALUE",			[ FBSDKAppEventParameterNameMaxRatingValue 			UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_NUM_ITEMS",				[ FBSDKAppEventParameterNameNumItems 				UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_PAYMENT_INFO_AVAILABLE",	[ FBSDKAppEventParameterNamePaymentInfoAvailable 	UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_REGISTRATION_METHOD",		[ FBSDKAppEventParameterNameRegistrationMethod 		UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_SEARCH_STRING",			[ FBSDKAppEventParameterNameSearchString 			UTF8String ]);
	state.SetField ( -1, "PARAM_NAME_SUCCESS",					[ FBSDKAppEventParameterNameSuccess 				UTF8String ]);

	// Analytics predefined event parameters values
	state.SetField ( -1, "PARAM_VALUE_NO",			[ FBSDKAppEventParameterValueNo 	UTF8String ]);
	state.SetField ( -1, "PARAM_VALUE_YES",			[ FBSDKAppEventParameterValueYes 	UTF8String ]);

	luaL_Reg regTable[] = {
		{ "createTestUser",					_createTestUser },
		{ "declinedPermissions", 			_declinedPermissions },
		{ "getExpirationDate", 				_getExpirationDate },
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIFacebookIOS > },
		{ "getToken", 						_getToken },
		{ "graphRequest", 					_graphRequest },
		{ "hasGranted", 					_hasGranted },
		{ "init", 							_init },
		{ "logEvent", 						_logEvent },
		{ "logPurchase", 					_logPurchase },
		{ "login", 							_login },
		{ "logout", 						_logout },
		{ "sendAppInvite", 					_sendAppInvite },
		{ "postToFeed", 					_postToFeed },
		{ "requestPublishPermissions", 		_requestPublishPermissions },
		{ "requestReadPermissions", 		_requestReadPermissions },
		{ "sendGameRequest", 				_sendGameRequest },
		{ "sessionValid", 					_sessionValid },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIFacebookIOS > },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::ClearCallbackRef ( int ref ) {
	
	if ( MOAILuaRuntime::IsValid () && ref != LUA_NOREF ) {
		this->mRefs.Unref ( ref );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::GameRequestDialogDidComplete ( NSDictionary* results, int ref ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_DIALOG_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		state.Push ( true );
		OBJC_TO_LUA ( results, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::GameRequestDialogDidFail ( NSError* error, int ref ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_DIALOG_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		state.Push ( false );
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::GraphRequestResponse ( id result, int ref ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		
		state.Push ( true );
		OBJC_TO_LUA ( result, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::GraphRequestResponseFailure ( NSError* error, int ref ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		
		state.Push ( false );
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::NotifyProfileChanged ( FBSDKProfile* profile ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( PROFILE_UPDATED, state )) {
		
		this->PushProfile	( state, profile );
		state.DebugCall		( 1, 0);
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::PermissionsDenied ( NSString *error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( PERMISSIONS_DENIED, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::PermissionsGranted () {
	
	this->InvokeListener ( PERMISSIONS_GRANTED );
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::PushProfile ( MOAILuaState& state, FBSDKProfile* profile ) {
	
	lua_newtable ( state );
	
	if ( profile != nil ) {
		
		if ( profile.userID ) {
			state.SetField ( -1, "userID", [ profile.userID UTF8String ]);
		}
		
		if ( profile.firstName ) {
			state.SetField ( -1, "firstName", [ profile.firstName UTF8String ]);
		}
		
		if ( profile.middleName ) {
			state.SetField ( -1, "middleName", [ profile.middleName UTF8String ]);
		}
		
		if ( profile.lastName ) {
			state.SetField ( -1, "lastName", [ profile.lastName UTF8String ]);
		}
		
		if ( profile.name ) {
			state.SetField ( -1, "name", [ profile.name UTF8String ]);
		}
		
		if ( profile.linkURL ) {
			state.SetField ( -1, "linkURL", [[ profile.linkURL absoluteString ] UTF8String ]);
		}
		
		if ( profile.refreshDate ) {
			
			lua_pushstring ( state, "refreshDate" );
			[ profile.refreshDate toLua:state ];
			lua_settable ( state, -3 );
		}
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::SessionDidLogin () {
	
	this->InvokeListener ( SESSION_DID_LOGIN );
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::SessionDidNotLogin () {
	
	this->InvokeListener ( SESSION_DID_NOT_LOGIN );
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::SessionExtended ( cc8* token, cc8* expDate ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( SESSION_EXTENDED, state )) {
		state.Push ( token );
		state.Push ( expDate );
		state.DebugCall ( 2, 0 );
	}
}


//================================================================//
// MOAIFacebookLuaCallbackRef
//================================================================//
@implementation MOAIFacebookLuaCallbackRef

//----------------------------------------------------------------//
- ( id ) initWithRef: ( int )ref {
	
	self = [ super init ];
	if ( self != nil ) {
		self->mRef = ref;
	}
	return self;
}

//----------------------------------------------------------------//
- ( int ) ref {
	return self->mRef;
}

//----------------------------------------------------------------//
- ( void ) dealloc {
	
	if ( MOAIFacebookIOS::IsValid ()) {
		MOAIFacebookIOS::Get ().ClearCallbackRef ( self->mRef );
	}
	self->mRef = LUA_NOREF;
	[ super dealloc ];
}

@end


//================================================================//
// MOAIFBSDKDelegate
//================================================================//
@implementation MOAIFBSDKDelegate

//----------------------------------------------------------------//
- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didCompleteWithResults:( NSDictionary* ) results {
	
	int ref = LUA_NOREF;
	id object = objc_getAssociatedObject ( gameRequestDialog, kGameRequestCallbackRef );
	if ( object ) {
		ref = [( MOAIFacebookLuaCallbackRef* )object ref ];
	}
	
	MOAIFacebookIOS::Get ().GameRequestDialogDidComplete ( results, ref );
}

//----------------------------------------------------------------//
- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didFailWithError:( NSError* ) error {

	int ref = LUA_NOREF;
	id object = objc_getAssociatedObject ( gameRequestDialog, kGameRequestCallbackRef );
	if ( object ) {
		ref = [( MOAIFacebookLuaCallbackRef* )object ref ];
	}
	
	MOAIFacebookIOS::Get ().GameRequestDialogDidFail ( error, ref );
}

//----------------------------------------------------------------//
- ( void ) gameRequestDialogDidCancel:( FBSDKGameRequestDialog* ) gameRequestDialog {
	
	int ref = LUA_NOREF;
	id object = objc_getAssociatedObject ( gameRequestDialog, kGameRequestCallbackRef );
	if ( object ) {
		ref = [( MOAIFacebookLuaCallbackRef* )object ref ];
	}
	
	MOAIFacebookIOS::Get ().GameRequestDialogDidFail ( nil, ref );
}

//----------------------------------------------------------------//
- ( void ) onProfileChanged:( NSNotification* ) notification {

	if ([ FBSDKAccessToken currentAccessToken ]) {
		
		FBSDKProfile* profile = ( FBSDKProfile* )[[ notification userInfo ] objectForKey:FBSDKProfileChangeNewKey ];
		
		if ( MOAIFacebookIOS::IsValid ()) {
			MOAIFacebookIOS::Get ().NotifyProfileChanged ( profile );
		}
	}
}

@end

