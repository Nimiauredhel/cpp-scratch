#include "scene.hpp"

static std::vector<Scene *> scenes;
static Scene *current_scene = nullptr;

Scene::Scene(void)
    : m_size{0, 0}, doors {{}}, entities{{}}
{
    doors.clear();
    entities.clear();
}

Scene::Scene(Vector2Int new_size)
    : m_size{new_size}, doors {{}}, entities{{}}
{
    doors.clear();
    entities.clear();
}

Vector2Int Scene::GetSize(void)
{
    return m_size;
}

void Scene::CreateDoor(int x, int y, std::size_t dst_door_idx, std::size_t dst_scene_idx)
{
    if (x < 0 || x >= m_size.x
      || y < 0 || y >= m_size.y)
    {
        std::cout << "Tried to add door at invalid position." << std::endl;
        return;
    }

    doors.push_back({ {x, y}, dst_door_idx, dst_scene_idx });
}

Door *Scene::GetDoorFromIdx(std::size_t idx)
{
    if (idx >= doors.size())
    {
        std::cout << "Tried to access door at invalid index " << idx << "." << std::endl;
        return nullptr;
    }

    return &doors[idx];
}

std::size_t Scene::GetDoorCount(void)
{
    return doors.size();
}

Entity *Scene::CreateEntity(TextureId initial_texture_id, Vector2Int initial_position)
{
    Entity *entity = new Entity();
    entity->SetTexture(gfx_get_texture_ptr(initial_texture_id));
    if (initial_position.x < 0 || initial_position.x >= m_size.x
        || initial_position.y < 0 || initial_position.y >= m_size.y)
    {
        std::cout << "New entity position unspecified or invalid - defaulting to (0, 0)." << std::endl;
        initial_position = { 0, 0 };
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

void scene_set_current(std::size_t idx)
{
    if (idx >= scenes.size()) return;

    if (current_scene == scenes[idx])
    {
        std::cout << "Tried to set new scene but it's already the current scene." << std::endl;
        return;
    }

    current_scene = scenes[idx];
}

Scene *scene_get_current(void)
{
    return current_scene;
}

std::size_t scene_get_count(void)
{
    return scenes.size();
}

Scene *scene_get_by_idx(std::size_t idx)
{
    if (idx >= scenes.size())
    {
        return nullptr;
    }

    return scenes[idx];
}

std::size_t scene_add_new(Vector2Int size)
{
    scenes.push_back(new Scene(size));
    return scenes.size()-1;
}
