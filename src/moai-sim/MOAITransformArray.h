// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAITRANSFORMARRAY_H
#define	MOAITRANSFORMARRAY_H

#include <moai-sim/MOAINode.h>

class MOAITransform;

//================================================================//
// MOAITransformArray
//================================================================//
/**	@name	MOAITransformArray
	@text	Array of transforms (for instance, a set of Bones in a skeletal animation).
*/
class MOAITransformArray :
public virtual MOAINode {
private:
	
	ZLLeanArray < MOAITransform* >				mTransforms;
	ZLLeanArray < ZLMatrix4x4 >					mInvBindPose;
	
	//----------------------------------------------------------------//
	static int		_getTransform				( lua_State* L );
	static int		_reserve					( lua_State* L );
	static int		_setTransform				( lua_State* L );

	//----------------------------------------------------------------//
	void			OnDepNodeUpdate				();
	
public:
	
	DECL_LUA_FACTORY ( MOAITransformArray )
	
	//----------------------------------------------------------------//
	void			Clear						();
	ZLMatrix4x4&	GetInvBindPose				( u32 idx );
	MOAITransform*	GetTransform				( u32 idx );
					MOAITransformArray			();
					~MOAITransformArray			();
	void			RegisterLuaClass			( MOAILuaState& state );
	void			RegisterLuaFuncs			( MOAILuaState& state );
	void			Reserve						( u32 total );
	void			SetTransform				( u32 idx, MOAITransform* transform, ZLMatrix4x4& invBindPose );
	void			SerializeIn					( MOAILuaState& state, MOAIDeserializer& serializer );
	void			SerializeOut				( MOAILuaState& state, MOAISerializer& serializer );
	u32				Size						();
};

#endif