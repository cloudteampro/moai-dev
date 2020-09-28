//----------------------------------------------------------------//
// Copyright (c) 2015 CloudTeam All Rights Reserved.
// http://cloudteam.pro

#ifndef MOAIADMOBIOS_H
#define MOAIADMOBIOS_H

#include <moai-core/headers.h>
#include <moai-ios/headers.h>

#import <GoogleMobileAds/GoogleMobileAds.h>

@class MOAIAdMobIOSDelegate;

//================================================================//
// MOAIAdMobIOS
//================================================================//
class MOAIAdMobIOS :
	public MOAIGlobalClass < MOAIAdMobIOS, MOAIGlobalEventSource > {
private:
	
	MOAIAdMobIOSDelegate*		mDelegate;
	GADInterstitial*			mInterstitial;
	
	//----------------------------------------------------------------//
	static int	_show							( lua_State* L );
	static int	_showInterstitial				( lua_State* L );
	static int	_init							( lua_State* L );
	static int	_isLoaded						( lua_State* L );
	static int	_isInterstitialLoaded			( lua_State* L );
	static int	_loadAd							( lua_State* L );
	static int	_loadInterstitial				( lua_State* L );
	
public:

	DECL_LUA_SINGLETON ( MOAIAdMobIOS );
	
	enum {
		ADMOB_INITIALIZED_SUCCESSULLY,
		ADMOB_INITIALIZED_FAILED,
		ADMOB_READY,
		ADMOB_OPENED,
		ADMOB_ERROR,
		ADMOB_CLOSED,
		ADMOB_REWARDED_READY,
		ADMOB_REWARDED_START,
		ADMOB_REWARDED_FINISH,
		ADMOB_REWARDED_ERROR,
		ADMOB_REWARDED_CLOSED,
	};
	
	NSMutableDictionary* 		mRewardedAds;
		
			MOAIAdMobIOS				();
			~MOAIAdMobIOS				();
	void	NotifyVideoFinished			( u32 result );
	void	NotifyVideoClosed			( NSString* placementName );
	void	RegisterLuaClass			( MOAILuaState& state );
};

//================================================================//
// MOAIAdMobIOSDelegate
//================================================================//
@interface MOAIAdMobIOSDelegate : NSObject < GADRewardedAdDelegate, GADInterstitialDelegate > {
@private
}
@end


#endif // MOAIUNITYADSIOS_H
