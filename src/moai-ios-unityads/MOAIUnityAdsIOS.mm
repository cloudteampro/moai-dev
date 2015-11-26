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

	[[ UnityAds sharedInstance ] setDebugMode:debug ];
	[[ UnityAds sharedInstance ] setTestMode:test ];
	[[ UnityAds sharedInstance ] setDelegate:MOAIUnityAdsIOS::Get ().mDelegate ];

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];

	[[ UnityAds sharedInstance ] startWithGameId:[ NSString stringWithUTF8String:appID ] andViewController:rootVC ];
	return 0;
}

//----------------------------------------------------------------//
/** TODO

*/
int MOAIUnityAdsIOS::_canShow ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* zone = state.GetValue < cc8* >( 1, 0 );

	if ( zone ) {
		[[ UnityAds sharedInstance ] setZone:[ NSString stringWithUTF8String:zone ]];
	}

	bool canShow = [[ UnityAds sharedInstance ] canShow ] && [[ UnityAds sharedInstance ] canShowAds ];
	state.Push ( canShow );
	return 1;
}

//----------------------------------------------------------------//
/** TODO

*/
int MOAIUnityAdsIOS::_show ( lua_State* L ) {   
	MOAILuaState state ( L );

	cc8* zone = state.GetValue < cc8* >( 1, 0 );

	if ( zone ) {
		[[ UnityAds sharedInstance ] setZone:[ NSString stringWithUTF8String:zone ]];
	}

	if ([[ UnityAds sharedInstance ] canShow ]) {
		state.Push ([[ UnityAds sharedInstance ] show ]);
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
void MOAIUnityAdsIOS::NotifyVideoCompleted ( cc8* reward, bool skipped ) {
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( AD_COMPLETED, state )) {
		
		state.Push ( reward );
		state.Push ( skipped );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIUnityAdsIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "AD_WILL_SHOW",		( u32 )AD_WILL_SHOW );
	state.SetField ( -1, "AD_DID_SHOW",			( u32 )AD_DID_SHOW );
	state.SetField ( -1, "AD_WILL_HIDE",		( u32 )AD_WILL_HIDE );
	state.SetField ( -1, "AD_DID_HIDE",			( u32 )AD_DID_HIDE );
	state.SetField ( -1, "AD_COMPLETED",		( u32 )AD_COMPLETED );
	
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

	- ( void ) unityAdsVideoCompleted:( NSString * )rewardItemKey skipped:( BOOL )skipped {
		MOAIUnityAdsIOS::Get ().NotifyVideoCompleted ([ rewardItemKey UTF8String ], skipped );
	}

	- ( void ) unityAdsWillShow {
		MOAIUnityAdsIOS::Get ().InvokeListener ( MOAIUnityAdsIOS::AD_WILL_SHOW );
	}

	- ( void ) unityAdsDidShow {
		MOAIUnityAdsIOS::Get ().InvokeListener ( MOAIUnityAdsIOS::AD_DID_SHOW );
	}

	- ( void ) unityAdsWillHide {
		MOAIUnityAdsIOS::Get ().InvokeListener ( MOAIUnityAdsIOS::AD_WILL_HIDE );
	}

	- ( void ) unityAdsDidHide {
		MOAIUnityAdsIOS::Get ().InvokeListener ( MOAIUnityAdsIOS::AD_DID_HIDE );
	}

@end
