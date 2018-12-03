//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.firebaseinvites;

import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.os.Bundle;

import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")

//================================================================//
// MoaiFirebaseInvites
//================================================================//
public class MoaiFirebaseInvites {

	private static Activity sActivity = null;

	//----------------------------------------------------------------//
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiFirebaseInvites onCreate: Initializing Firebase" );

		sActivity = activity;
	}

	//================================================================//
	// FirebaseInvites JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init () {
		
		MoaiLog.i ( "MoaiFirebaseInvites: init" );

	}

	//----------------------------------------------------------------//
	public static void showDialog ( String title, message, deepLink, cta ) {

		MoaiLog.i ( "MoaiFirebaseInvites: showDialog" );

	    Intent intent = new AppInviteInvitation.IntentBuilder(title)
	            .setMessage(message)
	            .setDeepLink(Uri.parse(deepLink))
	            //.setCustomImage(Uri.parse(getString(R.string.invitation_custom_image)))
	            .setCallToActionText(cta)
	            .build();
	    startActivityForResult(intent, REQUEST_INVITE);
	}

// @Override
// protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//     super.onActivityResult(requestCode, resultCode, data);
//     Log.d(TAG, "onActivityResult: requestCode=" + requestCode + ", resultCode=" + resultCode);

//     if (requestCode == REQUEST_INVITE) {
//         if (resultCode == RESULT_OK) {
//             // Get the invitation IDs of all sent messages
//             String[] ids = AppInviteInvitation.getInvitationIds(resultCode, data);
//             for (String id : ids) {
//                 Log.d(TAG, "onActivityResult: sent invitation " + id);
//             }
//         } else {
//             // Sending failed or it was canceled, show failure message to the user
//             // ...
//         }
//     }
// }


// @Override
// protected void onCreate(Bundle savedInstanceState) {
//     // ...

//     // Check for App Invite invitations and launch deep-link activity if possible.
//     // Requires that an Activity is registered in AndroidManifest.xml to handle
//     // deep-link URLs.
//     FirebaseDynamicLinks.getInstance().getDynamicLink(getIntent())
//             .addOnSuccessListener(this, new OnSuccessListener<PendingDynamicLinkData>() {
//                 @Override
//                 public void onSuccess(PendingDynamicLinkData data) {
//                     if (data == null) {
//                         Log.d(TAG, "getInvitation: no data");
//                         return;
//                     }

//                     // Get the deep link
//                     Uri deepLink = data.getLink();

//                     // Extract invite
//                     FirebaseAppInvite invite = FirebaseAppInvite.getInvitation(data);
//                     if (invite != null) {
//                         String invitationId = invite.getInvitationId();
//                     }

//                     // Handle the deep link
//                     // ...
//                 }
//             })
//             .addOnFailureListener(this, new OnFailureListener() {
//                 @Override
//                 public void onFailure(@NonNull Exception e) {
//                     Log.w(TAG, "getDynamicLink:onFailure", e);
//                 }
//             });
// }

}
