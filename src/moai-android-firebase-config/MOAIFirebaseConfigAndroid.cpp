// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-firebase-config/MOAIFirebaseConfigAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize FirebaseConfig.
	
	@out 	nil
*/
int	MOAIFirebaseConfigAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseConfigAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_Init );
	return 0;
}

//================================================================//
// MOAIFirebaseConfigAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIFirebaseConfigAndroid::MOAIFirebaseConfigAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/firebaseconfig/MoaiFirebaseConfig" );

	this->mJava_Init = this->GetStaticMethod ( "init", "(V)V" );
}

//----------------------------------------------------------------//
MOAIFirebaseConfigAndroid::~MOAIFirebaseConfigAndroid () {
}

//----------------------------------------------------------------//
void MOAIFirebaseConfigAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",						_init },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
