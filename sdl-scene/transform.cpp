#include "transform.hpp"
#include "scene.hpp"

Transform::Transform(void)
    : m_position{ 0 , 0 }, m_scale{ 1.0f, 1.0f }
{
}

void Transform::SetPosition(int x, int y)
{
    m_position = { x, y };
}

void Transform::MovePosition(int x, int y)
{
    Vector2Int new_position = { m_position.x + x, m_position.y + y };

    if (new_position.x < 0 || new_position.y < 0) return;
    Vector2Int scene_size = scene_get_current()->GetSize();
    if (new_position.x >= scene_size.x || new_position.y >= scene_size.y) return;

    m_position= new_position;
}

void Transform::SetScale(float x, float y)
{
    m_scale = { x, y };
}

int Transform::GetPosX(void)
{
    return m_position.x;
}

int Transform::GetPosY(void)
{
    return m_position.y;
}

float Transform::GetScaleX(void)
{
    return m_scale.x;
}

float Transform::GetScaleY(void)
{
    return m_scale.y;
}
