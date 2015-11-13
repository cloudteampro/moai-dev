// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef DISABLE_GOOGLEANALYTICS

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/moaiext-jni.h>
#include <moai-android-google-analytics/MOAIGoogleAnalyticsAndroid.h>

extern JavaVM* jvm;

//----------------------------------------------------------------//
/**	@name	logEvent
	@text	Log an event.  
			
	@in		string	event	 The name for the event.
	@in   	table   extra	(optional)  Extra data to send with the event.
	@out 	nil
*/
int MOAIGoogleAnalyticsAndroid::_logEvent ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* eventCategory = lua_tostring ( state, 1 );

	cc8* eventAction = lua_tostring ( state, 2 );

	cc8* eventLabel = lua_tostring ( state, 3 );

	int eventValue = lua_tointeger ( state, 4 );
	
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( eventCategory, jeventCategory );

	JNI_GET_JSTRING ( eventAction, jeventAction );

	JNI_GET_JSTRING ( eventLabel, jeventLabel );

	jclass ga = env->FindClass ( "com/ziplinegames/moai/MoaiGoogleAnalytics" );
	if ( ga == NULL ) {
	
		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGoogleAnalyticsAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGoogleAnalytics" );
	} else {
	
		jmethodID logEvent = env->GetStaticMethodID ( ga, "logEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V" );
		if ( logEvent == NULL ) {
	
			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGoogleAnalyticsAndroid: Unable to find static java method %s", "logEvent" );
		} else {
			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGoogleAnalyticsAndroid: calling google analytics event action = %s", eventAction );
			env->CallStaticVoidMethod ( ga, logEvent, jeventCategory, jeventAction, jeventLabel, eventValue );		
		}
	}
	return 0;
}

//================================================================//
// MOAIGoogleAnalyticsAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIGoogleAnalyticsAndroid::MOAIGoogleAnalyticsAndroid () {

	RTTI_SINGLE ( MOAILuaObject )	
}

//----------------------------------------------------------------//
MOAIGoogleAnalyticsAndroid::~MOAIGoogleAnalyticsAndroid () {

}

//----------------------------------------------------------------//
void MOAIGoogleAnalyticsAndroid::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "logEvent",		_logEvent },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

#endif