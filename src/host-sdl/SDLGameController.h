#ifndef	SDLGAMECONTROLLER_H
#define	SDLGAMECONTROLLER_H

#include <SDL.h>

#include <iostream>
#include <utility>

//================================================================//
// GameController
//================================================================//
class GameController {
    public:
        
        struct AXIS {
            int id;
            float x;
            float y;
            AXIS() :
                id ( 0 ),
                x ( 0.0f ),
                y ( 0.0f ) {
            }
        };

    private:

        AXIS mLeftAxis;
        AXIS mRightAxis;
        AXIS mTriggerAxis;

        int mIndex;
        SDL_JoystickID mJoyId;
        SDL_GameController* mGameController;
        SDL_Joystick* mJoystick;

        static const int JOYSTICK_DEAD_ZONE = 8000;
        static const int JOYSTICK_AXIS_MAX = 32767;

    public:

        //----------------------------------------------------------------//
        explicit        GameController      ();
                        ~GameController     ();
                        GameController      ( const GameController& ) = delete;
        void            operator=           ( const GameController& ) = delete;
        bool            Open                ( const int idx );
        void            Close               ();
        bool            isOpen              () const;
        bool            isMe                ( const int id );
        const AXIS      getAxis             ( const SDL_Event & event );

};

#endif
