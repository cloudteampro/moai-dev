//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.firebase;

import com.google.firebase.analytics.FirebaseAnalytics;
import com.google.firebase.appinvite.FirebaseAppInvite;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.google.firebase.dynamiclinks.DynamicLink;
import com.google.firebase.dynamiclinks.FirebaseDynamicLinks;
import com.google.firebase.dynamiclinks.PendingDynamicLinkData;
import com.google.firebase.dynamiclinks.ShortDynamicLink;
import com.google.firebase.remoteconfig.FirebaseRemoteConfig;
import com.google.firebase.remoteconfig.FirebaseRemoteConfigSettings;
import com.google.android.gms.appinvite.AppInviteInvitation;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.moaisdk.core.Moai;
import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.support.annotation.NonNull;
import android.os.Bundle;

import androidx.annotation.NonNull;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

//================================================================//
// MoaiFirebase
//================================================================//
public class MoaiFirebase {

	public enum ListenerEvent {
		FETCH_CONFIG_SUCCEEDED,
		FETCH_CONFIG_FAILED,
		DEEPLINK_CREATED_SUCCEEDED,
		PENDING_INVITATION_ID_SUCCEEDED,
		READ_FBDB_SUCCEEDED
	}

	private static String IOS_APP_CLIENT_ID = "164086327400-08sbqbtrae1v3l78fpblesuikse5mv48.apps.googleusercontent.com";
	private static int REQUEST_INVITE = 1496;

	private static String mInvitationUrl = "";
	private static String mInvitationId = "";
	private static String mValuesFromFBDB = "";

	private static Activity sActivity = null;
	private static FirebaseRemoteConfig sFirebaseRemoteConfig = null;
	private static FirebaseAnalytics sFirebaseAnalytics = null;

	protected static native void AKUInvokeListener ( int eventID );

	//----------------------------------------------------------------//
	public static class LuaException extends Exception {
    	public LuaException ( String message ) {
        	super ( message );
    	}
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiFirebase onCreate: " );

		sActivity = activity;

		sFirebaseAnalytics = FirebaseAnalytics.getInstance(sActivity);
		sFirebaseRemoteConfig = FirebaseRemoteConfig.getInstance ();
		FirebaseRemoteConfigSettings configSettings = new FirebaseRemoteConfigSettings.Builder ()
        .setDeveloperModeEnabled ( true )
        .build();
		sFirebaseRemoteConfig.setConfigSettings ( configSettings );

		FirebaseDynamicLinks.getInstance ().getDynamicLink ( sActivity.getIntent ()).addOnSuccessListener ( sActivity, new OnSuccessListener < PendingDynamicLinkData > () {

            @Override
            public void onSuccess ( PendingDynamicLinkData data ) {

                if ( data == null ) {

					MoaiLog.i ( "MoaiFirebase: getInvitation: no data" );
                    return;
                }

                Uri deepLink = data.getLink ();

                FirebaseAppInvite invite = FirebaseAppInvite.getInvitation ( data );

                if ( invite != null ) {

                	mInvitationId = deepLink.getQueryParameter ("invitedby" );

					MoaiLog.i ( "MoaiFirebase: getInvitation: invitation id: " + mInvitationId );

					synchronized ( Moai.sAkuLock ) {

						AKUInvokeListener ( ListenerEvent.PENDING_INVITATION_ID_SUCCEEDED.ordinal ());
					}
                }
            }
        })
        .addOnFailureListener ( sActivity, new OnFailureListener () {

            @Override
            public void onFailure ( @NonNull Exception e ) {

				MoaiLog.i ( "MoaiFirebase: getDynamicLink: onFailure "+e.getMessage () );
            }
        });
	}

	//----------------------------------------------------------------//
	public static void onActivityResult ( int requestCode, int resultCode, Intent data ) {

		MoaiLog.i ( "MoaiFirebase: onActivityResult: requestCode=" + requestCode + ", resultCode=" + resultCode );

		 if ( requestCode == REQUEST_INVITE ) {

			 if ( resultCode == Activity.RESULT_OK ) {

				 String [] ids = AppInviteInvitation.getInvitationIds ( resultCode, data );

				 for (String id : ids) {

					 MoaiLog.i ( "MoaiFirebase: onActivityResult: sent invitation " + id );
				 }
			 } else {

				 MoaiLog.i ( "MoaiFirebase: onActivityResult: sent invitation resultCode cancel" );
			 }
		 }
	}

	//================================================================//
	// FirebaseConfig JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init () {
		
