// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/JniUtils.h>
#include <moai-android-facebook/MOAIFacebookAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	graphRequest
	@text	Make a request on Facebook's Graph API

	@in 	string 		method, "GET" or "POST"
	@in		string		path
	@opt	table		parameters
	@opt	function 	callback
	@out	nil
*/
int MOAIFacebookAndroid::_graphRequest ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )

	MOAIJString jmethod = self->GetJString ( state.GetValue < cc8* >( 1, "GET" ) );
	MOAIJString jpath = self->GetJString ( state.GetValue < cc8* >( 2, "" ) );
	jobject jbundle;

	if ( state.IsType ( 3, LUA_TTABLE ) ) {
		jbundle = self->BundleFromLua( L, 3 );
	}

	int ref = LUA_NOREF;
	if ( state.IsType ( 4, LUA_TFUNCTION )) {
		ref = self->mRefs.Ref ( state, 4 );
	}

	self->CallStaticVoidMethod ( self->mJava_GraphRequest, ( jstring )jmethod, ( jstring )jpath, jbundle, ref );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	hasGranted
	@text	Determine whether or not the current permission is granted.
				
	@out 	boolean	valid
*/
int MOAIFacebookAndroid::_hasGranted ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )

	cc8* permission = state.GetValue < cc8* > ( 1, 0 );
	
	if ( permission ) {
		
		MOAIJString jpermission = self->GetJString ( permission );
		state.Push ( self->CallStaticBooleanMethod ( self->mJava_HasGranted, ( jstring )jpermission ));
	}
	else {
	
		state.Push ( false );
	}

	return 1;
}

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Facebook.
				
	@in		string	appId			Available in Facebook developer settings.
	@out 	nil
*/
int MOAIFacebookAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )
	
	jstring jidentifier = self->GetJString ( lua_tostring ( state, 1 ));
	self->CallStaticVoidMethod ( self->mJava_Init, jidentifier );		
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	logEvent
	@text	Log event

	@in 	string 	eventName
	@in		double 	valueToSum
	@opt	table 	parameters
	@out	nil
*/
int MOAIFacebookAndroid::_logEvent ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )

	jstring jeventName = self->GetJString ( lua_tostring ( state, 1 ));
	double valueToSum = state.GetValue < double >( 2, 0 );
	jobject jbundle = NULL;
	if ( state.IsType ( 3, LUA_TTABLE ) ) {
	   jbundle = self->BundleFromLua( L, 3 );
	}
	if ( jbundle == NULL ) {
		jclass clazz = self->Env ()->FindClass ( "android/os/Bundle" );
		jbundle = self->Env ()->NewObject ( clazz, self->Env ()->GetMethodID ( clazz, "<init>", "()V" ));
	}
	self->CallStaticVoidMethod ( self->mJava_LogEvent, jeventName, valueToSum, jbundle );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	logPurchase
	@text	Log purchase

	@in 	string 	eventName
	@in		double 	valueToSum
	@opt	table 	parameters
	@out	nil
*/
int MOAIFacebookAndroid::_logPurchase ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )

	double amount = state.GetValue < double >( 1, 0.0f );
	jstring jcurrency = self->GetJString ( state.GetValue < cc8* >( 2, "USD" ) );

	jobject jbundle;
	if ( state.IsType ( 3, LUA_TTABLE ) ) {
	   jbundle = self->BundleFromLua( L, 3 );
	}

	self->CallStaticVoidMethod ( self->mJava_LogPurchase, amount, jcurrency, jbundle );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	login
	@text	Prompt the user to login to Facebook.
				
	@opt	table	permissions			Optional set of required permissions. See Facebook documentation for a full list. Default is nil.
	@out 	nil
*/
int MOAIFacebookAndroid::_login ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )
	
	jobjectArray jpermissions = NULL;
	
	if ( state.IsType ( 1, LUA_TTABLE )) {
		jpermissions = self->StringArrayFromLua ( L, 1 );
	}
	
	if ( jpermissions == NULL ) {
		jpermissions = self->Env ()->NewObjectArray ( 0, self->Env ()->FindClass( "java/lang/String" ), 0 );
	}

	self->CallStaticVoidMethod ( self->mJava_Login, jpermissions );				
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	logout
	@text	Log the user out of Facebook.
				
	@out 	nil
