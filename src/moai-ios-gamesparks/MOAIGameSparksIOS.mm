//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios/headers.h>
#import <moai-ios-gamesparks/MOAIGameSparksIOS.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@lua	init
	@text	Init GameSparks.
	
	@in 	api key
	@in 	api secret
	@in 	credential
	@out 	nil
*/
int MOAIGameSparksIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* apikey = state.GetValue < cc8* >( 1, 0 );
	cc8* apisecret = state.GetValue < cc8* >( 2, 0 );
	cc8* credential = state.GetValue < cc8* >( 3, 0 );

	GS* gs = [[GS alloc] initWithApiKey:[ NSString stringWithUTF8String:apikey ]
		andApiSecret:[ NSString stringWithUTF8String:apisecret ]
		andCredential:[ NSString stringWithUTF8String:credential ]
		andPreviewMode:true];

	[GS setGs:gs];

	[gs setAvailabilityListener:^ (BOOL available) {
		MOAIGameSparksIOS::Get ().AvailabilityResponse (( int ) available );
	}];

	[gs setAuthenticatedListener:^(NSString* playerId) {
		NSLog ( @"MOAIGameSparksIOS: authenticated %@\n", playerId );
	}];

	// GSMessageListener* listener = [[GSMessageListener alloc] init];

	// [listener onGSScriptMessage:^(GSScriptMessage* message) {
	//     NSLog(@"%@", message.getMessageId);
	//     success = true;
	// }];

	// [gs setMessageListener:listener];

	[gs connect];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	connect
	@text	Provides authentication using 
			a username/password combination.

			The username will have been previously 
			created using a RegistrationRequest.
	
	@in 	string	username
	@in 	string	password
	@out 	nil
