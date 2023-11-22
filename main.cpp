#include <iostream>
#include <string>
#include "include/raylib.h"




int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    Font fonts[5] = {0};
    fonts[0] = LoadFont("resources/fonts/alagard.png");


    InitWindow(screenWidth, screenHeight, "Test");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextEx(fonts[0] , "Yay", (Vector2){100, 100} , fonts[0].baseSize, 0, BLACK);
        EndDrawing();
    }
    ////DrawText(TextFormat("Yay %d %d", count, petitCompteurdeLignes), 100 - MeasureText("Yay", 30), 100 - MeasureText("Yay", 30), 30, WHITE);

    return 0;
}