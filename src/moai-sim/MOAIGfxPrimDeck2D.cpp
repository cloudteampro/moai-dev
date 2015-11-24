// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIGfxPrimDeck2D.h>
#include <moai-sim/MOAIShaderMgr.h>
#include <moai-sim/MOAIVertexFormatMgr.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@lua	
	@text	
*/
int MOAIGfxPrimDeck2D::_reserveIndices ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGfxPrimDeck2D, "UN" )

	u32 total = state.GetValue < u32 >( 2, 0 );
	self->ReserveIndices ( total );

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	
	@text
*/
int MOAIGfxPrimDeck2D::_reservePrims ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGfxPrimDeck2D, "UN" )

	u32 total = state.GetValue < u32 >( 2, 0 );
	self->ReservePrims ( total );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	
	@text	
*/
int MOAIGfxPrimDeck2D::_reserveVertices ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGfxPrimDeck2D, "UN" )

	u32 total = state.GetValue < u32 >( 2, 0 );
	self->ReserveVertices ( total );

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	
*/
int MOAIGfxPrimDeck2D::_setIndex ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGfxPrimDeck2D, "UNN" )

	u32 idx 	= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 index 	= state.GetValue < u32 >( 3, 1 ) - 1;

	self->SetIndex ( idx, index );

	return 0;
}

//----------------------------------------------------------------//
/**	@lua
*/
int MOAIGfxPrimDeck2D::_setPrim ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGfxPrimDeck2D, "UNNNNN" )

	u32 idx 		= state.GetValue < u32 >( 2, 1 ) - 1;
	u32 vtxBase 	= state.GetValue < u32 >( 3, 1 ) - 1;
	u32 vtxCount 	= state.GetValue < u32 >( 4, 0 );
	u32 idxBase 	= state.GetValue < u32 >( 5, 1 ) - 1;
	u32 idxCount 	= state.GetValue < u32 >( 6, 0 );
	
	self->SetPrim ( idx, vtxBase, vtxCount, idxBase, idxCount );

	return 0;
}

//----------------------------------------------------------------//
/**	@lua
*/
int MOAIGfxPrimDeck2D::_setVertex ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGfxPrimDeck2D, "UNNNNN" )

	u32 idx = state.GetValue < u32 >( 2, 1 ) - 1;
	if ( MOAILogMessages::CheckIndexPlusOne ( idx, self->mVertices.Size (), L )) {
		
		ZLVertex vtx;
		
		vtx.mVtx.mX = state.GetValue < float >( 3, 0.0f );
		vtx.mVtx.mY = state.GetValue < float >( 4, 0.0f );
		vtx.mUV.mX	= state.GetValue < float >( 5, 0.0f );
		vtx.mUV.mY	= state.GetValue < float >( 6, 0.0f );

		self->SetVertex ( idx, vtx );
		self->SetBoundsDirty ();
	}
	return 0;
}

//================================================================//
// MOAIGfxPrimDeck2D
//================================================================//

//----------------------------------------------------------------//
ZLBox MOAIGfxPrimDeck2D::ComputeMaxBounds () {

	// TODO
	ZLBox bounds;
	bounds.Init ( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );

	return bounds;
}

//----------------------------------------------------------------//
bool MOAIGfxPrimDeck2D::Contains ( u32 idx, const ZLVec2D& vec ) {

	// TODO
	return false;
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::DrawIndex ( u32 idx, MOAIMaterialBatch& materials, ZLVec3D offset, ZLVec3D scale ) {

	u32 size = this->mBatches.Size ();
	if ( size ) {

		idx = idx - 1;
		u32 itemIdx = idx % size;
		
		materials.LoadGfxState ( this, idx, MOAIShaderMgr::DECK2D_SHADER );

		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
		gfxDevice.BindBufferedDrawing ( MOAIVertexFormatMgr::XYZWUVC );

		gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );
		gfxDevice.SetUVMtxMode ( MOAIGfxDevice::UV_STAGE_MODEL, MOAIGfxDevice::UV_STAGE_TEXTURE );
		
		ZLIndexedPrim& batch = this->mBatches [ itemIdx ];
		
		u32 vtxBase = batch.mVtxBase;
		u32 vtxTop 	= vtxBase + batch.mVtxCount;

		u32 idxBase = batch.mIdxBase;
		u32 idxTop 	= idxBase + batch.mIdxCount;

		gfxDevice.BeginPrimIndexed ( ZGL_PRIM_TRIANGLES, ( u32 )( batch.mVtxCount ), batch.mIdxCount / 3 );

		for ( u32 i = vtxBase; i < vtxTop; ++i ) {
			
			ZLVertex& vtx = this->mVertices [ i ];
			gfxDevice.WriteVtx ( vtx.mVtx );
			gfxDevice.WriteUV ( vtx.mUV );
			gfxDevice.WriteFinalColor4b ();	
		}

		for ( u32 i = idxBase; i < idxTop; ++i ) {

			gfxDevice.WriteIndex ( this->mIndices [ i ]);
		}

		gfxDevice.EndPrimIndexed ();
	}
}

//----------------------------------------------------------------//
ZLBox MOAIGfxPrimDeck2D::GetItemBounds ( u32 idx ) {
	
	// TODO
	ZLBox bounds;

	bounds.Init ( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
	return bounds;
}

//----------------------------------------------------------------//
bool MOAIGfxPrimDeck2D::Inside ( u32 idx, MOAIMaterialBatch& materials, u32 granularity, ZLVec3D vec, float pad ) {
	UNUSED ( pad );

	// TODO
	return false;
}

//----------------------------------------------------------------//
MOAIGfxPrimDeck2D::MOAIGfxPrimDeck2D () {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIStandardDeck )
	RTTI_END
	
	//this->SetContentMask ( MOAIProp::CAN_DRAW );
}

//----------------------------------------------------------------//
MOAIGfxPrimDeck2D::~MOAIGfxPrimDeck2D () {
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAIStandardDeck::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIStandardDeck::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "reserveIndices",		 	_reserveIndices },
		{ "reservePrims",		 	_reservePrims },
		{ "reserveVertices",		_reserveVertices },
		{ "setIndex",		 		_setIndex },
		{ "setPrim",		 		_setPrim },
		{ "setVertex",		 		_setVertex },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::ReserveIndices ( u32 total ) {

	this->mIndices.Init ( total );
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::ReservePrims ( u32 total ) {

	this->mBatches.Init ( total );
	
	ZLIndexedPrim zero;
	zero.mVtxBase	= 0;
	zero.mVtxCount	= 0;
	zero.mIdxBase	= 0;
	zero.mIdxCount	= 0;
	
	this->mBatches.Fill ( zero );
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::ReserveVertices ( u32 total ) {

	this->mVertices.Init ( total );
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::SetIndex ( u32 idx, u32 index ) {

	if ( !this->mIndices.Size ()) return;
	this->mIndices [ idx ] = index;
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::SetPrim ( u32 idx, u32 vtxBase, u32 vtxCount, u32 idxBase, u32 idxCount ) {
		
	ZLIndexedPrim& batch = this->mBatches [ idx % this->mBatches.Size ()];
	
	batch.mVtxBase	= vtxBase;
	batch.mVtxCount = vtxCount;
	batch.mIdxBase	= idxBase;
	batch.mIdxCount = idxCount;
}

//----------------------------------------------------------------//
void MOAIGfxPrimDeck2D::SetVertex ( u32 idx, ZLVertex& vtx ) {

	if ( idx > this->mVertices.Size ()) return;
	this->mVertices [ idx ] = vtx;
}
