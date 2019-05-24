//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-firebase/MOAIFirebaseIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize Firebase.
	
	@out 	nil
*/
int MOAIFirebaseIOS::_init ( lua_State* L ) {
	
	NSLog ( @"MOAIFirebaseIOS: init " );
	
	MOAILuaState state ( L );
	
	cc8* clientID = state.GetValue < cc8* >( 1, 0 );
	
	[FIRMessaging messaging].delegate = MOAIFirebaseIOS::Get ().mDelegate;
	[GIDSignIn sharedInstance].clientID = [ NSString stringWithUTF8String:clientID ];
	[GIDSignIn sharedInstance].delegate = MOAIFirebaseIOS::Get ().mDelegate;

	//MOAIFirebaseIOS::Get ().mDatabaseRef = [[ FIRDatabase database ] reference ];
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_fetchConfig ( lua_State* L ) {
	
	NSLog ( @"MOAIFirebaseIOS: fetchConfig " );
	
	[ MOAIFirebaseIOS::Get ().remoteConfig fetchWithCompletionHandler:^( FIRRemoteConfigFetchStatus status, NSError *error ) {
		
		if ( status == FIRRemoteConfigFetchStatusSuccess ) {
			
			NSLog ( @"MOAIFirebaseIOS: fetched config " );
			//[ MOAIFirebaseIOS::Get ().remoteConfig activateFetched ];
			MOAIFirebaseIOS::Get ().InvokeListener ( MOAIFirebaseIOS::FETCH_CONFIG_SUCCEEDED );
		} else {
			
			NSLog ( @"MOAIFirebaseIOS: not fetched " );
			NSLog ( @"MOAIFirebaseIOS: Error %@", error.localizedDescription );
			MOAIFirebaseIOS::Get ().InvokeListener ( MOAIFirebaseIOS::FETCH_CONFIG_FAILED );
		}
	}];

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_activateFetchedConfig ( lua_State *L ) {
	
	NSLog ( @"MOAIFirebaseIOS: activateFetchedConfig " );

	[ MOAIFirebaseIOS::Get ().remoteConfig activateFetched ];
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_getConfigString ( lua_State *L ) {
	
	NSLog ( @"MOAIFirebaseIOS: getConfigString " );
	
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* >( 1, 0 );
	
	NSString* value = MOAIFirebaseIOS::Get ().remoteConfig[[ NSString stringWithUTF8String:key ]].stringValue;
	
	lua_pushstring ( state, [ value UTF8String ] );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_getConfigBoolean ( lua_State *L ) {
	
	NSLog ( @"MOAIFirebaseIOS: getConfigBoolean " );
	
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* >( 1, 0 );
	
	bool value = MOAIFirebaseIOS::Get ().remoteConfig[[ NSString stringWithUTF8String:key ]].boolValue;
	
	lua_pushboolean ( state, value );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_getConfigDouble ( lua_State *L ) {
	
	NSLog ( @"MOAIFirebaseIOS: getConfigDouble " );
	
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* >( 1, 0 );
	
	NSNumber* value = MOAIFirebaseIOS::Get ().remoteConfig[[ NSString stringWithUTF8String:key ]].numberValue;
	
	lua_pushnumber ( state, [ value doubleValue ] );

	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_getConfigLong ( lua_State *L ) {
	
	NSLog ( @"MOAIFirebaseIOS: getConfigLong " );
	
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* >( 1, 0 );
	
	NSNumber* value = MOAIFirebaseIOS::Get ().remoteConfig[[ NSString stringWithUTF8String:key ]].numberValue;
	
	lua_pushnumber ( state, [ value doubleValue ] );
	
	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_enableAutoInitRemoteMessaging ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: enableAutoInitRemoteMessaging " );

	MOAILuaState state ( L );
	
	[FIRMessaging messaging].autoInitEnabled = YES;

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_createAnonymousAccountWithReferrerInfo ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: createAnonymousAccountWithReferrerInfo " );

	MOAILuaState state ( L );

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_getInvitationId ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: getInvitationId " );

	MOAILuaState state ( L );

	if(MOAIFirebaseIOS::Get ()._invitationId == nil) {
		return 0;
	}

	lua_pushstring ( state, [ MOAIFirebaseIOS::Get ()._invitationId UTF8String ]);

	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_getInvitationDeepLink ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: getInvitationDeepLink" );

	MOAILuaState state ( L );

	if(MOAIFirebaseIOS::Get ()._deepLink == nil) {
		return 0;
	}

	NSLog ( @"MOAIFirebaseIOS: getInvitationDeepLink %@", MOAIFirebaseIOS::Get ()._deepLink );

	lua_pushstring ( state, [ MOAIFirebaseIOS::Get ()._deepLink UTF8String ]);
	
	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_createInvitationDeepLink ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: createInvitationDeepLink " );
	
	MOAILuaState state ( L );
	
	cc8* uid = state.GetValue < cc8* >( 1, 0 );
	
//	NSString* encodedUid = [[ NSString stringWithUTF8String:uid ] stringByAddingPercentEncodingWithAllowedCharacters:[NSCharacterSet URLQueryAllowedCharacterSet]];
	NSString* fullUrl = [NSString stringWithFormat:@"http://fruitycat.cloudteam.pro/?invitedby=%@", [ NSString stringWithUTF8String:uid ]];
	NSURL *link = [[NSURL alloc] initWithString:fullUrl];
//	NSURL *link = [[NSURL alloc] initWithString:@"http://fruitycat.cloudteam.pro/my-page"];
	
	NSString *dynamicLinksDomain = @"cloudteam.page.link";
	FIRDynamicLinkComponents *linkBuilder = [[FIRDynamicLinkComponents alloc] initWithLink:link domain:dynamicLinksDomain];
	linkBuilder.iOSParameters = [[FIRDynamicLinkIOSParameters alloc] initWithBundleID:@"pro.cloudteam.Nashiri"];
	linkBuilder.iOSParameters.appStoreID = @"973082633";
	linkBuilder.iOSParameters.minimumAppVersion = @"1.41";
	linkBuilder.androidParameters = [[FIRDynamicLinkAndroidParameters alloc] initWithPackageName:@"pro.cloudteam.nashiri"];
	linkBuilder.androidParameters.minimumVersion = 240;
	
	[linkBuilder shortenWithCompletion:^(NSURL * _Nullable shortURL, NSArray<NSString *> * _Nullable warnings, NSError * _Nullable error) {
		
		if ( error || shortURL == nil ) { return; }

		NSLog(@"MOAIFirebaseIOS: createInvitationDeepLink The short URL is: %@", shortURL.absoluteString);

		MOAIFirebaseIOS::Get ()._deepLink = [ shortURL.absoluteString copy ];
		
		NSLog(@"MOAIFirebaseIOS: createInvitationDeepLink The short URL is: %@", MOAIFirebaseIOS::Get ()._deepLink);

		MOAIFirebaseIOS::Get ().InvokeListener ( MOAIFirebaseIOS::DEEPLINK_CREATED_SUCCEEDED );
	}];
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_showInviteSMSDialog ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: showInviteSMSDialog " );

	MOAILuaState state ( L );
	
	cc8* title = state.GetValue < cc8* >( 1, "" );
	cc8* message = state.GetValue < cc8* >( 2, "" );
	cc8* deepLink = state.GetValue < cc8* >( 3, "" );
	cc8* customImage = state.GetValue < cc8* >( 4, "" );
	cc8* cta = state.GetValue < cc8* >( 5, "" );

//	id<FIRInviteBuilder> inviteDialog = [FIRInvites inviteDialog];
//	[ inviteDialog setInviteDelegate: MOAIFirebaseIOS::Get ().mDelegate ];
//
//	FIRInvitesTargetApplication *targetApplication = [[ FIRInvitesTargetApplication alloc ] init ];
//	targetApplication.androidClientID = @"164086327400-jppiquk90pj7e6rr9ucdft4co7ghpfvq.apps.googleusercontent.com";
//	[ inviteDialog setOtherPlatformsTargetApplication:targetApplication ];
//
//	[ inviteDialog setMessage:[ NSString stringWithUTF8String:message ]];
//	[ inviteDialog setTitle:[ NSString stringWithUTF8String:title ]];
//	[ inviteDialog setDeepLink:[ NSString stringWithUTF8String:deepLink ]];
//	[ inviteDialog setCallToActionText:[ NSString stringWithUTF8String:cta ]];
//	//[ inviteDialog setCustomImage:[ NSString stringWithUTF8String:customImage ]];
//	[ inviteDialog open ];
	
	MFMessageComposeViewController *controller = [[MFMessageComposeViewController alloc] init];
	if ([ MFMessageComposeViewController canSendText ]) {
		controller.messageComposeDelegate = MOAIFirebaseIOS::Get ().mDelegate;
		// NSArray* to = [ NSArray arrayWithObject:@"" ];
		// [ controller setRecipients:to ];
		[ controller setBody:[ NSString stringWithUTF8String:message ]];
		
		if ( controller ) {
			UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
			UIViewController* rootVC = [ window rootViewController ];
			[ rootVC presentViewController:controller animated:YES completion:nil] ;
		}
		[ controller release ];
	}
	
	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_showInviteEmailDialog ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: showInviteEmailDialog " );

	MOAILuaState state ( L );
	
	cc8* title = state.GetValue < cc8* >( 1, "" );
	cc8* message = state.GetValue < cc8* >( 2, "" );
	cc8* deepLink = state.GetValue < cc8* >( 3, "" );
	cc8* customImage = state.GetValue < cc8* >( 4, "" );
	cc8* cta = state.GetValue < cc8* >( 5, "" );
	
//	id<FIRInviteBuilder> inviteDialog = [FIRInvites inviteDialog];
//	[ inviteDialog setInviteDelegate: MOAIFirebaseIOS::Get ().mDelegate ];
//
//	FIRInvitesTargetApplication *targetApplication = [[ FIRInvitesTargetApplication alloc ] init ];
//	targetApplication.androidClientID = @"164086327400-jppiquk90pj7e6rr9ucdft4co7ghpfvq.apps.googleusercontent.com";
//	[ inviteDialog setOtherPlatformsTargetApplication:targetApplication ];
//
//	[ inviteDialog setMessage:[ NSString stringWithUTF8String:message ]];
//	[ inviteDialog setTitle:[ NSString stringWithUTF8String:title ]];
//	[ inviteDialog setDeepLink:[ NSString stringWithUTF8String:deepLink ]];
//	[ inviteDialog setCallToActionText:[ NSString stringWithUTF8String:cta ]];
//	//[ inviteDialog setCustomImage:[ NSString stringWithUTF8String:customImage ]];
//	[ inviteDialog open ];

	MFMailComposeViewController* controller = [[ MFMailComposeViewController alloc ] init ];
	controller.mailComposeDelegate = MOAIFirebaseIOS::Get ().mDelegate;
	NSArray* to = [ NSArray arrayWithObject:@"" ];
	[ controller setToRecipients:to ];
	[ controller setSubject:[ NSString stringWithUTF8String:title ]];
	[ controller setMessageBody:[ NSString stringWithUTF8String:message ] isHTML:NO ];
	
	if ( controller ) {
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		[ rootVC presentViewController:controller animated:YES completion:nil] ;
	}
	[ controller release ];
	
	return 1;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_writeToFBDB ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: writeToFBDB " );

	MOAILuaState state ( L );

	cc8* userUid = state.GetValue < cc8* >( 1, "" );
	cc8* myUid = state.GetValue < cc8* >( 2, "" );
	cc8* value = state.GetValue < cc8* >( 3, "" );
	
	//FIRDatabaseReference* _ref = MOAIFirebaseIOS::Get ().mDatabaseRef;
	
	NSDictionary *dict = [[NSDictionary alloc] initWithObjectsAndKeys:[ NSString stringWithUTF8String:value ], [ NSString stringWithUTF8String:myUid ], nil];
	
	[[[ [[ FIRDatabase database ] reference ] child:@"users" ] child:[ NSString stringWithUTF8String:userUid ]] setValue:dict ];

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_readFromFBDB ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: readFromFBDB " );

	MOAILuaState state ( L );

	cc8* uid = state.GetValue < cc8* >( 1, "" );
	
	NSLog ( @"MOAIFirebaseIOS: readFromFBDB %@", [ NSString stringWithUTF8String:uid ]);
	
	//FIRDatabaseReference* _ref = MOAIFirebaseIOS::Get ().mDatabaseRef;
	
	[[[ [[ FIRDatabase database ] reference ] child:@"users" ] child:[ NSString stringWithUTF8String:uid ]] observeSingleEventOfType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
		
		NSLog ( @"MOAIFirebaseIOS: readFromFBDB success" );
		
		NSMutableDictionary* result = [[[ NSMutableDictionary alloc ] init ] autorelease ];
		
		for ( FIRDataSnapshot *child in [ snapshot children ] ) {
			
			if ( [ child key ]  ) {
				
				[ result setObject:[ child value ] forKey:[ child key ]];
			}
		}
		
		NSError *error;
		NSData *jsonData = [ NSJSONSerialization dataWithJSONObject:result options:NSJSONWritingPrettyPrinted error:&error ];
		
		if ( !jsonData ) {
			
			NSLog ( @"MOAIFirebaseIOS: readFromFBDB json error" );
		} else {
			
			NSLog ( @"MOAIFirebaseIOS: readFromFBDB json save" );
			
			NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
			
			MOAIFirebaseIOS::Get ()._valuesFromFBDB = jsonString;
			
			MOAIFirebaseIOS::Get ().InvokeListener ( MOAIFirebaseIOS::READ_FBDB_SUCCEEDED );
		}
		
	} withCancelBlock:^( NSError * _Nonnull error ) {
		
		NSLog ( @"MOAIFirebaseIOS: readFromFBDB error %@", error.localizedDescription );
	}];

	return 0;
}

//----------------------------------------------------------------//
int MOAIFirebaseIOS::_getValuesFromFBDB ( lua_State *L ) {

	NSLog ( @"MOAIFirebaseIOS: getValuesFromFBDB " );

	MOAILuaState state ( L );

	if(MOAIFirebaseIOS::Get ()._valuesFromFBDB == nil) {
		return 0;
	}

	NSLog ( @"MOAIFirebaseIOS: getValuesFromFBDB %@", MOAIFirebaseIOS::Get ()._valuesFromFBDB );

	lua_pushstring ( state, [ MOAIFirebaseIOS::Get ()._valuesFromFBDB UTF8String ]);

	return 1;
}

//================================================================//
// MOAIFirebaseIOS
//================================================================//

//----------------------------------------------------------------//
MOAIFirebaseIOS::MOAIFirebaseIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )

	mDelegate = [[ MOAIFirebaseIOSDelegate alloc ] init ];
	
	this->remoteConfig = [ FIRRemoteConfig remoteConfig ];
	FIRRemoteConfigSettings *remoteConfigSettings = [[ FIRRemoteConfigSettings alloc ] initWithDeveloperModeEnabled:YES ];
	remoteConfig.configSettings = remoteConfigSettings;
}

//----------------------------------------------------------------//
MOAIFirebaseIOS::~MOAIFirebaseIOS () {

	[ this->remoteConfig release ];
	[ mDelegate release ];
}

//----------------------------------------------------------------//
void MOAIFirebaseIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "FETCH_CONFIG_SUCCEEDED",				( u32 )FETCH_CONFIG_SUCCEEDED );
	state.SetField ( -1, "FETCH_CONFIG_FAILED",					( u32 )FETCH_CONFIG_FAILED );
	state.SetField ( -1, "DEEPLINK_CREATED_SUCCEEDED",			( u32 )DEEPLINK_CREATED_SUCCEEDED );
	state.SetField ( -1, "PENDING_INVITATION_ID_SUCCEEDED",		( u32 )PENDING_INVITATION_ID_SUCCEEDED );
	state.SetField ( -1, "READ_FBDB_SUCCEEDED",					( u32 )READ_FBDB_SUCCEEDED );

	luaL_Reg regTable [] = {
		{ "init",										_init },
		{ "fetchConfig",								_fetchConfig },
		{ "activateFetchedConfig",						_activateFetchedConfig },
		{ "getConfigString",							_getConfigString },
		{ "getConfigBoolean",							_getConfigBoolean },
		{ "getConfigDouble",							_getConfigDouble },
		{ "getConfigLong",								_getConfigLong },
		{ "enableAutoInitRemoteMessaging",				_enableAutoInitRemoteMessaging },
		{ "createAnonymousAccountWithReferrerInfo",		_createAnonymousAccountWithReferrerInfo },
		{ "getInvitationId",							_getInvitationId },
		{ "getInvitationDeepLink",						_getInvitationDeepLink },
		{ "createInvitationDeepLink",					_createInvitationDeepLink },
		{ "showInviteSMSDialog",						_showInviteSMSDialog },
		{ "showInviteEmailDialog",						_showInviteEmailDialog },
		{ "writeToFBDB",								_writeToFBDB },
		{ "readFromFBDB",								_readFromFBDB },
		{ "getValuesFromFBDB",							_getValuesFromFBDB },
		{ "getListener",								&MOAIGlobalEventSource::_getListener < MOAIFirebaseIOS > },
		{ "setListener",								&MOAIGlobalEventSource::_setListener < MOAIFirebaseIOS > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//================================================================//
// MOAIFirebaseIOSDelegate
//================================================================//
@implementation MOAIFirebaseIOSDelegate

	//----------------------------------------------------------------//
	-( void ) messaging:( FIRMessaging * )messaging didReceiveRegistrationToken:( NSString * )fcmToken {
		
		NSLog ( @"MOAIFirebaseIOSDelegate: FCM registration token: %@", fcmToken );
		NSDictionary *dataDict = [ NSDictionary dictionaryWithObject:fcmToken forKey:@"token" ];
		[[ NSNotificationCenter defaultCenter ] postNotificationName:@"FCMToken" object:nil userInfo:dataDict ];
	}

	//----------------------------------------------------------------//
	-( void ) inviteFinishedWithInvitations:( NSArray * )invitationIds error:( NSError * )error {
		if ( error ) {
			NSLog ( @"MOAIFirebaseIOSDelegate: invite error %@", error.localizedDescription );
		} else {
			NSLog ( @"MOAIFirebaseIOSDelegate: invite succeed %li invites sent", invitationIds.count );
		}
	}

	//----------------------------------------------------------------//
	-( void ) mailComposeController:( MFMailComposeViewController* )controller didFinishWithResult:( MFMailComposeResult )result error:( NSError* )error {
		UNUSED ( controller );
		UNUSED ( result );
		UNUSED ( error );
		
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		
		if ( rootVC ) {
			[ rootVC dismissViewControllerAnimated:YES completion:nil ];
		}
	}

	//----------------------------------------------------------------//
	-( void ) messageComposeViewController:( MFMessageComposeViewController * )controller didFinishWithResult:( MessageComposeResult )result {
		UNUSED ( controller );
		UNUSED ( result );
		
		UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
		UIViewController* rootVC = [ window rootViewController ];
		
		if ( rootVC ) {
			[ rootVC dismissViewControllerAnimated:YES completion:nil ];
		}
	}
@end
