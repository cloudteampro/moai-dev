//
//  MoaiViewController.h
//  MOAI_imessage
//
//  Created by Vavius on 26/08/16.
//  Copyright © 2016 Vavius. All rights reserved.
//

#import <GLKit/GLKit.h>
#import <Messages/Messages.h>

@class MessagesViewController;

@interface MOAIMessagesExtension : NSObject < GLKViewControllerDelegate, GLKViewDelegate >

-( void )		moaiInit								:( CGRect )frame;
-( void )		run										:( NSString* )filename;
-( void )		pause									:( BOOL )pause;
-( void )		setWorkingDirectory						:( NSString* )path;
-( UIView* )	view;
-( UIViewController* )viewController;

+( void )		didBecomeActive							:( MessagesViewController* )vc withConversation:( MSConversation* ) conversation;
+( void )		didSelectMessage						:( MSMessage* )message;
+( void )		didReceiveMessage						:( MSMessage* )message;
+( void )		didStartSendingMessage					:( MSMessage* )message;
+( void )		didCancelSendingMessage					:( MSMessage* )message;
+( void )		didTransitionToPresentationStyle		:( MSMessagesAppPresentationStyle )presentationStyle;
+( void )		willTransitionToPresentationStyle		:( MSMessagesAppPresentationStyle )presentationStyle;
+( void )		willResignActive;

@end
