#include <iostream>
#include <array>
#include <vector>
#include <raylib-cpp.hpp>
#include <raymath.hpp>
#include <rlgl.h>
#include <Helper.h>
#include <cmath>
const int WIDTH = 1280;
const int HEIGHT = 720;


class Bullet{
    raylib::Rectangle rectangle;
    raylib::Vector2 direction;
    raylib::Vector2 spawnPosition;

public:
    Bullet(raylib::Vector2 origin, raylib::Vector2 target) : direction{target - origin}{   
        float distance = std::sqrt((target.GetX() - origin.GetX()) * (target.GetX() - origin.GetX()) +
                         (target.GetY() - origin.GetY()) * (target.GetY() - origin.GetY()));
        direction *= 1.0f / distance;
        spawnPosition = origin + direction * 25;
        rectangle = raylib::Rectangle(spawnPosition, raylib::Vector2(10, 10));
        
    }
    raylib::Rectangle GetRectangle() {return rectangle;}
    friend std::ostream& operator<<(std::ostream& os, const Bullet& p){
        os << "pew pew\n" << "Direction: x:" << p.direction.GetX() << "  y:" << p.direction.GetY();
        return os;
    }
    
    void Fly() {
        raylib::Vector2 position = rectangle.GetPosition();
        position += direction * 5;
        rectangle.SetPosition(position);
        rectangle.Draw({0, 0}, 0,Color{0, 0, 0, 250});
    }
};

class Gun{
    std::vector<Bullet> bullets;

public:
    Gun() {}
    std::vector<Bullet>& GetBullets() {return bullets;}
    friend std::ostream& operator<<(std::ostream& os, const Gun& p){
        os << "Gun goes brrr (" << p.bullets.size() << " bullets flying)\n"; 
        return os;
    }
    void handleShooting(raylib::Vector2 origin) {
        if (IsMouseButtonPressed(0)){
            bullets.push_back(Bullet(origin, raylib::Vector2(GetMouseX(), GetMouseY())));
        }
    }
};

class Wall{
    raylib::Vector2 position;

    raylib::Rectangle rectangle;

public:
    raylib::Vector2 GetPosition() { return position; }
    Wall(float w, float h, raylib::Vector2 pos) : position{pos}, rectangle{raylib::Rectangle{pos.x, pos.y, w, h}}{}
    friend std::ostream& operator<<(std::ostream& os, const Wall& p){
        os << "Position: x-> " << p.rectangle.GetX() << "y-> " << p.rectangle.GetY() << '\n';
        return os;
    }
    raylib::Rectangle GetRectangle() const { return rectangle; } 
    void draw(){
        rectangle.Draw({0, 0}, 0, Color{80, 0, 0, 230});
    }
};
// ENEMY: --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Enemy{
    raylib::Rectangle rectangle;
    raylib::Vector2 position;
    float speed;
    raylib::Vector2 direction;
    raylib::Vector2 target;
    raylib::Rectangle up;
    raylib::Rectangle down;
    raylib::Rectangle left;
    raylib::Rectangle right; // "sensors" - help check collisions with walls
    bool hasCollided[4];
    

private:
    void CalculateAndNormalizeDirection(){
        direction = target - position;
        float distance = std::sqrt((target.GetX() - position.GetX()) * (target.GetX() - position.GetX()) 
                         + (target.GetY() - position.GetY()) * (target.GetY() - position.GetY()));
        direction *= 1.0f / distance;
        if ((direction.GetY() < 0 && hasCollided[0]) || (direction.GetY() > 0 && hasCollided[1]))
            direction.SetY(0);
        if ((direction.GetX() < 0 && hasCollided[2]) || (direction.GetX() > 0 && hasCollided[3]))
            direction.SetX(0);
    }

