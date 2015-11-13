//----------------------------------------------------------------//
// Copyright (c) 2014 DigitalClick Ltd. 
// All Rights Reserved. 
//----------------------------------------------------------------//

package com.ziplinegames.moai;

import com.google.android.gms.games.Games;

import com.google.example.games.basegameutils.GameHelper;
import com.google.example.games.basegameutils.GameHelper.GameHelperListener;

import android.app.Activity;
import android.content.Intent;

//================================================================//
// MoaiGooglePlayServicesGames
//================================================================//
public class MoaiGooglePlayServicesGames {

	private static Activity 				sActivity = null;
	private static GameHelper 				sHelper = null;
	private static GameHelperListener 		sListener = null;
	
	private static int 						REQUEST_ACHIEVEMENTS = 1488;
	private static int 						REQUEST_LEADERBOARD = 228;
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames onCreate:  -------------------------------------------------------- " );
		
		sActivity = activity;
		
		sHelper = new GameHelper ( sActivity, GameHelper.CLIENT_GAMES );
				
		sHelper.setConnectOnStart ( false );
		
		// sHelper.setMaxAutoSignInAttempts ( 3 );
		
		//TODO DEBUG_LOG
		// sHelper.enableDebugLog ( true );
		
		sListener = new GameHelper.GameHelperListener () {
	    	
	        public void onSignInSucceeded () {
	        	
	        	MoaiLog.i ( "MoaiGooglePlayServicesGames onSignInSucceeded: handle sign-in succeess" );
	        }

	        public void onSignInFailed () {
	        	
	        	MoaiLog.i ( "MoaiGooglePlayServicesGames onSignInFailed: handle sign-in failure (e.g. show Sign In button)" );
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

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames onStart:  -------------------------------------------------------- " );
		
		sHelper.onStart ( sActivity );
	}

	//----------------------------------------------------------------//
	public static void onStop () {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames onStop:  -------------------------------------------------------- " );
		
		sHelper.onStop ();
	}
	
	//----------------------------------------------------------------//
	public static void onDestroy () {}

	//----------------------------------------------------------------//
	public static void onBackPressed () {}
	
	//----------------------------------------------------------------//
	public static void onActivityResult ( int requestCode, int resultCode, Intent data ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames onActivityResult: requestCode::"+requestCode+" resultCode::"+resultCode+"  -------------------------------------------------------- " );
		
	    sHelper.onActivityResult ( requestCode, resultCode, data );
	}
	
	//================================================================//
	// MoaiGooglePlayServicesGames JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//	
	public static void authenticatePlayer () {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: authenticatePlayer -------------------------------------------------------- " );
		
		sHelper.beginUserInitiatedSignIn ();
	}

	//----------------------------------------------------------------//
	public static String getPlayerId () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: getPlayerId -------------------------------------------------------- " );
		if ( sHelper.isSignedIn ()) {
			return Games.Players.getCurrentPlayerId(sHelper.getApiClient());
		}
		return "";
	}
	
	//----------------------------------------------------------------//
	public static void getScores () {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: getScores -------------------------------------------------------- " );
	}
	
	//----------------------------------------------------------------//	
	public static boolean isSupported () {
		
		boolean signedIn = sHelper.isSignedIn ();
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: isSupported: "+signedIn+" -------------------------------------------------------- " );
	
		return signedIn;
	}
	
	//----------------------------------------------------------------//	
	public static void logout () {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: logout -------------------------------------------------------- " );
	
		sHelper.signOut ();
	}
	
	//----------------------------------------------------------------//	
	public static void showDefaultAchievements () {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: showDefaultAchievements -------------------------------------------------------- " );
		
		sActivity.startActivityForResult ( Games.Achievements.getAchievementsIntent ( sHelper.getApiClient() ), REQUEST_ACHIEVEMENTS );
	}
	
	//----------------------------------------------------------------//	
	public static void showLeaderboard ( String lbId ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: showLeaderboard: ibid =  "+lbId+" -------------------------------------------------------- " );
		
		sActivity.startActivityForResult ( Games.Leaderboards.getLeaderboardIntent ( sHelper.getApiClient (), lbId ), REQUEST_LEADERBOARD );
	}

	//----------------------------------------------------------------//	
	public static void reportScore ( String leaderBoardID, int score ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: reportScore: LBID "+leaderBoardID+"; SCORE "+score+" -------------------------------------------------------- " );
		
		if ( sHelper.isSignedIn ()) {
			Games.Leaderboards.submitScore ( sHelper.getApiClient(), leaderBoardID, score );
		}
	}
	
	//----------------------------------------------------------------//	
	public static void reportAchievementProgress ( String achievementID, int progress ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: reportAchievementProgress: AID "+achievementID+"; PROGRESS "+progress+" -------------------------------------------------------- " );
		
		if ( progress == 0 ) return;

		if ( sHelper.isSignedIn ()) {
			Games.Achievements.setSteps ( sHelper.getApiClient(), achievementID, progress );
		}
	}
	
	//----------------------------------------------------------------//	
	public static void unlockAchievement ( String achievementID ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: unlockAchievement: AID "+achievementID+" -------------------------------------------------------- " );
	
		if ( sHelper.isSignedIn ()) {
			Games.Achievements.unlockImmediate ( sHelper.getApiClient(), achievementID );
		}
	}
	
	//----------------------------------------------------------------//	
	public static void showGameCenter () {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGooglePlayServicesGames: showGameCenter -------------------------------------------------------- " );

	}
}
