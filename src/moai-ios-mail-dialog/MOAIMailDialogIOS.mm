// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#import <moai-ios-mail-dialog/MOAIMailDialogIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	sendMail
 @text	Send a mail with the passed in default values
 
 @in	string recipient
 @in	string subject
 @in	string message
 @out	nil
 */
int MOAIMailDialogIOS::_sendMail ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* recipient = state.GetValue < cc8* >( 1, "" );
	cc8* subject = state.GetValue < cc8* >( 2, "" );
	cc8* message = state.GetValue < cc8* >( 3, "" );
	
	MFMailComposeViewController* controller = [[ MFMailComposeViewController alloc ] init ];
	controller.mailComposeDelegate = MOAIMailDialogIOS::Get ().mMailDelegate;
	
	NSArray* to = [ NSArray arrayWithObject:[ NSString  stringWithUTF8String:recipient ]];
	
	[ controller setToRecipients:to ];
	[ controller setSubject:[ NSString stringWithUTF8String:subject ]];
	[ controller setMessageBody:[ NSString stringWithUTF8String:message ] isHTML:NO ]; 
	
	if ( controller ) {
				
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];	
		[ rootVC presentViewController:controller animated:YES completion:nil];
	}
	
	[controller release];
	
	return 1;
}


//================================================================//
// MOAIMailDialogIOS
//================================================================//

//----------------------------------------------------------------//
MOAIMailDialogIOS::MOAIMailDialogIOS () {

	RTTI_SINGLE ( MOAILuaObject )
	this->mMailDelegate = [[ MOAIMailComposeDelegate alloc ] init ];
}

//----------------------------------------------------------------//
MOAIMailDialogIOS::~MOAIMailDialogIOS () {

	[ this->mMailDelegate release ];
}

//----------------------------------------------------------------//
void MOAIMailDialogIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "sendMail",				_sendMail },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MOAIMailComposeDelegate
//================================================================//
@implementation MOAIMailComposeDelegate

//================================================================//
#pragma mark -
#pragma mark Protocol MOAIMailComposeDelegate
//================================================================//

-( void ) mailComposeController:( MFMailComposeViewController* )controller didFinishWithResult:( MFMailComposeResult )result error:( NSError* )error {
	UNUSED ( controller );
	UNUSED ( result );
	UNUSED ( error );

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];

	if ( rootVC ) {
		[ rootVC dismissViewControllerAnimated:YES completion:nil ];
	}
}

@end