public:
    Enemy() {}
    Enemy(float x, float y) : rectangle{raylib::Rectangle(x, y, 20, 20)}, 
    position{raylib::Vector2(x, y)},
    speed{1}
    {
        up = raylib::Rectangle{rectangle.GetX(), rectangle.GetY() - 2, 20, 1};
        down = raylib::Rectangle{rectangle.GetX(), rectangle.GetY() + rectangle.GetHeight() + 1, 20, 1};
        left = raylib::Rectangle{rectangle.GetX() - 2, rectangle.GetY(), 1, 20};
        right = raylib::Rectangle{rectangle.GetX() + rectangle.GetWidth() + 1, rectangle.GetHeight(), 1, 20};
    }
    friend std::ostream& operator<<(std::ostream& os, const Enemy& e) {
        os << "Position: x-> " << e.position.GetX() << " y-> " << e.position.GetY() << '\n';
        os << "Target: x-> " << e.target.GetX() << " y-> " << e.target.GetY() << '\n'; 
        return os;
    }
    raylib::Vector2 GetPosition() { return position; }
    raylib::Rectangle GetRectangle() { return rectangle; }
    void SetPosition(float x, float y) { position = raylib::Vector2(x, y); }
    void SetPosition(raylib::Vector2 vec) { position = vec; }
    void SetTarget(raylib::Vector2 t) { target = t; }
    void SetTarget(float x, float y) { target = raylib::Vector2(x, y); }
    void SetDirection(raylib::Vector2 dir) { direction = dir; }
    float GetSpeed(){return speed;}
    void SetSpeed(float val) {speed = val;}
    void InitializeCollision() { for(int i = 0; i < 4; i++) hasCollided[i] = false; }
    void SetCollision(const raylib::Rectangle &rec){
        hasCollided[0] = hasCollided[0] || up.CheckCollision(rec);
        hasCollided[1] = hasCollided[1] || down.CheckCollision(rec);
        hasCollided[2] = hasCollided[2] || left.CheckCollision(rec);
        hasCollided[3] = hasCollided[3] || right.CheckCollision(rec);
    }
    void HandleMovement(raylib::Vector2 t){
        SetTarget(t);
        CalculateAndNormalizeDirection();
        position += direction * speed;

        rectangle.SetPosition(position);
        up.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, -2.5f));
        down.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, 21.5f));
        left.SetPosition(rectangle.GetPosition() + raylib::Vector2(-2, 0));
        right.SetPosition(rectangle.GetPosition() + raylib::Vector2(21, 0));
        rectangle.Draw({0, 0}, 0, RED);
    }
};


