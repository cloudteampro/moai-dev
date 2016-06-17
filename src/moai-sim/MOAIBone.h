// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIBONE_H
#define	MOAIBONE_H

#include <moai-sim/MOAITransform.h>

//================================================================//
// MOAIBone
//================================================================//
// TODO: doxygen
class MOAIBone :
	public MOAITransform {
protected:
	
	// Class to mimic fbx transformation stack. 

	ZLAffine3D			mInvBindPose;
	ZLAffine3D			mBoneMtx;
	ZLVec3D				mPreRotation;

	//----------------------------------------------------------------//
	static int			_setInvBindPose				( lua_State* L );
	static int			_setPreRotation				( lua_State* L );
	

	//----------------------------------------------------------------//
	virtual void		BuildLocalToWorldMtx		( ZLAffine3D& localToWorldMtx );

public:

	DECL_LUA_FACTORY ( MOAIBone )
	
	//----------------------------------------------------------------//
	const ZLAffine3D&	GetBoneMtx					() const;
						MOAIBone					();
						~MOAIBone					();
	void				OnDepNodeUpdate				();
	void				RegisterLuaClass			( MOAILuaState& state );
	void				RegisterLuaFuncs			( MOAILuaState& state );
	void				SerializeIn					( MOAILuaState& state, MOAIDeserializer& serializer );
	void				SerializeOut				( MOAILuaState& state, MOAISerializer& serializer );
};

#endif
