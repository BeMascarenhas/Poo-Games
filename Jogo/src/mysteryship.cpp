#include "mysteryship.hpp"
#include<iostream>
Texture2D MysteryShip:: mysteryImages[2] = {};   
MysteryShip::MysteryShip(int type, Vector2 position): Alien(type, position)
{
    mysteryImages[2] = {};
    alive = false;
    
    if(mysteryImages[type].id == 0){

    switch (type) {
        case 0:
            mysteryImages[0] = LoadTexture("Graphics/mystery.png");
            break;
        case 1:
            mysteryImages[1] = LoadTexture("Graphics/heart.png");
            break;
        default:
            mysteryImages[0] = LoadTexture("Graphics/mystery.png");
            break;
    }
}
}

MysteryShip::~MysteryShip()
{
    for(int i = 0; i < 2; i++)
    {
        UnloadTexture(mysteryImages[i]);
    }
}

void MysteryShip::Update()
{
    
    if(alive)
    {
        position.x += speed;
        if(position.x > GetScreenWidth() - (float)mysteryImages[type].width -25 || position.x < 25)
        {
            alive = false;
        }
    }
}

void MysteryShip::Draw()
{
    if(alive)
    {
        DrawTextureV(mysteryImages[type], position, WHITE);
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
        position.x = GetScreenWidth() - (float)mysteryImages[type].width - 25;
        --(*this);
    }
    alive = true;
}

Rectangle MysteryShip::getRect()
{
    if(alive){
        return {position.x, position.y, (float)mysteryImages[type].width, (float)mysteryImages[type].height};
    }else{
        return {position.x,position.y,0,0};
    }
}
