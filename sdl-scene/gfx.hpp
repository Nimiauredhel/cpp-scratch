#ifndef GFX_HPP
#define GFX_HPP

#include "common.hpp"
#include "common_sdl.hpp"
#include "entity.hpp"
#include "scene.hpp"

void gfx_set_focal_entity(Entity *entity);
SDL_Texture** gfx_get_texture_pptr(TextureId id);
bool gfx_is_initialized(void);
int gfx_task(void *arg);

#endif
