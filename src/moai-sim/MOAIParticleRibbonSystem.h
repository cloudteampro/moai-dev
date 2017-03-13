// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIPARTICLERIBBONSYSTEM_H
#define	MOAIPARTICLERIBBONSYSTEM_H

#include <moai-sim/MOAIParticleSystem.h>
#include <moai-sim/MOAITexture.h>

//================================================================//
// MOAIParticleRibbonSystem
//================================================================//
/**	@lua	MOAIParticleRibbonSystem
	@text	Render particles as a single connected ribbon
*/
class MOAIParticleRibbonSystem :
	public MOAIParticleSystem {
private:

	// ZLLeanArray < MOAIParticle >	mRibbon;
	// bool			mIsDynamic;
	float			mWidth;
	
	//----------------------------------------------------------------//
	static int		_setWidth					( lua_State* L );
	
public:

	DECL_LUA_FACTORY ( MOAIParticleRibbonSystem )

	//----------------------------------------------------------------//
	void			Draw						( int subPrimID, float lod, MOAIMaterialBatch* materialsOverride );
					MOAIParticleRibbonSystem	();
					~MOAIParticleRibbonSystem	();
	void			RegisterLuaClass			( MOAILuaState& state );
	void			RegisterLuaFuncs			( MOAILuaState& state );
};

#endif
