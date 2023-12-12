#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "include/raylib.h"
#include "class/snake.cpp"
#include "class/fruit.cpp"

//Declaration of functions header
void update();

void initGame();

void updateGame();

void drawGame();

float randomNumber(int l, int h);

//Declaration of static variables
static const int MAXSNAKELENGTH = 500;
static const int SQUARESIZE = 40;

static Snake snake[MAXSNAKELENGTH] = {};
static Vector3 tailBuffer[MAXSNAKELENGTH] = {};
static Fruit fruit;
static bool gameOver = false;
static bool gamePaused = false;
static int InputBuffer = -1;
static int CURRENTSIZE = 1;
static int nextMove = -1;
static bool gameWin = false;
static int goalToWin = 0;
static int fontSize = 0;

static float screenHeight;
static float screenWidth;



int main(){
    InitWindow(0, 0, "Snake");

    srand( time(NULL));

    screenHeight = GetScreenHeight();
    screenWidth = GetScreenWidth();

    fontSize = screenWidth / 100;

    goalToWin = screenWidth/SQUARESIZE * screenHeight/SQUARESIZE / 10;
    goalToWin = goalToWin >= MAXSNAKELENGTH ? MAXSNAKELENGTH-1 : goalToWin;

    initGame();
    SetTargetFPS(60);
    
    //WindowShouldClose returns a boolean that states if the window should close (if we press esc for example)
    while (!WindowShouldClose()){
        update(); //Update is called each frame
    }
    CloseWindow();
}



float randomNumber(int l, int h){

    int RandId = rand() % (h-l) + l;

    return RandId;
}

void initGame(){
    CURRENTSIZE = 1;
    snake[0] = Snake((Vector2){0+SQUARESIZE*2,0+SQUARESIZE*2}, (Vector2){SQUARESIZE-1, SQUARESIZE-1}, (Vector2){0,0}, (Color)RED);
    snake[0].setSpeed((Vector2){SQUARESIZE/10, 0});

    //Reinitialization of tailbuffer
    for(int i = 0; i < MAXSNAKELENGTH; i++){
        tailBuffer[i] = (Vector3){-1,-1,-1};
    }

    Vector2 fruitPosition = (Vector2){randomNumber(2, screenWidth/SQUARESIZE - 2)*SQUARESIZE,
    randomNumber(2, screenHeight/SQUARESIZE -2)*SQUARESIZE};
    while (fruitPosition.x == snake[0].getPosition().x && fruitPosition.y == snake[0].getPosition().y){
        fruitPosition = (Vector2){randomNumber(2, screenWidth/SQUARESIZE - 2)*SQUARESIZE,
        randomNumber(2, screenHeight/SQUARESIZE -2)*SQUARESIZE};
    }
    fruit = Fruit(fruitPosition,(Vector2){SQUARESIZE-1, SQUARESIZE-1}, (Color)ColorFromNormalized((Vector4){0.11, 1,1,1}));
}

void update(){
    updateGame();
    drawGame();
}

