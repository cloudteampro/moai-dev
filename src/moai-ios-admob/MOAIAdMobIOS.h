//----------------------------------------------------------------//
// Copyright (c) 2015 CloudTeam All Rights Reserved.
// http://cloudteam.pro

#ifndef MOAIADMOBIOS_H
#define MOAIADMOBIOS_H

#include <moai-core/headers.h>

#import <GADMobileAds.h>
#import <GADRewardBasedVideoAdDelegate.h>

@class MOAIAdMobIOSDelegate;

//================================================================//
// MOAIAdMobIOS
//================================================================//
class MOAIAdMobIOS :
	public MOAIGlobalClass < MOAIAdMobIOS, MOAIGlobalEventSource > {
private:
	
	MOAIAdMobIOSDelegate*		mDelegate;
	
	//----------------------------------------------------------------//
	static int	_show							( lua_State* L );
	static int	_init							( lua_State* L );
	static int	_isLoaded						( lua_State* L );
	static int	_loadAd							( lua_State* L );
	
public:

	DECL_LUA_SINGLETON ( MOAIAdMobIOS );
	
	enum {
		ADMOB_READY,
		ADMOB_START,
		ADMOB_FINISH,
		ADMOB_ERROR,
		ADMOB_CLOSED,
	};
	
			MOAIAdMobIOS				();
			~MOAIAdMobIOS			();
	void	NotifyVideoFinished			( u32 result );
	void	RegisterLuaClass			( MOAILuaState& state );
};

//================================================================//
// MOAIAdMobIOSDelegate
//================================================================//
@interface MOAIAdMobIOSDelegate : NSObject < GADRewardBasedVideoAdDelegate > {
@private
}
@end


#endif // MOAIUNITYADSIOS_H
