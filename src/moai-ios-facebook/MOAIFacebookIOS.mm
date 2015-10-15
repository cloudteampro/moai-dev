//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios/headers.h>
#import <moai-ios-facebook/MOAIFacebookIOS.h>


//================================================================//
// MOAIFacebookLuaCallback
//================================================================//
//
// This class is for use with async objective-C block callbacks.
// It should be retained by block and will ensure that Lua callback ref
// will have the same lifetime as enclosing obj-C block.
//
@interface MOAIFacebookLuaCallback : NSObject {
@protected
	int mRef;
}

//----------------------------------------------------------------//
-( id )	initWithRef :( int )ref;
-( int ) ref;
@end


//================================================================//
// MOAIFacebookGameRequestCallback
//================================================================//
@interface MOAIFacebookGameRequestCallback : MOAIFacebookLuaCallback < FBSDKGameRequestDialogDelegate > {
@private
}

//----------------------------------------------------------------//
- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didCompleteWithResults:( NSDictionary* ) results;
- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didFailWithError:( NSError* ) error;
- ( void ) gameRequestDialogDidCancel:( FBSDKGameRequestDialog* ) gameRequestDialog;
@end




//================================================================//
// lua
//================================================================//

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
	
	if ( ![ FBSDKAccessToken currentAccessToken ]) {
		MOAIFacebookIOS::Get ().ReceivedRequestResponseFailure ( nil );
		return 0;
	}
	
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
	MOAIFacebookLuaCallback* callback = [[[ MOAIFacebookLuaCallback alloc ] initWithRef:ref ] autorelease ];
	
	NSString* nsMethod 	= [[[ NSString alloc ] initWithUTF8String:method ] autorelease ];
	NSString* nsPath 	= [[[ NSString alloc ] initWithUTF8String:path ] autorelease ];
	
	FBSDKGraphRequest *request = [[[ FBSDKGraphRequest alloc] initWithGraphPath:nsPath parameters:paramsDict HTTPMethod:nsMethod ] autorelease ];
	[ request startWithCompletionHandler:^( FBSDKGraphRequestConnection *connection, id result, NSError *error ) {
		
		UNUSED ( connection );

		if ( error ) {
			MOAIFacebookIOS::Get ().ReceivedRequestResponseFailure ( error );
		}
		else {
			MOAIFacebookIOS::Get ().ReceivedRequestResponse ( result, [ callback ref ]);
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
		
		BOOL result = [[ FBSDKAccessToken currentAccessToken ] hasGranted:[ NSString stringWithUTF8String:permission ]];
		state.Push (( bool )result );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Facebook.

	@in		string	loginAppId		Available in Facebook developer settings.
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
 
	@opt	table	permissions		Optional set of required permissions. See Facebook documentation for a full list. Default is nil.
	@out 	nil
*/
int MOAIFacebookIOS::_login ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIFacebookIOS, "" )
	
	NSMutableDictionary* paramsDict = [[ NSMutableDictionary alloc ] init ];
	if ( state.IsType ( 1, LUA_TTABLE )) {
		[ paramsDict initWithLua:state stackIndex:1 ];
	}
	NSArray* paramsArray = [ paramsDict allValues ];
	
	FBSDKLoginManager* login = [[ FBSDKLoginManager alloc] init ];
	[ login logInWithReadPermissions:paramsArray handler:^( FBSDKLoginManagerLoginResult *result, NSError *error ) {
	
		if ( error ) {
			self->DialogDidNotComplete ();
		}
		else if ( result.isCancelled ) {
		
			self->DialogDidNotComplete ();
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
	
	if ([ FBSDKAccessToken currentAccessToken ]) {
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
			FBSDKLoginManager* login = [[ FBSDKLoginManager alloc] init ];
			
			[ login logInWithPublishPermissions:requested handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
				
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
			FBSDKLoginManager* login = [[ FBSDKLoginManager alloc] init ];
			
			[ login logInWithReadPermissions:requested handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
				
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
	@opt 	function 	callback 		Signature: function(bool success, data)
										data can be table or nil if success, or string describing error
	
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

	BOOL frictionless = false;
	if ( state.IsType ( 2, LUA_TTABLE )) {
		frictionless		= state.GetValue < bool >( 2, "frictionless" );
		
		cc8* data			= state.GetField < cc8* >( 2, "data", "" );
		cc8* title			= state.GetField < cc8* >( 2, "title", "" );
		cc8* objectID		= state.GetField < cc8* >( 2, "objectID", "" );
		
		content.actionType	= state.GetField < u32 >( 2, "actionType",	FBSDKGameRequestActionTypeNone );
		content.filters		= state.GetField < u32 >( 2, "filters",		FBSDKGameRequestFilterNone );
		
		content.data		= [ NSString stringWithUTF8String:data ];
		content.title		= [ NSString stringWithUTF8String:title ];
		content.objectID	= [ NSString stringWithUTF8String:objectID ];
		
		if ( state.GetFieldWithType ( 2, "recipients", LUA_TTABLE )) {
			// TODO:	implement NSMutableArray+MOAILib initWithLua:
			//			I recall my failed attempt
			NSMutableDictionary* recipients = [[[ NSMutableDictionary alloc ] init ] autorelease ];
			[ recipients initWithLua:state stackIndex:-1 ];
			content.recipients = [ recipients allValues ];
			state.Pop ( 1 );
		}
		
		if ( state.GetFieldWithType ( 2, "recipientSuggestions", LUA_TTABLE )) {
			NSMutableDictionary* recipients = [[[ NSMutableDictionary alloc ] init ] autorelease ];
			[ recipients initWithLua:state stackIndex:-1 ];
			content.recipientSuggestions = [ recipients allValues ];
			state.Pop ( 1 );
		}
	}
	
	int ref = LUA_NOREF;
	if ( state.IsType ( 3, LUA_TFUNCTION )) {
		ref = self->mRefs.Ref ( state, 3 );
	}
	MOAIFacebookGameRequestCallback* delegate = [[[ MOAIFacebookGameRequestCallback alloc ] initWithRef: ref ] autorelease ];
	
	FBSDKGameRequestDialog* dialog = [[ FBSDKGameRequestDialog alloc ] init ];
	NSError* error = nil;
	if ([ dialog validateWithError:&error ]) {
		
		[ dialog setDelegate: delegate ];
		[ dialog setContent: content ];
		[ dialog setFrictionlessRequestsEnabled: frictionless ];
		
		state.Push ([ dialog show ]);
		return 1;
	}
	else {
		state.Push ( false );
		if ( error ) {
			[ error toLua:state ];
		}
		else {
			state.Push ();
		}
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
	
//================================================================//
// MOAIFacebookIOS
//================================================================//

//----------------------------------------------------------------//
MOAIFacebookIOS::MOAIFacebookIOS () {
	
	RTTI_SINGLE ( MOAIGlobalEventSource )

	mRefs.InitStrong ();
}

//----------------------------------------------------------------//
MOAIFacebookIOS::~MOAIFacebookIOS () {
	
	mRefs.Clear ();
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "DIALOG_DID_COMPLETE", 		( u32 )DIALOG_DID_COMPLETE );
	state.SetField ( -1, "DIALOG_DID_NOT_COMPLETE",		( u32 )DIALOG_DID_NOT_COMPLETE );
	state.SetField ( -1, "REQUEST_RESPONSE", 			( u32 )REQUEST_RESPONSE );
	state.SetField ( -1, "REQUEST_RESPONSE_FAILED", 	( u32 )REQUEST_RESPONSE_FAILED );
	state.SetField ( -1, "SESSION_DID_LOGIN", 			( u32 )SESSION_DID_LOGIN );
	state.SetField ( -1, "SESSION_DID_NOT_LOGIN", 		( u32 )SESSION_DID_NOT_LOGIN );
	state.SetField ( -1, "SESSION_EXTENDED",			( u32 )SESSION_EXTENDED );

	state.SetField ( -1, "ACTION_NONE", 				( u32 )FBSDKGameRequestActionTypeNone );
	state.SetField ( -1, "ACTION_SEND", 				( u32 )FBSDKGameRequestActionTypeSend );
	state.SetField ( -1, "ACTION_ASK_FOR", 				( u32 )FBSDKGameRequestActionTypeAskFor );
	state.SetField ( -1, "ACTION_TURN", 				( u32 )FBSDKGameRequestActionTypeTurn );

	state.SetField ( -1, "FILTER_NONE", 				( u32 )FBSDKGameRequestFilterNone );
	state.SetField ( -1, "FILTER_APP_USERS", 			( u32 )FBSDKGameRequestFilterAppUsers );
	state.SetField ( -1, "FILTER_APP_NON_USERS", 		( u32 )FBSDKGameRequestFilterAppNonUsers );

	
	state.SetField ( -1, "NAME_ACHIEVED_LEVEL",			[ FBSDKAppEventNameAchievedLevel 			UTF8String ]);
	state.SetField ( -1, "NAME_ADDED_PAYMENT_INFO",		[ FBSDKAppEventNameAddedPaymentInfo 		UTF8String ]);
	state.SetField ( -1, "NAME_ADDED_TO_CART",			[ FBSDKAppEventNameAddedToCart 				UTF8String ]);
	state.SetField ( -1, "NAME_ADDED_TO_WISHLIST",		[ FBSDKAppEventNameAddedToWishlist 			UTF8String ]);
	state.SetField ( -1, "NAME_COMPLETED_REGISTRATION", [ FBSDKAppEventNameCompletedRegistration 	UTF8String ]);
	state.SetField ( -1, "NAME_COMPLETED_TUTORIAL",		[ FBSDKAppEventNameCompletedTutorial 		UTF8String ]);
	state.SetField ( -1, "NAME_INITIATED_CHECKOUT",		[ FBSDKAppEventNameInitiatedCheckout 		UTF8String ]);
	state.SetField ( -1, "NAME_RATED",					[ FBSDKAppEventNameRated 					UTF8String ]);
	state.SetField ( -1, "NAME_SEARCHED",				[ FBSDKAppEventNameSearched 				UTF8String ]);
	state.SetField ( -1, "NAME_SPENT_CREDITS",			[ FBSDKAppEventNameSpentCredits 			UTF8String ]);
	state.SetField ( -1, "NAME_UNLOCKED_ACHIEVEMENT",	[ FBSDKAppEventNameUnlockedAchievement 		UTF8String ]);
	state.SetField ( -1, "NAME_VIEWED_CONTENT",			[ FBSDKAppEventNameViewedContent 			UTF8String ]);

	state.SetField ( -1, "PARAMETER_NAME_CONTENT_ID",				[ FBSDKAppEventParameterNameContentID 				UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_CONTENT_TYPE",				[ FBSDKAppEventParameterNameContentType 			UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_CURRENCY",					[ FBSDKAppEventParameterNameCurrency 				UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_DESCRIPTION",				[ FBSDKAppEventParameterNameDescription 			UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_LEVEL",					[ FBSDKAppEventParameterNameLevel 					UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_MAX_RATING_VALUE",			[ FBSDKAppEventParameterNameMaxRatingValue 			UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_NUM_ITEMS",				[ FBSDKAppEventParameterNameNumItems 				UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_PAYMENT_INFO_AVAILABLE",	[ FBSDKAppEventParameterNamePaymentInfoAvailable 	UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_REGISTRATION_METHOD",		[ FBSDKAppEventParameterNameRegistrationMethod 		UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_SEARCH_STRING",			[ FBSDKAppEventParameterNameSearchString 			UTF8String ]);
	state.SetField ( -1, "PARAMETER_NAME_SUCCESS",					[ FBSDKAppEventParameterNameSuccess 				UTF8String ]);
	
	state.SetField ( -1, "PARAMETER_VALUE_NO",			[ FBSDKAppEventParameterValueNo 	UTF8String ]);
	state.SetField ( -1, "PARAMETER_VALUE_YES",			[ FBSDKAppEventParameterValueYes 	UTF8String ]);

	luaL_Reg regTable[] = {
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
	
	if ( ref != LUA_NOREF ) {
		this->mRefs.Unref ( ref );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::DialogDidNotComplete () {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( DIALOG_DID_NOT_COMPLETE, state )) {
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::DialogDidComplete () {
		
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( DIALOG_DID_COMPLETE, state )) {
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::PermissionsDenied ( NSString *error ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( PERMISSIONS_DENIED, state )) {
		
		if ( error ) {
			
			[ error toLua:state ];
			state.DebugCall ( 1, 0 );
		}
		else {
			state.DebugCall ( 0, 0 );
		}
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::PermissionsGranted() {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( PERMISSIONS_GRANTED, state )) {
		
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::ReceivedRequestResponse ( id result, int ref ) {

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		
		if ([ result isKindOfClass:[ NSString class ]]) {
			[(( NSString* )result ) toLua:state ];
		}
		else if ([ result isKindOfClass:[ NSData class ]]) {
			[(( NSData* )result ) toLua:state ];
		}
		else {
			state.Push ();
		}
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::ReceivedRequestResponseFailure ( NSError* error ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->PushListener ( REQUEST_RESPONSE_FAILED, state )) {
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::RequestDialogDidComplete ( NSDictionary* results, int ref ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_DIALOG_DID_COMPLETE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {

		if ( results ) {
			[ results toLua:state ];
		}
		else {
			state.Push ();
		}
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::RequestDialogDidFail ( NSError* error, int ref ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_DIALOG_DID_FAIL, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		
		if ( error ) {
			[ error toLua:state ];
		}
		else {
			state.Push ();
		}
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::RequestDialogDidCancel ( int ref ) {

	if ( ref == LUA_NOREF ) {
		this->InvokeListener ( REQUEST_DIALOG_DID_CANCEL );
	}
	else {
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		this->mRefs.PushRef ( state, ref );
		
		if ( state.IsType ( -1, LUA_TFUNCTION )) {
			state.DebugCall ( 0, 0 );
		}
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::SessionDidLogin () {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( SESSION_DID_LOGIN, state )) {
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::SessionDidNotLogin () {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( SESSION_DID_NOT_LOGIN, state )) {
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookIOS::SessionExtended ( cc8* token, cc8* expDate ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( SESSION_EXTENDED, state )) {
		state.Push ( token );		
		state.Push ( expDate );
		state.DebugCall ( 2, 0 );
	}
}


//================================================================//
// MOAIFacebookLuaCallback
//================================================================//
@implementation MOAIFacebookLuaCallback

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
// MOAIFacebookGameRequestCallback
//================================================================//
@implementation MOAIFacebookGameRequestCallback

//----------------------------------------------------------------//
- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didCompleteWithResults:( NSDictionary* ) results {

	MOAIFacebookIOS::Get ().RequestDialogDidComplete ( results, self->mRef );
}

- ( void ) gameRequestDialog:( FBSDKGameRequestDialog* ) gameRequestDialog didFailWithError:( NSError* ) error {

	MOAIFacebookIOS::Get ().RequestDialogDidFail ( error, self->mRef );
}

- ( void ) gameRequestDialogDidCancel:( FBSDKGameRequestDialog* ) gameRequestDialog {

	MOAIFacebookIOS::Get ().RequestDialogDidCancel ( self->mRef );
}

@end

