// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-imgui/MOAIImGui.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	setCreateTexture
*/
//================================================================//
// MOAISpine
//================================================================//

//----------------------------------------------------------------//
MOAISpine::MOAISpine () {
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAISpine::~MOAISpine () {
}

//----------------------------------------------------------------//
void MOAISpine::RegisterLuaClass ( MOAILuaState& state ) {

	// here are the class methods:
	luaL_Reg regTable [] = {
		{ "setCreateTexture",		_setCreateTexture },
		{ "setReadFile",			_setReadFile },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
