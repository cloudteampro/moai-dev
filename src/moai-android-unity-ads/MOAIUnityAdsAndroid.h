//----------------------------------------------------------------//
// Copyright (c) 2015 CloudTeam All Rights Reserved.
// http://cloudteam.pro

#ifndef MOAIUNITYADSANDROID_H
#define MOAIUNITYADSANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIUnityAdsAndroid
//================================================================//
/**	@name	MOAIUnityAdsAndroid
 @text	Wrapper for FlurryAds integration on Android devices.
 Flurry provides analytics and behaviour statistics. 
 Exposed to lua via MOAIFlurryAds on 
 all mobile platforms.
 
 */
class MOAIUnityAdsAndroid :
	public MOAIGlobalClass < MOAIUnityAdsAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:
	
	jmethodID	mJava_CanShow;
	jmethodID	mJava_Init;
	jmethodID	mJava_Show;

	//----------------------------------------------------------------//
	static int	_canShow						( lua_State* L );
	static int	_init							( lua_State* L );
	static int	_show							( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIUnityAdsAndroid );

	enum {
		UNITYADS_READY,
		UNITYADS_START,
		UNITYADS_FINISH,
		UNITYADS_ERROR
	};

					MOAIUnityAdsAndroid				();
					~MOAIUnityAdsAndroid			();
	void			NotifyVideoFinished				( u32 result );
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIUNITYADSANDROID_H
