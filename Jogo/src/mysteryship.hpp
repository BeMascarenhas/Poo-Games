#pragma once

#include <raylib.h>

class MysteryShip{
    public:
        MysteryShip();
        ~MysteryShip();
        void Update();
        void Draw();
        void Spawn();
        Rectangle getRect();
        bool alive;

         MysteryShip& operator++();  
         MysteryShip& operator--();

    private:
        Texture2D image;
        Vector2 position;
        int speed;


};