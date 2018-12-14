// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFIREBASEANDROID_H
#define	MOAIFIREBASEANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIFirebaseAndroid
//================================================================//
class MOAIFirebaseAndroid :
	public MOAIGlobalClass < MOAIFirebaseAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_Init;
		jmethodID	mJava_FetchConfig;
		jmethodID	mJava_ActivateFetchedConfig;
		jmethodID	mJava_GetConfigString;
		jmethodID	mJava_GetConfigBoolean;
		jmethodID	mJava_GetConfigDouble;
		jmethodID	mJava_GetConfigLong;
		jmethodID	mJava_CreateAnonymousAccountWithReferrerInfo;
		jmethodID	mJava_ShowInviteSMSDialog;
		jmethodID	mJava_ShowInviteEmailDialog;
		jmethodID	mJava_GetInvitationId;
		jmethodID	mJava_GetInvitationDeepLink;
		jmethodID	mJava_CreateInvitationDeepLink;
		jmethodID	mJava_WriteToFBDB;
		jmethodID	mJava_ReadFromFBDB;
		jmethodID	mJava_GetValuesFromFBDB;

		//----------------------------------------------------------------//
		static int	_init	 									( lua_State* L );
		static int	_fetchConfig	 							( lua_State* L );
		static int	_activateFetchedConfig						( lua_State* L );
		static int	_getConfigString	 						( lua_State* L );
		static int	_getConfigBoolean	 						( lua_State* L );
		static int	_getConfigDouble	 						( lua_State* L );
		static int	_getConfigLong	 							( lua_State* L );
		static int	_createAnonymousAccountWithReferrerInfo		( lua_State* L );
		static int	_showInviteSMSDialog	 					( lua_State* L );
		static int	_showInviteEmailDialog	 					( lua_State* L );
		static int	_getInvitationId	 						( lua_State* L );
		static int	_getInvitationDeepLink	 					( lua_State* L );
		static int	_createInvitationDeepLink	 				( lua_State* L );
		static int	_writeToFBDB	 							( lua_State* L );
		static int	_readFromFBDB	 							( lua_State* L );
		static int	_getValuesFromFBDB	 						( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIFirebaseAndroid );

		enum {
			FETCH_CONFIG_SUCCEEDED,
			FETCH_CONFIG_FAILED,
			DEEPLINK_CREATED_SUCCEEDED,
			PENDING_INVITATION_ID_SUCCEEDED,
			READ_FBDB_SUCCEEDED
		};

		//----------------------------------------------------------------//
						MOAIFirebaseAndroid			();
						~MOAIFirebaseAndroid		();
		void			RegisterLuaClass			( MOAILuaState& state );
};

#endif  //MOAIFIREBASEANDROID_H

