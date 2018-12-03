//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-yandex-appmetrica/MOAIYandexAppMetricaIOS.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize YandexAppMetrica.
	
	@in 	string	apiKey			YandexAppMetrica account Api key.
	@out 	nil
*/
int MOAIYandexAppMetricaIOS::_init ( lua_State* L ) {

	NSLog ( @"MOAIYandexAppMetricaIOS: init " );
	
	MOAILuaState state ( L );
	
	cc8* apiKey = state.GetValue < cc8* >( 1, 0 );

    YMMYandexMetricaConfiguration *configuration = [[ YMMYandexMetricaConfiguration alloc ] initWithApiKey: [ NSString stringWithUTF8String:apiKey ]];
    [ YMMYandexMetrica activateWithConfiguration:configuration ];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackEvent
	@text	Tracking Event.
	
	@out 	nil
*/
int	MOAIYandexAppMetricaIOS::_trackEvent ( lua_State* L ) {

	return 0;
}

//----------------------------------------------------------------//
/**	@lua	trackLevelAchieved
	@text	Tracking Event Level Achieved.
	
	@out 	nil
*/
int	MOAIYandexAppMetricaIOS::_trackLevelAchieved ( lua_State* L ) {

	NSLog ( @"MOAIYandexAppMetricaIOS: trackLevelAchieved " );

	MOAILuaState state ( L );

	int level = state.GetValue < int >( 1, 0 );
	
	NSDictionary *params = @{@"level": [ NSNumber numberWithInt:level ]};
	[ YMMYandexMetrica reportEvent:@"Level Achieved" parameters:params onFailure: ^(NSError *error) {
		NSLog(@"MOAIYandexAppMetricaIOS: REPORT LEVEL EVENT ERROR: %@", [error localizedDescription]);
	} ];
}

//----------------------------------------------------------------//
/**	@lua	trackPurchase
	@text	Tracking Event Purchase.
	
	@out 	nil
*/
int	MOAIYandexAppMetricaIOS::_trackPurchase ( lua_State* L ) {

	NSLog ( @"MOAIYandexAppMetricaIOS: trackPurchase " );

	MOAILuaState state ( L );
	
	float revenue = state.GetValue < float >( 1, 0.0f );
	cc8* currency = state.GetValue < cc8* >( 2, 0 );
	
	YMMRevenueInfo *revenueInfo = [[ YMMRevenueInfo alloc ] initWithPrice:revenue currency:[ NSString stringWithUTF8String:currency ]];
	[ YMMYandexMetrica reportRevenue:revenueInfo onFailure: ^(NSError *error) {
		NSLog(@"MOAIYandexAppMetricaIOS: REPORT REVENUE ERROR: %@", [error localizedDescription]);
	} ];

	NSDictionary *params = @{@"value": [ NSNumber numberWithInt:revenue ], @"currency": [ NSString stringWithUTF8String:currency ]};
	[ YMMYandexMetrica reportEvent:@"Purchase" parameters:params onFailure: ^(NSError *error) {
		NSLog(@"MOAIYandexAppMetricaIOS: REPORT PURCHASE EVENT ERROR: %@", [error localizedDescription]);
	} ];
}

//================================================================//
// MOAIYandexAppMetricaIOS
//================================================================//

//----------------------------------------------------------------//
MOAIYandexAppMetricaIOS::MOAIYandexAppMetricaIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIYandexAppMetricaIOS::~MOAIYandexAppMetricaIOS () {
}

//----------------------------------------------------------------//
void MOAIYandexAppMetricaIOS::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",					_init },
		{ "trackEvent",				_trackEvent },
		{ "trackLevelAchieved",		_trackLevelAchieved },
		{ "trackPurchase",			_trackPurchase },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
