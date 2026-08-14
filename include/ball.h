#ifndef BALL_H
#define BALL_H
#include "raylib.h"

typedef struct Ball{
    Texture2D txt;
    
    float scale;

    float radius;

    Vector2 pos;
    Vector2 next;

    float velX;
    float velY;

    float angle;
    float rot;

    float gravity;
    float bounce;
    float friction;
}Ball;

void InitBall(Ball *ball, int windowX, int windowY);

void UpdateBall(Ball *ball, int windowX, int windowY, float GND);

void DrawBall(Ball *ball);

#endif