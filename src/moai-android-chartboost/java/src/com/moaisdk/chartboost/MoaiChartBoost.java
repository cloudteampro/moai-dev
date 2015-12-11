//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.chartboost;

import com.moaisdk.core.MoaiLog;
import com.moaisdk.core.Moai;

import android.app.Activity;

import com.chartboost.sdk.CBLocation;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostDelegate;

@SuppressWarnings("unused")

//================================================================//
// MoaiChartBoost
//================================================================//
public class MoaiChartBoost extends ChartboostDelegate {

	public enum ListenerEvent {
		INTERSTITIAL_LOAD_FAILED,
		INTERSTITIAL_DISMISSED,
		REWARDED_VIDEO_DISMISSED,
		REWARDED_VIDEO_WILL_START,
		REWARDED_VIDEO_COMPLETED,
		REWARDED_VIDEO_CACHED
	}

	private static Activity sActivity = null;
	
	protected static native void AKUInvokeListener 			( int eventID );
	protected static native void AKURewardedVideoCompleted 	( int reward );
	
	//----------------------------------------------------------------//
	public static void onBackPressed ( Activity activity ) {
		
		MoaiLog.i ( "MoaiChartBoost: onBackPressed" );

		if ( !Chartboost.onBackPressed ()) {
			activity.onBackPressed ();
		}
	}
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
	
		MoaiLog.i ( "MoaiChartBoost: onCreate" );
		sActivity = activity;
	}

	//----------------------------------------------------------------//
	public static void onDestroy ( Activity activity ) {
 
		MoaiLog.i ( "MoaiChartBoost: onDestroy" );
		Chartboost.onDestroy ( sActivity );
	}

	//----------------------------------------------------------------//
	public static void onPause () {
 
		MoaiLog.i ( "MoaiChartBoost: onPause" );
		Chartboost.onPause ( sActivity );
	}

	//----------------------------------------------------------------//
	public static void onResume () {
 
		MoaiLog.i ( "MoaiChartBoost: onResume" );
		Chartboost.onResume ( sActivity );
	}
		
	//----------------------------------------------------------------//
	public static void onStart () {
		
		MoaiLog.i ( "MoaiChartBoost: onStart" );
		Chartboost.onStart ( sActivity );
	}
	
	//----------------------------------------------------------------//
	public static void onStop () {

		MoaiLog.i ( "MoaiChartBoost: onStop" );
		Chartboost.onStop ( sActivity );
	}

	//================================================================//
	// ChartBoost JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void cacheInterstitial ( String location ) {
		
		MoaiLog.i ( "MoaiChartBoost: cacheInterstitial" );
		
		if ( location != null ) {
			Chartboost.cacheInterstitial ( location );
		}
		else {
			Chartboost.cacheInterstitial ( CBLocation.LOCATION_DEFAULT );
		}
	}

	//----------------------------------------------------------------//
	public static void cacheRewardedVideo ( String location ) {
		
		MoaiLog.i ( "MoaiChartBoost: cacheRewardedVideo" );
		
		if ( location != null ) {
			Chartboost.cacheRewardedVideo ( location );
		}
		else {
			Chartboost.cacheRewardedVideo ( CBLocation.LOCATION_DEFAULT );
		}
	}

	//----------------------------------------------------------------//
	public static boolean hasCachedInterstitial ( String location ) {
		
		MoaiLog.i ( "MoaiChartBoost: hasCachedInterstitial" );
		
		if ( location != null ) {
			return Chartboost.hasInterstitial ( location );
		}
		return Chartboost.hasInterstitial ( CBLocation.LOCATION_DEFAULT );
	}

	//----------------------------------------------------------------//
	public static boolean hasRewardedVideo ( String location ) {
		
		MoaiLog.i ( "MoaiChartBoost: hasRewardedVideo" );
		
		if ( location != null ) {
			return Chartboost.hasRewardedVideo ( location );
		}
		return Chartboost.hasRewardedVideo ( CBLocation.LOCATION_DEFAULT );
	}

	//----------------------------------------------------------------//
	public static void init ( String appId, String appSignature ) {
		
		MoaiLog.i ( "MoaiChartBoost: init" );

		Chartboost.startWithAppId ( sActivity, appId, appSignature );
		Chartboost.setDelegate ( new MoaiChartBoost ());
		Chartboost.onCreate ( sActivity );
	}

	//----------------------------------------------------------------//
	public static boolean showInterstitial ( String location ) {
		
		MoaiLog.i ( "MoaiChartBoost: showInterstitial" );

		if ( location == null ) {
			location = CBLocation.LOCATION_DEFAULT;
		}

		if ( !Chartboost.hasInterstitial ( location )) {
			return false;
		}
		
		Chartboost.showInterstitial ( location );
		return true;
	}

	//----------------------------------------------------------------//
	public static boolean showRewardedVideo ( String location ) {
		
		MoaiLog.i ( "MoaiChartBoost: showRewardedVideo" );
		
		if ( location == null ) {
			location = CBLocation.LOCATION_DEFAULT;
		}
		
		if ( !Chartboost.hasRewardedVideo ( location )) {
			return false;
		}

		Chartboost.showRewardedVideo ( location );
		return true;
	}

	//================================================================//
	// ChartBoostDelegate methods
	//================================================================//

	//----------------------------------------------------------------//
	public void didCacheRewardedVideo ( String location ) {
		
		synchronized ( Moai.sAkuLock ) {
			AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_CACHED.ordinal ());
		}		
	}

	//----------------------------------------------------------------//
	public void didDismissInterstitial ( String location ) {

		MoaiLog.i ( "MoaiChartBoost: didDismissInterstitial" );
		synchronized ( Moai.sAkuLock ) {
			AKUInvokeListener ( ListenerEvent.INTERSTITIAL_DISMISSED.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void didFailToLoadInterstitial ( String location ) {
		
		MoaiLog.i ( "MoaiChartBoost: didFailToLoadInterstitial" );
		synchronized ( Moai.sAkuLock ) {
			AKUInvokeListener ( ListenerEvent.INTERSTITIAL_LOAD_FAILED.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void willDisplayVideo ( String location ) {

		synchronized ( Moai.sAkuLock ) {
			AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_WILL_START.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void didCompleteRewardedVideo ( String location, int reward ) {
		
		synchronized ( Moai.sAkuLock ) {
			AKURewardedVideoCompleted ( reward );
		}
	}

	//----------------------------------------------------------------//
	public void didDismissRewardedVideo ( String location ) {

		synchronized ( Moai.sAkuLock ) {
			AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_DISMISSED.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public boolean shouldDisplayMoreApps () {
		
		return false;
	}
	
	//----------------------------------------------------------------//
	public boolean shouldRequestMoreApps () {
		
		return false;
	}
}
