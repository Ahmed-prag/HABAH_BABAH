#include "raylib.h"
#include "game.h"
#include "field.h"
#include "player.h"

static Texture2D fieldTexture;

static float scale; //Scale

static float GND; //ground

static Player player1, player2;

void InitGame(int windowX, int windowY)
{
    scale = 0.0002 * windowY;  // Calculated wrt player pic and windowY

    GND=(0.90625*windowY);  // ground

    fieldTexture = LoadTexture("assets/textures/field.png");
    player1.txt = LoadTexture("assets/textures/player1.png");
    player2.txt = LoadTexture("assets/textures/player2.png");

    player1.x = 0.55f* windowX;
    player2.x = 0.40f*windowX; //position in X

    player1.y = GND - (player1.txt.height*scale); //Positions in Y
    player2.y = GND - (player2.txt.height*scale);

    player1.velX = 1;// Speeds
    player2.velX = 1;

    player1.velY = 0; // Upward speeds
    player2.velY = 0;

    player1.g = 1.0f; // Gravitys
    player2.g = 1.0f;

    player1.jump = false;
    player2.jump = false;

    player1.jp=-19.0f;
    player2.jp=-19.0f;
}

void UpdateGame(int windowX, int windowY)
{
    UpdatePlayer( &player1, KEY_LEFT, KEY_RIGHT, KEY_UP, windowX, GND, scale);
    
    UpdatePlayer( &player2, KEY_A, KEY_D, KEY_W, windowX, GND, scale);
}

void DrawGame(int windowX, int windowY)
{

    // Field decor
    DrawTexture(fieldTexture, 0, 0, WHITE);

    //field outline in fieldd.c
    DrawField(windowX, windowY); // comes after field decor

    DrawPlayer(&player1, scale, false); // for now, true or fasle
    DrawPlayer(&player2, scale, true);

}

void CloseGame(void)
{
    UnloadTexture(fieldTexture);
    UnloadTexture(player1.txt);
    UnloadTexture(player2.txt);
}