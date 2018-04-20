// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-gamesparks/MOAIGameSparksAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize GameSparks.
	
	@in 	string	apiKey
	@in 	string	apiSecret
	@in 	string	credential
	@out 	nil
*/
int	MOAIGameSparksAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString japiKey	= self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	MOAIJString japiSecret	= self->GetJString ( state.GetValue < cc8* >( 2, 0 ));
	MOAIJString jcredential	= self->GetJString ( state.GetValue < cc8* >( 3, 0 ));

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )japiKey, ( jstring )japiSecret, ( jstring )jcredential );
	return 0;
}


//================================================================//
// MOAIGameSparksAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIGameSparksAndroid::MOAIGameSparksAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/gamesparks/MoaiGameSparks" );

	this->mJava_Init					= this->GetStaticMethod ( "init", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIGameSparksAndroid::~MOAIGameSparksAndroid () {
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",						_init },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
