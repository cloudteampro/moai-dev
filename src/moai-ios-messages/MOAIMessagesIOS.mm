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
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getLocalUser ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getPresentationStyle ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getRemoteUsers ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_getSelectedMessage ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}


//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_insertAttachment ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_insertMessage ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_insertSticker ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}

//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_insertText ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}


//----------------------------------------------------------------//
/** TODO
*/
int MOAIMessagesIOS::_requestPresentation ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIMessagesIOS, "" )
	return 0;
}

	
//================================================================//
// MOAIMessagesIOS
//================================================================//

//----------------------------------------------------------------//
MSMessage* MOAIMessagesIOS::GetMessage ( MOAILuaState& state, int index ) {
	return 0;
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::PushMessage ( MOAILuaState& state, MSMessage* message ) {
	
}

//----------------------------------------------------------------//
MOAIMessagesIOS::MOAIMessagesIOS () {
	
	RTTI_SINGLE ( MOAIGlobalEventSource )
}

//----------------------------------------------------------------//
MOAIMessagesIOS::~MOAIMessagesIOS () {
	
}

//----------------------------------------------------------------//
void MOAIMessagesIOS::RegisterLuaClass ( MOAILuaState& state ) {

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
		{ "getLocalUser",				_getLocalUser },
		{ "getPresentationStyle",		_getPresentationStyle },
		{ "getRemoteUsers",				_getRemoteUsers },
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
void MOAIMessagesIOS::NotifyActivated () {

}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyDeactivated () {

}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageSelected ( MSMessage* message ) {

}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageReceived ( MSMessage* message ) {

}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageStartSending ( MSMessage* message ) {

}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyMessageCancelSending ( MSMessage* message ) {

}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyWillChangePresentation ( MSMessagesAppPresentationStyle style ) {

}

//----------------------------------------------------------------//
void MOAIMessagesIOS::NotifyDidChangePresentation ( MSMessagesAppPresentationStyle style ) {

}


