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
	
	jmethodID	mJava_Init;
	jmethodID	mJava_LoadAd;
	jmethodID	mJava_ShowAd;
	jmethodID	mJava_HasCachedAd;
	jmethodID	mJava_SetAdSpace;

	//----------------------------------------------------------------//
	static int	_init 								( lua_State* L );
	static int	_loadAd			 					( lua_State* L );
	static int	_showAd			 					( lua_State* L );
	static int	_hasCachedAd		 				( lua_State* L );
	static int	_setAdSpace			 				( lua_State* L );

public:
    
	DECL_LUA_SINGLETON ( MOAIUnityAdsAndroid );

	enum {
		AD_LOAD_FAILED,
		AD_WILL_SHOW,
		AD_DISMISSED,
	};

					MOAIUnityAdsAndroid				();
					~MOAIUnityAdsAndroid			();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIFLURRYADS_H
