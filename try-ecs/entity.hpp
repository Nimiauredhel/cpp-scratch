#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "common.hpp"
#include "transform.hpp"

#define ENTITY_MAX_COUNT (200)

enum ComponentIndex
{
    COM_IDX_TRANSFORM = 0,
    COM_IDX_SPRITE = 1,
    COM_IDX_CONTROL = 2,
    COM_IDX_MAX = 2,
};

enum ComponentFlag
{
    COM_FLAG_NONE = 0x0000,
    COM_FLAG_TRANSFORM = 1 << COM_IDX_TRANSFORM,
    COM_FLAG_SPRITE = 1 << COM_IDX_SPRITE,
    COM_FLAG_CONTROL = 1 << COM_IDX_CONTROL,
};

struct Entity
{
    /// @ref ComponentFlag
    uint8_t signature;
};


#endif
