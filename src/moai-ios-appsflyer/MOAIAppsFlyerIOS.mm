//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

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
void MOAIAppsFlyerIOS::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",					_init },
		{ "trackEvent",				_trackEvent },
		{ "trackLevelAchieved",		_trackLevelAchieved },
		{ "trackPurchase",			_trackPurchase },
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