//----------------------------------------------------------------//
// Copyright (c) 2014 CloudTeam
// All Rights Reserved. 
// http://cloudteam.pro
//----------------------------------------------------------------//

#ifndef DISABLE_CLOUDMESSAGING

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <moai-android/moaiext-jni.h>
#include <moai-android-google-cloud-messaging/MOAIGoogleCloudMessagingAndroid.h>

#include <jansson.h>

extern JavaVM* jvm;

//================================================================//
// json
//================================================================//

//----------------------------------------------------------------//
void		_gcmJsonArrayToLua		( lua_State* L, json_t* json );
void		_gcmJsonObjectToLua		( lua_State* L, json_t* json );
void		_gcmJsonToLua			( lua_State* L, json_t* json );

//----------------------------------------------------------------//
void _gcmJsonArrayToLua ( lua_State* L, json_t* json ) {
	
	assert ( json->type == JSON_ARRAY );
	
	lua_newtable ( L );
	
	int size = json_array_size ( json );
	for ( int i = 0; i < size; ++i ) {
		
		json_t* value = json_array_get ( json, i );
		
		if ( value ) {
		
			lua_pushnumber ( L, i + 1 );
			_gcmJsonToLua ( L, value );
			lua_settable ( L, -3 );
		}
	}
}

//----------------------------------------------------------------//
void _gcmJsonObjectToLua ( lua_State* L, json_t* json ) {
	
	assert ( json->type == JSON_OBJECT );
	
	lua_newtable ( L );

	void* iter = json_object_iter ( json );
	for ( ; iter; iter = json_object_iter_next ( json, iter )) {
	
		cc8* key = json_object_iter_key ( iter );
		json_t* value = json_object_iter_value ( iter );
		
		_gcmJsonToLua ( L, value );
		lua_setfield ( L, -2, key );
	}
}

//----------------------------------------------------------------//
void _gcmJsonToLua ( lua_State* L, json_t* json ) {

	switch ( json->type ) {
	
		case JSON_OBJECT:
			_gcmJsonObjectToLua ( L, json );
			break;
		
		case JSON_ARRAY:
			_gcmJsonArrayToLua ( L, json );
			break;
		
		case JSON_STRING:
			lua_pushstring ( L, json_string_value ( json ));
			break;
		
		case JSON_INTEGER:
			lua_pushnumber ( L, static_cast<lua_Number> ( static_cast<long long> ( json_integer_value ( json ) )));
			break;
		
		case JSON_REAL:
			lua_pushnumber ( L, ( lua_Number )json_real_value ( json ));
			break;
		
		case JSON_TRUE:
			lua_pushboolean ( L, 1 );
			break;
		
		case JSON_FALSE:
			lua_pushboolean ( L, 0 );
			break;
		
		case JSON_NULL:
			lua_pushlightuserdata ( L, 0 );
			break;
	};
}

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
cc8* MOAIGoogleCloudMessagingAndroid::_luaParseTable ( lua_State* L, int idx ) {

	switch ( lua_type ( L, idx )) {

		case LUA_TSTRING: {

			cc8* str = lua_tostring ( L, idx );
			return str;
		}
	}

	return NULL;
}

