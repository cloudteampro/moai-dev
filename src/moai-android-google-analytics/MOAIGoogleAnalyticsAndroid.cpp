// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef DISABLE_GOOGLEANALYTICS

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/JniUtils.h>
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
	
	JNI_GET_ENV ( jvm, env );
	
	jstring jeventCategory = JNI_GET_JSTRING ( lua_tostring ( state, 1 ));
	jstring jeventAction = JNI_GET_JSTRING ( lua_tostring ( state, 2 ));
	jstring jeventLabel = JNI_GET_JSTRING ( lua_tostring ( state, 3 ));

	int eventValue = lua_tointeger ( state, 4 );

	jclass ga = env->FindClass ( "com/moaisdk/googleanalytics/MoaiGoogleAnalytics" );
	if ( ga == NULL ) {
	
		ZLLogF ( ZLLog::CONSOLE, "MOAIGoogleAnalyticsAndroid: Unable to find java class %s", "com/moaisdk/googleanalytics/MoaiGoogleAnalytics" );
	} else {
	
		jmethodID logEvent = env->GetStaticMethodID ( ga, "logEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V" );
		if ( logEvent == NULL ) {
	
			ZLLogF ( ZLLog::CONSOLE, "MOAIGoogleAnalyticsAndroid: Unable to find static java method %s", "logEvent" );
		} else {
			ZLLogF ( ZLLog::CONSOLE, "MOAIGoogleAnalyticsAndroid: calling google analytics event action = %s", lua_tostring ( state, 2 ) );
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