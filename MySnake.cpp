#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
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
        Fruit(Vector2 position = (Vector2){0,0}, Vector2 size = (Vector2){0,0}, Color color = BLUE){
            this->setPosition(position);
            this->setSize(size);
            this->setColor(color);
        }
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

void drawGame(int screenHeight, int screenWidth);

int RandomNumber(int l, int h);

void unloadGame();

Vector4 normalizeColor(int r, int g, int b);

static Snake snake[MAXSNAKELENGTH] = {};
static Vector3 followerBuffer[MAXSNAKELENGTH] = {};
static Fruit fruit;
static bool gameOver = false;
static bool gamePaused = false;
static int InputBuffer = -1;
static int ACTUALSIZE = 1;
static Font fonts[10] = {};
static int next = -1;

int main(){
    InitWindow(0, 0, "Game");

    //Loading textures (doit être load après l'initialisation de la fenêtre)
    fonts[0] = LoadFont("resources/fonts/setback.png");

    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    initGame(screenHeight, screenWidth);
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        update(screenHeight, screenWidth);
    }
    unloadGame();
    CloseWindow();
}

Vector4 normalizeColor(int r, int g, int b){
    float s = r + g + b;
    return (Vector4){r/s, g/s, b/s, 1};
}

int Ediv(int a, int b){
    int r = a%b;
    return (a-r) / b;
}

int RandomNumber(int l, int h){
    srand( time(NULL));

    int RandId = rand() % (h-l) + l;

    return RandId;
}

void initGame(int screenHeight, int screenWidth){
    ACTUALSIZE = 1;
    snake[0] = Snake((Vector2){0+SQUARESIZE*2,0+SQUARESIZE*2}, (Vector2){SQUARESIZE-1, SQUARESIZE-1}, (Vector2){0,0}, (Color)RED);
    snake[0].setSpeed((Vector2){Ediv(SQUARESIZE,10), 0});
    for(int i = 0; i < MAXSNAKELENGTH; i++){
        followerBuffer[i] = (Vector3){-1,-1,-1};
    }

    fruit = Fruit((Vector2){RandomNumber(2, Ediv(screenWidth, SQUARESIZE) - 2)*SQUARESIZE,RandomNumber(2, Ediv(screenHeight, SQUARESIZE)-2)*SQUARESIZE},(Vector2){SQUARESIZE-1, SQUARESIZE-1}, (Color)ColorFromNormalized((Vector4){0.11, 1,1,1}));
}

int update(int screenHeight, int screenWidth){
    updateGame(screenHeight, screenWidth);
    drawGame(screenHeight, screenWidth);
    return 0;
}

