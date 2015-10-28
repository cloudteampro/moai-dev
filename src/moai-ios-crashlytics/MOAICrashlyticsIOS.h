// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAICRASHLYTICSIOS_H
#define	MOAICRASHLYTICSIOS_H

#import <Foundation/Foundation.h> 
#import <moai-core/headers.h>

//================================================================//
// MOAICrashlyticsIOS
//================================================================//
/**	@lua	MOAICrashlyticsIOS
	@text	Wrapper for Crashlytics integration on iOS devices.
*/
class MOAICrashlyticsIOS :
	public MOAIGlobalClass < MOAICrashlyticsIOS, MOAILuaObject > {
private:

	//----------------------------------------------------------------//
	static int	_init 				( lua_State* L );
	static int	_forceException		( lua_State* L );
	static int  _setBool			( lua_State* L );
	static int  _setFloat			( lua_State* L );
	static int  _setInt				( lua_State* L );
	static int  _setString			( lua_State* L );
	static int	_setUser			( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAICrashlyticsIOS );
	
	//----------------------------------------------------------------//
			MOAICrashlyticsIOS		();
			~MOAICrashlyticsIOS		();
	void	RegisterLuaClass		( MOAILuaState& state );
};

#endif  //MOAICRASHLYTICSIOS_H
