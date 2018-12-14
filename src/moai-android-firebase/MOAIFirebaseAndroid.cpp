// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/JniUtils.h>
#include <moai-android-firebase/MOAIFirebaseAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Firebase.
	
	@out 	nil
*/
int	MOAIFirebaseAndroid::_init ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_Init );
	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_fetchConfig ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_FetchConfig );
	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_activateFetchedConfig ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	self->CallStaticVoidMethod ( self->mJava_ActivateFetchedConfig );
	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_getConfigString ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString key = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	JNI_GET_ENV ( jvm, env );

    jstring jstringValue = ( jstring )self->CallStaticObjectMethod ( self->mJava_GetConfigString, ( jstring )key );	

	JNI_GET_CSTRING ( jstringValue, stringValue );

	lua_pushstring ( state, stringValue );

	JNI_RELEASE_CSTRING ( jstringValue, stringValue );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_getConfigBoolean ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString key = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_GetConfigBoolean, ( jstring )key ));
	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_getConfigDouble ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString key = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	lua_pushnumber ( state, self->CallStaticDoubleMethod ( self->mJava_GetConfigDouble, ( jstring )key ));
	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_getConfigLong ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString key = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	lua_pushnumber ( state, self->CallStaticLongMethod ( self->mJava_GetConfigLong, ( jstring )key ));
	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_createAnonymousAccountWithReferrerInfo ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString uid = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	MOAIJString referrerUid = self->GetJString ( state.GetValue < cc8* >( 2, "" ));

	self->CallStaticVoidMethod ( self->mJava_CreateAnonymousAccountWithReferrerInfo, ( jstring )uid, ( jstring )referrerUid );

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_getInvitationId ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	JNI_GET_ENV ( jvm, env );

    jstring jstringValue = ( jstring )self->CallStaticObjectMethod ( self->mJava_GetInvitationId );	

	JNI_GET_CSTRING ( jstringValue, stringValue );

	lua_pushstring ( state, stringValue );

	JNI_RELEASE_CSTRING ( jstringValue, stringValue );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_getInvitationDeepLink ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	JNI_GET_ENV ( jvm, env );

    jstring jstringValue = ( jstring )self->CallStaticObjectMethod ( self->mJava_GetInvitationDeepLink );	

	JNI_GET_CSTRING ( jstringValue, stringValue );

	lua_pushstring ( state, stringValue );

	JNI_RELEASE_CSTRING ( jstringValue, stringValue );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_createInvitationDeepLink ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString uid = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	self->CallStaticVoidMethod ( self->mJava_CreateInvitationDeepLink, ( jstring )uid );

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_showInviteSMSDialog ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString title = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	MOAIJString message = self->GetJString ( state.GetValue < cc8* >( 2, "" ));
	MOAIJString deepLink = self->GetJString ( state.GetValue < cc8* >( 3, "" ));
	MOAIJString customImage = self->GetJString ( state.GetValue < cc8* >( 4, "" ));
	MOAIJString cta = self->GetJString ( state.GetValue < cc8* >( 5, "" ));

	self->CallStaticVoidMethod ( self->mJava_ShowInviteSMSDialog, ( jstring )title, ( jstring )message, ( jstring )deepLink, ( jstring )customImage, ( jstring )cta );

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_showInviteEmailDialog ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString title = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	MOAIJString message = self->GetJString ( state.GetValue < cc8* >( 2, "" ));
	MOAIJString deepLink = self->GetJString ( state.GetValue < cc8* >( 3, "" ));
	MOAIJString customImage = self->GetJString ( state.GetValue < cc8* >( 4, "" ));
	MOAIJString cta = self->GetJString ( state.GetValue < cc8* >( 5, "" ));

	self->CallStaticVoidMethod ( self->mJava_ShowInviteEmailDialog, ( jstring )title, ( jstring )message, ( jstring )deepLink, ( jstring )customImage, ( jstring )cta );

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_writeToFBDB ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString userUid = self->GetJString ( state.GetValue < cc8* >( 1, "" ));
	MOAIJString myUid = self->GetJString ( state.GetValue < cc8* >( 2, "" ));
	MOAIJString value = self->GetJString ( state.GetValue < cc8* >( 3, "" ));

	self->CallStaticVoidMethod ( self->mJava_WriteToFBDB, ( jstring )userUid, ( jstring )myUid, ( jstring )value );

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_readFromFBDB ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )

	MOAIJString uid = self->GetJString ( state.GetValue < cc8* >( 1, "" ));

	self->CallStaticVoidMethod ( self->mJava_ReadFromFBDB, ( jstring )uid );

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseAndroid::_getValuesFromFBDB ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIFirebaseAndroid, "" )
	
	JNI_GET_ENV ( jvm, env );

    jstring jstringValue = ( jstring )self->CallStaticObjectMethod ( self->mJava_GetValuesFromFBDB );	

	JNI_GET_CSTRING ( jstringValue, stringValue );

	lua_pushstring ( state, stringValue );

	JNI_RELEASE_CSTRING ( jstringValue, stringValue );

	return 1;
}

