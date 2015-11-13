// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef DISABLE_PLAYSERVICESGAMES

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/moaiext-jni.h>
#include <moai-android-google-play-services-games/MOAIGooglePlayServicesGamesAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	authenticatePlayer
	@text	Connects to the Google Play Game Services

	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_authenticatePlayer ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID authenticatePlayer = env->GetStaticMethodID ( playserv, "authenticatePlayer", "()V" );
		if ( authenticatePlayer == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "authenticatePlayer" );
		} else {

			env->CallStaticVoidMethod ( playserv, authenticatePlayer );
		}
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	getAchievements

	@out	table		achievements
*/
int MOAIGooglePlayServicesGamesAndroid::_getAchievements ( lua_State* L ) {
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getPlayerAlias

	@out	string 		name
*/
int MOAIGooglePlayServicesGamesAndroid::_getPlayerAlias ( lua_State* L ) {
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getPlayerId

	@out	string 		name
*/
int MOAIGooglePlayServicesGamesAndroid::_getPlayerId ( lua_State* L ) {
	
	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID getPlayerId = env->GetStaticMethodID ( playserv, "getPlayerId", "()Ljava/lang/String;" );
		if ( getPlayerId == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "getPlayerId" );
		} else {
			jstring jplayerId = (jstring)env->CallStaticObjectMethod( playserv, getPlayerId );
			JNI_GET_CSTRING ( jplayerId, playerId );
			if ( playerId ) {
				lua_pushstring ( state, playerId );
				return 1;
			}
		}
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	getScores

	@out	table		scores
*/
int MOAIGooglePlayServicesGamesAndroid::_getScores ( lua_State* L ) {
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	isSupported
	@text	Check connects to the Google Play Game Services

	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_isSupported ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID isSupported = env->GetStaticMethodID ( playserv, "isSupported", "()Z" );
		if ( isSupported == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "isSupported" );
		} else {

			bool success = ( bool ) env->CallStaticBooleanMethod ( playserv, isSupported );

			lua_pushboolean ( state, success );
			return 1;
		}
	}

	lua_pushboolean ( state, false );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	_logout
	@text	Logout

	@out	nil
 */
int MOAIGooglePlayServicesGamesAndroid::_logout ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID logout = env->GetStaticMethodID ( playserv, "logout", "()V" );
		if ( logout == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "logout" );
		} else {

			env->CallStaticVoidMethod ( playserv, logout );
		}
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	showDefaultAchievements
	@text	Shows the achievements

	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_showDefaultAchievements ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID showDefaultAchievements = env->GetStaticMethodID ( playserv, "showDefaultAchievements", "()V" );
		if ( showDefaultAchievements == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "showDefaultAchievements" );
		} else {

			env->CallStaticVoidMethod ( playserv, showDefaultAchievements );
		}
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	showLeaderboard
	@text	Shows the desired leaderboard

	@in		string leaderboardID
	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_showLeaderboard ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	cc8* board = lua_tostring ( state, 1 );

	JNI_GET_JSTRING ( board, jboard );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID showLeaderboard = env->GetStaticMethodID ( playserv, "showLeaderboard", "(Ljava/lang/String;)V" );
		if ( showLeaderboard == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "showLeaderboard" );
		} else {

			env->CallStaticVoidMethod ( playserv, showLeaderboard, jboard );
		}
	}

	return 0;
}


