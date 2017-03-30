// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <float.h>
#include <moai-sim/MOAIDeck.h>
#include <moai-sim/MOAIDeckRemapper.h>
#include <moai-sim/MOAIGfxDevice.h>
#include <moai-sim/MOAIParticleState.h>
#include <moai-sim/MOAIParticleSystem.h>
#include <moai-sim/MOAITextureBase.h>
#include <moai-sim/MOAIRenderMgr.h>
#include <moai-sim/MOAICamera.h>

class MOAIDataBuffer;

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@lua	capParticles
	@text	Controls capping vs. wrapping of particles in overflow situation.
			Capping will prevent emission of additional particles when system
			is full. Wrapping will overwrite the oldest particles with new particles.
	
	@in		MOAIParticleSystem self
	@opt	boolean cap					Default value is true.
	@out	nil
*/
int MOAIParticleSystem::_capParticles ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "U" )

	self->mCapParticles = state.GetValue < bool >( 2, true );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	capSprites
	@text	Controls capping vs. wrapping of sprites.
	
	@in		MOAIParticleSystem self
	@opt	boolean cap					Default value is true.
	@out	nil
*/
int MOAIParticleSystem::_capSprites ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "U" )

	self->mCapSprites = state.GetValue < bool >( 2, true );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	clearSprites
	@text	Flushes any existing sprites in system.
	
	@in		MOAIParticleSystem self
	@out	nil
*/
int MOAIParticleSystem::_clearSprites ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "U" )

	self->mSpriteTop = 0;
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getState
	@text	Returns a particle state for an index or nil if none exists.
	
	@in		MOAIParticleSystem self
	@in		number index
	@out	MOAIParticleState state
*/
int MOAIParticleSystem::_getState ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UN" )

	u32 idx = state.GetValue < u32 >( 2, 1 ) - 1;
	
	MOAIParticleState* particleState = self->GetState ( idx );
	if ( particleState ) {
		particleState->PushLuaUserdata ( state );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/** @lua	isIdle
	@text	Returns true if the current system is not currently
			processing any particles.
			
	@in		MOAIParticleSystem self
	@out	boolean isIdle				Indicates whether the system is currently idle.
*/
int  MOAIParticleSystem::_isIdle( lua_State* L ) {
	
	MOAI_LUA_SETUP ( MOAIParticleSystem, "U" )

	bool result = !self->mHead;

	lua_pushboolean ( state, result );
	return 1;
}	


//----------------------------------------------------------------//
/**	@lua	pushParticle
	@text	Adds a particle to the system.
	
	@in		MOAIParticleSystem self
	@opt	number x					Default value is 0.
	@opt	number y					Default value is 0.
	@opt	number dx					Default value is 0.
	@opt	number dy					Default value is 0.
	@opt	number state				Index of initial particle state.
	@out	boolean result				true if particle was added, false if not.
*/
int MOAIParticleSystem::_pushParticle ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "U" )

	if ( state.IsType ( 7, LUA_TNUMBER )) {
		float x = state.GetValue < float >( 2, 0.0f );
		float y = state.GetValue < float >( 3, 0.0f );
		float z = state.GetValue < float >( 4, 0.0f );
		
		float dx = state.GetValue < float >( 5, 0.0f );
		float dy = state.GetValue < float >( 6, 0.0f );
		float dz = state.GetValue < float >( 7, 0.0f );
		
		u32 stateIdx = state.GetValue < u32 >( 8, 1 ) - 1;
		
		bool result = self->PushParticle ( x, y, z, dx, dy, dz, stateIdx );
		lua_pushboolean ( state, result );
	}
	else {
		float x = state.GetValue < float >( 2, 0.0f );
		float y = state.GetValue < float >( 3, 0.0f );
		
		float dx = state.GetValue < float >( 4, 0.0f );
		float dy = state.GetValue < float >( 5, 0.0f );
		
		u32 stateIdx = state.GetValue < u32 >( 6, 1 ) - 1;
		
		bool result = self->PushParticle ( x, y, dx, dy, stateIdx );
		lua_pushboolean ( state, result );
	}
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	pushSprite
	@text	Adds a sprite to the system. Sprite will persist until
			particle simulation is begun or 'clearSprites' is called.
	
	@in		MOAIParticleSystem self
	@in		number x
	@in		number y
	@opt	number rot			Rotation in degrees. Default value is 0.
	@opt	number xScale		Default value is 1.
	@opt	number yScale		Default value is 1.
	@out	boolean result		true is sprite was added, false if not.
