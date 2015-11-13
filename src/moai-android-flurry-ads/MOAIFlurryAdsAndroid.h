//----------------------------------------------------------------//
// Copyright (c) 2015 CloudTeam All Rights Reserved.
// http://cloudteam.pro

#ifndef MOAIFLURRYADSANDROID_H
#define MOAIFLURRYADSANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIFlurryAdsAndroid
//================================================================//
/**	@name	MOAIFlurryAdsAndroid
 @text	Wrapper for FlurryAds integration on Android devices.
 Flurry provides analytics and behaviour statistics. 
 Exposed to lua via MOAIFlurryAds on 
 all mobile platforms.
 
 */
class MOAIFlurryAdsAndroid :
	public MOAIGlobalClass < MOAIFlurryAdsAndroid, MOAIGlobalEventSource >,
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
    
	DECL_LUA_SINGLETON ( MOAIFlurryAdsAndroid );

	enum {
		AD_LOAD_FAILED,
		AD_WILL_SHOW,
		AD_DISMISSED,
	};

					MOAIFlurryAdsAndroid			();
					~MOAIFlurryAdsAndroid			();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIFLURRYADS_H
