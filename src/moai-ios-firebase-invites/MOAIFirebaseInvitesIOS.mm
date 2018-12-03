//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-firebase-invites/MOAIFirebaseInvitesIOS.h>

//================================================================//
// lua
//================================================================//


//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize FirebaseInvites.
	
	@out 	nil
*/
int MOAIFirebaseInvitesIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	
	return 0;
}

// - (IBAction)inviteTapped:(id)sender {
//   id<FIRInviteBuilder> inviteDialog = [FIRInvites inviteDialog];
//   [inviteDialog setInviteDelegate:self];

//   // NOTE: You must have the App Store ID set in your developer console project
//   // in order for invitations to successfully be sent.
//   NSString *message =
//       [NSString stringWithFormat:@"Try this out!\n -%@",
//                                  [GIDSignIn sharedInstance].currentUser.profile.name];

//   // A message hint for the dialog. Note this manifests differently depending on the
//   // received invitation type. For example, in an email invite this appears as the subject.
//   [inviteDialog setMessage:message];

//   // Title for the dialog, this is what the user sees before sending the invites.
//   [inviteDialog setTitle:@"Invites Example"];
//   [inviteDialog setDeepLink:@"app_url"];
//   [inviteDialog setCallToActionText:@"Install!"];
//   [inviteDialog setCustomImage:@"https://www.google.com/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png"];
//   [inviteDialog open];
// }

// - (void)inviteFinishedWithInvitations:(NSArray *)invitationIds error:(NSError *)error {
//   if (error) {
//     NSLog(@"%@", error.localizedDescription);
//   } else {
//     NSLog(@"%li invites sent", invitationIds.count);
//   }
// }

//================================================================//
// MOAIFirebaseInvitesIOS
//================================================================//

//----------------------------------------------------------------//
MOAIFirebaseInvitesIOS::MOAIFirebaseInvitesIOS () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIFirebaseInvitesIOS::~MOAIFirebaseInvitesIOS () {
}

//----------------------------------------------------------------//
void MOAIFirebaseInvitesIOS::RegisterLuaClass ( MOAILuaState& state ) {

	luaL_Reg regTable [] = {
		{ "init",					_init },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