*/
int MOAIParticleSystem::_pushSprite ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UNN" )

	AKUParticleSprite sprite;

	sprite.mXLoc		= state.GetValue < float >( 2, 0.0f );
	sprite.mYLoc		= state.GetValue < float >( 3, 0.0f );
	sprite.mZRot		= state.GetValue < float >( 4, 0.0f );
	sprite.mXScl		= state.GetValue < float >( 5, 1.0f );
	sprite.mYScl		= state.GetValue < float >( 6, 1.0f );
	
	sprite.mRed			= 1.0f;
	sprite.mGreen		= 1.0f;
	sprite.mBlue		= 1.0f;
	sprite.mAlpha		= 1.0f;
	
	sprite.mGfxID = 1;
	
	bool result = self->PushSprite ( sprite );
	
	if ( result ) {
		self->ScheduleUpdate ();
	}
	lua_pushboolean ( state, result );
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	reserveParticles
	@text	Reserve particle capacity of system.
	
	@in		MOAIParticleSystem self
	@in		number nParticles		Total number of particle records.
	@in		number particleSize		Number of parameters reserved for the particle.
	@out	nil
*/
int MOAIParticleSystem::_reserveParticles ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UN" )

	u32 total	= state.GetValue < u32 >( 2, 0 );
	u32 size	= state.GetValue < u32 >( 3, 0 );

	self->ReserveParticles ( total, size );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	reserveSprites
	@text	Reserve sprite capacity of system.
	
	@in		MOAIParticleSystem self
	@in		number nSprites
	@out	nil
*/
int MOAIParticleSystem::_reserveSprites ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UN" )

	self->ReserveSprites ( state.GetValue < u32 >( 2, 0 ));
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	reserveStates
	@text	Reserve total number of states for system.
	
	@in		MOAIParticleSystem self
	@in		number nStates
	@out	nil
*/
int MOAIParticleSystem::_reserveStates ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UN" )

	self->ClearStates ();
	self->ReserveStates ( state.GetValue < u32 >( 2, 0 ));
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setDrawOrder
	@text	Set draw order of sprites in particle system
 
	@in		MOAIParticleSystem self
	@in     number  order		MOAIParticleSystem.ORDER_NORMAL or MOAIParticleSystem.ORDER_REVERSE
	@out	nil
*/
int MOAIParticleSystem::_setDrawOrder ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "U" )

	self->mDrawOrder = state.GetValue < u32 >( 2, ORDER_NORMAL );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setComputeBounds
	@text	Set the a flag controlling whether the particle system
			re-computes its bounds every frame.
	
	@in		MOAIParticleSystem self
	@opt	boolean computBounds		Default value is false.
	@out	nil
*/
int MOAIParticleSystem::_setComputeBounds ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "U" )

	self->mComputeBounds = state.GetValue < bool >( 2, false );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setSpriteColor
	@text	Set the color of the most recently added sprite.
	
	@in		MOAIParticleSystem self
	@in		number r
	@in		number g
	@in		number b
	@in		number a
	@out	nil
