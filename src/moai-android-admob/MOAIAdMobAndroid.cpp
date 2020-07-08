//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved.
// http://cloudteam.pro
//----------------------------------------------------------------//

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/JniUtils.h>
#include <moai-android-admob/MOAIAdMobAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	show
	@text	Request an ad display if a cached ad is available.

	@out 	boolean
*/
int MOAIAdMobAndroid::_show ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAdMobAndroid, "" )

	MOAIJString placementName = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_Show, ( jstring )placementName ));
	return 1;
}

//----------------------------------------------------------------//
/**	@name	showInterstitial
	@text	Request an ad display if a cached ad is available.

	@out 	boolean
*/
int MOAIAdMobAndroid::_showInterstitial ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAdMobAndroid, "" )

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_ShowInterstitial ));
	return 1;
}

//----------------------------------------------------------------//
/**	@name	isLoaded
	@text	Check whether ad is ready to be shown

	@out 	boolean
*/
int MOAIAdMobAndroid::_isLoaded ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAdMobAndroid, "" )

	MOAIJString placementName = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_IsLoaded, ( jstring )placementName ));
	return 1;
}

//----------------------------------------------------------------//
/**	@name	isInterstitialLoaded
	@text	Check whether ad is ready to be shown

	@out 	boolean
*/
int MOAIAdMobAndroid::_isInterstitialLoaded ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAdMobAndroid, "" )

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_IsInterstitialLoaded ));
	return 1;
}

//----------------------------------------------------------------//
/** @name   init
	@text   Initialize AdMob.

	@in     string  gameId      Your game id
	@out    nil
*/
int MOAIAdMobAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAdMobAndroid, "" )

	MOAIJString appID = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	jobject jbundle = NULL;
	if ( state.IsType ( 2, LUA_TTABLE ) ) {
		jbundle = self->BundleFromLua( L, 2 );
	}

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )appID, jbundle );
	return 0;
}

//----------------------------------------------------------------//
/** @name   loadAd
	@text   Load VideoAd.

	@in     string  unitId      Your unit ad id
	@out    nil
*/
int MOAIAdMobAndroid::_loadAd ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAdMobAndroid, "" )

	MOAIJString placementName = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	self->CallStaticVoidMethod ( self->mJava_LoadAd, ( jstring )placementName );
	return 0;
}

//----------------------------------------------------------------//
/** @name   loadInterstitial
	@text   Load VideoInterstitial.

	@in     string  unitId      Your unit ad id
	@out    nil
*/
int MOAIAdMobAndroid::_loadInterstitial ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAdMobAndroid, "" )

	MOAIJString unitID = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	self->CallStaticVoidMethod ( self->mJava_LoadInterstitial, ( jstring )unitID );
	return 0;
}

//================================================================//
// MOAIAdMobAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIAdMobAndroid::MOAIAdMobAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )

	this->SetClass ( "com/moaisdk/admob/MoaiAdMob" );

	this->mJava_Show					= this->GetStaticMethod ( "show", "(Ljava/lang/String;)Z" );
	this->mJava_ShowInterstitial		= this->GetStaticMethod ( "showInterstitial", "()Z" );
	this->mJava_Init					= this->GetStaticMethod ( "init", "(Ljava/lang/String;Landroid/os/Bundle;)V" );
	this->mJava_IsLoaded				= this->GetStaticMethod ( "isLoaded", "(Ljava/lang/String;)Z" );
	this->mJava_IsInterstitialLoaded	= this->GetStaticMethod ( "isInterstitialLoaded", "()Z" );
	this->mJava_LoadAd					= this->GetStaticMethod ( "loadAd", "(Ljava/lang/String;)V" );
	this->mJava_LoadInterstitial		= this->GetStaticMethod ( "loadInterstitial", "(Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIAdMobAndroid::~MOAIAdMobAndroid () {

}

//----------------------------------------------------------------//
void MOAIAdMobAndroid::NotifyVideoFinished ( int result ) {
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ADMOB_REWARDED_FINISH, state )) {

		state.Push ( result );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAdMobAndroid::NotifyVideoClosed ( cc8* placementName ) {
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ADMOB_REWARDED_CLOSED, state )) {

		state.Push ( placementName );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAdMobAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "ADMOB_READY",				( u32 )ADMOB_READY );
	state.SetField ( -1, "ADMOB_OPENED",			( u32 )ADMOB_OPENED );
	state.SetField ( -1, "ADMOB_ERROR",				( u32 )ADMOB_ERROR );
	state.SetField ( -1, "ADMOB_CLOSED",			( u32 )ADMOB_CLOSED );
	state.SetField ( -1, "ADMOB_REWARDED_READY",	( u32 )ADMOB_REWARDED_READY );
	state.SetField ( -1, "ADMOB_REWARDED_START",	( u32 )ADMOB_REWARDED_START );
	state.SetField ( -1, "ADMOB_REWARDED_FINISH",	( u32 )ADMOB_REWARDED_FINISH );
	state.SetField ( -1, "ADMOB_REWARDED_ERROR",	( u32 )ADMOB_REWARDED_ERROR );
	state.SetField ( -1, "ADMOB_REWARDED_CLOSED",	( u32 )ADMOB_REWARDED_CLOSED );

	luaL_Reg regTable [] = {
		{ "isLoaded",						_isLoaded },
		{ "isInterstitialLoaded",			_isInterstitialLoaded },
		{ "loadInterstitial",				_loadInterstitial },
		{ "loadAd",							_loadAd },
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIAdMobAndroid > },
		{ "init",							_init },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIAdMobAndroid > },
		{ "show",							_show },
		{ "showInterstitial",				_showInterstitial },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MOAIAdMobAndroid JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_admob_MoaiAdMob_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	if ( MOAIAdMobAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_admob_MoaiAdMob_AKUInvokeListener\n" );

		MOAIAdMobAndroid::Get ().InvokeListener (( u32 )eventID );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_admob_MoaiAdMob_AKUVideoCompleted ( JNIEnv* env, jclass obj, jint result ) {

	if ( MOAIAdMobAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_admob_MoaiAdMob_AKUVideoCompleted\n" );

		MOAIAdMobAndroid::Get ().NotifyVideoFinished ( result );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_admob_MoaiAdMob_AKUVideoClosed ( JNIEnv* env, jclass obj, jstring jplacementName ) {

	if ( MOAIAdMobAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_admob_MoaiAdMob_AKUVideoClosed\n" );

		JNI_GET_CSTRING ( jplacementName, placementName );
		MOAIAdMobAndroid::Get ().NotifyVideoClosed ( placementName );
		JNI_RELEASE_CSTRING ( jplacementName, placementName );
	}
}
