// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <ct-util/CTPerrySQLite.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int	CTPerrySQLite::_close ( lua_State* L ) {
	MOAI_LUA_SETUP ( CTPerrySQLite, "U" )
	
	self->Close ();
	return 0;
}

//----------------------------------------------------------------//
int	CTPerrySQLite::_get ( lua_State* L ) {
	MOAI_LUA_SETUP ( CTPerrySQLite, "US" )

	cc8* key = state.GetValue < cc8* >( 2, 0 );
	
	cc8* sql = "SELECT data FROM perry WHERE name = ?;";
	int result;
	sqlite3_stmt* stmt = 0;
	result = sqlite3_prepare_v2 ( self->mConnection, sql, -1, &stmt, NULL );
	
	if ( result != SQLITE_OK ) {
		state.Push ();
	}
	else {
		result = sqlite3_bind_text ( stmt, 1, key, -1, SQLITE_TRANSIENT );
		
		if ( result == SQLITE_OK && sqlite3_step ( stmt ) == SQLITE_ROW ) {
			size_t size = sqlite3_column_bytes ( stmt, 0 );
			const void* data = sqlite3_column_blob ( stmt, 0 );
			state.Push ( const_cast < void* >( data ), size );
		}
		else {
			state.Push ();
		}
	}
	
	sqlite3_finalize ( stmt );
	return 1;
}

//----------------------------------------------------------------//
int	CTPerrySQLite::_getAll ( lua_State* L ) {
	MOAI_LUA_SETUP ( CTPerrySQLite, "U" )
	
	lua_newtable ( L );
	
	cc8* sql = "SELECT name, data FROM perry;";
	
	int result;
	sqlite3_stmt* stmt = 0;
	result = sqlite3_prepare_v2 ( self->mConnection, sql, -1, &stmt, NULL );
	
	if ( result == SQLITE_OK ) {
		result = sqlite3_step ( stmt );
		while ( result == SQLITE_ROW ) {
			
			cc8* key = ( cc8* ) sqlite3_column_text ( stmt, 0 );
			
			size_t size = sqlite3_column_bytes ( stmt, 1 );
			const void* data = sqlite3_column_blob ( stmt, 1 );
			
			state.Push ( key );
			state.Push ( const_cast < void* >( data ), size );
			lua_settable ( state, -3 );
			
			result = sqlite3_step ( stmt );
		}
	}
	
	sqlite3_finalize ( stmt );
	return 1;
}

//----------------------------------------------------------------//
/** @lua	open
	@text	Open database connection
 
	@in		CTPerrySQLite	self
	@in		string			database file path
	@opt	function		error handler
	@out	boolean			success
**/
int	CTPerrySQLite::_open ( lua_State* L ) {
	MOAI_LUA_SETUP ( CTPerrySQLite, "US" )
	
	cc8* path = state.GetValue < cc8* >( 2, 0 );
	
	state.Push ( self->Open ( path ));
	return 1;
}

//----------------------------------------------------------------//
int	CTPerrySQLite::_set ( lua_State* L ) {
	MOAI_LUA_SETUP ( CTPerrySQLite, "US" )
	
	cc8* key = state.GetValue < cc8* >( 2, 0 );
	
	bool success = false;
	if ( state.IsType ( 3, LUA_TSTRING )) {
		
		size_t size;
		cc8* data = lua_tolstring ( state, 3, &size );
		
		int result;
		cc8* sql = "INSERT OR REPLACE INTO perry (name, data) VALUES (?, ?);";
		
		sqlite3_stmt* stmt = 0;
		result = sqlite3_prepare_v2 ( self->mConnection, sql, -1, &stmt, NULL );
		if ( result == SQLITE_OK ) {
			sqlite3_bind_text ( stmt, 1, key, -1, SQLITE_TRANSIENT );
			sqlite3_bind_blob ( stmt, 2, data, size, SQLITE_TRANSIENT );
			success = SQLITE_DONE == sqlite3_step ( stmt );
		}
		sqlite3_finalize ( stmt );
	}
	else {
		// delete row
		int result = 0;
		cc8* sql = "DELETE FROM perry WHERE name = ?;";
		sqlite3_stmt* stmt = 0;
		result = sqlite3_prepare_v2 ( self->mConnection, sql, -1, &stmt, NULL );
		if ( result == SQLITE_OK ) {
			sqlite3_bind_text ( stmt, 1, key, -1, SQLITE_TRANSIENT );
			success = SQLITE_DONE == sqlite3_step ( stmt );
		}
		sqlite3_finalize ( stmt );
	}
	
	state.Push ( success );
	return 1;
}