*/
int MOAIParticleSystem::_setSpriteColor ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UNNNN" )

	AKUParticleSprite* sprite = self->GetTopSprite ();
	if ( sprite ) {
	
		sprite->mRed	= state.GetValue < float >( 2, 1.0f );
		sprite->mGreen	= state.GetValue < float >( 3, 1.0f );
		sprite->mBlue	= state.GetValue < float >( 4, 1.0f );
		sprite->mAlpha	= state.GetValue < float >( 5, 1.0f );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setSpriteDeckIdx
	@text	Set the sprite's deck index.
	
	@in		MOAIParticleSystem self
	@in		number index
	@out	nil
*/
int MOAIParticleSystem::_setSpriteDeckIdx ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UN" )

	AKUParticleSprite* sprite = self->GetTopSprite ();
	if ( sprite ) {
		sprite->mGfxID = state.GetValue < u32 >( 2, sprite->mGfxID );
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setState
	@text	Set a particle state.
	
	@in		MOAIParticleSystem self
	@in		number index
	@in		MOAIParticleState state
	@out	nil
*/
int MOAIParticleSystem::_setState ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UNU" )

	u32 idx = state.GetValue < u32 >( 2, 0 ) - 1;

	if ( idx < self->mStates.Size ()) {
	
		MOAIParticleState* particleState =  state.GetLuaObject < MOAIParticleState >( 3, true );
		if ( particleState != self->mStates [ idx ]) {
		
			self->LuaRetain ( particleState );
			self->LuaRelease ( self->mStates [ idx ]);
			self->mStates [ idx ] = particleState;
		}
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	surge
	@text	Release a batch emission or particles into the system.
	
	@in		MOAIParticleSystem self
	@opt	number total			Default value is 1.
	@opt	number x				Default value is 0.
	@opt	number y				Default value is 0.
	@opt	number dx				Default value is 0.
	@opt	number dy				Default value is 0.
	@out	nil
*/
int MOAIParticleSystem::_surge ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIParticleSystem, "UN" )

	u32 n		= state.GetValue < u32 >( 2, 1 );
	float x		= state.GetValue < float >( 3, 0.0f );
	float y		= state.GetValue < float >( 4, 0.0f );
	float dx	= state.GetValue < float >( 5, 0.0f );
	float dy	= state.GetValue < float >( 6, 0.0f );
	u32 stateId	= state.GetValue < u32 >( 7, 1 ) - 1;
	
	for ( u32 i = 0; i < n; ++i ) {
		self->PushParticle ( x, y, dx, dy, stateId );
	}

	return 0;
}

//================================================================//
// MOAIParticleSystem
//================================================================//

//----------------------------------------------------------------//
void MOAIParticleSystem::ClearStates () {

	for ( u32 i = 0; i < this->mStates.Size (); ++i ) {
		this->LuaRelease ( this->mStates [ i ]);
	}
	this->mStates.Clear ();
}

//----------------------------------------------------------------//
void MOAIParticleSystem::ClearQueue () {

	this->mHead = 0;
	this->mTail = 0;
}

//----------------------------------------------------------------//
void MOAIParticleSystem::Draw ( int subPrimID, float lod, MOAIMaterialBatch* materialsOverride ) {
	UNUSED ( subPrimID );
	UNUSED ( materialsOverride );

	if ( !this->IsVisible ( lod )) return;
	if ( !this->mDeck ) return;
	if ( this->IsClear ()) return;

	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	
	this->LoadGfxState ();
	this->LoadUVTransform ();

	MOAIMaterialBatch& materials = this->mDeck->ResolveMaterialBatch ( this->mMaterialBatch );

	ZLAffine3D drawingMtx;
	ZLAffine3D spriteMtx;
	
	u32 maxSprites = this->mSprites.Size ();
	u32 total = this->mSpriteTop;
	u32 base = 0;
	if ( total > maxSprites ) {
		base = total % maxSprites;
		total = maxSprites;
	}
	
	ZLAffine3D billboardMtx;
	u32 billboard = this->mBillboard;
	// TODO: support another billboard modes
	if ( this->mBillboard == BILLBOARD_NORMAL ) {
		
		MOAIRenderMgr& renderMgr = MOAIRenderMgr::Get ();
		MOAICamera* camera = renderMgr.GetCamera ();
		
		u32 billboard = camera ? this->mBillboard : BILLBOARD_NONE;
		if ( camera ) {
			billboardMtx = camera->GetLocalToWorldMtx ();
			billboardMtx.m [ ZLAffine3D::C3_R0 ] = 0.0f;
			billboardMtx.m [ ZLAffine3D::C3_R1 ] = 0.0f;
			billboardMtx.m [ ZLAffine3D::C3_R2 ] = 0.0f;
		}
	}
	
	for ( u32 i = 0; i < total; ++i ) {

		u32 idx;
		if ( this->mDrawOrder == ORDER_NORMAL ) {
			idx = ( base + i ) % maxSprites;
		}
		else {
			idx = ( base + ( total - 1 - i )) % maxSprites;
		}
		
		AKUParticleSprite& sprite = this->mSprites [ idx ];
		gfxDevice.SetPenColor ( sprite.mRed, sprite.mGreen, sprite.mBlue, sprite.mAlpha );
		
		drawingMtx = this->GetLocalToWorldMtx ();
		spriteMtx.ScRoTr ( sprite.mXScl, sprite.mYScl, 1.0f, 0.0f, 0.0f, sprite.mZRot * ( float )D2R, sprite.mXLoc, sprite.mYLoc, sprite.mZLoc );
		drawingMtx.Prepend ( spriteMtx );
		
		if ( billboard == BILLBOARD_NORMAL ) {
			
			ZLVec3D worldLoc;
			worldLoc.mX = drawingMtx.m [ ZLAffine3D::C3_R0 ];
			worldLoc.mY = drawingMtx.m [ ZLAffine3D::C3_R1 ];
			worldLoc.mZ = drawingMtx.m [ ZLAffine3D::C3_R2 ];
			
			drawingMtx.m [ ZLAffine3D::C3_R0 ] = 0.0f;
			drawingMtx.m [ ZLAffine3D::C3_R1 ] = 0.0f;
			drawingMtx.m [ ZLAffine3D::C3_R2 ] = 0.0f;
			
			// orient to camera
			drawingMtx.Append ( billboardMtx );
			
			// restore world loc
			drawingMtx.m [ ZLAffine3D::C3_R0 ] = worldLoc.mX;
			drawingMtx.m [ ZLAffine3D::C3_R1 ] = worldLoc.mY;
			drawingMtx.m [ ZLAffine3D::C3_R2 ] = worldLoc.mZ;
		}
		
		gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM, drawingMtx );
		
		this->mDeck->Draw ( MOAIDeckRemapper::Remap ( this->mRemapper, this->mIndex + ( u32 )sprite.mGfxID ), materials );
	}
}

