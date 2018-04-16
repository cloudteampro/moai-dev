// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-fyber/host.h>
#include <moai-android/JniUtils.h>
#include <host-modules/aku_modules_android_config.h>
#include <moai-android-fyber/MOAIFyberAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidFyberAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidFyberAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidFyberContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFyberAndroid );
}