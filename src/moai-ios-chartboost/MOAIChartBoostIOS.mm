//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-chartboost/MOAIChartBoostIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	cacheInterstitial
	@text	Request that an interstitial ad be cached for later display.
	
	@out 	nil
*/
int MOAIChartBoostIOS::_cacheInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );
	[ Chartboost cacheInterstitial:CBLocationDefault ];
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	cacheRewardedVideo
	@text	Request that an interstitial ad be cached for later display.
	
	@out 	nil
*/
int MOAIChartBoostIOS::_cacheRewardedVideo ( lua_State* L ) {
	
	MOAILuaState state ( L );
	[ Chartboost cacheRewardedVideo:CBLocationDefault ];
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	hasCachedInterstitial
 @text	returns whether a cached ad is available
 
 @out 	bool	True, if an ad is cached.
 */
int MOAIChartBoostIOS::_hasCachedInterstitial ( lua_State* L ) {
	MOAILuaState state ( L );
	
	bool isAdAvailable = [ Chartboost hasInterstitial:CBLocationDefault ];
	
	lua_pushboolean ( state, isAdAvailable );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	hasRewardedVideo
	@text	returns whether a cached ad is available
 
	@out 	bool	True, if an ad is cached.
*/
int MOAIChartBoostIOS::_hasRewardedVideo ( lua_State* L ) {
	MOAILuaState state ( L );
	
	bool isAdAvailable = [ Chartboost hasRewardedVideo:CBLocationDefault ];
	
	lua_pushboolean ( state, isAdAvailable );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize ChartBoost.
	
	@in		string	appId			Available in ChartBoost dashboard settings.
	@in 	string	appSignature	Available in ChartBoost dashboard settings.
	@out 	nil
*/
int MOAIChartBoostIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* identifier = lua_tostring ( state, 1 );
	cc8* signature = lua_tostring ( state, 2 );
	
	[ Chartboost startWithAppId: [ NSString stringWithUTF8String:identifier ]
		appSignature: [ NSString stringWithUTF8String:signature ]
		delegate: MOAIChartBoostIOS::Get ().mDelegate ];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	showInterstitial
	@text	Request an interstitial ad display if a cached ad is available.
	
	@out 	bool					True, if an ad is cached and will be displayed.
*/
int MOAIChartBoostIOS::_showInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	if ([ Chartboost hasInterstitial:CBLocationDefault ]) {
		[ Chartboost showInterstitial:CBLocationDefault ];
		lua_pushboolean ( state, true );
		return 1;
	}
	lua_pushboolean ( state, false );
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	showRewardedVideo
	@text	Request an interstitial ad display if a cached ad is available.
	
	@out 	bool					True, if an ad is cached and will be displayed.
*/
int MOAIChartBoostIOS::_showRewardedVideo ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	if ([ Chartboost hasRewardedVideo:CBLocationDefault ]) {
		[ Chartboost showRewardedVideo:CBLocationDefault ];
		lua_pushboolean ( state, true );
		return 1;
	}
	lua_pushboolean ( state, false );
	return 1;
}


//================================================================//
// MOAIChartBoostIOS
//================================================================//

//----------------------------------------------------------------//
MOAIChartBoostIOS::MOAIChartBoostIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )

	mDelegate = [[ MoaiChartBoostDelegate alloc ] init ];
}

//----------------------------------------------------------------//
MOAIChartBoostIOS::~MOAIChartBoostIOS () {

	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIChartBoostIOS::NotifyRewardedVideoCompleted ( int reward ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->PushListener ( REWARDED_VIDEO_COMPLETED, state )) {
		state.Push ( reward );
		state.DebugCall	( 1, 0);
	}
}

//----------------------------------------------------------------//
void MOAIChartBoostIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "INTERSTITIAL_LOAD_FAILED",	( u32 )INTERSTITIAL_LOAD_FAILED );
	state.SetField ( -1, "INTERSTITIAL_DISMISSED", 		( u32 )INTERSTITIAL_DISMISSED );
	state.SetField ( -1, "REWARDED_VIDEO_DISMISSED",	( u32 )REWARDED_VIDEO_DISMISSED );
	state.SetField ( -1, "REWARDED_VIDEO_WILL_START",	( u32 )REWARDED_VIDEO_WILL_START );
	state.SetField ( -1, "REWARDED_VIDEO_COMPLETED",	( u32 )REWARDED_VIDEO_COMPLETED );

	luaL_Reg regTable [] = {
		{ "cacheInterstitial",		_cacheInterstitial },
		{ "cacheRewardedVideo",		_cacheRewardedVideo },
		{ "getListener",			&MOAIGlobalEventSource::_getListener < MOAIChartBoostIOS > },
		{ "hasCachedInterstitial",	_hasCachedInterstitial },
		{ "hasRewardedVideo",		_hasRewardedVideo },
		{ "init",					_init },
		{ "setListener",			&MOAIGlobalEventSource::_setListener < MOAIChartBoostIOS > },
		{ "showInterstitial",		_showInterstitial },
		{ "showRewardedVideo",		_showRewardedVideo },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MoaiChartBoostDelegate
//================================================================//
@implementation MoaiChartBoostDelegate

	//================================================================//
	#pragma mark -
	#pragma mark Protocol MoaiChartBoostDelegate
	//================================================================//

	//----------------------------------------------------------------//
	- ( BOOL ) shouldRequestInterstitial {
		return YES;
	}

	//----------------------------------------------------------------//
	- ( void ) didFailToLoadInterstitial {
		MOAIChartBoostIOS::Get ().InvokeListener ( MOAIChartBoostIOS::INTERSTITIAL_LOAD_FAILED );
	}

	//----------------------------------------------------------------//
	- ( BOOL ) shouldDisplayInterstitial:( CBLocation )location {
		UNUSED ( location );
		return YES;
	}

	//----------------------------------------------------------------//
	- ( void ) didDismissInterstitial:( CBLocation )location {
		UNUSED ( location );
		MOAIChartBoostIOS::Get ().InvokeListener ( MOAIChartBoostIOS::INTERSTITIAL_DISMISSED );
	}

	//----------------------------------------------------------------//
	- ( BOOL ) shouldDisplayMoreApps:( CBLocation )location {
		UNUSED ( location );
		return NO;
	}

	//----------------------------------------------------------------//
	- (void)didDisplayRewardedVideo:( CBLocation )location {
		UNUSED ( location );
		MOAIChartBoostIOS::Get ().InvokeListener ( MOAIChartBoostIOS::REWARDED_VIDEO_WILL_START );
	}

	//----------------------------------------------------------------//
	- (void)didDismissRewardedVideo:( CBLocation )location {
		UNUSED ( location );
		MOAIChartBoostIOS::Get ().InvokeListener ( MOAIChartBoostIOS::REWARDED_VIDEO_DISMISSED );
	}

	//----------------------------------------------------------------//
	- (void)didCompleteRewardedVideo:( CBLocation )location withReward:( int )reward {
		UNUSED ( location );
		MOAIChartBoostIOS::Get ().NotifyRewardedVideoCompleted ( reward );
	}

@end
