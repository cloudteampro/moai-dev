// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <ct-util/CTUtil.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int	CTUtil::_dumpTransform ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( CTUtil, "" )
	
	MOAIStream* stream = state.GetLuaObject < MOAIStream >( 1, true );
	MOAIProp* prop = state.GetLuaObject < MOAIProp >( 2, true );
	
	// Add option string to selectively dump values
	
	ZLVec3D loc = prop->GetLoc ();
//	ZLVec3D rot = prop->GetRot ();
//	ZLVec3D scl = prop->GetScl ();
	
	stream->WriteBytes ( &loc.mX, sizeof ( float ));
	stream->WriteBytes ( &loc.mY, sizeof ( float ));
	
	return 0;
}

//----------------------------------------------------------------//
int	CTUtil::_scheduleRelaunch ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( CTUtil, "" )
	
	self->mRelaunchScheduled = state.GetValue < bool >( 1, true );
	return 0;
}

//----------------------------------------------------------------//
CTUtil::CTUtil () :
	mRelaunchScheduled ( false ) {
    
    RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
CTUtil::~CTUtil () {

}

//----------------------------------------------------------------//
void CTUtil::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "SESSION_END",			( u32 )SESSION_END );
	state.SetField ( -1, "SESSION_START",		( u32 )SESSION_START );
	
	luaL_Reg regTable [] = {
		{ "dumpTransform",			_dumpTransform },
		{ "getListener",			&MOAIGlobalEventSource::_getListener < CTUtil > },
		{ "scheduleRelaunch",		_scheduleRelaunch },
		{ "setListener",			&MOAIGlobalEventSource::_setListener < CTUtil > },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void CTUtil::RegisterLuaFuncs ( MOAILuaState& state ) {
	UNUSED ( state );
}

