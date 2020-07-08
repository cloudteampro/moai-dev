//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.admob;

import android.app.Activity;
import android.os.Bundle;

import androidx.annotation.NonNull;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.RequestConfiguration;
import com.google.android.gms.ads.rewarded.RewardItem;
import com.google.android.gms.ads.rewarded.RewardedAdCallback;
import com.google.android.gms.ads.rewarded.RewardedAdLoadCallback;
import com.ironsource.mediationsdk.integration.IntegrationHelper;
import com.moaisdk.core.*;

import com.ironsource.mediationsdk.*;

import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.MobileAds;
//import com.google.android.gms.ads.reward.RewardItem;
import com.google.android.gms.ads.rewarded.RewardedAd;
//import com.google.android.gms.ads.reward.RewardedVideoAd;
//import com.google.android.gms.ads.reward.RewardedVideoAdListener;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

//================================================================//
// MoaiAdMob
//================================================================//

public class MoaiAdMob {//} implements RewardedVideoAdListener {

	public enum ListenerEvent {
		ADMOB_READY,
		ADMOB_OPENED,
		ADMOB_ERROR,
		ADMOB_CLOSED,
		ADMOB_REWARDED_READY,
		ADMOB_REWARDED_START,
		ADMOB_REWARDED_FINISH,
		ADMOB_REWARDED_ERROR,
		ADMOB_REWARDED_CLOSED,
    }

	private static Activity sActivity = null;
	private static InterstitialAd interstitialAd = null;
	private static Bundle sPlacements = null;
    //private static RewardedVideoAd rewardedVideoAd = null;
	private static MoaiAdMob sRewardedAdsListener = null;
	private static HashMap<String, RewardedAd> rewardedAds = null;
	private static AdListener sAdsListener = null;

	private static boolean destroyed = false;

	protected static native void AKUInvokeListener ( int eventID );
	protected static native void AKUVideoCompleted ( int result );
	protected static native void AKUVideoClosed ( String placementName );

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiAdMob: onCreate" );

		sActivity = activity;
	}

	//----------------------------------------------------------------//
	public static void onPause ( ) {

		MoaiLog.i ( "MoaiAdMob: onPause" );

		IronSource.onPause ( sActivity );

//		if ( rewardedVideoAd != null ) {
//
//			rewardedVideoAd.pause ( sActivity );
//		}
	}

	//----------------------------------------------------------------//
	public static void onResume ( ) {

		MoaiLog.i ( "MoaiAdMob: onResume" );

		IronSource.onResume ( sActivity );

//		if ( rewardedVideoAd != null ) {
//
//			rewardedVideoAd.resume ( sActivity );
//		}
	}

	//----------------------------------------------------------------//
	public static void onStop () {

		MoaiLog.i ( "MoaiAdMob: onStop" );
	}

	//----------------------------------------------------------------//
    public static void onDestroy() {

		MoaiLog.i ( "MoaiAdMob: onDestroy" );

//		if ( rewardedVideoAd != null ) {
//
//	    	rewardedVideoAd.destroy ( sActivity );
//	        rewardedVideoAd.setRewardedVideoAdListener ( null );
//	        rewardedVideoAd = null;
//	    }

	    if ( interstitialAd != null ) {
			interstitialAd.setAdListener ( null );
			interstitialAd = null;
		}

		destroyed = true;
    }

	//================================================================//
	// MoaiAdMob JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static boolean show ( final String placementName ) {

		for ( String key : rewardedAds.keySet() ) {
			if (key.equals(placementName)) {
				MoaiLog.i ( "MoaiAdMob show : " + placementName + " isLoaded " + rewardedAds.get(key).isLoaded() );
				if (rewardedAds.get(key).isLoaded()) {
					RewardedAdCallback adCallback = new RewardedAdCallback() {
						@Override
						public void onRewardedAdOpened() {
							// Ad opened.
							if ( destroyed ) return;

							synchronized ( Moai.sAkuLock ) {

								MoaiLog.i ( "MoaiAdMob: onRewardedAdOpened" );
								MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_START.ordinal ());
							}
						}

						@Override
						public void onRewardedAdClosed() {
							// Ad closed.
							if ( destroyed ) return;

							synchronized ( Moai.sAkuLock ) {

								MoaiLog.i ( "MoaiAdMob: onRewardedAdClosed" );
								//MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_CLOSED.ordinal () );
								MoaiAdMob.AKUVideoClosed ( placementName );
							}
						}

						@Override
						public void onUserEarnedReward(@NonNull RewardItem reward) {
							// User earned reward.

							if ( destroyed ) return;

							synchronized ( Moai.sAkuLock ) {

								MoaiLog.i ( "MoaiAdMob: onUserEarnedReward currency: " + reward.getType () + "  amount: " + reward.getAmount ());
								MoaiAdMob.AKUVideoCompleted ( 1 );
							}
						}

						@Override
						public void onRewardedAdFailedToShow(int errorCode) {
							// Ad failed to display.

							if ( destroyed ) return;

							synchronized ( Moai.sAkuLock ) {

								MoaiLog.i ( "MoaiAdMob: onRewardedAdFailedToShow errorCode - "+errorCode );
								MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_ERROR.ordinal ());
							}
						}
					};
					rewardedAds.get(key).show(sActivity, adCallback);
					return true;
				}
			}
		}

