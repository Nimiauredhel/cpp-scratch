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

extern bool should_terminate;

#endif