*/
int MOAIGameSparksIOS::_connect ( lua_State* L ) {

	MOAIJString username = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString password = self->GetJString ( lua_tostring ( state, 2 ));

	// GSRegistrationRequest* request = [[GSRegistrationRequest alloc] init];
	// [request setDisplayName:displayName;]
	// [request setPassword:password;]
	// [request setSegments:segments;]
	// [request setUserName:userName;]
	// [request setCallback:^ (GSRegistrationResponse* response) {
	//     NSString* authToken = [response getAuthToken]; 
	//     NSString* displayName = [response getDisplayName]; 
	//     BOOL newPlayer = [response getNewPlayer]; 
	//     NSDictionary* scriptData = [response getScriptData]; 
	//     GSPlayer* switchSummary = [response getSwitchSummary]; 
	//     NSString* userId = [response getUserId]; 
	// }];
	// [gs send:request];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	connectFB
	@text	Create gamesparks registration with fb
	
	@in 	accessToken - token from fb
	@out 	nil
*/
int MOAIGameSparksIOS::_connectFB ( lua_State* L ) {

	MOAILuaState state ( L );

	cc8* accessToken = state.GetValue < cc8* >( 1, 0 );

	GSFacebookConnectRequest* request = [[GSFacebookConnectRequest alloc] init];
	[request setAccessToken:[ NSString stringWithUTF8String:accessToken ]];
	// [request setCode:code];
	// [request setDoNotLinkToCurrentPlayer:doNotLinkToCurrentPlayer];
	// [request setErrorOnSwitch:errorOnSwitch];
	// [request setSegments:segments];
	// [request setSwitchIfPossible:switchIfPossible];
	// [request setSyncDisplayName:syncDisplayName];
	[request setCallback:^ (GSAuthenticationResponse* response) {
		if ([response getUserId]) {
			MOAIGameSparksIOS::Get ().FBConnectSuccessResponse ( [response getDisplayName], [response getUserId], ( bool ) [response getNewPlayer] );
		}
		else {
			// todo: fix get error from responce
			MOAIGameSparksIOS::Get ().FBConnectFailResponse ( [response getAuthToken] );
		}
	}];
	[[GS gs] send:request];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getAccountDetails
	@text	Create gamesparks registration with fb
	
	@in 	accessToken - token from fb
	@out 	nil
*/
int MOAIGameSparksIOS::_getAccountDetails ( lua_State* L ) {

	MOAILuaState state ( L );

	GSAccountDetailsRequest* request = [[GSAccountDetailsRequest alloc] init];
	[request setCallback:^ (GSAccountDetailsResponse* response) {
	    NSString* achievements = [response getAchievements]; 
	    NSDictionary* currencies = [response getCurrencies]; 
	//     NSNumber* currency1 = [response getCurrency1]; 
	//     NSNumber* currency2 = [response getCurrency2]; 
	//     NSNumber* currency3 = [response getCurrency3]; 
	//     NSNumber* currency4 = [response getCurrency4]; 
	//     NSNumber* currency5 = [response getCurrency5]; 
	//     NSNumber* currency6 = [response getCurrency6]; 
	//     NSString* displayName = [response getDisplayName]; 
	//     NSDictionary* externalIds = [response getExternalIds]; 
	//     GSLocation* location = [response getLocation]; 
	    NSDictionary* reservedCurrencies = [response getReservedCurrencies]; 
	//     NSDictionary* reservedCurrency1 = [response getReservedCurrency1]; 
	//     NSDictionary* reservedCurrency2 = [response getReservedCurrency2]; 
	//     NSDictionary* reservedCurrency3 = [response getReservedCurrency3]; 
	//     NSDictionary* reservedCurrency4 = [response getReservedCurrency4]; 
	//     NSDictionary* reservedCurrency5 = [response getReservedCurrency5]; 
	//     NSDictionary* reservedCurrency6 = [response getReservedCurrency6]; 
	//     NSString* userId = [response getUserId]; 
	//     NSDictionary* virtualGoods = [response getVirtualGoods];
		NSLog ( @"MOAIGameSparksIOS: got account details:\n achievements:%@\n currencies:%@\n reservedCurrencies:%@\n", achievements, currencies, reservedCurrencies );
	}];
	[[GS gs] send:request];

	return 0;
}

//================================================================//
// MOAIGameSparksIOS
//================================================================//

//----------------------------------------------------------------//
void MOAIGameSparksIOS::AvailabilityResponse ( int available ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_AVAILABILITY, state )) {
		
		state.Push ( available );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::FBConnectSuccessResponse ( NSString *displayName, NSString *userId, bool isNew ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FB_CONNECT_SUCCESS, state )) {
		
		OBJC_TO_LUA ( displayName, state );
		OBJC_TO_LUA ( userId, state );
		state.Push ( isNew );
		state.DebugCall ( 3, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::FBConnectFailResponse ( NSString *error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FB_CONNECT_FAIL, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
MOAIGameSparksIOS::MOAIGameSparksIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIGameSparksIOS::~MOAIGameSparksIOS () {
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::RegisterLuaClass ( MOAILuaState& state ) {

	// Events
	state.SetField ( -1, "ON_AVAILABILITY",			( u32 )ON_AVAILABILITY );
	state.SetField ( -1, "ON_GET_ACCOUNT_DETAILS",	( u32 )ON_GET_ACCOUNT_DETAILS );
	state.SetField ( -1, "ON_FB_CONNECT_SUCCESS",	( u32 )ON_FB_CONNECT_SUCCESS );
	state.SetField ( -1, "ON_FB_CONNECT_FAIL",		( u32 )ON_FB_CONNECT_FAIL );

	luaL_Reg regTable [] = {
		{ "connect",				_connect },
		{ "connectFB",				_connectFB },
		{ "getAccountDetails",		_getAccountDetails },
		{ "getListener",			&MOAIGlobalEventSource::_getListener < MOAIGameSparksIOS > },
		{ "init",					_init },
		{ "setListener",			&MOAIGlobalEventSource::_setListener < MOAIGameSparksIOS > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

