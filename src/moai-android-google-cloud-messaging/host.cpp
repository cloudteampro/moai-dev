// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-google-cloud-messaging/host.h>
#include <moai-android-google-cloud-messaging/MOAIGoogleCloudMessagingAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidGoogleCloudMessagingAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidGoogleCloudMessagingAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidGoogleCloudMessagingContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIGoogleCloudMessagingAndroid );
	
}