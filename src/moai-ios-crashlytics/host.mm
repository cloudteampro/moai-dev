// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-Crashlytics/host.h>
#include <moai-ios-Crashlytics/MOAICrashlyticsIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosCrashlyticsAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosCrashlyticsAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosCrashlyticsContextInitialize () {

	REGISTER_LUA_CLASS ( MOAICrashlyticsIOS );
}
