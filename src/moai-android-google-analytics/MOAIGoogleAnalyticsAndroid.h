//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIGOOGLEANALYTICSANDROID_H
#define MOAIGOOGLEANALYTICSANDROID_H

#include <moai-core/headers.h>

//================================================================//
// MOAIGoogleAnalyticsAndroid
//================================================================//
/**	@name	MOAIGoogleAnalyticsAndroid
 
 */
class MOAIGoogleAnalyticsAndroid :
public MOAIGlobalClass < MOAIGoogleAnalyticsAndroid, MOAILuaObject > {
private:
	
	//----------------------------------------------------------------//
	static int _logEvent			( lua_State* L );

public:
    
	DECL_LUA_SINGLETON ( MOAIGoogleAnalyticsAndroid );
	
	MOAIGoogleAnalyticsAndroid		();
	~MOAIGoogleAnalyticsAndroid		();
	void	RegisterLuaClass	( MOAILuaState& state );
};

#endif // MOAIGOOGLEANALYTICS_H