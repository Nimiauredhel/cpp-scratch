#include "common.hpp"
#include "common_sdl.hpp"
#include "gfx.hpp"
#include "scene.hpp"
#include "player.hpp"

static Vector2Int scene_size = { 16, 16 };

int main(void)
{
    SDL_Thread *gfx_thread = SDL_CreateThread(gfx_task, "gfx_thread", nullptr);

    while(!gfx_is_initialized()) SDL_Delay(10);

    for (int i = 0; i < 4; i++)
    {
        scene_add_new(scene_size);
    }

    scene_get_by_idx(0)->CreateDoor(8, 0, 1, 3);
    scene_get_by_idx(0)->CreateDoor(8, 8, 0, 1);

    scene_get_by_idx(1)->CreateDoor(0, 8, 1, 0);
    scene_get_by_idx(1)->CreateDoor(0, 12, 0, 2);

    scene_get_by_idx(2)->CreateDoor(5, 4, 1, 1);
    scene_get_by_idx(2)->CreateDoor(8, 4, 0, 3);

    scene_get_by_idx(3)->CreateDoor(3, 2, 1, 2);
    scene_get_by_idx(3)->CreateDoor(7, 4, 0, 0);

    scene_set_current(0);

    SDL_Thread *player_thread = SDL_CreateThread(player_task, "input_thred", nullptr);

    SDL_WaitThread(player_thread, nullptr);
    SDL_WaitThread(gfx_thread, nullptr);

    //scene_dispose_all();

    return 0;
}
