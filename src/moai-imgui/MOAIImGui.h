// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIIMGUI_H
#define MOAIIMGUI_H

#include <libimgui/imgui.h>

//================================================================//
// MOAIImGuiVtxBuffer
//================================================================//
class MOAIImGuiVtxBuffer:
	public MOAIVertexBuffer {
public:
	void			SetData			( void* data, u32 length );
};

//================================================================//
// MOAIImGui
//================================================================//
/**	@name	MOAIImGui
*/
class MOAIImGui :
	public MOAIGlobalClass < MOAIImGui, MOAILuaObject > {
private:
	friend class MOAIImGuiRenderable;
	
	MOAILuaSharedPtr < MOAITexture >		mTexture;
	MOAILuaSharedPtr < MOAIViewport >		mViewport;
	MOAILuaSharedPtr < MOAIVertexFormat >	mVtxFormat;
	MOAILuaSharedPtr < MOAIImGuiVtxBuffer >	mVtxBuffer;

	//----------------------------------------------------------------//
	static int			_getBounds					( lua_State* L );
	static int			_getWantCaptureMouse		( lua_State* L );
	static int			_getWantCaptureKeyboard		( lua_State* L );
	static int			_getWantTextInput			( lua_State* L );
	static int			_init						( lua_State* L );
	static int			_keyDown					( lua_State* L );
	static int			_textInput					( lua_State* L );
	static int			_mouseDown					( lua_State* L );
	static int			_mouseMoved					( lua_State* L );
	static int			_newFrame					( lua_State* L );
	static int			_wheelMoved					( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIImGui )

	//----------------------------------------------------------------//
	void				InitTexture					( int width, int height, u8* pixels );
						MOAIImGui					();
						~MOAIImGui					();
	void				RegisterLuaClass			( MOAILuaState& state );
};

//================================================================//
// MOAIImGuiRenderable
//================================================================//
/**	@name	MOAIImGuiRenderable
 */
class MOAIImGuiRenderable :
	public MOAIRenderable {
public:
	
	DECL_LUA_FACTORY ( MOAIImGuiRenderable )
	
	//----------------------------------------------------------------//
						MOAIImGuiRenderable			();
						~MOAIImGuiRenderable		();
	void				Render						();
};

#endif
