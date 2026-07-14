#include "raylib.h"
int main(){
    int window=800;
    InitWindow(window, window, "My Game");
    SetTargetFPS(60);
    // xtics du chatactere
    int charWidth=40, charHeight =60;
    int charX=window/2-charWidth/2;
    int charY=window -charHeight-20; // 20 pads au dessus du bas
    int charSpeed=6;
    Color green = {20, 160, 133, 255}; // coleur du arriere-plan
    while (!WindowShouldClose()) {
        // 1. gestion des evenement
        if (IsKeyDown(KEY_RIGHT)) charX+=charSpeed;
        else if (IsKeyDown(KEY_LEFT)) charX-=charSpeed;

        // garde charactere dans logiciel
        if (charX<0) charX = 0;
        if (charX>window-charWidth) charX=window-charWidth;

        // 2. Dessin
        BeginDrawing();
        ClearBackground(green);

        // Ligne du sol
        DrawLine(0, window-20, window, window-20, DARKGRAY);

        // rectangle duCharactere
        DrawRectangle(charX, charY, charWidth, charHeight, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}