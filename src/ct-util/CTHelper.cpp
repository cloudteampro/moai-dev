// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <ct-util/CTHelper.h>


//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int CTHelper::_stepSim ( lua_State *L ) {
	MOAILuaState state (L);

	if ( !state.CheckParams ( 1, "N" )) return 0;

	double step = state.GetValue< double >( 1, 0.0f );

	CTHelper::Get().stepSim( step );

	return 0;
}

//----------------------------------------------------------------//
int CTHelper::_setBufferSize ( lua_State *L ) {
	MOAILuaState state (L);

	if ( !state.CheckParams ( 1, "UNN" )) return 0;

	MOAIFrameBuffer* frameBuffer = state.GetLuaObject < MOAIFrameBuffer >( 1, false );

	u32 width = state.GetValue < u32 > ( 2, 0 );
	u32 height = state.GetValue < u32 > ( 3, 0) ;

	if (frameBuffer) {

		frameBuffer->SetBufferSize ( width, height );
	}
	
	return 0;
}

//----------------------------------------------------------------//
int CTHelper::_renderFrameBuffer ( lua_State *L ) {
	MOAILuaState state (L);

	if ( !state.CheckParams ( 1, "U" )) return 0;

	MOAIFrameBuffer* frameBuffer = state.GetLuaObject < MOAIFrameBuffer >( 1, false );

	if (frameBuffer) {

		zglBegin();
		frameBuffer->Render ();
		zglEnd();
	}

	return 0;
}

//----------------------------------------------------------------//
int CTHelper::_setWorldLoc( lua_State *L ){
	MOAILuaState state (L);

	if ( !state.CheckParams ( 1, "UN" )) return 0;

	MOAITransform* dst = state.GetLuaObject< MOAITransform >(1, true);
	float x = state.GetValue< float >( 2, 0.0f );
	float y = state.GetValue< float >( 3, 0.0f );
	float z = state.GetValue< float >( 4, 0.0f );

	ZLVec3D loc;
	loc.Init( x, y, z );		
	const ZLAffine3D* inherit = dst->GetLinkedValue < ZLAffine3D* >( PACK_ATTR ( MOAITransformBase, MOAITransformBase::INHERIT_TRANSFORM ), 0 );

	if( inherit ) {

		ZLAffine3D inverse;
		inverse.Inverse( *inherit ); 
		inverse.Transform( loc );
	}
	dst->SetLoc( loc );	
	dst->ScheduleUpdate();

	return 0;
}

//================================================================//
// CTHelper
//================================================================//

void CTHelper::stepSim ( double step ) {
	MOAISim::Get().GetActionTree().Update (( float )step );		
	MOAINodeMgr::Get ().Update ();
}

//----------------------------------------------------------------//
CTHelper::CTHelper () {
	
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
CTHelper::~CTHelper () {

}

//----------------------------------------------------------------//
void CTHelper::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "stepSim",             	_stepSim },
		{ "setBufferSize",			_setBufferSize },
		{ "renderFrameBuffer",		_renderFrameBuffer },
		{ "setWorldLoc",			_setWorldLoc },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void CTHelper::RegisterLuaFuncs ( MOAILuaState& state ) {
	UNUSED ( state );
}



