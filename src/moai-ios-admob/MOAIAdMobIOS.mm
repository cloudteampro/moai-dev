//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-admob/MOAIAdMobIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/** TODO

*/
int MOAIAdMobIOS::_show ( lua_State* L ) {

	MOAILuaState state ( L );

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];

	if ([[ GADRewardBasedVideoAd sharedInstance ] isReady ]) {
	  [[ GADRewardBasedVideoAd sharedInstance ] presentFromRootViewController:rootVC ];
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO

*/
int MOAIAdMobIOS::_isLoaded ( lua_State* L ) {

	MOAILuaState state ( L );

	bool isLoaded = [[ GADRewardBasedVideoAd sharedInstance ] isReady ];

	state.Push ( isLoaded );

	return 1;
}

//----------------------------------------------------------------//
/** @name   init
	@text   Initialize AdMob.
	
	@in     string  gameId      Your game id
	@out    nil
*/
int MOAIAdMobIOS::_init ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* appID = state.GetValue < cc8* >( 1, "" );
	
	[ GADMobileAds configureWithApplicationID:[ NSString stringWithUTF8String:appID ]];

	[ GADRewardBasedVideoAd sharedInstance ].delegate = MOAIAdMobIOS::Get ().mDelegate;

	return 0;
}

//----------------------------------------------------------------//
/** @name   init
	@text   Load rewarded video AdMob.
	
	@in     string  unitID      Your unit id
	@out    nil
*/
int MOAIAdMobIOS::_loadAd ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* unitID = state.GetValue < cc8* >( 1, "" );

	[[ GADRewardBasedVideoAd sharedInstance ] loadRequest:[GADRequest request] withAdUnitID:[ NSString stringWithUTF8String:unitID ]];

	return 0;
}
	
//================================================================//
// MOAIAdMobIOS
//================================================================//

//----------------------------------------------------------------//
MOAIAdMobIOS::MOAIAdMobIOS () {
	
	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	mDelegate = [[ MOAIAdMobIOSDelegate alloc ] init];
}

//----------------------------------------------------------------//
MOAIAdMobIOS::~MOAIAdMobIOS () {
	
	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIAdMobIOS::NotifyVideoFinished ( u32 result ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ADMOB_FINISH, state )) {
		
		state.Push ( result );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAdMobIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "ADMOB_READY",			( u32 )ADMOB_READY );
	state.SetField ( -1, "ADMOB_START",			( u32 )ADMOB_START );
	state.SetField ( -1, "ADMOB_FINISH",		( u32 )ADMOB_FINISH );
	state.SetField ( -1, "ADMOB_ERROR",			( u32 )ADMOB_ERROR );
	state.SetField ( -1, "ADMOB_CLOSED",		( u32 )ADMOB_CLOSED );
	
	luaL_Reg regTable [] = {
		{ "isLoaded",						_isLoaded },
		{ "loadAd",							_loadAd },
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIAdMobIOS > },
		{ "init",							_init },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIAdMobIOS > },
		{ "show",							_show },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MOAIAdMobIOSDelegate
//================================================================//
@implementation MOAIAdMobIOSDelegate

	- ( void ) rewardBasedVideoAd: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd 
		didRewardUserWithReward: ( GADAdReward * ) reward {

		NSLog ( @"MOAIAdMobIOS: didRewardUserWithReward: didRewardUserWithReward" );

		MOAIAdMobIOS::Get ().NotifyVideoFinished ( 1 );
	}

	- ( void ) rewardBasedVideoAdDidReceiveAd: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidReceiveAd: Reward based video ad is received." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_READY );
	}

	- ( void ) rewardBasedVideoAdDidOpen: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidOpen: Opened reward based video ad." );
	}

	- ( void ) rewardBasedVideoAdDidStartPlaying: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidStartPlaying: Reward based video ad started playing." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_START );
	}

	- ( void ) rewardBasedVideoAdDidCompletePlaying: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidCompletePlaying: Reward based video ad has completed." );
		// MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_FINISH );
	}

	- ( void ) rewardBasedVideoAdDidClose: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidClose: Reward based video ad is closed." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_CLOSED );
	}

	- ( void ) rewardBasedVideoAdWillLeaveApplication: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {
		
		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdWillLeaveApplication: Reward based video ad will leave application." );
	}

	- ( void ) rewardBasedVideoAd: (  GADRewardBasedVideoAd * ) rewardBasedVideoAd
	    didFailToLoadWithError:( NSError * )error {
		NSLog ( @"MOAIAdMobIOS: didFailToLoadWithError: Reward based video ad failed to load." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_ERROR );
	}

@end
