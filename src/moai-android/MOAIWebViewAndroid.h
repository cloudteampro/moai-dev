// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIWEBVIEWANDROID_H
#define MOAIWEBVIEWANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIWebViewAndroid
//================================================================//
/**	@lua	MOAIWebViewAndroid
	@text	Wrapper for WebView interaction on Android devices.
*/
class MOAIWebViewAndroid : 
	public MOAIGlobalClass < MOAIWebViewAndroid, MOAILuaObject >,
	public JniUtils {
private:

	jmethodID	mJava_CanGoBack;
	jmethodID	mJava_CanGoForward;
	jmethodID	mJava_ClickBack;
	jmethodID	mJava_ClickForward;
	jmethodID	mJava_ClickRefresh;
	jmethodID	mJava_ClickStop;
	jmethodID	mJava_Hide;
	jmethodID	mJava_IsHidden;
	jmethodID	mJava_IsLoading;
	jmethodID	mJava_LoadHTML;
	jmethodID	mJava_LoadRequest;
	jmethodID	mJava_Show;
	
	//----------------------------------------------------------------//
	static int	_canGoBack						( lua_State* L );	
	static int	_canGoForward					( lua_State* L );		
	static int	_clickBack						( lua_State* L );
	static int	_clickForward					( lua_State* L );
	static int	_clickRefresh					( lua_State* L );
	static int	_clickStop						( lua_State* L );
	static int	_hide							( lua_State* L );
	static int	_isHidden						( lua_State* L );
	static int	_isLoading						( lua_State* L );
	static int 	_loadHTML						( lua_State* L );
	static int	_loadRequest					( lua_State* L );
	static int	_show							( lua_State* L ); 
	
public:

	DECL_LUA_FACTORY ( MOAIWebViewAndroid )
	
	//----------------------------------------------------------------//
				MOAIWebViewAndroid						();
				~MOAIWebViewAndroid						();
	void		RegisterLuaClass						( MOAILuaState& state );
};

#endif