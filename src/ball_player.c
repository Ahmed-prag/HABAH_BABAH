#include "ball_player.h"
#include <math.h>

void BallPlayerCollision(Ball *ball, Player *player)
{
    // 1. Find closest point on player rectangle to ball center
    float pLeft   = player->pos.x - player->orgX;
    float pRight  = player->pos.x + player->orgX;
    float pTop    = player->pos.y - player->orgY;
    float pBottom = player->pos.y + player->orgY;

    float closestX = ball->next.x;
    float closestY = ball->next.y;

    if (closestX < pLeft)   closestX = pLeft;
    if (closestX > pRight)  closestX = pRight;
    if (closestY < pTop)    closestY = pTop;
    if (closestY > pBottom) closestY = pBottom;

    // 2. Vector from closest point to ball
    float dirX = ball->next.x - closestX;
    float dirY = ball->next.y - closestY;
    float distanceSq = dirX * dirX + dirY * dirY;

    if (distanceSq < (ball->radius * ball->radius)) // If ball is touching player
    {
        float distance = sqrtf(distanceSq);
        if (distance == 0.0f) {
            dirY = -1.0f;
            distance = 1.0f;
        }

        // Base Normal vector (direction away from player)
        float nx = dirX / distance;
        float ny = dirY / distance;

        // 3. Resolve Overlap
        float overlap = ball->radius - distance;
        ball->next.x += nx * overlap;
        ball->next.y += ny * overlap;

        // =========================================================
        // PINCH / STUCK FIX
        // =========================================================
        float pinchUpwardForce = -14.0f; 

        if (overlap > ball->radius * 0.3f && fabs(nx) > 0.6f)
        {
            ball->velY = pinchUpwardForce; // Launch cleanly upward
            ball->velX = 0.0f;              // Zero out horizontal velocity
        }

        //===========================================================//
        // ------------4. Player relative velocity-------------------//
        //===========================================================//
        float playerVelX = player->pos.x - player->old.x;
        float playerVelY = player->pos.y - player->old.y;

        // Relative velocity between ball and player
        float relVelX = ball->velX - playerVelX;
        float relVelY = ball->velY - playerVelY;

        // Calculate velocity along collision normal
        // How fast the ball and player are closing on each other
        float normalVel = relVelX * nx + relVelY * ny;

        // Only reflect if moving toward each other
        if (normalVel < 0.0f)
        {
            //=======================================================//
            // Restitution (bounciness): 0.6 absorbs speed, 1.0 retains full speed
            //=======================================================//
            float restitution = ball->bounce; 
            float impulse = -(1.0f + restitution) * normalVel *1.0;
            // add this factor for greater bounce off from player
            // (FORMULA) impulse= -(1+ e). Vnormal, e is ball bounce

            // Apply standard reflection impulse along normal
            ball->velX += nx * impulse;
            ball->velY += ny * impulse;

            // =========================================================
            // DYNAMIC JUMP-HEADER & SPEED LIFT
            // =========================================================

            // 4.1 JUMP-HEADER BOOST: When jumping UP (playerVelY < 0) into a falling ball
            if (playerVelY < 0.0f && ny < -0.3f) 
            {
                // Transfer upward jump momentum directly into the ball
                // The faster you jump up, the higher/stronger the header goes
                float jumpPowerMultiplier = 1.2f; 
                ball->velY += playerVelY * jumpPowerMultiplier; 

                // Add forward heading arc based on player horizontal motion
                ball->velX += playerVelX * 0.8f; 
            }

            // 4.2. INCOMING SPEED LIFT: Convert incoming horizontal speed into height
            // If ball is traveling fast horizontally, angled headers lift it higher
            float incomingSpeedX = fabs(relVelX);
            if (incomingSpeedX > 4.0f) 
            {
                float speedToLiftRatio = 0.35f; // 35% of horizontal speed converted to vertical lift
                ball->velY -= incomingSpeedX * speedToLiftRatio; 
            }

            // Transfer player momentum (only when player moves INTO the ball)
            if (playerVelX * nx > 0) ball->velX += playerVelX * 0.8f;
            if (playerVelY * ny > 0) ball->velY += playerVelY * 0.8f;
            // Add this 0.8 factor for modified kick power
        }

        // 5. Speed Cap & Pinch Prevention
        float maxVelX = 14.0f;
        float maxVelY = 20.0f; 

        if (ball->velY < -maxVelY) ball->velY = -maxVelY; 
        if (ball->velX >  maxVelX) ball->velX =  maxVelX;
        if (ball->velX < -maxVelX) ball->velX = -maxVelX;
    }
}