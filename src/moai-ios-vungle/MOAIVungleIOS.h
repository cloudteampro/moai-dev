//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIVUNGLEIOS_H
#define	MOAIVUNGLEIOS_H

#include <moai-core/headers.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <VungleSDK/VungleSDK.h>

@class MOAIVungleIOSDelegate;

//================================================================//
// MOAIVungleIOS
//================================================================//
class MOAIVungleIOS :
	public MOAIGlobalClass < MOAIVungleIOS, MOAIGlobalEventSource > {
private:

	MOAIVungleIOSDelegate*		mDelegate;
	
	//----------------------------------------------------------------//
	static int		_displayAdvert				( lua_State* L );
	static int		_init						( lua_State* L );
	static int		_isVideoAvailable			( lua_State* L );
	static int		_loadVideo					( lua_State* L );
	
public:
		
	enum {
		VUNGLE_INITIALIZED,
		VUNGLE_READY,
		VUNGLE_START,
		VUNGLE_FINISH
	};

	DECL_LUA_SINGLETON ( MOAIVungleIOS );

	//----------------------------------------------------------------//
					MOAIVungleIOS				();
					~MOAIVungleIOS				();
	void			RegisterLuaClass			( MOAILuaState& state );
};

//================================================================//
// MOAIVungleDelegate
//================================================================//
@interface MOAIVungleIOSDelegate : NSObject < VungleSDKDelegate > {
@private
}
@end

#endif  //MOAIVUNGLEIOS_H
