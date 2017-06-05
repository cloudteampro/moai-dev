// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#include <moai-sim/MOAIKeyCodeEnum.h>
#include <moai-imgui/MOAIImGui.h>
#include <moai-imgui/wrap_imgui_impl.h>

#ifdef MOAI_OS_WINDOWS
	#define NOC_FILE_DIALOG_IMPLEMENTATION
	#define NOC_FILE_DIALOG_WIN32
#endif
#include <moai-imgui/noc_file_dialog.h>

#define FTS_FUZZY_MATCH_IMPLEMENTATION
#include <moai-imgui/fts_fuzzy_match.h>

//================================================================//
// MOAIFuzzySearchResult
//================================================================//
class MOAIFuzzySearchResult :
	public ZLRadixKey32Base {
public:
	cc8*	mData;
};

//================================================================//
// lua
//================================================================//

int MOAIImGui::_endFrame ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	self->mDesiredCursor = ImGui::GetMouseCursor ();
	ImGui::Render ();
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_getBounds ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )

	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_getWantCaptureMouse ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_getWantCaptureKeyboard ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_getWantTextInput ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	fuzzyMatch
	@text	Perform fuzzy match and sort like Sublime Text does.

	@in		table	Table of strings to search matches in
	@in		string	Pattern
	@opt	number	Results limit

	@out	table	Subset of input table sorted by match score.
*/
int MOAIImGui::_fuzzyMatch ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "TS" )

	cc8* pattern = state.GetValue < cc8* >( 2, "" );

	u32 size = state.GetTableSize ( 1 );
	cc8** inputArray = new cc8* [ size ];
	for ( u32 i = 0; i < size; ++i ) {
		inputArray [ i ] = state.GetField < cc8* >( 1, i + 1, "" );
	}

	// resizing ZLLeanArray is costly operation: memory alloc + copy old values
	// so keeping this large enough
	u32 chunkSize = 128;
	ZLLeanArray < MOAIFuzzySearchResult > resultBuffer;
	if ( size < chunkSize ) {
		resultBuffer.Resize ( size );
	}

	u32 total = 0;
	for ( u32 i = 0; i < size; ++i ) {

		int score = 0;
		cc8* str = inputArray [ i ];
		if ( fts::fuzzy_match ( pattern, inputArray [ i ], score )) {
			if ( total >= resultBuffer.Size ()) {
				resultBuffer.Grow ( total + 1, chunkSize );
			}

			resultBuffer [ total ].mKey = 0 - score; // sort descending
			resultBuffer [ total ].mData = inputArray [ i ];
			total++;
		}
	}

	delete [] inputArray;

	RadixSort32 < MOAIFuzzySearchResult >( resultBuffer.Data (), total );
	lua_newtable ( L );
	
	for ( u32 i = 0; i < total; ++i ) {
		state.SetFieldByIndex < cc8* >( -1, i + 1, resultBuffer [ i ].mData );
	}
	return 1;
}

