#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

#include "gfx.hpp"

static constexpr int DELAY_MS = (32);

static bool is_initialized = false;

static Window main_window_data = {};

static SDL_Window *main_window = nullptr;
static SDL_Renderer *renderer = nullptr;

static SDL_Texture *texture_bg = nullptr;
static SDL_Texture *texture_test = nullptr;

static std::vector<GfxElement*> gfx_elements = {};

static void load_texture(std::string path, SDL_Texture **texture_ptr)
{
    SDL_Surface *bmp = SDL_LoadBMP(path.c_str());
    if (bmp == nullptr)
    {
        std::cout << "No texture found at path: " << path << std::endl;
        return;
    }
    *texture_ptr = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
}

static void gfx_draw_element(GfxElement *element)
{
    if (element == nullptr) return;
    element->Draw(main_window_data, renderer);
}

static void gfx_present(void)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_bg, NULL, NULL);

    for (std::size_t i = 0; i < gfx_elements.size(); i++)
    {
        gfx_draw_element(gfx_elements[i]);
    }

    SDL_RenderPresent(renderer);
}

static void gfx_window_init(int width, int height, int tile_size)
{
    main_window_data.width = width;
    main_window_data.height = height;
    main_window_data.tile_size = tile_size;
    std::string title = "Test Window";

    SDL_VideoInit(NULL);
    main_window = SDL_CreateWindow(title.c_str(), 32, 32, main_window_data.width*main_window_data.tile_size, main_window_data.height*main_window_data.tile_size, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

    load_texture("textures/bg.bmp", &texture_bg);
    load_texture("textures/head.bmp", &texture_test);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_bg, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_RaiseWindow(main_window);
}

static void gfx_window_deinit(void)
{
    SDL_DestroyTexture(texture_bg);
    SDL_DestroyTexture(texture_test);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_VideoQuit();
}

bool gfx_is_initialized(void)
{
    return is_initialized;
}

GfxElement *gfx_create_element(TextureId initial_texture_id)
{
    GfxElement *element = new GfxElement();
    element->SetTexture(gfx_get_texture_pptr(initial_texture_id));
    gfx_elements.push_back(element);
    return element;
}

void gfx_destroy_element(GfxElement *element)
{
    auto it = std::find(gfx_elements.begin(), gfx_elements.end(), element);

    if (it != gfx_elements.end())
    {
        gfx_elements.erase(it);
    }

    delete(element);
}

SDL_Texture** gfx_get_texture_pptr(TextureId id)
{
    switch (id)
    {
    case TEXTURE_BG:
        return &texture_bg;
    case TEXTURE_HEAD:
        return &texture_test;
    case TEXTURE_NONE:
    default:
        return nullptr;
    }
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
