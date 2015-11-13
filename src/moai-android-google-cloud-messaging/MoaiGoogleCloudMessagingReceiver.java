package com.ziplinegames.moai;

import android.content.Context;

import com.google.android.gcm.GCMBroadcastReceiver;

public class MoaiGoogleCloudMessagingReceiver extends GCMBroadcastReceiver {

	@Override
	protected String getGCMIntentServiceClassName ( Context context ) { 
		return "com.ziplinegames.moai.MoaiGoogleCloudMessagingIntentService"; 
	} 
}