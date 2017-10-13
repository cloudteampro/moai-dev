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

//----------------------------------------------------------------//
/** @lua	log
	@text	Write string to Crashlytics log. It will be associated with the crash
	
	@in		string	log
	@out	nil
*/
int MOAICrashlyticsIOS::_log ( lua_State* L ) {
	
	cc8* str = lua_tostring ( L, 1 );
	if ( str ) {
		CLSLog ( @"%s", str );
	}
	return 0;
}

//----------------------------------------------------------------//
/** @lua	reportTraceback
	@text	Report lua traceback to crashlytics site
	
	@in		string	error
	@in		table	stacktrace
	@out	nil
*/
int MOAICrashlyticsIOS::_reportTraceback ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* error = state.GetValue < cc8* >( 1, "" );
	NSMutableArray* stackTrace = [[[ NSMutableArray alloc ] init ] autorelease ];
	
	if ( state.IsType ( 2, LUA_TTABLE )) {
		
		int itr = state.PushTableItr ( 2 );
		while ( state.TableItrNext ( itr )) {
			
			if ( state.IsType ( -1, LUA_TTABLE )) {
				
				cc8* filename = state.GetField < cc8* >( -1, "file", "?" );
				cc8* funcname = state.GetField < cc8* >( -1, "func", "?" );
				int line = state.GetField < int >( -1, "line", 0 );
				
				CLSStackFrame* frame = [ CLSStackFrame stackFrame ];
				
				NSDictionary *bundleInfo = [[ NSBundle mainBundle ] infoDictionary ];

				frame.library = [ bundleInfo objectForKey:@"CFBundleDisplayName" ];
				frame.fileName = [ NSString stringWithUTF8String:filename ];
				frame.symbol = [ NSString stringWithUTF8String:funcname ];
				frame.lineNumber = line;
				
				[ stackTrace addObject:frame ];
			}
		}
	}
	
	[[ Crashlytics sharedInstance ] recordCustomExceptionName:[ NSString stringWithUTF8String:error ] reason:@"Lua" frameArray:stackTrace ];
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setBool
	@text	Set a bool value for a string key. Custom data will be available with crash info on Crashlytics site
	
	@in		string	key
	@in		bool	value
	@out	nil
*/
int MOAICrashlyticsIOS::_setBool ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* > ( 1, 0 );
	bool value = state.GetValue < bool >( 2, false );
	
	if ( key ) {
		[ Crashlytics setBoolValue:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setFloat
	@text	Set a float value for a string key. Custom data will be available with crash info on Crashlytics site
	
	@in		string	key
	@in		number	value
	@out	nil
*/
int MOAICrashlyticsIOS::_setFloat ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* > ( 1, 0 );
	float value = state.GetValue < float >( 2, 0.0 );
	
	if ( key ) {
		[ Crashlytics setFloatValue:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setInt
	@text	Set an int value for a string key. Custom data will be available with crash info on Crashlytics site
	
	@in		string	key
	@in		number	value
	@out	nil
*/
int MOAICrashlyticsIOS::_setInt ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* > ( 1, 0 );
	int value = state.GetValue < int >( 2, false );
	
	if ( key ) {
		[ Crashlytics setIntValue:value forKey:[ NSString stringWithUTF8String:key ]];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setString
	@text	Set an string value for a string key. Custom data will be available with crash info on Crashlytics site
	
	@in		string	key
	@in		string	value
	@out	nil
*/
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
		{ "log",				_log },
		{ "reportTraceback",	_reportTraceback },
		{ "setBool",			_setBool },
		{ "setFloat",			_setFloat },
		{ "setInt",				_setInt },
		{ "setString",			_setString },
		{ "setUser",			_setUser },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
