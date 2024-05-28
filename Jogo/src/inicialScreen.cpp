#include "inicialScreen.hpp"


InicialScreen::InicialScreen()
{
    flag = false;
    //image = LoadTexture("Graphics/startButton.png");
}

InicialScreen::~InicialScreen()
{
    UnloadTexture(image);
}


void InicialScreen::Draw()
{
    BeginDrawing();
    ClearBackground({29,29,27,255});
    DrawText("Press Enter To Start", 200, 200, 20, WHITE);
    //DrawTexture(image, 335, 350, WHITE);


    
}
