// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	CTPERRYSQLITE_H
#define	CTPERRYSQLITE_H

#include <moai-core/headers.h>
#include <moai-core/MOAILuaObject.h>
#include <sqlite3.h>

//================================================================//
// CTPerrySQLite
//================================================================//
/**	@name	CTPerrySQLite
	@text	Simple key-value storage in SQLite database. 
*/
class CTPerrySQLite :
	public MOAILuaObject {
private:
	
	sqlite3*			mConnection;

	//----------------------------------------------------------------//
	static int			_close					( lua_State* L );
	static int			_get 					( lua_State* L );
	static int			_getAll					( lua_State* L );
	static int			_open					( lua_State* L );
	static int			_set					( lua_State* L );
	static int			_setBatch				( lua_State* L );

	//----------------------------------------------------------------//
	void				AffirmDatabase			();

public:

	DECL_LUA_FACTORY ( CTPerrySQLite )

	//----------------------------------------------------------------//
	void				Close					();
						CTPerrySQLite			();
						~CTPerrySQLite			();
	int					Open					( cc8* path );
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};



//================================================================//
// CTPerrySQLiteLogger
//================================================================//
/**	@name	CTPerrySQLiteLogger
	@text	Global error logger for all instances of CTPerrySQLite
*/
class CTPerrySQLiteLogger :
	public ZLContextClass < CTPerrySQLiteLogger, MOAILuaObject > {
private:
	
	MOAILuaStrongRef	mErrorHandler;
		
	//----------------------------------------------------------------//
	static int			_setErrorHandler		( lua_State* L );
	
public:
	
	DECL_LUA_SINGLETON ( CTPerrySQLiteLogger )
	GET ( MOAILuaStrongRef&, ErrorHandler, mErrorHandler )
	
	//----------------------------------------------------------------//
	static void			AppInitialize			();
	static void			AppFinalize				();
						CTPerrySQLiteLogger		();
						~CTPerrySQLiteLogger	();
	void				RegisterLuaClass		( MOAILuaState& state );
	void				RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
