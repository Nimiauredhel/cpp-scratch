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

    Scene *test_scene = new Scene(scene_size);
    test_scene->CreateDoor(4, 0, 1);
    test_scene->CreateDoor(0, 5, 1);
    Entity *test_entity = test_scene->CreateEntity(TEXTURE_HEAD);
    scene_set_current(test_scene);
    gfx_set_focal_entity(test_entity);

    SDL_Thread *input_thread = SDL_CreateThread(player_task, "input_thred", &test_entity->GetTransform());

    SDL_WaitThread(input_thread, nullptr);
    SDL_WaitThread(gfx_thread, nullptr);

    test_scene->DestroyEntity(test_entity);
    delete(test_scene);

    return 0;
}