void updateGame(int screenHeight, int screenWidth){
    if (!gameOver && !gamePaused){
        int gridHeight = Ediv(screenHeight, SQUARESIZE);
        int gridWidth = Ediv(screenWidth, SQUARESIZE);
        bool canMove = false;
        if (next != -1){
            followerBuffer[1].x = next;
            followerBuffer[1].y = 1;
            next = -1;
        }
        if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_SPACE)){
            gamePaused = true;
        }
        if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT) || InputBuffer == 0){
            if (snake[0].getSpeed().x == 0){
                for (int i = 0; i < gridHeight; i++){
                    if (snake[0].getPosition().y == i*SQUARESIZE){
                        canMove = true;
                    }
                }
                if (canMove){
                    snake[0].setSpeed((Vector2){Ediv(SQUARESIZE,10), 0});
                    if (ACTUALSIZE > 1)next = 0;
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
                    if (ACTUALSIZE > 1)next = 1;
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
                    if (ACTUALSIZE > 1)next = 2;
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
                    if (ACTUALSIZE > 1)next = 3;
                    InputBuffer = -1;
                    canMove = false;
                }
                else{
                    InputBuffer = 3;
                }
            }
        }

        //Snake Collision with fruit
        if (snake[0].getPosition().x + SQUARESIZE > screenWidth - SQUARESIZE*2 || snake[0].getPosition().x < 0 + SQUARESIZE *2 || snake[0].getPosition().y + SQUARESIZE > screenHeight - SQUARESIZE*2 || snake[0].getPosition().y < 0 + SQUARESIZE*2) gameOver = true;
                if ((snake[0].getPosition().x == fruit.getPosition().x && snake[0].getPosition().y == fruit.getPosition().y) || (snake[0].getPosition().x+SQUARESIZE == fruit.getPosition().x && snake[0].getPosition().y == fruit.getPosition().y && snake[0].getSpeed().x > 0) || (snake[0].getPosition().x-SQUARESIZE == fruit.getPosition().x && snake[0].getPosition().y == fruit.getPosition().y && snake[0].getSpeed().x < 0) || (snake[0].getPosition().x == fruit.getPosition().x && snake[0].getPosition().y+SQUARESIZE == fruit.getPosition().y && snake[0].getSpeed().y > 0) || (snake[0].getPosition().x == fruit.getPosition().x && snake[0].getPosition().y-SQUARESIZE == fruit.getPosition().y && snake[0].getSpeed().y < 0)){


                    fruit.setPosition((Vector2){RandomNumber(2, Ediv(screenWidth, SQUARESIZE) - 2)*SQUARESIZE,RandomNumber(2, Ediv(screenHeight, SQUARESIZE)-2)*SQUARESIZE});
                    ACTUALSIZE++;
                    Snake oldSnake = snake[ACTUALSIZE-2];
                    if (oldSnake.getSpeed().x > 0){
                        snake[ACTUALSIZE-1] = Snake((Vector2){oldSnake.getPosition().x - SQUARESIZE, oldSnake.getPosition().y}, oldSnake.getSize(), oldSnake.getSpeed(), BLUE);
                    }
                    else if (oldSnake.getSpeed().x < 0){
                        snake[ACTUALSIZE-1] = Snake((Vector2){oldSnake.getPosition().x + SQUARESIZE, oldSnake.getPosition().y}, oldSnake.getSize(), oldSnake.getSpeed(), BLUE);
                    }
                    else if (oldSnake.getSpeed().y > 0){
                        snake[ACTUALSIZE-1] = Snake((Vector2){oldSnake.getPosition().x, oldSnake.getPosition().y - SQUARESIZE}, oldSnake.getSize(), oldSnake.getSpeed(), BLUE);
                    }
                    else if (oldSnake.getSpeed().y < 0){
                        snake[ACTUALSIZE-1] = Snake((Vector2){oldSnake.getPosition().x, oldSnake.getPosition().y + SQUARESIZE}, oldSnake.getSize(), oldSnake.getSpeed(), BLUE); 
                    }
                }
        

        for(int i = 0; i < ACTUALSIZE; i++){
            if (i != 0 && ACTUALSIZE > 1){//FollowerBehavior
                bool followerCanMove = false;
                if (followerBuffer[i].x == -1 && followerBuffer[i].z != -1){
                    followerBuffer[i].x = followerBuffer[i].z;
                    followerBuffer[i].z = -1;
                    followerBuffer[i].y = 0;
                }
                if (followerBuffer[i].x != -1){
                    if (followerBuffer[i].y == 0){
                        followerBuffer[i].y = 1;
                    }
                    else{
                        if (followerBuffer[i].x == 0){
                        if (snake[i].getSpeed().x == 0){
                        for (int j = 0; j < gridHeight; j++){
                            if (snake[i].getPosition().y == j*SQUARESIZE){
                                followerCanMove = true;
                            }
                        }
                        if (followerCanMove){
                            snake[i].setSpeed((Vector2){Ediv(SQUARESIZE,10), 0});
                            followerCanMove = false;
                            if (i != ACTUALSIZE-1){
                                if (followerBuffer[i+1].x == -1){
                                    followerBuffer[i+1].x = followerBuffer[i].x;
                                    followerBuffer[i+1].y = 0;
                                }else{
                                    followerBuffer[i+1].z = followerBuffer[i].x;
                                }
                            }
                            followerBuffer[i].x = -1;
                            followerBuffer[i].y = 0;
                            }
                        }
                    }
                    else if (followerBuffer[i].x == 1){
                        if (snake[i].getSpeed().x == 0){
                        for (int j = 0; j < gridHeight; j++){
                            if (snake[i].getPosition().y == j*SQUARESIZE){
                                followerCanMove = true;
                            }
                        }
                        if (followerCanMove){
                            snake[i].setSpeed((Vector2){-Ediv(SQUARESIZE,10), 0});
                            followerCanMove = false;
                            if (i != ACTUALSIZE-1){
                                if (followerBuffer[i+1].x == -1){
                                    followerBuffer[i+1].x = followerBuffer[i].x;
                                    followerBuffer[i+1].y = 0;
                                }else{
                                    followerBuffer[i+1].z = followerBuffer[i].x;
                                }
                            }
                            followerBuffer[i].x = -1;
                            followerBuffer[i].y = 0;
                            }
                        }
                    }
                    else if (followerBuffer[i].x == 2){
                        if (snake[i].getSpeed().y == 0){
                        for (int j = 0; j < gridWidth; j++){
                            if (snake[i].getPosition().x == j*SQUARESIZE){
                                followerCanMove = true;
                            }
                        }
                        if (followerCanMove){
                            snake[i].setSpeed((Vector2){0, -Ediv(SQUARESIZE,10)});
                            followerCanMove = false;
                            if (i != ACTUALSIZE-1){
                                if (followerBuffer[i+1].x == -1){
                                    followerBuffer[i+1].x = followerBuffer[i].x;
                                    followerBuffer[i+1].y = 0;
                                }else{
                                    followerBuffer[i+1].z = followerBuffer[i].x;
                                }
                            }
                            followerBuffer[i].x = -1;
                            followerBuffer[i].y = 0;
                            }
                        }
                    }
                    else if (followerBuffer[i].x == 3){
                        if (snake[i].getSpeed().y == 0){
                        for (int j = 0; j < gridWidth; j++){
                            if (snake[i].getPosition().x == j*SQUARESIZE){
                                followerCanMove = true;
                            }
                        }
                        if (followerCanMove){
                            snake[i].setSpeed((Vector2){0, Ediv(SQUARESIZE,10)});
                            if (i != ACTUALSIZE-1){
                                if (followerBuffer[i+1].x == -1){
                                    followerBuffer[i+1].x = followerBuffer[i].x;
                                    followerBuffer[i+1].y = 0;
                                }else{
                                    followerBuffer[i+1].z = followerBuffer[i].x;
                                }
                            }
                            followerBuffer[i].x = -1;
                            followerBuffer[i].y = 0;
                            followerCanMove = false;
                            }
                        }
                    }
                    }
                }
                if (i > 1){
                    //Collisions avec les followers
                    if (snake[0].getSpeed().x < 0){
                        if (snake[i].getPosition().x - snake[0].getPosition().x == 0 && snake[0].getPosition().y - snake[i].getPosition().y == 0){
                            gameOver = true;
                        }
                    }
                    else if (snake[0].getSpeed().x > 0){
                        if (snake[0].getPosition().x + SQUARESIZE == snake[i].getPosition().x && snake[0].getPosition().y == snake[i].getPosition().y){
                            std::cout << "Je sais pas pourquoi je teste ça ";
                            gameOver = true;
                        }
                    }
                    else if (snake[0].getSpeed().y < 0){
                        if (snake[0].getPosition().x == snake[i].getPosition().x && snake[0].getPosition().y - SQUARESIZE == snake[i].getPosition().y){
                            std::cout << "Je sais pas pourquoi je teste ça ";
                            gameOver = true;
                        }
                    }
                    else if (snake[0].getSpeed().y > 0){
                        if (snake[0].getPosition().x == snake[i].getPosition().x && snake[0].getPosition().y + SQUARESIZE == snake[i].getPosition().y){
                            std::cout << "Je sais pas pourquoi je teste ça ";
                            gameOver = true;
                        }
                    }
                }
            }
            Vector2 actualpos = snake[i].getPosition();
            Vector2 actualspeed =  snake[i].getSpeed();
            Vector2 NewPos = (Vector2){actualpos.x + actualspeed.x, actualpos.y + actualspeed.y};
            snake[i].setPosition(NewPos);
        }
    }
    else if(gamePaused && !gameOver){
        if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_SPACE)){
            gamePaused = false;
        }
    }
    else if (gameOver){
        if (IsKeyPressed(KEY_E)){
            initGame(screenHeight, screenWidth);
            gameOver = false;
        }
    }
}

