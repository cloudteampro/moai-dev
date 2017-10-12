//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIUNITYADSIOS_H
#define MOAIUNITYADSIOS_H

#include <moai-core/headers.h>

#import <UnityAds/UnityAds.h>

@class MOAIUnityAdsIOSDelegate;

//================================================================//
// MOAIUnityAdsIOS
//================================================================//
class MOAIUnityAdsIOS :
	public ZLContextClass < MOAIUnityAdsIOS, MOAIGlobalEventSource > {
private:
	
	MOAIUnityAdsIOSDelegate*		mDelegate;
	
	//----------------------------------------------------------------//
	static int	_canShow			( lua_State* L );
	static int	_init				( lua_State* L );
	static int	_show				( lua_State* L );
	
public:

	DECL_LUA_SINGLETON ( MOAIUnityAdsIOS );
	
	enum {
		AD_WILL_SHOW,
		AD_DID_SHOW,
		AD_WILL_HIDE,
		AD_DID_HIDE,
		AD_COMPLETED,
	};
	
			MOAIUnityAdsIOS				();
			~MOAIUnityAdsIOS			();
	void	NotifyVideoCompleted		( cc8* reward, bool skipped );
	void	RegisterLuaClass			( MOAILuaState& state );
};

//================================================================//
// MOAIUnityAdsIOSDelegate
//================================================================//
@interface MOAIUnityAdsIOSDelegate : NSObject < UnityAdsDelegate > {
@private
}
@end


#endif // MOAIUNITYADSIOS_H
