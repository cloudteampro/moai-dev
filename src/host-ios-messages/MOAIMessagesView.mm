//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import "MOAIMessagesView.h"

#import <CoreMotion/CoreMotion.h>
#import <OpenGLES/EAGLDrawable.h>
#import <QuartzCore/QuartzCore.h>

#import <host-modules/aku_modules_ios.h>
#import <host-modules/aku_modules.h>
#import <moai-ios/host.h>
#import <moai-ios-messages/host.h>
#import <ct-util/host.h>

enum {
	MOAI_INPUT_DEVICE,
	TOTAL_INPUT_DEVICES,
};

enum {
	MOAI_TOUCH_SENSOR,
	TOTAL_SENSORS,
};

//================================================================//
// MOAIApp
//================================================================//
@interface MOAIApp : NSObject
@end

@implementation MOAIApp

+( void ) affirm {
	// Thingy to call MOAIApp initialize methods only once...
	// This way it never calls finilize, but maybe it's not really needed since
	// AKU context is destroyed in MOAIView's destructor
	static dispatch_once_t onceToken;
	dispatch_once ( &onceToken, ^{
		AKUAppInitialize ();
		AKUModulesAppInitialize ();
	});
}

@end


//================================================================//
// MOAIMessagesView ()
//================================================================//
@interface MOAIMessagesView () {

	AKUContextID        mAKUContext;
	NSTimeInterval      mAnimInterval;
	CADisplayLink*      mDisplayLink;
	
	GLint				mWidth;
	GLint				mHeight;
	
	EAGLContext*		mEAGLContext;
	
	GLuint				mFramebuffer;
	GLuint				mRenderbuffer;
	GLuint              mDepthbuffer;
	
	GLuint				mMSAAFramebuffer;
	GLuint				mMSAARenderBuffer;
	
	GLuint				mDepthBuffer;
	int					mMultisample;
}

	//----------------------------------------------------------------//
	-( void )       beginDrawing;
	-( void )       closeGraphicsContext;
	-( bool )       createBuffers;
	-( void )       createContext;
	-( void )       deleteBuffers;
	-( void )       drawView;
	-( void )       dummyFunc;
	-( void )       endDrawing;
	-( void )       handleTouches           :( NSSet* )touches :( BOOL )down;
	-( void )       openGraphicsContext;
	-( void )       onUpdateAnim;
	-( void )       releaseContext;
	-( void )       renewContext;
	-( void )		render;
	-( BOOL )       sizeChanged;
	-( void )       startAnimation;
	-( void )       stopAnimation;
@end

