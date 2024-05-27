#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
using namespace std;
class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        void CheckCollisions();
        bool running;
        int lives;
        int score;
        int highscore;
        Music music;

    private:
        void DeleteInactiveLasers();
        vector<Obstacle> CreateObstacles(); 
        vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance);
        void AlienShootlaser();
        void GameOver();
        void Reset();
        void InitGame();
        void checkHighScore();
        void saveHighScore(int highscore);
        int loadHighScore();
        Spaceship spaceship;
        vector<Obstacle> obstacles;
        vector<Alien> aliens;
        int alienDirection;
        vector<Laser> alienlasers;
        constexpr static float alienShootCooldown = 0.35;
        float timeLastAlienShoot;
        MysteryShip mysteryShip;
        float mysteryShipSpawnInterval;
        float timeLastSpawn;
        Sound explosionSound;

        
};