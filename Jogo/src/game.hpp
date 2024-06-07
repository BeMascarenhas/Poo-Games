#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include "boss.hpp"
#include "inicialScreen.hpp"
#include <iostream>
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
        //int bosslives;
        int score;
        int highscore;
        Music music;

        friend ostream& operator<<(ostream& os, const Game& game);
        Game& operator--();
        Game& operator++();

    private:
        void DeleteInactiveLasers();
        vector<Obstacle> CreateObstacles(); 
        vector<Alien> CreateAliens();
        void MoveAliens();
        //void bossMove();
        void MoveDownAliens(int distance);
        void AlienShootlaser();
        void BossShootLaser();
        void Spawnboss();
        void GameOver();
        void Reset();
        void InitGame();
        void checkHighScore();
        void saveHighScore(int highscore,const string& name);
        void saveHighScores(int highscore,const string& name);
        int loadHighScore();
        Spaceship spaceship;
        vector<Obstacle> obstacles;
        vector<Alien> aliens;
        int alienDirection;
        int bossDirection;
        vector<Laser> alienlasers;
        vector<Laser> bossLasers;
        constexpr static float alienShootCooldown = 0.35;
        constexpr static float bossShootCooldown = 0.25;
        float timeLastAlienShoot;
        float timeLastBossShoot;
        MysteryShip mystery = MysteryShip(0,{300,350});
        MysteryShip heart = MysteryShip(1,{300,350});
        double timeMysteryCollision;
        Boss boss = Boss(0,{300,350});
        float mysteryShipSpawnInterval;
        float timeLastSpawn;
        Sound explosionSound;
        

        
};