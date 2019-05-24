//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIAPPSFLYERIOS_H
#define	MOAIAPPSFLYERIOS_H

#include <moai-core/headers.h>

#import <AppsFlyerLib/AppsFlyerTracker.h>

@class MoaiAppsFlyerDelegate;

//================================================================//
// MOAIAppsFlyerIOS
//================================================================//
class MOAIAppsFlyerIOS :
	public MOAIGlobalClass < MOAIAppsFlyerIOS, MOAIGlobalEventSource > {
private:

	MoaiAppsFlyerDelegate* mDelegate;

	static int		_init							( lua_State* L );
	static int		_trackAdView					( lua_State* L );
	static int		_trackEvent						( lua_State* L );
	static int		_trackLevelAchieved				( lua_State* L );
	static int		_trackPurchase					( lua_State* L );
	static int		_validateAndTrackInAppPurchase	( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIAppsFlyerIOS );

	enum {
		PURCHASE_VALIDATE_FAILURE,
		PURCHASE_VALIDATE_SUCCESS
	};

	//----------------------------------------------------------------//
					MOAIAppsFlyerIOS				();
					~MOAIAppsFlyerIOS				();
	void			PurchaseValidateFailure			( NSString *error );
	void			PurchaseValidateSuccess			( NSString *result );
	void			RegisterLuaClass				( MOAILuaState& state );
};

//================================================================//
// MoaiAppsFlyerDelegate
//================================================================//
@interface MoaiAppsFlyerDelegate : NSObject < AppsFlyerTrackerDelegate > {
@private
}
@end

#endif  //MOAIAPPSFLYERIOS_H