*/
int MOAIFacebookAndroid::_logout ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_Logout );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	postToFeed
	@text	Post a message to the logged in users' news feed.
				
	@in		string	link			The URL that the post links to. See Facebook documentation.
	@in		string	picture			The URL of an image to include in the post. See Facebook documentation.
	@in		string	name			The name of the link. See Facebook documentation.
	@in		string	caption			The caption of the link. See Facebook documentation.
	@in		string	description		The description of the link. See Facebook documentation.
	@in		string	message			The message for the post. See Facebook documentation.
	@out 	nil
*/
int MOAIFacebookAndroid::_postToFeed ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )
	
	MOAIJString jlink			= self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString jpicture		= self->GetJString ( lua_tostring ( state, 2 ));
	MOAIJString jname			= self->GetJString ( lua_tostring ( state, 3 ));
	MOAIJString jcaption		= self->GetJString ( lua_tostring ( state, 4 ));
	MOAIJString jdescription	= self->GetJString ( lua_tostring ( state, 5 ));
	MOAIJString jmessage		= self->GetJString ( lua_tostring ( state, 6 ));
	
	self->CallStaticVoidMethod ( self->mJava_PostToFeed, ( jstring )jlink, ( jstring )jpicture, ( jstring )jname, ( jstring )jcaption, ( jstring )jdescription, ( jstring )jmessage );	
		
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFacebookAndroid::_restoreSession ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_RestoreSession ));
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	sendRequest
	@text	Send an app request to the logged in users' friends.
				
	@opt	string	message			The message for the request. See Facebook documentation. Default is nil.
	@out 	nil
*/
int MOAIFacebookAndroid::_sendRequest ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )
	
	MOAIJString jmessage = self->GetJString ( lua_tostring ( state, 1 ));
	self->CallStaticVoidMethod ( self->mJava_SendRequest, ( jstring )jmessage );		
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	sessionValid
	@text	Determine whether or not the current Facebook session is valid.
				
	@out 	boolean	valid
*/
int MOAIFacebookAndroid::_sessionValid ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_IsSessionValid ));
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	showInviteDialog
	@text	Displays Facebook invite dialog.

	@out	void
*/
int MOAIFacebookAndroid::_showInviteDialog ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFacebookAndroid, "" )

	MOAIJString linkURL = self->GetJString ( lua_tostring ( state, 1 ));
	MOAIJString imgURL = self->GetJString ( lua_tostring ( state, 2 ));
	self->CallStaticVoidMethod ( self->mJava_ShowInviteDialog, ( jstring )linkURL, ( jstring )imgURL );
	return 0;
}

//================================================================//
// MOAIFacebookAndroid
//================================================================//

