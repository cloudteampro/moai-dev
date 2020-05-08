// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-appsflyer/MOAIAppsFlyerAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize ChartBoost.
	
	@in 	string	devKey			AppsFlyer account Dev Key.
	@out 	nil
*/
int	MOAIAppsFlyerAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAppsFlyerAndroid, "" )

	MOAIJString jdevKey	= self->GetJString ( state.GetValue < cc8* >( 1, 0 ));

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )jdevKey );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackAdView
	@text	Tracking Event Ad Show.
	
	@in
	@out 	nil
*/
int	MOAIAppsFlyerAndroid::_trackAdView ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAppsFlyerAndroid, "" )

	MOAIJString jplacement = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));

	self->CallStaticVoidMethod ( self->mJava_TrackAdView, ( jstring )jplacement );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackEvent
	@text	Tracking Event.
	
	@in
	@out 	nil
*/
int	MOAIAppsFlyerAndroid::_trackEvent ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAppsFlyerAndroid, "" )

	// MOAIJString jcurrency = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	// float revenue = state.GetValue < float >( 2, 0.0f );

	self->CallStaticVoidMethod ( self->mJava_TrackEvent );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackPurchase
	@text	Tracking Purchase.
	
	@in revenue
	@in currency
	@out 	nil
*/
int	MOAIAppsFlyerAndroid::_trackPurchase ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAppsFlyerAndroid, "" )

	float revenue = state.GetValue < float >( 1, 0.0f );
	MOAIJString jcurrency = self->GetJString ( state.GetValue < cc8* >( 2, 0 ));

	self->CallStaticVoidMethod ( self->mJava_TrackPurchase, ( jfloat )revenue, ( jstring )jcurrency );

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	tracklevelAchieved
	@text	Tracking Level Achieved.
	
	@in
	@out 	nil
*/
int	MOAIAppsFlyerAndroid::_trackLevelAchieved ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAppsFlyerAndroid, "" )

	int level = state.GetValue < int >( 1, 0 );

	self->CallStaticVoidMethod ( self->mJava_TrackLevelAchieved, ( jint )level );

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	validateAndTrackPurchase
	@text	Validate And Track Event Purchase.
	
	@in
	@out 	nil
*/
int	MOAIAppsFlyerAndroid::_validateAndTrackInAppPurchase ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIAppsFlyerAndroid, "" )

	MOAIJString jpublicKey = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	MOAIJString jsignature = self->GetJString ( state.GetValue < cc8* >( 2, 0 ));
	MOAIJString jpurchaseData = self->GetJString ( state.GetValue < cc8* >( 3, 0 ));
	MOAIJString jprice = self->GetJString ( state.GetValue < cc8* >( 4, 0 ));
	MOAIJString jcurrency = self->GetJString ( state.GetValue < cc8* >( 5, 0 ));

	self->CallStaticVoidMethod ( self->mJava_ValidateAndTrackInAppPurchase, ( jstring )jpublicKey, ( jstring )jsignature, ( jstring )jpurchaseData, ( jstring )jprice, ( jstring )jcurrency );

	return 0;
}


//================================================================//
// MOAIAppsFlyerAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIAppsFlyerAndroid::MOAIAppsFlyerAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/appsflyer/MoaiAppsFlyer" );

	this->mJava_Init							= this->GetStaticMethod ( "init", "(Ljava/lang/String;)V" );
	this->mJava_TrackAdView						= this->GetStaticMethod ( "trackAdView", "(Ljava/lang/String;)V" );
	this->mJava_TrackEvent						= this->GetStaticMethod ( "trackEvent", "()V" );
	this->mJava_TrackPurchase					= this->GetStaticMethod ( "trackPurchase", "(FLjava/lang/String;)V" );
	this->mJava_TrackLevelAchieved				= this->GetStaticMethod ( "trackLevelAchieved", "(I)V" );
	this->mJava_ValidateAndTrackInAppPurchase	= this->GetStaticMethod ( "validateAndTrackInAppPurchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIAppsFlyerAndroid::~MOAIAppsFlyerAndroid () {
}

//----------------------------------------------------------------//
void MOAIAppsFlyerAndroid::PurchaseValidateFailure ( cc8* error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( PURCHASE_VALIDATE_FAILURE, state )) {
		
		state.Push ( error );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAppsFlyerAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "PURCHASE_VALIDATE_FAILURE",				( u32 )PURCHASE_VALIDATE_FAILURE );
	state.SetField ( -1, "PURCHASE_VALIDATE_SUCCESS",				( u32 )PURCHASE_VALIDATE_SUCCESS );

	luaL_Reg regTable [] = {
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIAppsFlyerAndroid > },
		{ "init",							_init },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIAppsFlyerAndroid > },
		{ "trackAdView",					_trackAdView },
		{ "trackEvent",						_trackEvent },
		{ "trackLevelAchieved",				_trackLevelAchieved },
		{ "trackPurchase",					_trackPurchase },
		{ "validateAndTrackInAppPurchase",	_validateAndTrackInAppPurchase },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_appsflyer_MoaiAppsFlyer_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	if ( MOAIAppsFlyerAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_appsflyer_MoaiAppsFlyer_AKUInvokeListener\n" );
		MOAIAppsFlyerAndroid::Get ().InvokeListener (( u32 )eventID );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_appsflyer_MoaiAppsFlyer_PurchaseValidateFailure ( JNIEnv* env, jclass obj, jstring jerror ) {

	if ( MOAIAppsFlyerAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_appsflyer_MoaiAppsFlyer_PurchaseValidateFailure\n" );

		JNI_GET_CSTRING ( jerror, error );
		MOAIAppsFlyerAndroid::Get ().PurchaseValidateFailure ( error );
		JNI_RELEASE_CSTRING ( jerror, error );
	}
}

