//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.gamesparks;

import com.moaisdk.core.Moai;
import com.moaisdk.core.MoaiLog;

import android.app.Activity;
import android.os.Bundle;

import com.gamesparks.sdk.*;
import com.gamesparks.sdk.android.*;
//import com.gamesparks.sdk.api.GSData;
//import com.gamesparks.sdk.api.autogen.GSResponseBuilder;
import com.gamesparks.sdk.api.autogen.GSRequestBuilder.LogEventRequest;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.AuthenticationResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.AccountDetailsResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.BuyVirtualGoodResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.LogEventResponse;
import com.gamesparks.sdk.api.autogen.GSResponseBuilder.RegistrationResponse;
import com.gamesparks.sdk.api.autogen.GSTypes.*;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;
import java.util.Set;

//================================================================//
// MoaiGameSparks
//================================================================//
public class MoaiGameSparks {

    private static Activity sActivity = null;

    protected static native void AKUAuthenticationFailResponse      ( String error );
    protected static native void AKUAuthenticationSuccessResponse   ( String authToken, String displayName, boolean newPlayer, String userId );
    protected static native void AKUAvailabilityResponse            ( boolean available );
    protected static native void AKUAccountDetailsFailResponse      ( String error );
    protected static native void AKUAccountDetailsSuccessResponse   ( String displayName, String userId );
    protected static native void AKUBuyVirtualGoodFailResponse      ( String error );
    protected static native void AKUBuyVirtualGoodSuccessResponse   ( String boughtItems );
    protected static native void AKUFacebookConnectFailResponse     ( String error );
    protected static native void AKUFacebookConnectSuccessResponse  ( String authToken, String displayName, boolean newPlayer, String userId );
    protected static native void AKULogEventFailResponse            ( String error );
    protected static native void AKULogEventSuccessResponse         ( String eventKey, String attributes );
    protected static native void AKURegistrationFailResponse        ( String error );
    protected static native void AKURegistrationSuccessResponse     ( String authToken, String displayName, boolean newPlayer, String userId );

    //================================================================//
    // MoaiGameSparks GSEventConsumer methods
    //================================================================//

    //----------------------------------------------------------------//
    private static GSEventConsumer accountDetailsEventConsumer = new GSEventConsumer < AccountDetailsResponse >() {

        @Override
        public void onEvent ( AccountDetailsResponse accountDetailsResponse ) {

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

                    MoaiLog.i ( "MoaiGameSparks OnAccountDetailsSuccessResponse: " );
                    MoaiGameSparks.AKUAccountDetailsSuccessResponse ( displayName, userId );
                }
            } else {

                synchronized ( Moai.sAkuLock ) {

                    MoaiLog.i ( "MoaiGameSparks OnAccountDetailsFailResponse: " );
                    org.json.simple.JSONObject jsonObject = ( org.json.simple.JSONObject ) accountDetailsResponse.getAttribute ( "error" );
                    String error = "UNDEFINED_ERROR";
                    if ( jsonObject != null ) error = jsonObject.toString ();
                    MoaiGameSparks.AKUAccountDetailsFailResponse ( error );
                }
            }
        }
    };

    //----------------------------------------------------------------//
    private static GSEventConsumer authenticationEventConsumer = new GSEventConsumer < AuthenticationResponse >() {

        @Override
        public void onEvent ( AuthenticationResponse authenticationResponse ) {

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
                    String error = "UNDEFINED_ERROR";
                    if ( jsonObject != null ) error = jsonObject.toString ();
                    MoaiGameSparks.AKUAuthenticationFailResponse ( error );
                }
            }
        }
    };

    //----------------------------------------------------------------//
    private static GSEventConsumer availabityEventConsumer = new GSEventConsumer < Boolean >() {

        @Override
        public void onEvent ( Boolean available ) {

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
                            jsonObject.put ("shortCode", boughtitem.getShortCode ());
                            jsonObject.put ("quantity", boughtitem.getQuantity ());
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
                    String error = "UNDEFINED_ERROR";
                    if ( jsonObject != null ) error = jsonObject.toString ();
                    MoaiGameSparks.AKUBuyVirtualGoodFailResponse ( error );
                }
            }
        }
    };

    //----------------------------------------------------------------//
    private static GSEventConsumer facebookConnectEventConsumer = new GSEventConsumer < AuthenticationResponse >() {

        @Override
        public void onEvent ( AuthenticationResponse authenticationResponse ) {

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
                    String error = "UNDEFINED_ERROR";
                    if ( jsonObject != null ) error = jsonObject.toString ();
                    MoaiGameSparks.AKUFacebookConnectFailResponse ( error );
                }
            }
        }
    };

    //----------------------------------------------------------------//
    private static GSEventConsumer registrationEventConsumer = new GSEventConsumer < RegistrationResponse >() {

        @Override
        public void onEvent ( RegistrationResponse registrationResponse ) {

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
                    String error = "UNDEFINED_ERROR";
                    if ( jsonObject != null ) error = jsonObject.toString ();
                    MoaiGameSparks.AKURegistrationFailResponse ( error );
                }
            }
        }
    };

    //----------------------------------------------------------------//
    public static void onStart () {

        MoaiLog.i ( "MoaiGameSparks onStart" );

        // GSAndroidPlatform.gs ().start ();
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
    public static void init ( String apiKey, String apiSecret, String credential, boolean liveMode, boolean autoUpdate ) {

        MoaiLog.i ( "MoaiGameSparks: init" );
        GSAndroidPlatform.initialise ( sActivity, apiKey, apiSecret, credential, liveMode, autoUpdate );
        GSAndroidPlatform.gs ().setOnAvailable ( availabityEventConsumer );
        
        GSAndroidPlatform.gs ().start ();
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
    public static void requestFacebookConnect ( String token ) {

        MoaiLog.i ( "MoaiGameSparks: requestFacebookConnect" );
        GSAndroidPlatform.gs ().getRequestBuilder ().createFacebookConnectRequest ()
                .setAccessToken( token )
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

        MoaiLog.i ( "MoaiGameSparks: requestLogEvent" );
        LogEventRequest logEventRequest = GSAndroidPlatform.gs ().getRequestBuilder ().createLogEventRequest();
        logEventRequest.setEventKey ( eventKey );

        for ( String key : attributes.keySet ()) {

            String attribute = attributes.getString ( key );

            if ( !attribute.isEmpty ()) {
                logEventRequest.setEventAttribute ( key, attributes.getString ( key ));
            }
        }

        logEventRequest.send ( new GSEventConsumer < LogEventResponse >() {

            @Override
            public void onEvent ( LogEventResponse logEventResponse ) {

                if ( !logEventResponse.hasErrors ()) {

                    JSONObject json = new JSONObject ();
                    for ( String key : attributes.keySet ()) {

                        try {

                            String attribute = ( String ) logEventResponse.getScriptData ().getAttribute ( key );
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
                        String error = "UNDEFINED_ERROR";
                        if ( jsonObject != null ) error = jsonObject.toString ();
                        AKULogEventFailResponse ( error );
                    }
                }
            }
        });
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