//        MoaiLog.i ( "MoaiAdMob show : " + placementName + " isLoaded " + rewardedVideoAd.isLoaded () );
//
//        if ( rewardedVideoAd.isLoaded ()) {
//
//		    rewardedVideoAd.show ();
//			return true;
//		}

		return false;
	}

	//----------------------------------------------------------------//
	public static boolean showInterstitial () {

		MoaiLog.i ( "MoaiAdMob show : isInterstitialLoaded " + interstitialAd.isLoaded () );

		if ( interstitialAd.isLoaded ()) {

			interstitialAd.show ();
			return true;
		}

		return false;
	}

	//----------------------------------------------------------------//
	public static void init ( String appId, Bundle placements ) {

        MoaiLog.i ( "MoaiAdMob init" );

		sRewardedAdsListener = new MoaiAdMob ();
		sAdsListener = new AdMobAdListener ();
		sPlacements = placements;
		rewardedAds = new HashMap<String, RewardedAd>();
		Set<String> keys = placements.keySet();
		for(String key : keys) {
			rewardedAds.put(key, new RewardedAd(sActivity, placements.getString(key)));
		}

		MobileAds.initialize ( sActivity, appId );

//		List<String> testDeviceIds = Arrays.asList("AEABDDF5281389889CD2726746CF73B3");
//		RequestConfiguration configuration = new RequestConfiguration.Builder().setTestDeviceIds(testDeviceIds).build();
//		MobileAds.setRequestConfiguration(configuration);

		//rewardedVideoAd = MobileAds.getRewardedVideoAdInstance ( sActivity );
        //rewardedVideoAd.setRewardedVideoAdListener ( sRewardedAdsListener );

		interstitialAd = new InterstitialAd ( sActivity );
		interstitialAd.setAdListener ( sAdsListener );

		//IntegrationHelper.validateIntegration(sActivity);
	}

	//----------------------------------------------------------------//
	public static boolean isLoaded ( String placementName ) {
		
        // MoaiLog.i ( "MoaiAdMob isLoaded "+rewardedVideoAd.isLoaded () );

		//MoaiLog.i ("-------------------------------");
		//for ( Map.Entry<String, AdapterStatus> entry : MobileAds.getInitializationStatus ().getAdapterStatusMap ().entrySet () ) {
		//	MoaiLog.i (entry.getKey ()+"----"+entry.getValue ().getInitializationState ());
		//}

		for ( String key : rewardedAds.keySet() ) {
			if (key.equals(placementName)) {
				//MoaiLog.i ( "MoaiAdMob isLoaded " + placementName + " " +rewardedAds.get(key).isLoaded () );
				return rewardedAds.get(key).isLoaded();
			}
		}

		//return rewardedVideoAd.isLoaded ();
		return false;
	}

	//----------------------------------------------------------------//
	public static boolean isInterstitialLoaded () {

		// MoaiLog.i ( "MoaiAdMob isInterstitialLoaded "+rewardedVideoAd.isLoaded () );

		return interstitialAd.isLoaded ();
	}

	//----------------------------------------------------------------//
	public static void loadAd ( String placementName ) {

		for ( String key : rewardedAds.keySet() ) {
			if (key.equals(placementName)) {
				RewardedAd rewardedAd = new RewardedAd(sActivity, sPlacements.getString(key));

				rewardedAds.put(key, rewardedAd);

				RewardedAdLoadCallback adLoadCallback = new RewardedAdLoadCallback() {
					@Override
					public void onRewardedAdLoaded() {
						// Ad successfully loaded.
						if ( destroyed ) return;

						synchronized ( Moai.sAkuLock ) {

							MoaiLog.i ( "MoaiAdMob: onRewardedAdLoaded" );
							MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_READY.ordinal ());
						}
					}

					@Override
					public void onRewardedAdFailedToLoad(int errorCode) {
						// Ad failed to load.

						if ( destroyed ) return;

						synchronized ( Moai.sAkuLock ) {

							MoaiLog.i ( "MoaiAdMob: onRewardedAdFailedToLoad errorCode - "+errorCode );
							MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_ERROR.ordinal ());
						}
					}
				};
				rewardedAd.loadAd(new AdRequest.Builder().build(), adLoadCallback);
			}
		}

