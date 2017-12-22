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
// BOOL AKUIosAppsFlyerApplicationOpenURL ( UIApplication* application,  NSURL* url, NSDictionary* options ) {
// 	UNUSED ( application );

// 	[[AppsFlyerTracker sharedTracker] handleOpenURL:url options:options];
//     return YES;
// }

//----------------------------------------------------------------//
BOOL AKUIosAppsFlyerApplicationOpenURL ( UIApplication* application,  NSURL* url, NSString* sourceApplication, id annotation ) {
	UNUSED ( application );

	[[AppsFlyerTracker sharedTracker] handleOpenURL:url sourceApplication:sourceApplication withAnnotation:annotation];
    return YES;
}

//----------------------------------------------------------------//
// BOOL AKUIosAppsFlyerApplicationContinueUserActivity ( UIApplication* application,  NSUserActivity* userActivity, (void (^)(NSArray *_Nullable)) restorationHandler ) {
// 	UNUSED ( application );

// 	[[AppsFlyerTracker sharedTracker] continueUserActivity:userActivity restorationHandler:restorationHandler];
//     return YES;
// }

//----------------------------------------------------------------//
void AKUIosAppsFlyerContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIAppsFlyerIOS );
}