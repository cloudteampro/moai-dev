// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIBoneArray.h>
#include <moai-sim/MOAIBone.h>
#include <moai-sim/MOAIMatrix.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	getBone
	@text	Get transform for a given index. 

	@in		MOAIBoneArray self
	@in		number index
	@out	MOAIBone
*/
int MOAIBoneArray::_getBone ( lua_State *L ) {
	MOAI_LUA_SETUP ( MOAIBoneArray, "UN" )
	
	u32 idx = state.GetValue < u32 >( 2, 1 ) - 1;
	
	MOAIBone* bone = self->GetBone ( idx );
	if ( bone ) {
		state.Push ( bone );
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
 	
	@in		MOAIBoneArray self
	@opt	number total			Default value is 0.
	@out	nil
*/
int MOAIBoneArray::_reserve ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBoneArray, "U" )
	
	u32 total = state.GetValue < u32 >( 2, 0 );
	self->Reserve ( total );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setBone
	@text	Set or clears a transform for a given index. Note: If you leave this uninitialized,
			and try to use this as a skeleton for a MOAIProp, badness will ensue!

	@in		MOAIBoneArray self
	@in		number index
	@opt	MOAIBone bone		Default value is nil.
	@out	nil
*/
int MOAIBoneArray::_setBone ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBoneArray, "UN" )
	
	u32 idx = state.GetValue < u32 >( 2, 1 ) - 1;
	MOAIBone* bone = state.GetLuaObject < MOAIBone >( 3, true );

	self->SetBone ( idx, bone );
	
	return 0;
}

//================================================================//
// MOAIBoneArray
//================================================================//

//----------------------------------------------------------------//
bool MOAIBoneArray::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {
	
	if ( MOAIBoneArrayAttr::Check ( attrID )) {
		switch ( UNPACK_ATTR ( attrID )) {
			case ATTR_VEC4_ARRAY: {
				attrOp.ApplyNoAdd < ZLLeanArray<ZLVec4D>* >( &this->mBuffer, op, MOAIAttrOp::ATTR_READ, MOAIAttrOp::ATTR_TYPE_VARIANT );
				return true;
			}
		}
	}
	return false;
}

//----------------------------------------------------------------//
void MOAIBoneArray::Clear () {
	for ( u32 i = 0; i < this->mBones.Size (); ++i ) {
		this->LuaRelease ( this->mBones [ i ]);
	}
	
	this->mBones.Clear ();
}

//----------------------------------------------------------------//
void* MOAIBoneArray::GetBuffer () {
	return ( void* )this->mBuffer.Data ();
}

//----------------------------------------------------------------//
MOAIBoneArray::MOAIBoneArray () {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAINode )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIBoneArray::~MOAIBoneArray () {
	
	this->Clear ();
}

//----------------------------------------------------------------//
MOAIBone* MOAIBoneArray::GetBone ( u32 idx ) {
	
	return this->mBones [ idx ];
}

//----------------------------------------------------------------//
void MOAIBoneArray::OnDepNodeUpdate () {
	
	for ( u32 i = 0; i < this->mBones.Size (); ++i ) {
		const ZLAffine3D& mtx = this->mBones [ i ]->GetBoneMtx ();
		
		ZLVec4D& r0 = this->mBuffer [ i * 3 ];
		ZLVec4D& r1 = this->mBuffer [ i * 3 + 1 ];
		ZLVec4D& r2 = this->mBuffer [ i * 3 + 2 ];

		r0.mX = mtx.m [ ZLAffine3D::C0_R0 ];
		r0.mY = mtx.m [ ZLAffine3D::C1_R0 ];
		r0.mZ = mtx.m [ ZLAffine3D::C2_R0 ];
		r0.mW = mtx.m [ ZLAffine3D::C3_R0 ];

		r1.mX = mtx.m [ ZLAffine3D::C0_R1 ];
		r1.mY = mtx.m [ ZLAffine3D::C1_R1 ];
		r1.mZ = mtx.m [ ZLAffine3D::C2_R1 ];
		r1.mW = mtx.m [ ZLAffine3D::C3_R1 ];

		r2.mX = mtx.m [ ZLAffine3D::C0_R2 ];
		r2.mY = mtx.m [ ZLAffine3D::C1_R2 ];
		r2.mZ = mtx.m [ ZLAffine3D::C2_R2 ];
		r2.mW = mtx.m [ ZLAffine3D::C3_R2 ];
	}
}

//----------------------------------------------------------------//
void MOAIBoneArray::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAINode::RegisterLuaClass ( state );
	
	state.SetField ( -1, "ATTR_VEC4_ARRAY",	MOAIBoneArrayAttr::Pack ( ATTR_VEC4_ARRAY ));
}

//----------------------------------------------------------------//
void MOAIBoneArray::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAINode::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "getBone",				_getBone },
		{ "reserve",				_reserve },
		{ "setBone",				_setBone },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIBoneArray::Reserve ( u32 total ) {
	
	this->Clear ();
	this->mBones.Init ( total );
	this->mBones.Fill ( 0 );
	
	this->mBuffer.Init ( 3 * total );
	for ( u32 i = 0; i < total; ++i ) {

		this->mBuffer [ i * 3 + 0 ].Init ( 1.0f, 0.0f, 0.0f, 0.0f );
		this->mBuffer [ i * 3 + 1 ].Init ( 0.0f, 1.0f, 0.0f, 0.0f );
		this->mBuffer [ i * 3 + 2 ].Init ( 0.0f, 0.0f, 1.0f, 0.0f );
	}
}

//----------------------------------------------------------------//
void MOAIBoneArray::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAIBoneArray::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAIBoneArray::SetBone ( u32 idx, MOAIBone* bone ) {
	
	if ( idx >= this->mBones.Size ()) return;
	if ( this->mBones [ idx ] == bone ) return;
	
	if ( this->mBones [ idx ]) {
		this->ClearNodeLink ( *this->mBones [ idx ]);
		this->LuaRelease ( this->mBones [ idx ]);
	}
	
	this->LuaRetain ( bone );
	this->SetNodeLink ( *bone );
	this->mBones [ idx ] = bone;
}

//----------------------------------------------------------------//
u32 MOAIBoneArray::Size () {
	return this->mBones.Size ();
}
