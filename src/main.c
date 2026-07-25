#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update


        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw

        EndDrawing();
    }

    CloseWindow();

    return 0;
}