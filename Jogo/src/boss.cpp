#include "boss.hpp"
Boss::Boss(int type, Vector2 position): Alien(type, position)
{ 
    bossImages[1] = {};  
    bossDirection = 2;
    this -> type = type;
    this -> position = position;
    position.y = 50;
    position.x = 50;
    if(bossImages[type].id == 0){

    switch (type) {
        case 0:
            bossImages[0] = LoadTexture("Graphics/Boss.png");
            break;
        default:
            bossImages[0] = LoadTexture("Graphics/Boss.png");
            break;
    }
}
}

void Boss::Update(int direction)
{
    position.x += direction;
}

void Boss::Draw()
{
    if(alive){
    DrawTextureV(bossImages[type],position, WHITE);
    }
}

int Boss::getType()
{
    return this -> type;
}

Rectangle Boss::getRect()
{
    return {position.x, position.y, (float)bossImages[type].width, (float)bossImages[type].height};
}

void Boss::UnloadImages()
{
  UnloadTexture(bossImages[0]);
    
}

void Boss::bossMove()
{
    Update(bossDirection);
    if(position.x > GetScreenWidth() - bossImages[type].width - 25 || position.x < 25)
    {
        bossDirection *= -1;
        
    }
}

Boss& Boss::operator--() {
    --lives;
    return *this;
}

