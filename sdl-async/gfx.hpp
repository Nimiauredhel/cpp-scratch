#ifndef GFX_HPP
#define GFX_HPP

#include "common_sdl.hpp"
#include "gfx_element.hpp"

enum TextureId
{
    TEXTURE_NONE = 0,
    TEXTURE_BG = 1,
    TEXTURE_HEAD = 2,
};

SDL_Texture** gfx_get_texture_pptr(TextureId id);
bool gfx_is_initialized(void);
GfxElement *gfx_create_element(TextureId initial_texture_id);
void gfx_destroy_element(GfxElement *element);
int gfx_task(void *arg);

#endif
