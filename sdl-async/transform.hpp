#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "common.hpp"

class Transform
{
    public:
        Transform(void);
        void SetPosition(int x, int y);
        void SetScale(float x, float y);
        void MovePosition(int x, int y);
        int GetPosX(void);
        int GetPosY(void);
        float GetScaleX(void);
        float GetScaleY(void);
    private:
        Vector2Int m_position;
        Vector2Float m_scale;
};

#endif
