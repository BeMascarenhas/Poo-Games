#include "alien.hpp"

Texture2D Alien::alienImages[5] = {};

Alien::Alien(int type,Vector2 position): GameObject(position)
{
    this->type = type;
     if(alienImages[type].id == 0){

    switch (type) {
        case 0:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 1:
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 2: 
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            break;
        case 3:
            alienImages[3] = LoadTexture("Graphics/alien_5.png");
            break;
        case 4:
            alienImages[4] = LoadTexture("Graphics/alien_6.png");
            break;  
        default:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
    }
}
}
void Alien::Draw()
{
    DrawTextureV(alienImages[type],position, WHITE);
}

void Alien::Update(int direction)
{
    position.x += direction;

}

int Alien::getType()
{
    return type;
}

void Alien::UnloadImages()
{
    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::getRect()
{
    return {position.x, position.y, (float)alienImages[type].width, (float)alienImages[type].height};
}

