#include <iostream>

#include "gfx.hpp"

static constexpr SDL_Color WHITE = { 255, 255, 255, 255 };

static Window main_window_data = {};

static SDL_Window *main_window = nullptr;
static SDL_Renderer *renderer = nullptr;

static SDL_Texture *texture_bg = nullptr;
static SDL_Texture *texture_test = nullptr;

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
void gfx_window_init(int width, int height, int tile_size)
{
    main_window_data.width = width;
    main_window_data.height = height;
    main_window_data.tile_size = tile_size;
    std::string title = "Test Window";

    SDL_VideoInit(NULL);
    main_window = SDL_CreateWindow(title.c_str(), 0, 0, main_window_data.width*main_window_data.tile_size, main_window_data.height*main_window_data.tile_size, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

    load_texture("textures/bg.bmp", &texture_bg);
    load_texture("textures/head.bmp", &texture_test);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_bg, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_RaiseWindow(main_window);
}

void gfx_window_deinit(void)
{
    SDL_DestroyTexture(texture_bg);
    SDL_DestroyTexture(texture_test);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_VideoQuit();
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

void gfx_draw_element(GfxElement *element)
{
    element->Draw(main_window_data, renderer);
}

void gfx_clear(void)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_bg, NULL, NULL);
}

void gfx_present(void)
{
    SDL_RenderPresent(renderer);
}
