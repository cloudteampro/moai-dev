//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIFIREBASEIOS_H
#define	MOAIFIREBASEIOS_H

#include <moai-core/headers.h>

#import <MessageUI/MessageUI.h>
#import <MessageUI/MFMessageComposeViewController.h>

#import <FirebaseCore/FIRApp.h>
#import <FirebaseMessaging/FirMessaging.h>
#import <FirebaseAnalytics/FirebaseAnalytics.h>
#import <FirebaseAuth/FirebaseAuth.h>
#import <FirebaseDynamicLinks/FirebaseDynamicLinks.h>
#import <FirebaseDatabase/FirebaseDatabase.h>
#import <FirebaseRemoteConfig/FirebaseRemoteConfig.h>
#import <GoogleSignIn/GoogleSignIn.h>

@class MOAIFirebaseIOSDelegate;

//================================================================//
// MOAIFirebaseIOS
//================================================================//
class MOAIFirebaseIOS :
	public MOAIGlobalClass < MOAIFirebaseIOS, MOAIGlobalEventSource > {
private:
		
	FIRRemoteConfig* 			remoteConfig;
	MOAIFirebaseIOSDelegate*	mDelegate;
	FIRDatabaseReference*   	mDatabaseRef;

	//----------------------------------------------------------------//
	static int	_init	 									( lua_State* L );
	static int	_fetchConfig	 							( lua_State* L );
	static int	_signInWithCredential	 					( lua_State* L );
	static int	_signOut	 								( lua_State* L );
	static int	_activateFetchedConfig						( lua_State* L );
	static int	_getAllKeys			 						( lua_State* L );
	static int	_getConfigString	 						( lua_State* L );
	static int	_getConfigBoolean	 						( lua_State* L );
	static int	_getConfigDouble	 						( lua_State* L );
	static int	_getConfigLong	 							( lua_State* L );
	static int	_enableAutoInitRemoteMessaging				( lua_State* L );
	static int	_createAnonymousAccountWithReferrerInfo		( lua_State* L );
	static int	_logEvent									( lua_State* L );
	static int	_showInviteSMSDialog	 					( lua_State* L );
	static int	_showInviteEmailDialog	 					( lua_State* L );
	static int	_getInvitationId	 						( lua_State* L );
	static int	_getInvitationDeepLink	 					( lua_State* L );
	static int	_createInvitationDeepLink	 				( lua_State* L );
	static int	_writeToFBDB	 							( lua_State* L );
	static int	_readFromFBDB	 							( lua_State* L );
	static int	_getValuesFromFBDB	 						( lua_State* L );
	static int	_getUserUID	 								( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIFirebaseIOS );

	enum {
		FETCH_CONFIG_SUCCEEDED,
		FETCH_CONFIG_FAILED,
		DEEPLINK_CREATED_SUCCEEDED,
		PENDING_INVITATION_ID_SUCCEEDED,
		READ_FBDB_SUCCEEDED,
		SIGNIN_WITH_CREDENTIALS_SUCCEEDED,
		SIGNIN_WITH_CREDENTIALS_FAILED,
		SIGNOUT_SUCCEEDED,
		SIGNOUT_FAILED,
	};

	NSString* _deepLink = @"";
	NSString* _invitationId = @"";
	NSString* _valuesFromFBDB = @"";
	NSString* _userUid = @"";
	
	//----------------------------------------------------------------//
					MOAIFirebaseIOS					();
					~MOAIFirebaseIOS				();
	void			RegisterLuaClass				( MOAILuaState& state );
};

//================================================================//
// MOAIFirebaseIOSDelegate
//================================================================//
@interface MOAIFirebaseIOSDelegate : NSObject < FIRMessagingDelegate, GIDSignInDelegate, MFMessageComposeViewControllerDelegate, MFMailComposeViewControllerDelegate > {
@private
}
@end

#endif  //MOAIFIREBASEIOS_H
