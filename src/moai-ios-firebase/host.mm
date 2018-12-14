// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-firebase/host.h>
#include <moai-ios-firebase/MOAIFirebaseIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosFirebaseAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosFirebaseAppInitialize () {
}

//----------------------------------------------------------------//
BOOL AKUIosFirebaseApplicationDidFinishLaunchingWithOptions ( UIApplication* application, NSDictionary* launchOptions ) {

	[FIRApp configure];
	
	return YES;
}

//----------------------------------------------------------------//
BOOL AKUIosFirebaseApplicationOpenURL ( UIApplication* application,  NSURL* url, NSString* sourceApplication, id annotation ) {

	// if ([[GIDSignIn sharedInstance] handleURL:url sourceApplication:sourceApplication annotation:annotation]) {
	//     return YES;
	// }
	
	FIRDynamicLink *dynamicLink = [[ FIRDynamicLinks dynamicLinks ] dynamicLinkFromCustomSchemeURL:url ];
	
	if ( dynamicLink ) {
		if ( dynamicLink.url ) {
			
			NSLog ( @"MOAIFirebaseIOS: OpenURL dynamicLink is %@", url.absoluteString );
			
			NSURLComponents *components = [NSURLComponents componentsWithURL:url resolvingAgainstBaseURL:NO];
			
			NSString* uid = nil;
			for ( NSURLQueryItem *item in components.queryItems ) {
				
				if ([ item.name isEqualToString:@"deep_link_id" ]) {
					
					NSURLComponents *componentsDeep = [NSURLComponents componentsWithURL:[NSURL URLWithString:item.value] resolvingAgainstBaseURL:NO];
					
					for ( NSURLQueryItem *itemDeep in componentsDeep.queryItems ) {
						
						NSLog ( @"MOAIFirebaseIOS: components %@ : %@", itemDeep.name, itemDeep.value );
						if ([ itemDeep.name isEqualToString:@"invitedby" ]) {
							
							uid = itemDeep.value;
						}
					}
				}
			}
			
			if ( uid != nil ) {
			
				MOAIFirebaseIOS::Get ()._invitationId = uid;
				MOAIFirebaseIOS::Get ().InvokeListener ( MOAIFirebaseIOS::PENDING_INVITATION_ID_SUCCEEDED );
			}
			
		} else {
			
			NSLog ( @"MOAIFirebaseIOS: OpenURL dynamicLink empty" );
			// Dynamic link has empty deep link. This situation will happens if
			// Firebase Dynamic Links iOS SDK tried to retrieve pending dynamic link,
			// but pending link is not available for this device/App combination.
			// At this point you may display default onboarding view.
		}
		return YES;
	}
	
	return NO;
	//	return [FIRInvites handleUniversalLink:url completion:^(FIRReceivedInvite * _Nullable receivedInvite, NSError * _Nullable error) {
	//
	//	}];
}

//----------------------------------------------------------------//
void AKUIosFirebaseContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFirebaseIOS );
}
