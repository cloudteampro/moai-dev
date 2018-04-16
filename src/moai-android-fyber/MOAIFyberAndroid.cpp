// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-fyber/MOAIFyberAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIFyberAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFyberAndroid, "" )

	MOAIJString jappID			= self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	MOAIJString juserID			= self->GetJString ( state.GetValue < cc8* >( 2, 0 ));
	MOAIJString jsecurityToken	= self->GetJString ( state.GetValue < cc8* >( 3, 0 ));

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )jappID, ( jstring )juserID, ( jstring )jsecurityToken );
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIFyberAndroid::_requestVideo ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFyberAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_RequestVideo );
	return 0;
}

//================================================================//
// MOAIFyberAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIFyberAndroid::MOAIFyberAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/fyber/MoaiFyber" );

	this->mJava_Init				= this->GetStaticMethod ( "init", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_RequestVideo		= this->GetStaticMethod ( "requestVideo", "()V" );
}

//----------------------------------------------------------------//
MOAIFyberAndroid::~MOAIFyberAndroid () {
}

//----------------------------------------------------------------//
void MOAIFyberAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "REWARDED_VIDEO_START",		( u32 )REWARDED_VIDEO_START );
	state.SetField ( -1, "REWARDED_VIDEO_COMPLETED",	( u32 )REWARDED_VIDEO_COMPLETED );
	state.SetField ( -1, "REWARDED_VIDEO_ABORTED",		( u32 )REWARDED_VIDEO_ABORTED );
	state.SetField ( -1, "REWARDED_VIDEO_ERROR",		( u32 )REWARDED_VIDEO_ERROR );			

	luaL_Reg regTable [] = {
		{ "getListener",				&MOAIGlobalEventSource::_getListener < MOAIFyberAndroid > },
		{ "init",						_init },
		{ "setListener",				&MOAIGlobalEventSource::_setListener < MOAIFyberAndroid > },
		{ "requestVideo",				_requestVideo },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// Fyber JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_fyber_MoaiFyber_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	if ( MOAIFyberAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_fyber_MoaiFyber_AKUInvokeListener\n" );
		MOAIFyberAndroid::Get ().InvokeListener (( u32 )eventID );
	}
}
