#pragma once
#include <raylib.h>
#include "gameobject.hpp"
class Block:public GameObject{
    public:
        Block(Vector2 position);
        void Draw();
        Rectangle getRect();
    private:
        //feito como private pois nao sera acessado por outras classes e como forma de protecao da vairavel de posicao
        Vector2 position;
        
};