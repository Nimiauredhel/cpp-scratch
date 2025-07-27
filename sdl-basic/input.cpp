#include "input.hpp"

void input_init(void)
{
    SDL_Init(SDL_INIT_EVENTS);
}

InputId input_poll(void)
{
    static SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            case SDL_APP_TERMINATING:
                return INPUT_QUIT;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                        return INPUT_LEFT;
                    case SDLK_w:
                        return INPUT_UP;
                    case SDLK_d:
                        return INPUT_RIGHT;
                    case SDLK_s:
                        return INPUT_DOWN;
                }
                break;
            case SDL_KEYUP:
            default:
                break;
        }
    }

    return INPUT_NONE;
}
