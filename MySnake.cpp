#include <iostream>
#include <string>
#include "include/raylib.h"

//Définition des constantes statiques
static const int MAXSNAKELENGTH = 500;
static const int SQUARESIZE = 40;

class Snake{
    private:
        Vector2 _position;
        Vector2 _size;
        Vector2 _speed;
        Color _color;
    public:
        Vector2 getPosition(){
            return this->_position;
        }
        void setPosition(Vector2 val){
            this->_position = val;
        }
        Vector2 getSize(){
            return this->_size;
        }
        void setSize(Vector2 val){
            this->_size = val;
        }
        Vector2 getSpeed(){
            return this->_speed;
        }
        void setSpeed(Vector2 val){
            this->_speed = val;
        }
        Color getColor(){
            return this->_color;
        }
        void setColor(Color val){
            this->_color = val;
        }
};

class Fruit{
    private:
        Vector2 _position;
        Vector2 _size;
        Color _color;
    public:
        Vector2 getPosition(){
            return this->_position;
        }
        void setPosition(Vector2 val){
            this->_position = val;
        }
        Vector2 getSize(){
            return this->_size;
        }
        void setSize(Vector2 val){
            this->_size = val;
        }
        Color getColor(){
            return this->_color;
        }
        void setColor(Color val){
            this->_color = val;
        }
};

static Snake snake[MAXSNAKELENGTH] = {};
static Fruit fruit;


int main(){
    InitWindow(0, 0, "Game");

    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    Vector2 basePos = {screenWidth/2, screenHeight/2};
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(ColorFromNormalized((Vector4){0.258, 0, 0}));
        basePos.y = basePos.y + screenHeight/100;
        DrawText("Yay", basePos.x - MeasureText("Yay", 30), basePos.y-10 - MeasureText("Yay", 30), 30, WHITE);
        EndDrawing();
    }
}