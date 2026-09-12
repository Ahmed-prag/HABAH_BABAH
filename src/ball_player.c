#include "ball_player.h"
#include<math.h>


void BallPlayerCollision(Ball *ball, Player *player)
{
    // Ball movement this frame
    float ballMoveX = ball->next.x - ball->pos.x;
    float ballMoveY = ball->next.y - ball->pos.y;

    // Player movement this frame
    float playerMoveX = player->pos.x - player->old.x;
    float playerMoveY = player->pos.y - player->old.y;

    // Ball movement relative to player
    float relX = ballMoveX - playerMoveX;
    float relY = ballMoveY - playerMoveY;

    // Ball's starting position relative to player's old position
    float startX = ball->pos.x - player->old.x;
    float startY = ball->pos.y - player->old.y;

    // Player rectangle expanded by ball radius
    float left = -player->orgX - ball->radius;
    float right = player->orgX + ball->radius;
    float top = -player->orgY - ball->radius;
    float bottom = player->orgY + ball->radius;

    float tMin = 0.0f;
    float tMax = 1.0f;

    // We will remember whether X or Y produced the first collision.
    bool hitX = false;
    bool hitY = false;

    // ============= X AXIS ============//
    if (relX == 0.0f)
    {
        if (startX < left || startX > right)
            return;
    }
    else
    {
        float tx1 = (left - startX) /relX;
        float tx2 = (right - startX) /relX;
        if (tx1 > tx2)
        {
            float temp = tx1;
            tx1 = tx2;
            tx2 = temp;
        }
        if (tx1 > tMin)
        {
            tMin = tx1;
            hitX = true;
            hitY = false;
        }
        if (tx2 < tMax)
            tMax = tx2;
        if (tMin > tMax)
            return;
    }

    // ---------------- Y AXIS ----------------
    if (relY == 0.0f)
    {
        if (startY < top || startY > bottom)
            return;
    }
    else
    {
        float ty1 = (top - startY) /relY;
        float ty2 = (bottom - startY) / relY;
        if (ty1 > ty2)
        {
            float temp = ty1;
            ty1 = ty2;
            ty2 = temp;
        }
        if (ty1 > tMin)
        {
            tMin = ty1;
            hitX = false;
            hitY = true;
        }
        if (ty2 < tMax)
            tMax = ty2;

        if (tMin > tMax)
            return;
    }

    // No collision during this frame
    if (tMin < 0.0f || tMin > 1.0f)
        return;

    // ---------------- COLLISION POINT ----------------
    float hitT = tMin;
    float playerHitX = player->old.x + playerMoveX * hitT;
    float playerHitY = player->old.y + playerMoveY * hitT;

    // ---------------- HORIZONTAL HIT ----------------
    if (hitX)
    {
        // Where vertically on the player did the ball hit?
        // -1 = top
        // 0 = center
        // +1 = bottom

        float hitOffset =
            (ball->pos.y + ballMoveY * hitT - playerHitY) / player->orgY;
        // Limit the effect
        if (hitOffset > 1.0f) hitOffset = 1.0f;
        if (hitOffset < -1.0f) hitOffset = -1.0f;

        if (relX > 0)
        {
            // Ball moving right -> hits player's left side
            ball->next.x = playerHitX - player->orgX - ball->radius;
            // Normal horizontal bounce
            ball->velX = -fabs(ball->velX) * ball->bounce;

            // Player movement
            ball->velX += playerMoveX;
        }
        else
        {
            // Ball moving left -> hits player's right side
            ball->next.x = playerHitX + player->orgX + ball->radius;
            // Normal horizontal bounce
            ball->velX = fabs(ball->velX) * ball->bounce;
            // Player movement
            ball->velX += playerMoveX;
        }

        // Hit higher/lower on player changes vertical direction.
        // A hit near the top gives upward velocity.
        // A hit near the bottom gives downward velocity.

        float angleStrength = 9.0f; // can change this ;ater
        ball->velY += hitOffset * angleStrength;
    }

    // ---------------- VERTICAL HIT ----------------
    else if (hitY)
    {
        // Where horizontally on the player did the ball hit?
        //
        // -1 = left
        //  0 = center
        // +1 = right

        float hitOffset =
            (ball->pos.x + ballMoveX * hitT - playerHitX) / player->orgX;

        // Limit the effect
        if (hitOffset > 1.0f) hitOffset = 1.0f;
        if (hitOffset < -1.0f) hitOffset = -1.0f;

        if (relY > 0)
        {
            // Ball moving downward -> hits player's TOP
            ball->next.y = playerHitY - player->orgY - ball->radius;
            // KEEP THE ORIGINAL UPWARD BOUNCE
            ball->velY = -fabs(ball->velY) * ball->bounce;

            // Player movement still influences it
            ball->velY += playerMoveY*0.6f;
        }
        else
        {
            // Ball moving upward -> hits player's BOTTOM
            ball->next.y = playerHitY + player->orgY + ball->radius;
            ball->velY =  fabs(ball->velY) * ball->bounce;
            ball->velY += playerMoveY;
        }

        // Hit toward the left/right side of the player
        // gives the ball horizontal velocity.

        float angleStrength = 4.0f;// htis too
        ball->velX += hitOffset * angleStrength;
    }
}