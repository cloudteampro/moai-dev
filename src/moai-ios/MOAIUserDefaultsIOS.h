//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIUSERDEFAULTSIOS_H
#define MOAIUSERDEFAULTSIOS_H

#import <Foundation/Foundation.h>
#import <moai-core/headers.h>

//================================================================//
// MOAIUserDefaultsIOS
//================================================================//
class MOAIUserDefaultsIOS :
	public MOAIGlobalClass < MOAIUserDefaultsIOS, MOAILuaObject > {
private:
	
	//----------------------------------------------------------------//
	static int	_getBoolean					( lua_State* L );
	static int	_getNumber					( lua_State* L );
	static int	_getString					( lua_State* L );
	static int	_setBoolean					( lua_State* L );
	static int	_setNumber					( lua_State* L );
	static int	_setString					( lua_State* L );
	static int	_synchronize				( lua_State* L );

	//----------------------------------------------------------------//
	NSUserDefaults* 	GetUserDefaults		( cc8* suiteName );

public:

	DECL_LUA_SINGLETON ( MOAIUserDefaultsIOS );
	
			MOAIUserDefaultsIOS					();
			~MOAIUserDefaultsIOS				();

	void	RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIUSERDEFAULTSIOS_H
