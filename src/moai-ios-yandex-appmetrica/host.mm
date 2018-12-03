// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-yandex-appmetrica/host.h>
#include <moai-ios-yandex-appmetrica/MOAIYandexAppMetricaIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosYandexAppMetricaAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosYandexAppMetricaAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosYandexAppMetricaApplicationDidBecomeActive ( UIApplication* application ) {
	UNUSED ( application );
	
}

//----------------------------------------------------------------//
BOOL AKUIosYandexAppMetricaApplicationOpenURL ( UIApplication* application,  NSURL* url, NSString* sourceApplication, id annotation ) {
	UNUSED ( application );

	[ YMMYandexMetrica handleOpenURL:url ];
	return YES;
}

//----------------------------------------------------------------//
void AKUIosYandexAppMetricaContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIYandexAppMetricaIOS );
}
