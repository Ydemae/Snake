#include <iostream>
#include <string>
#include "include/raylib.h"

//Définition des constantes statiques
static const int MAXSNAKELENGTH = 500;
static const int SQUARESIZE = 40;
static int ACTUALSIZE = 1;

class Snake{
    private:
        Vector2 _position;
        Vector2 _size;
        Vector2 _speed;
        Color _color;
    public:
        Snake(Vector2 pos = (Vector2){0,0}, Vector2 size = (Vector2){0,0}, Vector2 speed = (Vector2){0,0}, Color color = (Color)RED){
            this->setPosition(pos);
            this->setSize(size);
            this->setSpeed(speed);
            this->setColor(color);
        };
        Vector2 getPosition(){
            return this->_position;
        };
        void setPosition(Vector2 val){
            this->_position = val;
        };
        Vector2 getSize(){
            return this->_size;
        };
        void setSize(Vector2 val){
            this->_size = val;
        };
        Vector2 getSpeed(){
            return this->_speed;
        };
        void setSpeed(Vector2 val){
            this->_speed = val;
        };
        Color getColor(){
            return this->_color;
        };
        void setColor(Color val){
            this->_color = val;
        };
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

int update(int screenHeight, int screenWidth);

int Ediv(int a, int b);

void initGame(int screenHeight, int screenWidth);

static Snake snake[MAXSNAKELENGTH] = {};
static Fruit fruit;
static int count = 0;


int main(){
    InitWindow(0, 0, "Game");
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    initGame(screenHeight, screenWidth);
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        update(screenHeight, screenWidth);
    }
}

int Ediv(int a, int b){
    int r = a%b;
    return (a-r) / b;
}

void initGame(int screenHeight, int screenWidth){
    snake[0] = Snake((Vector2){0+SQUARESIZE,0+SQUARESIZE}, (Vector2){SQUARESIZE, SQUARESIZE}, (Vector2){0,0}, (Color)RED);
}

int update(int screenHeight, int screenWidth){
    int GridHeight = Ediv(screenHeight, SQUARESIZE);
    int GridWidth = Ediv(screenWidth, SQUARESIZE);
    BeginDrawing();
    ClearBackground(ColorFromNormalized((Vector4){0.258, 0, 0}));
    int petitCompteurdeLignes = 0;
    for (int i = 0; i < GridHeight; i++){
        DrawLine(0, i*SQUARESIZE , screenWidth, i*SQUARESIZE, WHITE);
        petitCompteurdeLignes++;
    }
    for (int i = 0; i < GridWidth; i++){
            DrawLine(i*SQUARESIZE, 0, i*SQUARESIZE, screenHeight , WHITE);
            petitCompteurdeLignes++;
        }
    for (int i = 0; i < ACTUALSIZE; i++){
        DrawRectangleV(snake[i].getPosition(), snake[i].getSize(), snake[i].getColor());
    }
    EndDrawing();
    return 0;
}