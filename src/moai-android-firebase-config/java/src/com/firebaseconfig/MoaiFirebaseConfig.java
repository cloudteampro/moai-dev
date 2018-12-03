//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.firebaseconfig;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.os.Bundle;

import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")

//================================================================//
// MoaiFirebaseConfig
//================================================================//
public class MoaiFirebaseConfig {

	private static Activity sActivity = null;

	//----------------------------------------------------------------//
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiFirebaseConfig onCreate: Initializing Firebase" );

		sActivity = activity;

		FirebaseRemoteConfig mFirebaseRemoteConfig = FirebaseRemoteConfig.getInstance();
		FirebaseRemoteConfigSettings configSettings = new FirebaseRemoteConfigSettings.Builder()
        .setDeveloperModeEnabled(BuildConfig.DEBUG)
        .build();
		mFirebaseRemoteConfig.setConfigSettings(configSettings);
	}

	//================================================================//
	// FirebaseConfig JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init () {
		
		MoaiLog.i ( "MoaiFirebaseConfig: init" );

	}

// // cacheExpirationSeconds is set to cacheExpiration here, indicating the next fetch request
// // will use fetch data from the Remote Config service, rather than cached parameter values,
// // if cached parameter values are more than cacheExpiration seconds old.
// // See Best Practices in the README for more information.
// mFirebaseRemoteConfig.fetch(cacheExpiration)
//         .addOnCompleteListener(this, new OnCompleteListener<Void>() {
//             @Override
//             public void onComplete(@NonNull Task<Void> task) {
//                 if (task.isSuccessful()) {
//                     Toast.makeText(MainActivity.this, "Fetch Succeeded",
//                             Toast.LENGTH_SHORT).show();

//                     // After config data is successfully fetched, it must be activated before newly fetched
//                     // values are returned.
//                     mFirebaseRemoteConfig.activateFetched();
//                 } else {
//                     Toast.makeText(MainActivity.this, "Fetch Failed",
//                             Toast.LENGTH_SHORT).show();
//                 }
//                 displayWelcomeMessage();
//             }
//         });


// private void displayWelcomeMessage() {
//     String welcomeMessage = mFirebaseRemoteConfig.getString(WELCOME_MESSAGE_KEY);
//     if (mFirebaseRemoteConfig.getBoolean(WELCOME_MESSAGE_CAPS_KEY)) {
//         mWelcomeTextView.setAllCaps(true);
//     } else {
//         mWelcomeTextView.setAllCaps(false);
//     }
//     mWelcomeTextView.setText(welcomeMessage);
// }

}
