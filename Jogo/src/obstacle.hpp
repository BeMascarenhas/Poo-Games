#pragma once
#include <vector>
#include "block.hpp"
#include "GameObject.hpp"

using namespace std;

class Obstacle:public GameObject{
    public:
        Obstacle(Vector2 position);
        void Draw();
        Vector2 position;
     
        vector<Block> blocks;
        static vector<vector<int>> grid;// o grid precisa ser static para ser acessado sem precisar estanciar um objeto da classe e para nao ser ciado toda vez que um objeto da classe for criado
    private:
};