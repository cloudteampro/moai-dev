// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFIREBASECONFIGANDROID_H
#define	MOAIFIREBASECONFIGANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIFirebaseConfigAndroid
//================================================================//
class MOAIFirebaseConfigAndroid :
	public MOAIGlobalClass < MOAIFirebaseConfigAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_Init;

		//----------------------------------------------------------------//
		static int	_init	 						( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIFirebaseConfigAndroid );

		//----------------------------------------------------------------//
						MOAIFirebaseConfigAndroid		();
						~MOAIFirebaseConfigAndroid		();
		void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIFIREBASECONFIGANDROID_H
