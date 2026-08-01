#include "raylib.h"
#include "game.h"


int main(void)
{
    int windowX = 1350;
    int windowY = 800;
    InitWindow(windowX, windowY, "HABAH_BABAH");

    SetTargetFPS(60);

    InitGame();

    Texture2D fieldTexture = LoadTexture("field.png");

    while (!WindowShouldClose())
    {
        UpdateGame();

        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexture(fieldTexture, 0, 0, WHITE);

        DrawGame(windowX, windowY);

        EndDrawing();
    }
    // Unload before closing
    UnloadTexture(fieldTexture);

    CloseGame();

    CloseWindow();

    return 0;
}