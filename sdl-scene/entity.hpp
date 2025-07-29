#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "common.hpp"
#include "common_sdl.hpp"
#include "transform.hpp"

class Entity
{
    public:
        Entity(void);
        void SetTexture(SDL_Texture *texture_ptr);
        void Draw(Window window_data, SDL_Renderer *renderer, Vector2Int offset);
        Transform& GetTransform(void);
    private:
        Transform m_transform;
        SDL_Texture *m_texture_ptr;
};

#endif
