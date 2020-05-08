// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAICOLORBLENDER_H
#define	MOAICOLORBLENDER_H

#include <moai-sim/MOAIColor.h>

class MOAIDeck;
class MOAILayer;

//================================================================//
// MOAIColorBlender
//================================================================//
/**	@lua	MOAIColorBlender
	@text	Color vector that blends between two colors
	
*/
class MOAIColorBlender :
	public MOAIColor {
protected:
	
	float 			mBlendFactor;
	ZLColorVec		mColorA;
	ZLColorVec		mColorB;

	//----------------------------------------------------------------//
	static int		_setBlendFactor		( lua_State* L );
	static int		_setColors			( lua_State* L );

public:
	
	DECL_LUA_FACTORY ( MOAIColorBlender )
	DECL_ATTR_HELPER ( MOAIColorBlender )
		
	//----------------------------------------------------------------//
						MOAIColorBlender			();
						~MOAIColorBlender			();
	void				OnDepNodeUpdate		();
	void				RegisterLuaClass	( MOAILuaState& state );
	void				RegisterLuaFuncs	( MOAILuaState& state );
};

#endif
