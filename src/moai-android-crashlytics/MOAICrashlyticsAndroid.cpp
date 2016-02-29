// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android-crashlytics/MOAICrashlyticsAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/** TODO: doc
*/
int MOAICrashlyticsAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAICrashlyticsAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_Init );
	MOAICrashlyticsAndroid::Get ().Init ();

	return 0;
}

//----------------------------------------------------------------//
/** TODO: doc
*/
int MOAICrashlyticsAndroid::_log ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* msg = state.GetValue < cc8* >( 1, 0 );
	if ( msg ) {
		MOAICrashlyticsAndroid::Get ().Log ( msg );	
	}
	return 0;
}

//----------------------------------------------------------------//
/** TODO: doc
*/
int MOAICrashlyticsAndroid::_reportTraceback ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAICrashlyticsAndroid, "" )

	MOAIJString jerror = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	if ( state.IsType ( 2, LUA_TTABLE ) ) {

		JNIEnv*	env = self->Env ();
		
		jclass clazz = env->FindClass ( "android/os/Bundle" );
		jmethodID init = env->GetMethodID ( clazz, "<init>", "()V" );
		jmethodID putStr = env->GetMethodID ( clazz, "putString", "(Ljava/lang/String;Ljava/lang/String;)V" );
		jmethodID putInt = env->GetMethodID ( clazz, "putInt", "(Ljava/lang/String;I)V" );

		MOAIJString jkeyFile = self->GetJString ( "file" );
		MOAIJString jkeyFunc = self->GetJString ( "func" );
		MOAIJString jkeyLine = self->GetJString ( "line" );

		u32 total = state.GetTableSize ( 2 );
		jobjectArray stackTrace = env->NewObjectArray ( total, clazz, 0 );
		
		int itr = state.PushTableItr ( 2 );
		for ( u32 i = 0; state.TableItrNext ( itr ) && i < total; ++i ) {
			
			if ( state.IsType ( -1, LUA_TTABLE )) {
				jobject bundle = env->NewObject ( clazz, init );

				cc8* filename = state.GetField < cc8* >( -1, "file", "?" );
				cc8* funcname = state.GetField < cc8* >( -1, "func", "?" );
				int line = state.GetField < int >( -1, "line", 0 );
				
				MOAIJString jfile = self->GetJString ( filename );
				MOAIJString jfunc = self->GetJString ( funcname );

				env->CallVoidMethod ( bundle, putStr, ( jstring )jkeyFile, ( jstring )jfile );
				env->CallVoidMethod ( bundle, putStr, ( jstring )jkeyFunc, ( jstring )jfunc );
				env->CallVoidMethod ( bundle, putInt, ( jstring )jkeyLine, line );

				env->SetObjectArrayElement ( stackTrace, i, bundle );
			}
		}
		
		self->CallStaticVoidMethod ( self->mJava_ReportTraceback, ( jstring )jerror, stackTrace );
	}


	return 0;
}

//----------------------------------------------------------------//
/** TODO: doc
*/
int MOAICrashlyticsAndroid::_setBool ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* key = state.GetValue < cc8* >( 1, 0 );
	bool val = state.GetValue < bool >( 2, 0 );
	if ( key && val ) {
		STLString value = STLString::build ( "%d", val );
		MOAICrashlyticsAndroid::Get ().Set ( key, value.c_str ());
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO: doc
*/
int MOAICrashlyticsAndroid::_setFloat ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* key = state.GetValue < cc8* >( 1, 0 );
	float val = state.GetValue < float >( 2, 0 );
	if ( key ) {
		STLString value = STLString::build ( "%f", val );
		MOAICrashlyticsAndroid::Get ().Set ( key, value.c_str ());
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO: doc
*/
int MOAICrashlyticsAndroid::_setInt ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* key = state.GetValue < cc8* >( 1, 0 );
	int val = state.GetValue < int >( 2, 0 );
	if ( key ) {
		STLString value = STLString::build ( "%d", val );
		MOAICrashlyticsAndroid::Get ().Set ( key, value.c_str ());
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO: doc
*/
int MOAICrashlyticsAndroid::_setString ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* key = state.GetValue < cc8* >( 1, 0 );
	cc8* val = state.GetValue < cc8* >( 2, 0 );
	if ( key && val ) {
		MOAICrashlyticsAndroid::Get ().Set ( key, val );
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO: doc
*/
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
	
	this->SetClass ( "com/moaisdk/crashlytics/MoaiCrashlytics" );
	this->mJava_Init = this->GetStaticMethod ( "init", "()V" );
	this->mJava_ReportTraceback = this->GetStaticMethod ( "reportTraceback", "(Ljava/lang/String;[Landroid/os/Bundle;)V" );
	
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
		{ "init",				_init },
		{ "log",				_log },
		{ "reportTraceback",	_reportTraceback},
		{ "set",				_setString }, // back compat
		{ "setBool",			_setBool },
		{ "setFloat",			_setFloat },
		{ "setInt",				_setInt },
		{ "setString",			_setString },
		{ "setUser",			_setUser },
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
