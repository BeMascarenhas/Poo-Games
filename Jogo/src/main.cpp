#include <raylib.h>
#include "game.hpp"
#include "obstacle.hpp"
#include "inicialScreen.hpp"

typedef enum GameScreen { Inicial, Gameplay } GameScreen;
int main()
{
  
   InitWindow(800, 800, "Space Invaders para poo");
   GameScreen currentScreen = Inicial;
   SetTargetFPS(60);

    Color grey = {29,29,27,255};
    Color yellow = {243,216,63,255};
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
                DrawRectangleRoundedLines({10, 10,780,780}, 0.18f,20,2, yellow);
                game.Draw();

    
                
            }break;
            default: break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}