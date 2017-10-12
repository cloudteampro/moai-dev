// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAICHARTBOOSTANDROID_H
#define	MOAICHARTBOOSTANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIChartBoostAndroid
//================================================================//
class MOAIChartBoostAndroid :
	public ZLContextClass < MOAIChartBoostAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_CacheInterstitial;
		jmethodID	mJava_CacheRewardedVideo;
		jmethodID	mJava_HasCachedInterstitial;
		jmethodID	mJava_HasRewardedVideo;
		jmethodID	mJava_Init;
		jmethodID	mJava_ShowInterstitial;
		jmethodID	mJava_ShowRewardedVideo;


		//----------------------------------------------------------------//
		static int	_cacheInterstitial				( lua_State* L );
		static int	_cacheRewardedVideo				( lua_State* L );
		static int	_hasCachedInterstitial			( lua_State* L );
		static int	_hasRewardedVideo				( lua_State* L );
		static int	_init	 						( lua_State* L );
		static int	_showInterstitial 				( lua_State* L );
		static int	_showRewardedVideo				( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIChartBoostAndroid );

		enum {
			INTERSTITIAL_LOAD_FAILED,
			INTERSTITIAL_DISMISSED,
			REWARDED_VIDEO_DISMISSED,
			REWARDED_VIDEO_WILL_START,
			REWARDED_VIDEO_COMPLETED,
			REWARDED_VIDEO_CACHED
		};

		//----------------------------------------------------------------//
						MOAIChartBoostAndroid			();
						~MOAIChartBoostAndroid			();
		void 			NotifyRewardedVideoCompleted	( int reward );
		void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAICHARTBOOST_H
