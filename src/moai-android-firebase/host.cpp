// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-firebase/host.h>
#include <moai-android/JniUtils.h>
#include <host-modules/aku_modules_android_config.h>
#include <moai-android-firebase/MOAIFirebaseAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidFirebaseAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidFirebaseAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidFirebaseContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFirebaseAndroid );
}


