// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	AKU_MODULES_ANDROID_H
#define	AKU_MODULES_ANDROID_H

#include <host-modules/aku_modules_android_config.h>
#include <host-modules/aku_modules.h>

#if AKU_WITH_ANDROID
  #include <moai-android/host.h>
#endif

#if AKU_WITH_ANDROID_ADMOB
	#include <moai-android-admob/host.h>
#endif

#if AKU_WITH_ANDROID_APPSFLYER
	#include <moai-android-appsflyer/host.h>
#endif

#if AKU_WITH_ANDROID_BILLING
	#include <moai-android/host.h>
#endif

#if AKU_WITH_ANDROID_FACEBOOK
	#include <moai-android-facebook/host.h>
#endif

#if AKU_WITH_ANDROID_FIREBASE
	#include <moai-android-firebase/host.h>
#endif

#if AKU_WITH_ANDROID_NOTIFICATIONS
	#include <moai-android/host.h>
#endif

#if AKU_WITH_ANDROID_UNITY_ADS
	#include <moai-android-unity-ads/host.h>
#endif

//----------------------------------------------------------------//
void		AKUModulesAndroidAppFinalize				();
void		AKUModulesAndroidAppInitialize				();
void		AKUModulesAndroidContextInitialize			();
void		AKUModulesAndroidPause						( bool pause );
void		AKUModulesAndroidUpdate						();

#endif
