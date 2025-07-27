#ifndef GFX_ELEMENT_HPP
#define GFX_ELEMENT_HPP

#include "common.hpp"
#include "common_sdl.hpp"

class GfxElement
{
    public:
        GfxElement(void);
        void SetTexture(SDL_Texture **texture_pptr);
        void SetPosition(int x, int y);
        void SetScale(float x, float y);
        void Draw(Window window_data, SDL_Renderer *renderer);
    private:
        Vector2Int m_position;
        Vector2Float m_scale;
        SDL_Texture *m_texture_ptr;
};

#endif
