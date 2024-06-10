#pragma once
#include <raylib.h>
#include "alien.hpp"

class Boss:public Alien{
    public:
        Boss(int type, Vector2 position);
        void Update(int direction);
        void Draw() override;// aqui podemos ver eu sobreescrevendo a funcao Draw de alien
        int lives;
        int getType();
        Rectangle getRect();
        bool alive = false;
        Texture2D bossImages[1];
        void UnloadImages();
        Vector2 position;
        void bossMove();
        int bossDirection;

        Boss& operator--();//operador usado para decrementar a vida do boss

    private:

};