#include "spaceship.hpp"
#include "laser.hpp"
Texture2D Spaceship::image;
Spaceship::Spaceship()
{
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 120;
    lastFireTime = 0.0;
    laserSound = LoadSound("Sounds/laser.ogg");
    fireRate = 0.35;

}

Spaceship::~Spaceship() {
    UnloadTexture(image);
    UnloadSound(laserSound);
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}
Spaceship& Spaceship::operator++() {
    position.x += 7;
    return *this;
}
Spaceship& Spaceship::operator--() {
    position.x -= 7;
    return *this;
}

void Spaceship::MoveLeft() {
    --(*this);
    if(position.x < 25) {
        position.x = 25;
    }
}

void Spaceship::MoveRight() {
    ++(*this);
    if(position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
        
    }
}

void Spaceship::FireLaser() {
    if(GetTime() - lastFireTime >= fireRate) {
       
   lasers.push_back(Laser({position.x + image.width/2 -2 , position.y},-6));
   lastFireTime = GetTime();
   PlaySound(laserSound);
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, (float)image.width, (float)image.height};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height-100;
    lasers.clear();
}
