// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-yandex-appmetrica/MOAIYandexAppMetricaAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize ChartBoost.
	
	@in 	string	devKey			AppsFlyer account Dev Key.
	@out 	nil
*/
int	MOAIYandexAppMetricaAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIYandexAppMetricaAndroid, "" )

	MOAIJString jdevKey	= self->GetJString ( state.GetValue < cc8* >( 1, 0 ));

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )jdevKey );
	return 0;
}


//----------------------------------------------------------------//
/**	@lua	trackEvent
	@text	Tracking Event.
	
	@in
	@out 	nil
*/
int	MOAIYandexAppMetricaAndroid::_trackEvent ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIYandexAppMetricaAndroid, "" )

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
int	MOAIYandexAppMetricaAndroid::_trackPurchase ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIYandexAppMetricaAndroid, "" )

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
int	MOAIYandexAppMetricaAndroid::_trackLevelAchieved ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIYandexAppMetricaAndroid, "" )

	int level = state.GetValue < int >( 1, 0 );

	self->CallStaticVoidMethod ( self->mJava_TrackLevelAchieved, ( jint )level );

	return 0;
}


//================================================================//
// MOAIYandexAppMetricaAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIYandexAppMetricaAndroid::MOAIYandexAppMetricaAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/yandexappmetrica/MoaiYandexAppMetrica" );

	this->mJava_Init					= this->GetStaticMethod ( "init", "(Ljava/lang/String;)V" );
	this->mJava_TrackEvent				= this->GetStaticMethod ( "trackEvent", "()V" );
	this->mJava_TrackPurchase			= this->GetStaticMethod ( "trackPurchase", "(FLjava/lang/String;)V" );
	this->mJava_TrackLevelAchieved		= this->GetStaticMethod ( "trackLevelAchieved", "(I)V" );
}

//----------------------------------------------------------------//
MOAIYandexAppMetricaAndroid::~MOAIYandexAppMetricaAndroid () {
}

//----------------------------------------------------------------//
void MOAIYandexAppMetricaAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",						_init },
		{ "trackEvent",					_trackEvent },
		{ "trackPurchase",				_trackPurchase },
		{ "trackLevelAchieved",			_trackLevelAchieved },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
