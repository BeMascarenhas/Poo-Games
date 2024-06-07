#pragma once
#include <raylib.h>
#define MAX_INPUT_CHARS     10
class InicialScreen{
    public:
        InicialScreen();
        ~InicialScreen();
        void Draw();
        void nameinput();        
        bool flag;
        int letterCount;
        bool mouseOnText;
        int framesCounter;
        static char name[MAX_INPUT_CHARS + 1];
    private:
        Texture2D image;
        Vector2 position;
        Rectangle textBox;
};