//----------------------------------------------------------------//
void MOAIParticleSystem::EnqueueParticle ( MOAIParticle& particle ) {

	if ( this->mTail ) {
		this->mTail->mNext = &particle;
	}
	else {
		this->mHead = &particle;
	}
	
	particle.mNext = 0;
	this->mTail = &particle;
}

//----------------------------------------------------------------//
MOAIParticleState* MOAIParticleSystem::GetState ( u32 id ) {

	if ( id < this->mStates.Size ()) {
		return this->mStates [ id ];
	}
	return 0;
}

//----------------------------------------------------------------//
AKUParticleSprite* MOAIParticleSystem::GetTopSprite () {

	if ( this->mSpriteTop ) {
		u32 idx = (this->mSpriteTop - 1) % this->mSprites.Size();
		return &this->mSprites [ idx ];
	}
	return 0;
}

//----------------------------------------------------------------//
bool MOAIParticleSystem::IsDone () {

	return false;
}

//----------------------------------------------------------------//
MOAIParticleSystem::MOAIParticleSystem () :
	mParticleSize ( 0 ),
	mCapParticles ( false ),
	mCapSprites ( false ),
	mHead ( 0 ),
	mTail ( 0 ),
	mFree ( 0 ),
	mSpriteTop ( 0 ),
	mDrawOrder ( ORDER_NORMAL ),
	mComputeBounds ( false ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIGraphicsProp )
		RTTI_EXTEND ( MOAIAction )
	RTTI_END
	
	// prop's index is *added* to particle's index;
	// should be initialized to 0 instead of 1
	this->mIndex = 0;
}

