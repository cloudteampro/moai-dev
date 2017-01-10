
#include "SDLGameController.h"

//----------------------------------------------------------------//
GameController::GameController () :
    mIndex ( 0 ),
    mJoyId ( 0 ),
    mGameController ( NULL ),
    mJoystick ( NULL ) {

    mLeftAxis.id = 0;
    mRightAxis.id = 1;
    mTriggerAxis.id = 2;
}

//----------------------------------------------------------------//
GameController::~GameController () {
}

//----------------------------------------------------------------//
bool GameController::Open ( const int idx ) {

    mIndex = idx;

    mGameController = SDL_GameControllerOpen ( mIndex );

    if ( mGameController ) {

        mJoystick = SDL_GameControllerGetJoystick ( mGameController );

        if ( mJoystick == NULL ) {
            std::cerr << "Unable to open joystick" << std::endl;
            return false;
        }

        mJoyId = SDL_JoystickInstanceID ( mJoystick );

        return true;
    }
    else {
        std::cerr << "Unable to open game controller" << std::endl;
    }

    return false;
}

//----------------------------------------------------------------//
void GameController::Close () {

    if ( mGameController ) {

        SDL_GameControllerClose ( mGameController );

        mGameController = NULL;
        mJoystick = NULL;

        mIndex = -1;
        mJoyId = -1;

        mLeftAxis.x = 0.0f;
        mLeftAxis.y = 0.0f;
        mRightAxis.x = 0.0f;
        mRightAxis.y = 0.0f;
        mTriggerAxis.x = 0.0f;
        mTriggerAxis.y = 0.0f;
    }
}

//----------------------------------------------------------------//
bool GameController::isOpen () const {

    if ( NULL != mGameController && NULL != mJoystick ) {
        return true;
    }

    return false;
}

//----------------------------------------------------------------//
bool GameController::isMe ( const int id ) {
    
    return isOpen() && id == ( int ) mJoyId;
}

//----------------------------------------------------------------//
const GameController::AXIS GameController::getAxis ( const SDL_Event & event ) {

    float value = 0.0f;

    if ( event.caxis.value > JOYSTICK_DEAD_ZONE || event.caxis.value < -JOYSTICK_DEAD_ZONE ) {
        value = ( float ) event.caxis.value / ( float ) JOYSTICK_AXIS_MAX; 
    }

    if ( event.caxis.axis == 0 ) {
        mLeftAxis.x = value;
        return mLeftAxis;
    }
    else if ( event.caxis.axis == 1 ) {
        mLeftAxis.y = value;
        return mLeftAxis;
    }
    else if ( event.caxis.axis == 2 ) {
        mRightAxis.x = value;
        return mRightAxis;
    }
    else if ( event.caxis.axis == 3 ) {
        mRightAxis.y = value;
        return mRightAxis;
    }
    else if ( event.caxis.axis == 4 ) {
        mTriggerAxis.x = value;
        return mTriggerAxis;
    }
    else if ( event.caxis.axis == 5 ) {
        mTriggerAxis.y = value;
        return mTriggerAxis;
    }

    return mLeftAxis;
}
