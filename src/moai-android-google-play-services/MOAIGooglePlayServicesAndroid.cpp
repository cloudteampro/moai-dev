// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/JniUtils.h>
#include <moai-android-google-play-services/MOAIGooglePlayServicesAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	authenticatePlayer
	@text	Connects to the Google Play Game Services

	@out	nil
*/
int MOAIGooglePlayServicesAndroid::_authenticatePlayer ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_AuthenticatePlayer );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getPlayerAlias

	@out	string 		name
*/
int MOAIGooglePlayServicesAndroid::_getPlayerAlias ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	jstring jplayerAlias = ( jstring )self->CallStaticObjectMethod ( self->mJava_GetPlayerAlias );

	cc8* playerAlias = self->GetCString (( jstring )jplayerAlias );
	state.Push ( playerAlias );
	self->ReleaseCString (( jstring )jplayerAlias, playerAlias );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	getPlayerId

	@out	string 		id
*/
int MOAIGooglePlayServicesAndroid::_getPlayerId ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	jstring jplayerId = ( jstring )self->CallStaticObjectMethod ( self->mJava_GetPlayerId );

	cc8* playerId = self->GetCString (( jstring )jplayerId );
	state.Push ( playerId );
	self->ReleaseCString (( jstring )jplayerId, playerId );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	isSupported
	@text	Check connects to the Google Play Game Services

	@out	nil
*/
int MOAIGooglePlayServicesAndroid::_isSupported ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	bool supported = self->CallStaticBooleanMethod ( self->mJava_IsSupported );
	state.Push ( supported );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	_logout
	@text	Logout

	@out	nil
 */
int MOAIGooglePlayServicesAndroid::_logout ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_Logout );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	showDefaultAchievements
	@text	Shows the achievements

	@out	nil
*/
int MOAIGooglePlayServicesAndroid::_showDefaultAchievements ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_ShowDefaultAchievements );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	showLeaderboard
	@text	Shows the desired leaderboard

	@in		string leaderboardID
	@out	nil
*/
int MOAIGooglePlayServicesAndroid::_showLeaderboard ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	MOAIJString jboard = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	self->CallStaticVoidMethod ( self->mJava_ShowLeaderboard, ( jstring )jboard );
	return 0;
}


//----------------------------------------------------------------//
/**	@name	reportScore
	@text	Submits a score for the passed in leaderboard

	@in		string leaderboardID
	@in		number score
	@out	nil
*/
int MOAIGooglePlayServicesAndroid::_reportScore ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	MOAIJString jboard = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	jint score = state.GetValue < int >( 2, 0 );

	self->CallStaticVoidMethod ( self->mJava_ReportScore, ( jstring )jboard, score );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	reportAchievementProgress
	@text	Grants an achievement to the player

	@in		string achievementID
	@out	nil
*/
int MOAIGooglePlayServicesAndroid::_reportAchievementProgress ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	MOAIJString jboard = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	jint progress = state.GetValue < int >( 2, 0 );

	self->CallStaticVoidMethod ( self->mJava_ReportAchievementProgress, ( jstring )jboard, progress );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	unlockAchievement
	@text	Grants an achievement to the player

	@in		string achievementID
	@out	nil
*/
int MOAIGooglePlayServicesAndroid::_unlockAchievement ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGooglePlayServicesAndroid, "" )

	MOAIJString jach = self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	self->CallStaticVoidMethod ( self->mJava_UnlockAchievement, ( jstring )jach );
	return 0;
}

//================================================================//
// MOAIGooglePlayServicesAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIGooglePlayServicesAndroid::MOAIGooglePlayServicesAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )

	this->SetClass ( "com/moaisdk/googleplayservices/MoaiGooglePlayServices" );

	this->mJava_AuthenticatePlayer			= this->GetStaticMethod ( "authenticatePlayer", "()V" );
	this->mJava_GetPlayerAlias				= this->GetStaticMethod ( "getPlayerAlias", "()Ljava/lang/String;" );
	this->mJava_GetPlayerId					= this->GetStaticMethod ( "getPlayerId", "()Ljava/lang/String;" );
	this->mJava_IsSupported					= this->GetStaticMethod ( "isSupported", "()Z" );
	this->mJava_IsAuthenticated				= this->GetStaticMethod ( "isAuthenticated", "()Z" );
	this->mJava_Logout						= this->GetStaticMethod ( "logout", "()V" );
	this->mJava_ReportAchievementProgress	= this->GetStaticMethod ( "reportAchievementProgress", "(Ljava/lang/String;I)V" );
	this->mJava_ReportScore					= this->GetStaticMethod ( "reportScore", "(Ljava/lang/String;I)V" );
	this->mJava_ShowDefaultAchievements		= this->GetStaticMethod ( "showDefaultAchievements", "()V" );
	this->mJava_ShowLeaderboard				= this->GetStaticMethod ( "showLeaderboard", "(Ljava/lang/String;)V" );
	this->mJava_UnlockAchievement			= this->GetStaticMethod ( "unlockAchievement", "(Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIGooglePlayServicesAndroid::~MOAIGooglePlayServicesAndroid () {

}

//----------------------------------------------------------------//
void MOAIGooglePlayServicesAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	// state.SetField ( -1, "VIEW_DEFAULT",			( u32 )VIEW_DEFAULT );
	// state.SetField ( -1, "VIEW_LEADERBOARDS",		( u32 )VIEW_LEADERBOARDS );
	// state.SetField ( -1, "VIEW_ACHIEVEMENTS",		( u32 )VIEW_ACHIEVEMENTS );
	// state.SetField ( -1, "VIEW_CHALLENGES",			( u32 )VIEW_CHALLENGES );

	state.SetField ( -1, "ON_SIGN_IN_SUCCEEDED",	( u32 )ON_SIGN_IN_SUCCEEDED );
	state.SetField ( -1, "ON_SIGN_IN_FAILED",		( u32 )ON_SIGN_IN_FAILED );

	luaL_Reg regTable [] = {
		{ "authenticatePlayer", 				_authenticatePlayer },
		{ "getListener",						&MOAIGlobalEventSource::_getListener < MOAIGooglePlayServicesAndroid > },
		{ "getPlayerAlias",						_getPlayerAlias },
		{ "getPlayerId",						_getPlayerId },
		{ "isSupported",						_isSupported },
		{ "logout",								_logout },
		{ "reportAchievementProgress",			_reportAchievementProgress },
		{ "reportScore",						_reportScore },
		{ "setListener",						&MOAIGlobalEventSource::_setListener < MOAIGooglePlayServicesAndroid > },
		{ "showDefaultAchievements",			_showDefaultAchievements },
		{ "showLeaderboard",					_showLeaderboard },
		{ "unlockAchievement",					_unlockAchievement },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}


//================================================================//
// MOAIUnityAdsAndroid JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_googleplayservices_MoaiGooglePlayServices_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	if ( MOAIGooglePlayServicesAndroid::IsValid ()) {

		// ZLLogF ( ZLLog::CONSOLE, "Java_com_moaisdk_googleplayservices_MoaiGooglePlayServices_AKUInvokeListener \n" );
		MOAIGooglePlayServicesAndroid::Get ().InvokeListener (( u32 )eventID );
	}
}