// PLAYER: ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Player
{
    raylib::Vector2 position;
    raylib::Rectangle rectangle;
    raylib::Rectangle up;
    raylib::Rectangle down;
    raylib::Rectangle left;
    raylib::Rectangle right; // "sensors" - help check collisions with walls
    std::vector<bool> hasCollided;
    bool alive;

public:
    Player() : rectangle{raylib::Rectangle{WIDTH / 2, HEIGHT / 2, 20, 20}},
     hasCollided{{false, false, false, false}},
     alive{true}
     {    
        up = raylib::Rectangle{rectangle.GetX() + 1, rectangle.GetY() - 2, 18, 1};
        down = raylib::Rectangle{rectangle.GetX() + 1, rectangle.GetY() + rectangle.GetHeight() + 1, 18, 1};
        left = raylib::Rectangle{rectangle.GetX() - 2.2f, rectangle.GetY(), 1, 20};
        right = raylib::Rectangle{rectangle.GetX() + rectangle.GetWidth() + 1.2f, rectangle.GetHeight(), 1, 20}; 
        position = rectangle.GetPosition(); 
    }

    Player(const Player& other): position{other.position}, rectangle{other.rectangle}, 
    up{other.up}, down{other.down}, left{other.left}, right{other.right},
    hasCollided{other.hasCollided}, alive{other.alive}{
        std::cout << "Constr de copiere Player" << '\n';
    }
    ~Player() {
        std::cout << "Destructor Player" << '\n';
    }
    Player& operator=(const Player& other){
        position = other.position;
        rectangle = other.rectangle;
        up = other.up;
        down = other.down;
        left= other.left;
        right = other.right;
        hasCollided = other.hasCollided;
        alive = other.alive;
        return *this;
    }
    //operator <<:
    friend std::ostream& operator<<(std::ostream& os, const Player& p){
        os << "Position: x-> " << p.position.GetX() << "y-> " << p.position.GetY() << '\n';
        os << "Collisions:\n" << "up-> " << ((p.hasCollided[0]) ? "true\n" : "false\n");
        os << "down-> " << ((p.hasCollided[1]) ? "true\n" : "false\n");
        os << "left-> " << ((p.hasCollided[2]) ? "true\n" : "false\n");
        os << "right-> " << ((p.hasCollided[3]) ? "true\n" : "false\n");
        return os;
    }
    raylib::Vector2 GetPosition() { return position; }
    void SetPosition(float x, float y) { position.x = x, position.y = y; }
    void SetPosition(raylib::Vector2 vec) { position = vec; }
    void InitializeCollision() { hasCollided = {false, false, false, false}; }
    void SetCollision(raylib::Rectangle rec){
        hasCollided[0] = hasCollided[0] || rec.CheckCollision(up);
        hasCollided[1] = hasCollided[1] || rec.CheckCollision(down);
        hasCollided[2] = hasCollided[2] || rec.CheckCollision(left);
        hasCollided[3] = hasCollided[3] || rec.CheckCollision(right);
    }
    raylib::Rectangle GetRectangle() { return rectangle; }
    bool GetAlive() {return alive;}
    void SetAlive(bool val) {alive = val;}
    void handleMovement() {
        float offsetX = 0, offsetY = 0;
        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && !hasCollided[0])
            offsetY -= 0.5f;
        if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && !hasCollided[1])
            offsetY += 0.5f;
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && !hasCollided[2])
            offsetX -= 0.5f;
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && !hasCollided[3])
            offsetX += 0.5f;
        raylib::Vector2 offset{offsetX, offsetY};

        up.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, -2.5f));
        down.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, 21.5f));
        left.SetPosition(rectangle.GetPosition() + raylib::Vector2(-2, 0));
        right.SetPosition(rectangle.GetPosition() + raylib::Vector2(21, 0));
        if (offsetX && offsetY)
            offset *= 0.8f;
        offset *= 3;
        position += offset;
        rectangle.SetPosition(position);
        rectangle.Draw({0, 0}, 0, GREEN);
    }
};

class Statistics {
    int score;
    int highscore;

    public:
    Statistics() {
        score = 0;
        highscore = 0;
    }
    friend std::ostream& operator<<(std::ostream& os, const Statistics& st) {
        os << "Score: " << st.score << "\nHighscore: " << st.highscore << '\n';
        return os;
    }
    void AddScore() {score++;}
    void InitScore() {score = 0;}
    void UpdateHighscore() {highscore = std::max(highscore, score);}
    void draw(){
        raylib::DrawText("Kills: " + std::to_string(score), 10, 10, 30, GREEN);
        raylib::DrawText("Highscore: " + std::to_string(highscore), 10, 50, 15, GOLD);
    }
    int GetHighscore() {return highscore;}
};

class Game {

protected:
    //variables used in the gameplay:
    raylib::Vector2 startPosition{};
    std::vector<Wall> walls;
    Statistics statistics;
    Player player;
    Gun gun;
    Enemy enemy;
    std::vector<raylib::Vector2> spawnPoints;
    //variables used in the start menu:
    raylib::Rectangle startButton;
    bool started;

