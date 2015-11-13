//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved. 
// http://cloudteam.pro
//----------------------------------------------------------------//

package com.ziplinegames.moai;

import android.app.Activity;
import android.widget.FrameLayout;

import com.flurry.android.FlurryAdListener;
import com.flurry.android.FlurryAdSize;
import com.flurry.android.FlurryAdType;
import com.flurry.android.FlurryAds;

//================================================================//
// MoaiFlurryAds
//================================================================//
public class MoaiFlurryAds {

	public enum ListenerEvent {
		AD_LOAD_FAILED,
		AD_WILL_SHOW,
		AD_DISMISSED,
    }

	private static Activity 		sActivity 		= null;
	private static FrameLayout 		adLayout 		= null;
	private static String 			adSpace 		= "Takeover";
	
	protected static native void AKUInvokeListener ( int eventID );
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		
		MoaiLog.i ( " MoaiFlurryAds onCreate " );
		
		sActivity = activity;
	}

	//----------------------------------------------------------------//
	public static void onStart () {
		
		MoaiLog.i ( " MoaiFlurryAds onStart " );
		
		FlurryAds.setAdListener ( new FlurryAdListener () {

			public void onAdClicked ( String adSpace ) { }

			public void onAdClosed ( String adSpace ) {
				
				synchronized ( Moai.sAkuLock ) {
					
					MoaiLog.i ( " MoaiFlurryAds: Ad closed; space = "+adSpace );
					
					MoaiFlurryAds.AKUInvokeListener ( ListenerEvent.AD_DISMISSED.ordinal ());
				}
			}

			public void onAdOpened ( String adSpace ) { }

			public void onApplicationExit ( String adSpace ) { }

			public void onRenderFailed ( String adSpace ) { }

			public void onRendered ( String adSpace ) {

				synchronized ( Moai.sAkuLock ) {
					
					MoaiLog.i ( " MoaiFlurryAds: onRendered: space = "+adSpace );
					
					MoaiFlurryAds.AKUInvokeListener ( ListenerEvent.AD_WILL_SHOW.ordinal ());
				}
			}

			public void onVideoCompleted ( String adSpace ) { 
				
				synchronized ( Moai.sAkuLock ) {
					
					MoaiLog.i ( " MoaiFlurryAds: onVideoCompleted: space = "+adSpace );
					
					MoaiFlurryAds.AKUInvokeListener ( ListenerEvent.AD_DISMISSED.ordinal ());
				}
			}

			public boolean shouldDisplayAd ( String adSpace, FlurryAdType adType ) { return true; }

			public void spaceDidFailToReceiveAd ( String adSpace ) { 
				
				synchronized ( Moai.sAkuLock ) {
					
					MoaiLog.i ( " MoaiFlurryAds: spaceDidFailToReceiveAd: space = "+adSpace );
					MoaiFlurryAds.AKUInvokeListener ( ListenerEvent.AD_LOAD_FAILED.ordinal ());
				}
			}

			public void spaceDidReceiveAd ( String adSpace ) { }
		} );
	}

	//----------------------------------------------------------------//
	public static void onStop () {
		
		//MoaiLog.i ( " MoaiFlurryAds onStop: removeAd ( sActivity, adSpace, adLayout ) " );
		
        //FlurryAds.removeAd ( sActivity, adSpace, adLayout );
	}
	
	//================================================================//
	// MoaiFlurryAds JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init ( String difSpace ) {

		MoaiLog.i ( " MoaiFlurryAds: init: space = "+difSpace );
		
		adLayout = new FrameLayout ( sActivity );
		
		if ( difSpace != null ) {

			adSpace = difSpace;
		}
		
		FlurryAds.initializeAds ( sActivity );
	}
	
	//----------------------------------------------------------------//
	public static void loadAd () {
		
		FlurryAds.fetchAd( sActivity, adSpace, adLayout, FlurryAdSize.FULLSCREEN );
	}
	
	//----------------------------------------------------------------//
	public static void showAd () {
		
		FlurryAds.displayAd ( sActivity, adSpace, adLayout );
	}
	
	//----------------------------------------------------------------//
	public static boolean hasCachedAd () {
		
		if ( FlurryAds.isAdReady ( adSpace ) ) {
			
			return true;
		}
		
		return false;
	}
	
	//----------------------------------------------------------------//
	public static void setAdSpace ( String difSpace ) {
		
		adSpace = difSpace;
	}
}
