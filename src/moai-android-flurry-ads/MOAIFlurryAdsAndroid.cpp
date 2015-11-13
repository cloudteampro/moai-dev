//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved. 
// http://cloudteam.pro
//----------------------------------------------------------------//

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/moaiext-jni.h>
#include <moai-android-flurry-ads/MOAIFlurryAdsAndroid.h>

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
int MOAIFlurryAdsAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFlurryAdsAndroid, "" )

	ZLLog::LogF ( ZLLog::CONSOLE, "MOAIFlurryAdsAndroid::_init\n" );
	jstring jadspace = self->GetJString ( lua_tostring ( state, 1 ));
	self->CallStaticVoidMethod ( self->mJava_Init, jadspace );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	hasCachedAd

	@out 	boolean
*/
int MOAIFlurryAdsAndroid::_hasCachedAd ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFlurryAdsAndroid, "" )

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_HasCachedAd ));
	return 1;
}

//----------------------------------------------------------------//
/**	@name	loadAd
	@text	Request that an ad be cached for later display.
	
	@out 	nil
*/
int MOAIFlurryAdsAndroid::_loadAd ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFlurryAdsAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_LoadAd );
}

//----------------------------------------------------------------//
/**	@name	showAd
	@text	Request an ad display if a cached ad is available.
	
	@out 	nil
*/
int MOAIFlurryAdsAndroid::_showAd ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFlurryAdsAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_ShowAd );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setAdSpace
	@text	Change ad displaying type like (Interstitials, banners, videos - look at docs for params ad space).
	
	@out 	nil
*/
int MOAIFlurryAdsAndroid::_setAdSpace ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFlurryAdsAndroid, "" )

	ZLLog::LogF ( ZLLog::CONSOLE, "MOAIFlurryAdsAndroid::_init\n" );
	jstring jadspace = self->GetJString ( lua_tostring ( state, 1 ));
	self->CallStaticVoidMethod ( self->mJava_SetAdSpace, jadspace );
	return 0;
}

//================================================================//
// MOAIFlurryAdsAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIFlurryAdsAndroid::MOAIFlurryAdsAndroid () {

	RTTI_SINGLE ( MOAILuaObject )

	this->SetClass ( "com/ziplinegames/moai/MoaiFlurryAds" );
	
	this->mJava_Init			= this->GetStaticMethod ( "init", "(Ljava/lang/String;)V" );
	this->mJava_HasCachedAd		= this->GetStaticMethod ( "hasCachedAd", "()Z" );
	this->mJava_LoadAd			= this->GetStaticMethod ( "loadAd", "()V" );
	this->mJava_ShowAd			= this->GetStaticMethod ( "showAd", "()V" );
	this->mJava_SetAdSpace		= this->GetStaticMethod ( "setAdSpace", "(Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIFlurryAdsAndroid::~MOAIFlurryAdsAndroid () {

}

//----------------------------------------------------------------//
void MOAIFlurryAdsAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "AD_LOAD_FAILED",		( u32 )AD_LOAD_FAILED );
	state.SetField ( -1, "AD_DISMISSED", 		( u32 )AD_DISMISSED );
	state.SetField ( -1, "AD_WILL_SHOW", 		( u32 )AD_WILL_SHOW );

	luaL_Reg regTable [] = {
		{ "getListener",		&MOAIGlobalEventSource::_getListener < MOAIFlurryAdsAndroid > },
		{ "init",				_init },
		{ "loadAd",				_loadAd },
		{ "setListener",		&MOAIGlobalEventSource::_setListener < MOAIFlurryAdsAndroid > },
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
extern "C" JNIEXPORT void JNICALL Java_com_ziplinegames_moai_MoaiFlurryAds_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	ZLLog::LogF ( ZLLog::CONSOLE, "Java_com_ziplinegames_moai_MoaiFlurryAds_AKUInvokeListener\n" );
	MOAIFlurryAdsAndroid::Get ().InvokeListener (( u32 )eventID );
}