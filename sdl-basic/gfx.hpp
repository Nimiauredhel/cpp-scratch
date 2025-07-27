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

void gfx_window_init(int width, int height, int tile_size);
void gfx_window_deinit(void);
SDL_Texture** gfx_get_texture_pptr(TextureId id);
void gfx_draw_element(GfxElement *element);
void gfx_clear(void);
void gfx_present(void);

#endif
