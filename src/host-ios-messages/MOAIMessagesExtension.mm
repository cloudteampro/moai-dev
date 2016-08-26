//
//  MoaiViewController.m
//  MOAI_imessage
//
//  Created by Vavius on 26/08/16.
//  Copyright © 2016 Vavius. All rights reserved.
//

#import <host-modules/aku_modules_ios.h>
#import <host-modules/aku_modules.h>
#import <moai-ios/host.h>
#import <moai-ios-messages/host.h>

#import "MOAIMessagesExtension.h"
#import "MOAIView.h"

//================================================================//
// MOAIMessagesExtension
//================================================================//
@interface MOAIMessagesExtension () {
	AKUContextID        mAKUContext;
	
	GLint				mWidth;
	GLint				mHeight;
	
	EAGLContext*		mEAGLContext;
	GLKViewController*	mViewController;
	MOAIView*			mMoaiView;
}

+( void ) affirmMoai;

@end

@implementation MOAIMessagesExtension

#pragma mark - AKU interface

//----------------------------------------------------------------//
+( void ) affirmMoai {
	// Thingy to call MOAIApp initialize methods only once...
	// This way it never calls finilize, but maybe it's not really needed since
	// AKU context is destroyed in MOAIView's destructor
	static dispatch_once_t onceToken;
	dispatch_once ( &onceToken, ^{
		AKUAppInitialize ();
		AKUModulesAppInitialize ();
	});
}

//----------------------------------------------------------------//
+( void ) didBecomeActive:( id )vc withConversation:( MSConversation* ) conversation {
	AKUIosMessagesNotifyActivated ( vc );
}

//----------------------------------------------------------------//
+( void ) willResignActive {
	AKUIosMessagesNotifyDeactivated ();
}

//----------------------------------------------------------------//
+( void ) didSelectMessage:( MSMessage* ) message {
	AKUIosMessagesNotifyMessageSelected ( message );
}

//----------------------------------------------------------------//
+( void ) didReceiveMessage:( MSMessage* ) message {
	AKUIosMessagesNotifyMessageReceived ( message );
}

//----------------------------------------------------------------//
+( void ) didStartSendingMessage:( MSMessage* ) message {
	AKUIosMessagesNotifyMessageStartSending ( message );
}

//----------------------------------------------------------------//
+( void ) didCancelSendingMessage:( MSMessage* ) message {
	AKUIosMessagesNotifyMessageCancelSending ( message );
}

//----------------------------------------------------------------//
+( void ) willTransitionToPresentationStyle:( MSMessagesAppPresentationStyle ) presentationStyle {
	AKUIosMessagesNotifyWillChangePresentation ( presentationStyle );
}

//----------------------------------------------------------------//
+( void ) didTransitionToPresentationStyle:( MSMessagesAppPresentationStyle ) presentationStyle {
	AKUIosMessagesNotifyDidChangePresentation ( presentationStyle );
}

#pragma mark - MOAIMessagesExtension

//----------------------------------------------------------------//
-( void ) moaiInit:( CGRect ) frame {
	
	[ MOAIMessagesExtension affirmMoai ];
	
	mEAGLContext = [[ EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 ];
	mMoaiView = [[ MOAIView alloc ] initWithFrame:frame context:mEAGLContext ];
	mMoaiView.delegate = self;
	
	mMoaiView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
	mMoaiView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
	mMoaiView.drawableStencilFormat = GLKViewDrawableStencilFormatNone;
	mMoaiView.drawableMultisample = GLKViewDrawableMultisampleNone;
	
	[ mMoaiView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight ];
	
	mViewController = [[GLKViewController alloc ] init ];
	mViewController.view = mMoaiView;
	mViewController.delegate = self;
	mViewController.preferredFramesPerSecond = 60;
	
	mAKUContext = AKUCreateContext ();
	AKUSetUserdata (( __bridge void* )self );
	
	AKUModulesContextInitialize ();
	[ mMoaiView initInputDevice ];
	AKUSetScreenDpi ([ self guessScreenDpi ]);
	
	CGFloat scale	= mMoaiView.contentScaleFactor;
	CGSize size		= mMoaiView.bounds.size;
	AKUSetScreenSize ( scale * size.width, scale * size.height );
	AKUSetViewSize ( scale * size.width, scale * size.height );
	
	[ mMoaiView bindDrawable ];
	AKUDetectGfxContext ();
}

//----------------------------------------------------------------//
-( void ) glkViewControllerUpdate:( GLKViewController* ) controller {
	
	if ( AKUCheckContext ( mAKUContext ) != 0 ) {
		return;
	}
	AKUSetContext ( mAKUContext );
	
	// not sure if there is a guarantee that AKUUpdate() don't issue gl commands (gfxResource creation?)
	//[ mMoaiView bindDrawable ];
	AKUModulesUpdate ();
}

//----------------------------------------------------------------//
-( void ) glkViewController:( GLKViewController* ) controller willPause:( BOOL ) pause {
	
	AKUModulesPause ( pause );
}

//----------------------------------------------------------------//
-( void ) glkView:( GLKView* ) view drawInRect:( CGRect ) rect {
	
	// GLKView takes care of framebuffer objects, but doesn't give any callback when it recreates them.
	// It doesn't expose OpenGL ID of the underlying framebuffer, so the only way is to query current framebuffer every frame.
	// glGetIntegerv is slow, but probably it's OK to call it once a frame
	AKUSetContext ( mAKUContext );
	
	AKUDetectFramebuffer ();
	AKURender ();
	
	//view.opaque = AKUIsGfxBufferOpaque () != 0;
}

//----------------------------------------------------------------//
-( int ) guessScreenDpi {
	
	float dpi;
	float scale = 1;
	
	if ([[ UIScreen mainScreen ] respondsToSelector:@selector ( scale )]) {
		scale = [[ UIScreen mainScreen ] scale];
	}
	if ( UI_USER_INTERFACE_IDIOM () == UIUserInterfaceIdiomPad ) {
		//Not working for iPad Mini, but appropriate solution doesn't exist yet
		dpi = 132 * scale;
	}
	else {
		dpi = 163 * scale;
	}
	return dpi;
}

//----------------------------------------------------------------//
-( void ) run :( NSString* )filename {
	
	AKUSetContext ( mAKUContext );
	AKULoadFuncFromFile ([ filename UTF8String ]);
	AKUCallFunc ();
}

//----------------------------------------------------------------//
-( void ) pause:( BOOL )pause {
	
	mViewController.paused = pause;
}

//----------------------------------------------------------------//
-( void ) setWorkingDirectory :( NSString* )path {
	
	AKUSetContext ( mAKUContext );
	AKUSetWorkingDirectory ([ path UTF8String ]);
}

//----------------------------------------------------------------//
-( UIView* ) view {
	return mViewController.view;
}

//----------------------------------------------------------------//
-( UIViewController* ) viewController {
	return mViewController;
}


@end