//----------------------------------------------------------------//
int	CTPerrySQLite::_setBatch ( lua_State* L ) {
	MOAI_LUA_SETUP ( CTPerrySQLite, "UT" )
	
	u32 itr = state.PushTableItr ( 2 );
	
	// Advance to the next key, early exit on empty table;
	bool hasRows = state.TableItrNext ( itr );
	if ( !hasRows ) return 0;
	
	STLString query ( "INSERT OR REPLACE INTO perry (name, data) VALUES (?,?)" );
	while ( state.TableItrNext ( itr )) {
		query.append ( ",(?,?)" );
	}
	query.append ( ";" );
	
	sqlite3_stmt* stmt = 0;
	int result = sqlite3_prepare_v2 ( self->mConnection, query, -1, &stmt, NULL );
	
	if ( !stmt ) return 0;
	
	itr = state.PushTableItr ( 2 );
	u32 index = 1;
	while ( state.TableItrNext ( itr )) {
		
		if ( lua_type ( state, -2 ) != LUA_TSTRING || lua_type ( state, -1 ) != LUA_TSTRING ) {
			continue;
		}
		
		STLString key = lua_tostring ( state, -2 );
		
		size_t size;
		cc8* data = lua_tolstring ( state, -1, &size );
		
		sqlite3_bind_text ( stmt, index++, key, -1, SQLITE_TRANSIENT );
		sqlite3_bind_blob ( stmt, index++, data, size, SQLITE_TRANSIENT );
	}
	
	bool success = SQLITE_DONE == sqlite3_step ( stmt );
	sqlite3_finalize ( stmt );
	sqlite3_wal_checkpoint ( self->mConnection, NULL );
	
	state.Push ( success );
	return 1;
}


//================================================================//
// CTPerrySQLite
//================================================================//

//----------------------------------------------------------------//
static int AffirmCallback ( void* unused, int columnCount, char **text, char **name ) {
	return 0;
}

//----------------------------------------------------------------//
void CTPerrySQLite::AffirmDatabase () {
	if ( this->mConnection == 0 ) return;
	
	char* err = 0;
	
	cc8* sql = "PRAGMA journal_mode=WAL; CREATE TABLE IF NOT EXISTS perry (name TEXT PRIMARY KEY, data BLOB);";
	int result = sqlite3_exec ( this->mConnection, sql, AffirmCallback, NULL, &err );
	if ( result != SQLITE_OK ) {
		// log error
		sqlite3_free ( err );
	}
}

//----------------------------------------------------------------//
void CTPerrySQLite::Close () {
	
	if ( this->mConnection ) {
		if ( sqlite3_close_v2 ( this->mConnection ) == SQLITE_OK ) {
			this->mConnection = 0;
		}
	}
}

//----------------------------------------------------------------//
CTPerrySQLite::CTPerrySQLite ():
	mConnection ( 0 ) {
    
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
CTPerrySQLite::~CTPerrySQLite () {
	this->Close ();
}

//----------------------------------------------------------------//
int CTPerrySQLite::Open ( cc8* path ) {
	
	if ( this->mConnection ) {
		this->Close ();
	}
	
	int result = sqlite3_open_v2 ( path, &this->mConnection, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL );
	if ( result == SQLITE_OK ) {
		this->AffirmDatabase ();
	}
	return result;
}

//----------------------------------------------------------------//
void CTPerrySQLite::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void CTPerrySQLite::RegisterLuaFuncs ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "close",						_close },
		{ "get",						_get },
		{ "getAll",						_getAll },
		{ "open",						_open },
		{ "set",						_set },
		{ "setBatch",					_setBatch },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}



//================================================================//
// CTPerrySQLiteLogger
//================================================================//

//----------------------------------------------------------------//
/** @lua	setErrorHandler
	@text	Set global error logger for all database connections
 
	@in		function	logger ( number errorId, string message )
	@out	nil
**/
int	CTPerrySQLiteLogger::_setErrorHandler ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( CTPerrySQLiteLogger, "" )
	
	self->GetErrorHandler ().SetRef ( state, 1 );
	return 0;
}

