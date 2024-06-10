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
        float fireRate;
        Spaceship& operator++();  
        Spaceship& operator--();  
        static Texture2D image;//feito como static para nao precisar inicializar um objeto e ser acessado livremente em incial screen onde tem seu valor mudado.

    private:
        //feito como private para que nao seja acessado por outras classes e como forma de protecao da vairavel de posicao
        Vector2 position;
        double lastFireTime;
        Sound laserSound;
        
};