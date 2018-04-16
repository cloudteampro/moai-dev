//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.fyber;

import com.moaisdk.core.*;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;

import com.fyber.Fyber;
import com.fyber.ads.AdFormat;
import com.fyber.requesters.RequestCallback;
import com.fyber.requesters.RequestError;
import com.fyber.requesters.RewardedVideoRequester;
import com.fyber.ads.videos.RewardedVideoActivity;

import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")

//================================================================//
// MoaiFyber
//================================================================//
public class MoaiFyber {

	public enum ListenerEvent {
		REWARDED_VIDEO_START,
		REWARDED_VIDEO_COMPLETED,
		REWARDED_VIDEO_ABORTED,
		REWARDED_VIDEO_ERROR,
    }

	private static Activity sActivity = null;
	private static RequestCallback sCallback = null;
	private static Intent sRewardVideoIntent = null;
	private static boolean sIsRequestingState = false;

	private static String sAppId = null;
	private static String sUserId = null;
	private static String sSecurityToken = null;

	protected static native void AKUInvokeListener 	( int eventID );

	protected static final int REWARDED_VIDEO_REQUEST_CODE = 5678;

	//----------------------------------------------------------------//
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiFyber onCreate: Initializing Fyber" );

		sActivity = activity;
	}

	public static void onResume () {

		startFyber ();
	}

	//================================================================//
	// Fyber JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void startFyber () {

		if (sAppId != null && sUserId != null && sSecurityToken != null ) {

			try {

				// ** SDK INITIALIZATION **
				Fyber.Settings settings = Fyber.with(sAppId, sActivity).withUserId(sUserId).withSecurityToken(sSecurityToken).start();
		        settings.notifyUserOnCompletion(false).notifyUserOnReward(true).closeOfferWallOnRedirect(true);

			} catch (IllegalArgumentException e) {
			}
			
		}
	}

	//----------------------------------------------------------------//
	public static void init ( String appId, String userId, String securityToken ) {
		
		MoaiLog.i ( "MoaiFyber: init" );

		sAppId = appId;
		sUserId = userId;
		sSecurityToken = securityToken;

		startFyber ();

		RequestCallback requestCallback = new RequestCallback() {
			@Override
			public void onAdAvailable(Intent intent) {
				MoaiLog.i ( "MoaiFyber: Offers are available");

			    sRewardVideoIntent = intent;
			    resetRequestingState ();

			    MoaiFyber.AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_START.ordinal ());

			    // sActivity.startActivityForResult(sRewardVideoIntent, REWARDED_VIDEO_REQUEST_CODE);
			}

			@Override
			public void onAdNotAvailable(AdFormat adFormat) {
				MoaiLog.i ( "MoaiFyber: No ad available");

			    resetRequestingState ();
			    resetIntent ();

			    MoaiFyber.AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_ERROR.ordinal ());
			}

			@Override
			public void onRequestError(RequestError requestError) {
				MoaiLog.i ( "MoaiFyber: Something went wrong with the request: " + requestError.getDescription());
			    resetRequestingState ();
			    resetIntent ();

			    MoaiFyber.AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_ERROR.ordinal ());
			}
		};

		sCallback = requestCallback;
	}

	//----------------------------------------------------------------//
	public static void onActivityResult ( int requestCode, int resultCode, Intent data ) {

		resetIntent ();

		if (resultCode == sActivity.RESULT_OK && requestCode == REWARDED_VIDEO_REQUEST_CODE) {

			String engagementResult = data.getStringExtra(RewardedVideoActivity.ENGAGEMENT_STATUS);
			switch (engagementResult) {

				case RewardedVideoActivity.REQUEST_STATUS_PARAMETER_FINISHED_VALUE:
					
					MoaiLog.i ( "The video ad was dismissed because the user completed it"); // The user watched the entire video and will be rewarded
					MoaiFyber.AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_COMPLETED.ordinal ());
					break;

				case RewardedVideoActivity.REQUEST_STATUS_PARAMETER_ABORTED_VALUE:
					
					MoaiLog.i ( "The video ad was dismissed because the user explicitly closed it"); // The user stopped the video early and will not be rewarded
					MoaiFyber.AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_ABORTED.ordinal ());
					break;

				case RewardedVideoActivity.REQUEST_STATUS_PARAMETER_ERROR:
					
					MoaiLog.i ( "The video ad was dismissed error during playing"); // An error occurred while showing the video and the user will not be rewarded
					MoaiFyber.AKUInvokeListener ( ListenerEvent.REWARDED_VIDEO_ERROR.ordinal ());
					break;
			}
		}
	}

	//----------------------------------------------------------------//
	public static void requestVideo () {

		MoaiLog.i ( "MoaiFyber: requestVideo" );

		if (!isRequestingState ()) {

			if (isIntentAvailable ()) {

				sActivity.startActivityForResult ( sRewardVideoIntent, REWARDED_VIDEO_REQUEST_CODE );
			}
			else {

				sIsRequestingState = true;
				performRequest ();
			}
		}
	}

	private static void performRequest () {

		RewardedVideoRequester.create( sCallback ).request( sActivity );
	}

	private static void resetRequestingState () {
		sIsRequestingState = false;
	}

	private static boolean isRequestingState () {
		return sIsRequestingState;
	}

	private static void resetIntent () {
		sRewardVideoIntent = null;
	}

	private static boolean isIntentAvailable () {
		return sRewardVideoIntent != null;
	}
	
}
