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

public:

	DECL_LUA_SINGLETON ( MOAIGameSparksIOS );

	//----------------------------------------------------------------//
					MOAIGameSparksIOS				();
					~MOAIGameSparksIOS				();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIGAMESPARKSIOS_H