// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-facebook/host.h>
#include <moai-ios-facebook/MOAIFacebookIOS.h>

#import <FBSDKCoreKit/FBSDKCoreKit.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosFacebookAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosFacebookAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosFacebookApplicationDidBecomeActive ( UIApplication* application ) {
	UNUSED ( application );
	
	[ FBSDKAppEvents activateApp ];
}

//----------------------------------------------------------------//
BOOL AKUIosFacebookApplicationDidFinishLaunchingWithOptions ( UIApplication* application, NSDictionary* launchOptions ) {

	[[ FBSDKApplicationDelegate sharedInstance ] application:application didFinishLaunchingWithOptions:launchOptions ];

	// UIUserNotificationType userNotificationTypes = (UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIUserNotificationTypeSound);
	// UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:userNotificationTypes categories:nil];
	// [[UIApplication sharedApplication] registerUserNotificationSettings:settings];
	// [[UIApplication sharedApplication] registerForRemoteNotifications];

	return YES;
}

//----------------------------------------------------------------//
BOOL AKUIosFacebookApplicationOpenURL ( UIApplication* application,  NSURL* url, NSString* sourceApplication, id annotation ) {

	return [[ FBSDKApplicationDelegate sharedInstance ] application:application openURL:url sourceApplication:sourceApplication annotation:annotation ];
}

//----------------------------------------------------------------//
void AKUIosFacebookApplicationDidRegisterForRemoteNotificationsWithDeviceToken ( UIApplication* application,  NSData* deviceToken ) {
	UNUSED ( application );

	// [FBSDKAppEvents setPushNotificationsDeviceToken:deviceToken];
}

//----------------------------------------------------------------//
void AKUIosFacebookApplicationDidReceiveRemoteNotification ( UIApplication* application,  NSDictionary* userInfo ) {
	UNUSED ( application );

	[FBSDKAppEvents logPushNotificationOpen:userInfo];
}

//----------------------------------------------------------------//
void AKUIosFacebookApplicationHandleActionWithIdentifier ( UIApplication* application,  NSString* identifier, NSDictionary* userInfo ) {
	UNUSED ( application );

	[FBSDKAppEvents logPushNotificationOpen:userInfo action:identifier];
}

//----------------------------------------------------------------//
void AKUIosFacebookContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFacebookIOS );
}
