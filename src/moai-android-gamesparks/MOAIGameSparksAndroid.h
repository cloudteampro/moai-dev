// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGAMESPARKSANDROID_H
#define	MOAIGAMESPARKSANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIGameSparksAndroid
//================================================================//
class MOAIGameSparksAndroid :
	public MOAIGlobalClass < MOAIGameSparksAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_Init;

		//----------------------------------------------------------------//
		static int	_init	 						( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIGameSparksAndroid );

		//----------------------------------------------------------------//
						MOAIGameSparksAndroid			();
						~MOAIGameSparksAndroid			();
		void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIGAMESPARKSANDROID_H
