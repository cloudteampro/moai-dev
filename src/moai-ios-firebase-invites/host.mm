// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-firebase-invites/host.h>
#include <moai-ios-firebase-invites/MOAIFirebaseInvitesIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosFirebaseInvitesAppFinalize () {
}

//----------------------------------------------------------------//
void AKUIosFirebaseInvitesAppInitialize () {
}

//----------------------------------------------------------------//
void AKUIosFirebaseInvitesContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIFirebaseInvitesIOS );
}