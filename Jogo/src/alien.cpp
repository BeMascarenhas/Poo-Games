#include "alien.hpp"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(Vector2 position)
{
    this->position = position;
 
}
void Alien::Draw()
{
    DrawTextureV(alienImages[type],position, WHITE);
}

void Alien::Update(int direction)
{
    position.x += direction;

}

void Alien::UnloadImages()
{
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

Alien1::Alien1(Vector2 position): Alien(position)
{
    type = 0;
    if (alienImages[type].id == 0)
    {
        alienImages[type] = LoadTexture("Graphics/alien_1.png");
    }
    this->position = position;
    
}

Alien2::Alien2(Vector2 position): Alien(position)
{
    type = 1;
    if (alienImages[type].id == 0)
    {
        alienImages[type] = LoadTexture("Graphics/alien_2.png");
    }
    this->position = position;
}
    
    




Alien3::Alien3(Vector2 position): Alien(position)
{
    this->position = position;
    type = 2;
    if (alienImages[type].id == 0)
    {
        alienImages[type] = LoadTexture("Graphics/alien_3.png");
    }
}

