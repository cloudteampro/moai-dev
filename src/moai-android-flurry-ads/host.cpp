// Copyright (c) 2015 CloudTeam All Rights Reserved.
// http://cloudteam.pro

#include <moai-android-flurry-ads/host.h>
#include <moai-android-flurry-ads/MOAIFlurryAdsAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidFlurryAdsAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidFlurryAdsAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidFlurryAdsContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFlurryAdsAndroid );
	
}