// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIBone.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIBone::_setInvBindPose ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBone, "U" )
	
	float* m = self->mInvBindPose.m;
	
	m [ ZLAffine3D::C0_R0 ]	= state.GetValue < float >( 2, 1.0f );
	m [ ZLAffine3D::C1_R0 ]	= state.GetValue < float >( 3, 0.0f );
	m [ ZLAffine3D::C2_R0 ]	= state.GetValue < float >( 4, 0.0f );
	m [ ZLAffine3D::C3_R0 ]	= state.GetValue < float >( 5, 0.0f );
	
	m [ ZLAffine3D::C0_R1 ]	= state.GetValue < float >( 6, 0.0f );
	m [ ZLAffine3D::C1_R1 ]	= state.GetValue < float >( 7, 1.0f );
	m [ ZLAffine3D::C2_R1 ]	= state.GetValue < float >( 8, 0.0f );
	m [ ZLAffine3D::C3_R1 ]	= state.GetValue < float >( 9, 0.0f );
	
	m [ ZLAffine3D::C0_R2 ]	= state.GetValue < float >( 10, 0.0f );
	m [ ZLAffine3D::C1_R2 ]	= state.GetValue < float >( 11, 0.0f );
	m [ ZLAffine3D::C2_R2 ]	= state.GetValue < float >( 12, 1.0f );
	m [ ZLAffine3D::C3_R2 ]	= state.GetValue < float >( 13, 0.0f );
	
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIBone::_setPreRotation ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBone, "U" )

	self->mPreRotation.mX = state.GetValue < float >( 2, 0.0f );
	self->mPreRotation.mY = state.GetValue < float >( 3, 0.0f );
	self->mPreRotation.mZ = state.GetValue < float >( 4, 0.0f );

	return 0;
}


//================================================================//
// MOAIBone
//================================================================//

//----------------------------------------------------------------//
void MOAIBone::BuildLocalToWorldMtx ( ZLAffine3D& localToWorldMtx ) {
	
	float xPreRot = ClampEuler ( this->mPreRotation.mX ) * ( float )D2R;
	float yPreRot = ClampEuler ( this->mPreRotation.mY ) * ( float )D2R;
	float zPreRot = ClampEuler ( this->mPreRotation.mZ ) * ( float )D2R;

	float xRot = ClampEuler ( this->mRot.mX ) * ( float )D2R;
	float yRot = ClampEuler ( this->mRot.mY ) * ( float )D2R;
	float zRot = ClampEuler ( this->mRot.mZ ) * ( float )D2R;

	// TODO: euler order
	
	ZLAffine3D rot;
	
	localToWorldMtx.Scale ( this->mScale.mX, this->mScale.mY, this->mScale.mZ );
	
	rot.Rotate ( xRot, yRot, zRot );
	localToWorldMtx.Append ( rot );
	
	rot.Rotate ( xPreRot, yPreRot, zPreRot );
	localToWorldMtx.Append ( rot );

	localToWorldMtx.m [ ZLAffine3D::C3_R0 ] = this->mLoc.mX;
	localToWorldMtx.m [ ZLAffine3D::C3_R1 ] = this->mLoc.mY;
	localToWorldMtx.m [ ZLAffine3D::C3_R2 ] = this->mLoc.mZ;
	
	// TODO: shear and pivot? do we have to support them
	
	// ZLAffine3D shear;
	// shear.Shear ( this->mShearYX, this->mShearZX, this->mShearXY, this->mShearZY, this->mShearXZ, this->mShearYZ );
	// localToWorldMtx.Prepend ( shear );
	
	// if (( this->mPiv.mX != 0.0f ) || ( this->mPiv.mY != 0.0f ) || ( this->mPiv.mZ != 0.0f )) {
		
	// 	ZLAffine3D pivot;
	// 	pivot.Translate ( -this->mPiv.mX, -this->mPiv.mY, -this->mPiv.mZ );
	// 	localToWorldMtx.Prepend ( pivot );
	// }
}

//----------------------------------------------------------------//
const ZLAffine3D& MOAIBone::GetBoneMtx () const {
	return this->mBoneMtx;
}

//----------------------------------------------------------------//
MOAIBone::MOAIBone () : 
	mPreRotation ( 0.0f, 0.0f, 0.0f ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAITransform )
	RTTI_END

	this->mInvBindPose.Ident ();
	this->mBoneMtx.Ident ();
}

//----------------------------------------------------------------//
MOAIBone::~MOAIBone () {
}

//----------------------------------------------------------------//
void MOAIBone::OnDepNodeUpdate () {

	MOAITransform::OnDepNodeUpdate ();

	this->mBoneMtx.Init ( this->GetLocalToWorldMtx ());
	this->mBoneMtx.Prepend ( this->mInvBindPose );
}

//----------------------------------------------------------------//
void MOAIBone::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAITransform::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIBone::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAITransform::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "setInvBindPose",			_setInvBindPose },
		{ "setPreRotation",			_setPreRotation },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIBone::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAIBone::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	UNUSED ( serializer );
}