//----------------------------------------------------------------//
int MOAIImGui::_init ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	if ( !self->mViewport ) {
		MOAIViewport* viewport = new MOAIViewport ();
		viewport->SetOffset ( -1, 1 );
		self->mViewport.Set ( *self, viewport );
	}
	
	if ( !self->mVtxFormat ) {
		MOAIVertexFormat* vtxFormat = new MOAIVertexFormat ();
		vtxFormat->DeclareAttribute ( 0, ZGL_TYPE_FLOAT, 2, MOAIVertexFormat::ARRAY_VERTEX, false );
		vtxFormat->DeclareAttribute ( 1, ZGL_TYPE_FLOAT, 2, MOAIVertexFormat::ARRAY_TEX_COORD, false );
		vtxFormat->DeclareAttribute ( 2, ZGL_TYPE_UNSIGNED_BYTE, 4, MOAIVertexFormat::ARRAY_COLOR, true );
		self->mVtxFormat.Set ( *self, vtxFormat );
		
		assert ( self->mVtxFormat->GetVertexSize () == sizeof ( ImDrawVert ));
	}
	
	if ( !self->mVtxBuffer ) {
		MOAIImGuiVtxBuffer* vtxBuffer = new MOAIImGuiVtxBuffer ();
		self->mVtxBuffer.Set ( *self, vtxBuffer );
	}
	
	cc8* iniPath = state.GetValue < cc8* >( 1, "imgui.ini" );

	ImGuiIO& io = ImGui::GetIO ();

	// Create the texture object
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32 ( &pixels, &width, &height );
	self->InitTexture ( width, height, pixels );

	io.KeyMap [ ImGuiKey_Tab ]			= MOAI_KEY_TAB;
	io.KeyMap [ ImGuiKey_LeftArrow ]	= MOAI_KEY_LEFT;
	io.KeyMap [ ImGuiKey_RightArrow ]	= MOAI_KEY_RIGHT;
	io.KeyMap [ ImGuiKey_UpArrow ]		= MOAI_KEY_UP;
	io.KeyMap [ ImGuiKey_DownArrow ]	= MOAI_KEY_DOWN;
	io.KeyMap [ ImGuiKey_PageUp ]		= MOAI_KEY_PAGE_UP;
	io.KeyMap [ ImGuiKey_PageDown ]		= MOAI_KEY_PAGE_DOWN;
	io.KeyMap [ ImGuiKey_Home ]			= MOAI_KEY_HOME;
	io.KeyMap [ ImGuiKey_End ]			= MOAI_KEY_END;
	io.KeyMap [ ImGuiKey_Delete ]		= MOAI_KEY_DELETE;
	io.KeyMap [ ImGuiKey_Backspace ]	= MOAI_KEY_BACKSPACE;
	io.KeyMap [ ImGuiKey_Enter ]		= MOAI_KEY_RETURN;
	io.KeyMap [ ImGuiKey_Escape ]		= MOAI_KEY_ESCAPE;
	io.KeyMap [ ImGuiKey_A ]			= MOAI_KEY_A;
	io.KeyMap [ ImGuiKey_C ]			= MOAI_KEY_C;
	io.KeyMap [ ImGuiKey_V ]			= MOAI_KEY_V;
	io.KeyMap [ ImGuiKey_X ]			= MOAI_KEY_X;
	io.KeyMap [ ImGuiKey_Y ]			= MOAI_KEY_Y;
	io.KeyMap [ ImGuiKey_Z ]			= MOAI_KEY_Z;

	io.Fonts->TexID = ( void * )self->mTexture;
	io.IniFilename = iniPath;
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_newFrame ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	MOAIGfxDevice& device = MOAIGfxDevice::Get ();
	
	float w = state.GetValue < float >( 1, device.GetWidth ());
	float h = state.GetValue < float >( 2, device.GetHeight ());
	float dt = state.GetValue < float >( 3, 1.0f / 60.f );
	
	self->mViewport->Init ( 0.f, 0.f, w, h );
	self->mViewport->SetScale ( w, -h );
	
	ImGuiIO& io = ImGui::GetIO ();
	
	io.DisplaySize = ImVec2 ( w, h );
	io.DisplayFramebufferScale = ImVec2 ( 1.0f, 1.0f );
	io.DeltaTime = dt;
	
	ImGui::NewFrame ();
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	openFileDialog
	@text	Native file dialog
	
	@opt	number	flags. Bitwise combination of MOAIImGui.FILE_DIALOG_OPEN, MOAIImGui.FILE_DIALOG_SAVE
					MOAIImGui.FILE_DIALOG_DIR, MOAIImGui.FILE_DIALOG_CONFIRM
	@opt	string	Filter list.
					A list of strings separated by '\0' of the form:
						"name1 reg1 name2 reg2 ..."
					The last value is followed by two '\0'.
					For example, to filter png and jpeg files, you can use:
						"png\0*.png\0jpeg\0*.jpeg\0"
					You can also separate patterns with ';':
						"jpeg\0*.jpg;*.jpeg\0"
	@opt	string	Default directory path to use
	@opt	string	Default file name to use
	
	@out	string	User selected file name. nil if canceled
