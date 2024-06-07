#pragma once

#include "raylib.h"


class GameObject{
    public:
        GameObject(Vector2 position);
        ~GameObject();
        virtual void Draw() = 0;
        Vector2 position;
};