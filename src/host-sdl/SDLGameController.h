#ifndef	SDLGAMECONTROLLER_H
#define	SDLGAMECONTROLLER_H

#include <SDL.h>

#include <iostream>
#include <utility>

class GameController
{
    public:
        
        explicit GameController();
        ~GameController();
        
        GameController(const GameController&) = delete;
        void operator= (const GameController&) = delete;

        struct AXIS_MOTION {
            int id;
            float x;
            float y;
            AXIS_MOTION() : id(0), x(0.0f), y(0.0f) { }
        };

    public:

        bool Open(const int idx);
        void Close();

        bool isOpen() const;
        bool isMe(const int id);

        const AXIS_MOTION getAxis( const SDL_Event & event );

    private:

        AXIS_MOTION left_axis_motion;
        AXIS_MOTION right_axis_motion;
        AXIS_MOTION trigger_axis_motion;

        int index;
        SDL_JoystickID jID;
        SDL_GameController* sdl_gamecontroller;
        SDL_Joystick* sdl_joystick;

        static const int JOYSTICK_DEAD_ZONE = 8000;
        static const int JOYSTICK_AXIS_MAX = 32767;
};

#endif
