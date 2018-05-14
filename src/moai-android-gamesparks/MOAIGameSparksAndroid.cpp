// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-gamesparks/MOAIGameSparksAndroid.h>

//================================================================//
// lua
//================================================================//

displayName	Yes	string	A display name to use
password	Yes	string	The previously registered password
segments	No	JSON	An optional segment configuration for this request.
userName	Yes	string	The previously registered player name

//----------------------------------------------------------------//
/**	@lua	connect
	@text	Connect.
				
	@in 	string	username
	@in 	string	password
	@out 	nil
*/
int	MOAIGameSparksAndroid::_connect ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString username = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString password = self->GetJString ( lua_tostring ( state, 2 ));

	self->CallStaticVoidMethod ( self->mJava_Connect, ( jstring )username, ( jstring )password );
	return 0;
}

authToken	string	44b297a8-162a-4220-8c14-dad9a1946ad2
displayName	string	The player's display name
newPlayer	boolean	Indicates whether the player was created as part of this request
userId	string	The player's id

//----------------------------------------------------------------//
/**	@lua	connectFB
	@text	Connect with Facebook.
				
	@in 	string	token
	@out 	nil
*/
int	MOAIGameSparksAndroid::_connectFB ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString token = self->GetJString ( lua_tostring ( state, 1 ));

	self->CallStaticVoidMethod ( self->mJava_ConnectFB, ( jstring )token );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	getAccountDetails
	@text	Request account details.
				
	@out 	nil
*/
int	MOAIGameSparksAndroid::_getAccountDetails ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_GetAccountDetails );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize GameSparks.
	
	@in 	string	apiKey
	@in 	string	apiSecret
	@in 	string	credential
	@out 	nil
*/
int	MOAIGameSparksAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIGameSparksAndroid, "" )

	MOAIJString japiKey	= self->GetJString ( state.GetValue < cc8* >( 1, 0 ));
	MOAIJString japiSecret	= self->GetJString ( state.GetValue < cc8* >( 2, 0 ));
	MOAIJString jcredential	= self->GetJString ( state.GetValue < cc8* >( 3, 0 ));

	self->CallStaticVoidMethod ( self->mJava_Init, ( jstring )japiKey, ( jstring )japiSecret, ( jstring )jcredential );
	return 0;
}


//================================================================//
// MOAIGameSparksAndroid
//================================================================//

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::AccountDetailsResponse () {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_GET_ACCOUNT_DETAILS, state )) {

		state.Push ( result );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::AvailabilityResponse ( bool available ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();

	if ( this->PushListener ( ON_AVAILABILITY, state )) {

		state.Push ( result );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::FBConnectSuccessResponse ( cc8* *displayName, cc8* *userId, bool isNew ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FB_CONNECT_SUCCESS, state )) {

		state.Push ( displayName );
		state.Push ( userId );
		state.Push ( isNew );
		state.DebugCall ( 3, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIChartBoostAndroid::FBConnectFailResponse ( cc8* *error ) {

	if ( !MOAILuaRuntime::IsValid ()) return;

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ON_FB_CONNECT_FAIL, state )) {
		
		state.Push ( reward );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
MOAIGameSparksAndroid::MOAIGameSparksAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/gamesparks/MoaiGameSparks" );

	this->mJava_Connect				= this->GetStaticMethod ( "connect", "(Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_ConnectFB			= this->GetStaticMethod ( "connectFB", "(Ljava/lang/String;)V" );
	this->mJava_GetAccountDetails	= this->GetStaticMethod ( "getAccountDetails", "()V" );
	this->mJava_Init				= this->GetStaticMethod ( "init", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
}

//----------------------------------------------------------------//
MOAIGameSparksAndroid::~MOAIGameSparksAndroid () {
}

//----------------------------------------------------------------//
void MOAIGameSparksAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "ON_AVAILABILITY",			( u32 )ON_AVAILABILITY );
	state.SetField ( -1, "ON_GET_ACCOUNT_DETAILS",	( u32 )ON_GET_ACCOUNT_DETAILS );
	state.SetField ( -1, "ON_FB_CONNECT_SUCCESS",	( u32 )ON_FB_CONNECT_SUCCESS );
	state.SetField ( -1, "ON_FB_CONNECT_FAIL",		( u32 )ON_FB_CONNECT_FAIL );

	luaL_Reg regTable [] = {
		{ "connect",				_connect },
		{ "connectFB",				_connectFB },
		{ "getAccountDetails",		_getAccountDetails },
		{ "getListener",			&MOAIGlobalEventSource::_getListener < MOAIGameSparksAndroid > },
		{ "init",					_init },
		{ "setListener",			&MOAIGlobalEventSource::_setListener < MOAIGameSparksAndroid > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// ChartBoost JNI methods
//================================================================//

	void	AvailabilityResponse			( bool available );
	void	FBConnectSuccessResponse		( cc8* *displayName, cc8* *userId, bool isNew );
	void	FBConnectFailResponse			( cc8* *error );
	void	RegistrationResponse			( cc8* *authToken, cc8* *displayName, bool newPlayer, cc8* *userId );

	protected static native void 		();
	protected static native void AKUAvailabilityResponse 		( bool available );
	protected static native void AKUFBConnectSuccessResponse	( String displayName, String userId, boolean isNew );
	protected static native void AKUFBConnectFailResponse		( String error );
	protected static native void AKURegistrationResponse		( String authToken, String displayName, boolean newPlayer, String userId );

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAccountDetailsResponse ( JNIEnv* env, jclass obj ) {

	if ( MOAIChartBoostAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_gamesparks_MoaiGameSparks_AKUAccountDetailsResponse\n" );
		MOAIChartBoostAndroid::Get ().NotifyRewardedVideoCompleted ( reward );
	}
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_gamesparks_MoaiChartBoost_AKURewardedVideoCompleted ( JNIEnv* env, jclass obj, jint reward ) {

	if ( MOAIChartBoostAndroid::IsValid ()) {
		MOAIChartBoostAndroid::Get ().NotifyRewardedVideoCompleted ( reward );
	}
}

