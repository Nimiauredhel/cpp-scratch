#include "gfx_element.hpp"
#include "gfx.hpp"
#include <iostream>

GfxElement::GfxElement(void)
    : m_transform{Transform()}, m_texture_ptr{nullptr}
{
}

void GfxElement::SetTexture(SDL_Texture **texture_pptr)
{
    if (*texture_pptr != nullptr)
    {
        m_texture_ptr = *texture_pptr;
    }
    else
    {
        std::cout << "Tried to assign a null texture pointer to an element." << std::endl;
    }
}

Transform& GfxElement::GetTransform(void)
{
    return m_transform;
}

void GfxElement::Draw(Window window_data, SDL_Renderer *renderer)
{
    if (m_texture_ptr != nullptr)
    {
        Transform &transform = GetTransform();
        SDL_Rect destination = { transform.GetPosX() * window_data.tile_size, transform.GetPosY() * window_data.tile_size, 0, 0 };
        SDL_QueryTexture(m_texture_ptr, NULL, NULL, &destination.w, &destination.h);
        destination.w *= transform.GetScaleX();
        destination.h *= transform.GetScaleY();
        SDL_RenderCopy(renderer, m_texture_ptr, NULL, &destination);
    }
    else
    {
        std::cout << "Null texture pointer on gfx element" << std::endl;
        this->SetTexture(gfx_get_texture_pptr(TEXTURE_HEAD));
    }
}

