#pragma once

#include <raylib.h>

class Alien {
    public:
        Alien( Vector2 position);
        void Draw();
        void Update(int direction);

        static void UnloadImages();
        static Texture2D alienImages[5];
        int type;
        Vector2 position;

    private:
};

class Alien1 : public Alien {
    public:
        Alien1(Vector2 position);
};

class Alien2 : public Alien {
    public:
        Alien2(Vector2 position);
};

class Alien3 : public Alien {
    public:
        Alien3(Vector2 position);
};
class Alien4 : public Alien {
    public:
        Alien4(Vector2 position);
};
class Alien5 : public Alien {
    public:
        Alien5(Vector2 position);
};