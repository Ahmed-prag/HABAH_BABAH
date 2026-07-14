#include "raylib.h"

int main() {
    int ballX = 400;
    int ballY = 400;
    int radius = 20;
    int windowX = 1350, windowY = 800;

    // Vitesse de la balle
    int dx = 5;
    int dy = 5;

    // Définition des marges et dimensions du terrain
    int fieldMarginX = 50;
    int fieldMarginY = 50;
    int fieldWidth = windowX - (fieldMarginX * 2);
    int fieldHeight = windowY - (fieldMarginY * 2);

    // Dimensions des cages (goals)
    int goalWidth = 30;
    int goalHeight = 180;
    int goalY = fieldMarginY + (fieldHeight / 2) - (goalHeight / 2);

    InitWindow(windowX, windowY, "Bouncing Ball - Terrain Complet");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Mise à jour de la position
        ballX += dx;
        ballY += dy;

        // Rebond sur les bords de la FENÊTRE
        if (ballX < radius || ballX > windowX - radius) {
            dx = -dx;   
        }
        if (ballY < radius || ballY > windowY - radius) {
            dy = -dy;   
        }

        // Dessin
        BeginDrawing();
        ClearBackground(DARKGREEN);

        // 1. Le grand rectangle du terrain
        DrawRectangleLines(fieldMarginX, fieldMarginY, fieldWidth, fieldHeight, WHITE);

        // 2. LA LIGNE MÉDIANE (coupe le terrain en deux)
        DrawLine(windowX / 2, fieldMarginY, windowX / 2, fieldMarginY + fieldHeight, WHITE);

        // 3. LE ROND CENTRAL (au milieu du terrain)
        DrawCircleLines(windowX / 2, windowY / 2, 80, WHITE);

        // 4. But Gauche et But Droit
        DrawRectangleLines(fieldMarginX - goalWidth, goalY, goalWidth, goalHeight, WHITE);
        DrawRectangleLines(fieldMarginX + fieldWidth, goalY, goalWidth, goalHeight, WHITE);

        // 5. La balle
        DrawCircle(ballX, ballY, radius, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}