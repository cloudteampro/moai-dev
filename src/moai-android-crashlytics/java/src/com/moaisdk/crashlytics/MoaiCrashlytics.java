//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.crashlytics;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.os.Bundle;

import java.io.PrintWriter;
import java.io.StringWriter;
import java.lang.StackTraceElement;

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
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

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

			String file = frame.getString ( "file", "?" );
			String func = frame.getString ( "func", "?" );
			int line = frame.getInt ( "line", 0 );

			// class name is just Lua
			StackTraceElement element = new StackTraceElement ( "Lua", func, file, line );
			frames [ i ] = element;
		}
		
		LuaException luaCrash = new LuaException ( error );
		luaCrash.setStackTrace ( frames );
		Crashlytics.logException ( luaCrash );

		StringWriter writer = new StringWriter ();
		luaCrash.printStackTrace ( new PrintWriter ( writer ));
		MoaiLog.i ( writer.toString ());
	}
}
