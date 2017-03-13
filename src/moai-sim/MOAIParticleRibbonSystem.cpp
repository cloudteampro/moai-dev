// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <float.h>
#include <moai-sim/MOAIParticleRibbonSystem.h>
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIDeck.h>
#include <moai-sim/MOAIMaterialBatch.h>
#include <moai-sim/MOAIShaderMgr.h>
#include <moai-sim/MOAIVertexFormatMgr.h>
#include <moai-sim/MOAIRenderMgr.h>
#include <moai-sim/MOAICamera.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int MOAIParticleRibbonSystem::_setWidth ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleRibbonSystem, "U" )

	self->mWidth = state.GetValue < float >( 2, 1.f );
	return 0;
}

//================================================================//
// MOAIParticleRibbonSystem
//================================================================//

//----------------------------------------------------------------//
void MOAIParticleRibbonSystem::Draw ( int subPrimID, float lod, MOAIMaterialBatch* materialsOverride ) {
	UNUSED ( subPrimID );
	UNUSED ( materialsOverride );

	if ( !this->IsVisible ( lod )) return;
	if ( this->IsClear ()) return;

	u32 maxSprites = this->mSprites.Size ();
	u32 total = this->mSpriteTop;
	u32 base = 0;
	if ( total > maxSprites ) {
		base = total % maxSprites;
		total = maxSprites;
	}

	// ribbon is drawn between particles. We need at least 2 to render something.
	if ( total < 2 ) return;

	// ZLAffine3D billboardMtx;
	// u32 billboard = this->mBillboard;
	// // TODO: support another billboard types
	// if ( this->mBillboard == BILLBOARD_NORMAL ) {

	// 	MOAIRenderMgr& renderMgr = MOAIRenderMgr::Get ();
	// 	MOAICamera* camera = renderMgr.GetCamera ();

	// 	u32 billboard = camera ? this->mBillboard : BILLBOARD_NONE;
	// 	billboardMtx.Init ( camera->GetBillboardMtx ());
	// }
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	this->LoadGfxState ();
	this->LoadVertexTransform ();
	this->LoadUVTransform ();
	
	MOAIShader* shader = this->mMaterialBatch ? this->mMaterialBatch->RawGetShader ( 0 ) : 0;
	MOAITextureBase* texture = this->mMaterialBatch ? this->mMaterialBatch->RawGetTexture ( 0 ) : 0;

	if ( !shader ) {
		shader = MOAIShaderMgr::Get ().GetShader ( MOAIShaderMgr::DECK2D_SHADER );
	}
	
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );
	gfxDevice.SetUVMtxMode ( MOAIGfxDevice::UV_STAGE_MODEL, MOAIGfxDevice::UV_STAGE_TEXTURE );
	
	gfxDevice.BindBufferedDrawing ( MOAIVertexFormatMgr::XYZWUVC );
	
	gfxDevice.SetShader ( shader );
	gfxDevice.SetTexture ( texture );
	
	u32 vtxCount = 2 * ( total + 1 );
	u32 idxCount = 6 * ( total - 1 );
	gfxDevice.BeginPrimIndexed ( ZGL_PRIM_TRIANGLES, vtxCount, idxCount );

	MOAICamera* camera = MOAIRenderMgr::Get ().GetCamera ();
	ZLVec3D zAxis = ( camera && camera->GetType () == MOAICamera::CAMERA_TYPE_3D ) ? camera->GetLoc () - this->GetLoc () : this->mLocalToWorldMtx.GetZAxis ();

	for ( u32 i = 0; i < total; ++i ) {

		u32 idx = ( base + i ) % maxSprites;
		
		AKUParticleSprite& sprite = this->mSprites [ idx ];
		ZLVec3D cur ( sprite.mXLoc, sprite.mYLoc, sprite.mZLoc );
		gfxDevice.SetPenColor ( sprite.mRed, sprite.mGreen, sprite.mBlue, sprite.mAlpha );

		ZLVec3D next;
		ZLVec3D prev;

		if ( i > 0 ) {
			sprite = this->mSprites [( base + i - 1 ) % maxSprites ];
			prev.Init ( sprite.mXLoc, sprite.mYLoc, sprite.mZLoc );
		}
		else {
			prev.Init ( cur );
		}
		if ( i < total - 1 ) {
			sprite = this->mSprites [( base + i + 1 ) % maxSprites ];
			next.Init ( sprite.mXLoc, sprite.mYLoc, sprite.mZLoc );
		}
		else {
			next.Init ( cur );
		}
		
		ZLVec3D norm ( next - prev );
		norm.Cross ( zAxis );
		norm.SetLength ( this->mWidth * sprite.mXScl );

		float u = ( float ) i / total;

		gfxDevice.WriteVtx ( cur - norm );
		gfxDevice.WriteUV ( u, 0.f );
		gfxDevice.WriteFinalColor4b ();

		gfxDevice.WriteVtx ( cur + norm );
		gfxDevice.WriteUV ( u, 1.f );
		gfxDevice.WriteFinalColor4b ();

		if ( i > 0 ) {
			gfxDevice.WriteIndex ( 2 * i - 2 );
			gfxDevice.WriteIndex ( 2 * i - 1 );
			gfxDevice.WriteIndex ( 2 * i + 1 );

			gfxDevice.WriteIndex ( 2 * i - 2 );
			gfxDevice.WriteIndex ( 2 * i + 1 );
			gfxDevice.WriteIndex ( 2 * i );
		}
	}

	gfxDevice.EndPrimIndexed ();
}

//----------------------------------------------------------------//
MOAIParticleRibbonSystem::MOAIParticleRibbonSystem () :
	mWidth ( 1.f ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIParticleSystem )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIParticleRibbonSystem::~MOAIParticleRibbonSystem () {
}

//----------------------------------------------------------------//
void MOAIParticleRibbonSystem::RegisterLuaClass ( MOAILuaState& state ) {

	MOAIParticleSystem::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIParticleRibbonSystem::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAIParticleSystem::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "setWidth",			_setWidth },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}
