#include "inicialScreen.hpp"
#include <iostream>
using namespace std;

char InicialScreen::name[MAX_INPUT_CHARS + 1] = { '\0' };

InicialScreen::InicialScreen() {
    flag = false;
    //image = LoadTexture("Graphics/startButton.png");
    
    letterCount = 0;
    textBox = { 800 / 2.0f - 100, 180, 225, 50 };
    box1 = { 800 / 2.0f - 100, 250, 225, 50 };
    box2 = { 800 / 2.0f - 100, 320, 225, 50 };
    mouseOnText = false;
    mouseOnBox1 = false;
    mouseOnBox2 = false;
    framesCounter = 0;
}

InicialScreen::~InicialScreen() {
    UnloadTexture(image);
}

void InicialScreen::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Write your name down here! ", 240, 140, 20, GRAY);

    // Draw text input box
    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

    if (mouseOnText) {
        if (letterCount < MAX_INPUT_CHARS) {
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        } else {
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
        }
    }

    // Draw additional boxes without text
    DrawRectangleRec(box1, RED);
    if (mouseOnBox1) DrawRectangleLines((int)box1.x, (int)box1.y, (int)box1.width, (int)box1.height, RED);
    else DrawRectangleLines((int)box1.x, (int)box1.y, (int)box1.width, (int)box1.height, DARKGRAY);
    DrawText("portugol", box1.x + 10, box1.y + 10, 20, BLACK);
    DrawRectangleRec(box2, BLUE);
    if (mouseOnBox2) DrawRectangleLines((int)box2.x, (int)box2.y, (int)box2.width, (int)box2.height, RED);
    else DrawRectangleLines((int)box2.x, (int)box2.y, (int)box2.width, (int)box2.height, DARKGRAY);
     DrawText("c++", box2.x + 10, box2.y + 10, 20, BLACK);

    
}

void InicialScreen::nameinput() {
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();

        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }

        framesCounter++;
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        framesCounter = 0;
    }
}

void InicialScreen::checkclick() {
    Vector2 mousePosition = GetMousePosition();

    // Check if mouse is over box1 or box2
    mouseOnBox1 = CheckCollisionPointRec(mousePosition, box1);
    mouseOnBox2 = CheckCollisionPointRec(mousePosition, box2);

    if (mouseOnBox1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Spaceship::image = LoadTexture("Graphics/Portugol.png");
        cout << "Box 1 clicked" << endl;
    }

    if (mouseOnBox2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Spaceship::image = LoadTexture("Graphics/c++.png");
        cout << "Box 2 clicked" << endl;
    }
}
