// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <spine/extension.h>
#include <moai-spine/host.h>
#include <moai-spine/headers.h>

//================================================================//
// aku-util
//================================================================//

static bool sIsInitialized = false;

//================================================================//
// Required spine extension functions
//================================================================//
int spAtlasFilterToGL( spAtlasFilter filter ) {
	switch( filter ) {
		case SP_ATLAS_NEAREST:
			return ZGL_SAMPLE_LINEAR;
		case SP_ATLAS_LINEAR:
			return ZGL_SAMPLE_LINEAR;
		case SP_ATLAS_MIPMAP:
			return ZGL_SAMPLE_LINEAR_MIPMAP_LINEAR;
		case SP_ATLAS_MIPMAP_NEAREST_NEAREST:
			return ZGL_SAMPLE_NEAREST_MIPMAP_NEAREST;
		case SP_ATLAS_MIPMAP_LINEAR_NEAREST:
			return ZGL_SAMPLE_LINEAR_MIPMAP_NEAREST;
		case SP_ATLAS_MIPMAP_NEAREST_LINEAR:
			return ZGL_SAMPLE_NEAREST_MIPMAP_LINEAR;
		case SP_ATLAS_MIPMAP_LINEAR_LINEAR:
			return ZGL_SAMPLE_LINEAR_MIPMAP_LINEAR;
	}
	return ZGL_SAMPLE_LINEAR;
}

void _spAtlasPage_createTexture ( spAtlasPage* self, const char* path ) {
	
	MOAILuaStrongRef& createTextureRef = MOAISpine::Get ().GetCreateTextureRef ();
	MOAITextureBase* texture;
	
	if ( MOAILuaRuntime::IsValid () && createTextureRef ) {
		
		MOAIScopedLuaState state = createTextureRef.GetSelf ();
		
		state.Push ( path );
		state.Push ( spAtlasFilterToGL ( self->minFilter ));
		state.Push ( spAtlasFilterToGL ( self->magFilter ));
		state.DebugCall ( 3, 1 );
		
		texture = MOAITexture::AffirmTexture ( state, -1 );
	}
	else {
		
		MOAITexture* fallback = new MOAITexture ();
		fallback->Init ( path, MOAIImageTransform::TRUECOLOR | MOAIImageTransform::PREMULTIPLY_ALPHA );
		fallback->SetFilter ( spAtlasFilterToGL ( self->minFilter ), spAtlasFilterToGL ( self->magFilter ));
		
		texture = ( MOAITextureBase* )fallback;
	}
	
	self->rendererObject = texture;
	
	// Spine docs says that we must set width/height to spAtlasPage in this function.
	// However, width and height values are already set from atlas file.
	// Those values are used to calculate UVs, so not overriding them gives the ability to use different sized textures.
	
	texture->Retain ();
}

//----------------------------------------------------------------//
void _spAtlasPage_disposeTexture ( spAtlasPage* self ) {
	
	MOAITextureBase* texture = ( MOAITextureBase* ) self->rendererObject;
	texture->Release ();
}

//----------------------------------------------------------------//
char* _spUtil_readFile (const char* path, int* length) {
	
	MOAILuaStrongRef& readFileRef = MOAISpine::Get ().GetReadFileRef ();
	
	if ( MOAILuaRuntime::IsValid ()) {
		
		if ( readFileRef ) {
			MOAIScopedLuaState state = readFileRef.GetSelf ();
			state.Push ( path );
			state.DebugCall ( 1, 1 );
			
			path = state.GetValue < cc8* >( -1, path );
			return _readFile ( path, length );
		}
	}
	return _readFile ( path, length );
}

//----------------------------------------------------------------//
void AKUSpineAppFinalize () {
	
	if ( !sIsInitialized ) return;
	sIsInitialized = false;
}

void AKUSpineAppInitialize () {

}

//----------------------------------------------------------------//
void AKUSpineContextInitialize () {

	if ( !sIsInitialized ) {
		sIsInitialized = true;
	}

	REGISTER_LUA_CLASS ( MOAISpine )
	REGISTER_LUA_CLASS ( MOAISpineBone )
	REGISTER_LUA_CLASS ( MOAISpineSkeleton )
	REGISTER_LUA_CLASS ( MOAISpineSkeletonData )
	REGISTER_LUA_CLASS ( MOAISpineSlot )
}
