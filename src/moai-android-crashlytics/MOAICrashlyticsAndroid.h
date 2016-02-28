// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAICRASHLYTICSANDROID_H
#define MOAICRASHLYTICSANDROID_H

#include <moai-core/headers.h>
#include <moai-android-crashlytics/crashlytics_ndk.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAICrashlyticsAndroid
//================================================================//
class MOAICrashlyticsAndroid :
	public MOAIGlobalClass < MOAICrashlyticsAndroid, MOAILuaObject >,
	JniUtils {
private:

	jmethodID					mJava_Init;
	jmethodID					mJava_ReportTraceback;
	crashlytics_context_t*		mCtx;

	//----------------------------------------------------------------//
	static int	_init				( lua_State* L );
	static int	_log				( lua_State* L );
	static int	_reportTraceback	( lua_State* L );
	static int	_setBool			( lua_State* L );
	static int	_setFloat			( lua_State* L );
	static int	_setInt				( lua_State* L );
	static int	_setString			( lua_State* L );
	static int	_setUser			( lua_State* L );


public:

	DECL_LUA_SINGLETON ( MOAICrashlyticsAndroid );

	//----------------------------------------------------------------//
	void	Init 						();
	void	Log 						( cc8* message );
			MOAICrashlyticsAndroid		();
			~MOAICrashlyticsAndroid		();
	void	RegisterLuaClass			( MOAILuaState& state );
	void	Set							( cc8* key, cc8* value );
	void	SetUser 					( cc8* userId, cc8* userName, cc8* userEmail );
};

#endif
