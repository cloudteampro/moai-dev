//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIMESSAGESIOS_H
#define MOAIMESSAGESIOS_H

#include <moai-core/headers.h>

//================================================================//
// MOAIMessagesIOS
//================================================================//
class MOAIMessagesIOS :
	public MOAIGlobalClass < MOAIMessagesIOS, MOAIGlobalEventSource > {
private:
	
	MSMessagesAppViewController*		mViewController;

	//----------------------------------------------------------------//
	static int	_dissmiss					( lua_State* L );
	static int	_getLocalUser				( lua_State* L );
	static int	_getPresentationStyle		( lua_State* L );
	static int	_getRemoteUsers				( lua_State* L );
	static int	_getSelectedMessage			( lua_State* L );
	static int	_insertAttachment			( lua_State* L );
	static int	_insertMessage				( lua_State* L );
	static int	_insertSticker				( lua_State* L );
	static int	_insertText					( lua_State* L );
	static int	_requestPresentation		( lua_State* L );

	//----------------------------------------------------------------//
	MSMessage* 	GetMessage					( MOAILuaState& state, int index );
	void		PushMessage					( MOAILuaState& state, MSMessage* message );

public:

	DECL_LUA_SINGLETON ( MOAIMessagesIOS );
	
	enum {
		EXTENSION_ACTIVATED,
		EXTENSION_DEACTIVATED,

		MESSAGE_SELECTED,
		MESSAGE_RECEIVED,
		MESSAGE_START_SENDING,
		MESSAGE_CANCEL_SENDING,

		WILL_CHANGE_PRESENTATION,
		DID_CHANGE_PRESENTATION
	};

	
			MOAIMessagesIOS					();
			~MOAIMessagesIOS				();

	void	NotifyActivated					();
	void	NotifyDeactivated				();
	void	NotifyMessageSelected			( MSMessage* message );
	void	NotifyMessageReceived			( MSMessage* message );
	void	NotifyMessageStartSending		( MSMessage* message );
	void	NotifyMessageCancelSending		( MSMessage* message );
	void	NotifyWillChangePresentation	( MSMessagesAppPresentationStyle style );
	void	NotifyDidChangePresentation		( MSMessagesAppPresentationStyle style );

	void	RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIUNITYADSIOS_H
