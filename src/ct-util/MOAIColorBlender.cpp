// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <ct-util/MOAIColorBlender.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@lua	setColors
	@text	Initialize the colors.
	
	@in		MOAIColorBlender self
	@in		number r1	Default value is 0.
	@in		number g1	Default value is 0.
	@in		number b1	Default value is 0.
	@in		number a1	Default value is 1.
	@in		number r2	Default value is 0.
	@in		number g2	Default value is 0.
	@in		number b2	Default value is 0.
	@opt	number a2	Default value is 1.
	@out	nil
*/
int MOAIColorBlender::_setColors ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIColorBlender, "UNNN" )

	ZLColorVec color1 = state.GetColor ( 2, 0.0f, 0.0f, 0.0f, 1.0f );
	ZLColorVec color2 = state.GetColor ( 6, 0.0f, 0.0f, 0.0f, 1.0f );

	self->mColorA = color1;
	self->mColorB = color2;
	
	self->ScheduleUpdate ();
	return 0;
}

//----------------------------------------------------------------//
/**	
*/
int MOAIColorBlender::_setBlendFactor ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIColorBlender, "U" )

	self->mBlendFactor = state.GetValue < float >( 2, 0.0f );
	self->ScheduleUpdate ();
	return 0;
}

//================================================================//
// MOAIColorBlender
//================================================================//

//----------------------------------------------------------------//
MOAIColorBlender::MOAIColorBlender ():
	mBlendFactor ( 0.0f ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIColor )
	RTTI_END
	
	this->mColorA.Set ( 1.0f, 1.0f, 1.0f, 1.0f );
	this->mColorB.Set ( 1.0f, 1.0f, 1.0f, 1.0f );
}

//----------------------------------------------------------------//
MOAIColorBlender::~MOAIColorBlender () {
}

//----------------------------------------------------------------//
void MOAIColorBlender::OnDepNodeUpdate () {

	this->Lerp ( ZLInterpolate::kLinear, this->mColorA, this->mColorB, this->mBlendFactor );
	MOAIColor::OnDepNodeUpdate ();
}

//----------------------------------------------------------------//
void MOAIColorBlender::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAIColor::RegisterLuaClass ( state );
	
}

//----------------------------------------------------------------//
void MOAIColorBlender::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAIColor::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "setColors",			_setColors },
		{ "setBlendFactor",	_setBlendFactor },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}
