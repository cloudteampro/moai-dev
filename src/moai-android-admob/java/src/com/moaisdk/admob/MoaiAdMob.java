//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.admob;

import android.app.Activity;

import com.moaisdk.core.*;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.reward.RewardItem;
import com.google.android.gms.ads.reward.RewardedVideoAd;
import com.google.android.gms.ads.reward.RewardedVideoAdListener;

//================================================================//
// MoaiAdMob
//================================================================//

public class MoaiAdMob implements RewardedVideoAdListener {

	public enum ListenerEvent {
		ADMOB_READY,
		ADMOB_START,
		ADMOB_FINISH,
		ADMOB_ERROR,
		ADMOB_CLOSED,
    }

	private static Activity sActivity = null;
    private static RewardedVideoAd rewardedVideoAd = null;
	private static MoaiAdMob sAdsListener = null;

	private static boolean destroyed = false;

	protected static native void AKUInvokeListener ( int eventID );
	protected static native void AKUVideoCompleted ( int result );

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiAdMob: onCreate" );

		sActivity = activity;
	}

	//----------------------------------------------------------------//
	public static void onPause ( ) {

		MoaiLog.i ( "MoaiAdMob: onPause" );

		if ( rewardedVideoAd != null ) {
		
			rewardedVideoAd.pause ( sActivity );
		}
	}

	//----------------------------------------------------------------//
	public static void onResume ( ) {

		MoaiLog.i ( "MoaiAdMob: onResume" );

		if ( rewardedVideoAd != null ) {
		
			rewardedVideoAd.resume ( sActivity );
		}
	}

	//----------------------------------------------------------------//
	public static void onStop () {

		MoaiLog.i ( "MoaiAdMob: onStop" );
	}

	//----------------------------------------------------------------//
    public static void onDestroy() {

		MoaiLog.i ( "MoaiAdMob: onDestroy" );

		if ( rewardedVideoAd != null ) {
		
	    	rewardedVideoAd.destroy ( sActivity );
	        rewardedVideoAd.setRewardedVideoAdListener ( null );
	    }

		destroyed = true;
    }

	//================================================================//
	// MoaiAdMob JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static boolean show () {

        MoaiLog.i ( "MoaiAdMob show : isLoaded " + rewardedVideoAd.isLoaded () );

        if ( rewardedVideoAd.isLoaded ()) {

		    rewardedVideoAd.show ();
			return true;
		}

		return false;
	}

	//----------------------------------------------------------------//
	public static void init ( String appId ) {

        MoaiLog.i ( "MoaiAdMob init" );

		sAdsListener = new MoaiAdMob ();

		MobileAds.initialize ( sActivity, appId );

		rewardedVideoAd = MobileAds.getRewardedVideoAdInstance ( sActivity );
        rewardedVideoAd.setRewardedVideoAdListener ( sAdsListener );
	}

	//----------------------------------------------------------------//
	public static boolean isLoaded () {
		
        // MoaiLog.i ( "MoaiAdMob isLoaded "+rewardedVideoAd.isLoaded () );

		return rewardedVideoAd.isLoaded ();
	}

	//----------------------------------------------------------------//
	public static void loadAd ( String unitId ) {

        MoaiLog.i ( "MoaiAdMob loadAd unitId - "+unitId+" isLoaded "+rewardedVideoAd.isLoaded() );

        if ( !rewardedVideoAd.isLoaded() ) {

    		rewardedVideoAd.loadAd ( unitId, new AdRequest.Builder ().build ());
    	}
	}

	//================================================================//
	// VunglePub.EventListener
	//================================================================//

	//----------------------------------------------------------------//
	public void onRewarded ( RewardItem reward ) {

		if ( destroyed ) return;
		
		synchronized ( Moai.sAkuLock ) {
			
	 		MoaiLog.i ( "MoaiAdMob: onRewarded currency: " + reward.getType () + "  amount: " + reward.getAmount ());
			MoaiAdMob.AKUVideoCompleted ( 1 );
		}
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoAdLeftApplication () {
		
		if ( destroyed ) return;
		
	    MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdLeftApplication" );
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoAdClosed () {

		if ( destroyed ) return;
		
	    MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdClosed" );
		MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_CLOSED.ordinal ());
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoAdFailedToLoad ( int errorCode ) {

		if ( destroyed ) return;
		
		synchronized ( Moai.sAkuLock ) {

	    	MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdFailedToLoad errorCode - "+errorCode );
			MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_ERROR.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoAdLoaded () {

		if ( destroyed ) return;
		
		synchronized ( Moai.sAkuLock ) {

	    	MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdLoaded" );
			MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_READY.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoAdOpened () {
		
		if ( destroyed ) return;
		
	    MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdOpened" );
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoStarted () {

		if ( destroyed ) return;
		
		synchronized ( Moai.sAkuLock ) {
			
	    	MoaiLog.i ( "MoaiAdMob: onRewardedVideoStarted" );
			MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_START.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoCompleted () {

		if ( destroyed ) return;

		MoaiLog.i ( "MoaiAdMob: onRewardedVideoCompleted" );
	}

}