//----------------------------------------------------------------//
/**	@name	reportScore
	@text	Submits a score for the passed in leaderboard

	@in		string leaderboardID
	@in		number score
	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_reportScore ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	cc8* board = lua_tostring ( state, 1 );
	jint score = lua_tonumber ( state, 2 );

	JNI_GET_JSTRING ( board, jboard );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID reportScore = env->GetStaticMethodID ( playserv, "reportScore", "(Ljava/lang/String;I)V" );
		if ( reportScore == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "reportScore" );
		} else {

			env->CallStaticVoidMethod ( playserv, reportScore, jboard, score );
		}
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	reportAchievementProgress
	@text	Grants an achievement to the player

	@in		string achievementID
	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_reportAchievementProgress ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	cc8* ach = lua_tostring ( state, 1 );
	jint prgs = lua_tonumber ( state, 2 );

	JNI_GET_JSTRING ( ach, jach );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID reportAchievementProgress = env->GetStaticMethodID ( playserv, "reportAchievementProgress", "(Ljava/lang/String;I)V" );
		if ( reportAchievementProgress == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "reportAchievementProgress" );
		} else {

			env->CallStaticVoidMethod ( playserv, reportAchievementProgress, jach, prgs );
		}
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setGetScoresCallback

	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_setGetScoresCallback ( lua_State* L ) {
	
	return 0;
}

// //----------------------------------------------------------------//
// /**	@name	showGameCenter
// 	@text	

// 	@out	nil
// */
// int MOAIGooglePlayServicesGamesAndroid::_showGameCenter ( lua_State* L ) {

// 	JNI_GET_ENV ( jvm, env );
// 	MOAILuaState state ( L );

// 	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
//     if ( playserv == NULL ) {

// 		ZLLog::LogF ( "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
//     } else {

//     	jmethodID showGameCenter = env->GetStaticMethodID ( playserv, "showGameCenter", "()V" );
//    		if ( showGameCenter == NULL ) {

// 			ZLLog::LogF ( "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "showGameCenter" );
// 		} else {

// 			env->CallStaticVoidMethod ( playserv, showGameCenter );
// 		}
// 	}

// 	return 0;
// }

//----------------------------------------------------------------//
/**	@name	unlockAchievement
	@text	Grants an achievement to the player

	@in		string achievementID
	@out	nil
*/
int MOAIGooglePlayServicesGamesAndroid::_unlockAchievement ( lua_State* L ) {

	JNI_GET_ENV ( jvm, env );
	MOAILuaState state ( L );

	cc8* ach = lua_tostring ( state, 1 );

	JNI_GET_JSTRING ( ach, jach );

	jclass playserv = env->FindClass ( "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	if ( playserv == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiGooglePlayServicesGames" );
	} else {

		jmethodID unlockAchievement = env->GetStaticMethodID ( playserv, "unlockAchievement", "(Ljava/lang/String;)V" );
		if ( unlockAchievement == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MOAIGooglePlayServicesGamesAndroid: Unable to find static java method %s", "unlockAchievement" );
		} else {

			env->CallStaticVoidMethod ( playserv, unlockAchievement, jach );
		}
	}

	return 0;
}

//================================================================//
// MOAIGooglePlayServicesGamesAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIGooglePlayServicesGamesAndroid::MOAIGooglePlayServicesGamesAndroid () {

	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIGooglePlayServicesGamesAndroid::~MOAIGooglePlayServicesGamesAndroid () {

}

//----------------------------------------------------------------//
void MOAIGooglePlayServicesGamesAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "VIEW_DEFAULT",			( u32 )VIEW_DEFAULT );
	state.SetField ( -1, "VIEW_LEADERBOARDS",		( u32 )VIEW_LEADERBOARDS );
	state.SetField ( -1, "VIEW_ACHIEVEMENTS",		( u32 )VIEW_ACHIEVEMENTS );
	state.SetField ( -1, "VIEW_CHALLENGES",			( u32 )VIEW_CHALLENGES );

	luaL_Reg regTable [] = {
		{ "authenticatePlayer", 				_authenticatePlayer },
		{ "getAchievements",					_getAchievements },
		{ "getPlayerAlias",						_getPlayerAlias },
		{ "getPlayerId",						_getPlayerId },
		{ "getScores",							_getScores },
		{ "getAchievements",					_getAchievements },
		{ "isSupported",						_isSupported },
		{ "logout",								_logout },
		{ "reportAchievementProgress",			_reportAchievementProgress },
		{ "reportScore",						_reportScore },
		{ "setGetScoresCallback",				_setGetScoresCallback },
		{ "showDefaultAchievements",			_showDefaultAchievements },
		{ "showLeaderboard",					_showLeaderboard },
		// { "showGameCenter",						_showGameCenter },
		{ "unlockAchievement",					_unlockAchievement },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

// AKU Callbacks

//	EMPTY

#endif