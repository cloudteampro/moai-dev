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
	public MOAIGlobalClass < MOAIUnityAdsIOS, MOAIGlobalEventSource > {
private:
	
	MOAIUnityAdsIOSDelegate*		mDelegate;
	
	//----------------------------------------------------------------//
	static int	_canShow			( lua_State* L );
	static int	_init				( lua_State* L );
	static int	_show				( lua_State* L );
	
public:

	DECL_LUA_SINGLETON ( MOAIUnityAdsIOS );
	
	enum {
		UNITYADS_READY,
		UNITYADS_START,
		UNITYADS_FINISH,
		UNITYADS_ERROR
	};
	
			MOAIUnityAdsIOS				();
			~MOAIUnityAdsIOS			();
	void	NotifyVideoFinished			( u32 result );
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
