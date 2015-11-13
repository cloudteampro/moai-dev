// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/JniUtils.h>
#include <moai-android/MOAIWebViewAndroid.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	canGoBack
	@text	Checks if the WebView can go back.

	@in		MOAIWebViewAndroid self
	@out	nil
*/
int MOAIWebViewAndroid::_canGoBack ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_CanGoBack ));
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	canGoForward
	@text	Checks if the WebView can go forward.

	@out	nil
*/
int MOAIWebViewAndroid::_canGoForward ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIWebViewAndroid, "U" );

	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_CanGoForward ));
	return 1;	
}

//----------------------------------------------------------------//
/**	@lua	clickBack
	@text	Sends an event to the WebView that the user has clicked
			'back'.

	@out	nil
*/
int MOAIWebViewAndroid::_clickBack ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_ClickBack );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	clickForward
	@text	Sends an event to the WebView that the user has clicked
			'forward'.

	@out	nil
*/
int MOAIWebViewAndroid::_clickForward ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_ClickForward );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	clickRefresh
	@text	Sends an event to the WebView that the user has clicked
			'refresh'.

	@out	nil
*/
int MOAIWebViewAndroid::_clickRefresh ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_ClickRefresh );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	clickStop
	@text	Sends an event to the WebView that the user has clicked
			'stop'.

	@out	nil
*/
int MOAIWebViewAndroid::_clickStop ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_ClickStop );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	hide
	@text	Sets the WebView to hidden.
			
	@out	nil
*/
int MOAIWebViewAndroid::_hide ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_Hide );
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	isHidden
	@text	Returns whether or not the WebView is hidden.
	
	@out	bool isHidden
*/
int MOAIWebViewAndroid::_isHidden ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_IsHidden ));
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	isLoading
	@text	Returns whether or not the WebView is loading a page.
	
	@out	bool isLoading
*/
int MOAIWebViewAndroid::_isLoading ( lua_State *L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	lua_pushboolean ( state, self->CallStaticBooleanMethod ( self->mJava_IsLoading ));
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	isLoading
	@text	Returns whether or not the WebView is loading a page.
	
	@out	nil
*/
int MOAIWebViewAndroid::_loadHTML ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )

	jstring jhtml = self->GetJString ( lua_tostring ( state, 1 ));
	
	self->CallStaticVoidMethod ( self->mJava_LoadHTML, jhtml );	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	loadRequest
	@text	Returns whether or not the WebView is loading a page.
	
	@out	nil
*/
int MOAIWebViewAndroid::_loadRequest ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )

	jstring jurl = self->GetJString ( lua_tostring ( state, 1 ));
	
	self->CallStaticVoidMethod ( self->mJava_LoadRequest, jurl );	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	show
	@text	Shows the WebView.
	
	@out	nil
*/
int MOAIWebViewAndroid::_show ( lua_State* L ) {
	MOAI_JAVA_LUA_SETUP ( MOAIWebViewAndroid, "" )
	
	self->CallStaticVoidMethod ( self->mJava_Show );
	return 0;
}

//================================================================//
// MOAIWebViewAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIWebViewAndroid::MOAIWebViewAndroid () {

	RTTI_SINGLE ( MOAILuaObject )

	this->SetClass ( "com/ziplinegames/moai/MoaiWebView" );

	this->mJava_CanGoBack			= this->GetStaticMethod ( "canGoBack", "()Z" );
	this->mJava_CanGoForward		= this->GetStaticMethod ( "canGoForward", "()Z" );
	this->mJava_ClickBack			= this->GetStaticMethod ( "clickBack", "()V" );
	this->mJava_ClickForward		= this->GetStaticMethod ( "clickForward", "()V" );
	this->mJava_ClickRefresh		= this->GetStaticMethod ( "clickRefresh", "()V" );
	this->mJava_ClickStop			= this->GetStaticMethod ( "clickStop", "()V" );
	this->mJava_Hide				= this->GetStaticMethod ( "hide", "()V" );
	this->mJava_IsHidden			= this->GetStaticMethod ( "isHidden", "()Z" );
	this->mJava_IsLoading			= this->GetStaticMethod ( "isLoading", "()Z" );
	this->mJava_LoadHTML			= this->GetStaticMethod ( "loadHTML", "(Ljava/lang/String;)V" );
	this->mJava_LoadRequest			= this->GetStaticMethod ( "loadRequest", "(Ljava/lang/String;)V" );
	this->mJava_Show				= this->GetStaticMethod ( "show", "()V" );
}

//----------------------------------------------------------------//
MOAIWebViewAndroid::~MOAIWebViewAndroid () {}

//----------------------------------------------------------------//
void MOAIWebViewAndroid::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAIWebViewAndroid* self = &MOAIWebViewAndroid::Get ();
	
	luaL_Reg regTable [] = {
		{ "canGoBack",						_canGoBack },
		{ "canGoForward",					_canGoForward },
		{ "clickBack",						_clickBack },
		{ "clickForward",					_clickForward },
		{ "clickRefresh",					_clickRefresh },
		{ "clickStop",						_clickStop },
		{ "hide",							_hide },
		{ "isHidden",						_isHidden },
		{ "isLoading",						_isLoading },
		{ "loadHTML",						_loadHTML },
		{ "loadRequest",					_loadRequest },
		{ "show",							_show },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}
