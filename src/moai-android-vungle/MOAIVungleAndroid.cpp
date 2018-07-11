// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-vungle/MOAIVungleAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
int MOAIVungleAndroid::_displayAdvert ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIVungleAndroid, "" )

	MOAIJString placementId = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	jmethodID displayAdvert = self->GetStaticMethod ( "displayAdvert", "(Ljava/lang/String;)Z" );
	bool result = self->CallStaticBooleanMethod ( displayAdvert, ( jstring )placementId );
	state.Push ( result );
	return 1;
}

//----------------------------------------------------------------//
int	MOAIVungleAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIVungleAndroid, "" )
	
	MOAIJString appID = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	MOAIJString placementId = self->GetJString ( state.GetValue < cc8* >( 2, "" ));

	jmethodID init = self->GetStaticMethod ( "init", "(Ljava/lang/String;Ljava/lang/String;)V" );
	self->CallStaticVoidMethod ( init, ( jstring )appID, ( jstring )placementId );

	return 0;
}

//----------------------------------------------------------------//
int	MOAIVungleAndroid::_isVideoAvailable ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIVungleAndroid, "" )
	
	MOAIJString placementId = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	
	jmethodID isVideoAvailable = self->GetStaticMethod ( "isVideoAvailable", "(Ljava/lang/String;)Z" );
	bool result = self->CallStaticBooleanMethod ( isVideoAvailable, ( jstring )placementId );
	state.Push ( result );
	return 1;
}

//----------------------------------------------------------------//
int	MOAIVungleAndroid::_loadVideo ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIVungleAndroid, "" )
	
	MOAIJString placementId = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	
	jmethodID loadVideo = self->GetStaticMethod ( "loadVideo", "(Ljava/lang/String;)Z" );
	bool result = self->CallStaticBooleanMethod ( loadVideo, ( jstring )placementId );
	state.Push ( result );
	return 1;
}

//================================================================//
// MOAIChartBoostAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIVungleAndroid::MOAIVungleAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	this->SetClass ( "com/moaisdk/vungle/MoaiVungle" );
}

//----------------------------------------------------------------//
MOAIVungleAndroid::~MOAIVungleAndroid () {
}

//----------------------------------------------------------------//
void MOAIVungleAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "VUNGLE_INITIALIZED",	( u32 )VUNGLE_INITIALIZED );
	state.SetField ( -1, "VUNGLE_READY", 		( u32 )VUNGLE_READY );
	state.SetField ( -1, "VUNGLE_START", 		( u32 )VUNGLE_START );
	state.SetField ( -1, "VUNGLE_FINISH", 		( u32 )VUNGLE_FINISH );

	luaL_Reg regTable [] = {
		{ "displayAdvert",		_displayAdvert },
		{ "getListener",		&MOAIGlobalEventSource::_getListener < MOAIVungleAndroid > },
		{ "init",				_init },
		{ "isVideoAvailable",	_isVideoAvailable },
		{ "loadVideo",			_loadVideo },
		{ "setListener",		&MOAIGlobalEventSource::_setListener < MOAIVungleAndroid > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// ChartBoost JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_vungle_MoaiVungle_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_vungle_MoaiVungle_AKUInvokeListener\n" );
	MOAIVungleAndroid::Get ().InvokeListener (( u32 )eventID );
}

