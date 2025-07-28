#include "gfx_element.hpp"
#include "gfx.hpp"
#include <iostream>

GfxElement::GfxElement(void)
    : m_position{ 0 , 0 }, m_scale{ 1.0f, 1.0f }, m_texture_ptr{nullptr}
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

void GfxElement::SetPosition(int x, int y)
{
    m_position = { x, y };
}

void GfxElement::MovePosition(int x, int y)
{
    m_position.x += x;
    m_position.y +=y;
}

void GfxElement::SetScale(float x, float y)
{
    m_scale = { x, y };
}

void GfxElement::Draw(Window window_data, SDL_Renderer *renderer)
{
    if (m_texture_ptr != nullptr)
    {
        SDL_Rect destination = { m_position.x * window_data.tile_size, m_position.y * window_data.tile_size, 0, 0 };
        SDL_QueryTexture(m_texture_ptr, NULL, NULL, &destination.w, &destination.h);
        destination.w *= m_scale.x;
        destination.h *= m_scale.y;
        SDL_RenderCopy(renderer, m_texture_ptr, NULL, &destination);
    }
    else
    {
        std::cout << "Null texture pointer on gfx element" << std::endl;
        this->SetTexture(gfx_get_texture_pptr(TEXTURE_HEAD));
    }
}

