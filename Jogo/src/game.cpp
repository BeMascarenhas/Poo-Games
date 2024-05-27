
#include "game.hpp"
#include<iostream>
#include <fstream>
 using namespace std;

Game::Game()
{
    music = LoadMusicStream("Sounds/music.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
    

}

Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);

}

void Game::Update()
{
    if(running){
        double currentTime = GetTime();
        if(currentTime - timeLastSpawn > mysteryShipSpawnInterval)
        {
            mysteryShip.Spawn();
            timeLastSpawn = currentTime;
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }


        for (auto& laser: spaceship.lasers)
        {
            laser.Update();
        }


        MoveAliens();

        AlienShootlaser();

        for (auto& laser: alienlasers){
            laser.Update();
        }

        DeleteInactiveLasers();
        mysteryShip.Update();
        CheckCollisions();
    }else{
        if(IsKeyDown(KEY_ENTER))
        {
           Reset();
           InitGame();
    
        }
    }
}
void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }
    for (auto& obstacle: obstacles)
    {
        obstacle.Draw();
    }
    for ( auto& alien: aliens)
    {
        alien.Draw();
    }
    for(auto& laser: alienlasers)
    {
        laser.Draw();
    }
    mysteryShip.Draw();
   
}

void Game::HandleInput()
{
    if(running){
        if(IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft();
        }else if(IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE))
        {
            spaceship.FireLaser();
            //cout<<"Laser Fired"<<endl;
        }
    }

}

void Game::CheckCollisions()
{
    for(auto& laser: spaceship.lasers)
    {
       auto it = aliens.begin();
         while(it != aliens.end())
         {
              cout<<aliens.size()<<endl;
              
              if(CheckCollisionRecs(it->getRect(),laser.getRect()))
              {
                PlaySound(explosionSound);
                if(it-> type == 0){
                    score+=100;
                }else if(it->type == 1){
                    score+=200;
                }else if(it->type == 2){
                    score+=300;
                }else if(it->type == 3){
                    score+=400;
                }else if(it->type == 4){
                    score+=500;
                }
                checkHighScore();
                it = aliens.erase(it);
                laser.active = false;
              }else
              {
                it++;
              }
              if(aliens.size() == 0)
              {
                  GameOver();
              }
         }
         for(auto& obstacle: obstacles)
         {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->getRect(),laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }else
                {
                    it++;
                }
            }
         }
        
         if(CheckCollisionRecs(mysteryShip.getRect(),laser.getRect()))
         {
             mysteryShip.alive = false;
             laser.active = false;
             score += 1000;
             checkHighScore();
             PlaySound(explosionSound);
         }
        
    }
    for(auto& laser: alienlasers)
    {
        if(CheckCollisionRecs(laser.getRect(),spaceship.getRect()))
        {
            laser.active = false;
            //cout<<"Spaceship hit"<<endl;
            lives--;
            if(lives == 0)
            {
                GameOver();
            }
        }
        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->getRect(),laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }else
                {
                    it++;
                }
            }
        }
    }
    for(auto& alien: aliens)
    {
        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin(); 
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->getRect(),alien.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                }else
                {
                    it++;
                }
            }
        }
        if(CheckCollisionRecs(alien.getRect(),spaceship.getRect()))
        {
            //cout<<"Spaceship hit"<<endl;
            GameOver();
        }
    }
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if(!it->active)
        {
            it = spaceship.lasers.erase(it);
        }else
        {
            it++;
        }
    }
    for(auto it = alienlasers.begin(); it != alienlasers.end();)
    {
        if(!it->active)
        {
            it = alienlasers.erase(it);
        }else
        {
            it++;
        }
    }
}

vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size()*3;
    float gap = (GetScreenWidth() - obstacleWidth * 4) / 5;

    for(int i= 0; i<4 ; i++){
        float offsetX = (i+1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() -200)}));
    }
    return obstacles;

}


vector<Alien> Game::CreateAliens()
{
    vector<Alien> aliens;
    for(int i = 0; i<5;i++){
        for(int j = 0; j<11; j++){
            if(i == 0)
            {
                Vector2 position = {float(j*55)+75, float(i*55)+110};
                aliens.push_back(Alien3(position));
                continue;
            }else if (i == 1)
            {
                Vector2 position = {float(j*55)+75, float(i*55)+110};
                aliens.push_back(Alien2(position));
                continue;
            }else if(i == 2){
                Vector2 position = {float(j*55)+75, float(i*55)+110};
                aliens.push_back(Alien4(position));
                continue;
            }else if(i == 3){
                Vector2 position = {float(j*55)+75, float(i*55)+110};
                aliens.push_back(Alien5(position));
                continue;
            }else{
            Vector2 position = {float(j*55)+75, float(i*55)+110};
            aliens.push_back(Alien1(position));
        }
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for(auto& alien: aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type].width > GetScreenWidth() - 25)
        {
            alienDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
        {
            alienDirection = 1;
            MoveDownAliens(4);
        }
        
        alien.Update(alienDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto& alien: aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootlaser()
{
    double curretnTime = GetTime();
    if(curretnTime - timeLastAlienShoot >= alienShootCooldown && !aliens.empty())
    {
   
        int randomIndex = GetRandomValue(0, aliens.size()-1);
        Alien& alien = aliens[randomIndex];
        alienlasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type].width/2, alien.position.y + alien.alienImages[alien.type].height}, 6));
        timeLastAlienShoot = GetTime();
    }
}

void Game::GameOver()
{
    cout<<"Game Over"<<endl;
    running = false;
   
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienlasers.clear();
    obstacles.clear();
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    alienDirection = 1;
    timeLastAlienShoot =0;
    timeLastSpawn =0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    score = 0;
    highscore = loadHighScore();
    running = true;
}

void Game::checkHighScore()
{
    if(score > highscore)
    {
        highscore = score;
        saveHighScore(highscore);
    }
}

void Game::saveHighScore(int highscore)
{
    ofstream highScoreFile("highscore.txt");
    if(highScoreFile.is_open())
    {
        highScoreFile<<highscore;
        highScoreFile.close();
    }else{
        cerr<<"Unable to open file"<<endl;
    }
}

int Game::loadHighScore()
{
    int loadedHighScore = 0;
    ifstream highScoreFile("highscore.txt");
    if(highScoreFile.is_open())
    {
        highScoreFile>>loadedHighScore;
        highScoreFile.close();
    }else{
        cerr<<"Unable to open file"<<endl;
    }
    return loadedHighScore;
}
