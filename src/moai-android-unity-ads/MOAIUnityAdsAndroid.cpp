//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved. 
// http://cloudteam.pro
//----------------------------------------------------------------//

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/JniUtils.h>
#include <moai-android-unity-ads/MOAIUnityAdsAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	init
	@text	Initialize FlurryAds.
	
	@in		string	adSpace			FlurryAds ad type (Interstitials, banners, videos).
	@out 	nil
*/
int MOAIUnityAdsAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )

	ZLLogF ( ZLLog::CONSOLE, "MOAIUnityAdsAndroid::_init\n" );
	jstring jadspace = self->GetJString ( lua_tostring ( state, 1 ));
	self->CallStaticVoidMethod ( self->mJava_Init, jadspace );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	hasCachedAd

	@out 	boolean
*/
int MOAIUnityAdsAndroid::_hasCachedAd ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_HasCachedAd ));
	return 1;
}

//----------------------------------------------------------------//
/**	@name	loadAd
	@text	Request that an ad be cached for later display.
	
	@out 	nil
*/
int MOAIUnityAdsAndroid::_loadAd ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_LoadAd );
}

//----------------------------------------------------------------//
/**	@name	showAd
	@text	Request an ad display if a cached ad is available.
	
	@out 	nil
*/
int MOAIUnityAdsAndroid::_showAd ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_ShowAd );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setAdSpace
	@text	Change ad displaying type like (Interstitials, banners, videos - look at docs for params ad space).
	
	@out 	nil
*/
int MOAIUnityAdsAndroid::_setAdSpace ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )

	ZLLogF ( ZLLog::CONSOLE, "MOAIUnityAdsAndroid::_init\n" );
	jstring jadspace = self->GetJString ( lua_tostring ( state, 1 ));
	self->CallStaticVoidMethod ( self->mJava_SetAdSpace, jadspace );
	return 0;
}

//================================================================//
// MOAIUnityAdsAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIUnityAdsAndroid::MOAIUnityAdsAndroid () {

	RTTI_SINGLE ( MOAILuaObject )

	this->SetClass ( "com/ziplinegames/moai/MoaiFlurryAds" );
	
	this->mJava_Init			= this->GetStaticMethod ( "init", "(Ljava/lang/String;)V" );
	this->mJava_HasCachedAd		= this->GetStaticMethod ( "hasCachedAd", "()Z" );
	this->mJava_LoadAd			= this->GetStaticMethod ( "loadAd", "()V" );
	this->mJava_ShowAd			= this->GetStaticMethod ( "showAd", "()V" );
	this->mJava_SetAdSpace		= this->GetStaticMethod ( "setAdSpace", "(Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIUnityAdsAndroid::~MOAIUnityAdsAndroid () {

}

//----------------------------------------------------------------//
void MOAIUnityAdsAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "AD_LOAD_FAILED",		( u32 )AD_LOAD_FAILED );
	state.SetField ( -1, "AD_DISMISSED", 		( u32 )AD_DISMISSED );
	state.SetField ( -1, "AD_WILL_SHOW", 		( u32 )AD_WILL_SHOW );

	luaL_Reg regTable [] = {
		{ "getListener",		&MOAIGlobalEventSource::_getListener < MOAIUnityAdsAndroid > },
		{ "init",				_init },
		{ "loadAd",				_loadAd },
		{ "setListener",		&MOAIGlobalEventSource::_setListener < MOAIUnityAdsAndroid > },
		{ "showAd",				_showAd },
		{ "hasCachedAd",		_hasCachedAd },
		{ "setAdSpace",			_setAdSpace },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// FlurryAds JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_unityads_MoaiUnityAds_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	ZLLogF ( ZLLog::CONSOLE, "Java_com_moaisdk_unityads_MoaiUnityAds_AKUInvokeListener\n" );
	MOAIUnityAdsAndroid::Get ().InvokeListener (( u32 )eventID );
}