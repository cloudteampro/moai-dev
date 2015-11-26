// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android-crashlytics/MOAICrashlyticsAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
int MOAICrashlyticsAndroid::_init ( lua_State* L ) {
	
	MOAICrashlyticsAndroid::Get ().Init ();
	return 0;
}

//----------------------------------------------------------------//
int MOAICrashlyticsAndroid::_log ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* msg = state.GetValue < cc8* >( 1, 0 );
	if ( msg ) {
		MOAICrashlyticsAndroid::Get ().Log ( msg );	
	}
	return 0;
}

//----------------------------------------------------------------//
int MOAICrashlyticsAndroid::_set ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* key = state.GetValue < cc8* >( 1, 0 );
	cc8* val = state.GetValue < cc8* >( 2, 0 );
	if ( key && val ) {
		MOAICrashlyticsAndroid::Get ().Set ( key, val );
	}

	return 0;
}

//----------------------------------------------------------------//
int MOAICrashlyticsAndroid::_setUser ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* userId = state.GetValue < cc8* >( 1, 0 );
	cc8* userName = state.GetValue < cc8* >( 2, 0 );
	cc8* userEmail = state.GetValue < cc8* >( 3, 0 );

	MOAICrashlyticsAndroid::Get ().SetUser ( userId, userName, userEmail );
	return 0;
}


//================================================================//
// MOAICrashlyticsAndroid
//================================================================//

//----------------------------------------------------------------//
void MOAICrashlyticsAndroid::Init () {

	if ( !this->mCtx ) {
		this->mCtx = crashlytics_init ();
		if ( this->mCtx == 0 ) { 
			ZLLogF ( ZLLog::CONSOLE, "\n\n\n\n\n" );
			ZLLogF ( ZLLog::CONSOLE, "=====================================================\n" );
			ZLLogF ( ZLLog::CONSOLE, "Crashlytics initialization error\n" );
			ZLLogF ( ZLLog::CONSOLE, "\n\n\n\n\n" );
		}
	}
}

//----------------------------------------------------------------//
void MOAICrashlyticsAndroid::Log ( cc8* message ) {

	if ( this->mCtx ) {
		this->mCtx->log ( this->mCtx, message );
	}
}

//----------------------------------------------------------------//
MOAICrashlyticsAndroid::MOAICrashlyticsAndroid ():
	mCtx ( 0 ) {

	RTTI_SINGLE ( MOAILuaObject )
	
}

//----------------------------------------------------------------//
MOAICrashlyticsAndroid::~MOAICrashlyticsAndroid () {

	if ( this->mCtx ) {
		crashlytics_free ( &mCtx );
		this->mCtx = 0;
	}
}

//----------------------------------------------------------------//
void MOAICrashlyticsAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",		_init },
		{ "log",		_log },
		{ "set",		_set },
		{ "setUser",	_setUser },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAICrashlyticsAndroid::Set ( cc8* key, cc8* value ) {

	if ( this->mCtx ) {
		this->mCtx->set ( this->mCtx, key, value );
	}
}

//----------------------------------------------------------------//
void MOAICrashlyticsAndroid::SetUser ( cc8* userId, cc8* userName, cc8* userEmail ) {

	if ( this->mCtx ) {
		if ( userId ) {
			this->mCtx->set_user_identifier ( this->mCtx, userId );
		}
		if ( userName ) {
			this->mCtx->set_user_name ( this->mCtx, userName );
		}
		if ( userEmail ) {
			this->mCtx->set_user_email ( this->mCtx, userEmail );
		}
	}
}
