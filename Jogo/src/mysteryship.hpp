#pragma once

#include <raylib.h>

class MysteryShip{
    public:
        MysteryShip();
        ~MysteryShip();
        void Update();
        void Draw();
        void Spawn();
        bool alive;

    private:
        Texture2D image;
        Vector2 position;
        int speed;


};