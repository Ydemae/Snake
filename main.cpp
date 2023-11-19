#include <iostream>
#include <string>
#include "include/raylib.h"




int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Test");
    SetTargetFPS(60);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Yay", 100, 100, 50, BLACK);
    EndDrawing();

    return 0;
}