    //member functions:

public:
    Game() {
        walls.push_back(Wall(20, 360, raylib::Vector2(120, 150)));
        walls.push_back(Wall(320, 20, raylib::Vector2(180, 560)));
        walls.push_back(Wall(20, 260, raylib::Vector2(580, 220)));
        walls.push_back(Wall(20, 320, raylib::Vector2(820, 80)));
        walls.push_back(Wall(360, 20, raylib::Vector2(320, 120)));
        walls.push_back(Wall(240, 40, raylib::Vector2(880, 520)));
        walls.push_back(Wall(60, 60, raylib::Vector2(280, 300)));
        walls.push_back(Wall(160, 20, raylib::Vector2(1020, 320)));
        walls.push_back(Wall(20, 720, raylib::Vector2(0,0)));
        walls.push_back(Wall(20, 720, raylib::Vector2(WIDTH - 20, 0)));
        walls.push_back(Wall(1280, 20, raylib::Vector2(0,0)));
        walls.push_back(Wall(1280, 20, raylib::Vector2(0,HEIGHT - 20)));
        spawnPoints = {
            raylib::Vector2(80, 80),
            raylib::Vector2(WIDTH/2 + 70, 50),
            raylib::Vector2(WIDTH - 120, 100),
            raylib::Vector2(80, HEIGHT - 80),
            raylib::Vector2(WIDTH/2, HEIGHT - 80),
            raylib::Vector2(WIDTH - 80, HEIGHT - 100)
        };
        player = Player();
        enemy = Enemy(30, 30);
        gun = Gun();
        statistics = Statistics();
        startButton = raylib::Rectangle(580, 580, 110, 60);
        started = false;
    }
    void initGame() {
        player.SetAlive(true);
        enemy.SetPosition(spawnPoints[GetRandomValue(0, 5)]);
        player.SetPosition(WIDTH/2, HEIGHT/2);
        enemy.SetSpeed(1);
        statistics.InitScore();
    }
    void run() { // the "main" function of the program
            ClearBackground(Color{170, 230, 255, 200});
            gun.handleShooting(player.GetPosition() + raylib::Vector2(10, 10));
            
            if(player.GetRectangle().CheckCollision(enemy.GetRectangle())){
                player.SetAlive(false);
                statistics.UpdateHighscore();
            }
            player.InitializeCollision();
            enemy.InitializeCollision();
            for (int i = 0; i < (int)walls.size(); i++){
                player.SetCollision(walls[i].GetRectangle());
                enemy.SetCollision(walls[i].GetRectangle());
            }
            for (int i = 0; i < (int)walls.size(); i++){
                walls[i].draw();
            }
            for(int i = 0; i < (int)gun.GetBullets().size(); i++){
                gun.GetBullets()[i].Fly();
                bool erased = false;
                for(const auto &wall : walls) {
                    if(gun.GetBullets()[i].GetRectangle().CheckCollision(wall.GetRectangle())) gun.GetBullets().erase(gun.GetBullets().begin() + i), erased = true;
                }
                if(!erased)
                if(enemy.GetRectangle().CheckCollision(gun.GetBullets()[i].GetRectangle())) {
                    statistics.AddScore();
                    enemy.SetPosition(spawnPoints[GetRandomValue(0, 5)]);
                    gun.GetBullets().erase(gun.GetBullets().begin() + i);
                    enemy.SetSpeed(enemy.GetSpeed() + 0.1f);
                }
            }

            player.handleMovement();
            enemy.HandleMovement(player.GetPosition());
            
            statistics.draw();
        
    }
    void runStartWindow() {
        ClearBackground(Color{100, 5, 5, 150});
        raylib::DrawText("SuperSquares", 420, 150, 60, Color{50, 220, 60, 250});
        raylib::DrawText("Use WASD/arrows to move \n\nLeft click to shoot \n\nGood luck! :)", 300, 400, 20, Color{191, 255, 112, 250});
        startButton.Draw(GOLD);
        raylib::DrawText("START",  600, 600, 20, Color{251, 255, 143, 250});
        if(IsMouseButtonPressed(0) && startButton.CheckCollision(GetMousePosition())){
            started = true;
        }
    }

    void runLoserWindow() {
       
        ClearBackground(Color{130, 5, 5, 150});
        raylib::DrawText("You died!", 500, 150, 50, Color{50, 220, 60, 250});
        raylib::DrawText("Highscore: " + std::to_string(statistics.GetHighscore()), 350, 400, 30, Color{191, 255, 112, 250});
        startButton.Draw(GOLD);
        raylib::DrawText("RESTART",  590, 600, 18, Color{251, 255, 143, 250});
        if(IsMouseButtonPressed(0) && startButton.CheckCollision(GetMousePosition())){
            initGame();
        }
        
    }

    void main(){
        raylib::Window window(1280, 720, "SuperSquares");
        SetTargetFPS(120);
        while(!window.ShouldClose()){ 
            BeginDrawing();
            if(!started) runStartWindow();
            else if(started && player.GetAlive()) run();
            else runLoserWindow();
            EndDrawing();
        }
    }
};



int main()
{
    Game game;
    game.main();
    return 0;
}
