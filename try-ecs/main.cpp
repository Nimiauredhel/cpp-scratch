#include "common.hpp"
#include "common_sdl.hpp"
#include "gfx.hpp"
#include "scene.hpp"
#include "player.hpp"

int main(void)
{
    SDL_Thread *gfx_thread = SDL_CreateThread(gfx_task, "gfx_thread", nullptr);

    while(!gfx_is_initialized()) SDL_Delay(10);

    scene_add_new({10, 2}, std::vector<TileSequence>{
            {4, TILE_FLOOR}, {2, TILE_WALL},});
    scene_add_new({2, 20}, std::vector<TileSequence>{
            {9, TILE_FLOOR}, {1, TILE_WALL}, {1, TILE_FLOOR}, {1, TILE_WALL},});
    scene_add_new({20, 4}, std::vector<TileSequence>{
            {7, TILE_FLOOR}, {3, TILE_WALL}, {10, TILE_FLOOR}, {7, TILE_FLOOR}, {3, TILE_WALL}});
    scene_add_new({8, 8}, std::vector<TileSequence>{
            {4, TILE_FLOOR}, {2, TILE_WALL},});

    uint16_t last_created_entity_idx;

    scene_get_by_idx(0)->CreateDoor(0, 1, 1, 3);
    scene_get_by_idx(0)->CreateDoor(9, 0, 0, 1);
    last_created_entity_idx = scene_get_by_idx(0)->CreateEntity(COM_FLAG_TRANSFORM | COM_FLAG_SPRITE);
    scene_get_by_idx(0)->GetTransforms()[last_created_entity_idx] = { { 5, 1 }, { 1, 1 } };
    scene_get_by_idx(0)->GetSprites()[last_created_entity_idx].texture_id = TEXTURE_HUMANOID1;

    scene_get_by_idx(1)->CreateDoor(1, 0, 1, 0);
    scene_get_by_idx(1)->CreateDoor(1, 19, 0, 2);
    last_created_entity_idx = scene_get_by_idx(1)->CreateEntity(COM_FLAG_TRANSFORM | COM_FLAG_SPRITE);
    scene_get_by_idx(1)->GetTransforms()[last_created_entity_idx] = { { 0, 10 }, { 1, 1 } };
    scene_get_by_idx(1)->GetSprites()[last_created_entity_idx].texture_id = TEXTURE_HUMANOID1;

    scene_get_by_idx(2)->CreateDoor(0, 1, 1, 1);
    scene_get_by_idx(2)->CreateDoor(19, 0, 0, 3);
    last_created_entity_idx = scene_get_by_idx(2)->CreateEntity(COM_FLAG_TRANSFORM | COM_FLAG_SPRITE);
    scene_get_by_idx(2)->GetTransforms()[last_created_entity_idx] = { { 10, 0 }, { 1, 1 } };
    scene_get_by_idx(2)->GetSprites()[last_created_entity_idx].texture_id = TEXTURE_HUMANOID1;

    scene_get_by_idx(3)->CreateDoor(0, 1, 1, 2);
    scene_get_by_idx(3)->CreateDoor(6, 6, 0, 0);
    last_created_entity_idx = scene_get_by_idx(3)->CreateEntity(COM_FLAG_TRANSFORM | COM_FLAG_SPRITE);
    scene_get_by_idx(3)->GetTransforms()[last_created_entity_idx] = { { 3, 4 }, { 1, 1 } };
    scene_get_by_idx(3)->GetSprites()[last_created_entity_idx].texture_id = TEXTURE_HUMANOID1;

    scene_set_current(0);

    SDL_Thread *player_thread = SDL_CreateThread(player_task, "player_thread", nullptr);

    SDL_WaitThread(player_thread, nullptr);
    SDL_WaitThread(gfx_thread, nullptr);

    scene_dispose_all();

    return 0;
}
