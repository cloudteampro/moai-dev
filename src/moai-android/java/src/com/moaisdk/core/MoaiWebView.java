//----------------------------------------------------------------//
// Copyright (c) 2010-2013 Zipline Games, Inc.
// All Rights Reserved.
// http://getmoai.com
//----------------------------------------------------------------//

package com.moaisdk.core;

import android.app.Activity;
import android.content.Intent;
import android.content.Context;
import android.graphics.Color;
import android.net.MailTo;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.webkit.WebChromeClient;
import android.widget.Button;
import android.widget.RelativeLayout;

//================================================================//
// MoaiBrowser
//================================================================//
public class MoaiWebView {
    private static Activity sActivity = null;
    private static boolean isHidden = true;
    private static boolean isLoading = false;
    private static RelativeLayout webViewCont;
    private static WebView webView;

    //----------------------------------------------------------------//
    private static class MoaiWebViewClient extends WebViewClient {

        //----------------------------------------------------------------//
        public void onPageStarted ( WebView view, String url ) {
            isLoading = true;
        }

        //----------------------------------------------------------------//
        public void onPageFinished ( WebView view, String url ) {
            isLoading = false;
        }

        //----------------------------------------------------------------//
        @Override
        public boolean shouldOverrideUrlLoading ( WebView view, String url ) {

            if ( url.startsWith ( "mailto:" )) {

                if ( sActivity != null ) {
                    MailTo mt = MailTo.parse ( url );
                    Intent intent = sendMailIntent ( sActivity, mt.getTo (), mt.getSubject (), mt.getBody (), mt.getCc ());
                    sActivity.startActivity ( intent );
                    view.reload ();
                    return true;
                }
            }
            else {
                view.loadUrl ( url );
            }
            return true;
        }

        //----------------------------------------------------------------//
        private Intent sendMailIntent ( Context context, String address, String subject, String body, String cc ) {
            Intent intent = new Intent ( Intent.ACTION_SEND );
            intent.putExtra ( Intent.EXTRA_EMAIL, new String[] { address });
            intent.putExtra ( Intent.EXTRA_TEXT, body );
            intent.putExtra ( Intent.EXTRA_SUBJECT, subject );
            intent.putExtra ( Intent.EXTRA_CC, cc );
            intent.setType ( "message/rfc822" );
            return intent;
        }
    }

    //----------------------------------------------------------------//
    public static void onCreate ( Activity activity ) {
        sActivity = activity;
        webViewCont = new RelativeLayout ( sActivity );

        RelativeLayout.LayoutParams rl = new RelativeLayout.LayoutParams ( RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT );
        webViewCont.setLayoutParams ( rl );
        webViewCont.setPadding( 20, 20, 20, 20 );
        
        webView = new WebView ( sActivity );
        webView.setId ( 0X100 );
        webView.setScrollContainer ( false );

        android.widget.RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams ( RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT );
        params.addRule ( RelativeLayout.ALIGN_PARENT_BOTTOM );

        // Very ugly
        Button b = new Button( sActivity );
        b.setId ( 0X101 );
        b.setText ( "X" );
        b.setTextSize ( 24 );
        b.setBackgroundColor ( Color.TRANSPARENT );
        b.setLayoutParams ( new RelativeLayout.LayoutParams ( RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT ));
        b.setOnClickListener ( new View.OnClickListener() {
            public void onClick ( View v ) {

               hide ();
            }
        });
        android.widget.RelativeLayout.LayoutParams paramsbut = ( RelativeLayout.LayoutParams ) b.getLayoutParams ();
        paramsbut.addRule ( RelativeLayout.ALIGN_PARENT_RIGHT );
        paramsbut.addRule ( RelativeLayout.ALIGN_TOP, webView.getId () );
        webViewCont.addView ( webView, params );
        webViewCont.addView ( b, paramsbut );

        webView.setWebChromeClient ( new WebChromeClient ());
        webView.setWebViewClient ( new MoaiWebViewClient ());
        webView.getSettings ().setJavaScriptEnabled ( true );

        LinearLayoutIMETrap con = MoaiKeyboard.getContainer ();
        con.addView ( webViewCont );
        webViewCont.setVisibility ( View.GONE );
    }

    //----------------------------------------------------------------//
    public static boolean onBackPressed () {

        if ( webViewCont.getVisibility () == View.VISIBLE ) {
            hide ();
            return true;
        }
        return false;
    }

    //----------------------------------------------------------------//
    public static boolean canGoBack () {

        return webView.canGoBack ();
    }

    //----------------------------------------------------------------//
    public static boolean canGoForward () {

        return webView.canGoForward ();
    }

    //----------------------------------------------------------------//
    public static void clickBack () {

        webView.goBack ();
    }
    
    //----------------------------------------------------------------//
    public static void clickForward () {

        webView.goForward ();
    }

    //----------------------------------------------------------------//
    public static void clickRefresh () {

        webView.reload ();
    }
    
    //----------------------------------------------------------------//
    public static void clickStop () {

        webView.stopLoading ();
    }
    
    //----------------------------------------------------------------//
    public static void hide () {

        clickStop ();
        isHidden = true;
        webViewCont.setVisibility ( View.GONE );
    }
    
    //----------------------------------------------------------------//
    public static boolean isHidden () {

        return isHidden;
    }
    
    //----------------------------------------------------------------//
    public static boolean isLoading () {

        return isLoading;
    }
    
    //----------------------------------------------------------------//
    public static void loadHTML ( String html ) {
        
        webView.loadDataWithBaseURL ( "", html, "text/html", "UTF-8", "" );
    }
    
    //----------------------------------------------------------------//
    public static void loadRequest ( String url ) {

        webView.loadUrl ( url );
    }

    //----------------------------------------------------------------//
    public static void show () {

        isHidden = false;
        webViewCont.setVisibility ( View.VISIBLE );
    }
}
