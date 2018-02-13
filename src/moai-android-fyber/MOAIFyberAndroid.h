// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFYBERANDROID_H
#define	MOAIFYBERANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIFyberAndroid
//================================================================//
class MOAIFyberAndroid :
	public MOAIGlobalClass < MOAIFyberAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_Init;
		jmethodID	mJava_RequestVideo;


		//----------------------------------------------------------------//
		static int	_init	 						( lua_State* L );
		static int	_requestVideo 					( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIFyberAndroid );

		enum {
			REWARDED_VIDEO_START,
			REWARDED_VIDEO_COMPLETED,
			REWARDED_VIDEO_ABORTED,
			REWARDED_VIDEO_ERROR
		};

		//----------------------------------------------------------------//
						MOAIFyberAndroid			();
						~MOAIFyberAndroid			();
		void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIFYBERANDROID_H
