//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved. 
// http://cloudteam.pro
//----------------------------------------------------------------//

package com.moaisdk.unityads;

import android.app.Activity;

import com.moaisdk.core.*;

import com.unity3d.ads.android.data.UnityAdsDevice;
import com.unity3d.ads.android.IUnityAdsListener;
import com.unity3d.ads.android.UnityAds;

//================================================================//
// MoaiUnityAds
//================================================================//
public class MoaiUnityAds {

	public enum ListenerEvent {
		ON_HIDE,
		ON_SHOW,
		VIDEO_COMPLETED,
		VIDEO_STARTED,
    }

	private static Activity 		sActivity 		= null;
	
	protected static native void AKUInvokeListener 	( int eventID );
	protected static native void AKUVideoCompleted 	( String rewardItemKey, boolean skipped );
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		
		MoaiLog.i ( " MoaiUnityAds onCreate: UnityAds.changeActivity ( sActivity ) " );
		
		sActivity = activity;

  		UnityAds.changeActivity ( sActivity );
	}
	
	//================================================================//
	// MoaiUnityAds JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static boolean canShow ( String zone ) {

		if ( zone != null ) {
			try {
				UnityAds.setZone ( zone );
			} catch ( Exception e ) {
				e.printStackTrace ();
				return false;
			}
		}

		return UnityAds.canShow ();
	}

	//----------------------------------------------------------------//
	public static String getAdvertisingTrackingId () {

		MoaiLog.i ( "MoaiUnityAds getAdvertisingTrackingId" );
		String advertisingId;

		try {
			advertisingId = UnityAdsDevice.getAdvertisingTrackingId ();
		} catch ( Exception e ) {
			e.printStackTrace ();
			return null;
		}

		return advertisingId;
	}

	//----------------------------------------------------------------//
	public static void init ( String gameID, boolean debug, boolean test ) {

		MoaiLog.i ( " MoaiUnityAds: init with gameID" );

		UnityAds.init (( Activity ) sActivity, gameID, new IUnityAdsListener () {

			//================================================================//
			// MoaiUnityAds callback methods
			//================================================================//

			public void onHide () {

				synchronized ( Moai.sAkuLock ) {
					MoaiUnityAds.AKUInvokeListener ( ListenerEvent.ON_HIDE.ordinal ());
				}
			}

			public void onShow () {

				synchronized ( Moai.sAkuLock ) {
					MoaiUnityAds.AKUInvokeListener ( ListenerEvent.ON_SHOW.ordinal ());
				}
			}

			public void onVideoStarted () {

				synchronized ( Moai.sAkuLock ) {
					
					MoaiLog.i ( " MoaiUnityAds: onShow" );

					MoaiUnityAds.AKUInvokeListener ( ListenerEvent.VIDEO_STARTED.ordinal ());
				}
			}

			public void onVideoCompleted ( String rewardItemKey, boolean skipped ) {

				synchronized ( Moai.sAkuLock ) {
					
					MoaiLog.i ( " MoaiUnityAds: onVideoCompleted: skipped" );
					MoaiUnityAds.AKUVideoCompleted ( rewardItemKey, skipped );
				}
			}

			public void onFetchCompleted () {}

			public void onFetchFailed () {}
		});

		// Setting up debug mode with verbose print
		if ( debug ) {
			UnityAds.setDebugMode ( true );
		}
		if ( test ) {
			UnityAds.setTestMode ( true );
		}
	}
	
	//----------------------------------------------------------------//
	public static boolean show ( String zone ) {

		MoaiLog.i ( "MoaiUnityAds show" );
		MoaiLog.i ( zone );
		if ( zone != null ) {

			try {
				UnityAds.setZone ( zone );
			} catch ( Exception e ) {
				e.printStackTrace ();
				return false;
			}
		}
		if ( UnityAds.canShow ()) {
			return UnityAds.show ();
		}
		return false;
	}
}
