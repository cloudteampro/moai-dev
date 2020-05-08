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

	if (![[ GADRewardBasedVideoAd sharedInstance ] isReady ]) {

		NSLog ( @"MOAIAdMobIOS: GADRewardBasedVideoAd: not ready" );
		state.Push ( false );
		return 1;
	}

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];

	if ([[ GADRewardBasedVideoAd sharedInstance ] isReady ]) {

		NSLog ( @"MOAIAdMobIOS: GADRewardBasedVideoAd: presentFromRootViewController" );

		state.Push ( true );
	  	[[ GADRewardBasedVideoAd sharedInstance ] presentFromRootViewController:rootVC ];
		return 1;
	}

	NSLog ( @"MOAIAdMobIOS: GADRewardBasedVideoAd: failed to show" );
	
	state.Push ( false );

	return 1;
}

//----------------------------------------------------------------//
/** TODO
 
 */
int MOAIAdMobIOS::_showInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	if (!MOAIAdMobIOS::Get ().mInterstitial.isReady) {
		
		NSLog ( @"MOAIAdMobIOS: GADInterstitial: not ready" );
		state.Push ( false );
		return 1;
	}
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	
	if (MOAIAdMobIOS::Get ().mInterstitial.isReady) {
		
		NSLog ( @"MOAIAdMobIOS: GADInterstitial: presentFromRootViewController" );
		
		state.Push ( true );
		[ MOAIAdMobIOS::Get ().mInterstitial presentFromRootViewController:rootVC ];
		return 1;
	}
	
	NSLog ( @"MOAIAdMobIOS: GADInterstitial: failed to show" );
	
	state.Push ( false );
	
	return 1;
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
/** TODO
 
 */
int MOAIAdMobIOS::_isInterstitialLoaded ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	bool isLoaded = MOAIAdMobIOS::Get ().mInterstitial.isReady;
	
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

	if ([[ GADRewardBasedVideoAd sharedInstance ] isReady ]) {
		return 0;
	}
	
	cc8* unitID = state.GetValue < cc8* >( 1, "" );

	[[ GADRewardBasedVideoAd sharedInstance ] loadRequest:[GADRequest request] withAdUnitID:[ NSString stringWithUTF8String:unitID ]];

	return 0;
}

//----------------------------------------------------------------//
/** @name   init
 @text   Load interstitial video AdMob.
 
 @in     string  unitID      Your unit id
 @out    nil
 */
int MOAIAdMobIOS::_loadInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	if (MOAIAdMobIOS::Get ().mInterstitial.isReady) {
		return 0;
	}
	
	cc8* unitID = state.GetValue < cc8* >( 1, "" );
	
	[MOAIAdMobIOS::Get ().mInterstitial initWithAdUnitID:[ NSString stringWithUTF8String:unitID ]];
	GADRequest *request = [GADRequest request];
	[MOAIAdMobIOS::Get ().mInterstitial loadRequest:request];
	
	return 0;
}
	
//================================================================//
// MOAIAdMobIOS
//================================================================//

//----------------------------------------------------------------//
MOAIAdMobIOS::MOAIAdMobIOS () {
	
	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	mDelegate = [[ MOAIAdMobIOSDelegate alloc ] init];
	mInterstitial = [GADInterstitial alloc];
}

//----------------------------------------------------------------//
MOAIAdMobIOS::~MOAIAdMobIOS () {
	
	[ mDelegate release ];
	[ mInterstitial release ];
}

