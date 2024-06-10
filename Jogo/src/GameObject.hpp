#pragma once

#include "raylib.h"


class GameObject{
    public:
        GameObject(Vector2 position);
        ~GameObject();
        virtual void Draw() = 0;// essa e a classe abstrata(pura) do codigo que sera herdada por outras, obrigando-as a ter a funcao Draw
        Vector2 position;
};