//----------------------------------------------------------------//
jobject MOAIGoogleCloudMessagingAndroid::_luaReadMap( lua_State * L, int idx ) {

	MOAILuaState state ( L );
	JNI_GET_ENV ( jvm, env );

	if ( state.IsType( idx, LUA_TTABLE ) ) {

		// table is in the stack at index 'idx'
		lua_pushnil ( state );  // first key
		int numEntries = 0;
		while ( lua_next ( state, idx ) != 0 ) {
			
			// use the 'key' (at index -2) and 'value' (at index -1)
			cc8* key = _luaParseTable ( state, -2 );
			if ( key ) {
				
				cc8* value = _luaParseTable ( state, -1 );
				if ( value ) {
					++numEntries;
				}
			}			
			
			// removes 'value'; keeps 'key' for next iteration
			lua_pop ( state, 1 );
		}
				
		jclass mapClass = env->FindClass ( "java/util/HashMap" );
		jmethodID init = env->GetMethodID( mapClass, "<init>", "()V" );
		jobject hashMap = env->NewObject( mapClass, init );

		jmethodID put = env->GetMethodID( mapClass, "put",
			"(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
		
		// table is in the stack at index 'idx'
		lua_pushnil ( state );  // first key
		int curidx = 0;
		while ( lua_next ( state, idx ) != 0 ) {
			
			// use the 'key' (at index -2) and 'value' (at index -1)
			cc8* key = _luaParseTable ( state, -2 );
			if ( key ) {
				
				cc8* value = _luaParseTable ( state, -1 );
				if ( value ) {

					JNI_GET_JSTRING ( value, jvalue );
					JNI_GET_JSTRING ( key, jkey );

					env->CallObjectMethod( hashMap, put, jkey, jvalue );
					
					++curidx;
				}
			}			
			
			// removes 'value'; keeps 'key' for next iteration
			lua_pop ( state, 1 );
		}	
		return hashMap;
	}
	return NULL;
}

//----------------------------------------------------------------//
void MOAIGoogleCloudMessagingAndroid::_luaPushArrayString ( lua_State* L , char const* value ) {

    lua_pushstring ( L, value );

    lua_settable ( L, -3 );
} 

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	register
	@text	Register device in GCM.
				
	@in		string	appId			Available in Google developer console.
	@out 	nil
*/
int MOAIGoogleCloudMessagingAndroid::_register ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	JNI_GET_ENV ( jvm, env );
	
	jclass googleCloudMessaging = env->FindClass ( "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    if ( googleCloudMessaging == NULL ) {
	
		ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find java class %s", "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    } else {
	
    	jmethodID _register = env->GetStaticMethodID ( googleCloudMessaging, "register", "()V" );
   		if ( _register == NULL ) {
	
			ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find static java method %s", "register" );
		} else {
	
			env->CallStaticVoidMethod ( googleCloudMessaging, _register );		
		}
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	unregister
	@text	Unregister device in GCM.
				
	@out 	nil
*/
int MOAIGoogleCloudMessagingAndroid::_unregister ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	JNI_GET_ENV ( jvm, env );
	
	jclass googleCloudMessaging = env->FindClass ( "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    if ( googleCloudMessaging == NULL ) {
	
		ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find java class %s", "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    } else {
	
    	jmethodID _unregister = env->GetStaticMethodID ( googleCloudMessaging, "unregister", "()V" );
   		if ( _unregister == NULL ) {
	
			ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find static java method %s", "unregister" );
		} else {
	
			env->CallStaticVoidMethod ( googleCloudMessaging, _unregister );		
		}
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getToken
 	@text	Gets the CGM reg ID.
 
 	@out	string regId
*/
int MOAIGoogleCloudMessagingAndroid::_getToken ( lua_State* L ) {

	MOAILuaState state ( L );

	JNI_GET_ENV ( jvm, env );
	
	jclass googleCloudMessaging = env->FindClass ( "com/ziplinegames/moai/MoaiGoogleCloudMessaging" ); 
    if ( googleCloudMessaging == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find java class %s", "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    } else {

    	jmethodID getToken = env->GetStaticMethodID ( googleCloudMessaging, "getToken", "()Ljava/lang/String;" );
    	if ( getToken == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find static java method %s", "getToken" );
    	} else {

    		jstring jtoken = ( jstring )env->CallStaticObjectMethod ( googleCloudMessaging, getToken );	
    	
			JNI_GET_CSTRING ( jtoken, token );

			lua_pushstring ( state, token );

			JNI_RELEASE_CSTRING ( jtoken, token );

			return 1;
		}
	}

	lua_pushnil ( state );
			
	return 1;
}


//----------------------------------------------------------------//
/**	@name	getLastPush
 	@text	Gets the last push.
 
 	@out	string json string
*/
int MOAIGoogleCloudMessagingAndroid::_getLastPush ( lua_State* L ) {

	MOAILuaState state ( L );

	JNI_GET_ENV ( jvm, env );
	
	jclass googleCloudMessaging = env->FindClass ( "com/ziplinegames/moai/MoaiGoogleCloudMessaging" ); 
    if ( googleCloudMessaging == NULL ) {

		ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find java class %s", "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    } else {

    	jmethodID getLastPush = env->GetStaticMethodID ( googleCloudMessaging, "getLastPush", "()Ljava/lang/String;" );
    	if ( getLastPush == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find static java method %s", "getLastPush" );
    	} else {

    		jstring jjpush = ( jstring )env->CallStaticObjectMethod ( googleCloudMessaging, getLastPush );	

			JNI_GET_CSTRING ( jjpush, push );


			json_error_t error;

        	json_t *json = json_loads(push, 0, &error);

			if ( json ) {
			
				_gcmJsonToLua ( state, json );
				json_decref ( json );
			}

			JNI_RELEASE_CSTRING ( jjpush, push );

			return 1;
		}
	}

	lua_pushnil ( state );
			
	return 1;
}


//----------------------------------------------------------------//
/**	@name	remove last push
				
	@out 	nil
*/
int MOAIGoogleCloudMessagingAndroid::_removeLastPush ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	JNI_GET_ENV ( jvm, env );
	
	jclass googleCloudMessaging = env->FindClass ( "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    if ( googleCloudMessaging == NULL ) {
	
		ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find java class %s", "com/ziplinegames/moai/MoaiGoogleCloudMessaging" );
    } else {
	
    	jmethodID removeLastPush = env->GetStaticMethodID ( googleCloudMessaging, "removeLastPush", "()V" );
   		if ( removeLastPush == NULL ) {
	
			ZLLog::LogF ( ZLLog::CONSOLE, "MoaiGoogleCloudMessaging: Unable to find static java method %s", "removeLastPush" );
		} else {
	
			env->CallStaticVoidMethod ( googleCloudMessaging, removeLastPush );		
		}
	}
	
	return 0;
}


//================================================================//
// MOAIGoogleCloudMessagingAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIGoogleCloudMessagingAndroid::MOAIGoogleCloudMessagingAndroid () {

	RTTI_SINGLE ( MOAILuaObject )
	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIGoogleCloudMessagingAndroid::~MOAIGoogleCloudMessagingAndroid () {

}

//----------------------------------------------------------------//
void MOAIGoogleCloudMessagingAndroid::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "REGISTERED",			( u32 )REGISTERED );
	state.SetField ( -1, "UNREGISTERED",		( u32 )UNREGISTERED );
	state.SetField ( -1, "MESSAGE", 			( u32 )MESSAGE );
	state.SetField ( -1, "ERROR", 				( u32 )ERROR );

	luaL_Reg regTable [] = {
		{ "register",					_register },
		{ "unregister",					_unregister },
		{ "getToken",					_getToken },
		{ "getLastPush",				_getLastPush },
		{ "removeLastPush",				_removeLastPush },
		{ "setListener",				&MOAIGlobalEventSource::_setListener < MOAIGoogleCloudMessagingAndroid > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGoogleCloudMessagingAndroid::NotifyRegistered ( cc8* result ) {

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( REGISTERED, state )) {
		
		if ( result ) {
			
			state.Push ( result );
			state.DebugCall ( 1, 0 );
		}
		else {
			state.DebugCall ( 0, 0 );
		}
	}
}

//----------------------------------------------------------------//
void MOAIGoogleCloudMessagingAndroid::NotifyUnregistered ( cc8* result ) {

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( UNREGISTERED, state )) {
		
		if ( result ) {
			
			state.Push ( result );
			state.DebugCall ( 1, 0 );
		}
		else {
			state.DebugCall ( 0, 0 );
		}
	}
}

//----------------------------------------------------------------//
void MOAIGoogleCloudMessagingAndroid::NotifyMessage ( cc8* result ) {

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( MESSAGE, state )) {
		
		if ( result ) {
			
			json_error_t error;

        	json_t *json = json_loads(result, 0, &error);

			if ( json ) {
			
				_gcmJsonToLua ( state, json );
				json_decref ( json );
			}

			state.DebugCall ( 1, 0 );
		}
		else {
			state.DebugCall ( 0, 0 );
		}
	}
}

