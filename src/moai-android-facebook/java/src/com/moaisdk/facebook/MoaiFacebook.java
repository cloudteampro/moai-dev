//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.facebook;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Collection;
import com.moaisdk.core.*;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.annotation.NonNull;

import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
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
	private static AccessToken  		sLoginAccessToken			= null;
	private static GameRequestDialog 	sGameRequestDialog			= null;
	private static int					sGameRequestCallbackRef		= 0;

	protected static native void	AKUNotifyFacebookLoginSuccess	();
	protected static native void	AKUNotifyFacebookLoginDismissed	();
	protected static native void	AKUNotifyFacebookLoginError 	();

	//----------------------------------------------------------------//
	private static FacebookCallback sLoginCallback = new FacebookCallback<LoginResult>() {
		@Override
		public void onSuccess ( LoginResult loginResult ) {

			MoaiLog.i ( "MoaiFacebook onSuccess" );
			sLoginAccessToken = loginResult.getAccessToken ();

			synchronized ( Moai.sAkuLock ) {
				AKUNotifyFacebookLoginSuccess ();
			}
		}

		@Override
		public void onCancel () {

			MoaiLog.i ( "MoaiFacebook onCancel" );
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyFacebookLoginDismissed ();
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
			synchronized ( Moai.sAkuLock ) {
				AKUGameRequestDialogDidComplete ( result.getRequestId (), result.getRequestRecipients (), sGameRequestCallback );
				sGameRequestCallback = AKUClearCallbackRef ( sGameRequestCallback );
			}
		}

		@Override
		public void onCancel () {
			synchronized ( Moai.sAkuLock ) {
				AKUGameRequestDialogDidFail ( "cancel", sGameRequestCallback );
				sGameRequestCallback = AKUClearCallbackRef ( sGameRequestCallback );				
			}
		}

		@Override
		public void onError ( FacebookException error ) {
			synchronized ( Moai.sAkuLock ) {
				AKUGameRequestDialogDidFail ( error.toString (), sGameRequestCallback );
				sGameRequestCallback = AKUClearCallbackRef ( sGameRequestCallback );
			}
		}
	}

	//----------------------------------------------------------------//
	public static void onActivityResult ( int requestCode, int resultCode, Intent data ) {

		MoaiLog.i ( "MoaiFacebook onActivityResult: Calling Session onActivityResult ()" );
		sCallbackManager.onActivityResult(requestCode, resultCode, data);
	}

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiFacebook onCreate: Initializing Facebook" );

		sActivity = activity;
		FacebookSdk.sdkInitialize ( sActivity );

		sCallbackManager = CallbackManager.Factory.create ();

		sRequestDialog = new GameRequestDialog ( sActivity );
		sRequestDialog.registerCallback ( sCallbackManager, sGameRequestCallback );
		LoginManager.getInstance ().registerCallback ( sCallbackManager, sLoginCallback );
	}

	//----------------------------------------------------------------//
	public static void onResume ( ) {

		MoaiLog.i("MoaiFacebook on resume");
//		if(sAppId != null) {
//			com.facebook.AppEventsLogger.activateApp(sActivity, sAppId);
//		}
	}

	//================================================================//
	// Facebook JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static String getToken () {

		MoaiLog.i ( "MoaiFacebook: getToken" );
		return sLoginAccessToken.getToken ();
	}

	//----------------------------------------------------------------//
	public static void init ( String appId ) {

		sAppId = appId;
	}

	//----------------------------------------------------------------//
	public static boolean isSessionValid () {

		MoaiLog.i ( "MoaiFacebook: isSessionValid" );
//		Session session = Session.getActiveSession ();
//		if (( session != null ) && session.isOpened ()) {
//			MoaiLog.i ( "MoaiFacebook: session is valid" );
//			return true;
//		}
		MoaiLog.i ( "MoaiFacebook: SESSION IS INVALID" );
		return false;
	}

	//----------------------------------------------------------------//
	public static void login ( String [] permissions ) {

		MoaiLog.i("MoaiFacebook: login");

		if ( permissions == null ) {
			ArrayList<String> permissions = new ArrayList<String>();
			permissions.add ( "public_profile" );
		}

		LoginManager.getInstance().logInWithReadPermissions ( sActivity, permissions );
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
	public static boolean restoreSession () {

		MoaiLog.i ( "MoaiFacebook: restoreSession" );

		return false;
	}

	//----------------------------------------------------------------//
	public static boolean sendGameRequest ( String message, String actionType, String objectId, String filters, String [] recipients, String [] suggestions, int ref ) {

		GameRequestContent.Builder builder = new GameRequestContent.Builder ();

		builder.setMessage 		( message );
		builder.setActionType 	( GameRequestContent.ActionType.valueOf ( actionType ));
		builder.setObjectId 	( objectId );
		builder.setFilters 		( GameRequestContent.Filters.valueOf ( filters ));
		builder.setRecipients 	( recipients );
		builder.setSuggestions 	( suggestions );

		// Looks like callback is not bound to concrete GameRequestDialog instance, but is looked up by REQUEST_CODE.
		// Therefore, there is no point in spawning different GameRequestDialogs, 
		// the way to go is using single instance and callback manager as in tutorial code.
		// Here we remember the last Lua callback ref in class variable to be used later from FB dialog callback.
		sGameRequestCallbackRef = ref;
		sGameRequestDialog.show ( builder.build ());
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