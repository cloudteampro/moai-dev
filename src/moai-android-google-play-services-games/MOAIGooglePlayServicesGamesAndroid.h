// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGOOGLEPLAYSERVICESGAMESANDROID_H
#define	MOAIGOOGLEPLAYSERVICESGAMESANDROID_H

#ifndef DISABLE_PLAYSERVICESGAMES

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIGooglePlayServicesGamesAndroid
//================================================================//
/**	@name	MOAIGooglePlayServicesGamesAndroid
	@text	Wrapper for Google Play services.
*/
class MOAIGooglePlayServicesGamesAndroid :
	public MOAIGlobalClass < MOAIGooglePlayServicesGamesAndroid, MOAILuaObject >,
	public JniUtils {
private:

	//----------------------------------------------------------------//
	static int	_authenticatePlayer			( lua_State* L );
	static int	_getPlayerAlias				( lua_State* L );
	static int	_getPlayerId				( lua_State* L );
	static int	_getAchievements			( lua_State* L );
	static int	_getScores					( lua_State* L );
	static int	_isSupported				( lua_State* L );
	static int	_logout						( lua_State* L );
	static int	_reportAchievementProgress	( lua_State* L );
	static int	_reportScore				( lua_State* L );
	static int	_setGetScoresCallback		( lua_State* L );
	static int	_showLeaderboard			( lua_State* L );
	static int	_showDefaultAchievements	( lua_State* L );
	// static int	_showGameCenter				( lua_State* L );
	static int	_unlockAchievement			( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGooglePlayServicesGamesAndroid );

	enum {
		VIEW_DEFAULT,
		VIEW_LEADERBOARDS,
		VIEW_ACHIEVEMENTS,
		VIEW_CHALLENGES,
		TOTAL,
	};

	MOAILuaStrongRef		mListeners [ TOTAL ];

			MOAIGooglePlayServicesGamesAndroid		();
			~MOAIGooglePlayServicesGamesAndroid		();
	void	RegisterLuaClass					( MOAILuaState& state );
};

#endif  //DISABLE_PLAYSERVICESGAMES

#endif  //MOAIGOOGLEPLAYSERVICESANDROID_H
