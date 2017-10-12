//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIADTOAPPIOS_H
#define MOAIADTOAPPIOS_H

#include <moai-core/headers.h>

@class MOAIAdToAppDelegate;

//================================================================//
// MOAIAdToAppIOS
//================================================================//
class MOAIAdToAppIOS :
	public MOAIGlobalClass < MOAIAdToAppIOS, MOAILuaObject >,
	public MOAIGlobalEventSource {
private:

	MOAIAdToAppDelegate*				mDelegate;
	
	//----------------------------------------------------------------//
	static int	_hasInterstitial		( lua_State* L );
	static int	_hideInterstitial		( lua_State* L );
	static int	_init					( lua_State* L );
	static int	_isInterstitialVisible	( lua_State* L );
	static int	_showInterstitial		( lua_State* L );
	
public:

	enum {
		AD_APPEAR,
		AD_DISAPPEAR,
		AD_REWARD
	};

	DECL_LUA_SINGLETON ( MOAIAdToAppIOS );
	
    MOAIAdToAppIOS				();
	~MOAIAdToAppIOS			();
	
	void	NotifyAdAppear 				( cc8* adType );
	void	NotifyAdDisappear 			( cc8* adType );
	void	NotifyAdReward 				( int reward, cc8* currency );

	void	RegisterLuaClass			( MOAILuaState& state );
};



#endif // MOAIADTOAPP_H
