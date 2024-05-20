#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
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
        Spaceship spaceship;
        vector<Obstacle> obstacles;
        
};