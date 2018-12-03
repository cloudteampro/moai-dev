//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef AKU_IOS_FIREBASE_INVITES_HOST_H
#define AKU_IOS_FIREBASE_INVITES_HOST_H

#include <moai-core/host.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

AKU_API void	AKUIosFirebaseInvitesAppFinalize			();
AKU_API void	AKUIosFirebaseInvitesAppInitialize			();
AKU_API void	AKUIosFirebaseInvitesContextInitialize		();

#endif

// - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url
//             options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
//   return [self application:app
//                    openURL:url
//          sourceApplication:options[UIApplicationOpenURLOptionsSourceApplicationKey]
//                 annotation:options[UIApplicationOpenURLOptionsAnnotationKey]];
// }

// - (BOOL)application:(UIApplication *)application
//             openURL:(NSURL *)url
//   sourceApplication:(NSString *)sourceApplication
//          annotation:(id)annotation {
//   if ([[GIDSignIn sharedInstance] handleURL:url
//                       sourceApplication:sourceApplication
//                                  annotation:annotation]) {
//     return YES;
//   }
//   // Handle App Invite requests
//   return [FIRInvites handleUniversalLink:url
//                               completion:^(FIRReceivedInvite * _Nullable receivedInvite,
//                                            NSError * _Nullable error) {
//     // ...
//   }];
// }