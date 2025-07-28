#ifndef GFX_HPP
#define GFX_HPP

#include "common.hpp"
#include "common_sdl.hpp"
#include "gfx_element.hpp"
#include "scene.hpp"

SDL_Texture** gfx_get_texture_pptr(TextureId id);
bool gfx_is_initialized(void);
GfxElement *gfx_create_element(TextureId initial_texture_id);
void gfx_destroy_element(GfxElement *element);
void gfx_set_focal_element(GfxElement *element);
void gfx_set_scene(Scene *new_scene);
int gfx_task(void *arg);

#endif
