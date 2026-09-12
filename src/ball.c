#include "ball.h"
#include<math.h>

void InitBall(Ball *ball, int windowX, int windowY)
{
    ball->txt=LoadTexture("assets/textures/ball.png");

    ball->scale=0.08f;

    ball->radius=ball->txt.width*ball->scale /2.0f;

    ball->pos.x=windowX/2.0f;
    ball->pos.y=windowY/6.0f;

    ball->velX=-14.50f;
    ball->velY=0.0f;

    ball->angle=360.0f /(2*PI*ball->radius)*0.45f;
    ball->rot =0.0f;

    ball->gravity=0.5f;
    ball->bounce=0.8f;
    ball->friction=0.985;
}

void UpdateBall(Ball *ball, int windowX, int windowY, float GND)
{
    ball->next.x = ball->pos.x + ball->velX;
    ball->next.y = ball->pos.y + ball->velY;

    // --- COLLISION BARRE TRANSVERSALE ET TOIT EN DEUX SIDES (DEUX CÔTÉS) ---
    float leftTLX = 0.0740741f * windowX;       // Poteau avant gauche (~100px)
    float rightTLX = windowX - leftTLX;         // Poteau avant droit (~1250px)
    float crossbarY = GND - 200.0f;             // Niveau du toit / barre transversale

    Vector2 leftPostPoint  = { leftTLX, crossbarY };
    Vector2 rightPostPoint = { rightTLX, crossbarY };

    // 1. COLLISION ANGLE POTEAU AVANT (Rebond sur un point)
    if (CheckCollisionPointCircle(leftPostPoint, ball->next, ball->radius))
    {
        ball->next.x = leftTLX + ball->radius;
        ball->velX = -ball->velX * ball->bounce;
        ball->velY = -ball->velY * ball->bounce;
    }
    else if (CheckCollisionPointCircle(rightPostPoint, ball->next, ball->radius))
    {
        ball->next.x = rightTLX - ball->radius;
        ball->velX = -ball->velX * ball->bounce;
        ball->velY = -ball->velY * ball->bounce;
    }

    // 2. TOIT SOLIDE EN DEUX SENS (CAGE GAUCHE)
    if (ball->next.x <= leftTLX)
    {
        // Arrive du HAUT (atterrit sur le toit)
        if (ball->pos.y <= crossbarY && ball->next.y + ball->radius >= crossbarY)
        {
            ball->next.y = crossbarY - ball->radius;
            ball->velY = -ball->velY * ball->bounce;
            ball->velX *= ball->friction;
            if (fabs(ball->velY) < 0.1f) ball->velY = 0.0f;
        }
        // Arrive du BAS (à l'intérieur de la cage, tape le plafond)
        else if (ball->pos.y >= crossbarY && ball->next.y - ball->radius <= crossbarY)
        {
            ball->next.y = crossbarY + ball->radius;
            ball->velY = -ball->velY * ball->bounce;
        }
    }

    // 3. TOIT SOLIDE EN DEUX SENS (CAGE DROITE)
    if (ball->next.x >= rightTLX)
    {
        // Arrive du HAUT (atterrit sur le toit)
        if (ball->pos.y <= crossbarY && ball->next.y + ball->radius >= crossbarY)
        {
            ball->next.y = crossbarY - ball->radius;
            ball->velY = -ball->velY * ball->bounce;
            ball->velX *= ball->friction;
            if (fabs(ball->velY) < 0.1f) ball->velY = 0.0f;
        }
        // Arrive du BAS (à l'intérieur de la cage, tape le plafond)
        else if (ball->pos.y >= crossbarY && ball->next.y - ball->radius <= crossbarY)
        {
            ball->next.y = crossbarY + ball->radius;
            ball->velY = -ball->velY * ball->bounce;
        }
    }

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

int CheckGoal(Ball *ball, int windowX, float GND)
{
    float leftTLX = 0.0740741f * windowX;       // Ligne de but gauche
    float rightTLX = windowX - leftTLX;         // Ligne de but droite
    float crossbarY = GND - 200.0f;             // Hauteur sous la barre

    if (ball->pos.y > crossbarY)
    {
        // Ballon entre complètement dans la cage gauche -> But Joueur 2
        if (ball->pos.x + ball->radius < leftTLX)
        {
            return 2;
        }
        // Ballon entre complètement dans la cage droite -> But Joueur 1
        if (ball->pos.x - ball->radius > rightTLX)
        {
            return 1;
        }
    }
    return 0;
}

void ResetBall(Ball *ball, int windowX, int windowY)
{
    ball->pos.x = windowX / 2.0f;
    ball->pos.y = windowY / 2.0f;
    ball->velX = 0.0f;
    ball->velY = 0.0f;
}