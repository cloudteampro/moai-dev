//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef AKU_IOS_FIREBASE_HOST_H
#define AKU_IOS_FIREBASE_HOST_H

#include <moai-core/host.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

AKU_API void	AKUIosFirebaseAppFinalize								();
AKU_API void	AKUIosFirebaseAppInitialize								();
AKU_API BOOL	AKUIosFirebaseApplicationDidFinishLaunchingWithOptions	( UIApplication* application, NSDictionary* launchOptions );
AKU_API BOOL	AKUIosFirebaseApplicationOpenURL						( UIApplication* application, NSURL* url, NSString* sourceApplication, id annotation );
AKU_API void	AKUIosFirebaseContextInitialize							();

#endif