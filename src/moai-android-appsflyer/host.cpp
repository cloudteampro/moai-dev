// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-appsflyer/host.h>
#include <moai-android/JniUtils.h>
#include <host-modules/aku_modules_android_config.h>
#include <moai-android-appsflyer/MOAIAppsFlyerAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidAppsFlyerAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidAppsFlyerAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidAppsFlyerContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIAppsFlyerAndroid );
}
