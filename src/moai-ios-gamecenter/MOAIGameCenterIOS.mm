// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#import <moai-ios/headers.h>
#import <moai-ios-gamecenter/MOAIGameCenterIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	authenticatePlayer
	@text	Makes sure GameCenter is supported and an account is 
			logged in. If none are logged in, this will prompt the 
			user to log in. This must be called before any other 
			MOAIGameCenterIOS functions.
			
	@in		nil
	@out	nil
*/
int MOAIGameCenterIOS::_authenticatePlayer ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	// Check for presence of GKLocalPlayer class.
    BOOL localPlayerClassAvailable = ( NSClassFromString ( @"GKLocalPlayer" )) != nil;
	
	// The device must be running iOS 6.0 or later.
    NSString *reqSysVer = @"6.0";
    NSString *currSysVer = [[ UIDevice currentDevice ] systemVersion ];
    BOOL osVersionSupported = ([ currSysVer compare:reqSysVer options:NSNumericSearch ] != NSOrderedAscending );
    if ( localPlayerClassAvailable && osVersionSupported ) {

		// If GameCenter is available, attempt to authenticate the local player
		GKLocalPlayer* localPlayer = [ GKLocalPlayer localPlayer ];
		[ localPlayer setAuthenticateHandler:^( UIViewController *viewcontroller, NSError *error ) {
			
			if ( !error && viewcontroller ) {
				
				UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
				UIViewController* rootVC = [ window rootViewController ];
				[ rootVC presentViewController:viewcontroller animated:YES completion:nil ];
			}
			else {
				if ([ error code ] == GKErrorNotSupported || [ error code ] == GKErrorGameUnrecognized ) {
					
//                    MOAILogF ( L, ZLLog::LOG_ERROR, [[ error description ] UTF8String ]);
					MOAIGameCenterIOS::Get ().mIsGameCenterSupported = FALSE;
				}
				else if ([ GKLocalPlayer localPlayer ].isAuthenticated ) {
					
					MOAIGameCenterIOS::Get ().mLocalPlayer = localPlayer;
					MOAIGameCenterIOS::Get ().mIsGameCenterSupported = TRUE;
					MOAIGameCenterIOS::Get ().GetAchievements ();
				}
			}
		}];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getPlayerAlias
	@text	Returns the user visible player name string from GameCenter.

	@in 	nil
	@out 	string	alias
 */
int MOAIGameCenterIOS::_getPlayerAlias ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* alias = [[ GKLocalPlayer localPlayer ].alias UTF8String ];
	lua_pushstring ( state, alias );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getPlayerId
	@text	Returns the local playerid string from GameCenter.
 
	@in 	nil
	@out 	string	id
*/
int MOAIGameCenterIOS::_getPlayerId ( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	cc8* playerId = [[ GKLocalPlayer localPlayer ].playerID UTF8String ];
	state.Push ( playerId );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	getScores
	@text	Returns the top ten scores of everyone for all-time. 
			Optionally specify a leaderboard, player scope, time scope 
			and range. If no leaderboard was specified, this will 
			return scores from the default leaderboard.
	
	@opt	string		category
	@opt	number		playerScope
	@opt	number		timeScope
	@opt	number		startRange
	@opt	number		endRange
	@out	table		scores
*/
int MOAIGameCenterIOS::_getScores ( lua_State* L ) {
	
	if ( !MOAIGameCenterIOS::Get ().mIsGameCenterSupported ) {
		
		return 0;
	}

	MOAILuaState state ( L );
		
	cc8* category = state.GetValue < cc8* >( 1, NULL );
	int playerScope = state.GetValue < int >( 2, PLAYERSCOPE_GLOBAL );
	int timeScope = state.GetValue < int >( 3, TIMESCOPE_ALLTIME );
	int startRange = state.GetValue < int >( 4, 1 );
	int endRange = state.GetValue < int >( 5, 10 );

	GKLeaderboard *leaderboardRequest = [[ GKLeaderboard alloc] init ];
    if ( leaderboardRequest != nil ) {
	
		if ( category ) {
			
			leaderboardRequest.category = [ NSString stringWithUTF8String:category];
		}
		
        leaderboardRequest.playerScope = playerScope;
        leaderboardRequest.timeScope = timeScope;
        leaderboardRequest.range = NSMakeRange ( startRange, endRange );
        [ leaderboardRequest loadScoresWithCompletionHandler: ^( NSArray *scores, NSError *error ) {
		
            if ( error != nil ) {
	
				printf ( "Error in getting leaderboard scores: %ld\n", ( long )[ error code ]);
            }
            if ( scores != nil ) {
	
				MOAIGameCenterIOS::Get ().CallScoresCallback ( scores );
            }
		}];
    }
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	isAuthenticated
	@text	Returns whether or not there is an authenticated local player.
			
	@in		nil
	@out	bool	isAuthenticated
*/
int MOAIGameCenterIOS::_isAuthenticated ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	GKLocalPlayer* player = [ GKLocalPlayer localPlayer ];
	lua_pushboolean ( state, [ GKLocalPlayer localPlayer ].isAuthenticated == YES );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	isSupported
	@text	Returns whether or not GameCenter is supported on the 
			current device.
			
	@in		nil
	@out	bool	isSupported
*/
int MOAIGameCenterIOS::_isSupported ( lua_State* L ) {
	
	MOAILuaState state ( L );

	lua_pushboolean ( state, MOAIGameCenterIOS::Get ().mIsGameCenterSupported );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	reportAchievementProgress
	@text	Reports an achievement progress to GameCenter.
			
	@in		string	identifier
	@in		number	percentComplete
	@out	nil
*/
int MOAIGameCenterIOS::_reportAchievementProgress ( lua_State* L ) {
	
	if ( !MOAIGameCenterIOS::Get ().mIsGameCenterSupported ) {
		
		return 0;
	}
	
	MOAILuaState state ( L );

	cc8* identifier = state.GetValue < cc8* >( 1, "" );
	float percent	= state.GetValue < float >( 2, 0.0f );
		
	MOAIGameCenterIOS::Get ().ReportAchievementProgress ( identifier, percent );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	reportScore
	@text	Reports a score to a desired leaderboard on GameCenter.
	
	@in		string	category
	@in		number	score
	@out	nil
*/
int MOAIGameCenterIOS::_reportScore ( lua_State* L ) {
	
	if ( !MOAIGameCenterIOS::Get ().mIsGameCenterSupported ) {
		
		return 0;
	}
	
	MOAILuaState state ( L );
	
	cc8* category = state.GetValue < cc8* >( 1, "" );
    s64 score = state.GetValue < s64 >( 2, 0 );
	
	MOAIGameCenterIOS::Get ().ReportScore ( score, category );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	setGetScoresCallabck
	@text	Sets the function to be called upon a successful '
			getScores () call.
			
	@in		function	getScoresCallback
	@out	nil
*/
int MOAIGameCenterIOS::_setGetScoresCallback ( lua_State* L ) {
	
	MOAILuaState state ( L );

	MOAIGameCenterIOS::Get ().mGetScoresCallback.SetRef ( state, 1 );
		
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	showDefaultAchievments
	@text	Displays the default achievements view.
			
	@in		nil
	@out	nil
*/
int MOAIGameCenterIOS::_showDefaultAchievements ( lua_State* L ) {
	
	MOAILuaState state ( L );

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];	
	
	GKAchievementViewController *achievements = [[ GKAchievementViewController alloc ] init ];
    if (achievements != NULL) {
	
        achievements.achievementDelegate = MOAIGameCenterIOS::Get ().mAchievementDelegate;
		if  ( rootVC != nil ) {
			
			[ rootVC presentViewController: achievements animated: YES completion: nil ];
		}
    }

	[ achievements release ];
		
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	showDefaultLeaderboard
	@text	Displays the default leaderboard view.
			
	@in		nil
	@out	nil
*/
int MOAIGameCenterIOS::_showDefaultLeaderboard ( lua_State* L ) {
	
	MOAILuaState state ( L );

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];	
	GKLeaderboardViewController *leaderboardController = [[ GKLeaderboardViewController alloc ] init ];
    if ( leaderboardController != nil ) {	
	
        leaderboardController.leaderboardDelegate = MOAIGameCenterIOS::Get ().mLeaderboardDelegate;
		if ( rootVC != nil ) {
			
			[ rootVC presentViewController: leaderboardController animated: YES completion: nil ];
		}
    }

	[ leaderboardController release ];
		
	return 0;
}

//----------------------------------------------------------------//
/**	@name	showGameCenter
	@text	Displays the game center view
 
	@in		number	state	One of MOAIGameCenterIOS.VIEW_DEFAULT, VIEW_LEADERBOARDS,
							VIEW_ACHIEVEMENTS, VIEW_CHALLENGES
	@opt	string	id		Leaderboard ID
	@out	nil
*/

int MOAIGameCenterIOS::_showGameCenter ( lua_State *L ) {
	
	MOAILuaState state ( L );
	
	GKGameCenterViewControllerState viewState = state.GetValue < int >( 1, GKGameCenterViewControllerStateDefault );
	cc8* name = state.GetValue < cc8* > ( 2, 0 );
	
	NSString* leaderboardId = nil;
	if ( name ) {
		leaderboardId = [ NSString stringWithUTF8String:name ];
	}
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	
	GKGameCenterViewController* gameCenterController = [[ GKGameCenterViewController alloc ] init ];
	if ( gameCenterController ) {
		
		gameCenterController.gameCenterDelegate = MOAIGameCenterIOS::Get ().mGameCenterDelegate;
		gameCenterController.viewState = viewState;
		
		if ([ gameCenterController respondsToSelector:@selector ( leaderboardIdentifier )] ) {
			gameCenterController.leaderboardIdentifier = leaderboardId;
		}
		
		if ( rootVC != nil ) {
			
			[ rootVC presentViewController:gameCenterController animated:YES completion:nil ];
		}
	}
	
	[ gameCenterController release ];
	
	return 0;
}

//================================================================//
// MOAIGameCenterIOS
//================================================================//

//----------------------------------------------------------------//
MOAIGameCenterIOS::MOAIGameCenterIOS () :
	mIsGameCenterSupported ( false ) {

	RTTI_SINGLE ( MOAILuaObject )
	
	mLeaderboardDelegate	= [[ MOAIGameCenterIOSLeaderboardDelegate alloc ] init];
	mAchievementDelegate	= [[ MOAIGameCenterIOSAchievementDelegate alloc ] init];
	mGameCenterDelegate		= [[ MOAIGameCenterIOSGameCenterDelegate alloc ] init];
	mAchievementsDictionary = [[ NSMutableDictionary alloc ] init ];
}

//----------------------------------------------------------------//
MOAIGameCenterIOS::~MOAIGameCenterIOS () {
	
	[ mAchievementDelegate release ];
	[ mLeaderboardDelegate release ];
	[ mGameCenterDelegate release ];
	[ mAchievementsDictionary release ];
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "TIMESCOPE_TODAY",		( u32 )TIMESCOPE_TODAY );
	state.SetField ( -1, "TIMESCOPE_WEEK",		( u32 )TIMESCOPE_WEEK );
	state.SetField ( -1, "TIMESCOPE_ALLTIME",	( u32 )TIMESCOPE_ALLTIME );
	
	state.SetField ( -1, "PLAYERSCOPE_GLOBAL",	( u32 )PLAYERSCOPE_GLOBAL );
	state.SetField ( -1, "PLAYERSCOPE_FRIENDS",	( u32 )PLAYERSCOPE_FRIENDS );
	
	state.SetField ( -1, "VIEW_DEFAULT",		( int )GKGameCenterViewControllerStateDefault );
	state.SetField ( -1, "VIEW_LEADERBOARDS",	( int )GKGameCenterViewControllerStateLeaderboards );
	state.SetField ( -1, "VIEW_ACHIEVEMENTS",	( int )GKGameCenterViewControllerStateAchievements );
	state.SetField ( -1, "VIEW_CHALLENGES",		( int )GKGameCenterViewControllerStateChallenges );
	
	luaL_Reg regTable [] = {
		{ "authenticatePlayer",			_authenticatePlayer },
		{ "getPlayerAlias",				_getPlayerAlias },
		{ "getPlayerId",				_getPlayerId },
		{ "getScores",					_getScores },
		{ "isSupported",				_isSupported },
		{ "reportAchievementProgress",	_reportAchievementProgress },
		{ "reportScore",				_reportScore },
		{ "setGetScoresCallback",		_setGetScoresCallback },
		{ "showDefaultAchievements",	_showDefaultAchievements },
		{ "showDefaultLeaderboard",		_showDefaultLeaderboard },
		{ "showGameCenter",				_showGameCenter },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::CallScoresCallback ( NSArray* scores ) {

	if ( mGetScoresCallback && [ scores count ] > 0 ) {
	
		MOAIScopedLuaState state = mGetScoresCallback.GetSelf ();
		lua_newtable ( state );
		
		for ( id score in scores ) {
		
			lua_pushstring( state, "formattedValue");
			lua_pushstring ( state, [[ score formattedValue ] UTF8String ]);
			lua_settable ( state, -3 );			
			
			lua_pushstring( state, "playerId");
			lua_pushstring ( state, [[ score playerID ] UTF8String ]);
			lua_settable ( state, -3 );
			
			lua_pushstring( state, "category");
			lua_pushstring ( state, [[ score category ] UTF8String ]);
			lua_settable ( state, -3 );
						
			lua_pushstring( state, "rank");
			lua_pushnumber ( state, [ score rank ] );
			lua_settable ( state, -3 );
			
			lua_pushstring( state, "date");
			[[ score date ] toLua:state ];
			lua_settable ( state, -3 );
		}
		
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::CreateAchievementDictionary ( NSArray* achievements ) {
	
	for ( GKAchievement* achievement in achievements ) {
		[ mAchievementsDictionary setObject: achievement forKey: achievement.identifier ];
	}
}

//----------------------------------------------------------------//
GKAchievement* MOAIGameCenterIOS::GetAchievementFromDictionary ( cc8* identifier ) {
	
	GKAchievement* achievement = [ mAchievementsDictionary objectForKey:[ NSString stringWithUTF8String:identifier ]];
	
    if ( achievement == nil ) {
        achievement = [[[ GKAchievement alloc ] initWithIdentifier:[ NSString stringWithUTF8String:identifier ]] autorelease ];
        [ mAchievementsDictionary setObject:achievement forKey:achievement.identifier  ];
    }
	
    return [[ achievement retain ] autorelease ];
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::GetAchievements () {
	
	[ GKAchievement loadAchievementsWithCompletionHandler:^( NSArray* achievements, NSError* error ) {
		if ( error == nil ) {
			CreateAchievementDictionary ( achievements );
		}
	}];
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::ReportAchievementProgress ( cc8* identifier, float percent ) {

	GKAchievement *achievement = GetAchievementFromDictionary ( identifier );
	
    if ( achievement != nil && achievement.percentComplete < percent ) {
		
		if ( !achievement.isCompleted ) {
			
			achievement.percentComplete = percent;
			
			[ achievement reportAchievementWithCompletionHandler:^( NSError *error ) {
				if ( error != nil ) {
					printf ( "Error in achievement reporting: %ld", ( long )[ error code ]);
					// TODO: Save off achievement for later if network error
				}
			}];
		}
	}
}

//----------------------------------------------------------------//
void MOAIGameCenterIOS::ReportScore ( s64 score, cc8* category ) {

	GKScore *scoreReporter = [[[ GKScore alloc ] initWithCategory:[ NSString stringWithUTF8String:category ]] autorelease ];
	
	if ( scoreReporter ) {
	
		scoreReporter.value = score;
		
		[ scoreReporter reportScoreWithCompletionHandler: ^( NSError *error ) {
			if ( error != nil ) {
				
				printf ( "Error in score reporting: %ld", ( long )[ error code ]);
				// TODO: Save off score for later if network error
			}
		}];
	}
}

//================================================================//
// MOAIGameCenterIOSLeaderboardDelegate
//================================================================//
#pragma mark -
#pragma mark Protocol MOAIGameCenterIOSLeaderboardDelegate
@implementation MOAIGameCenterIOSLeaderboardDelegate

	//----------------------------------------------------------------//
	- ( void ) leaderboardViewControllerDidFinish:( GKLeaderboardViewController* ) viewController {
		UNUSED ( viewController );
	
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		if ( rootVC ) {
			[ rootVC dismissViewControllerAnimated:YES completion:nil ];
		}
	}
@end

//================================================================//
// MOAIGameCenterIOSAchievementDelegate
//================================================================//
#pragma mark -
#pragma mark Protocol MOAIGameCenterIOSAchievementDelegate
@implementation MOAIGameCenterIOSAchievementDelegate

	//----------------------------------------------------------------//
	- ( void ) achievementViewControllerDidFinish:( GKAchievementViewController* ) viewController {
		UNUSED ( viewController );
	
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		if ( rootVC ) {
			[ rootVC dismissViewControllerAnimated:YES completion:nil ];
		}
	}
@end

//================================================================//
// MOAIGameCenterIOSGameCenterDelegate
//================================================================//
#pragma mark -
#pragma mark Protocol MOAIGameCenterIOSGameCenterDelegate
@implementation MOAIGameCenterIOSGameCenterDelegate

	//----------------------------------------------------------------//
	- ( void ) gameCenterViewControllerDidFinish:( GKGameCenterViewController* ) viewController {
		
		UNUSED ( viewController );
		
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		if ( rootVC ) {
			
			[ rootVC dismissViewControllerAnimated:YES completion:nil ];
		}
	}
@end
