//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.yandexappmetrica;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;

import com.yandex.metrica.Revenue;
import com.yandex.metrica.YandexMetrica;
import com.yandex.metrica.YandexMetricaConfig;

import java.util.Currency;

@SuppressWarnings("unused")

//================================================================//
// MoaiYandexAppMetrica
//================================================================//
public class MoaiYandexAppMetrica {

	private static Activity sActivity = null;

	//----------------------------------------------------------------//
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiYandexAppMetrica onCreate: Initializing AppMetrica" );

		sActivity = activity;
	}

	//----------------------------------------------------------------//
	public static void onPause () {
 
		MoaiLog.i ( "MoaiYandexAppMetrica: onPause" );

        YandexMetrica.pauseSession ( sActivity );
	}

	//----------------------------------------------------------------//
	public static void onResume () {
 
		MoaiLog.i ( "MoaiYandexAppMetrica: onResume" );

        YandexMetrica.resumeSession ( sActivity );
	}

	//================================================================//
	// YandexAppMetrica JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init ( String apiKey ) {
		
		MoaiLog.i ( "MoaiYandexAppMetrica: init" );

		YandexMetricaConfig config = YandexMetricaConfig.newConfigBuilder ( apiKey ).withLogs ().build ();
		YandexMetrica.activate ( sActivity.getApplicationContext (), config );
	}

	//----------------------------------------------------------------//
	public static void trackEvent () {
		
		MoaiLog.i ( "MoaiYandexAppMetrica: trackEvent" );
	}

	//----------------------------------------------------------------//
	public static void trackLevelAchieved ( int level ) {
		
		MoaiLog.i ( "MoaiYandexAppMetrica: trackLevelAchieved "+level );

		String eventParameters = "{\"level\":\"" + level + "\" }";

		YandexMetrica.reportEvent("Level Achieved", eventParameters);
	}

	//----------------------------------------------------------------//
	public static void trackPurchase ( float price, String currency ) {
		
		MoaiLog.i ( "MoaiYandexAppMetrica: trackPurchase price: " + price + " currency: "+currency );

		YandexMetrica.reportRevenue ( Revenue.newBuilder ( price, Currency.getInstance ( currency ) ).build () );

		String eventParameters ="{\"value\":\""+ price +"\", \"currency\":\""+currency+"\"}";

		YandexMetrica.reportEvent("Purchase", eventParameters);
	}
}
