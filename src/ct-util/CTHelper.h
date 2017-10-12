// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	CTHELPER_H
#define	CTHELPER_H

#include <moai-core/headers.h>

//================================================================//
// CTHelper
//================================================================//
/**	@name	CTHelper
	@text	CloudTeam lua helper. Mostly for temporary hacks
*/
class CTHelper :
	public ZLContextClass < CTHelper, MOAILuaObject > {
private:

	//----------------------------------------------------------------//
	static int 	_stepSim            		( lua_State* L );
	static int	_setBufferSize				( lua_State* L );
 	static int	_renderFrameBuffer			( lua_State* L );
 	static int	_setWorldLoc				( lua_State* L );

public:

	DECL_LUA_SINGLETON ( CTHelper )

	//
	void stepSim( double step );

	//----------------------------------------------------------------//
					CTHelper		();
					~CTHelper		();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};

#endif