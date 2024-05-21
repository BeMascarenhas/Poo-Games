#include <raylib.h>
#include "game.hpp"
#include "obstacle.hpp"
#include "inicialScreen.hpp"

typedef enum GameScreen { Inicial, Gameplay } GameScreen;
int main()
{
  
   InitWindow(750, 700, "Space Invaders para poo");
   GameScreen currentScreen = Inicial;
   SetTargetFPS(60);

    Color grey = {29,29,27,255};
    InicialScreen inicialscreen;
    Game game;
    
    
   
    while (!WindowShouldClose()){
        switch (currentScreen)
        {case Inicial:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = Gameplay;
                }
            }break;
            default: break;
        }
        if (currentScreen == Gameplay)
        {
            game.HandleInput();
            game.Update();
        }
        
        BeginDrawing();
        ClearBackground(grey);
        
        switch (currentScreen)
        {
            case Inicial:
            {   
                
                inicialscreen.Draw();
             
            }break;
            case Gameplay:
            {
                game.Draw();
    
                
            }break;
            default: break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}