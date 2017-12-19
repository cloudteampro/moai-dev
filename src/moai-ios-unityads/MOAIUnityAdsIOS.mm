//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-unityads/MOAIUnityAdsIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/** @name   init
	@text   Initialize UnityAds.
	
	@in     string  gameId      Your game id
	@opt    boolean debug       Whether debug mode is active. Default if false
	@opt    boolean test        Whether test mode is active. Default is false
	@out    nil
*/
int MOAIUnityAdsIOS::_init ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* appID = state.GetValue < cc8* >( 1, "" );
	bool debug = state.GetValue < bool >( 2, false );
	bool test  = state.GetValue < bool >( 3, false );

	// UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	// UIViewController* rootVC = [ window rootViewController ];

	[ UnityAds initialize:[ NSString stringWithUTF8String:appID ] delegate:MOAIUnityAdsIOS::Get ().mDelegate testMode:test ];
	[ UnityAds setDebugMode:debug ];
	// [[ UnityAds sharedInstance ] setTestMode:test ];

	return 0;
}

//----------------------------------------------------------------//
/** TODO

*/
int MOAIUnityAdsIOS::_canShow ( lua_State* L ) {
	MOAILuaState state ( L );

	// cc8* zone = state.GetValue < cc8* >( 1, 0 );

	// if ( zone ) {
	// 	[[ UnityAds sharedInstance ] setZone:[ NSString stringWithUTF8String:zone ]];
	// }

	// bool canShow = [[ UnityAds sharedInstance ] canShow ] && [[ UnityAds sharedInstance ] canShowAds ];

	bool canShow = [ UnityAds isReady ];

	state.Push ( canShow );

	return 1;
}

//----------------------------------------------------------------//
/** TODO

*/
int MOAIUnityAdsIOS::_show ( lua_State* L ) {   
	MOAILuaState state ( L );

	// cc8* zone = state.GetValue < cc8* >( 1, 0 );

	// if ( zone ) {
	// 	[[ UnityAds sharedInstance ] setZone:[ NSString stringWithUTF8String:zone ]];
	// }

	// if ([[ UnityAds sharedInstance ] canShow ]) {
	// 	state.Push ([[ UnityAds sharedInstance ] show ]);
	// }
	// else {
	// 	state.Push ( false );
	// }

	if ([ UnityAds isReady ]) {

		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		[ UnityAds show:rootVC ];
		state.Push ( true );
	}
	else {
		state.Push ( false );
	}

	return 1;
}
	
//================================================================//
// MOAIUnityAdsIOS
//================================================================//

//----------------------------------------------------------------//
MOAIUnityAdsIOS::MOAIUnityAdsIOS () {
	
	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	mDelegate = [[ MOAIUnityAdsIOSDelegate alloc ] init];
}

//----------------------------------------------------------------//
MOAIUnityAdsIOS::~MOAIUnityAdsIOS () {
	
	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIUnityAdsIOS::NotifyVideoFinished ( u32 result ) {
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( UNITYADS_FINISH, state )) {
		
		state.Push ( result );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIUnityAdsIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "UNITYADS_READY",		( u32 )UNITYADS_READY );
	state.SetField ( -1, "UNITYADS_START",		( u32 )UNITYADS_START );
	state.SetField ( -1, "UNITYADS_FINISH",		( u32 )UNITYADS_FINISH );
	state.SetField ( -1, "UNITYADS_ERROR",		( u32 )UNITYADS_ERROR );
	
	luaL_Reg regTable [] = {
		{ "canShow",			_canShow },
		{ "getListener",		&MOAIGlobalEventSource::_getListener < MOAIUnityAdsIOS > },
		{ "init",				_init },
		{ "setListener",		&MOAIGlobalEventSource::_setListener < MOAIUnityAdsIOS > },
		{ "show",				_show },
		{ NULL, NULL }
	};
	
	luaL_register( state, 0, regTable );
}

//================================================================//
// MOAIUnityAdsIOSDelegate
//================================================================//
@implementation MOAIUnityAdsIOSDelegate

	- ( void ) unityAdsReady:( NSString * )placementId {
		MOAIUnityAdsIOS::Get ().InvokeListener ( MOAIUnityAdsIOS::UNITYADS_READY );
	}

	- ( void ) unityAdsDidStart:( NSString * )placementId {
		MOAIUnityAdsIOS::Get ().InvokeListener ( MOAIUnityAdsIOS::UNITYADS_START );
	}

	- ( void ) unityAdsDidFinish:( NSString * )placementId withFinishState:( UnityAdsFinishState )result {
		MOAIUnityAdsIOS::Get ().NotifyVideoFinished (( int )result );
	}

	- ( void ) unityAdsDidError:( UnityAdsError )error withMessage:( NSString * )message {
		MOAIUnityAdsIOS::Get ().InvokeListener ( MOAIUnityAdsIOS::UNITYADS_ERROR );
	}

@end