*/
int MOAIImGui::_openFileDialog ( lua_State *L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	u32 flags	= state.GetValue < u32 >( 1, NOC_FILE_DIALOG_OPEN );
	cc8* filter = state.GetValue < cc8* >( 2, 0 );
	cc8* dir	= state.GetValue < cc8* >( 3, 0 );
	cc8* name	= state.GetValue < cc8* >( 4, 0 );
	
	cc8* result = noc_file_dialog_open ( flags, filter, dir, name );
	if ( result ) {
		state.Push ( result );
		return 1;
	}
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_setKeyDown ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	u32 key = state.GetValue < u32 >( 1, 0 );
	bool down = state.GetValue < bool >( 2, false );
	
	ImGuiIO& io = ImGui::GetIO();
	
	switch ( key ) {
		case MOAI_KEY_SHIFT:
			io.KeyShift = down;
			break;
		
		case MOAI_KEY_CONTROL:
			io.KeyCtrl = down;
			break;
		
		case MOAI_KEY_ALT:
			io.KeyAlt = down;
			break;
		
		case MOAI_KEY_GUI:
			io.KeySuper = down;
			break;

		default:
			io.KeysDown [ key ] = down;
	}
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_setTextInput ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	cc8* str = state.GetValue < cc8* >( 1, 0 );
	if ( str ) {
		ImGui::GetIO ().AddInputCharactersUTF8 ( str );
	}

	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_setMouseMoved ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )

	float x = state.GetValue < float >( 1, -1 );
	float y = state.GetValue < float >( 2, -1 );
	
	ImGui::GetIO ().MousePos = ImVec2 ( x, y );
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_setMouseDown ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )

	u32 button = state.GetValue < u32 >( 1, 0 );
	bool down = state.GetValue < bool >( 2, false );

	ImGuiIO& io = ImGui::GetIO ();
	io.MouseDown [ button ] = down;
	
	return 0;
}

//----------------------------------------------------------------//
int MOAIImGui::_setWheelDelta ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIImGui, "" )
	
	float delta = state.GetValue < float >( 1, 0.f );
	ImGui::GetIO ().MouseWheel = delta;
	return 0;
}


//================================================================//
// MOAIImGui
//================================================================//

//----------------------------------------------------------------//
MOAIImGui::MOAIImGui () :
	mDesiredCursor ( ImGuiMouseCursor_Arrow ) {
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIImGui::~MOAIImGui () {
	this->mTexture.Set ( *this, 0 );
	this->mViewport.Set ( *this, 0 );
	this->mVtxFormat.Set ( *this, 0 );
	this->mVtxBuffer.Set ( *this, 0 );
}

//----------------------------------------------------------------//
void MOAIImGui::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "FILE_DIALOG_OPEN",			( u32 )NOC_FILE_DIALOG_OPEN );
	state.SetField ( -1, "FILE_DIALOG_SAVE",			( u32 )NOC_FILE_DIALOG_SAVE );
	state.SetField ( -1, "FILE_DIALOG_DIR",				( u32 )NOC_FILE_DIALOG_DIR );
	state.SetField ( -1, "FILE_DIALOG_CONFIRM",			( u32 )NOC_FILE_DIALOG_OVERWRITE_CONFIRMATION );
	
	luaL_Reg regTable [] = {
		{ "endFrame",					_endFrame },
		{ "fuzzyMatch",					_fuzzyMatch },
		{ "getBounds",					_getBounds },
		{ "getWantCaptureMouse",		_getWantCaptureMouse },
		{ "getWantCaptureKeyboard",		_getWantCaptureKeyboard },
		{ "getWantTextInput",			_getWantTextInput },
		{ "init",						_init },
		{ "newFrame",					_newFrame },
		{ "openFileDialog",				_openFileDialog },
		{ "setKeyDown",					_setKeyDown },
		{ "setTextInput",				_setTextInput },
		{ "setMouseDown",				_setMouseDown },
		{ "setMouseMoved",				_setMouseMoved },
		{ "setWheelDelta",				_setWheelDelta },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );

	// all other ImGui API will be under "imgui"
	luaopen_imgui ( state );
	state.Pop ();
}

//----------------------------------------------------------------//
void MOAIImGui::InitTexture ( int width, int height, u8 *pixels ) {
	
	MOAIImage* img = new MOAIImage ();
	img->Init ( pixels, width, height, ZLColor::RGBA_8888 );
	
	MOAITexture* texture = new MOAITexture ();
	texture->Init ( *img, "imgui_font_tex", true );
	this->mTexture.Set ( *this, texture );
}

//================================================================//
// MOAIImGuiVtxBuffer
//================================================================//

