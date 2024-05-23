#pragma once
#include <raylib.h>
#include "gameobject.hpp"
class Laser: public GameObject{
    public:
        Laser(Vector2 position, int speed);
        void Update();
        void Draw();
        Rectangle getRect();
        bool active;
    private:
        Vector2 position;
        int speed;
};