/**
 * Copyright 2016 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.moaisdk.core;

import android.util.Log;

import com.google.firebase.iid.FirebaseInstanceId;
import com.google.firebase.iid.FirebaseInstanceIdService;

import com.moaisdk.facebook.MoaiFacebook;
import com.moaisdk.gamesparks.MoaiGameSparks;


public class MoaiFirebaseInstanceIDService extends FirebaseInstanceIdService {

    private static final String TAG = "MoaiLog";

    @Override
    public void onTokenRefresh () {

        try {
            String refreshedToken = FirebaseInstanceId.getInstance ().getToken ();

            Log.d ( TAG, "MoaiFirebaseInstanceIDService: Token successully refreshed" + refreshedToken );

            MoaiFacebook.setPushNotificationsRegistrationId ( refreshedToken );
            MoaiGameSparks.firebaseToken = refreshedToken;

        } catch ( Exception e ) {
            Log.e ( TAG, "MoaiFirebaseInstanceIDService: Failed to complete token refresh", e );

        }
    }
}