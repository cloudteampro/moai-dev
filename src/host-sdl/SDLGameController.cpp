
#include "SDLGameController.h"


GameController::GameController() :
    index(0),
    jID(0),
    sdl_gamecontroller(NULL),
    sdl_joystick(NULL)
{
    left_axis_motion.id = 0;
    right_axis_motion.id = 1;
    trigger_axis_motion.id = 2;
}


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

        left_axis_motion.x = 0.0f;
        left_axis_motion.y = 0.0f;
        right_axis_motion.x = 0.0f;
        right_axis_motion.y = 0.0f;
        trigger_axis_motion.x = 0.0f;
        trigger_axis_motion.y = 0.0f;
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

const GameController::AXIS_MOTION & GameController::getAxis( const SDL_Event & event )
{
    float value = 0.0f;

    if( event.caxis.value > JOYSTICK_DEAD_ZONE or event.caxis.value < -JOYSTICK_DEAD_ZONE )
    {
        value = (float) event.caxis.value / (float) JOYSTICK_AXIS_MAX;    
    }

    if (event.caxis.axis == 0)
    {
        left_axis_motion.x = value;
        return left_axis_motion;
    }
    else if (event.caxis.axis == 1)
    {
        left_axis_motion.y = value;
        return left_axis_motion;
    }
    else if (event.caxis.axis == 2)
    {
        right_axis_motion.x = value;
        return right_axis_motion;
    }
    else if (event.caxis.axis == 3)
    {
        right_axis_motion.y = value;
        return right_axis_motion;
    }
    else if (event.caxis.axis == 4)
    {
        trigger_axis_motion.x = value;
        return trigger_axis_motion;
    }
    else if (event.caxis.axis == 5)
    {
        trigger_axis_motion.y = value;
        return trigger_axis_motion;
    }

    return left_axis_motion;
}
