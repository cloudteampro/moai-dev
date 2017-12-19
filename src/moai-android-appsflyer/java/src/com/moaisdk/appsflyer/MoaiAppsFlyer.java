//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.appsflyer;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.os.Bundle;

import com.appsflyer.*;

import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")


//================================================================//
// MoaiAppsFlyer
//================================================================//
public class MoaiAppsFlyer {

	private static Activity sActivity = null;

	//----------------------------------------------------------------//
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiAppsFlyer onCreate: Initializing AppsFlyer" );

		sActivity = activity;
	}

	//================================================================//
	// AppsFlyer JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init ( String devKey ) {
		
		MoaiLog.i ( "MoaiAppsFlyer: init" );

		AppsFlyerLib.getInstance ().startTracking ( ( Activity )sActivity.getApplication (), devKey );

		AppsFlyerLib.getInstance().registerConversionListener( ( Activity )sActivity, new AppsFlyerConversionListener() {
            @Override
            public void onInstallConversionDataLoaded(Map<String, String> conversionData) {
            //     for (String attrName : conversionData.keySet()) {
            //         Log.d(AppsFlyerLib.LOG_TAG, "attribute: " + attrName + " = " +
            //                 conversionData.get(attrName));
            //     }
            //     //SCREEN VALUES//
            //     final String install_type = "Install Type: " + conversionData.get("af_status");
            //     final String media_source = "Media Source: " + conversionData.get("media_source");
            //     final String install_time = "Install Time(GMT): " + conversionData.get("install_time");
            //     final String click_time = "Click Time(GMT): " + conversionData.get("click_time");
            //     runOnUiThread(new Runnable() {
            //         public void run() {
            //              ((TextView) findViewById(R.id.logView)).setText(install_type + "\n" + media_source + "\n" + click_time + "\n" + install_time);
            //         }


            //     });

            }

            @Override
            public void onInstallConversionFailure(String errorMessage) {
            //     Log.d(AppsFlyerLib.LOG_TAG, "error getting conversion data: " + errorMessage);
            //     ((TextView) findViewById(R.id.logView)).setText(errorMessage);
            }

            @Override
            public void onAppOpenAttribution(Map<String, String> conversionData) {
            }

            @Override
            public void onAttributionFailure(String errorMessage) {
            //     Log.d(AppsFlyerLib.LOG_TAG, "error onAttributionFailure : " + errorMessage);
            }
        });
	}

	//----------------------------------------------------------------//
	public static void trackEvent () {
		
		MoaiLog.i ( "MoaiAppsFlyer: trackEvent" );
	}

	//----------------------------------------------------------------//
	public static void trackLevelAchieved ( int level ) {
		
		MoaiLog.i ( "MoaiAppsFlyer: trackLevelAchieved" );

		Map<String, Object> eventValue = new HashMap<String, Object>();
		eventValue.put ( AFInAppEventParameterName.LEVEL, level );
		AppsFlyerLib.getInstance().trackEvent( ( Activity )sActivity.getApplicationContext(), AFInAppEventType.LEVEL_ACHIEVED, eventValue);
	}

	//----------------------------------------------------------------//
	public static void trackPurchase ( float revenue, String currency ) {
		
		MoaiLog.i ( "MoaiAppsFlyer: trackPurchase" );

		Map<String, Object> eventValue = new HashMap<String, Object>();
        eventValue.put ( AFInAppEventParameterName.REVENUE, revenue );
        eventValue.put ( AFInAppEventParameterName.CURRENCY, currency );
        AppsFlyerLib.getInstance().trackEvent( ( Activity )sActivity.getApplicationContext(), AFInAppEventType.PURCHASE, eventValue);
	}
}
