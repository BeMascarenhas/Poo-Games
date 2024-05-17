#include <raylib.h>

int main()
{
    
   InitWindow(800, 800, "Hello, Raylib!");
    SetTargetFPS(60);
    int x,y;
    x = 400;
    y = 400;
    
    while (!WindowShouldClose())
    {
       
        if (IsKeyDown(KEY_UP))
        {   
             y-=10;
            
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y+=10;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            x-=10;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            x+=10;
        }


        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(x, y, 50, RED);
        EndDrawing();
    }
    CloseWindow();

   
    return 0;
}