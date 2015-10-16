//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIFACEBOOKIOS_H
#define MOAIFACEBOOKIOS_H

#import <Foundation/Foundation.h> 
#import <moai-core/headers.h>
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>
#import <FBSDKShareKit/FBSDKShareKit.h>

@class MOAIFBGameRequestDialogDelegate;

//================================================================//
// MOAIFacebookIOS
//================================================================//
/**	@lua	MOAIFacebookIOS
	@text	Wrapper for Facebook integration on iOS devices.
			Facebook provides social integration for sharing on
			www.facebook.com. Exposed to Lua via MOAIFacebook on 
			all mobile platforms.

	@const	DIALOG_DID_COMPLETE			Event code for a successfully completed Facebook dialog.
	@const	DIALOG_DID_NOT_COMPLETE		Event code for a failed (or canceled) Facebook dialog.
	@const	SESSION_DID_LOGIN			Event code for a successfully completed Facebook login.
	@const	SESSION_DID_NOT_LOGIN		Event code for a failed (or canceled) Facebook login.
	@const	REQUEST_RESPONSE			Event code for graph request responses.
	@const	REQUEST_RESPONSE_FAILED		Event code for failed graph request responses.
*/
class MOAIFacebookIOS :
	public MOAIGlobalClass < MOAIFacebookIOS, MOAIGlobalEventSource > {
private:

	MOAILuaRefTable						mRefs;
	MOAIFBGameRequestDialogDelegate*	mGameRequestDelegate;
	
	//----------------------------------------------------------------//
	static int		_declinedPermissions		( lua_State* L );
//	static int		_extendToken				( lua_State* L );
	static int		_getExpirationDate			( lua_State* L );
	static int		_getToken					( lua_State* L );
	static int		_graphRequest				( lua_State* L );
	static int		_hasGranted					( lua_State* L );
	static int		_init						( lua_State* L );
	static int		_logEvent					( lua_State* L );
	static int		_logPurchase				( lua_State* L );
	static int		_login						( lua_State* L );
	static int		_logout						( lua_State* L );
	static int		_postToFeed					( lua_State* L );
	static int		_requestPublishPermissions	( lua_State* L );
	static int		_requestReadPermissions		( lua_State* L );
	static int		_sendGameRequest			( lua_State* L );
	static int		_sessionValid				( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIFacebookIOS );
	
	enum {
		DIALOG_DID_COMPLETE,
		DIALOG_DID_NOT_COMPLETE,
		PERMISSIONS_DENIED,
		PERMISSIONS_GRANTED,
		REQUEST_RESPONSE,
		REQUEST_RESPONSE_FAILED,
		REQUEST_DIALOG_DID_COMPLETE,
		REQUEST_DIALOG_DID_FAIL,
		REQUEST_DIALOG_DID_CANCEL,
		SESSION_DID_LOGIN,
		SESSION_DID_NOT_LOGIN,
		SESSION_EXTENDED
	};
	
	//----------------------------------------------------------------//
	void		ClearCallbackRef				( int ref );
	void		DialogDidNotComplete			();
	void		DialogDidComplete				();
	void		DialogDidComplete				( NSURL* result );
	void		GameRequestDialogDidComplete	( NSDictionary* results );
	void		GameRequestDialogDidFail		( NSError* error );
	void		GameRequestDialogDidCancel		();
	void		GraphRequestResponse			( id result, int ref );
	void		GraphRequestResponseFailure		( NSError* error, int ref );
	void		Logout							();
				MOAIFacebookIOS					();
				~MOAIFacebookIOS				();
	void		PermissionsDenied				( NSString* error );
	void		PermissionsGranted				();
	void		RegisterLuaClass				( MOAILuaState& state );
	void		SessionDidLogin					();
	void		SessionDidNotLogin				();
	void		SessionExtended					( cc8* token, cc8* expDate );
};


#endif // MOAIFACEBOOK_H
