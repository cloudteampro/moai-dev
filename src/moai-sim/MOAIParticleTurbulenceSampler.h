// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIPARTICLETURBULENCESAMPLER_H
#define	MOAIPARTICLETURBULENCESAMPLER_H

class MOAIImage;

//================================================================//
// MOAIParticleTurbulenceSampler
//================================================================//
class MOAIParticleTurbulenceSampler {
private:

	ZLLeanArray < ZLVec2D >		mVectorField;

	int				mSize;
	bool			mWrap;

	//----------------------------------------------------------------//
	float		GetLuma							( MOAIImage& image, int x, int y );

public:
	
	//----------------------------------------------------------------//
	void		Clear							();
	ZLVec2D		Eval							( const ZLVec2D& loc );
	void		GenerateFromImage				( MOAIImage& image, bool wrap );
				MOAIParticleTurbulenceSampler	();
				~MOAIParticleTurbulenceSampler	();
};

#endif
