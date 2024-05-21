#pragma once
#include <raylib.h>

class InicialScreen{
    public:
        InicialScreen();
        ~InicialScreen();
        void Draw();
        bool flag;
    private:
        Texture2D image;
        Vector2 position;
};

