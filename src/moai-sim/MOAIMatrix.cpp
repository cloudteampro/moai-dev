// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIMatrix.h>
#include <moai-sim/MOAISim.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int MOAIMatrix::_append ( lua_State *L ) {
	MOAI_LUA_SETUP ( MOAIMatrix, "U" )
	
	MOAIMatrix* mtx = state.GetLuaObject < MOAIMatrix >( 2, true );
	if ( mtx ) {
		self->Append ( *mtx );
		self->ScheduleUpdate ();
	}
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIMatrix::_getMatrix ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIMatrix, "U" )
	
	state.Push ( self->m [ ZLAffine3D::C0_R0 ]);
	state.Push ( self->m [ ZLAffine3D::C1_R0 ]);
	state.Push ( self->m [ ZLAffine3D::C2_R0 ]);
	state.Push ( self->m [ ZLAffine3D::C3_R0 ]);
	
	state.Push ( self->m [ ZLAffine3D::C0_R1 ]);
	state.Push ( self->m [ ZLAffine3D::C1_R1 ]);
	state.Push ( self->m [ ZLAffine3D::C2_R1 ]);
	state.Push ( self->m [ ZLAffine3D::C3_R1 ]);
	
	state.Push ( self->m [ ZLAffine3D::C0_R2 ]);
	state.Push ( self->m [ ZLAffine3D::C1_R2 ]);
	state.Push ( self->m [ ZLAffine3D::C2_R2 ]);
	state.Push ( self->m [ ZLAffine3D::C3_R2 ]);
	
	return 12;
}

//----------------------------------------------------------------//
int MOAIMatrix::_prepend ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIMatrix, "U" )
	
	MOAIMatrix* mtx = state.GetLuaObject < MOAIMatrix >( 2, true );
	if ( mtx ) {
		self->Prepend ( *mtx );
		self->ScheduleUpdate ();
	}
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIMatrix::_setMatrix ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIMatrix, "U" )
	
	self->m [ ZLAffine3D::C0_R0 ]	= state.GetValue < float >( 2, 1.0f );
	self->m [ ZLAffine3D::C1_R0 ]	= state.GetValue < float >( 3, 0.0f );
	self->m [ ZLAffine3D::C2_R0 ]	= state.GetValue < float >( 4, 0.0f );
	self->m [ ZLAffine3D::C3_R0 ]	= state.GetValue < float >( 5, 0.0f );
	
	self->m [ ZLAffine3D::C0_R1 ]	= state.GetValue < float >( 6, 0.0f );
	self->m [ ZLAffine3D::C1_R1 ]	= state.GetValue < float >( 7, 1.0f );
	self->m [ ZLAffine3D::C2_R1 ]	= state.GetValue < float >( 8, 0.0f );
	self->m [ ZLAffine3D::C3_R1 ]	= state.GetValue < float >( 9, 0.0f );
	
	self->m [ ZLAffine3D::C0_R2 ]	= state.GetValue < float >( 10, 0.0f );
	self->m [ ZLAffine3D::C1_R2 ]	= state.GetValue < float >( 11, 0.0f );
	self->m [ ZLAffine3D::C2_R2 ]	= state.GetValue < float >( 12, 1.0f );
	self->m [ ZLAffine3D::C3_R2 ]	= state.GetValue < float >( 13, 0.0f );
	
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIMatrix::_setScRoTr ( lua_State *L ) {
	MOAI_LUA_SETUP ( MOAIMatrix, "U" )
	
	ZLVec3D scale = state.GetVec3D ( 2, 1.f );
	ZLVec3D rotate = state.GetVec3D ( 5, 0.f );
	ZLVec3D translate = state.GetVec3D ( 8, 0.f );
	
	self->ScRoTr ( scale, rotate, translate );
	
	return 0;
}

//================================================================//
// MOAIMatrix
//================================================================//

//----------------------------------------------------------------//
void MOAIMatrix::BuildLocalToWorldMtx ( ZLAffine3D& localToWorldMtx ) {

	localToWorldMtx = *this;
}

//----------------------------------------------------------------//
MOAIMatrix::MOAIMatrix () {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITransformBase )
	RTTI_END
	
	this->Ident ();
}

//----------------------------------------------------------------//
MOAIMatrix::~MOAIMatrix () {
}

//----------------------------------------------------------------//
void MOAIMatrix::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAITransformBase::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIMatrix::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAITransformBase::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "append",				_append },
		{ "getMatrix",			_getMatrix },
		{ "prepend",			_prepend },
		{ "setMatrix",			_setMatrix },
		{ "setScRoTr",			_setScRoTr },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIMatrix::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAIMatrix::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}
