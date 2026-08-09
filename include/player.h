#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player
{
    Texture2D txt;

    float x;
    float y;

    float velX;
    float velY;
    
    float scale;

    float g;
    float jp;

    bool jump;

} Player;

void UpdatePlayer(Player *player, KeyboardKey left,
                  KeyboardKey right, KeyboardKey jump,
                  int windowX, float ground, float scale
);

void DrawPlayer(Player *player, float scale, bool dir);

#endif