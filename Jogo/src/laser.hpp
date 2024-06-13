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
    //feito como private pois nao sera acessado por outras classes e como forma de protecao da vairavel de posicao
        int speed;
};