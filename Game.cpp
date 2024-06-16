//
// Created by ASUS-ROG on 16.04.2024.
//

#include "Game.h"




Game::Game() {
    //w:20, h: 360, pos: raylib::Vector2(120, 150)
    walls.push_back(wallBuilder.width(20).height(360).x(120).y(150).build());
    std::cout << walls[0].GetBody().GetX() << " " << walls[0].GetBody().GetY();
    //w:320, h: 20, pos: raylib::Vector2(180, 560)
    walls.push_back(wallBuilder.width(320).height(20).x(180).y(560).build());
    //w:20, h: 260, pos: raylib::Vector2(580, 220)
    walls.push_back(wallBuilder.width(20).height(260).x(580).y(220).build());
    //w:20, h: 320, pos: raylib::Vector2(820, 80)
    walls.push_back(wallBuilder.width(20).height(320).x(820).y(80).build());
    //w:360, h: 20, pos: raylib::Vector2(320, 120)
    walls.push_back(wallBuilder.width(360).height(20).x(320).y(120).build());
    //w:240, h: 40, pos: raylib::Vector2(880, 520)
    walls.push_back(wallBuilder.width(240).height(40).x(880).y(520).build());
    //w:60, h: 60, pos: raylib::Vector2(280, 300)
    walls.push_back(wallBuilder.width(60).height(60).x(280).y(300).build());
    //w:160, h: 20, pos: raylib::Vector2(1020, 320)
    walls.push_back(wallBuilder.width(160).height(20).x(1020).y(320).build());
    //the next 4 are the margins of the map:
    //w:20, h: 720, pos: raylib::Vector2(0, 0)
    walls.push_back(wallBuilder.width(20).height(720).x(0).y(0).build());
    //w:20, h: 720, pos: raylib::Vector2(WIDTH - 20, 0)
    walls.push_back(wallBuilder.width(20).height(720).x(WIDTH - 20).build());
    //w:1280, h: 20, pos: raylib::Vector2(0, 0)
    walls.push_back(wallBuilder.width(1280).height(20).x(0).y(0).build());
    //w:1280, h: 20, pos: raylib::Vector2(0, HEIGHT - 20)
    walls.push_back(wallBuilder.width(1280).height(20).y(HEIGHT - 20).build());
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
    player = Player();
    player.SetPosition(raylib::Vector2(WIDTH/2, HEIGHT/2));
    enemy = Enemy();
    gun = Gun();
    coin = Coin();
    coin.SetPosition(coinSpawnPoints[GetRandomValue(0, 3)]);
    startButton = raylib::Rectangle(580, 580, 110, 60);
    started = false;
    player.afisare(std::cout);


}






void Game::initGame() {
    player.SetAlive(true);
    enemy.SetPosition(spawnPoints[GetRandomValue(0, 5)]);
    player.SetPosition(raylib::Vector2(WIDTH/2, HEIGHT/2));
    coin.SetPosition(coinSpawnPoints[GetRandomValue(0, 3)]);
    enemy.SetSpeed(1);
    Statistics::InitScore();
}


// GAMEPLAY FUNCTION:
void Game::run() {
    ClearBackground(Color{10, 5, 5, 200});
    gun.handleShooting(player.GetPosition() + raylib::Vector2(10, 10));

    if(player.GetBody().CheckCollision(enemy.GetBody())){
        //if the enemy caught the player, he dies, and it's game over:
        player.SetAlive(false);
        Statistics::UpdateHighscore();
    }
    if(player.GetBody().CheckCollision(coin.GetBody())){
        // move the coin in another point of the map, and update the score:
        Statistics::AddScore(coin.GetPointsOnCatch());
        raylib::Vector2 currentPosition = coin.GetBody().GetPosition();
        int choice = GetRandomValue(1, 50);
        if(choice % 10 == 0) coin = CoinFactory::goldenCoin();
        else if(choice % 4 == 0) coin = CoinFactory::silverCoin();
        else coin = CoinFactory::bronzeCoin();
        raylib::Vector2 otherPosition = coinSpawnPoints[GetRandomValue(0, 3)];
        while(otherPosition == currentPosition) otherPosition = coinSpawnPoints[GetRandomValue(0, 3)];
        coin.SetPosition(otherPosition);
        Statistics::AddCoin();
    }
    //checking the collisions with the walls:
    player.InitializeCollision();
    enemy.InitializeCollision();
    enemy.SetTarget(player.GetPosition());
    for(auto & wall : walls){
        player.SetCollision(wall.GetBody());
        enemy.SetCollision(wall.GetBody());
    }
    for(auto & wall : walls){
        wall.Draw();
    }
    for(int i = 0; i < (int)gun.GetBullets().size(); i++){
        gun.GetBullets()[i].handleMovement();
        bool erased = false;
        for(const auto& wall : walls) {
            if(gun.GetBullets()[i].GetBody().CheckCollision(wall.GetBody()))
                gun.GetBullets().erase(gun.GetBullets().begin() + i), erased = true;
        }
        if(!erased)
            if(enemy.GetBody().CheckCollision(gun.GetBullets()[i].GetBody())) {
                Statistics::AddKill();
                enemy.SetPosition(spawnPoints[GetRandomValue(0, 5)]);
                if(enemy.GetBody().GetX() < 0 || enemy.GetBody().GetY() < 0 ||
                enemy.GetBody().GetX() > (WIDTH - 20) || enemy.GetBody().GetY() > (HEIGHT - 20)) {
                    throw OutOfBoundsException("Enemy spawned out of the map.");
                }
                gun.GetBullets().erase(gun.GetBullets().begin() + i);
                enemy.SetSpeed(enemy.GetSpeed() + 0.1f);
            }
    }

    player.handleMovement();
    enemy.handleMovement();
    coin.Draw();
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
        if( player.GetAlive()) run();
        else runLoserWindow();
        EndDrawing();
    }
}
