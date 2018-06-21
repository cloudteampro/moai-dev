// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-gamesparks/MOAIGameSparksAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize GameSparks.
	
	@in 	string	apiKey
	@in 	string	apiSecret
	@in 	string	credential
	@in 	boolean	liveMode
	@in 	boolean	autoUpdate
	@out 	nil
*/
int	MOAIGameSparksAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString japiKey	= self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	MOAIJString japiSecret	= self->GetJString ( state.GetValue < cc8* >( 2, 0 ));
	MOAIJString jcredential	= self->GetJString ( state.GetValue < cc8* >( 3, 0 ));
	bool liveMode = state.GetValue < bool >( 4, false );
	bool autoUpdate = state.GetValue < bool >( 5, false );

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )japiKey, ( jstring )japiSecret, ( jstring )jcredential, liveMode, autoUpdate );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestAccountDetails
	@text	Request account details.
				
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestAccountDetails ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_RequestAccountDetails );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestAuthentication
	@text	Request authentication.
				
	@in 	string	password		The previously registered password
	@in 	string	username 		The previously registered player name
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestAuthentication ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString username = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString password = self->GetJString ( lua_tostring ( state, 2 ));

	self->CallStaticVoidMethod ( self->mJava_RequestAuthentication, ( jstring )username, ( jstring )password );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestBuyGoods
	@text	Request validate purchase.
				
	@opt 	string	currencyCode				The ISO 4217 currency code representing the real-world currency used for this transaction.
	@in 	string	signature 					The value obtained from data.getStringExtra("INAPP_DATA_SIGNATURE");
	@in 	string	signedData					The value obtained from data.getStringExtra("INAPP_PURCHASE_DATA")
	@opt 	int		subUnitPrice 				The price of this purchase
	@opt 	boolean	uniqueTransactionByPlayer 	boolean	If set to true, the transactionId from this receipt will not be 
												globally valdidated, this will mean replays between players are possible.
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestBuyGoods ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString signature = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString signedData = self->GetJString ( lua_tostring ( state, 2 ));

	self->CallStaticVoidMethod ( self->mJava_RequestBuyGoods, ( jstring )signature, ( jstring )signedData );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestChangeUserDetails
	@text	Request change user details.
				
	@in 	string	displayName		The new display name to set in the player data.
	@in 	string	language 		The new language code to set in the player data.
	@in 	string	newPassword		The new password to set in the player data.
	@in 	string	oldPassword 	The player's existing password. If supplied it will be checked against 
									the password stored in the player data. 
									This allows you re-authenticate the player making the change.
	@in 	string	userName 		The new userName with which this player will sign in. 
									If the player currently authenticates using device authentication this will 
									upgrade their account and require them to use 
									username and password authentication from now on.
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestChangeUserDetails ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString displayName = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString language = self->GetJString ( lua_tostring ( state, 2 ));
	MOAIJString newPassword = self->GetJString ( lua_tostring ( state, 3 ));
	MOAIJString oldPassword = self->GetJString ( lua_tostring ( state, 4 ));
	MOAIJString userName = self->GetJString ( lua_tostring ( state, 5 ));

	self->CallStaticVoidMethod ( self->mJava_RequestChangeUserDetails, ( jstring )displayName, ( jstring )language, ( jstring )newPassword, ( jstring )oldPassword, ( jstring )userName );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestDeviceAuthentication
	@text	Request device authentication.
				
	@in 	string	deviceId		A unique device identifier.
	@in 	string	deviceOS 		An indicator of the device platform, should be IOS, ANDROID, WP8 or W8
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestDeviceAuthentication ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString deviceId = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString deviceOS = self->GetJString ( lua_tostring ( state, 2 ));

	self->CallStaticVoidMethod ( self->mJava_RequestDeviceAuthentication, ( jstring )deviceId, ( jstring )deviceOS );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestFacebookConnect
	@text	Connect with Facebook.
				
	@in 	string	accessToken 				The access token is used by the client to 
												make authenticated requests on behalf of the end user.
	@opt 	string	code 						An authorization code is a short-lived token representing the user's access grant, 
												created by the authorization server and passed to the client application via the browser.
	@opt 	boolean	doNotLinkToCurrentPlayer	Indicates that the server should not try to link the external profile with the current player. 
												If false, links the external profile to the currently signed in player. 
												If true, creates a new player and links the external profile to them. Defaults to false.
	@opt 	boolean	errorOnSwitch				Indicates whether the server should return an error if an account switch would have occurred, 
												rather than switching automatically. Defaults to false.
	@opt 	JSON	segments					An optional segment configuration for this request.
	@opt 	boolean	switchIfPossible			Indicates that the server should switch to the supplied profile 
												if it isalready associated to a player. Defaults to false.
	@opt 	boolean	syncDisplayName				Indicates that the associated players displayName should be kept 
												in syn with this profile when it's updated by the external provider.
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestFacebookConnect ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString accessToken = self->GetJString ( lua_tostring ( state, 1 ));

	self->CallStaticVoidMethod ( self->mJava_RequestFacebookConnect, ( jstring )accessToken );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestLogEvent
	@text	Request log event.
				
	@in 	string	eventKey		Event key
	@in 	table	attributes 		Attributes
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestLogEvent ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString eventKey = self->GetJString ( lua_tostring ( state, 1 ));
	jobject jbundle = NULL;

	if ( state.IsType ( 2, LUA_TTABLE ) ) {
		jbundle = self->BundleFromLua( L, 2 );
	}

	self->CallStaticVoidMethod ( self->mJava_RequestLogEvent, ( jstring )eventKey, jbundle );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestRegistration
	@text	Request Registration.
				
	@in 	string	displayName		A display name to use
	@in 	string	password		The previously registered password
	@opt 	JSON	segments		An optional segment configuration for this request.
	@in 	string	userName 		The previously registered player name
	@out 	nil
