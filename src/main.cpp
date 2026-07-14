#include "raylib.h"

int main() {
    int ballX = 400;
    int ballY = 400;
    int radius = 20;
    int windowX=1350, windowY=800;

    // velocity (speed in pixels per frame)
    int dx = 5;
    int dy = 5;

    //Color green = {20, 160, 133, 255};
    InitWindow(windowX, windowY, "Bouncing Ball");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // Update position
        ballX+=dx;
        ballY+=dy;
        // Bounce on edges
        if(ballX<radius ||ballX > windowX-radius) {
            dx=-dx;   // reverse horizontal direction
        }
        if(ballY<radius ||ballY > windowY-radius) {
            dy=-dy;   // reverse vertical direction
        }

        // Drawing
        BeginDrawing();
        ClearBackground(GREEN);
        DrawCircle(ballX, ballY, radius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
