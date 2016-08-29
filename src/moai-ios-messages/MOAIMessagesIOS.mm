//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-messages/MOAIMessagesIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_dissmiss ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )

	[ self->mViewController dissmiss ];
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getLocalParticipant ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	
	MSConversation* conversation = [ self->mViewController activeConversation ];
	if ( conversation ) {
		NSUUID* uuid = [ conversation localParticipantIdentifier ];
		state.Push ([[ uuid UUIDString ] UTF8String ]);
		return 1;
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getPresentationStyle ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	
	state.Push (( u32 )self->mViewController.presentationStyle );
	return 1;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getRemoteParticipants ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )

	MSConversation* conversation = [ self->mViewController activeConversation ];
	NSArray* users = [ conversation remoteParticipantIdentifiers ];

	lua_newtable ( L );
	int idx = 1;
	for ( NSUUID* user in users ) {
		lua_pushnumber ( state, idx++ );
		lua_pushstring ( state, [[ user UUIDString ] UTF8String ]);
		lua_settable ( state, -3 );
	}
	return 1;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getSelectedMessage ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	
	MSConversation* conversation = [ self->mViewController activeConversation ];
	
	MSMessage* message = [ conversation selectedMessage ];
	NSLog ( @"message: %@", message );
	if ( message ) {
		self->PushMessage ( state, message );
		return 1;
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_insertAttachment ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )

	// Implement
	return 0;
}

//----------------------------------------------------------------//
/** TODO
	
	@in		table		message
	@opt	boolean		update active message. default is false
	@out 	nil
	
	message table: {
		boolean shouldExpire		Delete the message after it is read. Default is false
		string url 					You pass application data with this URL
		string accessibilityLabel
		string summaryText			This text will appear for collapsable messages instead of full template
		
		string media				Path to media file. Can be PNG, JPEG, GIF, or any video supported by MediaPlayer framework
		string caption
		string subcaption
		string trailingCaption
		string trailingSubcaption
		string imageTitle
		string imageSubtitle
	}
*/
int MOAIMessagesIOS::_insertMessage ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	
	if ( state.IsType ( 1, LUA_TTABLE )) {
		
		cc8* url				= state.GetField < cc8* >( 1, "url", 0 );
		cc8* accessibilityLabel	= state.GetField < cc8* >( 1, "accessibilityLabel", 0 );
		cc8* summaryText		= state.GetField < cc8* >( 1, "summaryText", 0 );
		BOOL shouldExpire		= state.GetField < bool >( 1, "shouldExpire", false );

		cc8* media				= state.GetField < cc8* >( 1, "media", 0 );
		cc8* caption			= state.GetField < cc8* >( 1, "caption", 0 );
		cc8* subcaption			= state.GetField < cc8* >( 1, "subcaption", 0 );
		cc8* trailingCaption	= state.GetField < cc8* >( 1, "trailingCaption", 0 );
		cc8* trailingSubcaption	= state.GetField < cc8* >( 1, "trailingSubcaption", 0 );
		cc8* imageTitle			= state.GetField < cc8* >( 1, "imageTitle", 0 );
		cc8* imageSubtitle		= state.GetField < cc8* >( 1, "imageSubtitle", 0 );
		
		MSMessageTemplateLayout* layout = [[ MSMessageTemplateLayout alloc ] init ];
		layout.caption 				= caption ? [ NSString stringWithUTF8String:caption ] : nil;
		layout.subcaption 			= subcaption ? [ NSString stringWithUTF8String:subcaption ] : nil;
		layout.imageTitle 			= imageTitle ? [ NSString stringWithUTF8String:imageTitle ] : nil;
		layout.imageSubtitle 		= imageSubtitle ? [ NSString stringWithUTF8String:imageSubtitle ] : nil;
		layout.trailingCaption 		= trailingCaption ? [ NSString stringWithUTF8String:trailingCaption ] : nil;
		layout.trailingSubcaption 	= trailingSubcaption ? [ NSString stringWithUTF8String:trailingSubcaption ] : nil;
		
		layout.mediaFileURL = media ? [ NSURL fileURLWithPath:[ NSString stringWithUTF8String:media ] isDirectory:NO] : nil;
		// TODO: add convertion from MOAIImage to UIImage

		BOOL update = state.GetValue < bool >( 2, false );
		
		MSConversation* conversation = [ self->mViewController activeConversation ];
		
		MSSession* session = update ? [[ conversation selectedMessage ] session ] : nil;
		if ( !session ) {
			session = [[[ MSSession alloc ] init ] autorelease ];
		}
		MSMessage* message = [[ MSMessage alloc ] initWithSession:session];
		
		message.URL 				= url ? [ NSURL URLWithString:[ NSString stringWithUTF8String:url ]] : nil;
		message.layout 				= layout;
		message.shouldExpire 		= shouldExpire;
		message.accessibilityLabel 	= accessibilityLabel ? [ NSString stringWithUTF8String:accessibilityLabel ] : nil;
		message.summaryText 		= summaryText ? [ NSString stringWithUTF8String:summaryText ] : nil;
		
		[ conversation insertMessage:message completionHandler:^(NSError* error) {
			if ( error ) {
				NSLog ( @"Error inserting message: %@", [ error localizedDescription ]);
			}
		}];
		
		[ layout release ];
		[ message release ];
	}

	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_insertSticker ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )

	// Implement
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_insertText ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )

	// Implement
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_requestPresentation ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )

	MSMessagesAppPresentationStyle style = ( MSMessagesAppPresentationStyle )state.GetValue < u32 >( 1, 0 );
	[ self->mViewController requestPresentationStyle:style ];
	return 0;
}


