//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIYANDEXAPPMETRICAIOS_H
#define	MOAIYANDEXAPPMETRICAIOS_H

#include <moai-core/headers.h>

#import <YandexMobileMetrica/YandexMobileMetrica.h>

//================================================================//
// MOAIYandexAppMetricaIOS
//================================================================//
class MOAIYandexAppMetricaIOS :
	public MOAIGlobalClass < MOAIYandexAppMetricaIOS, MOAIGlobalEventSource > {
private:

	static int		_init							( lua_State* L );
	static int		_trackEvent						( lua_State* L );
	static int		_trackLevelAchieved				( lua_State* L );
	static int		_trackPurchase					( lua_State* L );

public:
		
	DECL_LUA_SINGLETON ( MOAIYandexAppMetricaIOS );

	//----------------------------------------------------------------//
					MOAIYandexAppMetricaIOS			();
					~MOAIYandexAppMetricaIOS		();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIYANDEXAPPMETRICAIOS_H
