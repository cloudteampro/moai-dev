#include <moai-core/pch.h>
#include <moai-sim/pch.h>
#include <moai-android/JniUtils.h>

#include <jni.h>
#include <jansson.h>

extern JavaVM* jvm;

//================================================================//
// JniUtils
//================================================================//

//----------------------------------------------------------------//
jobject JniUtils::BundleFromLua ( lua_State* L, int index ) {
	MOAILuaState state ( L );

	jclass clazz = this->Env ()->FindClass ( "android/os/Bundle" );
	jobject bundle = this->Env ()->NewObject ( clazz, this->Env ()->GetMethodID ( clazz, "<init>", "()V" ));
	jmethodID put = this->Env ()->GetMethodID ( clazz, "putString", "(Ljava/lang/String;Ljava/lang/String;)V" );

	// table is in the stack at index 'index'
	lua_pushnil ( state );  // first key
	while ( lua_next ( state, index ) != 0 ) {
		// use the 'key' (at index -2) and 'value' (at index -1)
		cc8* key = lua_tostring( state, -2 );

		if ( key != NULL ) {
			cc8* value = lua_tostring( state, -1 );
			if ( value != NULL ) {
				
				MOAIJString jkey = this->GetJString ( key );
				MOAIJString jvalue = this->GetJString ( value );

				this->Env ()->CallObjectMethod( bundle, put, ( jstring )jkey, ( jstring )jvalue );
			}
		}
		// removes 'value'; keeps 'key' for next iteration
		lua_pop ( state, 1 );
	}
	return bundle;
}

//----------------------------------------------------------------//
bool JniUtils::CallStaticBooleanMethod ( jmethodID method, ... ) {

	va_list args;
	va_start ( args, method );
	bool result = ( bool )this->Env ()->CallStaticBooleanMethodV ( this->mClass, method, args );
	va_end ( args );
	
	return result;
}

//----------------------------------------------------------------//
long JniUtils::CallStaticLongMethod ( jmethodID method, ... ) {

	va_list args;
	va_start ( args, method );
	long result = ( long )this->Env ()->CallStaticLongMethod ( this->mClass, method, args );
	va_end ( args );
	
	return result;
}

//----------------------------------------------------------------//
jobject JniUtils::CallStaticObjectMethod ( jmethodID method, ... ) {
	
	va_list args;
	va_start ( args, method );
	jobject result = this->Env ()->CallStaticObjectMethodV ( this->mClass, method, args );
	va_end ( args );
	
	return result;
}

//----------------------------------------------------------------//
void JniUtils::CallStaticVoidMethod ( jmethodID method, ... ) {
	
	va_list args;
	va_start ( args, method );
	this->Env ()->CallStaticVoidMethodV ( this->mClass, method, args );
	va_end ( args );
}

//----------------------------------------------------------------//
void JniUtils::ClearException () {
	
	if ( this->Env ()->ExceptionCheck () == JNI_TRUE ) {
		this->Env ()->ExceptionClear ();
	}
}

//----------------------------------------------------------------//
jobject JniUtils::CreateObjectOfClass () {

	 if ( !this->mClass ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Missing class; cannot create object" );
		assert ( false );
		return NULL;
	}
	jmethodID constructor = this->Env ()->GetMethodID ( this->mClass, "<init>", "()V" );
	return this->Env ()->NewObject ( this->mClass, constructor );
}

//----------------------------------------------------------------//
JNIEnv* JniUtils::Env () {
	
	JNIEnv* env;
	jvm->GetEnv (( void** )&env, JNI_VERSION_1_4 );
	return env;
}

//----------------------------------------------------------------//
jclass JniUtils::GetClass ( cc8* className ) {
	
	jclass clazz = this->Env ()->FindClass ( className );
	if ( clazz == NULL ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Unable to find java class %s", className );
		this->ClearException ();
	}
	return clazz;
}

//----------------------------------------------------------------//
jclass JniUtils::GetClassViaLoader ( cc8* className ) {

	/*
	MOAIJString jclassName = this->GetJString ( className );
	
	jclass contextClass = this->GetClass ( "android/content/Context" );
	jmethodID getClassLoader = this->GetMethod ( contextClass, "getClassLoader", "()Ljava/lang/ClassLoader;" );
	
	jclass classLoaderClass = this->GetClass ( "java/lang/ClassLoader" );
	jmethodID loadClass = this->GetMethod ( classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;" );
	
	jobject classLoader = this->Env ()->CallObjectMethod ( this->mActivity, getClassLoader );
	jclass clazz = ( jclass )( this->Env ()->CallObjectMethod ( classLoader, loadClass, jclassName ));
	
	if ( clazz == NULL ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Missing class; cannot find java class %d", className );
		this->ClearException ();
	}
	return clazz;
	*/
	return NULL;
}

//----------------------------------------------------------------//
cc8* JniUtils::GetCString ( jstring jstr ) {
	
	return ( jstr != NULL ) ? this->Env ()->GetStringUTFChars ( jstr, NULL ) : NULL;
}

//----------------------------------------------------------------//
jstring JniUtils::GetJString ( cc8* cstr ) {
	
	return ( cstr != NULL ) ? this->Env ()->NewStringUTF (( const char* )cstr ) : NULL;
}

//----------------------------------------------------------------//
jmethodID JniUtils::GetMethod ( cc8* methodName, cc8* methodSignature ) {

	this->GetMethod ( this->mClass, methodName, methodSignature );
}

//----------------------------------------------------------------//
jmethodID JniUtils::GetMethod ( jclass clazz, cc8* methodName, cc8* methodSignature ) {
	
	if ( !clazz ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Missing class; cannot find java method %d", methodName );
		this->ClearException ();
		return NULL;
	}
	
	jmethodID method = this->Env ()->GetMethodID ( clazz, methodName, methodSignature );
	
	if ( method == NULL ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Unable to find java method %s", methodName );
		this->ClearException ();
	}
	return method;
}

//----------------------------------------------------------------//
jfieldID JniUtils::GetStaticField ( cc8* fieldName ) {

	this->GetStaticField ( this->mClass, fieldName );
}

//----------------------------------------------------------------//
jfieldID JniUtils::GetStaticField ( jclass clazz, cc8* fieldName ) {
	
	if ( !clazz ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Missing class; cannot find static java field id %d", fieldName );
		this->ClearException ();
		return NULL;
	}
	
	jfieldID fieldId = this->Env ()->GetStaticFieldID ( clazz, fieldName, "Ljava/lang/String;" );
	
	if ( fieldId == NULL ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Unable to find static java field id %s", fieldName );
		this->ClearException ();
	}
	return fieldId;
}

//----------------------------------------------------------------//
jmethodID JniUtils::GetStaticMethod ( cc8* methodName, cc8* methodSignature ) {

	this->GetStaticMethod ( this->mClass, methodName, methodSignature );
}

//----------------------------------------------------------------//
jmethodID JniUtils::GetStaticMethod ( jclass clazz, cc8* methodName, cc8* methodSignature ) {
	
	if ( !clazz ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Missing class; cannot find static java method %d", methodName );
		this->ClearException ();
		return NULL;
	}
	
	jmethodID method = this->Env ()->GetStaticMethodID ( clazz, methodName, methodSignature );
	
	if ( method == NULL ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Unable to find static java method %s", methodName );
		this->ClearException ();
	}
	return method;
}

//----------------------------------------------------------------//
jstring JniUtils::GetStaticObjectField ( cc8* fieldName ) {

	return this->GetStaticObjectField ( this->mClass, fieldName );
}

//----------------------------------------------------------------//
jstring JniUtils::GetStaticObjectField ( jclass clazz, cc8* fieldName ) {

	jfieldID fieldId = this->GetStaticField ( clazz, fieldName );
	return this->GetStaticObjectField ( clazz, fieldId );
}

//----------------------------------------------------------------//
jstring JniUtils::GetStaticObjectField ( jfieldID fieldId ) {

	return this->GetStaticObjectField ( this->mClass, fieldId );
}

//----------------------------------------------------------------//
jstring JniUtils::GetStaticObjectField ( jclass clazz, jfieldID fieldId ) {

	if ( !clazz ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Missing class; cannot find static java object field" );
		this->ClearException ();
		return NULL;
	}
	
	jstring jfieldValue = ( jstring ) this->Env ()->GetStaticObjectField ( clazz, fieldId );
	
	if ( jfieldValue == NULL ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Unable to find static java object field" );
		this->ClearException ();
	}
	return jfieldValue;
}

//----------------------------------------------------------------//
void JniUtils::JsonArrayToLua ( lua_State* L, json_t* json ) {
	assert ( json->type == JSON_ARRAY );
	lua_newtable ( L );
	int size = json_array_size ( json );
	for ( int i = 0; i < size; ++i ) {
		json_t* value = json_array_get ( json, i );
		if ( value ) {
			lua_pushnumber ( L, i + 1 );
			this->JsonToLua ( L, value );
			lua_settable ( L, -3 );
		}
	}
}

//----------------------------------------------------------------//
void JniUtils::JsonObjectToLua ( lua_State* L, json_t* json ) {
	assert ( json->type == JSON_OBJECT );
	lua_newtable ( L );
	void* iter = json_object_iter ( json );
	for ( ; iter; iter = json_object_iter_next ( json, iter )) {
		cc8* key = json_object_iter_key ( iter );
		json_t* value = json_object_iter_value ( iter );
		this->JsonToLua ( L, value );
		lua_setfield ( L, -2, key );
	}
}

//----------------------------------------------------------------//
void JniUtils::JsonToLua ( lua_State* L, json_t* json ) {
	switch ( json->type ) {
		case JSON_OBJECT:
			this->JsonObjectToLua ( L, json );
			break;
		case JSON_ARRAY:
			this->JsonArrayToLua ( L, json );
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

//----------------------------------------------------------------//
void JniUtils::JsonToLua ( lua_State* L, cc8* jsonString ) {

	json_error_t error;
	json_t *json = json_loads ( jsonString, 0, &error );
	if ( json ) {
		this->JsonToLua ( L, json );
		json_decref ( json );
	}
}

//----------------------------------------------------------------//
jobject JniUtils::HashMapFromLua ( lua_State* L, int index ) {
	MOAILuaState state ( L );

	jclass clazz = this->Env ()->FindClass ( "java/util/HashMap" );
	jobject hashMap = this->Env ()->NewObject ( clazz, this->Env ()->GetMethodID ( clazz, "<init>", "()V" ));
	jmethodID put = this->Env ()->GetMethodID ( clazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;" );

	// table is in the stack at index 'index'
	lua_pushnil ( state );  // first key
	while ( lua_next ( state, index ) != 0 ) {
		// use the 'key' (at index -2) and 'value' (at index -1)
		cc8* key = lua_tostring( state, -2 );

		if( key != NULL ) {
			cc8* value = lua_tostring( state, -1 );
			if ( value != NULL ) {
				
				MOAIJString jkey = this->GetJString ( key );
				MOAIJString jvalue = this->GetJString ( value );

				this->Env ()->CallObjectMethod( hashMap, put, ( jstring )jkey, ( jstring )jvalue );
			}
		}
		// removes 'value'; keeps 'key' for next iteration
		lua_pop ( state, 1 );
	}
	return hashMap;
}

//----------------------------------------------------------------//
JniUtils::JniUtils () :
	mClass ( 0 ) {
	
	//jclass clazz = this->GetClass ( "com.ziplinegames.moai.Moai" );
	//jmethodID getActivity = this->Env ()->GetStaticMethodID ( clazz, "getActivity", "()Landroid/app/Activity;" );
	//this->mActivity = this->Env ()->CallStaticObjectMethod ( clazz, getActivity );

	//assert ( this->mActivity );
}

//----------------------------------------------------------------//
JniUtils::~JniUtils () {
}

//----------------------------------------------------------------//
void JniUtils::RegisterStringConstant ( lua_State* L, cc8* fieldKey, cc8* fieldName ) {

	this->RegisterStringConstant ( L, this->mClass, fieldKey, fieldName );
}

//----------------------------------------------------------------//
void JniUtils::RegisterStringConstant ( lua_State* L, jclass clazz, cc8* fieldKey, cc8* fieldName ) {
	MOAILuaState state ( L );

	if ( !clazz ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Missing class; cannot register static java string constant %s, %s", fieldKey, fieldName );
		this->ClearException ();
	}
	
	MOAIJString jfieldValue = this->GetStaticObjectField ( clazz, fieldName );
	
	if ( jfieldValue == NULL ) {
		ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: Unable to find static java string constant %s", fieldName );
		this->ClearException ();
	}

	cc8* fieldValue = this->GetCString (( jstring )jfieldValue );
	state.SetField ( -1, fieldKey, fieldValue );
	this->ReleaseCString (( jstring )jfieldValue, fieldValue );
}

//----------------------------------------------------------------//
void JniUtils::ReleaseCString ( jstring jstr, cc8* cstr ) {
	
	if ( jstr && cstr ) {
		this->Env ()->ReleaseStringUTFChars ( jstr, cstr );
	}
}

//----------------------------------------------------------------//
bool JniUtils::SetClass ( cc8* className ) {
	
	ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: set class %s", className );
	this->mClass = ( jclass )this->Env()->NewGlobalRef ( this->GetClass ( className ));
	return this->mClass != NULL;
}

//----------------------------------------------------------------//
bool JniUtils::SetClassViaLoader ( cc8* className ) {
	
	ZLLogF ( ZLLog::CONSOLE, "MOAI JNI: set class via loader %s", className );
	this->mClass = this->GetClassViaLoader ( className );
	return this->mClass != NULL;
}

//----------------------------------------------------------------//
jobjectArray JniUtils::StringArrayFromLua ( lua_State* L, int index ) {
	MOAILuaState state ( L );

	index = state.AbsIndex ( index );

	int numEntries = 0;
	for ( int key = 1; ; ++key ) {
		state.GetField ( index, key );
		cc8* value = state.GetValue < cc8* >( -1, 0 );
		lua_pop ( state, 1 );

		if ( !value ) {
			numEntries = key - 1;
			break;
		}
	}

	jobjectArray array = this->Env ()->NewObjectArray ( numEntries, this->Env ()->FindClass( "java/lang/String" ), 0 );
	for ( int key = 1; ; ++key ) {

		state.GetField ( index, key );
		cc8* value = state.GetValue < cc8* >( -1, 0 );
		lua_pop ( state, 1 );

		if ( value ) {
			MOAIJString jvalue = this->GetJString ( value );
			this->Env ()->SetObjectArrayElement ( array, key - 1, jvalue );
		}
		else {
			break;
		}
	}
	return array;
}

//----------------------------------------------------------------//
void JniUtils::StringArrayToLua ( lua_State* L, jobjectArray jarray ) {

	int stringCount = this->Env ()->GetArrayLength ( jarray );
	lua_newtable ( L );

	for ( int i = 0; i < stringCount; ++i ) {
		
		MOAIJString jvalue = ( jstring )( this->Env ()->GetObjectArrayElement ( jarray, i ));

		// push key; remember that lua indexing starts at 1
		lua_pushnumber ( L, i + 1 );
		
		// push string value
		cc8* value = this->GetCString ( jvalue );
		lua_pushstring ( L, value );
		this->ReleaseCString ( jvalue, value );
		
		lua_settable ( L, -3 );
	}
}
