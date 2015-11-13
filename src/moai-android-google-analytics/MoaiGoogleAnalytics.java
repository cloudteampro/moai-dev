//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

package com.ziplinegames.moai;

import android.app.Activity;

import com.google.analytics.tracking.android.EasyTracker;
import com.google.analytics.tracking.android.MapBuilder;

//================================================================//
// MoaiFacebook
//================================================================//
public class MoaiGoogleAnalytics {

	private static Activity sActivity = null;
	private static EasyTracker easyTracker = null;
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		
		MoaiLog.i ( "MoaiGoogleAnalytics onCreate: Initializing GA" );

		sActivity = activity;

		easyTracker = EasyTracker.getInstance ( sActivity );
	}


	public static void onStart( ) {

		MoaiLog.i ( "MoaiGoogleAnalytics onStart: " );

		easyTracker.activityStart ( sActivity );
	}

	public static void onStop ( ) {

		MoaiLog.i ( "MoaiGoogleAnalytics onStop: Ending GA Session" );

		easyTracker.activityStop ( sActivity );
	}
	
	//================================================================//
	// GoogleAnalytics JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//	
	public static void logEvent ( String eventCategory, String eventAction, String eventLabel, int eventValue ) {
		MoaiLog.i ( "MoaiGoogleAnalytics logEvent: logEvent(String, String, String, Integer) " );
		easyTracker.send(MapBuilder
      		.createEvent(eventCategory,
                   eventAction,
                   eventLabel, 
                   (long)eventValue)
      		.build()
  		);
	}
}
