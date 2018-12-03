// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-firebase-invites/MOAIFirebaseInvitesAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize FirebaseInvites.
	
	@in 	string	devKey			FirebaseInvites account Dev Key.
	@out 	nil
*/
int	MOAIFirebaseInvitesAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseInvitesAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_Init );
	return 0;
}

//================================================================//
// MOAIFirebaseInvitesAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIFirebaseInvitesAndroid::MOAIFirebaseInvitesAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/firebaseinvites/MoaiFirebaseInvites" );

	this->mJava_Init = this->GetStaticMethod ( "init", "(v)V" );
}

//----------------------------------------------------------------//
MOAIFirebaseInvitesAndroid::~MOAIFirebaseInvitesAndroid () {
}

//----------------------------------------------------------------//
void MOAIFirebaseInvitesAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",						_init },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
