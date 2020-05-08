// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIBONEARRAY_H
#define	MOAIBONEARRAY_H

#include <moai-sim/MOAINode.h>

class MOAIBone;

//================================================================//
// MOAIBoneArray
//================================================================//
/**	@name	MOAIBoneArray
	@text	Array of MOAIBone for binding to skinning shader
*/
class MOAIBoneArray :
public virtual MOAINode {
private:
	
	ZLLeanArray < MOAIBone* >					mBones;
	ZLLeanArray < ZLVec4D >						mBuffer;
	
	//----------------------------------------------------------------//
	static int		_getBone					( lua_State* L );
	static int		_reserve					( lua_State* L );
	static int		_setBone					( lua_State* L );

	//----------------------------------------------------------------//
	void			OnDepNodeUpdate				();
	
public:
	
	DECL_ATTR_HELPER ( MOAIBoneArray )
	DECL_LUA_FACTORY ( MOAIBoneArray )
	
	enum {
		ATTR_VEC4_ARRAY,
		
		TOTAL_ATTR
	};
	
	//----------------------------------------------------------------//
	bool			ApplyAttrOp					( u32 attrID, MOAIAttrOp& attrOp, u32 op );
	void			Clear						();
	void*			GetBuffer					();
	ZLMatrix4x4&	GetInvBindPose				( u32 idx );
	MOAIBone*		GetBone						( u32 idx );
					MOAIBoneArray				();
					~MOAIBoneArray				();
	void			RegisterLuaClass			( MOAILuaState& state );
	void			RegisterLuaFuncs			( MOAILuaState& state );
	void			Reserve						( u32 total );
	void			SetBone						( u32 idx, MOAIBone* bone );
	void			SerializeIn					( MOAILuaState& state, MOAIDeserializer& serializer );
	void			SerializeOut				( MOAILuaState& state, MOAISerializer& serializer );
	u32				Size						();
};

#endif