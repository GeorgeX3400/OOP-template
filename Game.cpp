//
// Created by ASUS-ROG on 16.04.2024.
//

#include "Game.h"

Game::Game() {
    walls.push_back(new Wall(20, 360, raylib::Vector2(120, 150)));
    walls.push_back(new Wall(320, 20, raylib::Vector2(180, 560)));
    walls.push_back(new Wall(20, 260, raylib::Vector2(580, 220)));
    walls.push_back(new Wall(20, 320, raylib::Vector2(820, 80)));
    walls.push_back(new Wall(360, 20, raylib::Vector2(320, 120)));
    walls.push_back(new Wall(240, 40, raylib::Vector2(880, 520)));
    walls.push_back(new Wall(60, 60, raylib::Vector2(280, 300)));
    walls.push_back(new Wall(160, 20, raylib::Vector2(1020, 320)));
    //the next 4 are the margins of the map:
    walls.push_back(new Wall(20, 720, raylib::Vector2(0,0)));
    walls.push_back(new Wall(20, 720, raylib::Vector2(WIDTH - 20, 0)));
    walls.push_back(new Wall(1280, 20, raylib::Vector2(0,0)));
    walls.push_back(new Wall(1280, 20, raylib::Vector2(0,HEIGHT - 20)));
    spawnPoints = {
            raylib::Vector2(80, 80),
            raylib::Vector2(WIDTH/2 + 70, 50),
            raylib::Vector2(WIDTH - 120, 100),
            raylib::Vector2(80, HEIGHT - 80),
            raylib::Vector2(WIDTH/2, HEIGHT - 80),
            raylib::Vector2(WIDTH - 80, HEIGHT - 100)
    };
    coinSpawnPoints = {
            raylib::Vector2{200, 200},
            raylib::Vector2{100, 650},
            raylib::Vector2{780, 620},
            raylib::Vector2{1080, 200},

    };
    player = new Player;
    player->SetPosition(raylib::Vector2(WIDTH/2, HEIGHT/2));
    enemy = new Enemy();
    gun = Gun();
    coin = dynamic_cast<Coin*>(new Coin);
    coin->SetPosition(coinSpawnPoints[GetRandomValue(0, 3)]);
    startButton = raylib::Rectangle(580, 580, 110, 60);
    started = false;
    player->afisare(std::cout);
}


void Game::initGame() {
    player->SetAlive(true);
    enemy->SetPosition(spawnPoints[GetRandomValue(0, 5)]);
    player->SetPosition(raylib::Vector2(WIDTH/2, HEIGHT/2));
    coin->SetPosition(coinSpawnPoints[GetRandomValue(0, 3)]);
    enemy->SetSpeed(1);
    Statistics::InitScore();
}


// GAMEPLAY FUNCTION:
void Game::run() {
    ClearBackground(Color{10, 5, 5, 200});
    gun.handleShooting(player->GetPosition() + raylib::Vector2(10, 10));

    if(player->GetBody().CheckCollision(enemy->GetBody())){
        //if the enemy caught the player, he dies, and it's game over:
        player->SetAlive(false);
        Statistics::UpdateHighscore();
    }
    if(player->GetBody().CheckCollision(coin->GetBody())){
        // move the coin in another point of the map, and update the score:
        raylib::Vector2 otherPosition = coinSpawnPoints[GetRandomValue(0, 3)];
        while(otherPosition == coin->GetBody().GetPosition()) otherPosition = coinSpawnPoints[GetRandomValue(0, 3)];
        coin->SetPosition(otherPosition);
        Statistics::AddCoin();
    }
    //checking the collisions with the walls:
    player->InitializeCollision();
    enemy->InitializeCollision();
    enemy->SetTarget(player->GetPosition());
    for(auto & wall : walls){
        player->SetCollision(wall->GetBody());
        enemy->SetCollision(wall->GetBody());
    }
    for(auto & wall : walls){
        wall->Draw();
    }
    for(int i = 0; i < (int)gun.GetBullets().size(); i++){
        gun.GetBullets()[i].handleMovement();
        bool erased = false;
        for(const auto wall : walls) {
            if(gun.GetBullets()[i].GetBody().CheckCollision(wall->GetBody()))
                gun.GetBullets().erase(gun.GetBullets().begin() + i), erased = true;
        }
        if(!erased)
            if(enemy->GetBody().CheckCollision(gun.GetBullets()[i].GetBody())) {
                Statistics::AddKill();
                enemy->SetPosition(spawnPoints[GetRandomValue(0, 5)]);
                if(enemy->GetBody().GetX() < 0 || enemy->GetBody().GetY() < 0 ||
                enemy->GetBody().GetX() > (WIDTH - 20) || enemy->GetBody().GetY() > (HEIGHT - 20)) {
                    throw OutOfBoundsException("Enemy spawned out of the map.");
                }
                gun.GetBullets().erase(gun.GetBullets().begin() + i);
                enemy->SetSpeed(enemy->GetSpeed() + 0.1f);
            }
    }

    player->handleMovement();
    enemy->handleMovement();
    coin->Draw();
    Statistics::draw();

}

void Game::runStartWindow() {
    ClearBackground(Color{100, 5, 5, 150});
    raylib::DrawText("SuperSquares", 420, 150, 60, Color{50, 220, 60, 250});
    raylib::DrawText("Use WASD/arrows to move \n\nLeft click to shoot \n\nGood luck! :)", 300, 400, 20, Color{191, 255, 112, 250});
    startButton.Draw(GOLD);
    raylib::DrawText("START",  600, 600, 20, Color{251, 255, 143, 250});
    if(IsMouseButtonPressed(0) && startButton.CheckCollision(GetMousePosition())){
        started = true;
    }
}

void Game::runLoserWindow() {

    ClearBackground(Color{130, 5, 5, 150});
    raylib::DrawText("You died!", 500, 150, 50, Color{50, 220, 60, 250});
    raylib::DrawText("Highscore: " + std::to_string(Statistics::GetHighscore()), 350, 400, 30, Color{191, 255, 112, 250});
    startButton.Draw(GOLD);
    raylib::DrawText("RESTART",  590, 600, 18, Color{251, 255, 143, 250});
    if(IsMouseButtonPressed(0) && startButton.CheckCollision(GetMousePosition())){
        initGame();
    }

}

void Game::main() {
    raylib::Window window(1280, 720, "SuperSquares");
    SetTargetFPS(120);
    while(!started) {
        BeginDrawing();
        runStartWindow();
        EndDrawing();
    }
    while(!window.ShouldClose()){
        BeginDrawing();
        if( player->GetAlive()) run();
        else runLoserWindow();
        EndDrawing();
    }
}
