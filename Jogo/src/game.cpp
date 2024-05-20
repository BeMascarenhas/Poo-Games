
#include "game.hpp"
#include<iostream>
 using namespace std;

Game::Game()
{
    obstacles = CreateObstacles();

}

Game::~Game()
{
}

void Game::Update()
{
    for (auto& laser: spaceship.lasers)
    {
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
