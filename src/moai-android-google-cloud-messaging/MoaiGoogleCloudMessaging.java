//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

package com.ziplinegames.moai;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;

import com.google.android.gcm.GCMRegistrar;

//================================================================//
// MoaiGoogleCloudMessaging
//================================================================//
public class MoaiGoogleCloudMessaging {

	private static Activity sActivity = null;

	protected static native void	AKUNotifyError 			( String error_id );
	protected static native void	AKUNotifyRegistered 	( String registration_id );
	protected static native void	AKUNotifyUnregistered 	( String registration_id );
	protected static native void	AKUNotifyMessage 		( String message_json );
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging onCreate: -------------------------------------------------------- " );
		sActivity = activity;
	}
	
	//----------------------------------------------------------------//
	public static Activity getContextActivity ( ) {
		
		return sActivity;
	}
	
	//----------------------------------------------------------------//
	public static void onBackPressed () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging onBackPressed: destroyContext; -------------------------------------------------------- " );
			
		sActivity = null;
	}

	//----------------------------------------------------------------//
	public static void NotifyRegistered ( String registration_id ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Registered! registration is = "+registration_id+" -------------------------------------------------------- " );
		
		synchronized ( Moai.sAkuLock ) {
			try {

				AKUNotifyRegistered ( registration_id );
			} catch ( UnsatisfiedLinkError ule ) {

				MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Registered! but application is off -------------------------------------------------------- " );
			}
		}
	}
	
	//----------------------------------------------------------------//
	public static void NotifyUnregistered ( String registration_id ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Unregisterd! registration is = "+registration_id+" -------------------------------------------------------- " );
		
		synchronized ( Moai.sAkuLock ) {
			try {

				AKUNotifyUnregistered ( registration_id );
			} catch ( UnsatisfiedLinkError ule ) {

				MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Unegistered! but application is off -------------------------------------------------------- " );
			}
		}
	}

	//----------------------------------------------------------------//
	public static void NotifyMessage ( String message_json ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Incoming message! message = "+message_json+" -------------------------------------------------------- " );
		
		if ( sActivity != null ) {
			
			synchronized ( Moai.sAkuLock ) {
				try {

					AKUNotifyMessage ( message_json );
				} catch ( UnsatisfiedLinkError ule ) {

					MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Message received! but application is off -------------------------------------------------------- " );
				}
			}
		}
	}
	
	//----------------------------------------------------------------//
	public static void NotifyError ( String error_id ) {
		
		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Error! error = "+error_id+" -------------------------------------------------------- " );
		
		synchronized ( Moai.sAkuLock ) {
			try {

				AKUNotifyError ( error_id );
			} catch ( UnsatisfiedLinkError ule ) {

				MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Error handled! but application is off -------------------------------------------------------- " );
			}
		}
	}
	
	//================================================================//
	// MoaiGoogleCloudMessaging JNI callback methods
	//================================================================//
	
	//----------------------------------------------------------------//	
	public static String getToken () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: getToken -------------------------------------------------------- " );
		
		GCMRegistrar.checkDevice ( sActivity );
		
	    GCMRegistrar.checkManifest ( sActivity );
	    
	    String gcmToken = GCMRegistrar.getRegistrationId ( sActivity );
	    
	    if ( gcmToken.equals ( "" ) ) {
	    	
	    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Register! -------------------------------------------------------- " );
	    	
	        GCMRegistrar.register ( sActivity, @GCM_SENDER_ID@ );
	    } else {
	    	
	    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Already registered! RegistrationId = "+gcmToken+" -------------------------------------------------------- " );
	    }
	    
	    return gcmToken;
	}
	
	//----------------------------------------------------------------//	
	public static void register () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: register -------------------------------------------------------- " );
		
		try { 

			GCMRegistrar.checkDevice ( sActivity );
			
		    GCMRegistrar.checkManifest ( sActivity );
		    
		    GCMRegistrar.register ( sActivity, @GCM_SENDER_ID@ );
		} catch ( UnsupportedOperationException e ) {
			
			MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: device affected "+e.getLocalizedMessage()+" -------------------------------------------------------- " );
		}
	}
	
	//----------------------------------------------------------------//	
	public static String getLastPush () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: getLastPush -------------------------------------------------------- " );
		
		SharedPreferences preferences = sActivity.getApplicationContext ().getSharedPreferences ( "GCM", Context.MODE_PRIVATE );
  		
  		if ( preferences != null ) {
  			if ( preferences.contains("lastPush") ) {
  				
  				MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: push is = "+preferences.getString("lastPush", "")+" -------------------------------------------------------- " );
  		  		
  				return preferences.getString("lastPush", "");
  			}
  		}
		
  		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: push is empty -------------------------------------------------------- " );
  		
	    return "";
	}
	
	//----------------------------------------------------------------//	
	public static void removeLastPush () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: removeLastPush -------------------------------------------------------- " );
		
		SharedPreferences preferences = sActivity.getApplicationContext ().getSharedPreferences ( "GCM", Context.MODE_PRIVATE );
  		
  		if ( preferences != null ) {
  			if ( preferences.contains("lastPush") ) {
  				
  				MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: push is = "+preferences.getString("lastPush", "")+" -------------------------------------------------------- " );
  		  		
  				SharedPreferences.Editor editor = preferences.edit();

  		  		editor.clear();
  		  				
  		  		editor.commit();
  			}
  		}
  		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: push is empty -------------------------------------------------------- " );
	}
	
	//----------------------------------------------------------------//	
	public static void unregister () {

		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: unregister -------------------------------------------------------- " );
			
		GCMRegistrar.unregister ( sActivity );
	}
}