//================================================================//
// MOAIFirebaseAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIFirebaseAndroid::MOAIFirebaseAndroid () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	 
	this->SetClass ( "com/moaisdk/firebase/MoaiFirebase" );

	this->mJava_Init = this->GetStaticMethod ( "init", "()V" );
	this->mJava_FetchConfig = this->GetStaticMethod ( "fetchConfig", "()V" );
	this->mJava_ActivateFetchedConfig = this->GetStaticMethod ( "activateFetchedConfig", "()V" );
	this->mJava_GetConfigString = this->GetStaticMethod ( "getConfigString", "(Ljava/lang/String;)Ljava/lang/String;" );
	this->mJava_GetConfigBoolean = this->GetStaticMethod ( "getConfigBoolean", "(Ljava/lang/String;)Z" );
	this->mJava_GetConfigDouble = this->GetStaticMethod ( "getConfigDouble", "(Ljava/lang/String;)D" );
	this->mJava_GetConfigLong = this->GetStaticMethod ( "getConfigLong", "(Ljava/lang/String;)J" );
	this->mJava_CreateAnonymousAccountWithReferrerInfo = this->GetStaticMethod ( "createAnonymousAccountWithReferrerInfo", "(Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_GetInvitationId = this->GetStaticMethod ( "getInvitationId", "()Ljava/lang/String;" );
	this->mJava_GetInvitationDeepLink = this->GetStaticMethod ( "getInvitationDeepLink", "()Ljava/lang/String;" );
	this->mJava_CreateInvitationDeepLink = this->GetStaticMethod ( "createInvitationDeepLink", "(Ljava/lang/String;)V" );
	this->mJava_ShowInviteSMSDialog = this->GetStaticMethod ( "showInviteSMSDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_ShowInviteEmailDialog = this->GetStaticMethod ( "showInviteEmailDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_WriteToFBDB = this->GetStaticMethod ( "writeToFBDB", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V" );
	this->mJava_ReadFromFBDB = this->GetStaticMethod ( "readFromFBDB", "(Ljava/lang/String;)V" );
	this->mJava_GetValuesFromFBDB = this->GetStaticMethod ( "getValuesFromFBDB", "()Ljava/lang/String;" );
}

//----------------------------------------------------------------//
MOAIFirebaseAndroid::~MOAIFirebaseAndroid () {
}

//----------------------------------------------------------------//
void MOAIFirebaseAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "FETCH_CONFIG_SUCCEEDED",				( u32 )FETCH_CONFIG_SUCCEEDED );
	state.SetField ( -1, "FETCH_CONFIG_FAILED",					( u32 )FETCH_CONFIG_FAILED );
	state.SetField ( -1, "DEEPLINK_CREATED_SUCCEEDED",			( u32 )DEEPLINK_CREATED_SUCCEEDED );
	state.SetField ( -1, "PENDING_INVITATION_ID_SUCCEEDED",		( u32 )PENDING_INVITATION_ID_SUCCEEDED );
	state.SetField ( -1, "READ_FBDB_SUCCEEDED",					( u32 )READ_FBDB_SUCCEEDED );

	luaL_Reg regTable [] = {
		{ "init",										_init },
		{ "fetchConfig",								_fetchConfig },
		{ "activateFetchedConfig",						_activateFetchedConfig },
		{ "getConfigString",							_getConfigString },
		{ "getConfigBoolean",							_getConfigBoolean },
		{ "getConfigDouble",							_getConfigDouble },
		{ "getConfigLong",								_getConfigLong },
		{ "createAnonymousAccountWithReferrerInfo",		_createAnonymousAccountWithReferrerInfo },
		{ "getInvitationId",							_getInvitationId },
		{ "getInvitationDeepLink",						_getInvitationDeepLink },
		{ "createInvitationDeepLink",					_createInvitationDeepLink },
		{ "showInviteSMSDialog",						_showInviteSMSDialog },
		{ "showInviteEmailDialog",						_showInviteEmailDialog },
		{ "writeToFBDB",								_writeToFBDB },
		{ "readFromFBDB",								_readFromFBDB },
		{ "getValuesFromFBDB",							_getValuesFromFBDB },
		{ "getListener",								&MOAIGlobalEventSource::_getListener < MOAIFirebaseAndroid > },
		{ "setListener",								&MOAIGlobalEventSource::_setListener < MOAIFirebaseAndroid > },

		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// FirebaseConfig JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" JNIEXPORT void JNICALL Java_com_moaisdk_firebase_MoaiFirebase_AKUInvokeListener ( JNIEnv* env, jclass obj, jint eventID ) {

	if ( MOAIFirebaseAndroid::IsValid ()) {
		ZLLog::LogF ( 1, ZLLog::CONSOLE, "Java_com_moaisdk_firebase_MoaiFirebase_AKUInvokeListener\n" );
		MOAIFirebaseAndroid::Get ().InvokeListener (( u32 )eventID );
	}
}


