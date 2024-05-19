#include <raylib.h>
#include "spaceship.cpp"

int main()
{
    
   InitWindow(750, 700, "Hello, Raylib!");
    SetTargetFPS(60);
    spaceship spaceship;
    while (!WindowShouldClose()){


        BeginDrawing();
        ClearBackground(WHITE);
        spaceship.draw();
        EndDrawing();
    }
    CloseWindow();

   
    return 0;
}