// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAISKINNEDMESHSHADER_VSH_H
#define	MOAISKINNEDMESHSHADER_VSH_H

#define SHADER(str) #str

static cc8* _skinnedMeshShaderVSH = SHADER (

	attribute vec4 position;
	attribute vec2 uv;
	attribute vec4 boneWeight;
	attribute vec4 boneIndex;
	attribute vec4 color;

	uniform mat4 transform;
	uniform vec4 ucolor;
	
	// 3 vectors per matrix, max 40 bones (120 slots total)
	uniform vec4 palette [ 120 ];

	varying LOWP vec4 colorVarying;
	varying MEDP vec2 uvVarying;

	void main () {
		float weight = boneWeight [ 0 ];
		int index = int ( boneIndex [ 0 ]) * 3;
		
		vec4 r0 = palette [ index ] * weight;
		vec4 r1 = palette [ index + 1 ] * weight;
		vec4 r2 = palette [ index + 2 ] * weight;
		
		weight = boneWeight [ 1 ];
		if ( weight > 0.0 ) {
			
			index = int ( boneIndex [ 1 ]) * 3;
			r0 = r0 + palette [ index ] * weight;
			r1 = r1 + palette [ index + 1 ] * weight;
			r2 = r2 + palette [ index + 2 ] * weight;
			
			weight = boneWeight [ 2 ];
			if ( weight > 0.0 ) {
				
				index = int ( boneIndex [ 2 ]) * 3;
				r0 = r0 + palette [ index ] * weight;
				r1 = r1 + palette [ index + 1 ] * weight;
				r2 = r2 + palette [ index + 2 ] * weight;
			
				weight = boneWeight [ 3 ];
				if ( weight > 0.0 ) {
				
					index = int ( boneIndex [ 3 ]) * 3;
					r0 = r0 + palette [ index ] * weight;
					r1 = r1 + palette [ index + 1 ] * weight;
					r2 = r2 + palette [ index + 2 ] * weight;
				}
			}
		}
		
		vec4 skinnedPosition;
		skinnedPosition.x = dot ( position, r0 );
		skinnedPosition.y = dot ( position, r1 );
		skinnedPosition.z = dot ( position, r2 );
		skinnedPosition.w = position.w;
		
		gl_Position = skinnedPosition * transform;

		uvVarying = uv;
		colorVarying = color * ucolor;
	}
);

#endif
