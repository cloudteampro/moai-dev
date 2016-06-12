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
	MOAITransform* transform = state.GetLuaObject < MOAITransform >( 3, true );
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
bool MOAITransformArray::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {
	
	if ( MOAITransformArrayAttr::Check ( attrID )) {
		switch ( UNPACK_ATTR ( attrID )) {
			case ATTR_BUFFER_TRAIT: {
				attrOp.ApplyNoAdd < MOAITransformArray* >( this, op, MOAIAttrOp::ATTR_READ, MOAIAttrOp::ATTR_TYPE_VARIANT );
				return true;
			}
		}
	}
	return false;
}

//----------------------------------------------------------------//
void MOAITransformArray::Clear () {
	for ( u32 i = 0; i < this->mTransforms.Size (); ++i ) {
		this->LuaRelease ( this->mTransforms [ i ]);
	}
	
	this->mTransforms.Clear ();
	this->mInvBindPose.Clear ();
}

//----------------------------------------------------------------//
void* MOAITransformArray::GetBuffer () {
	return ( void* )this->mBuffer.Data ();
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
void MOAITransformArray::OnDepNodeUpdate () {
	
	for ( u32 i = 0; i < this->mTransforms.Size (); ++i ) {
		ZLMatrix4x4 out;
		out.Init ( this->mTransforms [ i ]->GetLocalToWorldMtx ());
		out.Prepend ( this->mInvBindPose [ i ]);
		
		float* m = this->mBuffer.Data () + 12 * i;
		
		m [ 0 ]		= out.m [ ZLMatrix4x4::C0_R0 ];
		m [ 1 ]		= out.m [ ZLMatrix4x4::C1_R0 ];
		m [ 2 ]		= out.m [ ZLMatrix4x4::C2_R0 ];
		m [ 3 ]		= out.m [ ZLMatrix4x4::C3_R0 ];
		
		m [ 4 ]		= out.m [ ZLMatrix4x4::C0_R1 ];
		m [ 5 ]		= out.m [ ZLMatrix4x4::C1_R1 ];
		m [ 6 ]		= out.m [ ZLMatrix4x4::C2_R1 ];
		m [ 7 ]		= out.m [ ZLMatrix4x4::C3_R1 ];
		
		m [ 8 ]		= out.m [ ZLMatrix4x4::C0_R2 ];
		m [ 9 ]		= out.m [ ZLMatrix4x4::C1_R2 ];
		m [ 10 ]	= out.m [ ZLMatrix4x4::C2_R2 ];
		m [ 11 ]	= out.m [ ZLMatrix4x4::C3_R2 ];
	}
}

//----------------------------------------------------------------//
void MOAITransformArray::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAINode::RegisterLuaClass ( state );
	
	state.SetField ( -1, "ATTR_BUFFER_TRAIT",	MOAITransformArrayAttr::Pack ( ATTR_BUFFER_TRAIT ));
}

//----------------------------------------------------------------//
void MOAITransformArray::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAINode::RegisterLuaFuncs ( state );
	
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
	
	this->mBuffer.Init ( 4 * 3 * total );
	for ( u32 i = 0; i < total; ++i ) {
		float* m = this->mBuffer.Data () + 12 * i;
		m [ 0 ] = 1.0f; m [ 1 ] = 0.0f; m [ 2 ] = 0.0f; m [ 3 ] = 0.0f;
		m [ 4 ] = 0.0f; m [ 5 ] = 1.0f; m [ 6 ] = 0.0f; m [ 7 ] = 0.0f;
		m [ 8 ] = 0.0f; m [ 9 ] = 0.0f; m [ 10 ] = 1.0f; m [ 11 ] = 0.0f;
	}
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
void MOAITransformArray::SetTransform ( u32 idx, MOAITransform* transform, ZLMatrix4x4& invBindPose ) {
	
	if ( idx >= this->mTransforms.Size ()) return;
	if ( this->mTransforms [ idx ] == transform ) return;
	
	if ( this->mTransforms [ idx ]) {
		this->ClearNodeLink ( *this->mTransforms [ idx ]);
		this->LuaRelease ( this->mTransforms [ idx ]);
	}
	
	this->LuaRetain ( transform );
	this->SetNodeLink ( *transform );
	this->mTransforms [ idx ] = transform;
	this->mInvBindPose [ idx ].Init ( invBindPose );
}

//----------------------------------------------------------------//
u32 MOAITransformArray::Size () {
	return this->mTransforms.Size ();
}
