#include "common.hpp"
#include "common_sdl.hpp"
#include "gfx.hpp"
#include "input.hpp"

static Vector2Int scene_size = { 8, 8 };
static Vector2Int scene_entrance = { 4, 3 };
static TextureId scene_tiles[8*8] =
{
    TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, 
    TEXTURE_BG, TEXTURE_BG, TEXTURE_NONE, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, 
    TEXTURE_BG, TEXTURE_BG, TEXTURE_NONE, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, 
    TEXTURE_BG, TEXTURE_BG, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, 
    TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_NONE, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, 
    TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_NONE, TEXTURE_BG, TEXTURE_BG, 
    TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, 
    TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, TEXTURE_BG, 
};

int main(void)
{
    std::cout << "Hello World!" << std::endl;

    SDL_Thread *gfx_thread = SDL_CreateThread(gfx_task, "gfx_thread", nullptr);

    while(!gfx_is_initialized()) SDL_Delay(10);

    GfxElement *test_element = gfx_create_element(TEXTURE_HEAD);

    Scene *test_scene = new Scene(scene_size, scene_tiles);
    test_scene->SetEntrance(scene_entrance.x, scene_entrance.y);

    gfx_set_focal_element(test_element);
    gfx_set_scene(test_scene);

    SDL_Thread *input_thread = SDL_CreateThread(input_task, "input_thred", &test_element->GetTransform());

    SDL_WaitThread(input_thread, nullptr);
    SDL_WaitThread(gfx_thread, nullptr);

    gfx_destroy_element(test_element);
    delete(test_scene);

    return 0;
}