//================================================================//
// MOAIMessagesIOS
//================================================================//

//----------------------------------------------------------------//
void MOAIMessagesIOS::PushMessage ( MOAILuaState& state, MSMessage* message ) {

	cc8* sender = [[ message.senderParticipantIdentifier UUIDString ] UTF8String ];
	cc8* url 	= [[ message.URL absoluteString ] UTF8String ];

	lua_newtable ( state );
	state.SetField ( -1, "sender", 				sender );
	state.SetField ( -1, "url", 				url );
	state.SetField ( -1, "accessibilityLabel", 	( cc8* )[ message.accessibilityLabel UTF8String ]);
	state.SetField ( -1, "summaryText", 		( cc8* )[ message.summaryText UTF8String ] );
}

//----------------------------------------------------------------//
MOAIMessagesIOS::MOAIMessagesIOS () {
	
	this->mViewController = nil;
	
	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIMessagesIOS::~MOAIMessagesIOS () {

	this->SetViewController ( nil );
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "STYLE_COMPACT",				( u32 )MSMessagesAppPresentationStyleCompact );
	state.SetField ( -1, "STYLE_EXPANDED",				( u32 )MSMessagesAppPresentationStyleExpanded );

	state.SetField ( -1, "EXTENSION_ACTIVATED",			( u32 )EXTENSION_ACTIVATED );
	state.SetField ( -1, "EXTENSION_DEACTIVATED",		( u32 )EXTENSION_DEACTIVATED );
	state.SetField ( -1, "MESSAGE_SELECTED",			( u32 )MESSAGE_SELECTED );
	state.SetField ( -1, "MESSAGE_RECEIVED",			( u32 )MESSAGE_RECEIVED );
	state.SetField ( -1, "MESSAGE_START_SENDING",		( u32 )MESSAGE_START_SENDING );
	state.SetField ( -1, "MESSAGE_CANCEL_SENDING",		( u32 )MESSAGE_CANCEL_SENDING );
	state.SetField ( -1, "WILL_CHANGE_PRESENTATION",	( u32 )WILL_CHANGE_PRESENTATION );
	state.SetField ( -1, "DID_CHANGE_PRESENTATION",		( u32 )DID_CHANGE_PRESENTATION );

	luaL_Reg regTable [] = {
		{ "dissmiss",					_dissmiss },
		{ "getListener",				&MOAIGlobalEventSource::_getListener < MOAIMessagesIOS > },
		{ "getLocalParticipant",		_getLocalParticipant },
		{ "getPresentationStyle",		_getPresentationStyle },
		{ "getRemoteParticipants",		_getRemoteParticipants },
		{ "getSelectedMessage",			_getSelectedMessage },
		{ "insertAttachment",			_insertAttachment },
		{ "insertMessage",				_insertMessage },
		{ "insertSticker",				_insertSticker },
		{ "insertText",					_insertText },
		{ "requestPresentation",		_requestPresentation },
		{ "setListener",				&MOAIGlobalEventSource::_setListener < MOAIMessagesIOS > },
		{ NULL, NULL }
	};
	
	luaL_register( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyActivated ( MSMessagesAppViewController* vc ) {

	this->SetViewController ( vc );
	this->InvokeListener ( EXTENSION_ACTIVATED );
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyDeactivated () {

	this->InvokeListener ( EXTENSION_DEACTIVATED );
	this->SetViewController ( nil );
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageSelected ( MSMessage* message ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( MESSAGE_SELECTED, state )) {
		this->PushMessage ( state, message );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageReceived ( MSMessage* message ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( MESSAGE_RECEIVED, state )) {
		this->PushMessage ( state, message );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageStartSending ( MSMessage* message ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( MESSAGE_START_SENDING, state )) {
		this->PushMessage ( state, message );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageCancelSending ( MSMessage* message ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( MESSAGE_CANCEL_SENDING, state )) {
		this->PushMessage ( state, message );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyWillChangePresentation ( MSMessagesAppPresentationStyle style ) {

	if ( !MOAILuaRuntime::IsValid ()) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( WILL_CHANGE_PRESENTATION, state )) {
		state.Push (( u32 )style );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyDidChangePresentation ( MSMessagesAppPresentationStyle style ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	
	if ( this->PushListener ( DID_CHANGE_PRESENTATION, state )) {
		state.Push (( u32 )style );
		state.DebugCall ( 1, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::SetViewController ( MSMessagesAppViewController* vc ) {

	if ( this->mViewController ) {
		[ this->mViewController release ];
	}
	this->mViewController = vc;
	[ this->mViewController retain ];
}

