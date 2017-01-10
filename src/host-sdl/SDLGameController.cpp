
#include "SDLGameController.h"


GameController::GameController() :
    index(0),
    jID(0),
    sdl_gamecontroller(NULL),
    sdl_joystick(NULL)
{ }


GameController::~GameController()
{ }

bool GameController::Open(const int idx)
{
    index = idx;

    sdl_gamecontroller = SDL_GameControllerOpen( index );

    if ( sdl_gamecontroller ) {

        sdl_joystick = SDL_GameControllerGetJoystick( sdl_gamecontroller );

        if ( sdl_joystick == NULL ) {
            std::cerr << "Unable to open joystick" << std::endl;
            return false;
        }

        jID = SDL_JoystickInstanceID( sdl_joystick );

        // std::cerr << "Open game controller " << index << " for joystick " << jID << std::endl;

        return true;
    }
    else
    {
        std::cerr << "Unable to open game controller" << std::endl;
    }

    return false;
}

void GameController::Close() {

    if ( sdl_gamecontroller ) {

        // std::cerr << "Close game controller " << index << " for joystick " << jID << std::endl;

        SDL_GameControllerClose(sdl_gamecontroller);

        sdl_gamecontroller = NULL;
        sdl_joystick = NULL;

        index = -1;
        jID = -1;
    }
}

bool GameController::isOpen() const {

    if ( NULL != sdl_gamecontroller && NULL != sdl_joystick ) {
        return true;
    }

    return false;
}

bool GameController::isMe(const int id)
{
    return isOpen() && id == (int)jID;
}
