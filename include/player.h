#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "ball.h"

typedef struct Player
{
    Texture2D txt;

    Vector2 pos;
    Vector2 old;

    float orgX;
    float orgY;

    float velX;
    float velY;
    
    float scale;

    float g;
    float jp;

    bool jump;

    bool dir;

    Rectangle rect;

} Player;

void InitPlayer(Player *player, float GND, float scale);

void UpdatePlayer(Player *player, KeyboardKey left,
                  KeyboardKey right, KeyboardKey jump,
                  int windowX, float ground,
                  float scale, Rectangle otherRect
);

void DrawPlayer(Player *player, float scale, bool dir);

#endif