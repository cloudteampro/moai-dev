// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAITransformArray.h>
#include <moai-sim/MOAITransform.h>
#include <moai-sim/MOAIMatrix.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	getTransform
	@text	Get transform for a given index. 

	@in		MOAITransformArray self
	@in		number index
	@out	MOAITransform
*/
int MOAITransformArray::_getTransform( lua_State *L ) {
	MOAI_LUA_SETUP ( MOAITransformArray, "UN" )
	
	u32 idx = state.GetValue < u32 >( 2, 1 ) - 1;
	
	MOAITransform* transform = self->GetTransform ( idx );
	if ( transform ) {
		state.Push ( transform );
	}
	else {
		state.Push ();
	}
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	reserve
	@text	Reserve (and either clear or allocate) slots for transforms. This will
			clear out any existing transforms before resizing the underlying array.
 	
	@in		MOAITransformArray self
	@opt	number total			Default value is 0.
	@out	nil
*/
int MOAITransformArray::_reserve ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransformArray, "U" )
	
	u32 total = state.GetValue < u32 >( 2, 0 );
	self->Reserve ( total );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setTransform
	@text	Set or clears a transform for a given index. Note: If you leave this uninitialized,
			and try to use this as a skeleton for a MOAIProp, badness will ensue!

	@in		MOAITransformArray self
	@in		number index
	@opt	MOAITransform transform		Default value is nil.
	@opt	MOAIMatrix	invBindPose		Inverse bind pose matrix. Pass nil to calculate it from current transform values
	@out	nil
*/
int MOAITransformArray::_setTransform ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransformArray, "UN" )
	
	u32 idx = state.GetValue < u32 >( 2, 1 ) - 1;
	MOAITransform* transform = state.GetLuaObject < MOAITransform >( 3, false );
	MOAIMatrix* matrix = state.GetLuaObject < MOAIMatrix >( 4, false );

	ZLMatrix4x4 invBindPose;
	if ( matrix ) {
		matrix->ForceUpdate ();
		invBindPose.Init ( matrix->GetLocalToWorldMtx ());
	}
	else {
		transform->ForceUpdate ();
		invBindPose.Init ( transform->GetLocalToWorldMtx ());
		invBindPose.Inverse ();
		invBindPose.Transpose ();
	}

	self->SetTransform ( idx, transform, invBindPose );
	
	return 0;
}

//================================================================//
// MOAITransformArray
//================================================================//

//----------------------------------------------------------------//
void MOAITransformArray::Clear () {
	for ( u32 i = 0; i < this->mTransforms.Size (); ++i ) {
		this->LuaRelease ( this->mTransforms [ i ]);
	}
	
	this->mTransforms.Clear ();
	this->mInvBindPose.Clear ();
}

//----------------------------------------------------------------//
MOAITransformArray::MOAITransformArray () {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAINode )
	RTTI_END
}

//----------------------------------------------------------------//
MOAITransformArray::~MOAITransformArray () {
}

//----------------------------------------------------------------//
ZLMatrix4x4& MOAITransformArray::GetInvBindPose ( u32 idx ) {

	return this->mInvBindPose [ idx ];
}

//----------------------------------------------------------------//
MOAITransform* MOAITransformArray::GetTransform ( u32 idx ) {
	
	return this->mTransforms [ idx ];
}

//----------------------------------------------------------------//
void MOAITransformArray::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAITransformArray::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAITransformArray::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAITransformArray::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "getTransform",			_getTransform },
		{ "reserve",				_reserve },
		{ "setTransform",			_setTransform },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITransformArray::Reserve ( u32 total ) {
	
	this->Clear ();
	this->mTransforms.Init ( total );
	this->mTransforms.Fill ( 0 );

	this->mInvBindPose.Init ( total );
}

//----------------------------------------------------------------//
void MOAITransformArray::SetTransform ( u32 idx, MOAITransform* transform, ZLMatrix4x4& invBindPose ) {
	
	if ( idx >= this->mTransforms.Size ()) return;
	if ( this->mTransforms [ idx ] == transform ) return;
	
	this->LuaRetain ( transform );
	this->LuaRelease ( this->mTransforms [ idx ]);
	this->mTransforms [ idx ] = transform;
	this->mInvBindPose [ idx ].Init ( invBindPose );
}

//----------------------------------------------------------------//
u32 MOAITransformArray::Size () {
	return this->mTransforms.Size ();
}