//----------------------------------------------------------------//
void MOAIGoogleCloudMessagingAndroid::NotifyError ( cc8* result ) {

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( ERROR, state )) {
		
		if ( result ) {
			
			state.Push ( result );
			state.DebugCall ( 1, 0 );
		}
		else {
			state.DebugCall ( 0, 0 );
		}
	}
}

//================================================================//
// MOAIGoogleCloudMessagingAndroid JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiGoogleCloudMessaging_AKUNotifyRegistered ( JNIEnv* env, jclass obj, jstring jresult ) { 

	JNI_GET_CSTRING ( jresult, result );
	
	MOAIGoogleCloudMessagingAndroid::Get ().NotifyRegistered ( result );
	
	JNI_RELEASE_CSTRING ( jresult, result );	
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiGoogleCloudMessaging_AKUNotifyUnregistered ( JNIEnv* env, jclass obj, jstring jresult ) { 

	JNI_GET_CSTRING ( jresult, result );
	
	MOAIGoogleCloudMessagingAndroid::Get ().NotifyUnregistered ( result );
	
	JNI_RELEASE_CSTRING ( jresult, result );	
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiGoogleCloudMessaging_AKUNotifyMessage ( JNIEnv* env, jclass obj, jstring jresult ) { 

	JNI_GET_CSTRING ( jresult, result );
	
	MOAIGoogleCloudMessagingAndroid::Get ().NotifyMessage ( result );
	
	JNI_RELEASE_CSTRING ( jresult, result );	
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiGoogleCloudMessaging_AKUNotifyError ( JNIEnv* env, jclass obj, jstring jerror ) { 

	JNI_GET_CSTRING ( jerror, error );
	
	MOAIGoogleCloudMessagingAndroid::Get ().NotifyError ( error );
	
	JNI_RELEASE_CSTRING ( jerror, error );	
}

#endif