//----------------------------------------------------------------//
void MOAIImGuiVtxBuffer::SetData ( void *data, u32 length ) {
	
	this->SetBuffer (( const void* )data, length, length );
	this->mData = data;
}

//----------------------------------------------------------------//
MOAIImGuiVtxBuffer::MOAIImGuiVtxBuffer () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIVertexBuffer )
	RTTI_END
}


//================================================================//
// MOAIImGuiRenderable
//================================================================//

//----------------------------------------------------------------//
MOAIImGuiRenderable::MOAIImGuiRenderable () {
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIRenderable )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIImGuiRenderable::~MOAIImGuiRenderable () {
	
}

//----------------------------------------------------------------//
void MOAIImGuiRenderable::Render () {
	
	MOAIImGui& imgui = MOAIImGui::Get ();
	if ( !imgui.mVtxBuffer ) return;
	
	ImDrawData* draw = ImGui::GetDrawData ();
	if ( !draw ) return;
	
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();
	MOAIRenderMgr& renderMgr = MOAIRenderMgr::Get ();
	
	gfxDevice.ResetState ();
	renderMgr.SetViewport ( imgui.mViewport );
	
	ZLRect viewRect = *imgui.mViewport;
	gfxDevice.SetViewRect ( viewRect );
	
	ZLMatrix4x4 proj = imgui.mViewport->GetProjMtx ();
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_VIEW_TRANSFORM );
	gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_PROJ_TRANSFORM, proj );
	
	gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_MODEL );
	gfxDevice.SetUVMtxMode ( MOAIGfxDevice::UV_STAGE_MODEL, MOAIGfxDevice::UV_STAGE_TEXTURE );
	gfxDevice.UpdateViewVolume ();
	
	gfxDevice.SetPenColor ( 1.f, 1.f, 1.f, 1.f );
	gfxDevice.SetCullFunc ( 0 );
	gfxDevice.SetDepthFunc ( 0 );
	
	gfxDevice.SetShader ( MOAIShaderMgr::MESH_SHADER );
	gfxDevice.UpdateShaderGlobals ();
	
	ZLRect scissorRect;
	MOAIBlendMode blendNormal;
	blendNormal.SetBlend ( ZGL_BLEND_FACTOR_SRC_ALPHA, ZGL_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA );

	MOAIBlendMode blendPremultiply;
	blendPremultiply.SetBlend ( MOAIBlendMode::BLEND_NORMAL );
	
	u32 indexSizeInBytes = sizeof ( ImDrawIdx );
	
	for ( u32 n = 0; n < draw->CmdListsCount; ++n ) {
		
		const ImDrawList* cmdList = draw->CmdLists [ n ];
		imgui.mVtxBuffer->SetData (( void* )cmdList->VtxBuffer.begin (), cmdList->VtxBuffer.size () * sizeof ( ImDrawVert ));
		
		gfxDevice.BindVertexBuffer ( imgui.mVtxBuffer );
		gfxDevice.BindVertexFormat ( imgui.mVtxFormat );
		
		gfxDevice.SetBlendMode ( blendNormal );
		
		int idxHead = 0;
		for ( u32 i = 0; i < cmdList->CmdBuffer.size (); ++i ) {
			
			const ImDrawCmd& cmd = cmdList->CmdBuffer [ i ];
			
			scissorRect.Init ( cmd.ClipRect.x, cmd.ClipRect.y, cmd.ClipRect.z, cmd.ClipRect.w );
			
			// TODO: custom textures may need premultiplied alpha blending
			gfxDevice.SetTexture (( MOAITexture* )cmd.TextureId );
			gfxDevice.SetScissorRect ( scissorRect );
			
			zglDrawElements (
				ZGL_PRIM_TRIANGLES,
				cmd.ElemCount,
				indexSizeInBytes == 2 ? ZGL_TYPE_UNSIGNED_SHORT : ZGL_TYPE_UNSIGNED_INT,
				( const void* )(( size_t )cmdList->IdxBuffer.begin () + ( idxHead * indexSizeInBytes ))
			);
			gfxDevice.IncrementDrawCount ();
			idxHead += cmd.ElemCount;
		}
		
		gfxDevice.BindVertexBuffer ();
		gfxDevice.BindVertexFormat ();
	}
}
