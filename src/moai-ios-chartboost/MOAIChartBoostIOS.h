//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAICHARTBOOSTIOS_H
#define	MOAICHARTBOOSTIOS_H

#include <moai-core/headers.h>

// those two are needed for chartboost headers
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import <Chartboost/Chartboost.h>

@class MoaiChartBoostDelegate;

//================================================================//
// MOAIChartBoostIOS
//================================================================//
class MOAIChartBoostIOS :
	public MOAIGlobalClass < MOAIChartBoostIOS, MOAIGlobalEventSource > {
private:

	MoaiChartBoostDelegate*	mDelegate;

	//----------------------------------------------------------------//
	static int		_cacheInterstitial				( lua_State* L );
	static int		_cacheRewardedVideo				( lua_State* L );
	static int		_hasCachedInterstitial			( lua_State* L );
	static int		_hasRewardedVideo				( lua_State* L );
	static int		_init							( lua_State* L );
	static int		_showInterstitial				( lua_State* L );
	static int		_showRewardedVideo				( lua_State* L );
	
public:

	DECL_LUA_SINGLETON ( MOAIChartBoostIOS );

	enum {
		INTERSTITIAL_LOAD_FAILED,
		INTERSTITIAL_DISMISSED,
		REWARDED_VIDEO_DISMISSED,
		REWARDED_VIDEO_WILL_START,
		REWARDED_VIDEO_COMPLETED,
		TOTAL
	};
	
	//----------------------------------------------------------------//
					MOAIChartBoostIOS				();
					~MOAIChartBoostIOS				();
	void 			NotifyRewardedVideoCompleted	( int reward );
	void			RegisterLuaClass				( MOAILuaState& state );
};

//================================================================//
// MoaiChartBoostDelegate
//================================================================//
@interface MoaiChartBoostDelegate : NSObject < ChartboostDelegate > {
@private
}
@end

#endif  //MOAICHARTBOOSTIOS_H
