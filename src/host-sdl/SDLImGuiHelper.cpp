// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <SDL.h>

#include "SDLImGuiHelper.h"
#include <libimgui/imgui.h>
#include <moai-imgui/host.h>


//================================================================//
// helpers
//================================================================//

#define UNUSED(p) (( void )p)

//----------------------------------------------------------------//
static const char* GetClipboardText ( void* userdata ) {
	UNUSED ( userdata );
	return SDL_GetClipboardText ();
}

//----------------------------------------------------------------//
static void SetClipboardText ( void* userdata, const char* text ) {
	UNUSED ( userdata );
	SDL_SetClipboardText ( text );
}

//----------------------------------------------------------------//
void SDLImGuiContextInitialize () {
	// Will break if we make use of ImGui contexts inside MOAIImGui.
	// Currently it uses default global ImGui context.
	ImGuiIO& io = ImGui::GetIO();
	io.GetClipboardTextFn = GetClipboardText;
	io.SetClipboardTextFn = SetClipboardText;
	io.ClipboardUserData = NULL;
}

//----------------------------------------------------------------//
void SDLImGuiUpdate () {
	
	// static reusable cursors?
	static SDL_Cursor* arrow 	= SDL_CreateSystemCursor ( SDL_SYSTEM_CURSOR_ARROW );
	static SDL_Cursor* text 	= SDL_CreateSystemCursor ( SDL_SYSTEM_CURSOR_IBEAM );
	static SDL_Cursor* move 	= SDL_CreateSystemCursor ( SDL_SYSTEM_CURSOR_SIZEALL );
	static SDL_Cursor* sizeNWSE = SDL_CreateSystemCursor ( SDL_SYSTEM_CURSOR_SIZENWSE );
	static SDL_Cursor* sizeNESW = SDL_CreateSystemCursor ( SDL_SYSTEM_CURSOR_SIZENESW );
	static SDL_Cursor* sizeWE 	= SDL_CreateSystemCursor ( SDL_SYSTEM_CURSOR_SIZEWE );
	static SDL_Cursor* sizeNS 	= SDL_CreateSystemCursor ( SDL_SYSTEM_CURSOR_SIZENS );

	ImGuiMouseCursor cursor = AKUImGuiGetDesiredCursor ();
	switch ( cursor ) {
		case ImGuiMouseCursor_Arrow:
			SDL_SetCursor ( arrow );
			break;
		case ImGuiMouseCursor_TextInput:
			SDL_SetCursor ( text );
			break;
		case ImGuiMouseCursor_Move:
			SDL_SetCursor ( move );
			break;
		case ImGuiMouseCursor_ResizeNS:
			SDL_SetCursor ( sizeNS );
			break;
		case ImGuiMouseCursor_ResizeEW:
			SDL_SetCursor ( sizeWE );
			break;
		case ImGuiMouseCursor_ResizeNESW:
			SDL_SetCursor ( sizeNESW );
			break;
		case ImGuiMouseCursor_ResizeNWSE:
			SDL_SetCursor ( sizeNWSE );
			break;
	}
}
