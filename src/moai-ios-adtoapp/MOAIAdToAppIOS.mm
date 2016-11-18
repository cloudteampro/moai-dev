//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-adtoapp/MOAIAdToAppIOS.h>
#import <moai-apple/NSDictionary+MOAILib.h>
#import <AdToAppSDK.h>
#import <ATALog.h>

//================================================================//
// MOAIAdToAppDelegate
//================================================================//
@interface MOAIAdToAppDelegate : NSObject < AdToAppSDKDelegate > {
@private
}
@end

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	hasInterstitial
	@text
	
	@opt 	string 		ad type. Default is to check for any type
	@out 	boolean
*/
int	MOAIAdToAppIOS::_hasInterstitial ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* type = state.GetValue < cc8* >( 1, 0 );

	if ( type ) {
		state.Push (( bool )[ AdToAppSDK hasInterstitial:[ NSString stringWithUTF8String:type ]]);
	}
	else {
		state.Push (( bool )[ AdToAppSDK hasInterstitial ]);
	}

	return 1;
}


//----------------------------------------------------------------//
/**	@name	hideInterstitial
	@text
	
	@out 	boolean
*/
int	MOAIAdToAppIOS::_hideInterstitial ( lua_State* L ) {
	MOAILuaState state ( L );

	state.Push ([ AdToAppSDK hideInterstitial ]);
	return 1;
}

//----------------------------------------------------------------//
/**	@name	init
	@text
	
	@in 	string 		appId
	@opt 	table 		modules. Any set of MOAIAdToAppIOS.IMAGE, MOAIAdToAppIOS.VIDEO, MOAIAdToAppIOS.REWARDED
	@opt 	boolean 	debug log. Default is false
	@opt 	boolean 	test mode. Default is false
	@out 	nil
*/
int	MOAIAdToAppIOS::_init ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIAdToAppIOS, "S" )

	cc8* appId 	= state.GetValue < cc8* >( 1, 0 );
	bool debug 	= state.GetValue < bool >( 3, false );
	bool test 	= state.GetValue < bool >( 4, false );

	NSArray* modules = nil;
	if ( state.IsType ( 2, LUA_TTABLE )) {
		NSMutableDictionary* dict = [[[ NSMutableDictionary alloc ] init ] autorelease ];
		[ dict initWithLua:state stackIndex:2 ];
		modules = [ dict allValues ];
	}

	if ( debug ) {
		[ AdToAppSDK enableDebugLogs ];
	}
	if ( test ) {
		[ AdToAppSDK enableTestMode ];
	}

	[ AdToAppSDK setDelegate:self->mDelegate ];
	[ AdToAppSDK startWithAppId:[ NSString stringWithUTF8String:appId ] modules:modules ];

	return 0;
}

//----------------------------------------------------------------//
/**	@name	isInterstitialVisible
	@text
	
	@out 	boolean
*/
int	MOAIAdToAppIOS::_isInterstitialVisible ( lua_State* L ) {
	MOAILuaState state ( L );

	state.Push ((bool) [ AdToAppSDK isInterstitialDisplayed ]);
	return 1;
}

//----------------------------------------------------------------//
/**	@name	showInterstitial
	@text
	
	@opt	Ad type. MOAIAdToAppIOS.IMAGE, MOAIAdToAppIOS.VIDEO, MOAIAdToAppIOS.REWARDED. 
			By default AdToAppSDK will decide what to show itself. 
	@out 	boolean
*/
int	MOAIAdToAppIOS::_showInterstitial ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* type = state.GetValue < cc8* >( 1, 0 );
	if ( type ) {
		state.Push ([ AdToAppSDK showInterstitial:[ NSString stringWithUTF8String:type ]]);
	}
	else {
		state.Push ([ AdToAppSDK showInterstitial ]);
	}
	return 1;
}


//================================================================//
// MOAIAdToAppIOS
//================================================================//

//----------------------------------------------------------------//
MOAIAdToAppIOS::MOAIAdToAppIOS () {

	RTTI_SINGLE ( MOAILuaObject )

	mDelegate = [[ MOAIAdToAppDelegate alloc ] init ];
}

//----------------------------------------------------------------//
MOAIAdToAppIOS::~MOAIAdToAppIOS () {

	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIAdToAppIOS::NotifyAdAppear ( cc8* adType ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( AD_APPEAR, state )) {
		
		state.Push ( adType );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAdToAppIOS::NotifyAdDisappear ( cc8* adType ) {

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( AD_DISAPPEAR, state )) {
		
		state.Push ( adType );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAdToAppIOS::NotifyAdReward ( int reward, cc8* currency ) {

	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( AD_REWARD, state )) {
		
		state.Push ( reward );
		state.Push ( currency );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIAdToAppIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "AD_APPEAR", 		( u32 )AD_APPEAR );
	state.SetField ( -1, "AD_DISAPPEAR", 	( u32 )AD_DISAPPEAR );
	state.SetField ( -1, "AD_REWARD", 		( u32 )AD_REWARD );

	state.SetField ( -1, "IMAGE", 			     [ ADTOAPP_IMAGE_INTERSTITIAL UTF8String ]);
	state.SetField ( -1, "VIDEO",			     [ ADTOAPP_VIDEO_INTERSTITIAL UTF8String ]);
	state.SetField ( -1, "ADTOAPP_INTERSTITIAL", [ ADTOAPP_INTERSTITIAL UTF8String ]);  //used when showInterstitial gets no type, then AdToApp decides itself what type to show
	state.SetField ( -1, "REWARDED",		     [ ADTOAPP_REWARDED_INTERSTITIAL UTF8String ]);

	luaL_Reg regTable [] = {
		{ "hasInterstitial",			_hasInterstitial },
		{ "hideInterstitial",			_hideInterstitial },
		{ "init",						_init },
		{ "isInterstitialVisible",		_isInterstitialVisible },
		{ "setListener",				&MOAIGlobalEventSource::_setListener < MOAIAdToAppIOS > },
		{ "showInterstitial",			_showInterstitial },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MOAIAdToAppDelegate
//================================================================//
@implementation MOAIAdToAppDelegate

	//================================================================//
	#pragma mark -
	#pragma mark Protocol MOAIAdToAppDelegate
	//================================================================//

	- ( void ) onAdWillAppear: ( NSString* )adType providerId: ( int )providerId {
		MOAIAdToAppIOS::Get ().NotifyAdAppear ([ adType UTF8String ]);
	}

	- ( void ) onAdDidDisappear: ( NSString* ) adType providerId: ( int )providerId {
		MOAIAdToAppIOS::Get ().NotifyAdDisappear ([ adType UTF8String ]);
	}

	- ( void ) onReward: ( int ) reward currency: ( NSString* ) gameCurrency providerId: ( int )providerId {
		MOAIAdToAppIOS::Get ().NotifyAdReward ( reward, [ gameCurrency UTF8String ]);
	}

@end

