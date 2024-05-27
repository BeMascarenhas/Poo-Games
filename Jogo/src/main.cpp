#include <raylib.h>
#include "game.hpp"
#include "obstacle.hpp"
#include "inicialScreen.hpp"
#include <string>
typedef enum GameScreen { Inicial, Gameplay } GameScreen;
string FormatWithLeadingZeros(int number, int width)
{
    string numberText = to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = string(leadingZeros, '0') + numberText;
}
int main()
{
  
   InitWindow(800, 800, "Space Invaders para poo");
   InitAudioDevice();
   GameScreen currentScreen = Inicial;
   Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
   Texture2D spaceshipimage = LoadTexture("Graphics/Portugol.png");
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
                UpdateMusicStream(game.music);
                DrawRectangleRoundedLines({10, 10,780,780}, 0.18f,20,2, yellow);
                DrawLineEx({25,730},{775,730}, 3, yellow);
                if(game.running){
                    DrawTextEx(font, "Level 01", {570, 740}, 34, 2, yellow);
                }else{
                    DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
                }
                float x = 50.0;
                for(int i = 0; i< game.lives;i++){
                    DrawTextureV(spaceshipimage,{x,745}, WHITE);
                    x += 50;
                }
                DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
                string scoreText = FormatWithLeadingZeros(game.score, 6);
                DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);
                DrawTextEx(font, "HIGHSCORE", {570, 15}, 34, 2, yellow);
                string highscoreText = FormatWithLeadingZeros(game.highscore, 6);
                DrawTextEx(font, highscoreText.c_str(), {610, 40}, 34, 2, yellow);
                game.Draw();

    
                
            }break;
            default: break;
        }
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}