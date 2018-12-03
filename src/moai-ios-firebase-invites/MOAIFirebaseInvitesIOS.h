//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAIFIREBASEINVITESIOS_H
#define	MOAIFIREBASEINVITESIOS_H

#include <moai-core/headers.h>

@class MoaiFirebaseInvitesDelegate;

//================================================================//
// MOAIFirebaseInvitesIOS
//================================================================//
class MOAIFirebaseInvitesIOS :
	public MOAIGlobalClass < MOAIFirebaseInvitesIOS, MOAIGlobalEventSource > {
private:

	static int		_init							( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAIFirebaseInvitesIOS );

	//----------------------------------------------------------------//
					MOAIFirebaseInvitesIOS			();
					~MOAIFirebaseInvitesIOS			();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif  //MOAIFIREBASEINVITESIOS_H