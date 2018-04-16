// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIAPPSFLYERANDROID_H
#define	MOAIAPPSFLYERANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIAppsFlyerAndroid
//================================================================//
class MOAIAppsFlyerAndroid :
	public MOAIGlobalClass < MOAIAppsFlyerAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_Init;
		jmethodID	mJava_TrackEvent;
		jmethodID	mJava_TrackPurchase;
		jmethodID	mJava_TrackLevelAchieved;

		//----------------------------------------------------------------//
		static int	_init	 						( lua_State* L );
		static int	_trackEvent						( lua_State* L );
		static int	_trackPurchase					( lua_State* L );
		static int	_trackLevelAchieved				( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIAppsFlyerAndroid );

		//----------------------------------------------------------------//
						MOAIAppsFlyerAndroid			();
						~MOAIAppsFlyerAndroid			();
		void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIAPPSFLYER_H