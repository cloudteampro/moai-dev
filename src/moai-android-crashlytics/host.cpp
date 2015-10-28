// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-crashlytics/host.h>
#include <moai-android-crashlytics/MOAICrashlyticsAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidCrashlyticsAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidCrashlyticsAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidCrashlyticsContextInitialize () {
    
	REGISTER_LUA_CLASS ( MOAICrashlyticsAndroid );
	
}