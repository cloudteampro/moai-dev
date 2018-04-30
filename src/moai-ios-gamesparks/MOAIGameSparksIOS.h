//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIGAMESPARKSIOS_H
#define	MOAIGAMESPARKSIOS_H

#include <moai-core/headers.h>

#import <GS.h>
#import <GSAPI.h>

//================================================================//
// MOAIGameSparksIOS
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
class MOAIGameSparksIOS :
	public MOAIGlobalClass < MOAIGameSparksIOS, MOAIGlobalEventSource > {
private:

	static int	_connect						( lua_State* L );
	static int	_connectFB						( lua_State* L );
	static int	_getAccountDetails				( lua_State* L );
	static int	_init							( lua_State* L );
	static int	_login							( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGameSparksIOS );

	enum {
		ON_AVAILABILITY,
		ON_FB_CONNECT_SUCCESS,
		ON_FB_CONNECT_FAIL,
		ON_GET_ACCOUNT_DETAILS,
		ON_REGISTRATION,
	};

	//----------------------------------------------------------------//
	void	AccountDetailsResponse			();
	void	AvailabilityResponse			( int available );
	void	FBConnectSuccessResponse		( NSString *displayName, NSString *userId, bool isNew );
	void	FBConnectFailResponse			( NSString *error );
			MOAIGameSparksIOS				();
			~MOAIGameSparksIOS				();
	void	RegistrationResponse			( cc8* *authToken, cc8* *displayName, bool newPlayer, cc8* *userId );
	void	RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIGAMESPARKSIOS_H

