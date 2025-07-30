#ifndef SCENE_HPP
#define SCENE_HPP

#include "common.hpp"
#include "gfx.hpp"
#include "entity.hpp"

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
        ~Scene(void);
        Vector2Int GetSize(void);
        void CreateDoor(int x, int y, std::size_t dst_door_idx, std::size_t dst_scene_idx);
        Door *GetDoorFromIdx(std::size_t idx);
        std::size_t GetDoorCount(void);
        Entity *CreateEntity(TextureId initial_texture_id, Vector2Int initial_position = { -1, -1 });
        void DestroyEntity(Entity *element);
        Entity *GetEntityFromIdx(std::size_t idx);
        std::size_t GetEntityCount(void);
    private:
        Vector2Int m_size;
        std::vector<Door> doors;
        std::vector<Entity *> entities;
};

void scene_set_current(std::size_t idx);
Scene *scene_get_current(void);
std::size_t scene_get_count(void);
Scene *scene_get_by_idx(std::size_t idx);
std::size_t scene_add_new(Vector2Int size);
void scene_dispose_all(void);

#endif
