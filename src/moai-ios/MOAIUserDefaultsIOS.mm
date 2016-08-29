//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios/MOAIUserDefaultsIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/** TODO
	@in 	string	key
	@opt	string	suiteName 	app group suite name
	
	@out	value
*/
int MOAIUserDefaultsIOS::_getBoolean ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIUserDefaultsIOS, "" )

	cc8* key 	= state.GetValue < cc8* >( 1, 0 );
	cc8* suite 	= state.GetValue < cc8* >( 2, 0 );

	NSUserDefaults* defaults = self->GetUserDefaults ( suite );
	if ( defaults && key ) {
		bool value = [ defaults boolForKey:[ NSString stringWithUTF8String:key ]];
		state.Push ( value );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**
*/
int MOAIUserDefaultsIOS::_getNumber ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIUserDefaultsIOS, "" )

	cc8* key 	= state.GetValue < cc8* >( 1, 0 );
	cc8* suite 	= state.GetValue < cc8* >( 2, 0 );

	NSUserDefaults* defaults = self->GetUserDefaults ( suite );
	if ( defaults && key ) {
		double value = [ defaults doubleForKey:[ NSString stringWithUTF8String:key ]];
		state.Push ( value );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
/**
*/
int MOAIUserDefaultsIOS::_getString ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIUserDefaultsIOS, "" )

	cc8* key 	= state.GetValue < cc8* >( 1, 0 );
	cc8* suite 	= state.GetValue < cc8* >( 2, 0 );

	NSUserDefaults* defaults = self->GetUserDefaults ( suite );
	if ( defaults && key ) {
		NSString* value = [ defaults stringForKey:[ NSString stringWithUTF8String:key ]];
		state.Push (( cc8* )[ value UTF8String ]);
		return 1;
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**
*/
int MOAIUserDefaultsIOS::_setBoolean ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIUserDefaultsIOS, "" )

	cc8* key 	= state.GetValue < cc8* >( 1, 0 );
	bool value 	= state.GetValue < bool >( 2, 0 );
	cc8* suite 	= state.GetValue < cc8* >( 3, 0 );

	NSUserDefaults* defaults = self->GetUserDefaults ( suite );
	if ( defaults && key ) {
		[ defaults setBool:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**
*/
int MOAIUserDefaultsIOS::_setNumber ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIUserDefaultsIOS, "" )

	cc8* key 		= state.GetValue < cc8* >( 1, 0 );
	double value 	= state.GetValue < double >( 2, 0.0 );
	cc8* suite 		= state.GetValue < cc8* >( 3, 0 );

	NSUserDefaults* defaults = self->GetUserDefaults ( suite );
	if ( defaults && key ) {
		[ defaults setDouble:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**
*/
int MOAIUserDefaultsIOS::_setString ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIUserDefaultsIOS, "" )

	cc8* key 	= state.GetValue < cc8* >( 1, 0 );
	cc8* value 	= state.GetValue < cc8* >( 2, 0 );
	cc8* suite 	= state.GetValue < cc8* >( 3, 0 );

	NSUserDefaults* defaults = self->GetUserDefaults ( suite );
	if ( defaults && key ) {
		NSString* obj = value ? [ NSString stringWithUTF8String:value ] : nil;
		[ defaults setObject:obj forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**
*/
int MOAIUserDefaultsIOS::_synchronize ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIUserDefaultsIOS, "" )

	cc8* suite 	= state.GetValue < cc8* >( 1, 0 );
	NSUserDefaults* defaults = self->GetUserDefaults ( suite );
	state.Push (( bool )[ defaults synchronize ]);
	return 1;
}


//================================================================//
// MOAIUserDefaultsIOS
//================================================================//

//----------------------------------------------------------------//
NSUserDefaults* MOAIUserDefaultsIOS::GetUserDefaults ( cc8* suite ) {
	if ( suite ) {
		NSString* name = [ NSString stringWithUTF8String: suite ];
		return [[[ NSUserDefaults alloc ] initWithSuiteName:name ] autorelease ];
	}
	else {
		return [ NSUserDefaults standardUserDefaults ];
	}
}

//----------------------------------------------------------------//
MOAIUserDefaultsIOS::MOAIUserDefaultsIOS () {
	
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIUserDefaultsIOS::~MOAIUserDefaultsIOS () {

}

//----------------------------------------------------------------//
void MOAIUserDefaultsIOS::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "getBoolean", 				_getBoolean },
		{ "getNumber", 					_getNumber },
		{ "getString", 					_getString },
		{ "setBoolean", 				_setBoolean },
		{ "setNumber", 					_setNumber },
		{ "setString", 					_setString },
		{ "synchronize", 				_synchronize },
		{ NULL, NULL }
	};
	
	luaL_register( state, 0, regTable );
}

