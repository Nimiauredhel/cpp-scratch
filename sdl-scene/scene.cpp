#include "scene.hpp"

static Scene *current_scene = nullptr;

Scene::Scene(void)
    : m_size{0, 0}, m_entrance{ 0, 0 }, m_tiles{nullptr}, entities{{}}
{}

Scene::Scene(Vector2Int new_size, TextureId *new_tiles)
    : m_size{new_size}, m_entrance{ 0, 0 }, m_tiles{new_tiles}, entities{{}}
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

Entity *Scene::CreateEntity(TextureId initial_texture_id, Vector2Int initial_position)
{
    Entity *entity = new Entity();
    entity->SetTexture(gfx_get_texture_pptr(initial_texture_id));
    if (initial_position.x < 0 || initial_position.x >= m_size.x
        || initial_position.y < 0 || initial_position.y >= m_size.y)
    {
        std::cout << "New entity position unspecified or invalid - defaulting to entrance" << std::endl;
        initial_position = m_entrance;
    }
    entity->GetTransform().SetPosition(initial_position.x, initial_position.y);
    entities.push_back(entity);
    return entity;
}

void Scene::DestroyEntity(Entity *entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);

    if (it != entities.end())
    {
        entities.erase(it);
    }

    delete(entity);
}

Entity *Scene::GetEntityFromIdx(std::size_t idx)
{
    if (idx >= entities.size())
    {
        std::cout << "Tried to access entity at invalid index " << idx << "." << std::endl;
        return nullptr;
    }

    return entities[idx];
}

std::size_t Scene::GetEntityCount(void)
{
    return entities.size();
}

void scene_set_current(Scene *new_scene)
{
    if (current_scene == new_scene)
    {
        std::cout << "Tried to set new scene but it's already the current scene." << std::endl;
        return;
    }

    current_scene = new_scene;
}

Scene *scene_get_current(void)
{
    return current_scene;
}
