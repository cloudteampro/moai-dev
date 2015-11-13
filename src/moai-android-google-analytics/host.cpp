// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-google-analytics/host.h>
#include <moai-android-google-analytics/MOAIGoogleAnalyticsAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidGoogleAnalyticsAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidGoogleAnalyticsAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidGoogleAnalyticsContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIGoogleAnalyticsAndroid );
	
}