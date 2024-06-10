#pragma once
#include <raylib.h>
#include "spaceship.hpp"
#define MAX_INPUT_CHARS     10
class InicialScreen{
    public:
        InicialScreen();
        ~InicialScreen();
        void Draw();
        void nameinput();  
        void checkclick();      
        bool flag;
        int letterCount;
        bool mouseOnText;
        int framesCounter;
        bool mouseOnBox1;
        bool mouseOnBox2;
        Rectangle box1;
        Rectangle box2;
        static char name[MAX_INPUT_CHARS + 1];//feito como static para que possa ser acessado por outras classes sem precisar criar um objeto, o seu uso foi feito em game.cpp.
    private:
        //feito como private para que nao seja acessado por outras classes e como forma de protecao da vairavel de posicao
        Texture2D image;
        Vector2 position;
        Rectangle textBox;
        
        
};

