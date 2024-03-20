#include <iostream>
#include <array>
#include <vector>
#include <raylib-cpp.hpp>
#include <raymath.hpp>
#include <rlgl.h>
#include <Helper.h>
#include <cmath>
#define WIDTH 1280
#define HEIGHT 720





class Bullet{
    raylib::Rectangle rectangle;
    raylib::Vector2 direction;
    raylib::Vector2 spawnPosition;
    public:
    Bullet(raylib::Vector2 origin, raylib::Vector2 target) {
        
        direction = target - origin;
        float distance = std::sqrt((target.GetX() - origin.GetX()) * (target.GetX() - origin.GetX()) + (target.GetY() - origin.GetY()) * (target.GetY() - origin.GetY()));
        direction *= 1.0f/distance;
        spawnPosition = origin + direction * 10;
        rectangle = raylib::Rectangle(spawnPosition, raylib::Vector2(10, 10));
    }
    void Fly() {
        raylib::Vector2 position = rectangle.GetPosition();
        position += direction * 5;
        rectangle.SetPosition(position);
        rectangle.Draw(Color{0,0,0, 250});

    }


};


class Gun {
    std::vector<Bullet> bullets;

    public:
        Gun() {}
        void handleShooting(raylib::Vector2 origin) {
            if(IsMouseButtonPressed(0)){
               bullets.push_back(Bullet(origin, raylib::Vector2(GetMouseX(), GetMouseY())));
            }
        }
};


class Wall {
    raylib::Vector2 position;
    float width, height;
    raylib::Rectangle rectangle;
    
    public:
        raylib::Vector2 GetPosition() {return position;}
        Wall(float w, float h , raylib::Vector2 pos) {
           width = w, height = h, position = pos; 
           rectangle = Rectangle{pos.x, pos.y, w, h};
           
        
        }
        raylib::Rectangle GetRectangle() { return rectangle;}

