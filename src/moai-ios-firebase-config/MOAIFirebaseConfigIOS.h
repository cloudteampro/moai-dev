//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIFIREBASECONFIGIOS_H
#define	MOAIFIREBASECONFIGIOS_H

#include <moai-core/headers.h>

//================================================================//
// MOAIFirebaseConfigIOS
//================================================================//
class MOAIFirebaseConfigIOS :
	public MOAIGlobalClass < MOAIFirebaseConfigIOS, MOAIGlobalEventSource > {
private:

	static int		_init							( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIFirebaseConfigIOS );

	//----------------------------------------------------------------//
					MOAIFirebaseConfigIOS				();
					~MOAIFirebaseConfigIOS				();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIFIREBASECONFIGIOS_H