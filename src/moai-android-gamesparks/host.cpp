// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-gamesparks/host.h>
#include <moai-android/JniUtils.h>
#include <host-modules/aku_modules_android_config.h>
#include <moai-android-gamesparks/MOAIGameSparksAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidGameSparksAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidGameSparksAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidGameSparksContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIGameSparksAndroid );
}
