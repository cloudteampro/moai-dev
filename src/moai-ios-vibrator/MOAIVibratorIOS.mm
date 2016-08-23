// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#import <moai-ios-vibrator/MOAIVibratorIOS.h>
#import <AudioToolbox/AudioToolbox.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	vibrate
	@text	Make the phone vibrate. Does nothing if vibration is unsupported by device.
 
	@out	nil
*/
int MOAIVibratorIOS::_vibrate ( lua_State *L ) {
	UNUSED ( L );
		
	AudioServicesPlaySystemSound ( kSystemSoundID_Vibrate );
	return 0;
}

//================================================================//
// MOAIVibratorIOS
//================================================================//

//----------------------------------------------------------------//
MOAIVibratorIOS::MOAIVibratorIOS () {

	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIVibratorIOS::~MOAIVibratorIOS () {

}

//----------------------------------------------------------------//
void MOAIVibratorIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "vibrate",				_vibrate },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
