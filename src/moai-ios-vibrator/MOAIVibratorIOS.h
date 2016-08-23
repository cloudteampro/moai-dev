// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIVIBRATORIOS_H
#define	MOAIVIBRATORIOS_H

#include <moai-core/headers.h>

//================================================================//
// MOAIVibratorIOS
//================================================================//
class MOAIVibratorIOS :
	public MOAIGlobalClass < MOAIVibratorIOS, MOAILuaObject > {
private:

	//----------------------------------------------------------------//
	static int			_vibrate						( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIVibratorIOS )
	
	//----------------------------------------------------------------//
						MOAIVibratorIOS					();
						~MOAIVibratorIOS				();
	void				RegisterLuaClass				( MOAILuaState& state );
};

#endif
