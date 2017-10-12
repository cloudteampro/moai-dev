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
	public ZLContextClass < MOAIUnityAdsAndroid, MOAIGlobalEventSource >,
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
		ON_HIDE,
		ON_SHOW,
		VIDEO_COMPLETED,
		VIDEO_STARTED,
	};

					MOAIUnityAdsAndroid				();
					~MOAIUnityAdsAndroid			();
	void			NotifyVideoCompleted			( cc8* reward, bool skipped );
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIUNITYADSANDROID_H
