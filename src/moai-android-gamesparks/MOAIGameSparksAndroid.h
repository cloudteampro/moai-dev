// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGAMESPARKSANDROID_H
#define	MOAIGAMESPARKSANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIGameSparksAndroid
//================================================================//
/**	@lua	MOAIGameSparksAndroid
	@text	Wrapper for GameSparks integration on Android devices.
			GameSparks - BaaS(backend-as-a-service) – platform with
			cloud storage and API. 
			Exposed to Lua via MOAIGameSparks on all mobile platforms.

	@const	ON_AVAILABILITY
	@const	ON_GET_ACCOUNT_DETAILS
	@const	ON_FB_CONNECT_SUCCESS
	@const	ON_FB_CONNECT_FAIL
	@const	ON_REGISTRATION
*/
class MOAIGameSparksAndroid :
	public MOAIGlobalClass < MOAIGameSparksAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

	jmethodID	mJava_Connect;
	jmethodID	mJava_ConnectFB;
	jmethodID	mJava_GetAccountDetails;
	jmethodID	mJava_Init;
	jmethodID	mJava_Login;

	//----------------------------------------------------------------//
	static int	_connect						( lua_State* L );
	static int	_connectFB						( lua_State* L );
	static int	_getAccountDetails				( lua_State* L );
	static int	_init	 						( lua_State* L );
	static int	_login							( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGameSparksAndroid );

	enum {
		ON_AVAILABILITY,
		ON_FB_CONNECT_SUCCESS,
		ON_FB_CONNECT_FAIL,
		ON_GET_ACCOUNT_DETAILS,
		ON_REGISTRATION,
	};

	//----------------------------------------------------------------//
			MOAIGameSparksAndroid			();
			~MOAIGameSparksAndroid			();
	void	AccountDetailsResponse			();
	void	AvailabilityResponse			( bool available );
	void	FBConnectSuccessResponse		( cc8* *displayName, cc8* *userId, bool isNew );
	void	FBConnectFailResponse			( cc8* *error );
	void	RegistrationResponse			( cc8* *authToken, cc8* *displayName, bool newPlayer, cc8* *userId );
	void	RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIGAMESPARKSANDROID_H

