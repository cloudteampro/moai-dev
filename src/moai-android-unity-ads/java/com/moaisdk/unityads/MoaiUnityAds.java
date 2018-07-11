//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved. 
// http://cloudteam.pro
//----------------------------------------------------------------//

package com.moaisdk.unityads;

import android.app.Activity;

import com.moaisdk.core.*;

import com.unity3d.ads.IUnityAdsListener;
import com.unity3d.ads.UnityAds;

//================================================================//
// MoaiUnityAds
//================================================================//
public class MoaiUnityAds {

	public enum ListenerEvent {
		UNITYADS_READY,
		UNITYADS_START,
		UNITYADS_FINISH,
		UNITYADS_ERROR,
    }

	private static Activity 		sActivity 		= null;
	private static UnityAdsListener sAdsListener 	= null;
	
	protected static native void AKUInvokeListener 	( int eventID );
	protected static native void AKUVideoCompleted 	( int result );
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		
		MoaiLog.i ( " MoaiUnityAds onCreate: " );
		
		sActivity = activity;
	}
	
	//================================================================//
	// MoaiUnityAds JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static boolean canShow ( String zone ) {

		if ( zone != null ) {
			return UnityAds.isReady ( zone );
		} else {
			return UnityAds.isReady ();
		}
	}

	//----------------------------------------------------------------//
	public static void init ( String gameID, boolean debug, boolean test ) {

		MoaiLog.i ( " MoaiUnityAds: initialize with gameID" );

		UnityAdsListener unityAdsListener = new UnityAdsListener();

		UnityAds.initialize (( Activity ) sActivity, gameID, unityAdsListener, test );

		sAdsListener = unityAdsListener;

		// Setting up debug mode with verbose print
		if ( debug ) {
			UnityAds.setDebugMode ( true );
		}
		// if ( test ) {
		// 	UnityAds.setTestMode ( true );
		// }
	}
	
	//----------------------------------------------------------------//
	public static boolean show ( String zone ) {

		MoaiLog.i ( "MoaiUnityAds show" + zone );

		if ( zone != null ) {

			if ( UnityAds.isReady ( zone )) {
				UnityAds.show (( Activity ) sActivity, zone );
				return true;
			}
			return false;
		} else {

			if ( UnityAds.isReady ()) {
				UnityAds.show (( Activity ) sActivity );
				return true;
			}
			return false;
		}
	}

	//----------------------------------------------------------------//
	private static class UnityAdsListener implements IUnityAdsListener {
		//================================================================//
		// MoaiUnityAds callback methods
		//================================================================//

		@Override
		public void onUnityAdsReady(final String zoneId) {

			synchronized ( Moai.sAkuLock ) {

				MoaiLog.i ( " MoaiUnityAds: onVideoReady" + zoneId );
				MoaiUnityAds.AKUInvokeListener ( ListenerEvent.UNITYADS_READY.ordinal ());
			}
		}

		@Override
		public void onUnityAdsStart(String zoneId) {

			synchronized ( Moai.sAkuLock ) {
				
				MoaiLog.i ( " MoaiUnityAds: onVideoStart" + zoneId );
				MoaiUnityAds.AKUInvokeListener ( ListenerEvent.UNITYADS_START.ordinal ());
			}
		}

		@Override
		public void onUnityAdsFinish(String zoneId, UnityAds.FinishState result) {

			synchronized ( Moai.sAkuLock ) {
				
				MoaiLog.i ( " MoaiUnityAds: onVideoFinish" + zoneId );
				MoaiUnityAds.AKUVideoCompleted ( result.ordinal ());
			}
		}

		@Override
		public void onUnityAdsError(UnityAds.UnityAdsError error, String message) {
			synchronized ( Moai.sAkuLock ) {
				MoaiLog.i ( " MoaiUnityAds: onVideoError" );
				MoaiUnityAds.AKUInvokeListener ( ListenerEvent.UNITYADS_ERROR.ordinal ());
			}
		}
	}
}
