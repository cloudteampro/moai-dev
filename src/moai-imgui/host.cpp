// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-imgui/host.h>
#include <moai-imgui/MOAIImGui.h>

//================================================================//
// aku-util
//================================================================//

//----------------------------------------------------------------//
void AKUImGuiContextInitialize () {

	REGISTER_LUA_CLASS ( MOAIImGui )
	REGISTER_LUA_CLASS ( MOAIImGuiRenderable )
}
