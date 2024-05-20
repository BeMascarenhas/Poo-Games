#include "inicialScreen.hpp"


InicialScreen::InicialScreen()
{
    flag = false;
}

InicialScreen::~InicialScreen()
{
}

void InicialScreen::Draw()
{
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Press Enter to start", 200, 200, 20, BLACK);

    
}
