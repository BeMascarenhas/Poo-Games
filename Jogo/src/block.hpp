#pragma once
#include <raylib.h>
#include "gameobject.hpp"
class Block:public GameObject{
    public:
        Block(Vector2 position);
        void Draw();
        Rectangle getRect();
    private:
        
};