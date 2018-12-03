// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-yandex-appmetrica/host.h>
#include <moai-android/JniUtils.h>
#include <host-modules/aku_modules_android_config.h>
#include <moai-android-yandex-appmetrica/MOAIYandexAppMetricaAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidYandexAppMetricaAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidYandexAppMetricaAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidYandexAppMetricaContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIYandexAppMetricaAndroid );
}