void updateGame(){
    if (!gameOver && !gamePaused && !gameWin){
        int gridHeight = screenHeight/SQUARESIZE;
        int gridWidth = screenWidth/SQUARESIZE;
        bool canMove = false;
        if (nextMove != -1){
            tailBuffer[1].x = nextMove;
            tailBuffer[1].y = 1;
            nextMove = -1;
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
                    snake[0].setSpeed((Vector2){SQUARESIZE/10, 0});
                    if (CURRENTSIZE > 1)nextMove = 0;
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
                    snake[0].setSpeed((Vector2){-SQUARESIZE/10, 0});
                    if (CURRENTSIZE > 1)nextMove = 1;
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
                    snake[0].setSpeed((Vector2){0, -SQUARESIZE/10});
                    if (CURRENTSIZE > 1)nextMove = 2;
                    InputBuffer = -1;
                    canMove = false;
                }
                else{
                    InputBuffer = 2;
                }
            }
        }
        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN) || InputBuffer == 3){
             if (snake[0].getSpeed().y == 0){
                for (int i = 0; i < gridWidth; i++){
                    if (snake[0].getPosition().x == i*SQUARESIZE){
                        canMove = true;
                    }
                }
                if (canMove){
                    snake[0].setSpeed((Vector2){0, SQUARESIZE/10});
                    if (CURRENTSIZE > 1)nextMove = 3;
                    InputBuffer = -1;
                    canMove = false;
                }
                else{
                    InputBuffer = 3;
                }
            }
        }

        //Snake Collision with wall
        if (snake[0].getPosition().x + SQUARESIZE > screenWidth - SQUARESIZE*2 ||
            snake[0].getPosition().x < 0 + SQUARESIZE *2 ||
            snake[0].getPosition().y + SQUARESIZE > screenHeight - SQUARESIZE*2 ||
            snake[0].getPosition().y < 0 + SQUARESIZE*2) gameOver = true;

        //Snake Collision with fruit
        if ((snake[0].getPosition().x == fruit.getPosition().x && snake[0].getPosition().y == fruit.getPosition().y) ||
            (snake[0].getPosition().x+SQUARESIZE == fruit.getPosition().x && snake[0].getPosition().y == fruit.getPosition().y &&
            snake[0].getSpeed().x > 0) ||
            (snake[0].getPosition().x-SQUARESIZE == fruit.getPosition().x && snake[0].getPosition().y == fruit.getPosition().y &&
            snake[0].getSpeed().x < 0) ||
            (snake[0].getPosition().x == fruit.getPosition().x && snake[0].getPosition().y+SQUARESIZE == fruit.getPosition().y &&
            snake[0].getSpeed().y > 0) ||
            (snake[0].getPosition().x == fruit.getPosition().x && snake[0].getPosition().y-SQUARESIZE == fruit.getPosition().y &&
            snake[0].getSpeed().y < 0))
            {
                //Fruit respawn
                Vector2 fruitposition = (Vector2){randomNumber(2, screenWidth/SQUARESIZE - 2)*SQUARESIZE,
                randomNumber(2, screenHeight/SQUARESIZE -2)*SQUARESIZE};
                bool canSpawnFruit = true;
                do{
                    canSpawnFruit = true;
                    fruitposition = (Vector2){randomNumber(2, screenWidth/SQUARESIZE - 2)*SQUARESIZE,
                    randomNumber(2, screenHeight/ SQUARESIZE -2)*SQUARESIZE};
                    for (int i = 0; i < CURRENTSIZE; i++){
                        if (snake[i].getPosition().x == fruitposition.x && snake[i].getPosition().y == fruitposition.y){
                            canSpawnFruit = false;
                        }
                    }
                }while(canSpawnFruit == false);
                fruit.setPosition(fruitposition);
                CURRENTSIZE++;
                if (CURRENTSIZE >= goalToWin){
                    gameWin = true;
                }
                Snake oldSnake = snake[CURRENTSIZE-2];
                if (oldSnake.getSpeed().x > 0){
                    snake[CURRENTSIZE-1] = Snake((Vector2){oldSnake.getPosition().x - SQUARESIZE, oldSnake.getPosition().y},
                    oldSnake.getSize(), oldSnake.getSpeed(), BLUE);
                }
                else if (oldSnake.getSpeed().x < 0){
                    snake[CURRENTSIZE-1] = Snake((Vector2){oldSnake.getPosition().x + SQUARESIZE, oldSnake.getPosition().y},
                    oldSnake.getSize(), oldSnake.getSpeed(), BLUE);
                }
                else if (oldSnake.getSpeed().y > 0){
                    snake[CURRENTSIZE-1] = Snake((Vector2){oldSnake.getPosition().x, oldSnake.getPosition().y - SQUARESIZE},
                    oldSnake.getSize(), oldSnake.getSpeed(), BLUE);
                }
                else if (oldSnake.getSpeed().y < 0){
                    snake[CURRENTSIZE-1] = Snake((Vector2){oldSnake.getPosition().x, oldSnake.getPosition().y + SQUARESIZE},
                    oldSnake.getSize(), oldSnake.getSpeed(), BLUE); 
                }
            }
        

        for(int i = 0; i < CURRENTSIZE; i++){
            if (i != 0 && CURRENTSIZE > 1){
                //Tail Behavior
                bool tailCanMove = false;
                if (tailBuffer[i].x == -1 && tailBuffer[i].z != -1){
                    tailBuffer[i].x = tailBuffer[i].z;
                    tailBuffer[i].z = -1;
                    tailBuffer[i].y = 0;
                }
                if (tailBuffer[i].x != -1){
                    if (tailBuffer[i].y == 0){
                        tailBuffer[i].y = 1;
                    }
                    else{
                        if (tailBuffer[i].x == 0){
                        if (snake[i].getSpeed().x == 0){
                        for (int j = 0; j < gridHeight; j++){
                            if (snake[i].getPosition().y == j*SQUARESIZE){
                                tailCanMove = true;
                            }
                        }
                        if (tailCanMove){
                            snake[i].setSpeed((Vector2){SQUARESIZE/10, 0});
                            tailCanMove = false;
                            if (i != CURRENTSIZE-1){
                                if (tailBuffer[i+1].x == -1){
                                    tailBuffer[i+1].x = tailBuffer[i].x;
                                    tailBuffer[i+1].y = 0;
                                }else{
                                    tailBuffer[i+1].z = tailBuffer[i].x;
                                }
                            }
                            tailBuffer[i].x = -1;
                            tailBuffer[i].y = 0;
                            }
                        }
                    }
                    else if (tailBuffer[i].x == 1){
                        if (snake[i].getSpeed().x == 0){
                        for (int j = 0; j < gridHeight; j++){
                            if (snake[i].getPosition().y == j*SQUARESIZE){
                                tailCanMove = true;
                            }
                        }
                        if (tailCanMove){
                            snake[i].setSpeed((Vector2){-SQUARESIZE/10, 0});
                            tailCanMove = false;
                            if (i != CURRENTSIZE-1){
                                if (tailBuffer[i+1].x == -1){
                                    tailBuffer[i+1].x = tailBuffer[i].x;
                                    tailBuffer[i+1].y = 0;
                                }else{
                                    tailBuffer[i+1].z = tailBuffer[i].x;
                                }
                            }
                            tailBuffer[i].x = -1;
                            tailBuffer[i].y = 0;
                            }
                        }
                    }
                    else if (tailBuffer[i].x == 2){
                        if (snake[i].getSpeed().y == 0){
                        for (int j = 0; j < gridWidth; j++){
                            if (snake[i].getPosition().x == j*SQUARESIZE){
                                tailCanMove = true;
                            }
                        }
                        if (tailCanMove){
                            snake[i].setSpeed((Vector2){0, -SQUARESIZE/10});
                            tailCanMove = false;
                            if (i != CURRENTSIZE-1){
                                if (tailBuffer[i+1].x == -1){
                                    tailBuffer[i+1].x = tailBuffer[i].x;
                                    tailBuffer[i+1].y = 0;
                                }else{
                                    tailBuffer[i+1].z = tailBuffer[i].x;
                                }
                            }
                            tailBuffer[i].x = -1;
                            tailBuffer[i].y = 0;
                            }
                        }
                    }
                    else if (tailBuffer[i].x == 3){
                        if (snake[i].getSpeed().y == 0){
                        for (int j = 0; j < gridWidth; j++){
                            if (snake[i].getPosition().x == j*SQUARESIZE){
                                tailCanMove = true;
                            }
                        }
                        if (tailCanMove){
                            snake[i].setSpeed((Vector2){0, SQUARESIZE/10});
                            if (i != CURRENTSIZE-1){
                                if (tailBuffer[i+1].x == -1){
                                    tailBuffer[i+1].x = tailBuffer[i].x;
                                    tailBuffer[i+1].y = 0;
                                }else{
                                    tailBuffer[i+1].z = tailBuffer[i].x;
                                }
                            }
                            tailBuffer[i].x = -1;
                            tailBuffer[i].y = 0;
                            tailCanMove = false;
                            }
                        }
                    }
                    }
                }
                if (i > 1){
                    //Collisions with tail
                    if (snake[0].getPosition().x - snake[i].getPosition().x < SQUARESIZE &&
                        snake[0].getPosition().x - snake[i].getPosition().x >= 0 &&
                        snake[0].getPosition().y - snake[i].getPosition().y < SQUARESIZE &&
                        snake[0].getPosition().y - snake[i].getPosition().y >= 0){
                        gameOver = true;
                    }
                    if (snake[0].getSpeed().x > 0){
                        if (snake[0].getPosition().x - snake[i].getPosition().x + SQUARESIZE - 10 < 0 && 
                            snake[0].getPosition().x - snake[i].getPosition().x + SQUARESIZE - 10 > -10 &&
                            snake[i].getPosition().y - snake[0].getPosition().y < SQUARESIZE &&
                            snake[i].getPosition().y - snake[0].getPosition().y > 0){
                            gameOver = true;
                        }
                    }
                    else if (snake[0].getSpeed().y > 0){
                        if (snake[i].getPosition().x - snake[0].getPosition().x < SQUARESIZE && snake[i].getPosition().x - snake[0].getPosition().x > 0 && snake[i].getPosition().y - snake[0].getPosition().y - SQUARESIZE + 10 < 0 && snake[i].getPosition().y - SQUARESIZE - snake[0].getPosition().y + 10 > -10 ){
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
    else if (gameOver || gameWin){
        if (IsKeyPressed(KEY_E)){
            initGame();
            gameOver = false;
            gameWin = false;
        }
    }
}

void drawGame(){
    int GridHeight = screenHeight/SQUARESIZE - 1;
    int GridWidth = screenWidth/ SQUARESIZE - 1;
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
        for (int i = 0; i < CURRENTSIZE; i++){
            DrawRectangleV(snake[i].getPosition(), snake[i].getSize(), snake[i].getColor());
        }
        DrawText(TextFormat("Score : %d", CURRENTSIZE),0+SQUARESIZE,0 +SQUARESIZE , fontSize*2, WHITE);
        DrawText(TextFormat("Goal to win : %d", goalToWin), screenWidth/2 - fontSize*2*4, screenHeight- 2*SQUARESIZE, fontSize*2, WHITE);
        DrawRectangleV(fruit.getPosition(), fruit.getSize(), fruit.getColor());
        if (gamePaused){
            DrawRectangleV((Vector2){0,0}, (Vector2){screenWidth, screenHeight}, ColorFromNormalized((Vector4){0,0,0,0.5}));
            Vector2 textPlacement = (Vector2){screenWidth/2 - fontSize*2*6, screenHeight/2 - screenHeight/15};
            DrawText("Game Paused", textPlacement.x, textPlacement.y, fontSize*4, WHITE);
            textPlacement = (Vector2){screenWidth/2 - fontSize*13, screenHeight/2};
            DrawText("Press [ SPACE ] to unpause", textPlacement.x, textPlacement.y, fontSize*2, WHITE);
        }
    }

    else{
        DrawRectangleV((Vector2){0,0}, (Vector2){screenWidth, screenHeight}, ColorFromNormalized((Vector4){0,0,0,0.5}));
        Vector2 textPlacement = (Vector2){screenWidth/2 - fontSize*2*5, screenHeight/2 - screenHeight/15};
        DrawText( "Game Over", textPlacement.x, textPlacement.y, fontSize*4, WHITE);
        textPlacement = (Vector2){screenWidth/2 - fontSize*12, screenHeight/2};
        DrawText("Press [ E ] to play again", textPlacement.x, textPlacement.y, fontSize*2, WHITE);
    }

    if (gameWin){
        DrawRectangleV((Vector2){0,0}, (Vector2){screenWidth, screenHeight}, ColorFromNormalized((Vector4){0,0,0,0.5}));
        Vector2 textPlacement = (Vector2){screenWidth/2 - fontSize*2*4, screenHeight/2 - screenHeight/10};
        DrawText("Game Won", textPlacement.x, textPlacement.y, fontSize*4, WHITE);
        textPlacement = (Vector2){screenWidth/2 - fontSize*13, screenHeight/2 - screenHeight/50};
        DrawText("Press [ E ] to play again", textPlacement.x, textPlacement.y, fontSize*2, WHITE);
        textPlacement = (Vector2){screenWidth/2 - fontSize*30, screenHeight/2 + screenHeight/25};
        DrawText(TextFormat("Vous avez joué à ce snake jusqu'à avoir un score de %d ?", CURRENTSIZE), textPlacement.x, textPlacement.y, fontSize*2, WHITE);
        textPlacement = (Vector2){screenWidth/2 - fontSize*18, screenHeight/2  + screenHeight/10};
        DrawText("C'est dur, vous devez avoir du temps !", textPlacement.x, textPlacement.y, fontSize*2, WHITE);
    }

    DrawText("Press [ ESC ] to quit", screenWidth - 2*SQUARESIZE - fontSize*2*12, 0 + SQUARESIZE, fontSize*2, WHITE);
    EndDrawing();
}