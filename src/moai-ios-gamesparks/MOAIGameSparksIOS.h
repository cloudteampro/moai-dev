//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIGAMESPARKSIOS_H
#define	MOAIGAMESPARKSIOS_H

#include <moai-core/headers.h>

#import <GS.h>
#import <GSAPI.h>

//================================================================//
// MOAIGameSparksIOS
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
	@const	ON_CHANGE_USER_DETAILS_FAIL
	@const	ON_CHANGE_USER_DETAILS_SUCCESS
	@const	ON_DEVICE_AUTHENTICATE_FAIL
	@const	ON_DEVICE_AUTHENTICATE_SUCCESS
	@const	ON_FACEBOOK_CONNECT_FAIL
	@const	ON_FACEBOOK_CONNECT_SUCCESS
	@const	ON_GET_ACCOUNT_DETAILS_FAIL
	@const	ON_GET_ACCOUNT_DETAILS_SUCCESS
	@const	ON_LOG_EVENT_FAIL
	@const	ON_LOG_EVENT_SUCCESS
	@const	ON_REGISTRATION_FAIL
	@const	ON_REGISTRATION_SUCCESS
*/
class MOAIGameSparksIOS :
	public MOAIGlobalClass < MOAIGameSparksIOS, MOAIGlobalEventSource > {
private:

	//----------------------------------------------------------------//
	static int	_init	 						( lua_State* L );
	static int	_requestAccountDetails			( lua_State* L );
	static int	_requestAuthentication			( lua_State* L );
	static int	_requestBuyGoods				( lua_State* L );
	static int	_requestChangeUserDetails		( lua_State* L );
	static int	_requestDeviceAuthentication	( lua_State* L );
	static int	_requestFacebookConnect			( lua_State* L );
	static int	_requestLogEvent				( lua_State* L );
	static int	_requestRegistration			( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIGameSparksIOS );

	enum {
        ON_AUTHENTICATE_FAIL,
        ON_AUTHENTICATE_SUCCESS,
		ON_AVAILABILITY,
		ON_BUY_VIRTUAL_GOOD_FAIL,
		ON_BUY_VIRTUAL_GOOD_SUCCESS,
		ON_CHANGE_USER_DETAILS_FAIL,
		ON_CHANGE_USER_DETAILS_SUCCESS,
		ON_DEVICE_AUTHENTICATE_FAIL,
		ON_DEVICE_AUTHENTICATE_SUCCESS,
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
	void	AuthenticationFailResponse				( NSString *errors );
	void	AuthenticationSuccessResponse			( NSString *authToken, NSString *displayName, bool newPlayer, NSString *userId );
	void	AvailabilityResponse					( bool available );
	void	AccountDetailsFailResponse				( NSString *errors );
	void	AccountDetailsSuccessResponse			( NSString *displayName, NSString *userId );
	void	BuyVirtualGoodFailResponse				( NSString *errors );
	void	BuyVirtualGoodSuccessResponse			( NSString *boughtItems );
	void	ChangeUserDetailsFailResponse			( NSString *errors );
	void	ChangeUserDetailsSuccessResponse		();
	void	DeviceAuthenticationFailResponse		( NSString *errors );
	void	DeviceAuthenticationSuccessResponse		( NSString *authToken, NSString *displayName, bool newPlayer, NSString *userId );
	void	FacebookConnectFailResponse				( NSString *errors );
	void	FacebookConnectSuccessResponse			( NSString *authToken, NSString *displayName, bool newPlayer, NSString *userId );
	void	LogEventFailResponse					( NSString *errors );
	void	LogEventSuccessResponse					( NSString *eventKey, NSMutableDictionary* attributes, GSLogEventResponse* request );
			MOAIGameSparksIOS						();
			~MOAIGameSparksIOS						();
	void	RegisterLuaClass						( MOAILuaState& state );
	void	RegistrationFailResponse				( NSString *errors );
	void	RegistrationSuccessResponse				( NSString *authToken, NSString *displayName, bool newPlayer, NSString *userId );
};

#endif  //MOAIGAMESPARKSIOS_H

