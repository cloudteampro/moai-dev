// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <moai-core/host.h>
#include <host-modules/aku_modules.h>

#include <zl-common/zl_types.h>
#include <zl-util/ZLLeanArray.h>

#ifdef MOAI_OS_WINDOWS
    #include <windows.h>
#elif defined(MOAI_OS_LINUX)
    #include <X11/Xlib.h>      //XOpenDisplay,etc
    #include <xcb/xcb.h>
    #include <xcb/xcb_aux.h> 
    #include <xcb/randr.h>
#endif

#include <SDL.h>

#include "SDLHost.h"
#include "SDLGameController.h"
#include "SDLKeyCodeMapping.h"

#define MAX_GAME_CONTROLLERS 4

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <limits.h>
#endif

#include "SDLImGuiHelper.h"

#define UNUSED(p) (( void )p)

namespace InputDeviceID {
	enum {
		DEVICE,
		GAMEPAD1,
		GAMEPAD2,
		GAMEPAD3,
		GAMEPAD4,
		TOTAL,
	};
}

namespace InputSensorID {
	enum {
		KEYBOARD,
		POINTER,
		MOUSE_LEFT,
		MOUSE_MIDDLE,
		MOUSE_RIGHT,
		MOUSE_WHEEL,
//		JOYSTICK,
//		TOUCH,
		TOTAL,
	};
}

namespace InputControllerSensorID {
	enum {
		BUTTON_A = 0,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_BACK,
		BUTTON_GUIDE,
		BUTTON_START,
		BUTTON_LEFTSTICK,
		BUTTON_RIGHTSTICK,
		BUTTON_LEFTSHOULDER,
		BUTTON_RIGHTSHOULDER,
		BUTTON_UP,
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		AXIS_LEFT,
		AXIS_RIGHT,
		AXIS_TRIGGER,
		TOTAL,
	};
}

const char* CONTROLLER_EVENT_NAMES[] = {
		"a",
		"b",
		"x",
		"y",
		"back",
		"guide",
		"start",
		"leftStick",
		"rightStick",
		"leftShoulder",
		"rightShoulder",
		"up",
		"down",
		"left",
		"right",
		"axisLeft",
		"axisRight",
		"axisTrigger", // left - x, right - y
};

static SDL_Window* sWindow = 0;

typedef int ( *DisplayModeFunc ) (int, SDL_DisplayMode *);

static void SetScreenSize ( DisplayModeFunc func);

//================================================================//
// aku callbacks
//================================================================//

void	_AKUEnterFullscreenModeFunc		();
void	_AKUExitFullscreenModeFunc		();
void	_AKUOpenWindowFunc				( const char* title, int width, int height );
void    _AKUShowCursor					();
void    _AKUHideCursor					();
void	_AKUSetTextInputRectFunc		( int xMin, int yMin, int xMax, int yMax );

//----------------------------------------------------------------//
void _AKUShowCursor () {
	SDL_ShowCursor(1);
}

//----------------------------------------------------------------//
void _AKUHideCursor () {
	SDL_ShowCursor(0);
}

//----------------------------------------------------------------//
void _AKUEnterFullscreenModeFunc () {

    //videomode change
    SDL_SetWindowFullscreen(sWindow, SDL_WINDOW_FULLSCREEN);
	SetScreenSize( SDL_GetCurrentDisplayMode );
}

//----------------------------------------------------------------//
void _AKUExitFullscreenModeFunc () {

    //videomode change
    SDL_SetWindowFullscreen(sWindow, 0);
	SetScreenSize( SDL_GetDesktopDisplayMode );
}

