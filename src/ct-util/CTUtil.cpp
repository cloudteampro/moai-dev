// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <ct-util/CTUtil.h>


//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int	CTUtil::_scheduleRelaunch ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( CTUtil, "" )
	
	self->mRelaunchScheduled = state.GetValue < bool >( 1, true );
	return 0;
}

//----------------------------------------------------------------//
CTUtil::CTUtil () :
	mRelaunchScheduled ( false ) {
    
    RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
CTUtil::~CTUtil () {

}

//----------------------------------------------------------------//
void CTUtil::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "scheduleRelaunch",		_scheduleRelaunch },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void CTUtil::RegisterLuaFuncs ( MOAILuaState& state ) {
	UNUSED ( state );
}

