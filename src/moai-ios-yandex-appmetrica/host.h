//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef AKU_IOS_YANDEXAPPMETRICA_HOST_H
#define AKU_IOS_YANDEXAPPMETRICA_HOST_H

#include <moai-core/host.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

AKU_API void	AKUIosYandexAppMetricaAppFinalize							();
AKU_API void	AKUIosYandexAppMetricaAppInitialize							();
AKU_API void	AKUIosYandexAppMetricaApplicationDidBecomeActive			( UIApplication* application );
AKU_API BOOL 	AKUIosYandexAppMetricaApplicationOpenURL 					( UIApplication* application,  NSURL* url, NSString* sourceApplication, id annotation );
AKU_API void	AKUIosYandexAppMetricaContextInitialize						();

#endif
