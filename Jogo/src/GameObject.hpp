#pragma once

#include "raylib.h"


class GameObject{
    public:
        GameObject(Vector2 position);
        ~GameObject();
        Vector2 position;
        Vector2 getPosition();
};