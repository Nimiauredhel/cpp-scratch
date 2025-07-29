#ifndef SCENE_HPP
#define SCENE_HPP

#include "common.hpp"
#include "gfx.hpp"
#include "entity.hpp"

class Scene
{
    public:
        Scene(void);
        Scene(Vector2Int new_size, TextureId *new_tiles);
        Vector2Int GetSize(void);
        TextureId GetTileTextureId(int x, int y);
        Vector2Int GetEntrance(void);
        void SetEntrance(int x, int y);
        Entity *CreateEntity(TextureId initial_texture_id, Vector2Int initial_position = { -1, -1 });
        void DestroyEntity(Entity *element);
        Entity *GetEntityFromIdx(std::size_t idx);
        std::size_t GetEntityCount(void);
    private:
        Vector2Int m_size;
        Vector2Int m_entrance;
        TextureId *m_tiles;
        std::vector<Entity *> entities;
};

void scene_set_current(Scene *new_scene);
Scene *scene_get_current(void);

#endif
