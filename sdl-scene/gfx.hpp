#ifndef GFX_HPP
#define GFX_HPP

#include "common.hpp"
#include "common_sdl.hpp"
#include "entity.hpp"

#define TEXTURE_ID_COUNT (6)

enum TextureId
{
    TEXTURE_NONE = 0,
    TEXTURE_BG = 1,
    TEXTURE_FLOOR = 2,
    TEXTURE_WALL = 3,
    TEXTURE_DOOR = 4,
    TEXTURE_PLAYER = 5,
};

void gfx_set_focal_entity(Entity *entity);
SDL_Texture* gfx_get_texture_ptr(TextureId id);
bool gfx_is_initialized(void);
int gfx_task(void *arg);

#endif
