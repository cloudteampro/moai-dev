// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	CTUTIL_H
#define	CTUTIL_H

#include <moai-core/headers.h>


//================================================================//
// CTUtil
//================================================================//
/**	@name	CTUtil
	@text	CloudTeam lua utilities
*/
class CTUtil :
	public MOAIGlobalClass < CTUtil, MOAILuaObject > {
private:

	bool 	mRelaunchScheduled;

	//----------------------------------------------------------------//
	static int	_scheduleRelaunch			( lua_State* L );

public:

	DECL_LUA_SINGLETON ( CTUtil )

	GET_BOOL ( IsRelaunchScheduled, mRelaunchScheduled )

	//----------------------------------------------------------------//
					CTUtil		();
					~CTUtil		();
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
};

#endif