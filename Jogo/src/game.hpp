#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
using namespace std;
class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();

    private:
        void DeleteInactiveLasers();
        vector<Obstacle> CreateObstacles(); 
        vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance);
        void AlienShootlaser();
        Spaceship spaceship;
        vector<Obstacle> obstacles;
        vector<Alien> aliens;
        int alienDirection;
        vector<Laser> alienlasers;
        constexpr static float alienShootCooldown = 0.35;
        float timeLastAlienShoot ;
        
};