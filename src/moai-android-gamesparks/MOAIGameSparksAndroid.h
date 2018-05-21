// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIGAMESPARKSANDROID_H
#define	MOAIGAMESPARKSANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIGameSparksAndroid
//================================================================//
/**	@lua	MOAIGameSparksAndroid
	@text	Wrapper for GameSparks integration on Android devices.
			GameSparks - BaaS(backend-as-a-service) – platform with
			cloud storage and API. 
			Exposed to Lua via MOAIGameSparks on all mobile platforms.

	@const	ON_AUTHENTICATE_FAIL
	@const	ON_AUTHENTICATE_SUCCESS
	@const	ON_AVAILABILITY
	@const	ON_BUY_VIRTUAL_GOOD_FAIL
	@const	ON_BUY_VIRTUAL_GOOD_SUCCESS
	@const	ON_FACEBOOK_CONNECT_FAIL
	@const	ON_FACEBOOK_CONNECT_SUCCESS
	@const	ON_GET_ACCOUNT_DETAILS_FAIL
	@const	ON_GET_ACCOUNT_DETAILS_SUCCESS
	@const	ON_LOG_EVENT_FAIL
	@const	ON_LOG_EVENT_SUCCESS
	@const	ON_REGISTRATION_FAIL
	@const	ON_REGISTRATION_SUCCESS
*/
class MOAIGameSparksAndroid :
	public MOAIGlobalClass < MOAIGameSparksAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

	jmethodID	mJava_Init;
	jmethodID	mJava_RequestAccountDetails;
	jmethodID	mJava_RequestAuthentication;
	jmethodID	mJava_RequestBuyGoods;
	jmethodID	mJava_RequestFacebookConnect;
	jmethodID	mJava_RequestLogEvent;
	jmethodID	mJava_RequestRegistration;

	//----------------------------------------------------------------//
	static int	_init	 					( lua_State* L );
	static int	_requestAccountDetails		( lua_State* L );
	static int	_requestAuthentication		( lua_State* L );
	static int	_requestBuyGoods			( lua_State* L );
	static int	_requestFacebookConnect		( lua_State* L );
	static int	_requestLogEvent			( lua_State* L );
	static int	_requestRegistration		( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGameSparksAndroid );

	enum {
        ON_AUTHENTICATE_FAIL,
        ON_AUTHENTICATE_SUCCESS,
		ON_AVAILABILITY,
		ON_BUY_VIRTUAL_GOOD_FAIL,
		ON_BUY_VIRTUAL_GOOD_SUCCESS,
		ON_FACEBOOK_CONNECT_FAIL,
		ON_FACEBOOK_CONNECT_SUCCESS,
        ON_GET_ACCOUNT_DETAILS_FAIL,
		ON_GET_ACCOUNT_DETAILS_SUCCESS,
		ON_LOG_EVENT_FAIL,
        ON_LOG_EVENT_SUCCESS,
        ON_REGISTRATION_FAIL,
		ON_REGISTRATION_SUCCESS
	};

	//----------------------------------------------------------------//
	void	AuthenticationFailResponse		( cc8* error );
	void	AuthenticationSuccessResponse	( cc8* authToken, cc8* displayName, bool newPlayer, cc8* userId );
	void	AvailabilityResponse			( bool available );
	void	AccountDetailsFailResponse		( cc8* error );
	void	AccountDetailsSuccessResponse	( cc8* displayName, cc8* userId );
	void	BuyVirtualGoodFailResponse		( cc8* error );
	void	BuyVirtualGoodSuccessResponse	( cc8* boughtItems );
	void	FacebookConnectFailResponse		( cc8* error );
	void	FacebookConnectSuccessResponse	( cc8* authToken, cc8* displayName, bool newPlayer, cc8* userId );
	void	LogEventFailResponse			( cc8* error );
	void	LogEventSuccessResponse			( cc8* eventKey, cc8* attributes );
			MOAIGameSparksAndroid			();
			~MOAIGameSparksAndroid			();
	void	RegisterLuaClass				( MOAILuaState& state );
	void	RegistrationFailResponse		( cc8* error );
	void	RegistrationSuccessResponse		( cc8* authToken, cc8* displayName, bool newPlayer, cc8* userId );
};

#endif  //MOAIGAMESPARKSANDROID_H

