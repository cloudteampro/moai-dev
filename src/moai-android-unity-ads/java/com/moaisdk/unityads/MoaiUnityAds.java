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

	private static boolean destoyed = false;
	
	protected static native void AKUInvokeListener 	( int eventID );
	protected static native void AKUVideoCompleted 	( int result );
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		
		MoaiLog.i ( " MoaiUnityAds onCreate: " );

		destoyed = false;
		
		sActivity = activity;
	}

	//----------------------------------------------------------------//
	public static void onPause () {
 
		MoaiLog.i ( "MoaiUnityAds: onPause" );
	}

	//----------------------------------------------------------------//
	public static void onResume () {
 
		MoaiLog.i ( "MoaiUnityAds: onResume" );
	}

	//----------------------------------------------------------------//
	public static void onStop () {

		MoaiLog.i ( "MoaiUnityAds: onStop" );
	}

	//----------------------------------------------------------------//
    public static void onDestroy() {
        
		MoaiLog.i ( "MoaiUnityAds: onDestroy" );

		destoyed = true;
    }
	
	//================================================================//
	// MoaiUnityAds JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static boolean canShow ( String zone ) {

		if ( zone != null ) {
			boolean ready = UnityAds.isReady ( zone );

			// MoaiLog.i ( " MoaiUnityAds: canShow for zone: " + zone + " " + ready );
			return ready;
		} else {

			boolean ready = UnityAds.isReady ();

			// MoaiLog.i ( " MoaiUnityAds: canShow " + ready );
			return ready;
		}
	}

	//----------------------------------------------------------------//
	public static void init ( String gameID, boolean debug, boolean test ) {

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
		public void onUnityAdsReady ( final String zoneId ) {

			if ( destoyed ) return;

			synchronized ( Moai.sAkuLock ) {

				MoaiLog.i ( " MoaiUnityAds: onVideoReady for zone: " + zoneId );
				MoaiUnityAds.AKUInvokeListener ( ListenerEvent.UNITYADS_READY.ordinal ());
			}
		}

		@Override
		public void onUnityAdsStart ( String zoneId ) {

			if ( destoyed ) return;

			synchronized ( Moai.sAkuLock ) {
				
				MoaiLog.i ( " MoaiUnityAds: onVideoStart for zone: " + zoneId );
				MoaiUnityAds.AKUInvokeListener ( ListenerEvent.UNITYADS_START.ordinal ());
			}
		}

		@Override
		public void onUnityAdsFinish ( String zoneId, UnityAds.FinishState result ) {
			
			if ( destoyed ) return;

			synchronized ( Moai.sAkuLock ) {
				
				MoaiLog.i ( " MoaiUnityAds: onVideoFinish for zone: " + zoneId );
				MoaiUnityAds.AKUVideoCompleted ( result.ordinal ());
			}
		}

		@Override
		public void onUnityAdsError ( UnityAds.UnityAdsError error, String message ) {

			if ( destoyed ) return;

			synchronized ( Moai.sAkuLock ) {
				
				MoaiLog.i ( " MoaiUnityAds: onVideoError: " + message );
				MoaiUnityAds.AKUInvokeListener ( ListenerEvent.UNITYADS_ERROR.ordinal ());
			}
		}
	}
}


