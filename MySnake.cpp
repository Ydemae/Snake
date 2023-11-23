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

void updateGame(int screenHeight, int screenWidth);

int drawGame(int screenHeight, int screenWidth);

static Snake snake[MAXSNAKELENGTH] = {};
static Fruit fruit;
static bool gameOver = false;
static bool gamePaused = false;
static int InputBuffer = -1;


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
    snake[0] = Snake((Vector2){0+SQUARESIZE*2,0+SQUARESIZE*2}, (Vector2){SQUARESIZE, SQUARESIZE}, (Vector2){0,0}, (Color)RED);
    snake[0].setSpeed((Vector2){Ediv(SQUARESIZE,10), 0});
}

int update(int screenHeight, int screenWidth){
    updateGame(screenHeight, screenWidth);
    drawGame(screenHeight, screenWidth);
    return 0;
}

void updateGame(int screenHeight, int screenWidth){
    if (!gameOver){
        int gridHeight = Ediv(screenHeight, SQUARESIZE);
        int gridWidth = Ediv(screenWidth, SQUARESIZE);
        bool canMove = false;
        if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT) || InputBuffer == 0){
            if (snake[0].getSpeed().x == 0){
                for (int i = 0; i < gridHeight; i++){
                    if (snake[0].getPosition().y == i*SQUARESIZE){
                        canMove = true;
                    }
                }
                if (canMove){
                    snake[0].setSpeed((Vector2){Ediv(SQUARESIZE,10), 0});
                    InputBuffer = -1;
                    canMove = false;
                }
                else{
                    InputBuffer = 0;
                }
            }
        }
        if (IsKeyPressed(KEY_A) ||IsKeyPressed(KEY_LEFT) || InputBuffer == 1){
            if (snake[0].getSpeed().x == 0){
                for (int i = 0; i < gridHeight; i++){
                    if (snake[0].getPosition().y == i*SQUARESIZE){
                        canMove = true;
                    }
                }
                if (canMove){
                    snake[0].setSpeed((Vector2){-Ediv(SQUARESIZE,10), 0});
                    InputBuffer = -1;
                    canMove = false;
                }
                else{
                    InputBuffer = 1;
                }
            }
        }
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || InputBuffer == 2){
           if (snake[0].getSpeed().y == 0){
                for (int i = 0; i < gridWidth; i++){
                    if (snake[0].getPosition().x == i*SQUARESIZE){
                        canMove = true;
                    }
                }
                if (canMove){
                    snake[0].setSpeed((Vector2){0, -Ediv(SQUARESIZE,10)});
                    InputBuffer = -1;
                    canMove = false;
                }
                else{
                    InputBuffer = 2;
                }
            }
        }
        if (IsKeyPressed(KEY_S) ||IsKeyPressed(KEY_DOWN) || InputBuffer == 3){
             if (snake[0].getSpeed().y == 0){
                for (int i = 0; i < gridWidth; i++){
                    if (snake[0].getPosition().x == i*SQUARESIZE){
                        canMove = true;
                    }
                }
                if (canMove){
                    snake[0].setSpeed((Vector2){0, Ediv(SQUARESIZE,10)});
                    InputBuffer = -1;
                    canMove = false;
                }
                else{
                    InputBuffer = 3;
                }
            }
        }
        for(int i = 0; i < ACTUALSIZE; i++){
            Vector2 actualpos = snake[i].getPosition();
            Vector2 actualspeed =  snake[i].getSpeed();
            Vector2 NewPos = (Vector2){actualpos.x + actualspeed.x, actualpos.y + actualspeed.y};
            snake[i].setPosition(NewPos);
        }
    }
}

int drawGame(int screenHeight, int screenWidth){
    int GridHeight = Ediv(screenHeight, SQUARESIZE) - 1;
    int GridWidth = Ediv(screenWidth, SQUARESIZE) - 1;
    Vector2 offset;
    offset.x = SQUARESIZE * 2;
    offset.y = SQUARESIZE * 2;
    BeginDrawing();
    ClearBackground(ColorFromNormalized((Vector4){0.258, 0, 0}));
    for (int i = 2; i < GridHeight; i++){
        DrawLine(0 + offset.y, i*SQUARESIZE , screenWidth - offset.x, i*SQUARESIZE, WHITE);
    }
    for (int i = 2; i < GridWidth; i++){
            DrawLine(i*SQUARESIZE, 0 + offset.x, i*SQUARESIZE, screenHeight - offset.y , WHITE);
    }
    for (int i = 0; i < ACTUALSIZE; i++){
        DrawRectangleV(snake[i].getPosition(), snake[i].getSize(), snake[i].getColor());
    }
    //DrawText(TextFormat("Yay %d %d", offset.x, offset.y ), 100 - MeasureText("Yay", 30), 100 - MeasureText("Yay", 30), 30, WHITE);
    EndDrawing();
    return 0;
}