//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef AKU_IOS_APPSFLYER_HOST_H
#define AKU_IOS_APPSFLYER_HOST_H

#include <moai-core/host.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

AKU_API void	AKUIosAppsFlyerAppFinalize				();
AKU_API void	AKUIosAppsFlyerAppInitialize			();
AKU_API void	AKUIosAppsFlyerApplicationDidBecomeActive				( UIApplication* application );
// AKU_API BOOL 	AKUIosAppsFlyerApplicationOpenURL 		( UIApplication* application,  NSURL* url, NSDictionary* options );
AKU_API BOOL 	AKUIosAppsFlyerApplicationOpenURL 		( UIApplication* application,  NSURL* url, NSString* sourceApplication, id annotation );
// AKU_API BOOL 	AKUIosAppsFlyerApplicationContinueUserActivity 			( UIApplication* application,  NSUserActivity* userActivity, (void (^)(NSArray *_Nullable)) restorationHandler );
AKU_API void	AKUIosAppsFlyerContextInitialize		();

#endif