// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-fyber/host.h>
#include <moai-ios-fyber/MOAIFyberIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosFyberAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosFyberAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosFyberContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFyberIOS );
}