// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-adtoapp/host.h>
#include <moai-ios-adtoapp/MOAIAdToAppIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosAdToAppAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosAdToAppAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosAdToAppContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIAdToAppIOS );
}