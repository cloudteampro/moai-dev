//----------------------------------------------------------------//
// Copyright (c) 2015 CloudTeam All Rights Reserved.
// http://cloudteam.pro

#ifndef MOAIADMOBANDROID_H
#define MOAIADMOBANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIAdMobAndroid
//================================================================//

class MOAIAdMobAndroid :
	public MOAIGlobalClass < MOAIAdMobAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:
	
	jmethodID	mJava_Show;
	jmethodID	mJava_ShowInterstitial;
	jmethodID	mJava_Init;
	jmethodID	mJava_IsLoaded;
	jmethodID	mJava_IsInterstitialLoaded;
	jmethodID	mJava_LoadAd;
	jmethodID	mJava_LoadInterstitial;

	//----------------------------------------------------------------//
	static int	_show							( lua_State* L );
	static int	_showInterstitial				( lua_State* L );
	static int	_init							( lua_State* L );
	static int	_isLoaded						( lua_State* L );
	static int	_isInterstitialLoaded			( lua_State* L );
	static int	_loadAd							( lua_State* L );
	static int	_loadInterstitial				( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIAdMobAndroid );

	enum {
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

					MOAIAdMobAndroid				();
					~MOAIAdMobAndroid				();
	void			NotifyVideoFinished				( int result );
	void			NotifyVideoClosed				( cc8* placementName );
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIUNITYADSANDROID_H
