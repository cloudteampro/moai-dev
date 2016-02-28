//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.crashlytics;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;

import io.fabric.sdk.android.Fabric;
import com.crashlytics.android.Crashlytics;
import com.crashlytics.android.ndk.CrashlyticsNdk;

@SuppressWarnings("unused")

//================================================================//
// MoaiCrashlytics
//================================================================//
public class MoaiCrashlytics {

	private static Activity sActivity = null;

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiCrashlytics onCreate: Initializing Crashlytics" );

		sActivity = activity;
	}

	//================================================================//
	// Crashlytics JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init () {

		Fabric.with ( sActivity, new Crashlytics (), new CrashlyticsNdk ());
	}

	//----------------------------------------------------------------//
	public static void reportTraceback ( String error, Bundle [] stackFrames ) {

		StackTraceElement [] frames = new StackTraceElement [ stackFrames.length ];

		for ( int i = 0; i < stackFrames.length; i++ ) {
			
			Bundle frame = stackFrames [ i ];

			String file = frame.getString ( "file" );
			String func = frame.getString ( "func" );
			int line = frame.getInt ( "line" );

			// Using filename as class name
			StackTraceElement element = StackTraceElement ( file, func, file, line );
			frames [ i ] = element;
		}
		
		Exception luaCrash = new Exception ( error );
		luaCrash.setStackTrace ( frames );
		Crashlytics.logException ( luaCrash );
	}
}
