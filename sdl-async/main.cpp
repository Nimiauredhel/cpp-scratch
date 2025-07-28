#include <iostream>
#include <chrono>
#include <thread>

#include "common.hpp"
#include "common_sdl.hpp"
#include "gfx.hpp"
#include "input.hpp"

int main(void)
{
    std::cout << "Hello World!" << std::endl;

    SDL_Thread *gfx_thread = SDL_CreateThread(gfx_task, "gfx_thread", nullptr);

    while(!gfx_is_initialized()) SDL_Delay(10);

    GfxElement *test_element = gfx_create_element(TEXTURE_HEAD);

    SDL_Thread *input_thread = SDL_CreateThread(input_task, "input_thred", test_element);

    SDL_WaitThread(input_thread, nullptr);
    SDL_WaitThread(gfx_thread, nullptr);

    gfx_destroy_element(test_element);

    return 0;
}
