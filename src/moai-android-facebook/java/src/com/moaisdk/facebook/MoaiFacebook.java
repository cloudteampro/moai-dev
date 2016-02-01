//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.facebook;

import com.moaisdk.core.*;

import java.io.IOException;
import java.math.BigDecimal;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Currency;
import java.util.HashMap;
import java.util.List;
import java.util.Set;
import java.util.Collection;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.facebook.AccessToken;
import com.facebook.appevents.AppEventsLogger;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookRequestError;
import com.facebook.FacebookSdk;
import com.facebook.GraphResponse;
import com.facebook.GraphRequest;
import com.facebook.HttpMethod;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import com.facebook.share.widget.AppInviteDialog;
import com.facebook.share.model.AppInviteContent;
import com.facebook.share.widget.GameRequestDialog;
import com.facebook.share.model.GameRequestContent;

import java.net.URL;
import java.util.HashMap;

import org.json.*;

@SuppressWarnings("unused")

//================================================================//
// MoaiFacebook
//================================================================//
public class MoaiFacebook {

	public enum DialogResultCode {

		RESULT_SUCCESS,
		RESULT_CANCEL,
		RESULT_ERROR;

		public static DialogResultCode valueOf ( int index ) {

			DialogResultCode [] values = DialogResultCode.values ();
			if (( index < 0 ) || ( index >= values.length )) {

				return RESULT_ERROR;
			}

			return values [ index ];
		}
	}

	private static Activity 			sActivity					= null;
	private static CallbackManager 		sCallbackManager			= null;
	private static String 				sAppId						= null;
	private static GameRequestDialog 	sGameRequestDialog			= null;
	private static int					sGameRequestCallbackRef		= 0;
	private static AppEventsLogger		sLogger						= null;

	// If true then loginWithReadPermissions is called to request additional permissions.
	// Necessary to distinguish different callbacks
	private static boolean				sRequestingPermissions		= false;

	protected static native int		AKUClearCallbackRef				( int gameRequestCallbackRef );
	protected static native void	AKUNotifyFacebookLoginDismissed	( String msg );
	protected static native void	AKUNotifyFacebookLoginError		( String exceptionMsg );
	protected static native void	AKUNotifyFacebookLoginSuccess	();
	protected static native void	AKUNotifyGameRequestFailed		( String msg, int gameRequestCallbackRef );
	protected static native void	AKUNotifyGameRequestSuccess		( String requestId, String[] recipientsArr, int gameRequestCallbackRef );
	protected static native void	AKUNotifyGraphRequestFailed		( String error, int ref );
	protected static native void	AKUNotifyGraphRequestSuccess	( String response, int ref );

	//----------------------------------------------------------------//
	private static FacebookCallback sLoginCallback = new FacebookCallback<LoginResult>() {
		@Override
		public void onSuccess ( LoginResult loginResult ) {

			MoaiLog.i ( "MoaiFacebook onSuccess" );
			// sLoginAccessToken = loginResult.getAccessToken ();

			synchronized ( Moai.sAkuLock ) {
				AKUNotifyFacebookLoginSuccess ();
			}
		}

		@Override
		public void onCancel () {

			MoaiLog.i ( "MoaiFacebook onCancel" );
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyFacebookLoginDismissed ( "cancel" );
			}
		}

