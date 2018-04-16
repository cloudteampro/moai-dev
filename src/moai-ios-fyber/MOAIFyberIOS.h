//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIFYBERIOS_H
#define	MOAIFYBERIOS_H

#include <moai-core/headers.h>

#import "FyberSDK.h"

@class MoaiFyberDelegate;

//================================================================//
// MOAIFyberIOS
//================================================================//
class MOAIFyberIOS :
	public MOAIGlobalClass < MOAIFyberIOS, MOAIGlobalEventSource > {
private:

	MoaiFyberDelegate* mDelegate;

	static int		_init							( lua_State* L );
	static int		_requestVideo					( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIFyberIOS );

	enum {
		REWARDED_VIDEO_START,
		REWARDED_VIDEO_COMPLETED,
		REWARDED_VIDEO_ABORTED,
		REWARDED_VIDEO_ERROR
	};

	//----------------------------------------------------------------//
					MOAIFyberIOS				();
					~MOAIFyberIOS				();
	void 			PresentRewardedVideo		( FYBRewardedVideoController* rewardedVideoController );
	void			RegisterLuaClass			( MOAILuaState& state );
};

//================================================================//
// MoaiFyberDelegate
//================================================================//
@interface MoaiFyberDelegate : NSObject < FYBRewardedVideoControllerDelegate > {
@private
}
@end

#endif  //MOAIFYBERIOS_H