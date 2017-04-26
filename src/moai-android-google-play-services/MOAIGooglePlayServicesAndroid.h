// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGOOGLEPLAYSERVICESANDROID_H
#define	MOAIGOOGLEPLAYSERVICESANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIGooglePlayServicesAndroid
//================================================================//
/**	@lua	MOAIGooglePlayServicesAndroid
	@text	Wrapper for Google Play services.
*/
class MOAIGooglePlayServicesAndroid :
	public MOAIGlobalClass < MOAIGooglePlayServicesAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

	jmethodID			mJava_AuthenticatePlayer;
	jmethodID			mJava_GetPlayerAlias;
	jmethodID			mJava_GetPlayerId;
	jmethodID			mJava_IsSupported;
	jmethodID			mJava_IsAuthenticated;
	jmethodID			mJava_Logout;
	jmethodID			mJava_ReportAchievementProgress;
	jmethodID			mJava_ReportScore;
	jmethodID			mJava_ShowDefaultAchievements;
	jmethodID			mJava_ShowLeaderboard;
	jmethodID			mJava_UnlockAchievement;

	//----------------------------------------------------------------//
	static int	_authenticatePlayer			( lua_State* L );
	static int	_getPlayerAlias				( lua_State* L );
	static int	_getPlayerId				( lua_State* L );
	static int	_isAuthenticated			( lua_State* L );
	static int	_isSupported				( lua_State* L );
	static int	_logout						( lua_State* L );
	static int	_reportAchievementProgress	( lua_State* L );
	static int	_reportScore				( lua_State* L );
	static int	_showLeaderboard			( lua_State* L );
	static int	_showDefaultAchievements	( lua_State* L );
	static int	_unlockAchievement			( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGooglePlayServicesAndroid );

	enum {
		ON_SIGN_IN_SUCCEEDED,
		ON_SIGN_IN_FAILED,
	};

			MOAIGooglePlayServicesAndroid		();
			~MOAIGooglePlayServicesAndroid		();
	void 	NotifyConnectionComplete			();
	void	RegisterLuaClass					( MOAILuaState& state );
};

#endif  //MOAIGOOGLEPLAYSERVICESANDROID_H