//----------------------------------------------------------------//
static void ReportError ( void* unused, int error, cc8* message ) {
	
	if ( error == SQLITE_OK ) return;
	
	// Early exit on malloc error. Pushing error message to Lua most likely will attempt to allocate more memory
	if ( error == SQLITE_NOMEM ) return;
	
	// Some hosts may call AppInitialize multiple times during lifetime (actually, that's improper behavior, but it works fine).
	// This can lead to sqlite3_config call on intialized sqlite3 library that will log SQLITE_MISUSE error.
	//
	// Don't even try to make a Lua callback if there is 0 contexts
	if ( AKUCountContexts () > 0 && CTPerrySQLiteLogger::IsValid () && MOAILuaRuntime::IsValid ()) {
		
		MOAILuaStrongRef& errorHandler = CTPerrySQLiteLogger::Get ().GetErrorHandler ();
		if ( errorHandler ) {
			
			MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
			if ( errorHandler.PushRef ( state )) {
				
				state.Push ( error );
				state.Push ( message );
				state.DebugCall ( 2, 0 );
			}
		}
	}
}

//----------------------------------------------------------------//
void CTPerrySQLiteLogger::AppInitialize () {
	sqlite3_config ( SQLITE_CONFIG_LOG, ReportError, NULL );
	sqlite3_initialize ();
}

//----------------------------------------------------------------//
void CTPerrySQLiteLogger::AppFinalize () {
	sqlite3_shutdown ();
}

//----------------------------------------------------------------//
CTPerrySQLiteLogger::CTPerrySQLiteLogger () {
	
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
CTPerrySQLiteLogger::~CTPerrySQLiteLogger () {

}

//----------------------------------------------------------------//
void CTPerrySQLiteLogger::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAILuaObject::RegisterLuaClass ( state );
	
	state.SetField ( -1, "SQLITE_ERROR",		( u32 ) SQLITE_ERROR );
	state.SetField ( -1, "SQLITE_INTERNAL",		( u32 ) SQLITE_INTERNAL );
	state.SetField ( -1, "SQLITE_PERM",			( u32 ) SQLITE_PERM );
	state.SetField ( -1, "SQLITE_BUSY",			( u32 ) SQLITE_BUSY );
	state.SetField ( -1, "SQLITE_LOCKED",		( u32 ) SQLITE_LOCKED );
	state.SetField ( -1, "SQLITE_NOMEM",		( u32 ) SQLITE_NOMEM );
	state.SetField ( -1, "SQLITE_READONLY",		( u32 ) SQLITE_READONLY );
	state.SetField ( -1, "SQLITE_INTERRUPT",	( u32 ) SQLITE_INTERRUPT );
	state.SetField ( -1, "SQLITE_IOERR",		( u32 ) SQLITE_IOERR );
	state.SetField ( -1, "SQLITE_CORRUPT",		( u32 ) SQLITE_CORRUPT );
	state.SetField ( -1, "SQLITE_NOTFOUND",		( u32 ) SQLITE_NOTFOUND );
	state.SetField ( -1, "SQLITE_FULL",			( u32 ) SQLITE_FULL );
	state.SetField ( -1, "SQLITE_CANTOPEN",		( u32 ) SQLITE_CANTOPEN );
	state.SetField ( -1, "SQLITE_PROTOCOL",		( u32 ) SQLITE_PROTOCOL );
	state.SetField ( -1, "SQLITE_EMPTY",		( u32 ) SQLITE_EMPTY );
	state.SetField ( -1, "SQLITE_SCHEMA",		( u32 ) SQLITE_SCHEMA );
	state.SetField ( -1, "SQLITE_TOOBIG",		( u32 ) SQLITE_TOOBIG );
	state.SetField ( -1, "SQLITE_CONSTRAINT",	( u32 ) SQLITE_CONSTRAINT );
	state.SetField ( -1, "SQLITE_MISMATCH",		( u32 ) SQLITE_MISMATCH );
	state.SetField ( -1, "SQLITE_MISUSE",		( u32 ) SQLITE_MISUSE );
	state.SetField ( -1, "SQLITE_NOLFS",		( u32 ) SQLITE_NOLFS );
	state.SetField ( -1, "SQLITE_AUTH",			( u32 ) SQLITE_AUTH );
	state.SetField ( -1, "SQLITE_FORMAT",		( u32 ) SQLITE_FORMAT );
	state.SetField ( -1, "SQLITE_RANGE",		( u32 ) SQLITE_RANGE );
	state.SetField ( -1, "SQLITE_NOTADB",		( u32 ) SQLITE_NOTADB );
	
	luaL_Reg regTable [] = {
		{ "setErrorHandler",			_setErrorHandler },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void CTPerrySQLiteLogger::RegisterLuaFuncs ( MOAILuaState& state ) {
	UNUSED ( state );
}

