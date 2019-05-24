// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIAPPSFLYERANDROID_H
#define	MOAIAPPSFLYERANDROID_H

#include <moai-core/headers.h>
#include <moai-android/JniUtils.h>

//================================================================//
// MOAIAppsFlyerAndroid
//================================================================//
class MOAIAppsFlyerAndroid :
	public MOAIGlobalClass < MOAIAppsFlyerAndroid, MOAIGlobalEventSource >,
	public JniUtils {
private:

		jmethodID	mJava_Init;
		jmethodID	mJava_TrackAdView;
		jmethodID	mJava_TrackEvent;
		jmethodID	mJava_TrackLevelAchieved;
		jmethodID	mJava_TrackPurchase;
		jmethodID	mJava_ValidateAndTrackInAppPurchase;

		//----------------------------------------------------------------//
		static int	_init	 						( lua_State* L );
		static int	_trackAdView					( lua_State* L );
		static int	_trackEvent						( lua_State* L );
		static int	_trackLevelAchieved				( lua_State* L );
		static int	_trackPurchase					( lua_State* L );
		static int	_validateAndTrackInAppPurchase	( lua_State* L );

public:

		DECL_LUA_SINGLETON ( MOAIAppsFlyerAndroid );

		enum {
			PURCHASE_VALIDATE_FAILURE,
			PURCHASE_VALIDATE_SUCCESS
		};

		//----------------------------------------------------------------//
						MOAIAppsFlyerAndroid			();
						~MOAIAppsFlyerAndroid			();
		void			PurchaseValidateFailure			( cc8* error );
		void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIAPPSFLYER_H
