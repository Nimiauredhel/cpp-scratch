#include "scene.hpp"

static std::vector<Scene *> scenes;
static Scene *current_scene = nullptr;

Scene::Scene(void)
    : m_size{0 , 0}, doors{{}}, tiles{{}}, entities{{}}
{
    doors.clear();
    tiles.clear();
    entities.clear();
}

Scene::Scene(Vector2Int new_size)
    : m_size{new_size}, doors{{}}, tiles{{}}, entities{{}}
{
    doors.clear();
    entities.clear();
    tiles.clear();

    int tile_count = m_size.x * m_size.y;

    for (int i = 0; i < tile_count; i++)
    {
        tiles.push_back({ TILE_FLOOR, {}});
    }
}

Scene::Scene(Vector2Int new_size, std::vector<TileSequence> *blueprint)
    : m_size{new_size}, doors{{}}, tiles{{}}, entities{{}}
{
    doors.clear();
    entities.clear();
    tiles.clear();

    int tile_count = m_size.x * m_size.y;
    int sequence_count = blueprint->size();

    int tile_idx = 0;

    for (int s = 0; s < sequence_count; s++)
    {
        for (int t = 0; t < (*blueprint)[s].length; t++)
        {
            tiles.push_back({(*blueprint)[s].type, {}});
            tile_idx++;
        }
    }

    // fill in the remainder with regular floor tiles
    for (int i = tile_idx; i < tile_count; i++)
    {
        tiles.push_back({ TILE_FLOOR, {}});
    }
}

Scene::~Scene(void)
{
    std::size_t entity_count = entities.size();

    std::cout << "Deleting " << entity_count << " entities." << std::endl;

    for (int i = entity_count -1; i >= 0; i--)
    {
        if(entities[i] != nullptr)
        {
            delete(entities[i]);
        }

        entities.pop_back();
    }

    entities.clear();
}

Vector2Int Scene::GetSize(void)
{
    return m_size;
}

TileType Scene::GetTileTypeByIdx(std::size_t idx)
{
    if (idx < tiles.size())
    {
        return tiles[idx].type;
    }

    return TILE_NONE;
}

TileInstance *Scene::GetTilePtrByIdx(std::size_t idx)
{
    if (idx < tiles.size())
    {
        return &tiles[idx];
    }

    return nullptr;
}

TileType Scene::GetTileTypeByCoord(int x, int y)
{
    int idx = x + (m_size.x * y);
    return GetTileTypeByIdx(idx);
}

TileInstance *Scene::GetTilePtrByCoord(int x, int y)
{
    int idx = x + (m_size.x * y);
    return GetTilePtrByIdx(idx);
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

std::size_t scene_add_new(Vector2Int size, std::vector<TileSequence> blueprint)
{
    if (blueprint.size() == 0)
    {
        scenes.push_back(new Scene(size));
    }
    else
    {
        scenes.push_back(new Scene(size, &blueprint));
    }
    return scenes.size()-1;
}

void scene_dispose_all(void)
{
    std::size_t scene_count = scenes.size();

    for (int i = scene_count -1; i >= 0; i--)
    {
        std::cout << "Deleting scene #" << i << "." << std::endl;

        if(scenes[i] != nullptr)
        {
            delete(scenes[i]);
        }

        scenes.pop_back();
    }

    scenes.clear();
}
