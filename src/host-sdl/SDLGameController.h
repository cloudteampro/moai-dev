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

    public:

        bool Open(const int idx);
        void Close();

        bool isOpen() const;
        bool isMe(const int id);

    private:

        int index;
        SDL_JoystickID jID;
        SDL_GameController* sdl_gamecontroller;
        SDL_Joystick* sdl_joystick;

        static const int JOYSTICK_DEAD_ZONE = 8000;
};

#endif
