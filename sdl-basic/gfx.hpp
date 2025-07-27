#ifndef GFX_H
#define GFX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

struct Vector2Int
{
    int x;
    int y;
};

struct Vector2Float
{
    float x;
    float y;
};

class GfxElement
{
    public:
        GfxElement(void);
        void SetTexture(SDL_Texture **texture_pptr);
        void SetPosition(int x, int y);
        void SetScale(float x, float y);
        void Draw(void);
    private:
        Vector2Int m_position;
        Vector2Float m_scale;
        SDL_Texture *m_texture_ptr;
};

void gfx_window_init(int width, int height, int tile_size);
void gfx_window_deinit(void);
void gfx_clear(void);
void gfx_present(void);

#endif