//----------------------------------------------------------------//
void _AKUOpenWindowFunc ( const char* title, int width, int height ) {
	
	if ( !sWindow ) {
		sWindow = SDL_CreateWindow ( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
		SDL_GL_CreateContext ( sWindow );
		SDL_GL_SetSwapInterval ( 1 );
		AKUDetectGfxContext ();
		AKUSetViewSize ( width, height );
		AKUSdlSetWindow ( sWindow );

		// Enable keyboard text input.
		// According to the SDL documentation, this will open an on-screen keyboard on some platforms.
		// Currently we're using the SDL host for desktop platforms only, so this should not be a problem.
		SDL_StartTextInput ();
	}
	else {
		SDL_SetWindowSize ( sWindow, width, height );
	}
}

//----------------------------------------------------------------//
void _AKUSetTextInputRectFunc ( int xMin, int yMin, int xMax, int yMax ) {
	SDL_Rect sdlRect;
	sdlRect.x = xMin;
	sdlRect.y = yMin;
	sdlRect.w = xMax - xMin;
	sdlRect.h = yMax - yMin;
	
	SDL_SetTextInputRect ( &sdlRect );
}


//================================================================//
// helpers
//================================================================//

static void	Finalize			();
static void	Init				( int argc, char** argv );
static void	MainLoop			();
static void	PrintMoaiVersion	();
static void SetScreenDpi        ();

//----------------------------------------------------------------//
void Finalize () {

	AKUModulesAppFinalize ();
	AKUAppFinalize ();
	
	SDL_Quit ();
}

//----------------------------------------------------------------//
void Init ( int argc, char** argv ) {

	SDL_Init ( SDL_INIT_EVERYTHING );
	PrintMoaiVersion ();

	AKUAppInitialize ();
	AKUModulesAppInitialize ();

	AKUCreateContext ();
	AKUModulesContextInitialize ();
	AKUModulesRunLuaAPIWrapper ();
	
	// for now this one is here
	SDLImGuiContextInitialize ();
	
	AKUSetInputConfigurationName ( "SDL" );

	SetScreenSize( SDL_GetDesktopDisplayMode );

    SetScreenDpi();

	AKUReserveInputDevices			( InputDeviceID::TOTAL );
	AKUSetInputDevice				( InputDeviceID::DEVICE, 	"device" );
	AKUSetInputDevice				( InputDeviceID::GAMEPAD1, 	"gamepad1" );
	AKUSetInputDevice				( InputDeviceID::GAMEPAD2, 	"gamepad2" );
	AKUSetInputDevice				( InputDeviceID::GAMEPAD3, 	"gamepad3" );
	AKUSetInputDevice				( InputDeviceID::GAMEPAD4, 	"gamepad4" );

	AKUReserveInputDeviceSensors	( InputDeviceID::DEVICE, 	InputSensorID::TOTAL );
	AKUSetInputDeviceKeyboard		( InputDeviceID::DEVICE, 	InputSensorID::KEYBOARD,	"keyboard" );
	AKUSetInputDevicePointer		( InputDeviceID::DEVICE, 	InputSensorID::POINTER,		"pointer" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, 	InputSensorID::MOUSE_LEFT,	"mouseLeft" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, 	InputSensorID::MOUSE_MIDDLE,"mouseMiddle" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, 	InputSensorID::MOUSE_RIGHT,	"mouseRight" );
	AKUSetInputDeviceWheel			( InputDeviceID::DEVICE, 	InputSensorID::MOUSE_WHEEL,	"mouseWheel" );
	// AKUSetInputDeviceJoystick       ( InputDeviceID::DEVICE, InputSensorID::JOYSTICK,	    "joystick" );

	AKUReserveInputDeviceSensors	( InputDeviceID::GAMEPAD1, 	InputControllerSensorID::TOTAL );
	for ( int i = 0; i <= InputControllerSensorID::BUTTON_RIGHT; ++i ) {
		AKUSetInputDeviceButton		( InputDeviceID::GAMEPAD1, 	i,	CONTROLLER_EVENT_NAMES [ i ] );
	}
	for ( int i = InputControllerSensorID::AXIS_LEFT; i < InputControllerSensorID::TOTAL; ++i ) {
		AKUSetInputDeviceJoystick	( InputDeviceID::GAMEPAD1, 	i,	CONTROLLER_EVENT_NAMES [ i ] );
	}
	AKUSetInputDeviceActive			( InputDeviceID::GAMEPAD1, 	false );

	AKUReserveInputDeviceSensors	( InputDeviceID::GAMEPAD2, 	InputControllerSensorID::TOTAL );
	for ( int i = 0; i <= InputControllerSensorID::BUTTON_RIGHT; ++i ) {
		AKUSetInputDeviceButton		( InputDeviceID::GAMEPAD2, 	i, 	CONTROLLER_EVENT_NAMES [ i ] );
	}
	for ( int i = InputControllerSensorID::AXIS_LEFT; i < InputControllerSensorID::TOTAL; ++i ) {
		AKUSetInputDeviceJoystick	( InputDeviceID::GAMEPAD2, 	i, 	CONTROLLER_EVENT_NAMES [ i ] );
	}
	AKUSetInputDeviceActive			( InputDeviceID::GAMEPAD2, 	false );

	AKUReserveInputDeviceSensors	( InputDeviceID::GAMEPAD3, InputControllerSensorID::TOTAL );
	for ( int i = 0; i <= InputControllerSensorID::BUTTON_RIGHT; ++i ) {
		AKUSetInputDeviceButton		( InputDeviceID::GAMEPAD3, 	i, 	CONTROLLER_EVENT_NAMES [ i ] );
	}
	for ( int i = InputControllerSensorID::AXIS_LEFT; i < InputControllerSensorID::TOTAL; ++i ) {
		AKUSetInputDeviceJoystick	( InputDeviceID::GAMEPAD3, 	i, 	CONTROLLER_EVENT_NAMES [ i ] );
	}
	AKUSetInputDeviceActive			( InputDeviceID::GAMEPAD3, 	false );

	AKUReserveInputDeviceSensors	( InputDeviceID::GAMEPAD4, InputControllerSensorID::TOTAL );
	for ( int i = 0; i <= InputControllerSensorID::BUTTON_RIGHT; ++i ) {
		AKUSetInputDeviceButton		( InputDeviceID::GAMEPAD4, i, 	CONTROLLER_EVENT_NAMES [ i ] );
	}
	for ( int i = InputControllerSensorID::AXIS_LEFT; i < InputControllerSensorID::TOTAL; ++i ) {
		AKUSetInputDeviceJoystick	( InputDeviceID::GAMEPAD4, 	i, 	CONTROLLER_EVENT_NAMES [ i ] );
	}
	AKUSetInputDeviceActive			( InputDeviceID::GAMEPAD4, 	false );

	AKUSetFunc_EnterFullscreenMode 	( _AKUEnterFullscreenModeFunc );
	AKUSetFunc_ExitFullscreenMode 	( _AKUExitFullscreenModeFunc );

	AKUSetFunc_ShowCursor ( _AKUShowCursor );
	AKUSetFunc_HideCursor ( _AKUHideCursor );

	AKUSetFunc_OpenWindow ( _AKUOpenWindowFunc );
	
	AKUSetFunc_SetTextInputRect( _AKUSetTextInputRectFunc );
	
	#ifdef __APPLE__
			//are we a bundle?
			CFBundleRef bref = CFBundleGetMainBundle();
			if (bref == NULL || CFBundleGetIdentifier(bref) == NULL) {
	AKUModulesParseArgs ( argc, argv );
	
			} 
			else {
			
					CFURLRef bundleurl = CFBundleCopyResourcesDirectoryURL(bref);
					assert(bundleurl != NULL);
					
					UInt8 buf[PATH_MAX];
					CFURLGetFileSystemRepresentation(bundleurl, true, buf, PATH_MAX);

					AKUSetWorkingDirectory((const char *)buf);
					AKULoadFuncFromFile("bootstrap.lua");
					AKUCallFunc();
			}
	#else
			
			
		AKUModulesParseArgs ( argc, argv );
	#endif

	
	atexit ( Finalize ); // do this *after* SDL_Init
}

// based on host-glut 
//void _onMultiButton( int touch_id, float x, float y, int state );
//void _onMultiButton( int touch_id, float x, float y, int state ) {
//
//	AKUEnqueueTouchEvent (
//		InputDeviceID::DEVICE,
//		InputSensorID::TOUCH,
//		touch_id,
//		state == SDL_FINGERDOWN,
//		( float )x,
//		( float )y
//	);
//}



//----------------------------------------------------------------//
void SetScreenSize(DisplayModeFunc func ) {

    SDL_DisplayMode dm;

    if ( func != NULL && func( 0, &dm ) == 0 ) {
    	AKUSetScreenSize(dm.w, dm.h);
    }
}


//----------------------------------------------------------------//
void SetScreenDpi() {

#ifdef MOAI_OS_WINDOWS

    HDC hDC = GetWindowDC(NULL);
    int widthInMm = GetDeviceCaps(hDC, HORZSIZE);
    double widthInInches = widthInMm / 25.4;
    int widthInPixels = GetDeviceCaps(hDC, HORZRES);
    AKUSetScreenDpi(( int )( widthInPixels / widthInInches ));

#elif defined(MOAI_OS_LINUX)

	char* display_name = getenv( "DISPLAY" );
	if ( !display_name ) return;

	int nscreen = 0;
	xcb_connection_t* conn = xcb_connect( display_name, &nscreen );
	if ( !conn ) return;

	xcb_screen_t* screen = xcb_aux_get_screen( conn, nscreen );

	double widthInInches = screen->width_in_millimeters / 25.4;
	int widthInPixels = screen->width_in_pixels;

	AKUSetScreenDpi(( int )widthInPixels / widthInInches );

	xcb_disconnect( conn );
  
#endif

}

//----------------------------------------------------------------//
void MainLoop () {

	SDL_InitSubSystem ( SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER ); // for win32 correct joystick work

	SDL_GameControllerAddMappingsFromFile ( "gamecontrollerdb.txt" );

	ZLLeanArray < GameController > gameControllers;
	gameControllers.Init ( MAX_GAME_CONTROLLERS );

	int gcIndex = 0;
	for ( int i = 0; i < SDL_NumJoysticks (); ++i ) {

	    if ( !SDL_IsGameController ( i )) continue;

	    if ( gcIndex >= MAX_GAME_CONTROLLERS ) break;

	    gameControllers [ i ].Open ( i );
	    AKUSetInputDeviceActive ( InputDeviceID::GAMEPAD1 + i, true );
	    gcIndex++;
	}

	Uint32 lastFrame = SDL_GetTicks ();
	
	bool running = true;
	while ( running ) {
		
		SDL_Event sdlEvent;
		
		while ( SDL_PollEvent ( &sdlEvent )) {  
			   
			switch ( sdlEvent.type )  {
			
				case SDL_QUIT:
				
					running = false;
					break;
				
				case SDL_KEYDOWN:
				case SDL_KEYUP:	{
					if ( sdlEvent.key.repeat ) break;
					int moaiKeyCode = GetMoaiKeyCode ( sdlEvent );
					AKUEnqueueKeyboardKeyEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, moaiKeyCode, sdlEvent.key.type == SDL_KEYDOWN );
					break;
				}
				
				case SDL_TEXTINPUT: {
					AKUEnqueueKeyboardTextEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, sdlEvent.text.text );
					break;
				}
				case SDL_TEXTEDITING: {
					char *text = sdlEvent.edit.text;
					int start = sdlEvent.edit.start;
					int length = sdlEvent.edit.length;
					
					AKUEnqueueKeyboardEditEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, text, start, length, SDL_TEXTEDITINGEVENT_TEXT_SIZE );
					break;
				}
				
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
	
					switch ( sdlEvent.button.button ) {
					
						case SDL_BUTTON_LEFT:
							AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_LEFT, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
							break;
						
						case SDL_BUTTON_MIDDLE:
							AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_MIDDLE, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
							break;
						
						case SDL_BUTTON_RIGHT:
							AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_RIGHT, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
							break;
					}

					break;

				case SDL_MOUSEWHEEL: 

						if ( sdlEvent.wheel.which != SDL_TOUCH_MOUSEID ) {
                            //const int32_t x = sdlEvent.wheel.x;
							const int32_t y = sdlEvent.wheel.y; 

							//XXX: x or y ?
							AKUEnqueueWheelEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_WHEEL, ( float )y );
						}
					break;

					/*
					 * TODO:
					 * SDL_JOYBALLMOTION joystick trackball motion
					 * SDL_JOYHATMOTION	 joystick hat position change
					 * SDL_JOYBUTTONDOWN joystick button pressed
					 * SDL_JOYBUTTONUP	 joystick button released
					 * SDL_JOYDEVICEADDED	joystick connected
					 * SDL_JOYDEVICEREMOVED	joystick disconnected
					 * */

				case SDL_CONTROLLERDEVICEADDED: {

					int id = sdlEvent.cdevice.which;

					if( SDL_IsGameController ( id ) ) {

						for ( int i = 0; i < MAX_GAME_CONTROLLERS; ++i ) {

							if ( !gameControllers [ i ].isOpen ()) {

								gameControllers [ i ].Open ( id );
								AKUSetInputDeviceActive ( InputDeviceID::GAMEPAD1 + i, true );
								printf ( "MOAI: Controller added %d (%d)\n", i, id );
								break;
							}
						}
				    }
				    break;
				}
					
				case SDL_CONTROLLERDEVICEREMOVED: {

					int id = sdlEvent.cdevice.which;

					for ( int i = 0; i < MAX_GAME_CONTROLLERS; ++i ) {

						if (gameControllers [ i ].isMe ( id )) {

							AKUSetInputDeviceActive ( InputDeviceID::GAMEPAD1 + i, false );
							gameControllers [ i ].Close ();
							printf ( "MOAI: Controller removed %d (%d)\n", i, id );
							break;
						}
					}
					break;
				}
					
				case SDL_CONTROLLERBUTTONDOWN:
				case SDL_CONTROLLERBUTTONUP: {

					int id = sdlEvent.cbutton.which;

					for ( int i = 0; i < MAX_GAME_CONTROLLERS; ++i ) {

						if ( gameControllers [ i ].isMe ( id )) {

							AKUEnqueueButtonEvent ( InputDeviceID::GAMEPAD1 + i, sdlEvent.cbutton.button, ( sdlEvent.cbutton.state == 1 ));
							break;
						}
					}
					break;
				}
					
				case SDL_CONTROLLERAXISMOTION: {
					int id = sdlEvent.caxis.which;

					for ( int i = 0; i < MAX_GAME_CONTROLLERS; ++i ) {

						if ( gameControllers [ i ].isMe ( id )) {

							const GameController::AXIS axis = gameControllers [ i ].getAxis ( sdlEvent );
							int sensorID = InputControllerSensorID::AXIS_LEFT + axis.id;
							AKUEnqueueJoystickEvent ( InputDeviceID::GAMEPAD1 + i, sensorID, axis.x, axis.y );
							break;
						}
					}
					break;
				}

				case SDL_MOUSEMOTION:
				
					AKUEnqueuePointerEvent ( InputDeviceID::DEVICE, InputSensorID::POINTER, sdlEvent.motion.x, sdlEvent.motion.y );
					break;

				case SDL_WINDOWEVENT:
					// Note: this only support fullscreen videomode change.
					// Not for the event "resize", by default SDL main window is not resizable(at least Linux)
					if ( sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
							sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED ) {
						
						AKUSetViewSize(sdlEvent.window.data1, sdlEvent.window.data2);
					} else if ( sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST ) {
						// If the focus is lost, it must be stopped.
						SDL_StopTextInput();
						
						// Clear Editing text.
						AKUEnqueueKeyboardEditEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, "", 0, 0, SDL_TEXTEDITINGEVENT_TEXT_SIZE );
					} else if ( sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED ) {
						// Start when the focus is given.
						// TODO:Restored the edit text.
						SDL_StartTextInput();
					}
					break;

