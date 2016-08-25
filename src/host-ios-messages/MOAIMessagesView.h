//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Messages/Messages.h>

@class MessagesViewController;

//================================================================//
// MOAIMessagesView
//================================================================//
@interface MOAIMessagesView : UIView {
@private
}
	@property ( readonly, nonatomic ) int multisample;
	@property ( readonly, nonatomic ) BOOL multisampleEnabled;

	//----------------------------------------------------------------//
	+( BOOL )		isSystemVersionLessThan					:( NSString* )version;
	-( void )		moaiInit;
	-( void )		moaiInitWithMultisample					:( int )multisample; // pass 1 or 4 for multisample
	-( void )		pause									:( BOOL )paused;
	-( void )		pauseRender								:( BOOL )paused;
	-( void )		run										:( NSString* )filename;
	-( void )		scheduleRedrawOnSizeChange;
	-( void )		setWorkingDirectory						:( NSString* )path;

	+( void )		didBecomeActive							:( MessagesViewController* )vc withConversation:( MSConversation* ) conversation;
	+( void )		didSelectMessage						:( MSMessage* )message;
	+( void )		didReceiveMessage						:( MSMessage* )message;
	+( void )		didStartSendingMessage					:( MSMessage* )message;
	+( void )		didCancelSendingMessage					:( MSMessage* )message;
	+( void )		didTransitionToPresentationStyle		:( MSMessagesAppPresentationStyle )presentationStyle;
	+( void )		willTransitionToPresentationStyle		:( MSMessagesAppPresentationStyle )presentationStyle;
	+( void )		willResignActive;

@end
