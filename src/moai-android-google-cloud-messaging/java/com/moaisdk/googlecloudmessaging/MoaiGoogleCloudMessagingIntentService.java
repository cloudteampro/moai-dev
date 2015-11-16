package com.moaisdk.googlecloudmessaing;

import org.json.JSONException;
import org.json.JSONObject;

import @PACKAGE@.MoaiActivity;
import @PACKAGE@.R;
import com.google.android.gcm.GCMBaseIntentService;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Vibrator;
import android.support.v4.app.NotificationCompat;
import android.graphics.drawable.BitmapDrawable;

public class MoaiGoogleCloudMessagingIntentService extends GCMBaseIntentService {
	
	private static int mLastId = 0;

	  //----------------------------------------------------------------//
    public MoaiGoogleCloudMessagingIntentService () {
    	super (	@GCM_SENDER_ID@ );
    }

    //----------------------------------------------------------------//
    protected void onRegistered ( Context context, String registrationId ) {
    	
    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessagingIntentService: Device registered: REGISTRATION_ID = "+registrationId+" -------------------------------------------------------- " );
    
    	MoaiGoogleCloudMessaging.NotifyRegistered ( registrationId );
    }

    //----------------------------------------------------------------//
    protected void onUnregistered ( Context context, String registrationId ) {
    	
    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessagingIntentService: Device unregistered: REGISTRATION_ID = "+registrationId+" -------------------------------------------------------- " );

    	MoaiGoogleCloudMessaging.NotifyUnregistered ( registrationId );
    }

    //----------------------------------------------------------------//
    protected void onMessage ( Context context, Intent intent ) {
    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessagingIntentService: Message received -------------------------------------------------------- " ); 
		Vibrator vibr = ( Vibrator ) getSystemService ( VIBRATOR_SERVICE );
		notify ( context, intent.getExtras () );
		vibr.vibrate ( new long [] { 100, 300, 200, 400 }, -1 );
		String result = "{";
		for ( String key : intent.getExtras ().keySet () ) {
		    String value = (String) intent.getExtras ().get ( key );
		    result = result + "\"" + key + "\":\""+ value + "\",";
		}
		result = result + "}";
		
		result = result.replace(",}", "}");
		
		try {
			
			JSONObject jsonObj = new JSONObject ( result );
			
			SaveLastPush ( context, jsonObj.toString () );
			
			if ( MoaiGoogleCloudMessaging.getContextActivity () != null ) {
				
				MoaiGoogleCloudMessaging.NotifyMessage ( jsonObj.toString () );
			}
		} catch (JSONException e) {
			
			if ( MoaiGoogleCloudMessaging.getContextActivity () != null ) {
				
				MoaiGoogleCloudMessaging.NotifyError ( "___666___" );
			}
			e.printStackTrace();
		}
    }
    
    //----------------------------------------------------------------//
  	public void SaveLastPush ( Context context, String jsonPush ) {
  		
  		MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessaging: Save last push notification! push is = "+jsonPush+" -------------------------------------------------------- " );
  		
  		SharedPreferences preferences = getSharedPreferences("GCM", MODE_PRIVATE);
  		
  		SharedPreferences.Editor editor = preferences.edit();

  		if ( preferences != null ) {
  			if ( preferences.contains("lastPush") ) {
  				
  				editor.clear();
  				
  		  		editor.putString("lastPush", jsonPush);
  			} else {

  		  		editor.putString("lastPush", jsonPush);
  			}
  		}
  		
  		editor.commit();
  	}

    //----------------------------------------------------------------//
    private void notify ( final Context context, final Bundle data ) {
		final String msg = data.getString ( "msg" );
		NotificationCompat.Builder nb = new NotificationCompat.Builder ( context )
			 .setVibrate ( new long [] { 100, 300, 200, 300 } )
	         .setSmallIcon ( R.drawable.icon_notify ) 
	         .setAutoCancel (true) 
           .setLargeIcon ( (( BitmapDrawable ) context.getResources ().getDrawable ( R.drawable.icon )).getBitmap() )
	         .setTicker ( "Message for you!" ) 
	         .setContentText ( msg ) 
	         .setWhen ( System.currentTimeMillis () ) 
	         .setContentTitle ( msg ) 
	         .setDefaults ( Notification.DEFAULT_ALL );
		Intent notificationIntent = null;
		notificationIntent = new Intent ( context, MoaiActivity.class );
		data.putBoolean ( "push-reference", true );
		notificationIntent.putExtras ( data );
		nb.setContentIntent ( PendingIntent.getActivity ( this, 0, notificationIntent, Intent.FLAG_ACTIVITY_NEW_TASK ) );
	    final Notification notification = nb.build ();
        final NotificationManager manager = ( NotificationManager ) context.getSystemService ( Context.NOTIFICATION_SERVICE );
        manager.notify ( mLastId, notification );
        mLastId++;
	}

    //----------------------------------------------------------------//
    public static void clearStatusBar ( final Context context ) {
		
    	final NotificationManager manager = ( NotificationManager ) context.getSystemService ( Context.NOTIFICATION_SERVICE );
        
    	manager.cancelAll ();
	}

    //----------------------------------------------------------------//
	public static void clearNotificationByID ( final Context context, final int id ) {
		
		final NotificationManager manager = ( NotificationManager ) context.getSystemService ( Context.NOTIFICATION_SERVICE );
        
		manager.cancel ( id );
	}

	  //----------------------------------------------------------------//
    protected void onDeletedMessages(Context context, int total ) {
    	
    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessagingIntentService: Received deleted messages notification -------------------------------------------------------- " );
    }

    //----------------------------------------------------------------//
    public void onError(Context context, String errorId ) {
    	
    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessagingIntentService: Received error: " + errorId + " -------------------------------------------------------- " );
    
		MoaiGoogleCloudMessaging.NotifyError ( errorId );
    }

    //----------------------------------------------------------------//
    protected boolean onRecoverableError ( Context context, String errorId ) {
    	
    	MoaiLog.i ( " -------------------------------------------------------- MoaiGoogleCloudMessagingIntentService: Received recoverable error: " + errorId + " -------------------------------------------------------- " );

		MoaiGoogleCloudMessaging.NotifyError ( errorId );
		
    	return super.onRecoverableError ( context, errorId );
    }
}