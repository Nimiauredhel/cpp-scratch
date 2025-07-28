#ifndef SCENE_HPP
#define SCENE_HPP

#include "common.hpp"

class Scene
{
    public:
        Scene(void);
        Scene(Vector2Int new_size, TextureId *new_tiles);
        Vector2Int GetSize(void);
        TextureId GetTileTextureId(int x, int y);
    private:
        Vector2Int m_size;
        TextureId *m_tiles;
};


#endif
