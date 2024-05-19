#include <raylib.h>


class spaceship{
private:
    Vector2 position;
public:
Texture2D Image;


spaceship(){
    Image = LoadTexture("Graphics/spaceship.png");
    position = {100, 100};
}


void draw(){
    DrawTextureV(Image, position, WHITE);
}


};