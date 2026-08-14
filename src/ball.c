#include "ball.h"
#include<math.h>

void InitBall(Ball *ball, int windowX, int windowY)
{
    ball->txt=LoadTexture("assets/textures/ball.png");

    ball->scale=0.08f;

    ball->radius=ball->txt.width*ball->scale /2.0f;

    ball->pos.x=windowX/2.0f;
    ball->pos.y=windowY/2.0f;

    ball->velX=0.0f;
    ball->velY=0.0f;

    ball->angle=360.0f /(2*PI*ball->radius)*0.45f;
    ball->rot =0.0f;

    ball->gravity=0.5f;
    ball->bounce=0.6f;
    ball->friction=0.985;
}

void UpdateBall(Ball *ball, int windowX, int windowY, float GND)
{
    ball->next.x = ball->pos.x + ball->velX;
    ball->next.y = ball->pos.y + ball->velY;

    /*ball->pos.x += ball->velX;
    ball->pos.y += ball->velY;*/
    // left and right walls
    if(ball->next.x < ball->radius)
    {
        ball->next.x = ball->radius;
        ball->velX = -ball->velX * ball->bounce;
    }
    if (ball->next.x > windowX- ball->radius)
    {
        ball->next.x = windowX- ball->radius;
        ball->velX = -ball->velX * ball->bounce;
    }

    // Ball has to fall
    if(ball->next.y <GND-ball->radius)
    {
        ball->velY+=ball->gravity;
    }
    else //Ball cant go lower than GND
    {
        ball->next.y = GND -ball->radius;
        ball->velY =-ball->velY*ball->bounce;
        // rolling frriction
        ball->velX *= ball->friction;
    }

    // confirm the update 
    //ball->pos = ball->next;
    // after collision with player is confirmed

    // Stop endless vibrations
    if(fabs(ball->velY)<0.05f) ball->velY=0.0f;
    if(fabs(ball->velX)<0.05f) ball->velX=0.0f;

    // Ball rotation
    ball->rot+=ball->velX*ball->angle;
    if(ball->rot >360.0f) ball->rot-=360.0f;
    else if(ball->rot<0.) ball->rot+=360.0f;
}

void DrawBall(Ball *ball){
    Rectangle src={0, 0, ball->txt.width, ball->txt.height};
    Rectangle dest={ball->pos.x, ball->pos.y, ball->txt.width*ball->scale, ball->txt.height*ball->scale};
    DrawTexturePro(ball->txt, src, dest, (Vector2){ball->radius, ball->radius}, ball->rot, WHITE);

}