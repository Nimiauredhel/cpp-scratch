#include <iostream>
#include "gfx.hpp"

static constexpr SDL_Color WHITE = { 255, 255, 255, 255 };

static uint16_t window_width;
static uint16_t window_height;
static uint16_t window_tile_size;

static SDL_Window *main_window;
static SDL_Renderer *renderer;

static SDL_Texture *texture_bg;
static SDL_Texture *texture_test;

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

GfxElement::GfxElement(void)
    : m_position{ 0 , 0 }, m_scale{ 1.0f, 1.0f }, m_texture_ptr{nullptr}
{
    this->SetTexture(&texture_test);
}

void GfxElement::SetTexture(SDL_Texture **texture_pptr)
{
    m_texture_ptr = *texture_pptr;
}

void GfxElement::SetPosition(int x, int y)
{
    m_position = { x, y };
}

void GfxElement::SetScale(float x, float y)
{
    m_scale = { x, y };
}

void GfxElement::Draw(void)
{
    if (m_texture_ptr != nullptr)
    {
        SDL_Rect destination = { m_position.x * window_tile_size, m_position.y * window_tile_size, 0, 0 };
        SDL_QueryTexture(m_texture_ptr, NULL, NULL, &destination.w, &destination.h);
        destination.w *= m_scale.x;
        destination.h *= m_scale.y;
        SDL_RenderCopy(renderer, m_texture_ptr, NULL, &destination);
    }
    else
    {
        std::cout << "Null texture pointer on gfx element" << std::endl;
    }
}

void gfx_window_init(int width, int height, int tile_size)
{
    window_width = width;
    window_height = height;
    window_tile_size = tile_size;
    std::string title = "Test Window";

    SDL_VideoInit(NULL);
    main_window = SDL_CreateWindow(title.c_str(), 0, 0, window_width*window_tile_size, window_height*window_tile_size, SDL_WINDOW_SHOWN);
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

void gfx_clear(void)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_bg, NULL, NULL);
}

void gfx_present(void)
{
    SDL_RenderPresent(renderer);
}
