#pragma once
#include <raylib.h>
#include "alien.hpp"

class Boss:public Alien{
    public:
        Boss(int type, Vector2 position);
        void Update(int direction);
        void Draw();
        int getType();
        Rectangle getRect();
        bool alive = false;
        static Texture2D bossImages[2];
        static void UnloadImages();
        Vector2 position;
        int lives;
        void bossMove();
        int bossDirection;
    private:
        
};