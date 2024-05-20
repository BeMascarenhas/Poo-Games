
#include "game.hpp"
#include<iostream>
 using namespace std;

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    alienDirection = 1;
    timeLastAlienShoot =0;

}

Game::~Game()
{
    Alien::UnloadImages();
}

void Game::Update()
{
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
   
}

void Game::HandleInput()
{
    if(IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }else if(IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    } else if (IsKeyDown(KEY_SPACE))
    {
        spaceship.FireLaser();
        cout<<"Laser Fired"<<endl;
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
}

vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size()*3;
    float gap = (GetScreenWidth() - obstacleWidth * 4) / 5;

    for(int i= 0; i<4 ; i++){
        float offsetX = (i+1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() -100)}));
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
            }else if (i == 1 || i == 2)
            {
                Vector2 position = {float(j*55)+75, float(i*55)+110};
                aliens.push_back(Alien2(position));
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
        if (alien.position.x + alien.alienImages[alien.type].width > GetScreenWidth())
        {
            alienDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 0)
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
