// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <ct-util/CTHelper.h>


//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int CTHelper::_setBufferSize ( lua_State *L ) {
	MOAI_LUA_SETUP ( CTHelper, "NN" )

	u32 width = state.GetValue < u32 > ( 1, 0 );
	u32 height = state.GetValue < u32 > ( 2, 0 );

	MOAIGfxDevice::Get ().SetBufferSize ( width, height );

	return 0;
}

//----------------------------------------------------------------//
int CTHelper::_renderFrameBuffer ( lua_State *L ) {
	MOAI_LUA_SETUP ( CTHelper, "U" )

	// MOAIFrameBufferRenderCommand* command = state.GetLuaObject < MOAIFrameBufferRenderCommand >( -1, false );

	// if ( command ) {

	// 	if ( command->IsEnabled() && command->GetFrameBuffer() ) {

	// 		zglBegin();
	// 		command->Render();
	// 		zglEnd();
	// 	}
	// } else {

		MOAIFrameBuffer* frameBuffer = state.GetLuaObject < MOAIFrameBuffer >( -1, false );

		if ( frameBuffer ) {

			zglBegin();
			// frameBuffer->Render ( NULL );
			frameBuffer->Render ();
			zglEnd();
		}
	// }
	return 0;
}

//================================================================//
// CTHelper
//================================================================//

//----------------------------------------------------------------//
CTHelper::CTHelper () {
	
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
CTHelper::~CTHelper () {

}

//----------------------------------------------------------------//
void CTHelper::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "setBufferSize",			_setBufferSize },
		{ "renderFrameBuffer",		_renderFrameBuffer },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void CTHelper::RegisterLuaFuncs ( MOAILuaState& state ) {
	UNUSED ( state );
}

