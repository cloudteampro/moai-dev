//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios/headers.h>
#import <moai-ios-appsflyer/MOAIAppsFlyerIOS.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize AppsFlyer.
	
	@in 	string	devKey			AppsFlyer account Dev Key.
	@in		string	appId			AppStore app id.
	@out 	nil
*/
int MOAIAppsFlyerIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* devKey = state.GetValue < cc8* >( 1, 0 );
	cc8* appId = state.GetValue < cc8* >( 2, 0 );
	bool isDebug = state.GetValue < bool >( 3, false );

	[AppsFlyerTracker sharedTracker].appsFlyerDevKey = [ NSString stringWithUTF8String:devKey ];
	[AppsFlyerTracker sharedTracker].appleAppID = [ NSString stringWithUTF8String:appId ];
	[AppsFlyerTracker sharedTracker].delegate = MOAIAppsFlyerIOS::Get ().mDelegate;
	[AppsFlyerTracker sharedTracker].isDebug = isDebug;

	if ( isDebug ) {
		[AppsFlyerTracker sharedTracker].useReceiptValidationSandbox = YES;
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackAdView
 @text	Tracking Event Ad Show.
 
 @out 	nil
 */
int	MOAIAppsFlyerIOS::_trackAdView ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* placement = state.GetValue < cc8* >( 1, 0 );
	
	[[ AppsFlyerTracker sharedTracker ] trackEvent: AFEventAdView withValues: @{
		AFEventParamAdRevenuePlacementId: [ NSString stringWithUTF8String:placement ]
	}];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackEvent
	@text	Tracking Event.
	
	@out 	nil
*/
int	MOAIAppsFlyerIOS::_trackEvent ( lua_State* L ) {

	// [[AppsFlyerTracker sharedTracker] trackEvent: AFEventLevelAchieved withValues:@{
 //        AFEventParamContentId:@"1234567",
 //        AFEventParamContentType : @"category_a",
 //        AFEventParamRevenue: @1.99,
 //        AFEventParamCurrency:@"USD"
 //    }];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackLevelAchieved
	@text	Tracking Event Level Achieved.
	
	@out 	nil
*/
int	MOAIAppsFlyerIOS::_trackLevelAchieved ( lua_State* L ) {
	MOAILuaState state ( L );

	int level = state.GetValue < int >( 1, 0 );

	[[ AppsFlyerTracker sharedTracker ] trackEvent: AFEventLevelAchieved withValues: @{
		AFEventParamLevel: [ NSNumber numberWithInt:level ]
	}];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackPurchase
	@text	Tracking Event Purchase.
	
	@out 	nil
*/
int	MOAIAppsFlyerIOS::_trackPurchase ( lua_State* L ) {
	MOAILuaState state ( L );
	
	float revenue = state.GetValue < float >( 1, 0.0f );
	cc8* currency = state.GetValue < cc8* >( 2, 0 );

	[[ AppsFlyerTracker sharedTracker ] trackEvent: AFEventPurchase withValues: @{
		AFEventParamRevenue: [ NSNumber numberWithFloat:revenue ],
		AFEventParamCurrency: [ NSString stringWithUTF8String:currency ]
	}];

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	validateAndTrackPurchase
 @text	Validate And Track Event Purchase.
 
 @out 	nil
 */
int	MOAIAppsFlyerIOS::_validateAndTrackInAppPurchase ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* productId = state.GetValue < cc8* >( 1, 0 );
	cc8* price = state.GetValue < cc8* >( 2, 0 );
	cc8* currency = state.GetValue < cc8* >( 3, 0 );
	cc8* transactionId = state.GetValue < cc8* >( 4, 0 );
	
	[[ AppsFlyerTracker sharedTracker ] validateAndTrackInAppPurchase:[ NSString stringWithUTF8String:productId ]
		price:[ NSString stringWithUTF8String:price ]
		currency:[ NSString stringWithUTF8String:currency ]
		transactionId:[ NSString stringWithUTF8String:transactionId ]
		additionalParameters:@{}
		success:^( NSDictionary *result ) {
			NSLog(@"Purchase succeeded And verified!!! response: %@", result[@"receipt"]);
			MOAIAppsFlyerIOS::Get ().PurchaseValidateSuccess ( result[@"receipt"] );
		}
		failure:^( NSError *error, id response ) {
			NSLog(@"response = %@", response);
			MOAIAppsFlyerIOS::Get ().PurchaseValidateFailure ( response );
		}
	];
	
	return 0;
}

//================================================================//
// MOAIAppsFlyerIOS
//================================================================//

//----------------------------------------------------------------//
MOAIAppsFlyerIOS::MOAIAppsFlyerIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )

	mDelegate = [[ MoaiAppsFlyerDelegate alloc ] init ];
}

//----------------------------------------------------------------//
MOAIAppsFlyerIOS::~MOAIAppsFlyerIOS () {

	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIAppsFlyerIOS::PurchaseValidateFailure ( NSString *error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	NSLog ( @"MOAIAppsFlyerIOS: PurchaseValidateFailure" );

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( PURCHASE_VALIDATE_FAILURE, state )) {
		
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAppsFlyerIOS::PurchaseValidateSuccess ( NSString *result ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	NSLog ( @"MOAIAppsFlyerIOS: PurchaseValidateSuccess" );

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( PURCHASE_VALIDATE_SUCCESS, state )) {

		OBJC_TO_LUA ( result, state );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAppsFlyerIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "PURCHASE_VALIDATE_FAILURE",				( u32 )PURCHASE_VALIDATE_FAILURE );
	state.SetField ( -1, "PURCHASE_VALIDATE_SUCCESS",				( u32 )PURCHASE_VALIDATE_SUCCESS );

	luaL_Reg regTable [] = {
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIAppsFlyerIOS > },
		{ "init",							_init },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIAppsFlyerIOS > },
		{ "trackAdView",					_trackAdView },
		{ "trackEvent",						_trackEvent },
		{ "trackLevelAchieved",				_trackLevelAchieved },
		{ "trackPurchase",					_trackPurchase },
		{ "validateAndTrackInAppPurchase",	_validateAndTrackInAppPurchase },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MoaiAppsFlyerDelegate
//================================================================//
@implementation MoaiAppsFlyerDelegate

	//================================================================//
	#pragma mark -
	#pragma mark Protocol MoaiAppsFlyerDelegate
	//================================================================//

@end
