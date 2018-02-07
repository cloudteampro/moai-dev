//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-fyber/MOAIFyberIOS.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Fyber.
	
	@in 	string	appId
	@in		string	userId
	@in		string	securityToken
	@out 	nil
*/
int MOAIFyberIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* appId = state.GetValue < cc8* >( 1, 0 );
	cc8* userId = state.GetValue < cc8* >( 2, 0 );
	cc8* token = state.GetValue < cc8* >( 3, 0 );

	FYBSDKOptions *options = [FYBSDKOptions optionsWithAppId:[ NSString stringWithUTF8String:appId ]
											userId:[ NSString stringWithUTF8String:userId ]
											securityToken:[ NSString stringWithUTF8String:token ]];
	[FyberSDK startWithOptions:options];

	// FYBSDKOptions *options = [FYBSDKOptions optionsWithAppId:@"00000" securityToken:@"000000000000000000000000"];
	// [FyberSDK startWithOptions:options];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestVideo
	@text	Request Video.
	
	@in 	nil
	@out 	nil
*/
int MOAIFyberIOS::_requestVideo ( lua_State* L ) {

	FYBRewardedVideoController *rewardedVideoController = [FyberSDK rewardedVideoController];

	[rewardedVideoController requestVideo];

	return 0;
}

//================================================================//
// MOAIFyberIOS
//================================================================//

//----------------------------------------------------------------//
MOAIFyberIOS::MOAIFyberIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )

	mDelegate = [[ MoaiFyberDelegate alloc ] init ];

	FYBRewardedVideoController *rewardedVideoController = [FyberSDK rewardedVideoController];
	rewardedVideoController.delegate = mDelegate;

	[FyberSDK instance].shouldShowToastOnReward = NO;
	[FyberSDK rewardedVideoController].shouldShowToastOnCompletion = NO;
}

//----------------------------------------------------------------//
MOAIFyberIOS::~MOAIFyberIOS () {

	[ mDelegate release ];
}

void MOAIFyberIOS::PresentRewardedVideo ( FYBRewardedVideoController* rewardedVideoController ) {

	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	[rewardedVideoController presentRewardedVideoFromViewController:rootVC];
}

//----------------------------------------------------------------//
void MOAIFyberIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "REWARDED_VIDEO_START",		( u32 )REWARDED_VIDEO_START );
	state.SetField ( -1, "REWARDED_VIDEO_COMPLETED",	( u32 )REWARDED_VIDEO_COMPLETED );
	state.SetField ( -1, "REWARDED_VIDEO_ABORTED",		( u32 )REWARDED_VIDEO_ABORTED );
	state.SetField ( -1, "REWARDED_VIDEO_ERROR",		( u32 )REWARDED_VIDEO_ERROR );

	luaL_Reg regTable [] = {
		{ "getListener",			&MOAIGlobalEventSource::_getListener < MOAIFyberIOS > },
		{ "init",					_init },
		{ "requestVideo",			_requestVideo },
		{ "setListener",			&MOAIGlobalEventSource::_setListener < MOAIFyberIOS > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MoaiFyberDelegate
//================================================================//
@implementation MoaiFyberDelegate

	//================================================================//
	#pragma mark -
	#pragma mark Protocol MoaiFyberDelegate
	//================================================================//

- (void)rewardedVideoControllerDidReceiveVideo:(FYBRewardedVideoController *)rewardedVideoController {

	MOAIFyberIOS::Get ().PresentRewardedVideo ( rewardedVideoController );
}

- (void)rewardedVideoControllerDidStartVideo:(FYBRewardedVideoController *)rewardedVideoController {

	MOAIFyberIOS::Get ().InvokeListener ( MOAIFyberIOS::REWARDED_VIDEO_START );
}

- (void)rewardedVideoController:(FYBRewardedVideoController *)rewardedVideoController didDismissVideoWithReason:(FYBRewardedVideoControllerDismissReason)reason {

    switch (reason) {
        case FYBRewardedVideoControllerDismissReasonError:
	        MOAIFyberIOS::Get ().InvokeListener ( MOAIFyberIOS::REWARDED_VIDEO_ERROR );
            break;

        case FYBRewardedVideoControllerDismissReasonUserEngaged:
            MOAIFyberIOS::Get ().InvokeListener ( MOAIFyberIOS::REWARDED_VIDEO_COMPLETED );
            break;

        case FYBRewardedVideoControllerDismissReasonAborted:
            MOAIFyberIOS::Get ().InvokeListener ( MOAIFyberIOS::REWARDED_VIDEO_ABORTED );
            break;
    }
}

@end