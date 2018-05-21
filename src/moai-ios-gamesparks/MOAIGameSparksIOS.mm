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
	@text	Initialize GameSparks.
	
	@in 	string	apiKey
	@in 	string	apiSecret
	@in 	string	credential
	@in 	boolean	liveMode
	@in 	boolean	autoUpdate
	@out 	nil
*/
int MOAIGameSparksIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* apikey = state.GetValue < cc8* >( 1, 0 );
	cc8* apiSecret = state.GetValue < cc8* >( 2, 0 );
	cc8* credential = state.GetValue < cc8* >( 3, 0 );
	bool liveMode = state.GetValue < bool >( 4, false );
	bool autoUpdate = state.GetValue < bool >( 5, false );

	GS* gs = [[ GS alloc ] initWithApiKey:[ NSString stringWithUTF8String:apikey ]
		andApiSecret:[ NSString stringWithUTF8String:apiSecret ]
		andCredential:[ NSString stringWithUTF8String:credential ]
		andPreviewMode:liveMode ];

	[ GS setGs:gs ];

	[ gs setAvailabilityListener:^ ( BOOL available ) {

		MOAIGameSparksIOS::Get ().AvailabilityResponse ( available );
	}];

	[ gs setAuthenticatedListener:^( NSString* playerId ) {

		NSLog ( @"MOAIGameSparksIOS: authenticated %@\n", playerId );
	}];

	[ gs connect ];
	
	return 0;
}


