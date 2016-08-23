// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIMailDialogIOS_H
#define	MOAIMailDialogIOS_H

#import <MessageUI/MFMailComposeViewController.h>
#import <moai-core/headers.h>

@class MOAIMailComposeDelegate;

//================================================================//
// MOAIMailDialogIOS
//================================================================//
class MOAIMailDialogIOS :
	public MOAIGlobalClass < MOAIMailDialogIOS, MOAILuaObject > {
private:

	MOAIMailComposeDelegate*	mMailDelegate;

	//----------------------------------------------------------------//
	static int			_sendMail						( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIMailDialogIOS )
	
	//----------------------------------------------------------------//
						MOAIMailDialogIOS				();
						~MOAIMailDialogIOS				();
	void				RegisterLuaClass				( MOAILuaState& state );
};

//================================================================//
// MOAIMailComposeDelegate
//================================================================//
@interface MOAIMailComposeDelegate : NSObject < MFMailComposeViewControllerDelegate > {
@private
}
@end


#endif