//================================================================//
// MOAIMessagesView
//================================================================//
@implementation MOAIMessagesView

	@dynamic multisample;
	@dynamic multisampleEnabled;

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

	//----------------------------------------------------------------//
	-( void ) beginDrawing {
	
		[self openGraphicsContext];
		[self bindFramebuffer];
	}

	//----------------------------------------------------------------//
	- (void) bindFramebuffer {

		if ([ self multisampleEnabled ]) {
			// draw into multisample buffer
			glBindFramebufferOES ( GL_FRAMEBUFFER_OES, mMSAAFramebuffer );
		}
		else {
			glBindFramebufferOES ( GL_FRAMEBUFFER_OES, mFramebuffer );
		}
	}

	//----------------------------------------------------------------//
	-( void ) closeGraphicsContext {
	
		if ([ EAGLContext currentContext ] == mEAGLContext ) {
			[ EAGLContext setCurrentContext:nil ];
		}
	}

	//----------------------------------------------------------------//
	-( bool ) createBuffers {
		
		mWidth = 0;
		mHeight = 0;
		
		// layer is empty at the moment, framebuffer creation will fail.
		// buffers will be recreated in the -(void)layoutSubviews call
		if ( CGRectIsEmpty ( self.layer.bounds )) {
			return false;
		}
		
		// set us up the frame buffers
		glGenFramebuffersOES(1, &mFramebuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, mFramebuffer);
		
		glGenRenderbuffersOES(1, &mRenderbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, mRenderbuffer);
		
		[ mEAGLContext renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer ];
		glGetRenderbufferParameterivOES ( GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &mWidth );
		glGetRenderbufferParameterivOES ( GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &mHeight );
		
		glFramebufferRenderbufferOES ( GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, mRenderbuffer );

		// check OK
		if (glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
			NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
			return false;
		}

		// set us up the msaa buffers
		if ([self multisampleEnabled]) {
			glGenFramebuffersOES ( 1 , &mMSAAFramebuffer );
			glBindFramebufferOES ( GL_FRAMEBUFFER_OES, mMSAAFramebuffer );
		
			glGenRenderbuffersOES ( 1, &mMSAARenderBuffer );
			glBindRenderbufferOES ( GL_RENDERBUFFER_OES, mMSAARenderBuffer );

			glRenderbufferStorageMultisampleAPPLE ( GL_RENDERBUFFER_OES, self.multisample, GL_RGBA4_OES, mWidth, mHeight );
			glFramebufferRenderbufferOES ( GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, mMSAARenderBuffer);
		}

		glGenRenderbuffersOES ( 1, &mDepthBuffer );
		glBindRenderbufferOES ( GL_RENDERBUFFER_OES, mDepthBuffer );
		
		// set us up the depth buffer
		if ([self multisampleEnabled]) {
			glRenderbufferStorageMultisampleAPPLE ( GL_RENDERBUFFER_OES, self.multisample, GL_DEPTH_COMPONENT16_OES, mWidth, mHeight );
		}
		else {
			glRenderbufferStorageOES ( GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, mWidth, mHeight );
		}
		
		glFramebufferRenderbufferOES ( GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, mDepthBuffer );

		// check OK
		if ( glCheckFramebufferStatusOES ( GL_FRAMEBUFFER_OES ) != GL_FRAMEBUFFER_COMPLETE_OES ) {
			NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES ( GL_FRAMEBUFFER_OES ));
			return false;
		}
		
		// Using full physical screen size, however the view never occupies it entirely
		CGRect screenRect = [[ UIScreen mainScreen ] bounds ];
		CGFloat scale = [[ UIScreen mainScreen ] scale ];
		CGFloat screenWidth = screenRect.size.width * scale;
		CGFloat screenHeight = screenRect.size.height * scale;
		
		[ self bindFramebuffer ];
		
		AKUSetScreenSize ( screenWidth, screenHeight );
		AKUSetViewSize ( mWidth, mHeight );
		AKUDetectFramebuffer ();
		
		return true;
	}

	//----------------------------------------------------------------//
	-( void ) createContext {
		
		// Get the layer
		CAEAGLLayer* glLayer = ( CAEAGLLayer* )self.layer;
		
		glLayer.opaque = YES;
		glLayer.drawableProperties = @{
			kEAGLDrawablePropertyRetainedBacking:[NSNumber numberWithBool:NO],
			kEAGLDrawablePropertyColorFormat:kEAGLColorFormatRGBA8, // kEAGLColorFormatRGB565 or kEAGLColorFormatRGBA8
		};
		
		glLayer.contentsScale = [[ UIScreen mainScreen ] scale ];
		
		mEAGLContext = [[ EAGLContext alloc ] initWithAPI:kEAGLRenderingAPIOpenGLES2 ];
		assert ( mEAGLContext );

		[ self openGraphicsContext ];
		AKUDetectGfxContext ();
	}

	//----------------------------------------------------------------//
	-( void ) dealloc {
		
		AKUDeleteContext ( mAKUContext );
		[ self releaseContext ];
	}

	//----------------------------------------------------------------//
	- ( void ) deleteBuffers {

		if ( mFramebuffer ) {
			glDeleteFramebuffersOES ( 1, &mFramebuffer );
			mFramebuffer = 0;
		}
		
		if ( mRenderbuffer ) {
			glDeleteRenderbuffersOES ( 1, &mRenderbuffer );
			mRenderbuffer = 0;
		}
		
		if ( mMSAAFramebuffer ) {
			glDeleteFramebuffersOES ( 1, &mMSAAFramebuffer );
			mMSAAFramebuffer = 0;
		}
		
		if (mMSAARenderBuffer ) {
			glDeleteRenderbuffersOES ( 1, &mMSAARenderBuffer );
			mMSAARenderBuffer = 0;
		}
		
		if ( mDepthBuffer ) {
			glDeleteRenderbuffersOES ( 1, &mDepthBuffer );
			mDepthBuffer = 0;
		}
	}

	//----------------------------------------------------------------//
	-( void ) drawView {
		
		self.opaque = AKUIsGfxBufferOpaque () != 0;
		
		[ self beginDrawing ];
		
		AKUSetContext ( mAKUContext );
		AKURender ();

		[ self endDrawing ];
	}
	
	//----------------------------------------------------------------//
	-( void ) dummyFunc {
		//dummy to fix weird input bug
	}

	//----------------------------------------------------------------//
	-( void ) endDrawing {
		
		if ([ self multisampleEnabled ]) {
			// resolve multisample buffer
			glBindFramebufferOES ( GL_READ_FRAMEBUFFER_APPLE, mMSAAFramebuffer );
			glBindFramebufferOES ( GL_DRAW_FRAMEBUFFER_APPLE, mFramebuffer );
			glResolveMultisampleFramebufferAPPLE ();
				
			GLenum attachments [] = { GL_COLOR_ATTACHMENT0_OES, GL_DEPTH_ATTACHMENT_OES };
			glDiscardFramebufferEXT ( GL_READ_FRAMEBUFFER_APPLE, 1, attachments );
		}
			
		// finish & present
		glBindRenderbufferOES ( GL_RENDERBUFFER_OES, mRenderbuffer );
		[ mEAGLContext presentRenderbuffer:GL_RENDERBUFFER_OES ];

		[ self closeGraphicsContext ]; // do not remove this
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
	-( void ) handleTouches :( NSSet* )touches :( BOOL )down {
	
		for ( UITouch* touch in touches ) {
			
			CGPoint p = [ touch locationInView:self ];
			
			AKUEnqueueTouchEvent (
				MOAI_INPUT_DEVICE,
				MOAI_TOUCH_SENSOR,
				( int )( long ) touch, // use the address of the touch as a unique id
				down,
				p.x * [[ UIScreen mainScreen ] scale ],
				p.y * [[ UIScreen mainScreen ] scale ]
			);
		}
	}

	//----------------------------------------------------------------//
	-( id ) initWithCoder:(NSCoder*)aDecoder
	{
		// make sure to do self init here
		if ( self = [ self init ]) {
			mMultisample = 1;
		}
		return self;
	}

	//----------------------------------------------------------------//
	+( BOOL ) isSystemVersionLessThan :( NSString* )version {

		return ([[[ UIDevice currentDevice ] systemVersion ] compare:version options:NSNumericSearch ] == NSOrderedAscending );
	}

	//----------------------------------------------------------------//
	// You must implement this method
	+( Class ) layerClass {
		return [ CAEAGLLayer class ];
	}

	//----------------------------------------------------------------//
	-( void ) layoutSubviews {
	
		// It is necessary to call super here
		[ super layoutSubviews ];
		
		if (( mEAGLContext != nil ) && ([ self sizeChanged ])) {
			[ self openGraphicsContext ];
			[ self deleteBuffers ];
			[ self createBuffers ];
			
			//if ( mRedrawOnSizeChange ) {
			//	// trying to achieve smooth transition between compact and expanded styles.
		//		// best way is to redraw when going larger and NOT drawing when collapsing
		//		CGSize size = self.layer.bounds.size;
		//		NSLog ( @"%f, %f", size.width, size.height );
		//		mRedrawOnSizeChange = NO;
		//		[ self onUpdateAnim ];
		//	}
		}
	}

	//----------------------------------------------------------------//
	-( void ) moaiInit {
		[self moaiInitWithMultisample:1 ];
	}

	//----------------------------------------------------------------//
	-( void ) moaiInitWithMultisample :( int )multisample {
	
		NSAssert ((( multisample == 1 ) || ( multisample == 4 )), @"Invalid multisample" );
		
		[ MOAIApp affirm ];
		mMultisample = multisample;
		
		if ( AKUCheckContext ( mAKUContext ) == 0 ) {
			[ self releaseContext ];
			AKUDeleteContext ( mAKUContext );
		}
		
		mAKUContext = AKUCreateContext ();
		AKUSetUserdata (( __bridge void* )self );
		
		AKUModulesContextInitialize ();
		
		AKUSetInputConfigurationName ( "iPhone" );

		AKUReserveInputDevices			( TOTAL_INPUT_DEVICES );
		AKUSetInputDevice				( MOAI_INPUT_DEVICE, "device" );
		
		AKUReserveInputDeviceSensors	( MOAI_INPUT_DEVICE, TOTAL_SENSORS );
		AKUSetInputDeviceTouch			( MOAI_INPUT_DEVICE, MOAI_TOUCH_SENSOR,		"touch" );
				
		AKUSetScreenDpi ([ self guessScreenDpi ]);
		
		[ self renewContext ];
		
		mAnimInterval = 1; // 1 for 60fps, 2 for 30fps
		[ self closeGraphicsContext ];
	}

	//----------------------------------------------------------------//
	-( int ) multisample {
		return mMultisample;
	}

	//----------------------------------------------------------------//
	-( BOOL ) multisampleEnabled {
		return mMultisample > 1;
	}
	
	//----------------------------------------------------------------//
	-( void ) openGraphicsContext {
		
		if ([ EAGLContext currentContext ] != mEAGLContext ) {
			[ EAGLContext setCurrentContext:mEAGLContext ];
		}
	}

	//----------------------------------------------------------------//
	-( void ) onUpdateAnim {
		
		if ( AKUCheckContext ( mAKUContext ) != 0 ) {
			return;
		}

		AKUSetContext ( mAKUContext );
		AKUModulesUpdate ();
		
		[ self render ];
		
		//sometimes the input handler will get 'locked out' by the render, this will allow it to run
		[ self performSelector:@selector( dummyFunc ) withObject:self afterDelay: 0 ];
	}
	
	//----------------------------------------------------------------//
	-( void ) pause :( BOOL )paused {
	
		AKUModulesPause ( paused );
	
		if ( paused ) {
			[ self stopAnimation ];
		}
		else {
			[ self startAnimation ];
		}
	}

	//----------------------------------------------------------------//
	-( void ) releaseContext {
	
		[ self closeGraphicsContext ];
	
		if ( mEAGLContext != nil ) {
			[ self openGraphicsContext ];
			[ self deleteBuffers ];
			[ self closeGraphicsContext ];
		}
		mEAGLContext = nil;
	}

	//----------------------------------------------------------------//
	-( void ) renewContext {
		
		if ( !mEAGLContext ) {
			[ self createContext ];
			[ self openGraphicsContext ];
			[ self createBuffers ];
		}
	}

	//----------------------------------------------------------------//
	-( void ) render {
		
		self.opaque = AKUIsGfxBufferOpaque () != 0;
		
		[ self beginDrawing ];
		AKUSetContext ( mAKUContext );
		AKURender ();
		[ self endDrawing ];
	}

	//----------------------------------------------------------------//
	-( void ) run :( NSString* )filename {
	
		AKUSetContext ( mAKUContext );
		AKULoadFuncFromFile ([ filename UTF8String ]);
		AKUCallFunc ();
	}

	//----------------------------------------------------------------//
	-( void ) setWorkingDirectory :( NSString* )path {
	
		AKUSetContext ( mAKUContext );
		AKUSetWorkingDirectory ([ path UTF8String ]);
	}

	//----------------------------------------------------------------//
	-( BOOL ) sizeChanged {
		
		float scale = [ self contentScaleFactor ];
		CGSize size = self.layer.bounds.size;
		return (( mWidth != ( GLint )( size.width * scale )) || ( mHeight != ( GLint )( size.height * scale )));
	}

	//----------------------------------------------------------------//
	-( void ) startAnimation {
		
		if ( !mDisplayLink ) {
			CADisplayLink* aDisplayLink = [[ UIScreen mainScreen ] displayLinkWithTarget:self selector:@selector( onUpdateAnim )];
			[ aDisplayLink setFrameInterval:mAnimInterval ];
			[ aDisplayLink addToRunLoop:[ NSRunLoop currentRunLoop ] forMode:NSRunLoopCommonModes ]; // or NSRunLoopCommonModes
			mDisplayLink = aDisplayLink;
		}
	}

	//----------------------------------------------------------------//
	-( void ) stopAnimation {

		[ mDisplayLink invalidate ];
		mDisplayLink = nil;
	}

	//----------------------------------------------------------------//
	-( void )touchesBegan:( NSSet* )touches withEvent:( UIEvent* )event {
		( void )event;
		
		[ self handleTouches :touches :YES ];
	}
	
	//----------------------------------------------------------------//
	-( void )touchesCancelled:( NSSet* )touches withEvent:( UIEvent* )event {
		( void )touches;
		( void )event;
		
		AKUEnqueueTouchEventCancel ( MOAI_INPUT_DEVICE, MOAI_TOUCH_SENSOR );
	}
	
	//----------------------------------------------------------------//
	-( void )touchesEnded:( NSSet* )touches withEvent:( UIEvent* )event {
		( void )event;
		
		[ self handleTouches :touches :NO ];
	}

	//----------------------------------------------------------------//
	-( void )touchesMoved:( NSSet* )touches withEvent:( UIEvent* )event {
		( void )event;
		
		[ self handleTouches :touches :YES ];
	}
	
@end
