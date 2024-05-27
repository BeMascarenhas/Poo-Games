#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>
using namespace std;

class Spaceship{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        Rectangle getRect();
        void Reset();
        vector<Laser> lasers;

    private:
        Texture2D image;
        Vector2 position;
        double lastFireTime;
        Sound laserSound;
        
};