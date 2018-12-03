// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFIREBASEINVITESANDROID_H
#define	MOAIFIREBASEINVITESANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIFirebaseInvitesAndroid
//================================================================//
class MOAIFirebaseInvitesAndroid :
	public MOAIGlobalClass < MOAIFirebaseInvitesAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_Init;

		//----------------------------------------------------------------//
		static int	_init	 						( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIFirebaseInvitesAndroid );

		//----------------------------------------------------------------//
						MOAIFirebaseInvitesAndroid		();
						~MOAIFirebaseInvitesAndroid		();
		void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIFIREBASEINVITESANDROID_H
