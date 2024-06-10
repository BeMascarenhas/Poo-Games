
#include "game.hpp"
#include<iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Game::Game()
{
    music = LoadMusicStream("Sounds/music.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();

}

Game::~Game()
{
   
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);

}

void Game::Update()
{
    if(running){
        if(boss.alive){
            boss.bossMove();
            for (auto& laser: spaceship.lasers)
            {
            laser.Update();
            }
            for (auto& laser: bossLasers)
            {
                laser.Update();
            }
            DeleteInactiveLasers();
            CheckCollisions();
            BossShootLaser();

        }else{
            UpdateMusicStream(music);
        
        double currentTime = GetTime();
        if(currentTime - timeLastSpawn > mysteryShipSpawnInterval)
        {
            if(GetRandomValue(0,1) == 0)
            {
                heart.Spawn();
            }else{
                mystery.Spawn();
            }
            timeLastSpawn = currentTime;
            mysteryShipSpawnInterval = GetRandomValue(7, 15);
        }


        for (auto& laser: spaceship.lasers)
        {
            laser.Update();
        }

        if (GetTime() - timeMysteryCollision >= 4.0) {
        spaceship.fireRate = 0.35; // Volte ao fireRate padrão após 2 segundos
        }
        MoveAliens();

        AlienShootlaser();

        for (auto& laser: alienlasers)
        {
            laser.Update();
        }

        DeleteInactiveLasers();
        mystery.Update();
        heart.Update();
        CheckCollisions();
    }
    }else{
        if(IsKeyDown(KEY_ENTER))
        {
           Reset();
           InitGame();
        }
    }
}
void Game::Draw()
{
    
    spaceship.Draw();

    for (auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }
    for (auto& obstacle: obstacles)
    {
        obstacle.Draw();
    }
    for ( auto& alien: aliens)
    {
        alien.Draw();
    }
    for(auto& laser: alienlasers)
    {
        laser.Draw();
    }
   
    mystery.Draw();
    heart.Draw();
    boss.Draw();
    for(auto& laser: bossLasers)
    {
        laser.Draw();
    }
    
    if(running == false)
    {
        spaceship.Reset();
        aliens.clear();
        alienlasers.clear();
        obstacles.clear();
        cout << *this << endl;
    }
    
}

void Game::HandleInput()
{
    if(running){
        if(IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft();
        }else if(IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE))
        {
            spaceship.FireLaser();
           
        }
    }

}
Game& Game::operator--() {
    --lives;
    return *this;
}
Game &Game::operator++()
{
    lives = 3;
    return *this;
}
void Game::CheckCollisions()
{
    for(auto& laser: spaceship.lasers)
    {
       auto it = aliens.begin();
         while(it != aliens.end())
         {
             
              
              if(CheckCollisionRecs(it->getRect(),laser.getRect()))
              {
                PlaySound(explosionSound);
                if(it-> type == 0){
                    score+=100;
                }else if(it->type == 1){
                    score+=200;
                }else if(it->type == 2){
                    score+=300;
                }else if(it->type == 3){
                    score+=400;
                }else if(it->type == 4){
                    score+=500;
                }
                //checkHighScore();
                it = aliens.erase(it);
                laser.active = false;
              }else
              {
                it++;
              }
              if(aliens.size() == 0)
              {
                  Spawnboss();
                  cout<<"mozilla foundation"<<endl;
              }
         }
         for(auto& obstacle: obstacles)
         {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->getRect(),laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }else
                {
                    it++;
                }
            }
         }
        
         if(CheckCollisionRecs(mystery.getRect(),laser.getRect()))
         {
             timeMysteryCollision = 0.0;
             mystery.alive = false;
             laser.active = false;
             spaceship.fireRate = 0.1;
             timeMysteryCollision = GetTime();
             //checkHighScore();
             PlaySound(explosionSound);
         }
         if(CheckCollisionRecs(heart.getRect(),laser.getRect()))
         {
             heart.alive = false;
             laser.active = false;
             if(lives < 3){
                ++(*this);
             }

             PlaySound(explosionSound);
         }
        
    }
    for(auto& laser: alienlasers)
    {
        if(CheckCollisionRecs(laser.getRect(),spaceship.getRect()))
        {
            laser.active = false;
          
            --(*this);
            if(lives == 0)
            {

                GameOver();
            }
        }
        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->getRect(),laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }else
                {
                    it++;
                }
            }
        }
    }
    for(auto& alien: aliens)
    {
        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin(); 
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->getRect(),alien.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                }else
                {
                    it++;
                }
            }
        }
        if(CheckCollisionRecs(alien.getRect(),spaceship.getRect()))
        {
           
            GameOver();
        }
    }
    if(boss.alive){
    for(auto& laser: bossLasers)
    {
        if(CheckCollisionRecs(laser.getRect(),spaceship.getRect()))
        {
            laser.active = false;
            
            --(*this);
            if(lives == 0)
            {
                GameOver();
            }
        }
        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it->getRect(),laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }else
                {
                    it++;
                }
            }
        }
    }
    if(CheckCollisionRecs(boss.getRect(),spaceship.getRect()))
    {
        cout<<"Boss hit"<<endl;
        //GameOver();
    }
    for(auto& laser: spaceship.lasers)
    {
        if(CheckCollisionRecs(laser.getRect(),boss.getRect()))
        {
            --boss;
            laser.active = false;
            if(boss.lives == 0)
            {
                boss.alive = false;
                score += 10000;
                checkHighScore();
                GameOver();
                bossLasers.clear();
            }
        }
    }
    }
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if(!it->active)
        {
            it = spaceship.lasers.erase(it);
        }else
        {
            it++;
        }
    }
    for(auto it = alienlasers.begin(); it != alienlasers.end();)
    {
        if(!it->active)
        {
            it = alienlasers.erase(it);
        }else
        {
            it++;
        }
    }
    if(boss.alive){
    for (auto it = bossLasers.begin(); it != bossLasers.end();)
    {
        if(!it->active)
        {
            it = bossLasers.erase(it);
        }else
        {
            it++;
        }
    }
    }
}

vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size()*3;
    float gap = (GetScreenWidth() - obstacleWidth * 4) / 5;

    for(int i= 0; i<4 ; i++){
        float offsetX = (i+1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() -200)}));
    }
    return obstacles;

}


vector<Alien> Game::CreateAliens()
{
    vector<Alien> aliens;
    for(int i = 0; i<5;i++){
        for(int j = 0; j<11; j++){
            int alienType;
            if(i == 0) {
                alienType = 0;
            } else if (i == 1) {
                alienType = 1;
            } else if (i == 2) {
                alienType = 2;
            }else if (i == 3) {
                alienType = 3;
            }else if (i == 4) {
                alienType = 4;
            }

            float x = 75 + j * 55;
            float y = 110 + i * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for(auto& alien: aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type].width > GetScreenWidth() - 25)
        {
            alienDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
        {
            alienDirection = 1;
            MoveDownAliens(4);
        }
        
        alien.Update(alienDirection);
    }
}



void Game::MoveDownAliens(int distance)
{
    for (auto& alien: aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootlaser()
{
    double curretnTime = GetTime();
    if(curretnTime - timeLastAlienShoot >= alienShootCooldown && !aliens.empty())
    {
   
        int randomIndex = GetRandomValue(0, aliens.size()-1);
        Alien& alien = aliens[randomIndex];
        alienlasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type].width/2, alien.position.y + alien.alienImages[alien.type].height}, 6));
        timeLastAlienShoot = GetTime();
    }
}

void Game::BossShootLaser()
{
     double curretnTime = GetTime();
    if(curretnTime - timeLastBossShoot >= bossShootCooldown && boss.alive)
    {
        bossLasers.push_back(Laser({boss.position.x + boss.bossImages[boss.type].width/2, boss.position.y + boss.bossImages[boss.type].height}, 6));
        timeLastBossShoot = GetTime();
    
    }

}


void Game::Spawnboss()
{
     spaceship.lasers.clear();
     obstacles.clear();
     obstacles = CreateObstacles();
     boss.position.x = 350;
     boss.position.y = 350;
     boss.alive = true;
     boss.lives = 1;
     alienlasers.clear();
}
ostream& operator<<(ostream& os, const Game& game) {
    int yPosition = 100;  // Posição inicial vertical para desenhar as pontuações
    DrawText("Game Over! High Scores:", 100, yPosition, 20, RED);
    yPosition += 30;  // Move para a próxima linha

    std::ifstream inputFile("highscores.txt");
    if (inputFile.is_open()) {
        std::vector<std::pair<std::string, int>> scores;
        std::string line;

        // Ler as linhas do arquivo e armazenar no vetor de pares
        while (std::getline(inputFile, line)) {
            size_t delimiterPos = line.find(":");
            if (delimiterPos != std::string::npos) {
                std::string name = line.substr(0, delimiterPos);
                std::string scoreStr = line.substr(delimiterPos + 1);

                try {
                    int score = std::stoi(scoreStr);
                    scores.push_back(std::make_pair(name, score));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid score format for line: " << line << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Score out of range for line: " << line << std::endl;
                }
            }
        }
        inputFile.close();

        // Ordenar o vetor em ordem decrescente de pontuação
        std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        // Desenhar as pontuações ordenadas na tela
        for (const auto& score : scores) {
            std::string displayText = score.first + ": " + std::to_string(score.second);
            DrawText(displayText.c_str(), 100, yPosition, 20, WHITE);
            yPosition += 30;  // Move para a próxima linha
        }
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return os;
}
void Game::GameOver()
{
    
    checkHighScore();
    running = false;
    
    
    
   
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienlasers.clear();
    obstacles.clear();
}

void Game::InitGame()
{
    Boss b = Boss(0,{300,350});
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    alienDirection = 1;
    timeLastAlienShoot =0;
    timeLastSpawn =0.0;
    timeLastBossShoot = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(7,15);
    ++(*this);//lives = 3;
    score = 0;
    //bosslives = 1;
    highscore = loadHighScore();
    running = true;
    boss.alive = false;
    
}



void Game::checkHighScore()
{   
    saveHighScores(score, InicialScreen::name);
    if (score > highscore) {
        highscore = score;
        saveHighScore(highscore, InicialScreen::name);
    }
}

void Game::saveHighScore(int highscore, const string& name)
{
    ofstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile << highscore << std::endl;
        highScoreFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
}

void Game::saveHighScores(int highscore, const string &name)
{
    ofstream highScoresFile("highscores.txt", ios::app);
    if (highScoresFile.is_open()) {
        highScoresFile << name << ": " << highscore << std::endl;
        highScoresFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
}



int Game::loadHighScore()
{
    ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        int score;
        if (highScoreFile >> score) {
            highScoreFile.close();
            return score;
        }
        highScoreFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
    return 0; // Retorna 0 se não conseguir ler o arquivo
}


