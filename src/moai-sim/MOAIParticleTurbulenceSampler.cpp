// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIParticleTurbulenceSampler.h>
#include <moai-sim/MOAIImage.h>

//================================================================//
// MOAIParticleTurbulenceSampler
//================================================================//

//----------------------------------------------------------------//
void MOAIParticleTurbulenceSampler::Clear () {
	this->mVectorField.Clear ();
}

//----------------------------------------------------------------//
void MOAIParticleTurbulenceSampler::GenerateFromImage ( MOAIImage& image, bool wrap) {
	if ( image.GetWidth () != image.GetHeight ()) {
		MOAILogF ( 0, ZLLog::LOG_ERROR, "MOAIParticleTurbulenceSampler: noise image must be square\n" );
		return;
	}
	
	this->mWrap = wrap;
	this->mSize = image.GetWidth ();
	this->mVectorField.Init ( this->mSize * this->mSize );
	
	for ( u32 j = 0; j < image.GetHeight (); ++j ) {
		for ( u32 i = 0; i < image.GetWidth (); ++i ) {
			
			float dx = this->GetLuma ( image, i, j ) - this->GetLuma ( image, i + 1, j );
			float dy = this->GetLuma ( image, i, j ) - this->GetLuma ( image, i, j + 1 );
			ZLVec2D& vec = this->mVectorField [ j * this->mSize + i ];
			
			// Maximum value for dx and dy is 1, but most common is around 0.01 (for smooth images)
			// Scale velocity field with arbitrary value so that turbulence force magnitude is more aligned with other forces...
			vec.mX = dy * 60.f;
			vec.mY = -dx * 60.f;
		}
	}
}

//----------------------------------------------------------------//
float MOAIParticleTurbulenceSampler::GetLuma ( MOAIImage& image, int x, int y ) {
	
	ZLColorVec color ( image.GetColor ( x % image.GetWidth (), y % image.GetHeight ()));
	return color.GetLuma ();
}

//----------------------------------------------------------------//
ZLVec3D MOAIParticleTurbulenceSampler::Eval ( const ZLVec3D& loc ) {
	
	int i = ZLFloat::Round ( loc.mX );
	int j = ZLFloat::Round ( loc.mY );
	
	if ( this->mWrap && this->mSize != 0 ) {
		i = i % this->mSize;
		if ( i < 0 ) i += this->mSize;

		j = j % this->mSize;
		if ( j < 0 ) j += this->mSize;
	}
	
	if ( i < 0 || j < 0 || i > this->mSize || j > this->mSize ) {
		return ZLVec3D ( 0.f, 0.f, 0.f );
	}
	
	ZLVec3D result;
	result.Init ( this->mVectorField [ j * this->mSize + i ]);
	return result;
}

//----------------------------------------------------------------//
MOAIParticleTurbulenceSampler::MOAIParticleTurbulenceSampler () :
	mSize ( 0 ),
	mWrap ( false ) {
}

//----------------------------------------------------------------//
MOAIParticleTurbulenceSampler::~MOAIParticleTurbulenceSampler () {
}