//----------------------------------------------------------------//
void MOAIAdMobIOS::NotifyVideoFinished ( u32 result ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ADMOB_REWARDED_FINISH, state )) {
		
		state.Push ( result );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAdMobIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "ADMOB_READY",				( u32 )ADMOB_READY );
	state.SetField ( -1, "ADMOB_OPENED",			( u32 )ADMOB_OPENED );
	state.SetField ( -1, "ADMOB_ERROR",				( u32 )ADMOB_ERROR );
	state.SetField ( -1, "ADMOB_CLOSED",			( u32 )ADMOB_CLOSED );
	state.SetField ( -1, "ADMOB_REWARDED_READY",	( u32 )ADMOB_REWARDED_READY );
	state.SetField ( -1, "ADMOB_REWARDED_START",	( u32 )ADMOB_REWARDED_START );
	state.SetField ( -1, "ADMOB_REWARDED_FINISH",	( u32 )ADMOB_REWARDED_FINISH );
	state.SetField ( -1, "ADMOB_REWARDED_ERROR",	( u32 )ADMOB_REWARDED_ERROR );
	state.SetField ( -1, "ADMOB_REWARDED_CLOSED",	( u32 )ADMOB_REWARDED_CLOSED );
	
	luaL_Reg regTable [] = {
		{ "isLoaded",						_isLoaded },
		{ "isInterstitialLoaded",			_isInterstitialLoaded },
		{ "loadInterstitial",				_loadInterstitial },
		{ "loadAd",							_loadAd },
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIAdMobIOS > },
		{ "init",							_init },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIAdMobIOS > },
		{ "show",							_show },
		{ "showInterstitial",				_showInterstitial },
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
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_REWARDED_READY );
	}

	- ( void ) rewardBasedVideoAdDidOpen: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidOpen: Opened reward based video ad." );
	}

	- ( void ) rewardBasedVideoAdDidStartPlaying: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidStartPlaying: Reward based video ad started playing." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_REWARDED_START );
	}

	- ( void ) rewardBasedVideoAdDidCompletePlaying: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidCompletePlaying: Reward based video ad has completed." );
		// MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_REWARDED_FINISH );
	}

	- ( void ) rewardBasedVideoAdDidClose: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {

		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidClose: Reward based video ad is closed." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_REWARDED_CLOSED );
	}

	- ( void ) rewardBasedVideoAdWillLeaveApplication: ( GADRewardBasedVideoAd * ) rewardBasedVideoAd {
		
		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdWillLeaveApplication: Reward based video ad will leave application." );
	}

	- ( void ) rewardBasedVideoAd: (  GADRewardBasedVideoAd * ) rewardBasedVideoAd didFailToLoadWithError:( NSError * )error {
		NSLog ( @"MOAIAdMobIOS: didFailToLoadWithError: Reward based video ad failed to load." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_REWARDED_ERROR );
	}

	- ( void ) interstitialDidReceiveAd: ( GADInterstitial * ) ad {
		
		NSLog ( @"MOAIAdMobIOS: interstitialDidReceiveAd: Interstitial based video ad is received." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_READY );
	}

	- ( void ) interstitial: ( GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error {
		NSLog ( @"MOAIAdMobIOS: didFailToReceiveAdWithError: Interstitial based video ad failed to load." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_ERROR );
	}

	/// Tells the delegate that an interstitial will be presented.
	- ( void ) interstitialWillPresentScreen:(GADInterstitial *)ad {
		
		NSLog ( @"MOAIAdMobIOS: rewardBasedVideoAdDidStartPlaying: Interstitial based video ad started playing." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_OPENED );
	}

	/// Tells the delegate the interstitial is to be animated off the screen.
	- ( void ) interstitialWillDismissScreen:(GADInterstitial *)ad {
		NSLog(@"interstitialWillDismissScreen");
	}

	/// Tells the delegate the interstitial had been animated off the screen.
	- ( void ) interstitialDidDismissScreen:(GADInterstitial *)ad {
		
		NSLog ( @"MOAIAdMobIOS: interstitialDidDismissScreen: Interstitial based video ad is closed." );
		MOAIAdMobIOS::Get ().InvokeListener ( MOAIAdMobIOS::ADMOB_CLOSED );
	}

	/// Tells the delegate that a user click will open another app
	/// (such as the App Store), backgrounding the current app.
	- ( void ) interstitialWillLeaveApplication:(GADInterstitial *)ad {
		NSLog(@"interstitialWillLeaveApplication");
	}

@end