//----------------------------------------------------------------//
/**	@lua	requestAccountDetails
	@text	Request account details.
				
	@out 	nil
*/
int MOAIGameSparksIOS::_requestAccountDetails ( lua_State* L ) {

	MOAILuaState state ( L );

	GSAccountDetailsRequest* request = [[GSAccountDetailsRequest alloc] init];
	[ request setCallback:^ ( GSAccountDetailsResponse* response ) {

	    //NSString* achievements = [ response getAchievements ];
	    //NSDictionary* currencies = [ response getCurrencies ];
	    //NSNumber* currency1 = [ response getCurrency1 ]; 
	    //NSNumber* currency2 = [ response getCurrency2 ]; 
	    //NSNumber* currency3 = [ response getCurrency3 ]; 
	    //NSNumber* currency4 = [ response getCurrency4 ]; 
	    //NSNumber* currency5 = [ response getCurrency5 ]; 
	    //NSNumber* currency6 = [ response getCurrency6 ]; 
	    NSString* displayName = [ response getDisplayName ];
	    //NSDictionary* externalIds = [ response getExternalIds ]; 
	    //GSLocation* location = [ response getLocation ]; 
	    //NSDictionary* reservedCurrencies = [ response getReservedCurrencies ];
	    //NSDictionary* reservedCurrency1 = [ response getReservedCurrency1 ]; 
	    //NSDictionary* reservedCurrency2 = [ response getReservedCurrency2 ]; 
	    //NSDictionary* reservedCurrency3 = [ response getReservedCurrency3 ]; 
	    //NSDictionary* reservedCurrency4 = [ response getReservedCurrency4 ]; 
	    //NSDictionary* reservedCurrency5 = [ response getReservedCurrency5 ]; 
	    //NSDictionary* reservedCurrency6 = [ response getReservedCurrency6 ]; 
	    NSString* userId = [ response getUserId ];
	    //NSDictionary* virtualGoods = [ response getVirtualGoods ];
		NSDictionary* errors = [ response getErrors ];
		
		if ( !errors ) {
			
			MOAIGameSparksIOS::Get ().AccountDetailsSuccessResponse ( displayName, userId );
		} else {
			
			MOAIGameSparksIOS::Get ().AccountDetailsFailResponse ( @"" );
		}
	}];
	[[ GS gs ] send:request ];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestAuthentication
	@text	Request authentication.
				
	@in 	string	password		The previously registered password
	@in 	string	userName 		The previously registered player name
	@out 	nil
*/
int MOAIGameSparksIOS::_requestAuthentication ( lua_State* L ) {

	MOAILuaState state ( L );

	cc8* password = state.GetValue < cc8* >( 1, 0 );
	cc8* username = state.GetValue < cc8* >( 2, 0 );

	GSAuthenticationRequest* request = [[ GSAuthenticationRequest alloc ] init ];
	[ request setPassword:[ NSString stringWithUTF8String:password ]];
	[ request setUserName:[ NSString stringWithUTF8String:username ]];
	[ request setCallback:^ ( GSAuthenticationResponse* response ) {

		NSString* authToken = [ response getAuthToken ];
		NSString* displayName = [ response getDisplayName ];
		BOOL newPlayer = [ response getNewPlayer ];
		NSDictionary* scriptData = [ response getScriptData ];
		GSPlayer* switchSummary = [ response getSwitchSummary ];
		NSString* userId = [ response getUserId ];
		NSDictionary* errors = [ response getErrors ];
		
		if ( !errors ) {
			
			MOAIGameSparksIOS::Get ().AuthenticationSuccessResponse ( authToken, displayName, newPlayer, userId );
		} else {
			
			MOAIGameSparksIOS::Get ().AuthenticationFailResponse ([ errors objectForKey:@"DETAILS" ]);
		}
	}];
	[[ GS gs ] send:request ];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestBuyGoods
	@text	Request validate purchase.
				
	@opt 	string	currencyCode				The ISO 4217 currency code representing the real-world currency used for this transaction.
	@in 	string	receipt 					The receipt obtained from SKPaymentTransaction. transactionReceipt
	@opt 	boolean	sandbox						Should the sandbox account be used
	@opt 	number	subUnitPrice 				The price of this purchase
	@opt 	boolean	uniqueTransactionByPlayer 	boolean	If set to true, the transactionId from this receipt will not be 
												globally valdidated, this will mean replays between players are possible.
	@out 	nil
*/
int	MOAIGameSparksIOS::_requestBuyGoods ( lua_State* L ) {

	MOAILuaState state ( L );

	cc8* receipt = state.GetValue < cc8* >( 1, 0 );

	GSIOSBuyGoodsRequest* request = [[ GSIOSBuyGoodsRequest alloc ] init ];
	//[ request setCurrencyCode:currencyCode ];
	[ request setReceipt:[ NSString stringWithUTF8String:receipt ]];
	//[ request setSandbox:sandbox ];
	//[ request setSubUnitPrice:subUnitPrice ];
	//[ request setUniqueTransactionByPlayer:uniqueTransactionByPlayer ];
	[ request setCallback:^ ( GSBuyVirtualGoodResponse* response ) {
		
		NSArray* boughtItems = [ response getBoughtItems ]; 
		//NSDictionary* currenciesAdded = [response getCurrenciesAdded ]; 
		//NSNumber* currency1Added = [ response getCurrency1Added ]; 
		//NSNumber* currency2Added = [ response getCurrency2Added ]; 
		//NSNumber* currency3Added = [ response getCurrency3Added ]; 
		//NSNumber* currency4Added = [ response getCurrency4Added ]; 
		//NSNumber* currency5Added = [ response getCurrency5Added ]; 
		//NSNumber* currency6Added = [ response getCurrency6Added ]; 
		//NSNumber* currencyConsumed = [ response getCurrencyConsumed ]; 
		//NSString* currencyShortCode = [ response getCurrencyShortCode ]; 
		//NSNumber* currencyType = [ response getCurrencyType ]; 
		//NSArray* invalidItems = [ response getInvalidItems ]; 
		//NSDictionary* scriptData = [ response getScriptData ]; 
		//NSArray* transactionIds = [ response getTransactionIds ];
		NSDictionary* errors = [ response getErrors ];
		
		if ( !errors ) {
			
			MOAIGameSparksIOS::Get ().BuyVirtualGoodSuccessResponse ( boughtItems[1] );
		} else {
			
			MOAIGameSparksIOS::Get ().BuyVirtualGoodFailResponse ([ errors objectForKey:@"verificationError" ]);
		}
    }];
    [[ GS gs ] send:request ];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestFacebookConnect
	@text	Connect with Facebook.
				
	@in 	string	accessToken 				The access token is used by the client to 
												make authenticated requests on behalf of the end user.
	@opt 	string	code 						An authorization code is a short-lived token representing the user's access grant, 
												created by the authorization server and passed to the client application via the browser.
	@opt 	boolean	doNotLinkToCurrentPlayer	Indicates that the server should not try to link the external profile with the current player. 
												If false, links the external profile to the currently signed in player. 
												If true, creates a new player and links the external profile to them. Defaults to false.
	@opt 	boolean	errorOnSwitch				Indicates whether the server should return an error if an account switch would have occurred, 
												rather than switching automatically. Defaults to false.
	@opt 	JSON	segments					An optional segment configuration for this request.
	@opt 	boolean	switchIfPossible			Indicates that the server should switch to the supplied profile 
												if it isalready associated to a player. Defaults to false.
	@opt 	boolean	syncDisplayName				Indicates that the associated players displayName should be kept 
												in syn with this profile when it's updated by the external provider.
	@out 	nil
*/
int MOAIGameSparksIOS::_requestFacebookConnect ( lua_State* L ) {

	MOAILuaState state ( L );

	cc8* accessToken = state.GetValue < cc8* >( 1, 0 );

	GSFacebookConnectRequest* request = [[ GSFacebookConnectRequest alloc ] init ];
	[ request setAccessToken:[ NSString stringWithUTF8String:accessToken ]];
	//[request setCode:code];
	//[request setDoNotLinkToCurrentPlayer:doNotLinkToCurrentPlayer];
	//[request setErrorOnSwitch:errorOnSwitch];
	//[request setSegments:segments];
	//[request setSwitchIfPossible:switchIfPossible];
	//[request setSyncDisplayName:syncDisplayName];
	[ request setCallback:^ ( GSAuthenticationResponse* response ) {

	    NSString* authToken = [ response getAuthToken ]; 
	    NSString* displayName = [ response getDisplayName ]; 
	    BOOL newPlayer = [ response getNewPlayer ]; 
	    //NSDictionary* scriptData = [ response getScriptData ]; 
	    //GSPlayer* switchSummary = [ response getSwitchSummary ]; 
	    NSString* userId = [ response getUserId ];
		NSDictionary* errors = [ response getErrors ];
		
		if ( !errors ) {
			
			MOAIGameSparksIOS::Get ().FacebookConnectSuccessResponse ( authToken, displayName, ( bool ) newPlayer, userId );
		} else {
			
			MOAIGameSparksIOS::Get ().FacebookConnectFailResponse ([ errors objectForKey:@"accessToken" ], [ errors objectForKey:@"code" ], [ errors objectForKey:@"authentication" ]);
		}
	}];
	[[ GS gs ] send:request ];

	return 0;
}


//----------------------------------------------------------------//
/**	@lua	requestLogEvent
	@text	Request log event.
				
	@in 	string	eventKey		Event key
	@in 	array	attributes 		Key-value attributes
	@out 	nil
*/
int	MOAIGameSparksIOS::_requestLogEvent ( lua_State* L ) {

	MOAILuaState state ( L );

	cc8* eventKey = state.GetValue < cc8* >( 1, 0 );
	
	GSLogEventRequest* request = [[ GSLogEventRequest alloc ] init ];
	NSMutableDictionary* attributes = nil;
	
	if ( state.IsType( 2, LUA_TTABLE )) {
		
		attributes = [[[ NSMutableDictionary alloc ] init ] autorelease ];
		[ attributes initWithLua:state stackIndex:2 ];
	}
	
	if ( attributes ) {
		
		for ( NSObject *aKey in [ attributes allKeys ]) {
			NSObject *aValue = [ attributes valueForKey:aKey ];
			
			if ( [ aValue length ] != 0  ) {
				
				[ request setEventAttribute:[ NSString stringWithUTF8String: ( cc8* )aKey ] withString:[ NSString stringWithUTF8String: ( cc8* )aValue ]];
			}
		}
	}
	
    [ request setEventKey:[ NSString stringWithUTF8String:eventKey ]];
    [ request setCallback:^ ( GSLogEventResponse* response ) {

    	NSDictionary* scriptData = [ response getScriptData ];
		NSDictionary* errors = [ response getErrors ];
		
		if ( !errors ) {
			
			MOAIGameSparksIOS::Get ().LogEventSuccessResponse ([ NSString stringWithUTF8String:eventKey ], attributes, response );
		} else {
			
			MOAIGameSparksIOS::Get ().LogEventFailResponse ( @"" );
		}
    }];
    [[ GS gs ] send:request ];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestRegistration
	@text	Request Registration.
				
	@in 	string	displayName		A display name to use
	@in 	string	password		The previously registered password
	@opt 	JSON	segments		An optional segment configuration for this request.
	@in 	string	userName 		The previously registered player name
	@out 	nil
*/
int	MOAIGameSparksIOS::_requestRegistration ( lua_State* L ) {

	MOAILuaState state ( L );

	cc8* displayName = state.GetValue < cc8* >( 1, 0 );
	cc8* password = state.GetValue < cc8* >( 2, 0 );
	cc8* userName = state.GetValue < cc8* >( 3, 0 );

	GSRegistrationRequest* request = [[ GSRegistrationRequest alloc ] init ];
    [ request setDisplayName:[ NSString stringWithUTF8String:displayName ]];
    [ request setPassword:[ NSString stringWithUTF8String:password ]];
    //[ request setSegments:segments ];
    [ request setUserName:[ NSString stringWithUTF8String:userName ]];
    [ request setCallback:^ ( GSRegistrationResponse* response ) {
	    NSString* authToken = [ response getAuthToken ]; 
	    NSString* displayName = [ response getDisplayName ]; 
	    BOOL newPlayer = [ response getNewPlayer ]; 
	    NSDictionary* scriptData = [ response getScriptData ]; 
	    GSPlayer* switchSummary = [ response getSwitchSummary ]; 
	    NSString* userId = [ response getUserId ];
		NSDictionary* errors = [ response getErrors ];

		if ( !errors ) {
			
			MOAIGameSparksIOS::Get ().RegistrationSuccessResponse ( authToken, displayName, newPlayer, userId );
		} else {
			
			MOAIGameSparksIOS::Get ().RegistrationFailResponse ([ errors objectForKey:@"USERNAME" ]);
		}
    }];
    [[ GS gs ] send:request ];

	return 0;
}


//================================================================//
// MOAIGameSparksIOS
//================================================================//

//----------------------------------------------------------------//
void MOAIGameSparksIOS::AuthenticationFailResponse ( NSString *error ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_AUTHENTICATE_FAIL, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::AuthenticationSuccessResponse ( NSString *authToken, NSString *displayName, bool newPlayer, NSString *userId ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_AUTHENTICATE_SUCCESS, state )) {
		
		OBJC_TO_LUA ( authToken, state );
		OBJC_TO_LUA ( displayName, state );
		state.Push ( newPlayer );
		OBJC_TO_LUA ( userId, state );
		state.DebugCall ( 4, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::AvailabilityResponse ( bool available ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_AVAILABILITY, state )) {
		
		state.Push ( available );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::AccountDetailsFailResponse ( NSString *error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_GET_ACCOUNT_DETAILS_FAIL, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::AccountDetailsSuccessResponse ( NSString *displayName, NSString *userId ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_GET_ACCOUNT_DETAILS_SUCCESS, state )) {

		OBJC_TO_LUA ( displayName, state );
		OBJC_TO_LUA ( userId, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::BuyVirtualGoodFailResponse ( NSString *error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_BUY_VIRTUAL_GOOD_FAIL, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::BuyVirtualGoodSuccessResponse ( NSString *boughtItems ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_BUY_VIRTUAL_GOOD_SUCCESS, state )) {

		OBJC_TO_LUA ( boughtItems, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::FacebookConnectFailResponse ( NSString *accessToken, NSString *code, NSString *authentication ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FACEBOOK_CONNECT_FAIL, state )) {
		
		OBJC_TO_LUA ( accessToken, state );
		OBJC_TO_LUA ( code, state );
		OBJC_TO_LUA ( authentication, state );
		state.DebugCall ( 3, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::FacebookConnectSuccessResponse ( NSString *authToken, NSString *displayName, bool newPlayer, NSString *userId ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FACEBOOK_CONNECT_SUCCESS, state )) {
		
		OBJC_TO_LUA ( authToken, state );
		OBJC_TO_LUA ( displayName, state );
		state.Push ( newPlayer );
		OBJC_TO_LUA ( userId, state );
		state.DebugCall ( 4, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::LogEventFailResponse ( NSString *error ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_LOG_EVENT_FAIL, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::LogEventSuccessResponse ( NSString *eventKey, NSMutableDictionary* attributes, GSLogEventResponse* response ) {
	
	ZLLog::LogF ( 1, ZLLog::CONSOLE, "LogEventSuccessResponse\n" );

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_LOG_EVENT_SUCCESS, state )) {
		
		OBJC_TO_LUA ( eventKey, state );
		
		lua_newtable ( state );

		for ( NSObject *aKey in [ attributes allKeys ]) {

			ZLLog::LogF ( 1, ZLLog::CONSOLE, "LogEventSuccessResponse\n", aKey );
			
			NSString* attribute = [ response getAttribute:aKey ];
			
			if ( attribute ) {

				lua_newtable ( state );

				state.SetField ( -1, (cc8 *)eventKey, [ attribute UTF8String ]);

				lua_settable ( state, -3 );
			} else {

				//TODO
			}
		}
		
		state.DebugCall ( 2, 0 );
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

	state.SetField ( -1, "ON_AUTHENTICATE_FAIL",			( u32 )ON_AUTHENTICATE_FAIL );
	state.SetField ( -1, "ON_AUTHENTICATE_SUCCESS",			( u32 )ON_AUTHENTICATE_SUCCESS );
	state.SetField ( -1, "ON_AVAILABILITY",					( u32 )ON_AVAILABILITY );
	state.SetField ( -1, "ON_BUY_VIRTUAL_GOOD_FAIL",		( u32 )ON_BUY_VIRTUAL_GOOD_FAIL );
	state.SetField ( -1, "ON_BUY_VIRTUAL_GOOD_SUCCESS",		( u32 )ON_BUY_VIRTUAL_GOOD_SUCCESS );
	state.SetField ( -1, "ON_FACEBOOK_CONNECT_FAIL",		( u32 )ON_FACEBOOK_CONNECT_FAIL );
	state.SetField ( -1, "ON_FACEBOOK_CONNECT_SUCCESS",		( u32 )ON_FACEBOOK_CONNECT_SUCCESS );
	state.SetField ( -1, "ON_GET_ACCOUNT_DETAILS_FAIL",		( u32 )ON_GET_ACCOUNT_DETAILS_FAIL );
	state.SetField ( -1, "ON_GET_ACCOUNT_DETAILS_SUCCESS",	( u32 )ON_GET_ACCOUNT_DETAILS_SUCCESS );
	state.SetField ( -1, "ON_LOG_EVENT_FAIL",				( u32 )ON_LOG_EVENT_FAIL );
	state.SetField ( -1, "ON_LOG_EVENT_SUCCESS",			( u32 )ON_LOG_EVENT_SUCCESS );
	state.SetField ( -1, "ON_REGISTRATION_FAIL",			( u32 )ON_REGISTRATION_FAIL );
	state.SetField ( -1, "ON_REGISTRATION_SUCCESS",			( u32 )ON_REGISTRATION_SUCCESS );

	luaL_Reg regTable [] = {
		{ "init",						_init },
		{ "getListener",				&MOAIGlobalEventSource::_getListener < MOAIGameSparksIOS > },
		{ "requestAccountDetails",		_requestAccountDetails },
		{ "requestAuthentication",		_requestAuthentication },
		{ "requestBuyGoods",			_requestBuyGoods },
		{ "requestFacebookConnect",		_requestFacebookConnect },
		{ "requestLogEvent",			_requestLogEvent },
		{ "requestRegistration",		_requestRegistration },
		{ "setListener",				&MOAIGlobalEventSource::_setListener < MOAIGameSparksIOS > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}


//----------------------------------------------------------------//
void MOAIGameSparksIOS::RegistrationFailResponse ( NSString *error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_REGISTRATION_FAIL, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::RegistrationSuccessResponse ( NSString *authToken, NSString *displayName, bool newPlayer, NSString *userId ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_REGISTRATION_SUCCESS, state )) {

		OBJC_TO_LUA ( authToken, state );
		OBJC_TO_LUA ( displayName, state );
		state.Push ( newPlayer );
		OBJC_TO_LUA ( userId, state );
		state.DebugCall ( 4, 0 );
	}
}

