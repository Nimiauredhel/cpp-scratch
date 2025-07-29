#include "scene.hpp"

Scene::Scene(void)
    : m_size{0, 0}, m_tiles{nullptr}
{}

Scene::Scene(Vector2Int new_size, TextureId *new_tiles)
    : m_size{new_size}, m_entrance{ 0, 0 }, m_tiles{new_tiles}
{}

Vector2Int Scene::GetSize(void)
{
    return m_size;
}

TextureId Scene::GetTileTextureId(int x, int y)
{
    if (m_tiles == nullptr
        || x < 0 || x > m_size.x
        || y < 0 || y > m_size.y)
    {
        return TEXTURE_NONE;
    }

    return m_tiles[x + (y * m_size.x)];
}

Vector2Int Scene::GetEntrance(void)
{
    return m_entrance;
}

void Scene::SetEntrance(int x, int y)
{
    if (x < 0 || x >= m_size.x
      || y < 0 || y >= m_size.y)
    {
        std::cout << "Tried to set invalid scene entrance position." << std::endl;
        return;
    }

    m_entrance = { x, y };
}