//        MoaiLog.i ( "MoaiAdMob loadAd unitId - "+placementName+" isLoaded "+rewardedVideoAd.isLoaded() );
//
//        if ( !rewardedVideoAd.isLoaded() ) {
//
//    		rewardedVideoAd.loadAd ( unitId, new AdRequest.Builder ().build ());
//    	}
	}

	//----------------------------------------------------------------//
	public static void loadInterstitial ( String unitId ) {

		MoaiLog.i ( "MoaiAdMob loadInterstitial unitId - "+unitId+" isLoaded "+interstitialAd.isLoaded() );

		interstitialAd.setAdUnitId ( unitId );
		interstitialAd.loadAd ( new AdRequest.Builder ().build () );
	}

	//================================================================//
	// AdMob.EventListener
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

		synchronized ( Moai.sAkuLock ) {

			MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdClosed" );
			MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_CLOSED.ordinal () );
		}
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoAdFailedToLoad ( int errorCode ) {

		if ( destroyed ) return;
		
		synchronized ( Moai.sAkuLock ) {

	    	MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdFailedToLoad errorCode - "+errorCode );
			MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_ERROR.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoAdLoaded () {

		if ( destroyed ) return;
		
		synchronized ( Moai.sAkuLock ) {

	    	MoaiLog.i ( "MoaiAdMob: onRewardedVideoAdLoaded" );
			MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_READY.ordinal ());
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
			MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_REWARDED_START.ordinal ());
		}
	}

	//----------------------------------------------------------------//
	public void onRewardedVideoCompleted () {

		if ( destroyed ) return;

		MoaiLog.i ( "MoaiAdMob: onRewardedVideoCompleted" );
	}

	//----------------------------------------------------------------//
	private static class AdMobAdListener extends AdListener {

		//================================================================//
		// MoaiAdMob callback methods
		//================================================================//

		//----------------------------------------------------------------//
		public void onAdLoaded() {

			if ( destroyed ) return;

			synchronized ( Moai.sAkuLock ) {

				MoaiLog.i ( "MoaiAdMob: onAdLoaded" );
				MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_READY.ordinal ());
			}
		}

		//----------------------------------------------------------------//
		public void onAdFailedToLoad(int errorCode) {

			if ( destroyed ) return;

			synchronized ( Moai.sAkuLock ) {

				MoaiLog.i ( "MoaiAdMob: onAdFailedToLoad errorCode - "+errorCode );
				MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_ERROR.ordinal ());
			}
		}

		//----------------------------------------------------------------//
		public void onAdOpened() {

			if ( destroyed ) return;

			synchronized ( Moai.sAkuLock ) {

				MoaiLog.i ( "MoaiAdMob: onAdOpened" );
				MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_OPENED.ordinal ());
			}
		}

		//----------------------------------------------------------------//
		public void onAdClicked() {

			if ( destroyed ) return;

			MoaiLog.i ( "MoaiAdMob: onAdClicked" );
		}

		//----------------------------------------------------------------//
		public void onAdLeftApplication() {

			if ( destroyed ) return;

			MoaiLog.i ( "MoaiAdMob: onAdLeftApplication" );
		}

		//----------------------------------------------------------------//
		public void onAdClosed() {

			if ( destroyed ) return;

			synchronized ( Moai.sAkuLock ) {
				MoaiLog.i ( "MoaiAdMob: onAdClosed" );
				MoaiAdMob.AKUInvokeListener ( ListenerEvent.ADMOB_CLOSED.ordinal () );
			}
		}
	}
}

