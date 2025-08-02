#include "scene.hpp"

static std::vector<Scene *> scenes;
static Scene *current_scene = nullptr;

Scene::Scene(void)
    : m_size{0 , 0}, doors{{}}, tiles{{}}, entity_count{0}, entity_next{0}, entities{{}}, transforms{{}}, sprites{{}}

{
    doors.clear();
    tiles.clear();

    entity_count = 0;
    entity_next = 0;
    explicit_bzero(entities, ENTITY_MAX_COUNT);
}

Scene::Scene(Vector2Int new_size)
    : m_size{new_size}, doors{{}}, tiles{{}}, entity_count{0}, entity_next{0}, entities{{}}, transforms{{}}, sprites{{}}
{
    doors.clear();
    tiles.clear();

    entity_count = 0;
    entity_next = 0;
    explicit_bzero(entities, ENTITY_MAX_COUNT);

    int tile_count = m_size.x * m_size.y;

    for (int i = 0; i < tile_count; i++)
    {
        tiles.push_back({ TILE_FLOOR, {}});
    }
}

Scene::Scene(Vector2Int new_size, std::vector<TileSequence> *blueprint)
    : m_size{new_size}, doors{{}}, tiles{{}}, entity_count{0}, entity_next{0}, entities{{}}, transforms{{}}, sprites{{}}
{
    doors.clear();
    tiles.clear();

    entity_count = 0;
    entity_next = 0;
    explicit_bzero(entities, ENTITY_MAX_COUNT);

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
    doors.clear();
    tiles.clear();
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

uint16_t Scene::CreateEntity(uint8_t flags)
{
    if (entity_count >= ENTITY_MAX_COUNT)
    {
        /// TODO: return value indicating max entities
        return 0;
    }

    entity_count++;

    /// TODO: extract & optimize (e.g. start from next+1)
    for (uint16_t i = 0; i < ENTITY_MAX_COUNT; i++)
    {
        if (entities[i].signature == 0)
        {
            entity_next = i;
            break;
        }
    }

    uint16_t idx = entity_next;
    entities[idx].signature = flags;

    if (flags & COM_FLAG_TRANSFORM)
    {
        explicit_bzero(transforms+idx, sizeof(Transform));
    }

    if (flags & COM_FLAG_SPRITE)
    {
        explicit_bzero(sprites+idx, sizeof(Sprite));
    }

    return idx;
}

void Scene::DestroyEntity(uint16_t idx)
{
    entities[idx].signature = COM_FLAG_NONE;
}

Entity &Scene::GetEntityFromIdx(uint16_t idx)
{
    return entities[idx];
}

uint16_t Scene::GetEntityCount(void)
{
    return entity_count;
}

Entity *Scene::GetEntities(void)
{
    return entities;
}

Transform *Scene::GetTransforms(void)
{
    return transforms;
}

Sprite *Scene::GetSprites(void)
{
    return sprites;
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
