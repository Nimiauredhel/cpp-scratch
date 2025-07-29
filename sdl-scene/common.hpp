#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <vector>
#include <algorithm>

struct Window
{
    int width;
    int height;
    int tile_size;
};

struct Vector2Int
{
    int x;
    int y;
};

struct Vector2Float
{
    float x;
    float y;
};

enum TextureId
{
    TEXTURE_NONE = 0,
    TEXTURE_BG = 1,
    TEXTURE_HEAD = 2,
};

extern bool should_terminate;

#endif
