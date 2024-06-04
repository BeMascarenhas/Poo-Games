#pragma once
#include <raylib.h>
#include "alien.hpp"

class Boss:public Alien{
    public:
        Boss(int type, Vector2 position);
        void Update(int direction);
        void Draw() override;
        int lives;
        int getType();
        Rectangle getRect();
        bool alive = false;
        static Texture2D bossImages[2];
        static void UnloadImages();
        Vector2 position;
        void bossMove();
        int bossDirection;

        Boss& operator--();
    private:
        
};