//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved. 
// http://cloudteam.pro
//----------------------------------------------------------------//

#ifndef	MOAIGOOGLECLOUDMESSAGINGANDROID_H
#define	MOAIGOOGLECLOUDMESSAGINGANDROID_H

#ifndef DISABLE_CLOUDMESSAGING

#include <jni.h>

#include <moai-core/headers.h>

//================================================================//
// MOAIGoogleCloudMessagingAndroid
//================================================================//
class MOAIGoogleCloudMessagingAndroid :
	public MOAIGlobalClass < MOAIGoogleCloudMessagingAndroid, MOAILuaObject >,
	public MOAIGlobalEventSource {
private:
		//----------------------------------------------------------------//
		static int	_register							( lua_State* L );
		static int	_unregister							( lua_State* L );
		static int	_getToken 							( lua_State* L );
		static int	_getLastPush						( lua_State* L );
		static int	_removeLastPush						( lua_State* L );
		static cc8*	_luaParseTable 				( lua_State* L, int idx );
		static jobject _luaReadMap				( lua_State * L, int idx );
		static void _luaPushArrayString			( lua_State * L, char const* array );

	public:

		DECL_LUA_SINGLETON ( MOAIGoogleCloudMessagingAndroid );

		enum {
			UNREGISTERED,
			REGISTERED,
			MESSAGE,
			ERROR,
			TOTAL
		};

		//MOAILuaRef		mListeners [ TOTAL ];

						MOAIGoogleCloudMessagingAndroid				();
						~MOAIGoogleCloudMessagingAndroid			();
		void 			NotifyRegistered							( cc8* result );
		void 			NotifyUnregistered							( cc8* result );
		void 			NotifyMessage								( cc8* result );
		void 			NotifyError									( cc8* result );
		void			RegisterLuaClass							( MOAILuaState& state );
};

#endif //DISABLE_CLOUDMESSAGING

#endif  //MOAIGOOGLECLOUDMESSAGINGANDROID_H