//----------------------------------------------------------------//
void MOAIFacebookAndroid::ClearCallbackRef ( int ref ) {
	
	if ( MOAILuaRuntime::IsValid () && ref != LUA_NOREF ) {
		this->mRefs.Unref ( ref );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::DialogDidNotComplete () {
	
	this->InvokeListener ( DIALOG_DID_NOT_COMPLETE );
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::DialogDidComplete () {

	this->InvokeListener ( DIALOG_DID_COMPLETE );
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::GameRequestDialogDidComplete ( NSDictionary* results, int ref ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_DIALOG_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		state.Push ( true );
		OBJC_TO_LUA ( results, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::GameRequestDialogDidFail ( NSError* error, int ref ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_DIALOG_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		state.Push ( false );
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::GraphRequestResponse ( id result, int ref ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		
		state.Push ( true );
		OBJC_TO_LUA ( result, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::GraphRequestResponseFailure ( NSError* error, int ref ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( ref == LUA_NOREF ) {
		this->PushListener ( REQUEST_RESPONSE, state );
	}
	else {
		this->mRefs.PushRef ( state, ref );
	}
	
	if ( state.IsType ( -1, LUA_TFUNCTION )) {
		
		state.Push ( false );
		OBJC_TO_LUA ( error, state );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
MOAIFacebookAndroid::MOAIFacebookAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	this->SetClass ( "com/moaisdk/facebook/MoaiFacebook" );

	// this->mJava_DeclinedPermissions			= this->GetStaticMethod ( "declinedPermissions", "()" );
	// this->mJava_GetExpirationDate			= this->GetStaticMethod ( "getExpirationDate", "()" );
	// this->mJava_GetProfile					= this->GetStaticMethod ( "getProfile", "()" );
	// this->mJava_GetToken					= this->GetStaticMethod ( "getToken", "()" );
	this->mJava_GraphRequest				= this->GetStaticMethod ( "graphRequest", "(Ljava/lang/String;Ljava/lang/String;Landroid/os/Bundle;I)V" );
	this->mJava_HasGranted					= this->GetStaticMethod ( "hasGranted", "(Ljava/lang/String;)Z" );
	this->mJava_Init						= this->GetStaticMethod ( "init", "(Ljava/lang/String;)V" );
	this->mJava_LogEvent					= this->GetStaticMethod ( "logEvent", "(Ljava/lang/String;DLandroid/os/Bundle;)V" );
	this->mJava_LogPurchase					= this->GetStaticMethod ( "logPurchase", "(DLjava/lang/String;Landroid/os/Bundle;)V" );
	this->mJava_Login						= this->GetStaticMethod ( "login", "([Ljava/lang/String;Z)V" );
	this->mJava_Logout						= this->GetStaticMethod ( "logout", "()V" );
	// this->mJava_PostToFeed					= this->GetStaticMethod ( "postToFeed", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_RequestPublishPermissions	= this->GetStaticMethod ( "requestPublishPermissions", "([Ljava/lang/String;)V" );
	this->mJava_RequestReadPermissions		= this->GetStaticMethod ( "requestReadPermissions", "([Ljava/lang/String;)V" );
	this->mJava_SendGameRequest				= this->GetStaticMethod ( "sendGameRequest", "(Ljava/lang/String;Landroid/os/Bundle;)V" );
	this->mJava_SessionValid				= this->GetStaticMethod ( "sessionValid", "()Z" );

	mRefs.InitStrong ();
}

//----------------------------------------------------------------//
MOAIFacebookAndroid::~MOAIFacebookAndroid () {

	if ( MOAILuaRuntime::IsValid ()) {
		mRefs.Clear ();
	}
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	// Events
	state.SetField ( -1, "DIALOG_DID_COMPLETE", 		( u32 )DIALOG_DID_COMPLETE );
	state.SetField ( -1, "DIALOG_DID_NOT_COMPLETE",		( u32 )DIALOG_DID_NOT_COMPLETE );
	state.SetField ( -1, "PERMISSIONS_DENIED",			( u32 )PERMISSIONS_DENIED );
	state.SetField ( -1, "PERMISSIONS_GRANTED",			( u32 )PERMISSIONS_GRANTED );
	state.SetField ( -1, "PROFILE_UPDATED",				( u32 )PROFILE_UPDATED );
	state.SetField ( -1, "REQUEST_RESPONSE", 			( u32 )REQUEST_RESPONSE );
	state.SetField ( -1, "REQUEST_DIALOG_RESPONSE",		( u32 )REQUEST_DIALOG_RESPONSE );
	state.SetField ( -1, "SESSION_DID_LOGIN", 			( u32 )SESSION_DID_LOGIN );
	state.SetField ( -1, "SESSION_DID_NOT_LOGIN", 		( u32 )SESSION_DID_NOT_LOGIN );
	state.SetField ( -1, "SESSION_EXTENDED",			( u32 )SESSION_EXTENDED );

	// Game request action types
	state.SetField ( -1, "ACTION_NONE", 				( u32 )FBSDKGameRequestActionTypeNone );
	state.SetField ( -1, "ACTION_SEND", 				( u32 )FBSDKGameRequestActionTypeSend );
	state.SetField ( -1, "ACTION_ASK_FOR", 				( u32 )FBSDKGameRequestActionTypeAskFor );
	state.SetField ( -1, "ACTION_TURN", 				( u32 )FBSDKGameRequestActionTypeTurn );
	
	// Game request filters
	state.SetField ( -1, "FILTER_NONE", 				( u32 )FBSDKGameRequestFilterNone );
	state.SetField ( -1, "FILTER_APP_USERS", 			( u32 )FBSDKGameRequestFilterAppUsers );
	state.SetField ( -1, "FILTER_APP_NON_USERS", 		( u32 )FBSDKGameRequestFilterAppNonUsers );

	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_ACHIEVED_LEVEL",		"EVENT_NAME_ACHIEVED_LEVEL" );

	// Analytics predefined event names
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_ACHIEVED_LEVEL",			"EVENT_NAME_ACHIEVED_LEVEL" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_ADDED_PAYMENT_INFO",		"EVENT_NAME_ADDED_PAYMENT_INFO" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_ADDED_TO_CART",				"EVENT_NAME_ADDED_TO_CART" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_ADDED_TO_WISHLIST",			"EVENT_NAME_ADDED_TO_WISHLIST" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_COMPLETED_REGISTRATION", 	"EVENT_NAME_COMPLETED_REGISTRATION" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_COMPLETED_TUTORIAL",		"EVENT_NAME_COMPLETED_TUTORIAL" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_INITIATED_CHECKOUT",		"EVENT_NAME_INITIATED_CHECKOUT" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_RATED",						"EVENT_NAME_RATED" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_SEARCHED",					"EVENT_NAME_SEARCHED" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_SPENT_CREDITS",				"EVENT_NAME_SPENT_CREDITS" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_UNLOCKED_ACHIEVEMENT",		"EVENT_NAME_UNLOCKED_ACHIEVEMENT" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "NAME_VIEWED_CONTENT",			"EVENT_NAME_VIEWED_CONTENT" );

	// Analytics predefined event parameters names
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_CONTENT_ID",				"EVENT_PARAM_NAME_CONTENT_ID" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_CONTENT_TYPE",			"EVENT_PARAM_NAME_CONTENT_TYPE" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_CURRENCY",				"EVENT_PARAM_NAME_CURRENCY" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_DESCRIPTION",				"EVENT_PARAM_NAME_DESCRIPTION" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_LEVEL",					"EVENT_PARAM_NAME_LEVEL" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_MAX_RATING_VALUE",		"EVENT_PARAM_NAME_MAX_RATING_VALUE" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_NUM_ITEMS",				"EVENT_PARAM_NAME_NUM_ITEMS" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_PAYMENT_INFO_AVAILABLE",	"EVENT_PARAM_NAME_PAYMENT_INFO_AVAILABLE" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_REGISTRATION_METHOD",		"EVENT_PARAM_NAME_REGISTRATION_METHOD" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_SEARCH_STRING",			"EVENT_PARAM_NAME_SEARCH_STRING" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_NAME_SUCCESS",					"EVENT_PARAM_NAME_SUCCESS" );

	// Analytics predefined event parameters values
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_VALUE_NO",						"EVENT_PARAM_VALUE_NO" );
	RegisterStringConstant ( state, mJava_AppEventsConstants, "PARAMETER_VALUE_YES",					"EVENT_PARAM_VALUE_YES" );

	luaL_Reg regTable [] = {
		{ "getListener",				&MOAIGlobalEventSource::_getListener < MOAIFacebookAndroid > },
		{ "graphRequest",				graphRequest },
		{ "hasGranted",					hasGranted },
		{ "init",						init },
		{ "logEvent",					logEvent },
		{ "logPurchase",				logPurchase },
		{ "login",						login },
		{ "logout",						logout },
		{ "requestPublishPermissions",	requestPublishPermissions },
		{ "requestReadPermissions",		requestReadPermissions },
		{ "sendGameRequest",			sendGameRequest },
		{ "sessionValid",				sessionValid },
		{ "setListener",				&MOAIGlobalEventSource::_setListener < MOAIFacebookAndroid > },
	}

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::NotifyLoginSuccess () {

	this->InvokeListener ( LOGIN_SUCCESS );
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::NotifyLoginDismissed () {

	this->InvokeListener ( LOGIN_DISMISSED );
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::NotifyLoginError () {

	this->InvokeListener ( LOGIN_ERROR );
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::NotifyRequestComplete ( cc8* response ) {

	//MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	//if ( this->PushListener ( REQUEST_RESPONSE, state )) {
	//	lua_pushstring ( state, response );
	//	state.DebugCall ( 1, 0 );
	//}
}

//----------------------------------------------------------------//
void MOAIFacebookAndroid::NotifyRequestFailed () {

	//this->InvokeListener ( REQUEST_RESPONSE_FAILED );
}

//================================================================//
// Facebook JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_facebook_MoaiFacebook_AKUNotifyFacebookLoginSuccess ( JNIEnv* env, jclass obj ) {

	MOAIFacebookAndroid::Get ().NotifyLoginSuccess ();
}

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_facebook_MoaiFacebook_AKUNotifyFacebookLoginError ( JNIEnv* env, jclass obj ) {

	MOAIFacebookAndroid::Get ().NotifyLoginError ();
}

extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_facebook_MoaiFacebook_AKUNotifyFacebookLoginDismissed ( JNIEnv* env, jclass obj ) {

	MOAIFacebookAndroid::Get ().NotifyLoginDismissed ();
}

extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_facebook_MoaiFacebook_AKUNotifyFacebookRequestFailed ( JNIEnv* env, jclass obj ) {

	MOAIFacebookAndroid::Get ().NotifyRequestFailed ( );
}

