#pragma once

#include <raylib.h>
#include "gameobject.hpp"
class Alien :public GameObject{
    public:
        Alien( int type, Vector2 position);
        virtual void Draw();//foi feito virtual para que as classes filhas possam sobrescrever a funcao, foi sobreescrito em boss e mysteryship
        void Update(int direction);
        int getType();
        static void UnloadImages();// foi feito como static para que eu nao precisa criar um objeto para chamar a funcao, uso isso no unload do jogo
        Rectangle getRect();
        static Texture2D alienImages[5];// foi feito como static para que possa ser compartilhado entre todos os objetos da classe e tambem inicializado somente uma vez.
        int type;

   

    private:
};

