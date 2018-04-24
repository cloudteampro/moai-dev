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
class MOAIGameSparksIOS :
	public MOAIGlobalClass < MOAIGameSparksIOS, MOAIGlobalEventSource > {
private:

	static int		_init							( lua_State* L );
	static int		_connect						( lua_State* L );
	static int		_connectFB						( lua_State* L );
	static int		_getAccountDetails				( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGameSparksIOS );

	enum {
		ON_AVAILABILITY,
		ON_GET_ACCOUNT_DETAILS,
		ON_FB_CONNECT_SUCCESS,
		ON_FB_CONNECT_FAIL,
	};

	//----------------------------------------------------------------//
	void			AvailabilityResponse			( int available );
	void			FBConnectSuccessResponse		( NSString *displayName, NSString *userId, int isnew );
	void			FBConnectFailResponse			( NSString *error );
					MOAIGameSparksIOS				();
					~MOAIGameSparksIOS				();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIGAMESPARKSIOS_H