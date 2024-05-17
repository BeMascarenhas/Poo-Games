#include <raylib.h>

int main()
{
   InitWindow(800, 450, "Hello, Raylib!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, World!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();

   
    return 0;
}