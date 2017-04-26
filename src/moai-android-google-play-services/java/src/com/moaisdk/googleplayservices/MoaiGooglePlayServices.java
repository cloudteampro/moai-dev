//----------------------------------------------------------------//
// Copyright (c) 2014 DigitalClick Ltd.
// All Rights Reserved.
//----------------------------------------------------------------//

package com.moaisdk.googleplayservices;

import com.moaisdk.core.*;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.Player;

import com.google.example.games.basegameutils.GameHelper;
import com.google.example.games.basegameutils.GameHelper.GameHelperListener;

import android.app.Activity;
import android.content.Intent;

//================================================================//
// MoaiGooglePlayServices
//================================================================//
public class MoaiGooglePlayServices {

	public enum ListenerEvent {
		ON_SIGN_IN_SUCCEEDED,
		ON_SIGN_IN_FAILED,
	}

	private static Activity 				sActivity = null;
	private static GameHelper 				sHelper = null;
	private static GameHelperListener 		sListener = null;

	protected static native void AKUInvokeListener 	( int eventID );

	private static int 						REQUEST_ACHIEVEMENTS = 1488;
	private static int 						REQUEST_LEADERBOARD = 228;

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices onCreate:  -------------------------------------------------------- " );

		sActivity = activity;

		sHelper = new GameHelper ( sActivity, GameHelper.CLIENT_GAMES );

		sHelper.setConnectOnStart ( false );
		// sHelper.setMaxAutoSignInAttempts ( 3 );

		//TODO DEBUG_LOG
		// sHelper.enableDebugLog ( true );

		sListener = new GameHelper.GameHelperListener () {

			public void onSignInSucceeded () {
				MoaiLog.i ( "MoaiGooglePlayServices onSignInSucceeded: handle sign-in succeess" );
				synchronized ( Moai.sAkuLock ) {
					MoaiGooglePlayServices.AKUInvokeListener ( ListenerEvent.ON_SIGN_IN_SUCCEEDED.ordinal ());
				}
			}

			public void onSignInFailed () {
				MoaiLog.i ( "MoaiGooglePlayServices onSignInFailed: handle sign-in failure (e.g. show Sign In button)" );
				synchronized ( Moai.sAkuLock ) {
					MoaiGooglePlayServices.AKUInvokeListener ( ListenerEvent.ON_SIGN_IN_FAILED.ordinal ());
				}
			}
		};

		sHelper.setup ( sListener );
	}

	//----------------------------------------------------------------//
	public static void onResume () {}

	//----------------------------------------------------------------//
	public static void onPause () {}

	//----------------------------------------------------------------//
	public static void onStart () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices onStart:  -------------------------------------------------------- " );

		sHelper.onStart ( sActivity );
	}

	//----------------------------------------------------------------//
	public static void onStop () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices onStop:  -------------------------------------------------------- " );

		sHelper.onStop ();
	}

	//----------------------------------------------------------------//
	public static void onDestroy () {}

	//----------------------------------------------------------------//
	public static void onBackPressed () {}

	//----------------------------------------------------------------//
	public static void onActivityResult ( int requestCode, int resultCode, Intent data ) {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices onActivityResult: requestCode::"+requestCode+" resultCode::"+resultCode+"  -------------------------------------------------------- " );

		sHelper.onActivityResult ( requestCode, resultCode, data );
	}

	//================================================================//
	// MoaiGooglePlayServices JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void authenticatePlayer () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: authenticatePlayer -------------------------------------------------------- " );

		sHelper.beginUserInitiatedSignIn ();
	}

	//----------------------------------------------------------------//
	public static String getPlayerAlias () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: getPlayerId -------------------------------------------------------- " );
		if ( sHelper.isSignedIn ()) {
			Player player = Games.Players.getCurrentPlayer ( sHelper.getApiClient ());
			if ( player != null ) {
				return player.getDisplayName ();
			}
		}
		return "";
	}

	//----------------------------------------------------------------//
	public static String getPlayerId () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: getPlayerId -------------------------------------------------------- " );
		if ( sHelper.isSignedIn ()) {
			return Games.Players.getCurrentPlayerId(sHelper.getApiClient());
		}
		return "";
	}

	//----------------------------------------------------------------//
	public static void getScores () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: getScores -------------------------------------------------------- " );
	}

	//----------------------------------------------------------------//
	public static boolean isAuthenticated () {
		boolean signedIn = sHelper.isSignedIn ();
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: isAuthenticated: "+signedIn+" -------------------------------------------------------- " );
		return signedIn;
	}

	//----------------------------------------------------------------//
	public static boolean isSupported () {

		boolean signedIn = sHelper.isSignedIn ();

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: isSupported: "+signedIn+" -------------------------------------------------------- " );

		return signedIn;
	}

	//----------------------------------------------------------------//
	public static void logout () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: logout -------------------------------------------------------- " );

		sHelper.signOut ();
	}

	//----------------------------------------------------------------//
	public static void showDefaultAchievements () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: showDefaultAchievements -------------------------------------------------------- " );

		sActivity.startActivityForResult ( Games.Achievements.getAchievementsIntent ( sHelper.getApiClient() ), REQUEST_ACHIEVEMENTS );
	}

	//----------------------------------------------------------------//
	public static void showLeaderboard ( String lbId ) {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: showLeaderboard: ibid =  "+lbId+" -------------------------------------------------------- " );

		sActivity.startActivityForResult ( Games.Leaderboards.getLeaderboardIntent ( sHelper.getApiClient (), lbId ), REQUEST_LEADERBOARD );
	}

	//----------------------------------------------------------------//
	public static void reportScore ( String leaderBoardID, int score ) {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: reportScore: LBID "+leaderBoardID+"; SCORE "+score+" -------------------------------------------------------- " );

		if ( sHelper.isSignedIn ()) {
			Games.Leaderboards.submitScore ( sHelper.getApiClient(), leaderBoardID, score );
		}
	}

	//----------------------------------------------------------------//
	public static void reportAchievementProgress ( String achievementID, int progress ) {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: reportAchievementProgress: AID "+achievementID+"; PROGRESS "+progress+" -------------------------------------------------------- " );

		if ( progress == 0 ) return;

		if ( sHelper.isSignedIn ()) {
			Games.Achievements.setSteps ( sHelper.getApiClient(), achievementID, progress );
		}
	}

	//----------------------------------------------------------------//
	public static void unlockAchievement ( String achievementID ) {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: unlockAchievement: AID "+achievementID+" -------------------------------------------------------- " );

		if ( sHelper.isSignedIn ()) {
			Games.Achievements.unlockImmediate ( sHelper.getApiClient(), achievementID );
		}
	}

	//----------------------------------------------------------------//
	public static void showGameCenter () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServices: showGameCenter -------------------------------------------------------- " );

	}
}