*/
int	MOAIGameSparksAndroid::_requestRegistration ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString displayName = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString password = self->GetJString ( lua_tostring ( state, 2 ));
	MOAIJString userName = self->GetJString ( lua_tostring ( state, 3 ));

	self->CallStaticVoidMethod ( self->mJava_RequestRegistration, ( jstring )displayName, ( jstring )password, ( jstring )userName );
	return 0;
}

//================================================================//
// MOAIGameSparksAndroid
//================================================================//

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::AuthenticationFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_AUTHENTICATE_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::AuthenticationSuccessResponse ( cc8* authToken, cc8* displayName, bool newPlayer, cc8* userId ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_AUTHENTICATE_SUCCESS, state )) {

		state.Push ( authToken );
		state.Push ( displayName );
		state.Push ( newPlayer );
		state.Push ( userId );
		state.DebugCall ( 4, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::AvailabilityResponse ( bool available ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_AVAILABILITY, state )) {

		state.Push ( available );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::AccountDetailsFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_GET_ACCOUNT_DETAILS_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::AccountDetailsSuccessResponse ( cc8* displayName, cc8* userId ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_GET_ACCOUNT_DETAILS_SUCCESS, state )) {

		state.Push ( displayName );
		state.Push ( userId );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::BuyVirtualGoodFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_BUY_VIRTUAL_GOOD_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::BuyVirtualGoodSuccessResponse ( cc8* boughtItems ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_BUY_VIRTUAL_GOOD_SUCCESS, state )) {

		state.Push ( boughtItems );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::ChangeUserDetailsFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_CHANGE_USER_DETAILS_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::ChangeUserDetailsSuccessResponse () {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_CHANGE_USER_DETAILS_SUCCESS, state )) {

		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::DeviceAuthenticationFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_DEVICE_AUTHENTICATE_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::DeviceAuthenticationSuccessResponse ( cc8* authToken, cc8* displayName, bool newPlayer, cc8* userId ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_DEVICE_AUTHENTICATE_SUCCESS, state )) {

		state.Push ( authToken );
		state.Push ( displayName );
		state.Push ( newPlayer );
		state.Push ( userId );
		state.DebugCall ( 4, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::FacebookConnectFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FACEBOOK_CONNECT_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::FacebookConnectSuccessResponse ( cc8* authToken, cc8* displayName, bool newPlayer, cc8* userId ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FACEBOOK_CONNECT_SUCCESS, state )) {

		state.Push ( authToken );
		state.Push ( displayName );
		state.Push ( newPlayer );
		state.Push ( userId );
		state.DebugCall ( 4, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::LogEventFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_LOG_EVENT_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::LogEventSuccessResponse ( cc8* eventKey, cc8* attributes ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_LOG_EVENT_SUCCESS, state )) {

		state.Push ( eventKey );
		this->JsonToLua ( state, attributes );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
MOAIGameSparksAndroid::MOAIGameSparksAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/gamesparks/MoaiGameSparks" );

	this->mJava_Init							= this->GetStaticMethod ( "init", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ZZ)V" );
	this->mJava_RequestAccountDetails			= this->GetStaticMethod ( "requestAccountDetails", "()V" );
	this->mJava_RequestAuthentication			= this->GetStaticMethod ( "requestAuthentication", "(Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_RequestBuyGoods					= this->GetStaticMethod ( "requestBuyGoods", "(Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_RequestChangeUserDetails		= this->GetStaticMethod ( "requestChangeUserDetails", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_RequestDeviceAuthentication		= this->GetStaticMethod ( "requestDeviceAuthentication", "(Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_RequestFacebookConnect			= this->GetStaticMethod ( "requestFacebookConnect", "(Ljava/lang/String;)V" );
	this->mJava_RequestLogEvent					= this->GetStaticMethod ( "requestLogEvent", "(Ljava/lang/String;Landroid/os/Bundle;)V" );
	this->mJava_RequestRegistration				= this->GetStaticMethod ( "requestRegistration", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIGameSparksAndroid::~MOAIGameSparksAndroid () {
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "ON_AUTHENTICATE_FAIL",				( u32 )ON_AUTHENTICATE_FAIL );
	state.SetField ( -1, "ON_AUTHENTICATE_SUCCESS",				( u32 )ON_AUTHENTICATE_SUCCESS );
	state.SetField ( -1, "ON_AVAILABILITY",						( u32 )ON_AVAILABILITY );
	state.SetField ( -1, "ON_BUY_VIRTUAL_GOOD_FAIL",			( u32 )ON_BUY_VIRTUAL_GOOD_FAIL );
	state.SetField ( -1, "ON_BUY_VIRTUAL_GOOD_SUCCESS",			( u32 )ON_BUY_VIRTUAL_GOOD_SUCCESS );
	state.SetField ( -1, "ON_CHANGE_USER_DETAILS_FAIL",			( u32 )ON_CHANGE_USER_DETAILS_FAIL );
	state.SetField ( -1, "ON_CHANGE_USER_DETAILS_SUCCESS",		( u32 )ON_CHANGE_USER_DETAILS_SUCCESS );
	state.SetField ( -1, "ON_DEVICE_AUTHENTICATE_FAIL",			( u32 )ON_DEVICE_AUTHENTICATE_FAIL );
	state.SetField ( -1, "ON_DEVICE_AUTHENTICATE_SUCCESS",		( u32 )ON_DEVICE_AUTHENTICATE_SUCCESS );
	state.SetField ( -1, "ON_FACEBOOK_CONNECT_FAIL",			( u32 )ON_FACEBOOK_CONNECT_FAIL );
	state.SetField ( -1, "ON_FACEBOOK_CONNECT_SUCCESS",			( u32 )ON_FACEBOOK_CONNECT_SUCCESS );
	state.SetField ( -1, "ON_GET_ACCOUNT_DETAILS_FAIL",			( u32 )ON_GET_ACCOUNT_DETAILS_FAIL );
	state.SetField ( -1, "ON_GET_ACCOUNT_DETAILS_SUCCESS",		( u32 )ON_GET_ACCOUNT_DETAILS_SUCCESS );
	state.SetField ( -1, "ON_LOG_EVENT_FAIL",					( u32 )ON_LOG_EVENT_FAIL );
	state.SetField ( -1, "ON_LOG_EVENT_SUCCESS",				( u32 )ON_LOG_EVENT_SUCCESS );
	state.SetField ( -1, "ON_REGISTRATION_FAIL",				( u32 )ON_REGISTRATION_FAIL );
	state.SetField ( -1, "ON_REGISTRATION_SUCCESS",				( u32 )ON_REGISTRATION_SUCCESS );

	luaL_Reg regTable [] = {
		{ "init",							_init },
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIGameSparksAndroid > },
		{ "requestAccountDetails",			_requestAccountDetails },
		{ "requestAuthentication",			_requestAuthentication },
		{ "requestBuyGoods",				_requestBuyGoods },
		{ "requestChangeUserDetails",		_requestChangeUserDetails },
		{ "requestDeviceAuthentication",	_requestDeviceAuthentication },
		{ "requestFacebookConnect",			_requestFacebookConnect },
		{ "requestLogEvent",				_requestLogEvent },
		{ "requestRegistration",			_requestRegistration },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIGameSparksAndroid > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::RegistrationFailResponse ( cc8* errors ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_REGISTRATION_FAIL, state )) {
		
		state.Push ( errors );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::RegistrationSuccessResponse ( cc8* authToken, cc8* displayName, bool newPlayer, cc8* userId ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_REGISTRATION_SUCCESS, state )) {

		state.Push ( authToken );
		state.Push ( displayName );
		state.Push ( newPlayer );
		state.Push ( userId );
		state.DebugCall ( 4, 0 );
	}
}

//================================================================//
// GameSparks JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAuthenticationFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAuthenticationFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().AuthenticationFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAuthenticationSuccessResponse ( JNIEnv* env, jclass obj, jstring jauthToken, jstring jdisplayName, jboolean newPlayer, jstring juserId ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAuthenticationSuccessResponse\n" );

		JNI_GET_CSTRING ( jauthToken, authToken );
		JNI_GET_CSTRING ( jdisplayName, displayName );
		JNI_GET_CSTRING ( juserId, userId );

		MOAIGameSparksAndroid::Get ().AuthenticationSuccessResponse (  authToken, displayName, newPlayer, userId  );

		JNI_RELEASE_CSTRING ( jauthToken, authToken );
		JNI_RELEASE_CSTRING ( jdisplayName, displayName );
		JNI_RELEASE_CSTRING ( juserId, userId );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAvailabilityResponse ( JNIEnv* env, jclass obj, jboolean available ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAvailabilityResponse\n" );
		MOAIGameSparksAndroid::Get ().AvailabilityResponse ( available );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAccountDetailsFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAccountDetailsFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().AccountDetailsFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAccountDetailsSuccessResponse ( JNIEnv* env, jclass obj, jstring jdisplayName, jstring juserId ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAccountDetailsSuccessResponse\n" );

		JNI_GET_CSTRING ( jdisplayName, displayName );
		JNI_GET_CSTRING ( juserId, userId );

		MOAIGameSparksAndroid::Get ().AccountDetailsSuccessResponse ( displayName, userId );

		JNI_RELEASE_CSTRING ( jdisplayName, displayName );
		JNI_RELEASE_CSTRING ( juserId, userId );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUBuyVirtualGoodFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUBuyVirtualGoodFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().BuyVirtualGoodFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUBuyVirtualGoodSuccessResponse ( JNIEnv* env, jclass obj, jstring jboughtItems ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUBuyVirtualGoodSuccessResponse\n" );

		JNI_GET_CSTRING ( jboughtItems, boughtItems );

		MOAIGameSparksAndroid::Get ().BuyVirtualGoodSuccessResponse ( boughtItems );

		JNI_RELEASE_CSTRING ( jboughtItems, boughtItems );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUChangeUserDetailsFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUChangeUserDetailsFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().ChangeUserDetailsFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUChangeUserDetailsSuccessResponse ( JNIEnv* env, jclass obj ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUChangeUserDetailsSuccessResponse\n" );

		MOAIGameSparksAndroid::Get ().ChangeUserDetailsSuccessResponse ();
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUDeviceAuthenticationFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUDeviceAuthenticationFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().DeviceAuthenticationFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUDeviceAuthenticationSuccessResponse ( JNIEnv* env, jclass obj, jstring jauthToken, jstring jdisplayName, jboolean newPlayer, jstring juserId ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUDeviceAuthenticationSuccessResponse\n" );

		JNI_GET_CSTRING ( jauthToken, authToken );
		JNI_GET_CSTRING ( jdisplayName, displayName );
		JNI_GET_CSTRING ( juserId, userId );

		MOAIGameSparksAndroid::Get ().DeviceAuthenticationSuccessResponse (  authToken, displayName, newPlayer, userId  );

		JNI_RELEASE_CSTRING ( jauthToken, authToken );
		JNI_RELEASE_CSTRING ( jdisplayName, displayName );
		JNI_RELEASE_CSTRING ( juserId, userId );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUFacebookConnectFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUFacebookConnectFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().FacebookConnectFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUFacebookConnectSuccessResponse ( JNIEnv* env, jclass obj, jstring jauthToken, jstring jdisplayName, jboolean newPlayer, jstring juserId ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUFacebookConnectSuccessResponse\n" );

		JNI_GET_CSTRING ( jauthToken, authToken );
		JNI_GET_CSTRING ( jdisplayName, displayName );
		JNI_GET_CSTRING ( juserId, userId );

		MOAIGameSparksAndroid::Get ().FacebookConnectSuccessResponse (  authToken, displayName, newPlayer, userId  );

		JNI_RELEASE_CSTRING ( jauthToken, authToken );
		JNI_RELEASE_CSTRING ( jdisplayName, displayName );
		JNI_RELEASE_CSTRING ( juserId, userId );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKULogEventFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKULogEventFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().LogEventFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}


//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKULogEventSuccessResponse ( JNIEnv* env, jclass obj, jstring jeventKey, jstring jattributes ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKULogEventSuccessResponse\n" );

		JNI_GET_CSTRING ( jeventKey, eventKey );
		JNI_GET_CSTRING ( jattributes, attributes );

		MOAIGameSparksAndroid::Get ().LogEventSuccessResponse ( eventKey, attributes );

		JNI_RELEASE_CSTRING ( jeventKey, eventKey );
		JNI_RELEASE_CSTRING ( jattributes, attributes );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKURegistrationFailResponse ( JNIEnv* env, jclass obj, jstring jerrors ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKURegistrationFailResponse\n" );

		JNI_GET_CSTRING ( jerrors, errors );
		MOAIGameSparksAndroid::Get ().RegistrationFailResponse ( errors );
		JNI_RELEASE_CSTRING ( jerrors, errors );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKURegistrationSuccessResponse ( JNIEnv* env, jclass obj, jstring jauthToken, jstring jdisplayName, jboolean newPlayer, jstring juserId ) {

	if ( MOAIGameSparksAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKURegistrationSuccessResponse\n" );

		JNI_GET_CSTRING ( jauthToken, authToken );
		JNI_GET_CSTRING ( jdisplayName, displayName );
		JNI_GET_CSTRING ( juserId, userId );

		MOAIGameSparksAndroid::Get ().RegistrationSuccessResponse (  authToken, displayName, newPlayer, userId  );

		JNI_RELEASE_CSTRING ( jauthToken, authToken );
		JNI_RELEASE_CSTRING ( jdisplayName, displayName );
		JNI_RELEASE_CSTRING ( juserId, userId );
	}
}

