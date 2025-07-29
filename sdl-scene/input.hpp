#ifndef INPUT_HPP
#define INPUT_HPP

#include "common.hpp"
#include "common_sdl.hpp"

enum InputId
{
    INPUT_NONE = 0,
    INPUT_LEFT = 1,
    INPUT_UP = 2,
    INPUT_RIGHT = 3,
    INPUT_DOWN = 4,
    INPUT_QUIT = 5,
};

bool player_is_initialized(void);
int player_task(void *arg);

#endif
