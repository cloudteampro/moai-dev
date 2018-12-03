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

import pro.cloudteam.nashiri.R;
import pro.cloudteam.nashiri.MoaiActivity;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.util.Log;
import java.util.Map;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;

public class MoaiFirebaseMessagingService extends FirebaseMessagingService {

    private static final String TAG = "MoaiLog";

    private static final int NOTIFY_ID = 123;

    @Override
    public void onMessageReceived(RemoteMessage remoteMessage) {

        Bundle data = new Bundle();
        for (Map.Entry<String, String> entry : remoteMessage.getData().entrySet()) {
            data.putString(entry.getKey(), entry.getValue());
        }

        Context context = this.getApplicationContext();
        Intent defaultAction = new Intent(context, MoaiActivity.class)
            .setAction(Intent.ACTION_DEFAULT)
            .putExtra("push", data);

        String title = data.getString("title");
        String body = data.getString("body");

        Log.d ( TAG, "MoaiFirebaseMessagingService: onMessageReceived " + title + " " + body );

        NotificationCompat.Builder mBuilder = new NotificationCompat.Builder(context)
            .setSmallIcon(R.drawable.notification_template_icon_bg)
            .setContentTitle(title == null ? "" : title)
            .setContentText(body == null ? "Hello world" : body)
            .setAutoCancel(true)
            .setContentIntent(PendingIntent.getActivity(
                context,
                0,
                defaultAction,
                PendingIntent.FLAG_UPDATE_CURRENT
            ));

        NotificationManager mNotificationManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        mNotificationManager.notify(NOTIFY_ID, mBuilder.build());
    }
}