//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.vungle;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;

import com.vungle.publisher.VungleAdEventListener;
import com.vungle.publisher.VungleInitListener;
import com.vungle.publisher.VunglePub;

//================================================================//
// MoaiVungle
//================================================================//

public class MoaiVungle implements VungleAdEventListener {

	public enum ListenerEvent {
		VUNGLE_INITIALIZED,
		VUNGLE_READY,
		VUNGLE_START,
		VUNGLE_FINISH,
    }

	private static Activity sActivity = null;
    private static VunglePub vunglePub = null;
    private static MoaiVungle vungleListener = null;
    private static boolean isAvailable = false;

	protected static native void AKUInvokeListener ( int eventID );
	protected static native void AKUOnView ( double watched, double length );

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiVungle: onCreate" );

		sActivity = activity;

		vunglePub = VunglePub.getInstance();
		vungleListener = new MoaiVungle ();
	}

	//----------------------------------------------------------------//
	public static void onPause ( ) {

		MoaiLog.i ( "MoaiVungle: onPause" );

		vunglePub.onPause ();
	}

	//----------------------------------------------------------------//
	public static void onResume ( ) {

		MoaiLog.i ( "MoaiVungle: onResume" );

		vunglePub.onResume ();
	}

    public static void onDestroy() {

		MoaiLog.i ( "MoaiVungle: onDestroy" );

        vunglePub.removeEventListeners ( vungleListener );
    }

	//================================================================//
	// MoaiVungle JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static boolean displayAdvert ( String placement ) {

        MoaiLog.i ( "MoaiVungle displayAdvert " + placement );
		
		vunglePub.playAd ( placement, null );
		return isAvailable;
	}

	//----------------------------------------------------------------//
	public static void init ( String appId, String placement ) {

        MoaiLog.i ( "MoaiVungle init" );

        vunglePub.init ( sActivity, appId, new String[] { placement }, new VungleInitListener () {
            @Override
            public void onSuccess () {

                MoaiLog.i ( "MoaiVungle init success" );

                vunglePub.clearAndSetEventListeners ( vungleListener );

				AKUInvokeListener ( ListenerEvent.VUNGLE_INITIALIZED.ordinal ());
            }

            @Override
            public void onFailure ( Throwable error ) {

                MoaiLog.i ( "MoaiVungle init failure: " );
            }
        });
	}

	//----------------------------------------------------------------//
	public static boolean isVideoAvailable ( String placement ) {
		
        MoaiLog.i ( "MoaiVungle isVideoAvailable " + placement );

		return vunglePub.isAdPlayable ( placement );
		//return isAvailable;
	}

	//----------------------------------------------------------------//
	public static void loadVideo ( String placement ) {

        MoaiLog.i ( "MoaiVungle loadVideo " + placement );

		vunglePub.loadAd ( placement );
	}

	//================================================================//
	// VunglePub.EventListener
	//================================================================//

	//----------------------------------------------------------------//
    public void onAdEnd ( String placementReferenceId, boolean wasSuccessfulView, boolean wasCallToActionClicked ) {

		MoaiLog.i ( "MoaiVungle: onAdEnd " + placementReferenceId + " " + wasSuccessfulView + " " + wasCallToActionClicked );
		AKUInvokeListener ( ListenerEvent.VUNGLE_FINISH.ordinal ());
    }

	//----------------------------------------------------------------//
    public void onAdStart ( String placementReferenceId ) {

		MoaiLog.i ( "MoaiVungle: onAdStart " + placementReferenceId );
		AKUInvokeListener ( ListenerEvent.VUNGLE_START.ordinal ());
    }

	//----------------------------------------------------------------//
    public void onUnableToPlayAd ( String placementReferenceId, String reason ) {

		MoaiLog.i ( "MoaiVungle: onUnableToPlayAd " + placementReferenceId + " " + reason ); 
    }

	//----------------------------------------------------------------//
    public void onAdAvailabilityUpdate ( String placementReferenceId, boolean isAdAvailable ) {

		MoaiLog.i ( "MoaiVungle: onAdAvailabilityUpdate " + placementReferenceId + " " + isAdAvailable );

		if ( isAdAvailable ) {

			AKUInvokeListener ( ListenerEvent.VUNGLE_READY.ordinal ());
		}
		isAvailable = isAdAvailable;
    }
}