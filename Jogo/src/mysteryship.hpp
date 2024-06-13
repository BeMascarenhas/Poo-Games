#pragma once
#include "alien.hpp"
#include <raylib.h>

class MysteryShip:public Alien{
    public:
        MysteryShip(int type, Vector2 position);
        ~MysteryShip();
        void Update();
        void Draw() override;
        void Spawn();
        Rectangle getRect();
        static Texture2D mysteryImages[2];// static pelo mesmo motivo de alien
        int speed;
        bool alive;

         MysteryShip& operator++(); //seta o incremento da posicao para 3, pois vai para a direita
         MysteryShip& operator--();//seta o incremento da posicao para -3, pois vai para a esquerda

    private:
        
       


};