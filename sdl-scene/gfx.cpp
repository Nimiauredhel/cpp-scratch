#include "gfx.hpp"
#include "scene.hpp"

static constexpr int DELAY_MS = (32);

static const std::string texture_paths[TEXTURE_ID_COUNT] =
{
    "",
    "textures/bg.bmp",
    "textures/floor.png",
    "textures/wall.png",
    "textures/door.png",
    "textures/head.png",
};

static bool is_initialized = false;

static Window main_window_data = {};

static SDL_Window *main_window = nullptr;
static SDL_Renderer *renderer = nullptr;

static SDL_Texture *texture_ptrs[TEXTURE_ID_COUNT] = { nullptr };

static Entity *focal_entity = nullptr;

static void load_texture(std::string path, SDL_Texture **texture_ptr)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        std::cout << "No texture found at path: " << path << std::endl;
        return;
    }
    *texture_ptr = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

static void gfx_draw_element(Entity *element, Vector2Int offset)
{
    if (element == nullptr) return;
    element->Draw(main_window_data, renderer, offset);
}

static void gfx_draw_tile(int x, int y, TextureId texture_id)
{
    if (texture_id == TEXTURE_NONE) return;
    SDL_Rect destination = { x * main_window_data.tile_size, y * main_window_data.tile_size, 0, 0 };
    SDL_Texture *texture_ptr = gfx_get_texture_ptr(texture_id);
    SDL_QueryTexture(texture_ptr, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(renderer, texture_ptr, NULL, &destination);
}

static void gfx_present(void)
{
    Scene *current_scene = scene_get_current();

    /**
     * no scene, no refresh.
     * TODO: consider clearing the screen once.
     **/
    if (current_scene == nullptr) return;

    Vector2Int offset = { 0, 0 };
    Vector2Int mid_screen = { main_window_data.width / 2, main_window_data.height / 2 };

    if (focal_entity == nullptr)
    {
        offset = mid_screen;
    }
    else
    {
        Transform &focal_transform = focal_entity->GetTransform();
        offset = { mid_screen.x-focal_transform.GetPosX(), mid_screen.y-focal_transform.GetPosY()};
    }

    /// Renderer is cleared - no drawing before this step
    SDL_RenderClear(renderer);

    Vector2Int scene_size = current_scene->GetSize();
    Vector2Int draw_pos = { 0, 0 };
    TextureId texture_id = TEXTURE_NONE;

    /// Drawing begins here
    for (int x = -1; x < scene_size.x+1; x++)
    {
        for (int y = -1; y < scene_size.y+1; y++)
        {
            draw_pos.x = x + offset.x;
            if (draw_pos.x < 0 || draw_pos.x >= main_window_data.width) continue;
            draw_pos.y = y + offset.y;
            if (draw_pos.y < 0 || draw_pos.y >= main_window_data.height) continue;

            texture_id = (x < 0 || x >= scene_size.x
                    || y < 0 || y >= scene_size.y) ?
                    TEXTURE_WALL : TEXTURE_FLOOR;

            gfx_draw_tile(x + offset.x, y + offset.y, texture_id);
        }
    }

    std::size_t door_count = current_scene->GetDoorCount();
    Door *door = nullptr;

    for (std::size_t i = 0; i < door_count; i++)
    {
        door = current_scene->GetDoorFromIdx(i);
        gfx_draw_tile(door->position.x + offset.x, door->position.y + offset.y, TEXTURE_DOOR);
    }

    std::size_t entity_count = current_scene->GetEntityCount();
    Entity *entity = nullptr;

    for (std::size_t i = 0; i < entity_count; i++)
    {
        entity = current_scene->GetEntityFromIdx(i);

        if (entity == focal_entity)
        {
            continue;
        }
        else
        {
            gfx_draw_element(entity, offset);
        }
    }

    gfx_draw_element(focal_entity, offset);

    SDL_RenderPresent(renderer);
}

static void gfx_window_init(int width, int height, int tile_size)
{
    main_window_data.width = width;
    main_window_data.height = height;
    main_window_data.tile_size = tile_size;
    std::string title = "Test Window";

    SDL_VideoInit(NULL);
    main_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, main_window_data.width*main_window_data.tile_size, main_window_data.height*main_window_data.tile_size, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

    texture_ptrs[TEXTURE_NONE] = nullptr;

    for (int i = TEXTURE_NONE+1; i < TEXTURE_ID_COUNT; i++)
    {
        load_texture(texture_paths[i], &texture_ptrs[i]);
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_ptrs[TEXTURE_BG], NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_RaiseWindow(main_window);
}

static void gfx_window_deinit(void)
{
    for (int i = TEXTURE_NONE+1; i < TEXTURE_ID_COUNT; i++)
    {
        if (texture_ptrs[i] != nullptr)
        {
            SDL_DestroyTexture(texture_ptrs[i]);
            texture_ptrs[i] = nullptr;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_VideoQuit();
}

void gfx_set_focal_entity(Entity *entity)
{
    focal_entity = entity;
}

bool gfx_is_initialized(void)
{
    return is_initialized;
}

SDL_Texture* gfx_get_texture_ptr(TextureId id)
{
    if (id == TEXTURE_NONE || id >= TEXTURE_ID_COUNT) return nullptr;
    return texture_ptrs[id];
}

int gfx_task(void *arg)
{
    gfx_window_init(32, 16, 32);
    is_initialized = true;

    while (!should_terminate)
    {
        gfx_present();
        SDL_Delay(DELAY_MS);
    }

    gfx_window_deinit();

    return 0;
}
