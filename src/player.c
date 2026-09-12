#include "player.h"
#include<math.h>

void InitPlayer(Player *player, float GND, float scale)
{

    player->orgX=player->txt.width*scale /2;
    
    player->orgY=player->txt.height*scale /2;


    player->pos.y = GND - (player->orgY); //Positions in Y

    player->velX = 0.0f;// Speed

    player->velY = 0.0f; // Upward speed

    player->g = 1.0f; // Gravity

    player->jump = false;

    player->dir=false;

    player->jp=-19.0f;

}
void UpdatePlayer(Player *player, KeyboardKey left,
                  KeyboardKey right, KeyboardKey jump,
                  int windowX, float ground, float scale,
                  Rectangle otherRect)   // <-- new parameter
{
    player->old = player->pos;

    // --- X movement ---
    if(IsKeyDown(left)) {
        if(player->velX>0.0f)
            player->velX -= 0.5f; // if opposite, break
        else
            player->velX -= 0.1f; // accelerate
        if(player->velX < -6)
            player->velX = -6; //max
    }
    else if(IsKeyDown(right)) {
        if(player->velX<0.0f)
            player->velX += 0.5f; //Brake hard
        //testPos.x += player->velX;
        else
            player->velX += 0.1f; // accelerate
        if(player->velX > 6)
            player->velX = 6;  //Maximum
    }
    else {
        player->velX *= 0.8f;
    }

    // Velocity never reaches zero.
    if (fabs(player->velX) < 0.05f)
        player->velX = 0.0f;

    Vector2 testPos = player->pos;
    testPos.x += player->velX;

    Rectangle testRect = (Rectangle){
        testPos.x - player->orgX,
        testPos.y - player->orgY,
        2*player->orgX,
        2*player->orgY
    };

    if (!CheckCollisionRecs(testRect, otherRect)) {
        player->pos.x = testPos.x; // accept X move only if no collision
    }

    // --- Y movement (jump/gravity) ---
    if(IsKeyPressed(jump) && !player->jump) {
        player->velY = player->jp;
        player->jump = true;
    }

    if(player->jump || player->pos.y < ground - player->orgY) {
        testPos = player->pos;
        testPos.y += player->velY;

        Rectangle testRectY = (Rectangle){
            testPos.x - player->orgX,
            testPos.y - player->orgY,
            2*player->orgX,
            2*player->orgY
        };

        if (!CheckCollisionRecs(testRectY, otherRect)) {
            player->pos.y = testPos.y; // accept Y move only if no collision
        }
        else
        {
            if(player->velY > 0)
            {
                // Moving downward = landed on P2
                player->pos.y = otherRect.y - player->orgY;
                player->jump = false;
            }
            else if(player->velY < 0)
            {
                // Moving upward = hit the bottom of P2
                player->pos.y = otherRect.y + otherRect.height + player->orgY;
            }

            player->velY = 0;
        }
        /*else {
            player->velY=0;
            player->jump=false;
        }*/

        player->velY += player->g;

        if(player->pos.y > ground - player->orgY) {
            player->pos.y = ground - player->orgY;
            player->velY = 0;
            player->jump = false;
        }
    }

    // Walls
    if(player->pos.x < player->orgX) player->pos.x = player->orgX;
    if(player->pos.x > windowX - player->orgX) player->pos.x = windowX - player->orgX;

    // Update rect
    player->rect.x = player->pos.x - player->orgX;
    player->rect.y = player->pos.y - player->orgY;
    player->rect.width  = 2*player->orgX;
    player->rect.height = 2*player->orgY;
}

void DrawPlayer(Player *player, float scale, bool dir)
{
    int sign=1;
    if (dir) sign=-1;
    Rectangle src={0, 0, sign*player->txt.width, player->txt.height};
    Rectangle dest={player->pos.x, player->pos.y, player->txt.width*scale, player->txt.height*scale};
    DrawTexturePro(player->txt, src, dest, (Vector2){player->orgX, player->orgY}, 0.0f, WHITE);

}