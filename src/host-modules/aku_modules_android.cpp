// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <zl-common/zl_platform.h>
#include <host-modules/aku_modules_android.h>

//================================================================//
// implementation
//================================================================//

//----------------------------------------------------------------//
void AKUModulesAndroidAppFinalize () {

	#if AKU_WITH_ANDROID
		AKUAndroidAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_ADMOB
		AKUAndroidAdMobAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_APPSFLYER
		AKUAndroidAppsFlyerAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_FACEBOOK
		AKUAndroidFacebookAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_FIREBASE
		AKUAndroidFirebaseAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_UNITY_ADS
		AKUAndroidUnityAdsAppFinalize ();
	#endif
}

//----------------------------------------------------------------//
void AKUModulesAndroidAppInitialize () {

	#if AKU_WITH_ANDROID
		AKUAndroidAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_ADMOB
		AKUAndroidAdMobAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_APPSFLYER
		AKUAndroidAppsFlyerAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FACEBOOK
		AKUAndroidFacebookAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FIREBASE
		AKUAndroidFirebaseAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_UNITY_ADS
		AKUAndroidUnityAdsAppInitialize ();
	#endif
}

//----------------------------------------------------------------//
void AKUModulesAndroidContextInitialize () {

	#if AKU_WITH_ANDROID
		AKUAndroidContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_ADMOB
		AKUAndroidAdMobContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_APPSFLYER
		AKUAndroidAppsFlyerContextInitialize();
	#endif
	
	#if AKU_WITH_ANDROID_FACEBOOK
		AKUAndroidFacebookContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FIREBASE
		AKUAndroidFirebaseContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_UNITY_ADS
        AKUAndroidUnityAdsContextInitialize ();
    #endif
}

//----------------------------------------------------------------//
void AKUModulesAndroidPause ( bool pause ) {
	UNUSED ( pause );
}


//----------------------------------------------------------------//
void AKUModulesAndroidUpdate () {
}
