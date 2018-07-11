//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-vungle/MOAIVungleIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	displayAdvert
	@text	Display video
 
	@in		string	placement			Available in Vungle dashboard settings.
	@out 	bool						True, if an ad is cached and will be displayed.
 */
int	MOAIVungleIOS::_displayAdvert ( lua_State* L ) {
	MOAILuaState state ( L );
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	
	cc8* placement = lua_tostring ( state, 1 );
	
	VungleSDK* sdk = [ VungleSDK sharedSDK ];
	NSError *error = nil;
	[ sdk playAd:rootVC options:nil placementID:[ NSString stringWithUTF8String:placement ] error:&error ];
	if ( error ) {
		
		NSLog( @"MOAIVungleIOS Error encountered playing ad: %@", [error localizedDescription] );
		state.Push ( false );
	} else {
		
		state.Push ( true );
	}

	return 1;
}
	
//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Vungle.
	
	@in		string	appId			Available in Vungle dashboard settings.
	@out 	nil
*/
int MOAIVungleIOS::_init ( lua_State* L ) {
	MOAILuaState state ( L );

	cc8* identifier = state.GetValue < cc8* >( 1, 0 );
	bool debug = state.GetValue < bool >( 2, false );
	
	NSError* error = nil;
	VungleSDK* sdk = [ VungleSDK sharedSDK ];
	[ sdk setDelegate: MOAIVungleIOS::Get ().mDelegate ];
	if ( debug ) {
		[ sdk setLoggingEnabled:YES ];
	}
	[ sdk startWithAppId:[ NSString stringWithUTF8String:identifier ] error:&error ];
	
	if ( error ) {
		
		NSLog( @"MOAIVungleIOS Error initialize: %@", [error localizedDescription] );
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	isVideoAvailable
	@text	Detects if an add has been downloaded
 
 	@in		string	placement			Available in Vungle dashboard settings.
	@out 	bool						True, if an ad is cached and will be displayed.
 */
int MOAIVungleIOS::_isVideoAvailable ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* placement = state.GetValue < cc8* >( 1, 0 );
	
	VungleSDK* sdk = [ VungleSDK sharedSDK ];
	bool isAdAvailable = [ sdk isAdCachedForPlacementID:[ NSString stringWithUTF8String:placement ]];
	
	state.Push ( isAdAvailable );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	loadVideo
 	@text	Cache video for placement
 
 	@in		string	placement			Available in Vungle dashboard settings.
 */
int	MOAIVungleIOS::_loadVideo ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* placement = state.GetValue < cc8* >( 1, 0 );
	
	VungleSDK* sdk = [ VungleSDK sharedSDK ];
	NSError *error = nil;
	
	[ sdk loadPlacementWithID:[ NSString stringWithUTF8String:placement ] error:&error];
	
	if ( error ) {
		
		NSLog( @"MOAIVungleIOS Unable to load placement with reference ID :%@, Error %@", [ NSString stringWithUTF8String:placement ], [error localizedDescription] );
	}
	
	return 0;
}

//================================================================//
// MOAIVungleIOS
//================================================================//

//----------------------------------------------------------------//
MOAIVungleIOS::MOAIVungleIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	mDelegate = [[ MOAIVungleIOSDelegate alloc ] init ];
}

//----------------------------------------------------------------//
MOAIVungleIOS::~MOAIVungleIOS () {
	
	[[VungleSDK sharedSDK] setDelegate:nil];
	
	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIVungleIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "VUNGLE_INITIALIZED", 	( u32 )VUNGLE_INITIALIZED );
	state.SetField ( -1, "VUNGLE_READY", 		( u32 )VUNGLE_READY );
	state.SetField ( -1, "VUNGLE_START", 		( u32 )VUNGLE_START );
	state.SetField ( -1, "VUNGLE_FINISH", 		( u32 )VUNGLE_FINISH );

	luaL_Reg regTable [] = {
		{ "displayAdvert",		_displayAdvert },
		{ "getListener",		&MOAIGlobalEventSource::_getListener < MOAIVungleIOS > },
		{ "init",				_init },
		{ "isVideoAvailable",	_isVideoAvailable },
		{ "loadVideo",			_loadVideo },
		{ "setListener",		&MOAIGlobalEventSource::_setListener < MOAIVungleIOS > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MOAIVungleDelegate
//================================================================//
@implementation MOAIVungleIOSDelegate

	- ( void ) vungleSDKDidInitialize {
		
		NSLog(@"MOAIVungleIOS: vungleSDKDidInitialize: ");
		
		MOAIVungleIOS::Get ().InvokeListener ( MOAIVungleIOS::VUNGLE_INITIALIZED );
	}

	- ( void ) vungleAdPlayabilityUpdate:( BOOL ) isAdPlayable placementID:( nullable NSString * ) placementID error:( nullable NSError * ) error {
		UNUSED ( error );
		
		if (isAdPlayable) {
			
			NSLog(@"MOAIVungleIOS: vungleAdPlayabilityUpdate: Ad is available for Placement ID: %@", placementID);
			
			MOAIVungleIOS::Get ().InvokeListener ( MOAIVungleIOS::VUNGLE_READY );
		} else {
			
			NSLog(@"MOAIVungleIOS: vungleAdPlayabilityUpdate: Ad is NOT availablefor Placement ID: %@", placementID);
		}
	}

	- ( void ) vungleWillShowAdForPlacementID:( nullable NSString * ) placementID {
		
		NSLog(@"MOAIVungleIOS: vungleSDKwillShowAd: for Placement ID: %@", placementID);
		
		MOAIVungleIOS::Get ().InvokeListener ( MOAIVungleIOS::VUNGLE_START );
	}

	- ( void ) vungleWillCloseAdWithViewInfo:( VungleViewInfo * ) info placementID:( NSString * ) placementID {
		
		NSLog(@"MOAIVungleIOS: vungleWillCloseAdWithViewInfo: for Placement ID: %@", placementID);
		
		if (info) {
			
			NSLog(@"MOAIVungleIOS: Info about ad viewed: %@", info);
		}
		
		MOAIVungleIOS::Get ().InvokeListener ( MOAIVungleIOS::VUNGLE_FINISH );
	}

@end
