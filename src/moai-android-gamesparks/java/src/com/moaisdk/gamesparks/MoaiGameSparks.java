//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.gamesparks;

import com.gamesparks.sdk.api.autogen.GSResponseBuilder;
import com.moaisdk.core.Moai;
import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;

import com.gamesparks.sdk.*;
import com.gamesparks.sdk.android.*;
//import com.gamesparks.sdk.api.GSData;
//import com.gamesparks.sdk.api.autogen.GSResponseBuilder;
import com.gamesparks.sdk.api.autogen.GSRequestBuilder.LogEventRequest;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.AuthenticationResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.AccountDetailsResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.BuyVirtualGoodResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.ChangeUserDetailsResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.LogEventResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.PushRegistrationResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.RegistrationResponse;
import com.gamesparks.sdk.api.autogen.GSTypes.*;

import com.google.firebase.iid.FirebaseInstanceId;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;
import java.util.Set;

//================================================================//
// MoaiGameSparks
//================================================================//
public class MoaiGameSparks {

	public static String firebaseToken = null;

	private static Activity sActivity = null;

	private static boolean paused = false;

	protected static native void AKUAuthenticationFailResponse 				( String errors );
	protected static native void AKUAuthenticationSuccessResponse 			( String authToken, String displayName, boolean newPlayer, String userId );
	protected static native void AKUAvailabilityResponse 					( boolean available );
	protected static native void AKUAccountDetailsFailResponse 				( String errors );
	protected static native void AKUAccountDetailsSuccessResponse 			( String displayName, String userId );
	protected static native void AKUBuyVirtualGoodFailResponse 				( String errors );
	protected static native void AKUBuyVirtualGoodSuccessResponse 			( String boughtItems );
	protected static native void AKUChangeUserDetailsFailResponse 			( String errors );
	protected static native void AKUChangeUserDetailsSuccessResponse 		();
	protected static native void AKUDeviceAuthenticationFailResponse 		( String errors );
	protected static native void AKUDeviceAuthenticationSuccessResponse 	( String authToken, String displayName, boolean newPlayer, String userId );
	protected static native void AKUFacebookConnectFailResponse 			( String errors );
	protected static native void AKUFacebookConnectSuccessResponse 			( String authToken, String displayName, boolean newPlayer, String userId );
	protected static native void AKULogEventFailResponse 					( String errors );
	protected static native void AKULogEventSuccessResponse 				( String eventKey, String attributes );
	protected static native void AKUPushRegistrationFailResponse 			( String errors );
	protected static native void AKUPushRegistrationSuccessResponse 		( String registrationId );
	protected static native void AKURegistrationFailResponse 				( String errors );
	protected static native void AKURegistrationSuccessResponse 			( String authToken, String displayName, boolean newPlayer, String userId );

	//================================================================//
	// MoaiGameSparks GSEventConsumer methods
	//================================================================//