//----------------------------------------------------------------//
MOAIParticleSystem::~MOAIParticleSystem () {

	this->ClearStates ();
}

//----------------------------------------------------------------//
u32 MOAIParticleSystem::OnGetModelBounds ( ZLBox& bounds ) {

	if ( this->mSpriteTop ) {
		bounds = this->mParticleBounds;
		return BOUNDS_OK;
	}
	return BOUNDS_EMPTY;
}

//----------------------------------------------------------------//
void MOAIParticleSystem::OnUpdate ( double step ) {

	bool schedule = ( this->mSpriteTop > 0 );

	// clear out the sprites
	this->mSpriteTop = 0;

	this->mParticleBounds.Init ( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );

	// if particles
	if ( this->mHead ) {

		// grab the head then clear out the queue
		MOAIParticle* cursor = this->mHead;
		this->ClearQueue ();
		
		// update the particles and rebuild the queue
		while ( cursor ) {
			MOAIParticle* particle = cursor;
			cursor = cursor->mNext;
			
			// update the particle
			if ( particle->mState ) {
				particle->mState->ProcessParticle ( *this, *particle, step );
			}
			
			// if is still to be killed, move it to the free list, else put it back in the queue
			if ( !particle->mState ) {
				particle->mNext = this->mFree;
				this->mFree = particle;
			}
			else {
				// and put it back in the queue
				this->EnqueueParticle ( *particle );
			}
		}
	}
	
	if ( schedule || this->mSpriteTop ) {
		this->ScheduleUpdate ();
	}
}

//----------------------------------------------------------------//
bool MOAIParticleSystem::PushParticle ( float x, float y ) {
	
	return this->PushParticle ( x, y, 0.0f, 0.0f, 0 );
}

//----------------------------------------------------------------//
bool MOAIParticleSystem::PushParticle ( float x, float y, float dx, float dy ) {
	
	return this->PushParticle ( x, y, 0.0f, dx, dy, 0.0f, 0 );
}

//----------------------------------------------------------------//
bool MOAIParticleSystem::PushParticle ( float x, float y, float dx, float dy, u32 stateIdx ) {
	
	return this->PushParticle ( x, y, 0.0f, dx, dy, 0.0f, stateIdx );
}

//----------------------------------------------------------------//
bool MOAIParticleSystem::PushParticle ( float x, float y, float z, float dx, float dy, float dz, u32 stateIdx ) {
	
	if (( !this->mFree ) && this->mCapParticles ) {
		return false;
	}
	
	MOAIParticleState* state = this->GetState ( stateIdx );
	if ( !state ) return false;
	
	MOAIParticle* particle = 0;
	
	if ( this->mFree ) {
		particle = this->mFree;
		this->mFree = particle->mNext;
	}
	else if ( this->mHead ) {
		particle = this->mHead;
		this->mHead = particle->mNext;
	}
	
	if ( particle ) {
		
		float* r = particle->mData;
		
		r [ MOAIParticle::PARTICLE_X ] = x;
		r [ MOAIParticle::PARTICLE_Y ] = y;
		r [ MOAIParticle::PARTICLE_Z ] = z;
		
		r [ MOAIParticle::PARTICLE_DX ] = dx;
		r [ MOAIParticle::PARTICLE_DY ] = dy;
		r [ MOAIParticle::PARTICLE_DZ ] = dz;
		
		for ( u32 i = MOAIParticle::TOTAL_PARTICLE_REG; i < this->mParticleSize; ++i ) {
			r [ i ] = 0.0f;
		}
		
		state->InitParticle ( *this, *particle );
		this->EnqueueParticle ( *particle );
		
		return true;
	}
	return false;
}

