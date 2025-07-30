#include "common.hpp"
#include "common_sdl.hpp"
#include "gfx.hpp"
#include "scene.hpp"
#include "player.hpp"

int main(void)
{
    SDL_Thread *gfx_thread = SDL_CreateThread(gfx_task, "gfx_thread", nullptr);

    while(!gfx_is_initialized()) SDL_Delay(10);

    scene_add_new({10, 2});
    scene_add_new({2, 20});
    scene_add_new({20, 4});
    scene_add_new({8, 8});

    scene_get_by_idx(0)->CreateDoor(0, 1, 1, 3);
    scene_get_by_idx(0)->CreateDoor(9, 0, 0, 1);

    scene_get_by_idx(1)->CreateDoor(1, 0, 1, 0);
    scene_get_by_idx(1)->CreateDoor(1, 19, 0, 2);

    scene_get_by_idx(2)->CreateDoor(0, 1, 1, 1);
    scene_get_by_idx(2)->CreateDoor(19, 0, 0, 3);

    scene_get_by_idx(3)->CreateDoor(0, 1, 1, 2);
    scene_get_by_idx(3)->CreateDoor(6, 6, 0, 0);

    scene_set_current(0);

    SDL_Thread *player_thread = SDL_CreateThread(player_task, "input_thred", nullptr);

    SDL_WaitThread(player_thread, nullptr);
    SDL_WaitThread(gfx_thread, nullptr);

    scene_dispose_all();

    return 0;
}
