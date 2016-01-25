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
/**	@name	canShow
	@text	Check whether ad is ready to be shown

	@opt 	zone
	@out 	boolean
*/
int MOAIUnityAdsAndroid::_canShow ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )

	MOAIJString zone = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_CanShow, ( jstring )zone ));
	return 1;
}

//----------------------------------------------------------------//
/** @name   init
	@text   Initialize UnityAds.
	
	@in     string  gameId      Your game id
	@opt    boolean debug       Whether debug mode is active. Default if false
	@opt    boolean test        Whether test mode is active. Default is false
	@out    nil
*/
int MOAIUnityAdsAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )

	MOAIJString appID = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	bool debug = state.GetValue < bool >( 2, false );
	bool test  = state.GetValue < bool >( 3, false );

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )appID, debug, test );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	show
	@text	Request an ad display if a cached ad is available.
	
	@opt 	zone
	@out 	boolean
*/
int MOAIUnityAdsAndroid::_show ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIUnityAdsAndroid, "" )
	
	MOAIJString zone = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_Show, ( jstring )zone ));
	return 1;
}


//================================================================//
// MOAIUnityAdsAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIUnityAdsAndroid::MOAIUnityAdsAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )

	this->SetClass ( "com/moaisdk/unityads/MoaiUnityAds" );
	
	this->mJava_Init						= this->GetStaticMethod ( "init", "(Ljava/lang/String;ZZ)V" );
	this->mJava_CanShow						= this->GetStaticMethod ( "canShow", "(Ljava/lang/String;)Z" );
	this->mJava_Show						= this->GetStaticMethod ( "show", "(Ljava/lang/String;)Z" );
}

//----------------------------------------------------------------//
MOAIUnityAdsAndroid::~MOAIUnityAdsAndroid () {

}

//----------------------------------------------------------------//
void MOAIUnityAdsAndroid::NotifyVideoCompleted ( cc8* reward, bool skipped ) {
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( VIDEO_COMPLETED, state )) {
		
		state.Push ( reward );
		state.Push ( skipped );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIUnityAdsAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "ON_HIDE",					( u32 )ON_HIDE );
	state.SetField ( -1, "ON_SHOW",					( u32 )ON_SHOW );
	state.SetField ( -1, "VIDEO_COMPLETED",			( u32 )VIDEO_COMPLETED );
	state.SetField ( -1, "VIDEO_STARTED",			( u32 )VIDEO_STARTED );

	luaL_Reg regTable [] = {
		{ "canShow",						_canShow },
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIUnityAdsAndroid > },
		{ "init",							_init },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIUnityAdsAndroid > },
		{ "show",							_show },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MOAIUnityAdsAndroid JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_unityads_MoaiUnityAds_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	if ( MOAIUnityAdsAndroid::IsValid ()) {
		ZLLogF ( ZLLog::CONSOLE, "Java_com_moaisdk_unityads_MoaiUnityAds_AKUInvokeListener\n" );
		MOAIUnityAdsAndroid::Get ().InvokeListener (( u32 )eventID );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_unityads_MoaiUnityAds_AKUVideoCompleted ( JNIEnv* env, jclass obj, jstring jreward, jboolean skipped ) {

	if ( MOAIUnityAdsAndroid::IsValid ()) {

		JNI_GET_CSTRING ( jreward, reward );
		MOAIUnityAdsAndroid::Get ().NotifyVideoCompleted ( reward, skipped );
		JNI_RELEASE_CSTRING ( jreward, reward );
	}
}
