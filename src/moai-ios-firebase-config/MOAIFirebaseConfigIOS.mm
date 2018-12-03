//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-firebase-config/MOAIFirebaseConfigIOS.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize FirebaseConfig.
	
	@out 	nil
*/
int MOAIFirebaseConfigIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	
	return 0;
}

//================================================================//
// MOAIFirebaseConfigIOS
//================================================================//

//----------------------------------------------------------------//
MOAIFirebaseConfigIOS::MOAIFirebaseConfigIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIFirebaseConfigIOS::~MOAIFirebaseConfigIOS () {
}

//----------------------------------------------------------------//
void MOAIFirebaseConfigIOS::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",					_init },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

