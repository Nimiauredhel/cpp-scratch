#include "transform.hpp"

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
    m_position.x += x;
    m_position.y +=y;
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
