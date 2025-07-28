#ifndef GFX_ELEMENT_HPP
#define GFX_ELEMENT_HPP

#include "common.hpp"
#include "common_sdl.hpp"
#include "transform.hpp"

class GfxElement
{
    public:
        GfxElement(void);
        void SetTexture(SDL_Texture **texture_pptr);
        void Draw(Window window_data, SDL_Renderer *renderer, Vector2Int offset);
        Transform& GetTransform(void);
    private:
        Transform m_transform;
        SDL_Texture *m_texture_ptr;
};

#endif