		MoaiLog.i ( "MoaiFirebase: init" );
	}

	//----------------------------------------------------------------//
	public static void fetchConfig () {

		MoaiLog.i ( "MoaiFirebase: fetchConfig" );

		sFirebaseRemoteConfig.fetch ().addOnCompleteListener ( sActivity, new OnCompleteListener < Void > () {

			@Override
			public void onComplete ( @NonNull Task< Void > task ) {
				if (task.isSuccessful()) {

					MoaiLog.i ( "MoaiFirebase: fetch config succeeded" );

					synchronized ( Moai.sAkuLock ) {
						AKUInvokeListener ( ListenerEvent.FETCH_CONFIG_SUCCEEDED.ordinal ());
					}
				} else {

					MoaiLog.i ( "MoaiFirebase: fetch config failed" );

					synchronized ( Moai.sAkuLock ) {
						AKUInvokeListener ( ListenerEvent.FETCH_CONFIG_FAILED.ordinal ());
					}
				}
			}
		});
	}

	//----------------------------------------------------------------//
	public static void activateFetchedConfig () {

		MoaiLog.i ( "MoaiFirebase: activateFetchedConfig" );

		sFirebaseRemoteConfig.activateFetched ();
	}

	//----------------------------------------------------------------//
	public static String getConfigString ( String key ) {

		MoaiLog.i ( "MoaiFirebase: getConfigString key "+key );

		return sFirebaseRemoteConfig.getString ( key );
	}

	//----------------------------------------------------------------//
	public static boolean getConfigBoolean ( String key ) {

		MoaiLog.i ( "MoaiFirebase: getConfigBoolean key "+key );

		return sFirebaseRemoteConfig.getBoolean ( key );
	}

	//----------------------------------------------------------------//
	public static double getConfigDouble ( String key ) {

		MoaiLog.i ( "MoaiFirebase: getConfigDouble key "+key );

		return sFirebaseRemoteConfig.getDouble ( key );
	}

	//----------------------------------------------------------------//
	public static double getConfigLong ( String key ) {

		MoaiLog.i ( "MoaiFirebase: getConfigLong key "+key );

		return sFirebaseRemoteConfig.getLong ( key );
	}

	//----------------------------------------------------------------//
	public static void createAnonymousAccountWithReferrerInfo ( String uid, String referrerUid ) {

		MoaiLog.i ( "MoaiFirebase: createAnonymousAccountWithReferrerInfo: " + uid + " ref " + referrerUid );

		DatabaseReference userRecord = FirebaseDatabase.getInstance ().getReference ().child ( "users" ).child ( uid );
		userRecord.child ( "referred_by" ).setValue ( referrerUid );
	}

	//----------------------------------------------------------------//
	public static void logEvent ( String eventName, Bundle params ) {

		MoaiLog.i ( "MoaiFirebase: logEvent: " + eventName );
		sFirebaseAnalytics.logEvent(eventName, params);
	}

	//----------------------------------------------------------------//
	public static String getInvitationId () {

		MoaiLog.i ( "MoaiFirebase: getInvitationId: " + mInvitationId );

		return mInvitationId;
	}

	//----------------------------------------------------------------//
	public static String getInvitationDeepLink () {

		MoaiLog.i ( "MoaiFirebase: getInvitationDeepLink: " + mInvitationUrl );

		return mInvitationUrl;
	}

	//----------------------------------------------------------------//
	public static void showInviteSMSDialog ( String title, String message, String deepLink, String customImage, String cta ) {

		MoaiLog.i ( "MoaiFirebase: showInviteSmsDialog" );

		Intent intent = new Intent( Intent.ACTION_VIEW );
		intent.setData ( Uri.parse ( "sms:" ));
		intent.setType ( "vnd.android-dir/mms-sms" );
		// intent.putExtra ( Intent.EXTRA_TEXT, message );
		intent.putExtra ( "sms_body", message );
		if ( intent.resolveActivity ( sActivity.getPackageManager ()) != null ) {
			sActivity.startActivity ( intent );
		}

	   //  Intent intent = new AppInviteInvitation.IntentBuilder ( title )
	   //          .setMessage ( message )
	   //          .setDeepLink ( Uri.parse ( deepLink ))
	   //          //.setCustomImage ( Uri.parse ( customImage ))
	   //          .setCallToActionText ( cta )
				// .setOtherPlatformsTargetApplication ( AppInviteInvitation.IntentBuilder.PlatformMode.PROJECT_PLATFORM_IOS, IOS_APP_CLIENT_ID )
	   //          .build ();
	   //  sActivity.startActivityForResult ( intent, REQUEST_INVITE );
	}

	//----------------------------------------------------------------//
	public static void showInviteEmailDialog ( String title, String message, String deepLink, String customImage, String cta ) {

		MoaiLog.i ( "MoaiFirebase: showInviteEmailDialog" );

		Intent intent = new Intent( Intent.ACTION_SENDTO );
		intent.setData ( Uri.parse ( "mailto:" ));
		intent.putExtra ( Intent.EXTRA_SUBJECT, title );
		intent.putExtra ( Intent.EXTRA_TEXT, message );
		// intent.putExtra ( Intent.EXTRA_HTML_TEXT, msgHtml );
		if ( intent.resolveActivity ( sActivity.getPackageManager ()) != null ) {
			sActivity.startActivity ( intent );
		}

		// Intent intent = new AppInviteInvitation.IntentBuilder ( title )
		// 		.setDeepLink ( Uri.parse ( deepLink ))
		// 		.setEmailHtmlContent ( "<a href='%%APPINVITE_LINK_PLACEHOLDER%%'><h1>"+cta+"</h1><img src='https://appjoy.org/wp-content/uploads/2016/06/firebase-invites-logo.png'></a>" )
		// 		.setEmailSubject ( message )
		// 		.setOtherPlatformsTargetApplication ( AppInviteInvitation.IntentBuilder.PlatformMode.PROJECT_PLATFORM_IOS, IOS_APP_CLIENT_ID )
		// 		.build ();
		// sActivity.startActivityForResult ( intent, REQUEST_INVITE );
	}

	//----------------------------------------------------------------//
	public static void createInvitationDeepLink ( String uid ) {

		MoaiLog.i ( "MoaiFirebase: createInvitationDeepLink: "+uid );

		String link = "http://fruitycat.cloudteam.pro/?invitedby=" + uid;
		FirebaseDynamicLinks.getInstance ().createDynamicLink ()
				.setLink ( Uri.parse ( link ))
				.setDomainUriPrefix ( "https://cloudteam.page.link" )
				.setAndroidParameters (
						new DynamicLink.AndroidParameters.Builder("pro.cloudteam.nashiri" )
								.setMinimumVersion ( 240 )
								.build())
				.setIosParameters(
						new DynamicLink.IosParameters.Builder("pro.cloudteam.Nashiri" )
								.setAppStoreId ( "973082633" )
								.setMinimumVersion ( "1.41" )
								.build ())
				.buildShortDynamicLink ()
				.addOnSuccessListener ( new OnSuccessListener < ShortDynamicLink >() {

					@Override
					public void onSuccess ( ShortDynamicLink shortDynamicLink ) {

						mInvitationUrl = shortDynamicLink.getShortLink ().toString ();

						MoaiLog.i ( "MoaiFirebase: createInvitationDeepLink: onSuccess: " + mInvitationUrl );

						synchronized ( Moai.sAkuLock ) {

							AKUInvokeListener ( ListenerEvent.DEEPLINK_CREATED_SUCCEEDED.ordinal ());
						}
					}
				});
	}

	//----------------------------------------------------------------//
	public static void writeToFBDB ( String userUid, String myUid, String value ) {

		MoaiLog.i ( "MoaiFirebase: writeToFBDB: " + userUid + " : " + myUid + " : " + value );

		DatabaseReference userRecord = FirebaseDatabase.getInstance ().getReference ().child ( "users" ).child ( userUid );

		userRecord.child ( myUid ).setValue ( value );
	}

	//----------------------------------------------------------------//
	public static void readFromFBDB ( String uid ) {

		MoaiLog.i ( "MoaiFirebase: readFromFBDB: " + uid );

		DatabaseReference userRecord = FirebaseDatabase.getInstance ().getReference ().child ( "users" ).child ( uid );

		userRecord.addListenerForSingleValueEvent ( new ValueEventListener () {

			//----------------------------------------------------------------//
			public void onDataChange ( DataSnapshot dataSnapshot ) {

				MoaiLog.i ( "MoaiFirebase: readFromFBDB: onDataChange" );

				Map<String,Map<String,String>> data = ( Map<String,Map<String,String>> ) dataSnapshot.getValue();

				MoaiLog.i ( "MoaiFirebase: readFromFBDB: onDataChange "+data );

				if (data != null) {
					JSONObject jsonObject = new JSONObject ( data );

					mValuesFromFBDB = jsonObject.toString ();

					synchronized ( Moai.sAkuLock ) {

						AKUInvokeListener ( ListenerEvent.READ_FBDB_SUCCEEDED.ordinal ());
					}
				}
			}

			//----------------------------------------------------------------//
			public void onCancelled ( DatabaseError databaseError ) {

				MoaiLog.i ( "MoaiFirebase: onCancelled: " + databaseError.getMessage ());
			}
		});
	}

	//----------------------------------------------------------------//
	public static String getValuesFromFBDB () {

		MoaiLog.i ( "MoaiFirebase: getValuesFromFBDB: " + mValuesFromFBDB );

		return mValuesFromFBDB;
	}
}

