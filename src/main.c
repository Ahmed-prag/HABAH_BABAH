#include "raylib.h"
#include "game.h"
#include <stdbool.h>


int main(void)
{
    int windowX = 1350;
    int windowY = 800;
    int GND=(0.90625*windowY);  // ground


    InitWindow(windowX, windowY, "HABAH_BABAH");

    SetTargetFPS(60);

    InitGame(windowX, windowY); // all initializations

    while (!WindowShouldClose())
    {
        UpdateGame(windowX, windowY); // all events

        BeginDrawing();

        ClearBackground(BLACK);

        DrawGame(windowX, windowY); // all drawings

        EndDrawing();
    }

    CloseGame(); // all unloadings

    CloseWindow();

    return 0;
}