//                case SDL_FINGERDOWN:
//                case SDL_FINGERUP:
//                case SDL_FINGERMOTION:
//                    const int id    = ( int )sdlEvent.tfinger.fingerId;
//					const float x   = sdlEvent.tfinger.x;
//					const float y   = sdlEvent.tfinger.y;
//					const int state = ( sdlEvent.type == SDL_FINGERDOWN || sdlEvent.type == SDL_FINGERMOTION ) ? SDL_FINGERDOWN : SDL_FINGERUP;
//
//					_onMultiButton(id, x, y, state);
//
//					break;
			} //end_switch
		}//end_while
		
		AKUModulesUpdate ();
		SDLImGuiUpdate ();
		
		AKURender ();
		SDL_GL_SwapWindow ( sWindow );
		
		Uint32 frameDelta = ( Uint32 )( AKUGetSimStep () * 1000.0 );
		Uint32 currentFrame = SDL_GetTicks ();
		Uint32 delta = currentFrame - lastFrame;
		
		if ( delta < frameDelta ) {
			SDL_Delay ( frameDelta - delta );
		}
		lastFrame = SDL_GetTicks();
	}
}

//----------------------------------------------------------------//
void PrintMoaiVersion () {

	static const int length = 255;
	char version [ length ];
	AKUGetMoaiVersion ( version, length );
	printf ( "%s\n", version );
}

//================================================================//
// SDLHost
//================================================================//

//----------------------------------------------------------------//
int SDLHost ( int argc, char** argv ) {

	Init ( argc, argv );

	if ( sWindow ) {
		MainLoop ();
	}

	return 0;
}
