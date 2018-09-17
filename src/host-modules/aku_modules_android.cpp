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

	#if AKU_WITH_ANDROID_ADCOLONY
		AKUAndroidAdColonyAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_ADMOB
		AKUAndroidAdMobAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_APPSFLYER
		AKUAndroidAppsFlyerAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_CHARTBOOST
		AKUAndroidChartBoostAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_CRITTERCISM
		AKUAndroidCrittercismAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_FACEBOOK
		AKUAndroidFacebookAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_FLURRY
		AKUAndroidFlurryAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_FLURRY_ADS
		AKUAndroidFlurryAdsAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_FYBER
		AKUAndroidFyberAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_GAMESPARKS
		AKUAndroidGameSparksAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_GOOGLE_ANALYTICS
		AKUAndroidGoogleAnalyticsAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_GOOGLE_PLAY_SERVICES
		AKUAndroidGooglePlayServicesAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_GOOGLE_CLOUD_MESSAGING
		AKUAndroidGoogleCloudMessagingAppFinalize ();
	#endif

	#if AKU_WITH_ANDROID_GOOGLE_PLAY_SERVICES_GAMES
		AKUAndroidGooglePlayServicesGamesAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_TAPJOY
		AKUAndroidTapjoyAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_TWITTER
		AKUAndroidTwitterAppFinalize ();
	#endif
	
	#if AKU_WITH_ANDROID_VUNGLE
		AKUAndroidVungleAppFinalize ();
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

	#if AKU_WITH_ANDROID_ADCOLONY
		AKUAndroidAdColonyAppInitialize ();
	#endif
		
	#if AKU_WITH_ANDROID_ADMOB
		AKUAndroidAdMobAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_APPSFLYER
		AKUAndroidAppsFlyerAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_CHARTBOOST
		AKUAndroidChartBoostAppInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_CRITTERCISM
		AKUAndroidCrittercismAppInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_FACEBOOK
		AKUAndroidFacebookAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FLURRY
		AKUAndroidFlurryAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FLURRY_ADS
		AKUAndroidFlurryAdsAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FYBER
		AKUAndroidFyberAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_GAMESPARKS
		AKUAndroidGameSparksAppInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_GOOGLE_ANALYTICS
		AKUAndroidGoogleAnalyticsAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_GOOGLE_CLOUD_MESSAGING
		AKUAndroidGoogleCloudMessagingAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_GOOGLE_PLAY_SERVICES
		AKUAndroidGooglePlayServicesAppInitialize ();
	#endif

	#if AKU_WITH_ANDROID_GOOGLE_PLAY_SERVICES_GAMES
		AKUAndroidGooglePlayServicesGamesAppInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_TAPJOY
		AKUAndroidTapjoyAppInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_TWITTER
		AKUAndroidTwitterAppInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_VUNGLE
		AKUAndroidVungleAppInitialize ();
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

	#if AKU_WITH_ANDROID_ADCOLONY
		AKUAndroidAdColonyContextInitialize ();
	#endif
		
	#if AKU_WITH_ANDROID_ADMOB
		AKUAndroidAdMobContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_APPSFLYER
		AKUAndroidAppsFlyerContextInitialize();
	#endif

	#if AKU_WITH_ANDROID_CHARTBOOST
		AKUAndroidChartBoostContextInitialize ();
	#endif
    
    #if AKU_WITH_ANDROID_CRITTERCISM
		AKUAndroidCrittercismContextInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_FACEBOOK
		AKUAndroidFacebookContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FLURRY
		AKUAndroidFlurryContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FLURRY_ADS
		AKUAndroidFlurryAdsContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_FYBER
		AKUAndroidFyberContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_GAMESPARKS
		AKUAndroidGameSparksContextInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_GOOGLE_ANALYTICS
		AKUAndroidGoogleAnalyticsContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_GOOGLE_PLAY_SERVICES
		AKUAndroidGooglePlayServicesContextInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_GOOGLE_CLOUD_MESSAGING
		AKUAndroidGoogleCloudMessagingContextInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_GOOGLE_PLAY_SERVICES_GAMES
		AKUAndroidGooglePlayServicesGamesContextInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_TAPJOY
		AKUAndroidTapjoyContextInitialize ();
	#endif
	
	#if AKU_WITH_ANDROID_TWITTER
		AKUAndroidTwitterContextInitialize ();
	#endif

	#if AKU_WITH_ANDROID_VUNGLE
        AKUAndroidVungleContextInitialize ();
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