	//----------------------------------------------------------------//
	private static GSEventConsumer accountDetailsEventConsumer = new GSEventConsumer < AccountDetailsResponse >() {

		@Override
		public void onEvent ( AccountDetailsResponse accountDetailsResponse ) {

			if ( paused ) return;

			if ( !accountDetailsResponse.hasErrors ()) {

				//List<String> achievements = accountDetailsResponse.getAchievements ();
				//GSData currencies = accountDetailsResponse.getCurrencies ();
				//Long currency1 = accountDetailsResponse.getCurrency1 ();
				//Long currency2 = accountDetailsResponse.getCurrency2 ();
				//Long currency3 = accountDetailsResponse.getCurrency3 ();
				//Long currency4 = accountDetailsResponse.getCurrency4 ();
				//Long currency5 = accountDetailsResponse.getCurrency5 ();
				//Long currency6 = accountDetailsResponse.getCurrency6 ();
				String displayName = accountDetailsResponse.getDisplayName ();
				//GSData externalIds = accountDetailsResponse.getExternalIds ();
				//Location location = accountDetailsResponse.getLocation ();
				//GSData reservedCurrencies = accountDetailsResponse.getReservedCurrencies ();
				//GSData reservedCurrency1 = accountDetailsResponse.getReservedCurrency1 ();
				//GSData reservedCurrency2 = accountDetailsResponse.getReservedCurrency2 ();
				//GSData reservedCurrency3 = accountDetailsResponse.getReservedCurrency3 ();
				//GSData reservedCurrency4 = accountDetailsResponse.getReservedCurrency4 ();
				//GSData reservedCurrency5 = accountDetailsResponse.getReservedCurrency5 ();
				//GSData reservedCurrency6 = accountDetailsResponse.getReservedCurrency6 ();
				String userId = accountDetailsResponse.getUserId ();
				//GSData virtualGoods = accountDetailsResponse.getVirtualGoods ();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnAccountDetailsSuccessResponse: "+displayName+" "+userId );
					MoaiGameSparks.AKUAccountDetailsSuccessResponse ( displayName, userId );
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnAccountDetailsFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) accountDetailsResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKUAccountDetailsFailResponse ( errors );
				}
			}
		}
	};

	//----------------------------------------------------------------//
	private static GSEventConsumer authenticationEventConsumer = new GSEventConsumer < AuthenticationResponse >() {

		@Override
		public void onEvent ( AuthenticationResponse authenticationResponse ) {

			if ( paused ) return;

			if ( !authenticationResponse.hasErrors ()) {

				String authToken = authenticationResponse.getAuthToken ();
				String displayName = authenticationResponse.getDisplayName ();
				boolean newPlayer = authenticationResponse.getNewPlayer ();
				//GSData scriptData = authenticationResponse.getScriptData ();
				//Player switchSummary = authenticationResponse.getSwitchSummary ();
				String userId = authenticationResponse.getUserId ();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnAuthenticationSuccessResponse: " );
					MoaiGameSparks.AKUAuthenticationSuccessResponse ( authToken, displayName, newPlayer, userId );
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnAuthenticationFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) authenticationResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKUAuthenticationFailResponse ( errors );
				}
			}
		}
	};

	//----------------------------------------------------------------//
	private static GSEventConsumer availabityEventConsumer = new GSEventConsumer < Boolean >() {

		@Override
		public void onEvent ( Boolean available ) {

			if ( paused ) return;

			synchronized ( Moai.sAkuLock ) {

				MoaiLog.i ( "MoaiGameSparks OnAvailable: " + available );
				MoaiGameSparks.AKUAvailabilityResponse ( available );
			}
		}
	};

	//----------------------------------------------------------------//
	private static GSEventConsumer buyVirtualGoodEventConsumer = new GSEventConsumer < BuyVirtualGoodResponse >() {

		@Override
		public void onEvent ( BuyVirtualGoodResponse buyVirtualGoodResponse ) {

			if ( paused ) return;

			if ( !buyVirtualGoodResponse.hasErrors ()) {

				List < Boughtitem > boughtItems = buyVirtualGoodResponse.getBoughtItems ();
				//GSData currenciesAdded = validationResponse.getCurrenciesAdded ();
				//Long currency1Added = validationResponse.getCurrency1Added ();
				//Long currency2Added = validationResponse.getCurrency2Added ();
				//Long currency3Added = validationResponse.getCurrency3Added ();
				//Long currency4Added = validationResponse.getCurrency4Added ();
				//Long currency5Added = validationResponse.getCurrency5Added ();
				//Long currency6Added = validationResponse.getCurrency6Added ();
				//Long currencyConsumed = validationResponse.getCurrencyConsumed ();
				//String currencyShortCode = validationResponse.getCurrencyShortCode ();
				//Integer currencyType = validationResponse.getCurrencyType ();
				//List < String > invalidItems = validationResponse.getInvalidItems ();
				//GSData scriptData = validationResponse.getScriptData ();
				//List < String > transactionIds = validationResponse.getTransactionIds ();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnPurchaseValidationSuccessResponse: " );

					JSONArray jsonArray = new JSONArray ();
					for ( Boughtitem boughtitem : boughtItems ) {
						JSONObject jsonObject = new JSONObject ();
						try {
							jsonObject.put ( "shortCode", boughtitem.getShortCode ());
							jsonObject.put ( "quantity", boughtitem.getQuantity ());
							jsonArray.put ( jsonObject );
						} catch ( JSONException e ) {
							e.printStackTrace ();
						}
					}
					MoaiGameSparks.AKUBuyVirtualGoodSuccessResponse ( jsonArray.toString ());
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnPurchaseValidationFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) buyVirtualGoodResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKUBuyVirtualGoodFailResponse ( errors );
				}
			}
		}
	};

	//----------------------------------------------------------------//
	private static GSEventConsumer changeUserDetailsEventConsumer = new GSEventConsumer < ChangeUserDetailsResponse >() {

		@Override
		public void onEvent ( ChangeUserDetailsResponse changeUserDetailsResponse ) {

			if ( paused ) return;

			if ( !changeUserDetailsResponse.hasErrors ()) {

				//GSData scriptData = response.getScriptData();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnChangeUserDetailsSuccessResponse: " );
					MoaiGameSparks.AKUChangeUserDetailsSuccessResponse ();
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnChangeUserDetailsFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) changeUserDetailsResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKUChangeUserDetailsFailResponse ( errors );
				}
			}
		}
	};

	//----------------------------------------------------------------//
	private static GSEventConsumer deviceAuthenticationEventConsumer = new GSEventConsumer < AuthenticationResponse >() {

		@Override
		public void onEvent ( AuthenticationResponse authenticationResponse ) {

			if ( paused ) return;

			if ( !authenticationResponse.hasErrors ()) {

				String authToken = authenticationResponse.getAuthToken ();
				String displayName = authenticationResponse.getDisplayName ();
				Boolean newPlayer = authenticationResponse.getNewPlayer ();
				//GSData scriptData = authenticationResponse.getScriptData ();
				//Player switchSummary = authenticationResponse.getSwitchSummary ();
				String userId = authenticationResponse.getUserId ();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnDeviceAuthenticationSuccessResponse: " );
					MoaiGameSparks.AKUDeviceAuthenticationSuccessResponse ( authToken, displayName, newPlayer, userId );
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnDeviceAuthenticationFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) authenticationResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKUDeviceAuthenticationFailResponse ( errors );
				}
			}
		}

	};

	//----------------------------------------------------------------//
	private static GSEventConsumer facebookConnectEventConsumer = new GSEventConsumer < AuthenticationResponse >() {

		@Override
		public void onEvent ( AuthenticationResponse authenticationResponse ) {

			if ( paused ) return;

			if ( !authenticationResponse.hasErrors ()) {

				String authToken = authenticationResponse.getAuthToken ();
				String displayName = authenticationResponse.getDisplayName ();
				Boolean newPlayer = authenticationResponse.getNewPlayer ();
				//GSData scriptData = authenticationResponse.getScriptData ();
				//Player switchSummary = authenticationResponse.getSwitchSummary ();
				String userId = authenticationResponse.getUserId ();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnFacebookConnectSuccessResponse: " );
					MoaiGameSparks.AKUFacebookConnectSuccessResponse ( authToken, displayName, newPlayer, userId );
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnFacebookConnectFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) authenticationResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKUFacebookConnectFailResponse ( errors );
				}
			}
		}
	};

	//----------------------------------------------------------------//
	private static GSEventConsumer pushRegistrationEventConsumer = new GSEventConsumer < PushRegistrationResponse >() {
	
		@Override
		public void onEvent ( PushRegistrationResponse pushRegistrationResponse ) {

			if ( paused ) return;

			if ( !pushRegistrationResponse.hasErrors ()) {

	            String registrationId = pushRegistrationResponse.getRegistrationId ();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnPushRegistrationSuccessResponse: " );
					MoaiGameSparks.AKUPushRegistrationSuccessResponse ( registrationId );
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnPushRegistrationFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) pushRegistrationResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKUPushRegistrationFailResponse ( errors );
				}
			}
		}
	};

	//----------------------------------------------------------------//
	private static GSEventConsumer registrationEventConsumer = new GSEventConsumer < RegistrationResponse >() {

		@Override
		public void onEvent ( RegistrationResponse registrationResponse ) {

			if ( paused ) return;

			if ( !registrationResponse.hasErrors ()) {

				String authToken = registrationResponse.getAuthToken ();
				String displayName = registrationResponse.getDisplayName ();
				Boolean newPlayer = registrationResponse.getNewPlayer ();
				//GSData scriptData = registrationResponse.getScriptData ();
				//Player switchSummary = registrationResponse.getSwitchSummary ();
				String userId = registrationResponse.getUserId ();

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnRegistrationSuccessResponse: " );
					MoaiGameSparks.AKURegistrationSuccessResponse ( authToken, displayName, newPlayer, userId );
				}
			} else {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnRegistrationFailResponse: " );
					org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) registrationResponse.getAttribute ( "error" );
					String errors = "UNDEFINED_ERROR";
					if ( jsonObject != null ) errors = jsonObject.toString ();
					MoaiGameSparks.AKURegistrationFailResponse ( errors );
				}
			}
		}
	};

	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {

		MoaiLog.i ( "MoaiGameSparks onCreate: Initializing GameSparks" );

		sActivity = activity;
	}

	// //----------------------------------------------------------------//
	// public static void onStart () {

	// 	MoaiLog.i ( "MoaiGameSparks onStart" );

	// 	// if (GSAndroidPlatform.gs () != null) {

	// 	// 	GSAndroidPlatform.gs ().start ();
	// 	// 	GSAndroidPlatform.gs ().setOnAvailable ( availabityEventConsumer );
	// 	// }
	// }
	
	// //----------------------------------------------------------------//
	// public static void onStop () {

	// 	MoaiLog.i ( "MoaiGameSparks: onStop" );

	// 	// GSAndroidPlatform.gs ().stop ();
	// 	// GSAndroidPlatform.gs ().setOnAvailable ( null );
	// }

	//----------------------------------------------------------------//
    public static void onDestroy() {

		MoaiLog.i ( "MoaiGameSparks: onDestroy" );
		
		// GSAndroidPlatform.gs ().stop ();
		// GSAndroidPlatform.gs ().setOnAvailable ( null );
    }

	// TODO 

	//----------------------------------------------------------------//
	public static void onPause () {
 
		MoaiLog.i ( "MoaiGameSparks: onPause" );

		paused = true;

		// GSAndroidPlatform.gs ().stop ();
		// GSAndroidPlatform.gs ().setOnAvailable ( null );
	}

	//----------------------------------------------------------------//
	public static void onResume () {
 
		MoaiLog.i ( "MoaiGameSparks: onResume" );

		paused = false;

		if ( GSAndroidPlatform.gs () != null ) {
			boolean available = GSAndroidPlatform.gs ().isAvailable ();

			MoaiLog.i ( "MoaiGameSparks: onResume " + available );
			if ( available ) {

				synchronized ( Moai.sAkuLock ) {

					MoaiLog.i ( "MoaiGameSparks OnAvailable (ON_RESUME): " + available );
					MoaiGameSparks.AKUAvailabilityResponse ( available );
				}
			}
		}

		// if ( GSAndroidPlatform.gs () != null ) {
		// 	GSAndroidPlatform.gs ().start ();
		// }
	}

	//----------------------------------------------------------------//
	public static void onStop () {

		MoaiLog.i ( "MoaiGameSparks: onStop" );
	}

	//================================================================//
	// GameSparks JNI callback methods
	//================================================================//

	//----------------------------------------------------------------//
	public static void init ( String apiKey, String apiSecret, String credential, boolean liveMode, boolean autoUpdate ) {
		
		MoaiLog.i ( "MoaiGameSparks: init" );

		GSAndroidPlatform.initialise ( sActivity, apiKey, apiSecret, credential, liveMode, autoUpdate );
		GSAndroidPlatform.gs ().setOnAvailable ( availabityEventConsumer );

		GSAndroidPlatform.gs ().start ();

		if ( !liveMode ) {

	        Intent reorderActivity = new Intent ( sActivity, sActivity.getClass ());
	        reorderActivity.setFlags ( Intent.FLAG_ACTIVITY_REORDER_TO_FRONT );
	        sActivity.startActivity ( reorderActivity );
	    }
	}

	//----------------------------------------------------------------//
	public static boolean isAvailable () {

		boolean available = false;

		if ( GSAndroidPlatform.gs () != null ) {

			available = GSAndroidPlatform.gs ().isAvailable ();
		}

		MoaiLog.i ( "MoaiGameSparks: isAvailable " + available );

		return available;
	}

	//----------------------------------------------------------------//
	public static void requestAccountDetails () {

		MoaiLog.i ( "MoaiGameSparks: requestAccountDetails" );
		GSAndroidPlatform.gs ().getRequestBuilder ().createAccountDetailsRequest ().send ( accountDetailsEventConsumer );
	}

	//----------------------------------------------------------------//
	public static void requestAuthentication ( String username, String password ) {

		MoaiLog.i ( "MoaiGameSparks: requestAuthentication" );
		GSAndroidPlatform.gs ().getRequestBuilder ().createAuthenticationRequest ()
				.setUserName ( username )
				.setPassword ( password )
				.send ( authenticationEventConsumer );
	}

	//----------------------------------------------------------------//
	public static void requestBuyGoods ( String signature, String signedData ) {

		MoaiLog.i ( "MoaiGameSparks: requestBuyGoods" );
		GSAndroidPlatform.gs ().getRequestBuilder ().createGooglePlayBuyGoodsRequest ()
				//.setCurrencyCode ( currencyCode )
				.setSignature ( signature )
				.setSignedData ( signedData )
				//.setSubUnitPrice ( subUnitPrice )
				//.setUniqueTransactionByPlayer ( uniqueTransactionByPlayer )
				.send ( buyVirtualGoodEventConsumer );
	}

	//----------------------------------------------------------------//
	public static void requestChangeUserDetails ( String displayName, String language, String newPassword, String oldPassword, String userName ) {

		MoaiLog.i ( "MoaiGameSparks: requestChangeUserDetails "+displayName+" "+language+" "+userName );
		GSAndroidPlatform.gs ().getRequestBuilder ().createChangeUserDetailsRequest ()
				.setDisplayName ( displayName )
				.setLanguage ( language )
				// .setNewPassword ( newPassword )
				// .setOldPassword (oldPassword )
				// .setUserName ( userName )
				.send ( changeUserDetailsEventConsumer );
	}

	//----------------------------------------------------------------//
	public static void requestDeviceAuthentication ( String deviceId, String deviceOS ) {

		String deviceModel = Build.MODEL;
		String deviceName = Build.DEVICE;

		MoaiLog.i ( "MoaiGameSparks: requestDeviceAuthentication" );
		GSAndroidPlatform.gs ().getRequestBuilder ().createDeviceAuthenticationRequest ()
				.setDeviceId ( deviceId )
				.setDeviceModel ( deviceModel )
				.setDeviceName ( deviceName )
				.setDeviceOS ( deviceOS )
				//.setDeviceType ( deviceType )
				//.setDisplayName ( displayName )
				//.setOperatingSystem ( operatingSystem )
				//.setSegments ( segments )
				.send ( deviceAuthenticationEventConsumer );
	}

	//----------------------------------------------------------------//
	public static void requestFacebookConnect ( String token ) {

		MoaiLog.i ( "MoaiGameSparks: requestFacebookConnect" );
		GSAndroidPlatform.gs ().getRequestBuilder ().createFacebookConnectRequest ()
				.setAccessToken ( token )
				//.setCode(code)
				//.setDoNotLinkToCurrentPlayer(doNotLinkToCurrentPlayer)
				//.setErrorOnSwitch(errorOnSwitch)
				//.setSegments(segments)
				//.setSwitchIfPossible(switchIfPossible)
				//.setSyncDisplayName(syncDisplayName)
				.send ( facebookConnectEventConsumer );
	}

	//----------------------------------------------------------------//
	public static void requestLogEvent ( final String eventKey, final Bundle attributes ) {

		MoaiLog.i ( "MoaiGameSparks: requestLogEvent " + eventKey );
		LogEventRequest logEventRequest = GSAndroidPlatform.gs ().getRequestBuilder ().createLogEventRequest ();
		logEventRequest.setEventKey ( eventKey );

		for ( String key : attributes.keySet ()) {

			String attribute = attributes.getString ( key );

			if ( !attribute.isEmpty ()) {
				logEventRequest.setEventAttribute ( key, attributes.getString ( key ));
			}
		}

		logEventRequest.send ( new GSEventConsumer < LogEventResponse > () {

			@Override
			public void onEvent ( LogEventResponse logEventResponse ) {
				
				if ( paused ) return;

				if ( !logEventResponse.hasErrors ()) {

					JSONObject json = new JSONObject ();
					for ( String key : attributes.keySet ()) {

						try {

							String attribute = logEventResponse.getScriptData ().getAttribute ( key ).toString();
							if ( attribute != null ) {
								json.put ( key, attribute );
							}
						} catch ( JSONException e ) {

						} catch ( NullPointerException e ) {
							//Handle exception here
						}
					}

					synchronized ( Moai.sAkuLock ) {

						MoaiLog.i ( "MoaiGameSparks OnLogEventSuccessResponse: " );
						AKULogEventSuccessResponse ( eventKey, json.toString ());
					}
				} else {

					synchronized ( Moai.sAkuLock ) {

						MoaiLog.i ( "MoaiGameSparks OnLogEventFailResponse: " );
						org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) logEventResponse.getAttribute ( "error" );
						String errors = "UNDEFINED_ERROR";
						if ( jsonObject != null ) errors = jsonObject.toString ();
						AKULogEventFailResponse ( errors );
					}
				}
			}
		} );
	}

	//----------------------------------------------------------------//
	public static void requestPushRegistration ( String deviceOS, String pushId ) {
		String refreshedToken = FirebaseInstanceId.getInstance ().getToken ();

		MoaiLog.i ( "MoaiGameSparks: requestPushRegistration" );
		GSAndroidPlatform.gs ().getRequestBuilder ().createPushRegistrationRequest ()
				// .setDeviceOS ( deviceOS )
				// .setPushId ( pushId )
				// .setDeviceOS ( "android" )
				.setDeviceOS ( "FCM" )
				.setPushId ( refreshedToken )
				.send ( pushRegistrationEventConsumer );
	}

	//----------------------------------------------------------------//
	public static void requestRegistration ( String displayName, String password, String userName ) {

		MoaiLog.i ( "MoaiGameSparks: requestRegistration" );
		GSAndroidPlatform.gs ().getRequestBuilder ().createRegistrationRequest ()
				.setDisplayName ( displayName )
				.setPassword ( password )
				//.setSegments ( segments )
				.setUserName ( userName )
				.send ( registrationEventConsumer );
	}
}

