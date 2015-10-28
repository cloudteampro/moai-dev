// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#import <UIKit/UIKit.h>

#import <moai-ios-crashlytics/MOAICrashlyticsIOS.h>

#import <Fabric/Fabric.h>
#import <Crashlytics/Crashlytics.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Crashlytics. AppID and other settings are in host info.plist
	
	@out	nil
*/
int MOAICrashlyticsIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

//	cc8* appId = state.GetValue < cc8* >( state, "" );
//
//	NSString* appID = [ NSString stringWithUTF8String:appId ];
	
	[ Fabric with:@[ CrashlyticsKit ]];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	forceException
	@text	Forces a crash and crashlytics report, can be used for internal errors or debugging crashlytics
 	
 	@in 	
	@out	nil 
 */
int	MOAICrashlyticsIOS::_forceException ( lua_State* L ) {
	MOAILuaState state ( L );
	
	[ NSException raise:NSInvalidArgumentException format:@"Moai Force Exception" ];
	return 0;
}

int MOAICrashlyticsIOS::_setBool ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* > ( 1, 0 );
	bool value = state.GetValue < bool >( 2, false );
	
	if ( key ) {
		[ Crashlytics setBoolValue:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

int MOAICrashlyticsIOS::_setFloat ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* > ( 1, 0 );
	float value = state.GetValue < float >( 2, 0.0 );
	
	if ( key ) {
		[ Crashlytics setFloatValue:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

int MOAICrashlyticsIOS::_setInt ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* > ( 1, 0 );
	int value = state.GetValue < int >( 2, false );
	
	if ( key ) {
		[ Crashlytics setIntValue:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

int MOAICrashlyticsIOS::_setString ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* > ( 1, 0 );
	cc8* value = state.GetValue < cc8* >( 2, 0 );
	
	if ( key && value ) {
		[ Crashlytics setObjectValue:[ NSString stringWithUTF8String:value ] forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setUser
	@text	Sets the user info
	
	@in		string user ID
	@opt	string user name
	@opt	string user email
	
	@out	nil
*/
int MOAICrashlyticsIOS::_setUser ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* userId = state.GetValue < cc8* >( 1, 0 );
	cc8* userName = state.GetValue < cc8* >( 2, 0 );
	cc8* userEmail = state.GetValue < cc8* >( 3, 0 );
	
	if ( userId ) {
		[ Crashlytics setUserIdentifier:[ NSString stringWithUTF8String:userId ]];
	}
	
	if ( userName ) {
		[ Crashlytics setUserName:[ NSString stringWithUTF8String:userName ]];
	}
	
	if ( userEmail ) {
		[ Crashlytics setUserEmail:[ NSString stringWithUTF8String:userEmail ]];
	}
	
	return 0;
}


//================================================================//
// MOAICrashlyticsIOS
//================================================================//

//----------------------------------------------------------------//
MOAICrashlyticsIOS::MOAICrashlyticsIOS () {

	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAICrashlyticsIOS::~MOAICrashlyticsIOS () {
}

//----------------------------------------------------------------//
void MOAICrashlyticsIOS::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable[] = {
		{ "init",				_init },
		{ "forceException",		_forceException },
		{ "setBool",			_setBool },
		{ "setFloat",			_setFloat },
		{ "setInt",				_setInt },
		{ "setString",			_setString },
		{ "setUser",			_setUser },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
