#pragma once
#include "alien.hpp"
#include <raylib.h>

class MysteryShip:public Alien{
    public:
        MysteryShip(int type, Vector2 position);
        ~MysteryShip();
        void Update();
        void Draw();
        void Spawn();
        Rectangle getRect();
        static Texture2D mysteryImages[2];// static pelo mesmo motivo de alien
        Vector2 position;
        int speed;
        bool alive;

         MysteryShip& operator++();  
         MysteryShip& operator--();

    private:
        
       


};