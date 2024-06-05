#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
    
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

void MysteryShip::Update()
{
    if(alive)
    {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width -25 || position.x < 25)
        {
            alive = false;
        }
    }
}

void MysteryShip::Draw()
{
    if(alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}
MysteryShip& MysteryShip::operator++() {
    speed = 3;
    return *this;
}
MysteryShip& MysteryShip::operator--() {
    speed = -3;
    return *this;
}
void MysteryShip::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0,1);
    if(side == 0)
    {
        position.x = 25;
        ++(*this);
    }else
    {
        position.x = GetScreenWidth() - image.width - 25;
        --(*this);
    }
    alive = true;
}

Rectangle MysteryShip::getRect()
{
    if(alive){
        return {position.x, position.y, (float)image.width, (float)image.height};
    }else{
        return {position.x,position.y,0,0};
    }
}
