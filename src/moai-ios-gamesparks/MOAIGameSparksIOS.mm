//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-gamesparks/MOAIGameSparksIOS.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@lua	init
	@text	Init GameSparks.
	
	@out 	nil
*/
int MOAIGameSparksIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	//
	
	return 0;
}

//================================================================//
// MOAIGameSparksIOS
//================================================================//

//----------------------------------------------------------------//
MOAIGameSparksIOS::MOAIGameSparksIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIGameSparksIOS::~MOAIGameSparksIOS () {
}

//----------------------------------------------------------------//
void MOAIGameSparksIOS::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",					_init },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}