		@Override
		public void onError ( FacebookException exception ) {

			MoaiLog.i ( "MoaiFacebook onError" );
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyFacebookLoginError ( exception.toString ());
			}
		}
	};

	//----------------------------------------------------------------//
	private static FacebookCallback sGameRequestCallback = new FacebookCallback<GameRequestDialog.Result> () {
		@Override
		public void onSuccess ( GameRequestDialog.Result result ) {

			List recipientsList = result.getRequestRecipients ();

			String[] recipientsArr = new String [ recipientsList.size () ];
			recipientsArr = ( String[] ) recipientsList.toArray ( recipientsArr );
			
			MoaiLog.i ( "MoaiFacebook request dialog onSuccess" );
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyGameRequestSuccess ( result.getRequestId (), recipientsArr, sGameRequestCallbackRef );
				sGameRequestCallbackRef = AKUClearCallbackRef ( sGameRequestCallbackRef );
			}
		}

		@Override
		public void onCancel () {

			MoaiLog.i ( "MoaiFacebook request dialog onCancel" );
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyGameRequestFailed ( "cancel", sGameRequestCallbackRef );
				sGameRequestCallbackRef = AKUClearCallbackRef ( sGameRequestCallbackRef );
			}
		}

		@Override
		public void onError ( FacebookException error ) {

			MoaiLog.i ( "MoaiFacebook request dialog onError" + error.toString ());
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyGameRequestFailed ( error.toString (), sGameRequestCallbackRef );
				sGameRequestCallbackRef = AKUClearCallbackRef ( sGameRequestCallbackRef );
			}
		}
	};

	//----------------------------------------------------------------//
	public static void onActivityResult ( int requestCode, int resultCode, Intent data ) {

		MoaiLog.i ( "MoaiFacebook onActivityResult: Calling Session onActivityResult ()" );
		sCallbackManager.onActivityResult ( requestCode, resultCode, data );
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiFacebook onCreate: Initializing Facebook" );

		sActivity = activity;
		FacebookSdk.sdkInitialize ( sActivity );

		sLogger = AppEventsLogger.newLogger ( sActivity );
		sCallbackManager = CallbackManager.Factory.create ();

		sGameRequestDialog = new GameRequestDialog ( sActivity );
		sGameRequestDialog.registerCallback ( sCallbackManager, sGameRequestCallback );
		LoginManager.getInstance ().registerCallback ( sCallbackManager, sLoginCallback );
	}

	//----------------------------------------------------------------//
	public static void onPause( ) {

		MoaiLog.i("MoaiFacebook on pause");
		com.facebook.appevents.AppEventsLogger.deactivateApp ( sActivity );
	}

	//----------------------------------------------------------------//
	public static void onResume ( ) {

		MoaiLog.i("MoaiFacebook on resume");
		com.facebook.appevents.AppEventsLogger.activateApp ( sActivity );
	}

	//================================================================//
	// Facebook JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static String getToken () {

		MoaiLog.i ( "MoaiFacebook: getToken" );
		return AccessToken.getCurrentAccessToken ().getToken ();
	}

	//----------------------------------------------------------------//
	public static void graphRequest ( String method, String path, Bundle params, final int callbackRef ) {

		AccessToken token = AccessToken.getCurrentAccessToken ();

		if ( token != null ) {

			GraphRequest.Callback callback = new GraphRequest.Callback () {
				private int mRef;
				private boolean mExecuted;

				@Override
				public void onCompleted ( GraphResponse response ) {
					if ( mExecuted ) return;

					synchronized ( Moai.sAkuLock ) {
						FacebookRequestError error = response.getError ();
						if ( error != null ) {

							AKUNotifyGraphRequestFailed ( error.toString (), mRef );
							AKUClearCallbackRef ( mRef );
						}
						else {

							AKUNotifyGraphRequestSuccess ( response.getJSONObject ().toString (), mRef );
							AKUClearCallbackRef ( mRef );
						}
					}

					mExecuted = true;
				}

				private GraphRequest.Callback init ( int ref ) {
					mRef = ref;
					mExecuted = false;
					return this;
				}
			}.init ( callbackRef );

			GraphRequest request = new GraphRequest ( token, path, params, HttpMethod.valueOf( method ), callback );
			request.executeAsync ();
		}
	}

	//----------------------------------------------------------------//
	public static boolean hasGranted ( String permission ) {

		AccessToken token = AccessToken.getCurrentAccessToken ();

		if ( token != null && !token.isExpired ()) {

			Set < String > granted = ( Set < String >) token.getPermissions ();
			for ( String p : granted ) {
				if ( permission.equals ( p )) {
					return true;
				}
			}
		}

		return false;
	}

	//----------------------------------------------------------------//
	public static void init ( String appId ) {

		sAppId = appId;
	}

	//----------------------------------------------------------------//
	public static void logEvent ( String eventName, double valueToSum, Bundle params ) {

		MoaiLog.i ( "MoaiFacebook: logEvent --- event = " + eventName + ", value = " + valueToSum );
		sLogger.logEvent ( eventName, valueToSum, params );
	}

	//----------------------------------------------------------------//
	public static void logPurchase ( double money, String currency, Bundle params ) {

		MoaiLog.i ( "MoaiFacebook: logPurchase --- event = " + money + ", value = " + currency );
		sLogger.logPurchase ( BigDecimal.valueOf ( money ), Currency.getInstance ( currency ), params );
	}

	//----------------------------------------------------------------//
	public static void login ( String [] permissions ) {

		MoaiLog.i("MoaiFacebook: login");

		if ( permissions == null ) {
			permissions = new String []{ "public_profile" };
		}

		sRequestingPermissions = false;
		LoginManager.getInstance().logInWithReadPermissions ( sActivity, Arrays.asList ( permissions ) );
	}

	//----------------------------------------------------------------//
	public static void logout () {

		MoaiLog.i("MoaiFacebook: logout");
		LoginManager.getInstance ().logOut ();
	}

	//----------------------------------------------------------------//
	public static void postToFeed ( String link, String picture, String name, String caption, String description, String message ) {
		// TODO
	}

	//----------------------------------------------------------------//
	public static void requestPublishPermissions ( String [] permissions ) {

		sRequestingPermissions = true;
		LoginManager.getInstance ().logInWithPublishPermissions ( sActivity, Arrays.asList ( permissions ) );
	}

	//----------------------------------------------------------------//
	public static void requestReadPermissions ( String [] permissions ) {

		sRequestingPermissions = true;
		LoginManager.getInstance ().logInWithReadPermissions ( sActivity, Arrays.asList ( permissions ) );
	}

	//----------------------------------------------------------------//
	public static boolean sendGameRequest ( String message, String actionType, String objectId, String filters, String [] recipients, String [] suggestions, int ref ) {

		GameRequestContent.Builder builder = new GameRequestContent.Builder ();

		builder.setMessage 	( message );
		builder.setObjectId ( objectId );

		if ( recipients != null ) {
			builder.setRecipients 	( new ArrayList < String > ( Arrays.asList ( recipients )));
		}
		if ( suggestions != null ) {
			builder.setSuggestions 	( new ArrayList < String > ( Arrays.asList ( suggestions )));
		}
		
		// There is a FILTER_NONE enum value in C++ code, but in java it is replaced by null
		try {
			GameRequestContent.Filters filter = GameRequestContent.Filters.valueOf ( filters );
			builder.setFilters ( filter );
		} catch ( Exception e ) {}

		try {
			GameRequestContent.ActionType action = GameRequestContent.ActionType.valueOf ( actionType );
			builder.setActionType ( action );
		} catch ( Exception e ) {}

		// Looks like callback is not bound to concrete GameRequestDialog instance, but is looked up by REQUEST_CODE.
		// Therefore, there is no point in spawning different GameRequestDialogs, 
		// the way to go is using single instance and callback manager as in tutorial code.
		// Here we remember the last Lua callback ref in class variable to be used later from FB dialog callback.
		sGameRequestCallbackRef = ref;
		sGameRequestDialog.show ( builder.build ());
		return sGameRequestDialog.canShow ();
	}

	//----------------------------------------------------------------//
	public static boolean sessionValid () {

		MoaiLog.i ( "MoaiFacebook: sessionValid" );

		AccessToken accessToken = AccessToken.getCurrentAccessToken ();
		return accessToken != null && !accessToken.isExpired ();
	}

	//----------------------------------------------------------------//
	public static void showInviteDialog ( String linkURL, String imgURL ) {

		MoaiLog.i ( "MoaiFacebook: showInviteDialog" );

		if ( AppInviteDialog.canShow()) {
			AppInviteContent content = new AppInviteContent.Builder ()
					.setApplinkUrl ( linkURL )
					.setPreviewImageUrl ( imgURL )
					.build ();
			AppInviteDialog.show ( sActivity, content );
		}
	}
}