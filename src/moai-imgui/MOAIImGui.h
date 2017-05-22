// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIIMGUI_H
#define MOAIIMGUI_H

//================================================================//
// MOAIImGui
//================================================================//
/**	@name	MOAIImGui
*/
class MOAIImGui :
	public MOAIGlobalClass < MOAIImGui, MOAILuaObject > {
private:
	
	//----------------------------------------------------------------//
	
public:
	
	DECL_LUA_SINGLETON ( MOAIImGui )

	//----------------------------------------------------------------//
					MOAIImGui			();
					~MOAIImGui			();
	void			RegisterLuaClass	( MOAILuaState& state );
};

#endif