        void draw() {
            rectangle.Draw({0, 0}, 0, Color{180, 0, 0, 200});
            
            
        }


};
//ENEMY: --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Enemy {
    raylib::Vector2 position;
    raylib::Rectangle rectangle;
    raylib::Vector2 direction;
    raylib::Vector2 target;
    raylib::Rectangle up;
    raylib::Rectangle down;
    raylib::Rectangle left;
    raylib::Rectangle right; // "sensors" - help check collisions with walls
    std::vector<bool> hasCollided;
    private:
        void CalculateAndNormalizeDirection(){        
            direction = target - position;
            float distance = std::sqrt((target.GetX() - position.GetX()) * (target.GetX() - position.GetX()) + (target.GetY() - position.GetY()) * (target.GetY() - position.GetY()));
            direction *= 1.0f/distance;

            if((direction.GetY() < 0 && hasCollided[0]) || (direction.GetY() > 0 && hasCollided[1])) direction.SetY(0);
            if((direction.GetX() < 0 && hasCollided[2]) || (direction.GetX() > 0 && hasCollided[3])) direction.SetX(0);
            
        }
    public:
        Enemy() {}
        Enemy(float x, float y) {
            rectangle = raylib::Rectangle(x, y, 20, 20);
            position = raylib::Vector2(x, y);
            up = raylib::Rectangle{rectangle.GetX(), rectangle.GetY() - 2, 20, 1};
            down = raylib::Rectangle{rectangle.GetX(), rectangle.GetY() + rectangle.GetHeight() + 1, 20, 1};
            left = raylib::Rectangle{rectangle.GetX() - 2, rectangle.GetY(), 1, 20};
            right = raylib::Rectangle{rectangle.GetX() + rectangle.GetWidth() + 1, rectangle.GetHeight(), 1, 20};
        }
        raylib::Vector2 GetPosition() {return position;}
        raylib::Vector2 GetDirection() {return direction;}
        raylib::Rectangle GetRectangle() {return rectangle;}
        void SetPosition(float x, float y) {position = raylib::Vector2(x, y);}
        void SetPosition(raylib::Vector2 vec) {position = vec;}
        void SetTarget(raylib::Vector2 t) {target = t;}
        void SetTarget(float x, float y) {target = raylib::Vector2(x, y);}
        void SetDirection(float x, float y) {direction = raylib::Vector2(x, y);}
        void SetDirection(raylib::Vector2 dir) {direction = dir;}
        void InitializeCollision(){ hasCollided = {false, false, false, false};}
        void SetCollision(raylib::Rectangle rec) {
            hasCollided[0] = hasCollided[0] || up.CheckCollision(rec); 
            hasCollided[1] = hasCollided[1] || down.CheckCollision(rec); 
            hasCollided[2] = hasCollided[2] || left.CheckCollision(rec); 
            hasCollided[3] = hasCollided[3] || right.CheckCollision(rec); 
        }
        void HandleMovement(raylib::Vector2 t) {
            SetTarget(t);
            CalculateAndNormalizeDirection();
            position += direction * 1.5f;
            rectangle.SetPosition(position);
            up.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, -2.5f));
            down.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, 21.5f));
            left.SetPosition(rectangle.GetPosition() + raylib::Vector2(-2, 0));
            right.SetPosition(rectangle.GetPosition() + raylib::Vector2(21, 0));
            rectangle.Draw({0, 0}, 0, RED);
        }
};
// PLAYER: ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Player {

    raylib::Vector2 position;
    raylib::Rectangle rectangle;
    raylib::Rectangle up;
    raylib::Rectangle down;
    raylib::Rectangle left;
    raylib::Rectangle right; // "sensors" - help check collisions with walls
    std::vector<bool> hasCollided;
    public:
        Player() {
            position = raylib::Vector2{0, 0};
            rectangle = raylib::Rectangle{WIDTH/2, HEIGHT/2, 20, 20};
            up = raylib::Rectangle{rectangle.GetX(), rectangle.GetY() - 2, 20, 1};
            down = raylib::Rectangle{rectangle.GetX(), rectangle.GetY() + rectangle.GetHeight() + 1, 20, 1};
            left = raylib::Rectangle{rectangle.GetX() - 2, rectangle.GetY(), 1, 20};
            right = raylib::Rectangle{rectangle.GetX() + rectangle.GetWidth() + 1, rectangle.GetHeight(), 1, 20};
            hasCollided = {false, false, false, false};
        }
        raylib::Vector2 GetPosition() {return position;}
        void SetPosition(float x, float y) {position.x = x, position.y = y;}
        void SetPosition(raylib::Vector2 vec) {position = vec;}
        void InitializeCollision() {hasCollided = {false, false, false, false};}
        void SetCollision(raylib::Rectangle rec) {
            hasCollided[0] = hasCollided[0] || rec.CheckCollision(up);
            hasCollided[1] = hasCollided[1] || rec.CheckCollision(down);
            hasCollided[2] = hasCollided[2] || rec.CheckCollision(left);
            hasCollided[3] = hasCollided[3] || rec.CheckCollision(right);
        }
        raylib::Rectangle GetRectangle() {return rectangle;}
        void SetRectangle(raylib::Rectangle newRectangle) {rectangle = newRectangle;}
        void handleMovement() {
            float offsetX = 0, offsetY = 0;
            if((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && !hasCollided[0]) offsetY -= 0.5f;
            if((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && !hasCollided[1]) offsetY += 0.5f;
            if((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && !hasCollided[2]) offsetX -= 0.5f;
            if((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && !hasCollided[3]) offsetX += 0.5f;
            raylib::Vector2 offset{offsetX, offsetY};
            
            SetPosition(rectangle.GetPosition());
            up.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, -2.5f));
            down.SetPosition(rectangle.GetPosition() + raylib::Vector2(0, 21.5f));
            left.SetPosition(rectangle.GetPosition() + raylib::Vector2(-2, 0));
            right.SetPosition(rectangle.GetPosition() + raylib::Vector2(21, 0));
            if(offsetX && offsetY) offset *= 0.8f;
            offset *= 3;
            position += offset;
            rectangle.SetPosition(position);
            rectangle.Draw({0,0}, 0, GREEN); 
        }
};


class Game{
    
    protected:
        raylib::Vector2 startPosition{};
        std::vector<Wall> walls;
        //std::vector<Enemy> enemies;
        Enemy enemy;
        Player player;
        Gun gun;
    public:
        Game() {
            walls.push_back(Wall(20, 400, raylib::Vector2(120, 140)));
            walls.push_back(Wall(320, 20, raylib::Vector2(160, 560)));
            walls.push_back(Wall(20, 260, raylib::Vector2(580, 220)));
            walls.push_back(Wall(20, 320, raylib::Vector2(820, 80)));
            walls.push_back(Wall(360, 20, raylib::Vector2(320, 120)));
            walls.push_back(Wall(240, 40, raylib::Vector2(880, 540)));
            walls.push_back(Wall(60, 60, raylib::Vector2(280, 300)));
            walls.push_back(Wall(160, 20, raylib::Vector2(1020, 320)));
            player = Player();
            enemy = Enemy(WIDTH -100, HEIGHT - 60);
            gun = Gun();
        }
        void run() { // the "main" function of the program
            raylib::Window window(1280, 720, "SuperSquares");
            SetTargetFPS(90);
            
            while(!window.ShouldClose()){
                BeginDrawing();
                ClearBackground(Color{170, 230, 255, 200});
                gun.handleShooting(player.GetPosition());
                raylib::DrawText("a", 50, 50, 20, RED);
                player.InitializeCollision();
                enemy.InitializeCollision();
                for(int i = 0; i < (int)walls.size(); i++) {
                    player.SetCollision(walls[i].GetRectangle()); 
                    enemy.SetCollision(walls[i].GetRectangle());
                }
                for(int i = 0; i < (int)walls.size(); i++) {
                    walls[i].draw();
                }
                player.handleMovement();
                enemy.HandleMovement(player.GetPosition());
                
                EndDrawing();
            }
            return;
        }
};

int main() {
    Game game;
    game.run();
    return 0;
}