//----------------------------------------------------------------//
bool MOAIParticleSystem::PushSprite ( const AKUParticleSprite& sprite ) {

	u32 size = this->mSprites.Size ();
	
	if ( size && this->mDeck ) {
	
		if (( this->mSpriteTop >= size ) && this->mCapSprites ) {
			return false;
		}
		
		u32 idx = ( this->mSpriteTop++ ) % size;
		this->mSprites [ idx ] = sprite;
		
		// TODO: need to take rotation into account
		ZLBox bounds = this->mDeck->GetBounds ( MOAIDeckRemapper::Remap ( this->mRemapper, sprite.mGfxID ));
		
		ZLVec3D offset ( sprite.mXLoc, sprite.mYLoc, sprite.mZLoc );
		ZLVec3D scale ( sprite.mXScl, sprite.mYScl, 0.0f );
		
		bounds.Scale ( scale );
		
		float radius = bounds.GetMaxExtent () * 1.4f; // handles case when bounds are rotated
		
		bounds.mMin.Init ( -radius, -radius, 0.0f );
		bounds.mMax.Init ( radius, radius, 0.0f );
		
		bounds.Offset ( offset );
		
		if ( this->mSpriteTop == 1 ) {
			this->mParticleBounds = bounds;
		}
		else {
			this->mParticleBounds.Grow ( bounds );
		}
		return true;
	}
	return false;
}

//----------------------------------------------------------------//
void MOAIParticleSystem::RegisterLuaClass ( MOAILuaState& state ) {

	MOAIGraphicsProp::RegisterLuaClass ( state );
	MOAIAction::RegisterLuaClass ( state );

	state.SetField ( -1, "ORDER_NORMAL",	( u32 )ORDER_NORMAL );
	state.SetField ( -1, "ORDER_REVERSE",	( u32 )ORDER_REVERSE );
}

//----------------------------------------------------------------//
void MOAIParticleSystem::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	MOAIGraphicsProp::RegisterLuaFuncs ( state );
	MOAIAction::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "capParticles",		_capParticles },
		{ "capSprites",			_capSprites },
		{ "clearSprites",		_clearSprites },
		{ "isIdle",				_isIdle },
		{ "getState",			_getState },
		{ "pushParticle",		_pushParticle },
		{ "pushSprite",			_pushSprite },
		{ "reserveParticles",	_reserveParticles },
		{ "reserveSprites",		_reserveSprites },
		{ "reserveStates",		_reserveStates },
		{ "setDrawOrder",		_setDrawOrder },
		{ "setComputeBounds",	_setComputeBounds },
		{ "setSpriteColor",		_setSpriteColor },
		{ "setSpriteDeckIdx",	_setSpriteDeckIdx },
		{ "setState",			_setState },
		{ "surge",				_surge },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIParticleSystem::ReserveParticles ( u32 maxParticles, u32 particleSize ) {
	
	particleSize += MOAIParticle::TOTAL_PARTICLE_REG;
	
	this->mHead = 0;
	this->mTail = 0;
	this->mFree = 0;
	
	this->mParticleSize = particleSize;
	
	this->mParticles.Init ( maxParticles );
	this->mParticleData.Init ( maxParticles * particleSize );
	this->mParticleData.Fill ( 0.0f );
	
	for ( u32 i = 0; i < maxParticles; ++i ) {
		MOAIParticle& particle = this->mParticles [ i ];
		particle.mNext = this->mFree;
		this->mFree = &particle;
		
		if ( particleSize ) {
			particle.mData = &this->mParticleData [ i * particleSize ];
		}
		else {
			particle.mData = 0;
		}
	}
}

//----------------------------------------------------------------//
void MOAIParticleSystem::ReserveSprites ( u32 maxSprites ) {

	this->mSprites.Init ( maxSprites );
}

//----------------------------------------------------------------//
void MOAIParticleSystem::ReserveStates ( u32 total ) {

	this->mStates.Init ( total );
	this->mStates.Fill ( 0 );
}

//----------------------------------------------------------------//
void MOAIParticleSystem::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {

	MOAIGraphicsProp::SerializeIn ( state, serializer );
	MOAIAction::SerializeIn ( state, serializer );
}

//----------------------------------------------------------------//
void MOAIParticleSystem::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {

	MOAIGraphicsProp::SerializeOut ( state, serializer );
	MOAIAction::SerializeOut ( state, serializer );
}
