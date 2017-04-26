// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-chartboost/MOAIChartBoostAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIChartBoostAndroid::_cacheInterstitial ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIChartBoostAndroid, "" )
	
	MOAIJString jlocation = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	self->CallStaticVoidMethod ( self->mJava_CacheInterstitial, ( jstring )jlocation );
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIChartBoostAndroid::_cacheRewardedVideo ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIChartBoostAndroid, "" )

	MOAIJString jlocation = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	self->CallStaticVoidMethod ( self->mJava_CacheRewardedVideo, ( jstring )jlocation );
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIChartBoostAndroid::_hasCachedInterstitial ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIChartBoostAndroid, "" )

	MOAIJString jlocation = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	bool result = self->CallStaticBooleanMethod ( self->mJava_HasCachedInterstitial, ( jstring )jlocation );
	state.Push ( result );
	return 1;
}

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIChartBoostAndroid::_hasRewardedVideo ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIChartBoostAndroid, "" )

	MOAIJString jlocation = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));	
	bool result = self->CallStaticBooleanMethod ( self->mJava_HasRewardedVideo, ( jstring )jlocation );
	state.Push ( result );
	return 1;
}

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIChartBoostAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIChartBoostAndroid, "" )

	MOAIJString jappID			= self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	MOAIJString jappSignature	= self->GetJString ( state.GetValue < cc8* >( 2, 0 ));

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )jappID, ( jstring )jappSignature );
	return 0;
}

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIChartBoostAndroid::_showInterstitial ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIChartBoostAndroid, "" )

	MOAIJString jlocation = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	bool result = self->CallStaticBooleanMethod ( self->mJava_ShowInterstitial, ( jstring )jlocation );
	state.Push ( result );
	return 1;
}

//----------------------------------------------------------------//
// TODO: 3dparty doxygen
int	MOAIChartBoostAndroid::_showRewardedVideo ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIChartBoostAndroid, "" )

	MOAIJString jlocation = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	bool result = self->CallStaticBooleanMethod ( self->mJava_ShowRewardedVideo, ( jstring )jlocation );
	state.Push ( result );
	return 1;
}


//================================================================//
// MOAIChartBoostAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIChartBoostAndroid::MOAIChartBoostAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	this->SetClass ( "com/moaisdk/chartboost/MoaiChartBoost" );

	this->mJava_CacheInterstitial		= this->GetStaticMethod ( "cacheInterstitial", "(Ljava/lang/String;)V" );
	this->mJava_CacheRewardedVideo		= this->GetStaticMethod ( "cacheRewardedVideo", "(Ljava/lang/String;)V" );
	this->mJava_HasCachedInterstitial	= this->GetStaticMethod ( "hasCachedInterstitial", "(Ljava/lang/String;)Z" );
	this->mJava_HasRewardedVideo		= this->GetStaticMethod ( "hasRewardedVideo", "(Ljava/lang/String;)Z" );
	this->mJava_Init					= this->GetStaticMethod ( "init", "(Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_ShowInterstitial		= this->GetStaticMethod ( "showInterstitial", "(Ljava/lang/String;)Z" );
	this->mJava_ShowRewardedVideo		= this->GetStaticMethod ( "showRewardedVideo", "(Ljava/lang/String;)Z" );
}

//----------------------------------------------------------------//
MOAIChartBoostAndroid::~MOAIChartBoostAndroid () {
}

//----------------------------------------------------------------//
void MOAIChartBoostAndroid::NotifyRewardedVideoCompleted ( int reward ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( REWARDED_VIDEO_COMPLETED, state )) {
		
		state.Push ( reward );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIChartBoostAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "INTERSTITIAL_LOAD_FAILED",	( u32 )INTERSTITIAL_LOAD_FAILED );
	state.SetField ( -1, "INTERSTITIAL_DISMISSED",		( u32 )INTERSTITIAL_DISMISSED );
	state.SetField ( -1, "REWARDED_VIDEO_DISMISSED",	( u32 )REWARDED_VIDEO_DISMISSED );
	state.SetField ( -1, "REWARDED_VIDEO_WILL_START",	( u32 )REWARDED_VIDEO_WILL_START );
	state.SetField ( -1, "REWARDED_VIDEO_COMPLETED",	( u32 )REWARDED_VIDEO_COMPLETED );
	state.SetField ( -1, "REWARDED_VIDEO_CACHED",		( u32 )REWARDED_VIDEO_CACHED );

	luaL_Reg regTable [] = {
		{ "cacheInterstitial",			_cacheInterstitial },
		{ "cacheRewardedVideo",			_cacheRewardedVideo },
		{ "hasCachedInterstitial",		_hasCachedInterstitial },
		{ "hasRewardedVideo",			_hasRewardedVideo },
		{ "getListener",				&MOAIGlobalEventSource::_getListener < MOAIChartBoostAndroid > },
		{ "init",						_init },
		{ "setListener",				&MOAIGlobalEventSource::_setListener < MOAIChartBoostAndroid > },
		{ "showInterstitial",			_showInterstitial },
		{ "showRewardedVideo",			_showRewardedVideo },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// ChartBoost JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_chartboost_MoaiChartBoost_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	if ( MOAIChartBoostAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_chartboost_MoaiChartBoost_AKUInvokeListener\n" );
		MOAIChartBoostAndroid::Get ().InvokeListener (( u32 )eventID );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_chartboost_MoaiChartBoost_AKURewardedVideoCompleted ( JNIEnv* env, jclass obj, jint reward ) {

	if ( MOAIChartBoostAndroid::IsValid ()) {
		MOAIChartBoostAndroid::Get ().NotifyRewardedVideoCompleted ( reward );
	}
}
