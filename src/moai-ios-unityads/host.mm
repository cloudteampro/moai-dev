// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-unityads/host.h>
#include <moai-ios-unityads/MOAIUnityAdsIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosUnityAdsAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosUnityAdsAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosUnityAdsContextInitialize () {

    REGISTER_LUA_CLASS ( MOAIUnityAdsIOS );
}