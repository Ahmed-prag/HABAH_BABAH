#include "raylib.h"
#include "game.h"
#include "field.h"
#include "player.h"
#include "ball.h"
#include "ball_player.h"
#include<math.h>

static Texture2D fieldTexture;

static float scale; //Scale

static float GND; //ground

static Player player1, player2;

static Ball ball;

void InitGame(int windowX, int windowY)
{
    scale = 0.0002 * windowY;  // Calculated wrt player pic and windowY

    GND=(0.90625*windowY);  // ground
    
    // Ball
    InitBall(&ball, windowX, windowY);

    //============Field Texture============//
    fieldTexture = LoadTexture("assets/textures/field.png");

    //================Player===============//
    player1.txt = LoadTexture("assets/textures/player1.png");
    player2.txt = LoadTexture("assets/textures/player2.png");

    player1.pos.x = 0.6f* windowX;
    player2.pos.x = 0.4f*windowX; //position in X

    // Other attributes
    InitPlayer(&player1, GND, scale);
    InitPlayer(&player2, GND, scale);
    
}

void UpdateGame(int windowX, int windowY)
{
    Rectangle P1R = player1.rect, P2R=player2.rect; //Player rectangle
    UpdateBall(&ball, windowX, windowY, GND);

    UpdatePlayer( &player1, KEY_LEFT, KEY_RIGHT, KEY_UP, windowX, GND, scale, P2R);
    
    UpdatePlayer( &player2, KEY_A, KEY_D, KEY_W, windowX, GND, scale, P1R);

    //Ball player collision.
    BallPlayerCollision(&ball, &player1);
    BallPlayerCollision(&ball, &player2);

    // Confirm here, the new ball pos.
    ball.pos = ball.next;
    
    //==========player facing===========//
    // Player 1
    if(ball.pos.x<player1.pos.x) player1.dir=false;
    else player1.dir=true;

    //Player 2
    if(ball.pos.x<player2.pos.x) player2.dir=false;
    else player2.dir=true;

}

void DrawGame(int windowX, int windowY)
{
    // Field decor
    DrawTexture(fieldTexture, 0, 0, WHITE);

    //field outline in fieldd.c
    DrawField(windowX, windowY); // comes after field decor

    // Ball
    DrawBall(&ball);

    //Players
    DrawPlayer(&player1, scale, player1.dir); // for now, true or fasle
    DrawPlayer(&player2, scale, player2.dir);
}

void CloseGame(void)
{
    UnloadTexture(fieldTexture);
    UnloadTexture(player1.txt);
    UnloadTexture(player2.txt);
    UnloadTexture(ball.txt);
}