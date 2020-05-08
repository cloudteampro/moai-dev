// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-spine-v3/MOAISpineSlot.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@name	lockColor
	@in		MOAISpineSlot self
	@in		bool	lock flag
	@out	nil
*/
int MOAISpineSlot::_lockColor ( lua_State *L ) {
	MOAI_LUA_SETUP ( MOAISpineSlot, "UB" );
	
	self->LockColor( state.GetValue < bool >( 2, true ) );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setColor

	@in		MOAISpineSlot self
	@in		number r
	@in		number g
	@in		number b
	@opt	number a
	@out	nil
*/
int MOAISpineSlot::_setColor ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAISpineSlot, "UNNN" )
	
	float r = state.GetValue < float >( 2, 1.0f );
	float g = state.GetValue < float >( 3, 1.0f );
	float b = state.GetValue < float >( 4, 1.0f );
	float a = state.GetValue < float >( 5, 1.0f );
	
	if ( self->mSlot ) {
		self->mSlot->color.r = r;
		self->mSlot->color.g = g;
		self->mSlot->color.b = b;
		self->mSlot->color.a = a;
	}
	self->Set ( r, g, b, a );
	self->ScheduleUpdate ();
	
	return 0;
}

//================================================================//
// MOAISpine
//================================================================//

//----------------------------------------------------------------//
bool MOAISpineSlot::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {

	if ( mSlot && MOAIColor::MOAIColorAttr::Check ( attrID )) {
		
		switch ( UNPACK_ATTR ( attrID )) {
			case MOAIColor::ATTR_R_COL: {
				if ( mLocked ) break;
				mSlot->color.r = attrOp.Apply ( mSlot->color.r, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				return true;
			}
			case MOAIColor::ATTR_G_COL: {
				if ( mLocked ) break;
				mSlot->color.g = attrOp.Apply ( mSlot->color.g, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				return true;
			}
			case MOAIColor::ATTR_B_COL: {
				if ( mLocked ) break;
				mSlot->color.b = attrOp.Apply ( mSlot->color.b, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				return true;
			}
			case MOAIColor::ATTR_A_COL: {
				if ( mLocked ) break;
				mSlot->color.a = attrOp.Apply ( mSlot->color.a, op, MOAIAttrOp::ATTR_READ_WRITE, MOAIAttrOp::ATTR_TYPE_FLOAT );
				return true;
			}
		}
	}
	
	return MOAIColor::ApplyAttrOp (attrID, attrOp, op );
}


//----------------------------------------------------------------//
void MOAISpineSlot::LockColor ( bool flag ) {
	mLocked = flag;
	
	if ( mSlot ) {
		this->Set ( mSlot->color.r, mSlot->color.g, mSlot->color.b, mSlot->color.a );
		this->mColor.Set ( mSlot->color.r, mSlot->color.g, mSlot->color.b, mSlot->color.a );
	}
}

//----------------------------------------------------------------//
MOAISpineSlot::MOAISpineSlot ():
	mSlot ( 0 ),
	mLocked ( false ) {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIColor )
	RTTI_END
}

//----------------------------------------------------------------//
MOAISpineSlot::~MOAISpineSlot () {
	
}

//----------------------------------------------------------------//
void MOAISpineSlot::OnDepNodeUpdate () {
	
	if ( mSlot ) {
		
		if ( mLocked ) {
			mSlot->color.r = this->mR;
			mSlot->color.g = this->mG;
			mSlot->color.b = this->mB;
			mSlot->color.a = this->mA;
		}
		
		this->Set ( mSlot->color.r, mSlot->color.g, mSlot->color.b, mSlot->color.a );
		this->mColor = *this;
	}
}

//----------------------------------------------------------------//
void MOAISpineSlot::RegisterLuaClass ( MOAILuaState &state ) {

	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAISpineSlot::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIColor::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "lockColor",		_lockColor },
		{ "new",			MOAILogMessages::_alertNewIsUnsupported },
		{ "setColor",		_setColor },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAISpineSlot::SetSlot ( spSlot *slot ) {
	mSlot = slot;
	this->ScheduleUpdate ();
}