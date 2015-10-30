// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFACEBOOKANDROID_H
#define	MOAIFACEBOOKANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIFacebookAndroid
//================================================================//
/**	@lua	MOAIFacebookAndroid
	@text	Wrapper for Facebook integration on Android devices.
			Facebook provides social integration for sharing on
			www.facebook.com. Exposed to Lua via MOAIFacebook on
			all mobile platforms.

	@const	DIALOG_DID_COMPLETE			Event code for a successfully completed Facebook dialog.
	@const	DIALOG_DID_NOT_COMPLETE		Event code for a failed (or canceled) Facebook dialog.
	@const	REQUEST_RESPONSE			Event code for graph request responses.
	@const	REQUEST_RESPONSE_FAILED		Event code for failed graph request responses.
	@const	SESSION_DID_LOGIN			Event code for a successfully completed Facebook login.
	@const	SESSION_DID_NOT_LOGIN		Event code for a failed (or canceled) Facebook login.
*/
class MOAIFacebookAndroid :
	public MOAIGlobalClass < MOAIFacebookAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:
	
	MOAILuaRefTable			mRefs;

	jclass					mJava_AppEventsConstants;
	jclass					mJava_GameRequestActionTypeConstants;
	jclass					mJava_GameRequestFilterConstants;

	jmethodID 				mJava_GraphRequest;
	jmethodID 				mJava_HasGranted;
	jmethodID 				mJava_Init;
	jmethodID 				mJava_LogEvent;
	jmethodID 				mJava_LogPurchase;
	jmethodID 				mJava_Login;
	jmethodID 				mJava_Logout;
	jmethodID 				mJava_PostToFeed;
	jmethodID 				mJava_RequestPublishPermissions;
	jmethodID 				mJava_RequestReadPermissions;
	jmethodID 				mJava_SendGameRequest;
	jmethodID 				mJava_SessionValid;

	//----------------------------------------------------------------//
	// static int		_declinedPermissions		( lua_State* L );
	// static int		_getExpirationDate			( lua_State* L );
	// static int		_getProfile					( lua_State* L );
	// static int		_getToken					( lua_State* L );
	static int		_graphRequest				( lua_State* L );
	static int		_hasGranted					( lua_State* L );
	static int		_init						( lua_State* L );
	static int		_logEvent					( lua_State* L );
	static int		_logPurchase				( lua_State* L );
	static int		_login						( lua_State* L );
	static int		_logout						( lua_State* L );
	// static int		_postToFeed					( lua_State* L );
	static int		_requestPublishPermissions	( lua_State* L );
	static int		_requestReadPermissions		( lua_State* L );
	static int		_sendGameRequest			( lua_State* L );
	static int		_sessionValid				( lua_State* L );
	// static int		_setProfileAutoUpdate		( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIFacebookAndroid );

	enum {
		DIALOG_DID_COMPLETE,		// deprecated, never dispatched
		DIALOG_DID_NOT_COMPLETE,	// deprecated, never dispatched
		PERMISSIONS_DENIED,
		PERMISSIONS_GRANTED,
		PROFILE_UPDATED,
		REQUEST_RESPONSE,
		REQUEST_DIALOG_RESPONSE,
		SESSION_DID_LOGIN,
		SESSION_DID_NOT_LOGIN,
		SESSION_EXTENDED,
	};

	void	ClearCallbackRef				( int ref );
	void	GameRequestDialogDidComplete	( jbundle result, int ref );
	void	GameRequestDialogDidFail		( cc8* error, int ref );
	void	GraphRequestResponse			( jbundle result, int ref );
	void	GraphRequestResponseFailure		( cc8* error, int ref );
			MOAIFacebookAndroid				();
			~MOAIFacebookAndroid			();
	void	PermissionsDenied				();
	void	PermissionsGranted				();
	void	RegisterLuaClass				( MOAILuaState& state );
	void	SessionDidLogin					();
	void	SessionDidNotLogin				();
};

#endif  //MOAIFACEBOOK_H
