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
	jmethodID	mJava_Init;
	jmethodID	mJava_IsLoaded;
	jmethodID	mJava_LoadAd;

	//----------------------------------------------------------------//
	static int	_show							( lua_State* L );
	static int	_init							( lua_State* L );
	static int	_isLoaded						( lua_State* L );
	static int	_loadAd							( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIAdMobAndroid );

	enum {
		ADMOB_READY,
		ADMOB_START,
		ADMOB_FINISH,
		ADMOB_ERROR,
		ADMOB_CLOSED,
	};

					MOAIAdMobAndroid				();
					~MOAIAdMobAndroid				();
	void			NotifyVideoFinished				( int result );
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIUNITYADSANDROID_H