void drawGame(int screenHeight, int screenWidth){
    int GridHeight = Ediv(screenHeight, SQUARESIZE) - 1;
    int GridWidth = Ediv(screenWidth, SQUARESIZE) - 1;
    DrawText(TextFormat("Yay %f", snake[2].getPosition().x - snake[0].getPosition().x), 100 - MeasureText("Yay", 30), 600 - MeasureText("Yay", 30), 30, WHITE);
    Vector2 offset;
    offset.x = SQUARESIZE * 2;
    offset.y = SQUARESIZE * 2;
    BeginDrawing();
    ClearBackground(ColorFromNormalized((Vector4){0.258, 0, 0}));
    if (!gameOver){
        for (int i = 2; i < GridHeight; i++){
            DrawLine(0 + offset.y, i*SQUARESIZE , screenWidth - offset.x, i*SQUARESIZE, WHITE);
        }
        for (int i = 2; i < GridWidth; i++){
                DrawLine(i*SQUARESIZE, 0 + offset.x, i*SQUARESIZE, screenHeight - offset.y , WHITE);
        }
        for (int i = 0; i < ACTUALSIZE; i++){
            DrawRectangleV(snake[i].getPosition(), snake[i].getSize(), snake[i].getColor());
        }
        DrawTextEx(fonts[0], TextFormat("Score : %d", ACTUALSIZE), (Vector2){0+SQUARESIZE,0 +SQUARESIZE} , 35, 5, WHITE);
        DrawRectangleV(fruit.getPosition(), fruit.getSize(), fruit.getColor());
        if (gamePaused){
            DrawRectangleV((Vector2){0,0}, (Vector2){screenWidth, screenHeight}, ColorFromNormalized((Vector4){0,0,0,0.5}));
            Vector2 textPlacement = (Vector2){screenWidth/2 - MeasureTextEx(fonts[0], "Game Paused", 40, 5).x, screenHeight/2 - MeasureTextEx(fonts[0], "Game Paused", 40, 5).y};
            DrawTextEx(fonts[0], "Game Paused", textPlacement, 80, 5, WHITE);
        }
    }
    else{
        DrawRectangleV((Vector2){0,0}, (Vector2){screenWidth, screenHeight}, ColorFromNormalized((Vector4){0,0,0,0.5}));
        Vector2 textPlacement = (Vector2){screenWidth/2 - MeasureTextEx(fonts[0], "Game Over", 40, 5).x, screenHeight/2 - MeasureTextEx(fonts[0], "Game Over", 80, 5).y};
        DrawTextEx(fonts[0], "Game Over", textPlacement, 80, 5, WHITE);
        textPlacement = (Vector2){screenWidth/2 - MeasureTextEx(fonts[0], "Press [ E ] to play again", 40, 5).x, screenHeight/2 + MeasureTextEx(fonts[0], "Press [ E ] to play again", 80, 5).y};
        DrawTextEx(fonts[0], "Press [ E ] to play again", textPlacement, 80, 5, WHITE);
    }
    DrawTextEx(fonts[0], "Press [ ESC ] to quit", (Vector2){screenWidth - 2*SQUARESIZE - MeasureText("Press [ ESC ] to quit", 35), 0 + SQUARESIZE}, 35, 5, WHITE);
    EndDrawing();
}

void unloadGame(){
    UnloadFont(fonts[0]);
}