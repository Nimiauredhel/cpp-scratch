#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>

#include "common.hpp"

#include "entity.hpp"
#include "transform.hpp"
#include "sprite.hpp"

enum TileType
{
    TILE_NONE = 0,
    TILE_FLOOR = 1,
    TILE_WALL = 2,
};

struct TileSequence
{
    int length;
    TileType type;
};

struct TileInstance
{
    TileType type;
    std::list<Entity> contents;
};

struct Door
{
    Vector2Int position;
    std::size_t dest_door_index;
    std::size_t dest_scene_index;
};

class Scene
{
    public:
        Scene(void);
        Scene(Vector2Int new_size);
        Scene(Vector2Int new_size, std::vector<TileSequence> *blueprint);
        ~Scene(void);

        Vector2Int GetSize(void);
        TileType GetTileTypeByIdx(std::size_t idx);
        TileInstance *GetTilePtrByIdx(std::size_t idx);
        TileType GetTileTypeByCoord(int x, int y);
        TileInstance *GetTilePtrByCoord(int x, int y);

        void CreateDoor(int x, int y, std::size_t dst_door_idx, std::size_t dst_scene_idx);
        Door *GetDoorFromIdx(std::size_t idx);
        std::size_t GetDoorCount(void);

        uint16_t CreateEntity(uint8_t flags);
        void DestroyEntity(uint16_t idx);
        Entity &GetEntityFromIdx(uint16_t idx);
        uint16_t GetEntityCount(void);
        Entity *GetEntities(void);
        Transform *GetTransforms(void);
        Sprite *GetSprites(void);

    private:
        Vector2Int m_size;
        std::vector<Door> doors;
        std::vector<TileInstance> tiles;

        uint16_t entity_count;
        uint16_t entity_next;
        Entity entities[ENTITY_MAX_COUNT];
        Transform transforms[ENTITY_MAX_COUNT];
        Sprite sprites[ENTITY_MAX_COUNT];
};

void scene_set_current(std::size_t idx);
Scene *scene_get_current(void);
std::size_t scene_get_count(void);
Scene *scene_get_by_idx(std::size_t idx);
std::size_t scene_add_new(Vector2Int size, std::vector<TileSequence> blueprint);
void scene_dispose_all(void);

#endif
