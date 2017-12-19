// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-appsflyer/host.h>
#include <moai-ios-appsflyer/MOAIAppsFlyerIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosAppsFlyerAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosAppsFlyerAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosAppsFlyerApplicationDidBecomeActive ( UIApplication* application ) {
	UNUSED ( application );
	
	[[ AppsFlyerTracker sharedTracker ] trackAppLaunch ]; 
}

//----------------------------------------------------------------//
void AKUIosAppsFlyerContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIAppsFlyerIOS );
}
