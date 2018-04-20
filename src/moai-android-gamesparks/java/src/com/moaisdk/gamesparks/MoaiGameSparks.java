//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.gamesparks;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.os.Bundle;

import com.gamesparks.sdk.*;
import com.gamesparks.sdk.api.*;
import com.gamesparks.sdk.api.autogen.*;

import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")

//================================================================//
// MoaiGameSparks
//================================================================//
public class MoaiGameSparks {

	private static Activity sActivity = null;

	//----------------------------------------------------------------//
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

	//----------------------------------------------------------------//
	public static void onStart ( ) {

		MoaiLog.i ( "MoaiGameSparks onStart" );

		GSAndroidPlatform.gs().start();
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiGameSparks onCreate: Initializing GameSparks" );

		sActivity = activity;
	}

	//================================================================//
	// GameSparks JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init ( String apiKey, String apiSecret, String credential ) {
		
		MoaiLog.i ( "MoaiGameSparks: init" );

		// GSAndroidPlatform.initialise(this, "YOUR KEY", "YOUR SECRET", "YOUR CREDENTIAL", liveMode, autoUpdate);
		GSAndroidPlatform.initialise(this, apiKey, apiSecret, credential, false, true);

		// GSAndroidPlatform.gs().setOnAvailable(new GSEventConsumer<Boolean>() {
  //           @Override
  //           public void onEvent(Boolean available) {

  //               if (available) {
  //                 //If we connect, authenticate our player
  //                   GSAndroidPlatform.gs().getRequestBuilder().createAuthenticationRequest().setUserName("username").setPassword("password").send(new GSEventConsumer<GSResponseBuilder.AuthenticationResponse>() {
  //                       @Override
  //                       public void onEvent(GSResponseBuilder.AuthenticationResponse authenticationResponse) {

  //                           if(!authenticationResponse.hasErrors()){
  //                             //Do something when we authenticate
  //                           }

  //                       }
  //                   });
  //               }
  //           }
  //       });
	}
}
