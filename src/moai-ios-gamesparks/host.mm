// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-gamesparks/host.h>
#include <moai-ios-gamesparks/MOAIGameSparksIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosGameSparksAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosGameSparksAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosGameSparksContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIGameSparksIOS );
}