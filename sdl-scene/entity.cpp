#include "entity.hpp"
#include "gfx.hpp"

Entity::Entity(void)
    : m_transform{Transform()}, m_texture_ptr{nullptr}
{
}

void Entity::SetTexture(SDL_Texture *texture_ptr)
{
    if (texture_ptr != nullptr)
    {
        m_texture_ptr = texture_ptr;
    }
    else
    {
        std::cout << "Tried to assign a null texture pointer to an element." << std::endl;
    }
}

Transform& Entity::GetTransform(void)
{
    return m_transform;
}

void Entity::Draw(Window window_data, SDL_Renderer *renderer, Vector2Int offset)
{
    if (m_texture_ptr != nullptr)
    {
        Vector2Int draw_pos = { 0, 0 };
        Transform &transform = GetTransform();

        draw_pos.x = offset.x + transform.GetPosX();
        if (draw_pos.x < 0 || draw_pos.x >= window_data.width) return;
        draw_pos.y = offset.y + transform.GetPosY();
        if (draw_pos.y < 0 || draw_pos.y >= window_data.height) return;
        SDL_Rect destination = { draw_pos.x*window_data.tile_size, draw_pos.y*window_data.tile_size, 0, 0 };
        SDL_QueryTexture(m_texture_ptr, NULL, NULL, &destination.w, &destination.h);
        destination.w *= transform.GetScaleX();
        destination.h *= transform.GetScaleY();
        SDL_RenderCopy(renderer, m_texture_ptr, NULL, &destination);
    }
    else
    {
        std::cout << "Null texture pointer on gfx element" << std::endl;
        this->SetTexture(gfx_get_texture_ptr(TEXTURE_HUMANOID1));
    }
}

