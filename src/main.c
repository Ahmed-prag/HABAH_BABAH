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

    InitGame();

    Texture2D fieldTexture = LoadTexture("assets/textures/field.png"); //can use // or \\, windows accepts both, better /

    Texture2D playerTexture = LoadTexture("assets/textures/player1.png");
    float scale = 0.15f; // scale of player
    int width  = playerTexture.width *scale; //player width wrt scale
    int height = playerTexture.height *scale; //height

    // Player position
    float positionX=800, positionY=GND-(height);//*0.95);
    float vx=1; //player speed
    // vertical attributes
    float g=1.0f; //gravity
    float vy=0; //initial upward velcity
    bool jump = false;
    float jp= -19.0f;  // jump power

    while (!WindowShouldClose())
    {
        UpdateGame();
        if(IsKeyDown(KEY_LEFT)){ //move left
            positionX-=vx;
            vx+=0.1; //accelerate
            if(vx>6) vx=6.0;
        }
        else if(IsKeyDown(KEY_RIGHT)){ // move right
            positionX+=vx;
            vx+=0.1;  // accelerate
            if(vx>3) vx=3;
        } 
        else vx=1;  // reset speed

        // jump
        if (IsKeyPressed(KEY_UP) && !jump){
            vy=jp;
            jump=true;
        }
        if(jump ){
            positionY+=vy;
            vy+=g;
            if(positionY>GND-height){
                vy=0;
                jump=false;
                positionY=GND-height;
            }
        }

        // Keep in window for now
        if(positionX>=windowX-width) positionX=windowX-width;
        if(positionX<0) positionX=0;

        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexture(fieldTexture, 0, 0, WHITE);

        DrawGame(windowX, windowY);

        // player
          // 20% of original size

        Vector2 playerPos = { positionX, positionY };   // Position on field
        DrawTextureEx(playerTexture, playerPos, 0.0f, scale, WHITE);

        EndDrawing();
    }
    // Unload before closing
    UnloadTexture(fieldTexture);

    CloseGame();

    CloseWindow();

    return 0;
}
