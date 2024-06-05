#pragma once

#include <raylib.h>
#include "gameobject.hpp"
class Alien :public GameObject{
    public:
        Alien( int type, Vector2 position);
        virtual void Draw();
        void Update(int direction);
        int getType();
        static void UnloadImages();
        Rectangle getRect();
        static Texture2D alienImages[5];
        int type;
        Vector2 position;

   

    private:
};

