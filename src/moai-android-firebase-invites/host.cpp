// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-firebase-invites/host.h>
#include <moai-android/JniUtils.h>
#include <host-modules/aku_modules_android_config.h>
#include <moai-android-firebase-invites/MOAIFirebaseInvitesAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidFirebaseInvitesAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidFirebaseInvitesAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidFirebaseInvitesContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFirebaseInvitesAndroid );
}
