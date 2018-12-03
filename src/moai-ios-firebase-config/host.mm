// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-firebase-config/host.h>
#include <moai-ios-firebase-config/MOAIFirebaseConfigIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosFirebaseConfigAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosFirebaseConfigAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosFirebaseConfigContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFirebaseConfigIOS );
}

