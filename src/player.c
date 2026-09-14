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
void UpdatePlayer(Player *player, KeyboardKey left, KeyboardKey right, KeyboardKey jump,
                  int windowX, float ground, float scale, Rectangle otherRect)
{
    player->old = player->pos;

    // --- X movement ---
    if(IsKeyDown(left)) {
        if (player->velX > 0.0f)
            player->velX -= 0.5f; //If moving opposite way, break
        else
            player->velX -= 0.1f; // accelerate
        if (player->velX < -6.0f)
        player->velX = -6.0f;
    }
    else if (IsKeyDown(right)) {
        if (player->velX < 0.0f)
            player->velX += 0.5f; //Brake hard
        else
            player->velX += 0.1f; // accelerate
        if(player->velX > 6.0f)
            player->velX = 6.0f; // MAX
    }
    else {
        player->velX *= 0.8f;
    }

    // Velocity never reaches zero...
    if(fabs(player->velX) < 0.05f) player->velX = 0.0f;

    if(IsKeyPressed(jump) && !player->jump) {
        player->velY = player->jp;
        player->jump = true;
    }

    // Apply movement
    player->pos.x += player->velX;
    player->pos.y += player->velY;

    // Apply gravity
    if(player->jump || player->pos.y < ground - player->orgY) {
        player->velY += player->g;
    }

    // Ground constraint
    if (player->pos.y > ground - player->orgY) {
        player->pos.y = ground - player->orgY;
        player->velY = 0.0f;
        player->jump = false;
    }

    // Window boundaries
    if (player->pos.x < player->orgX) player->pos.x = player->orgX;
    if (player->pos.x > windowX - player->orgX) player->pos.x = windowX - player->orgX;

    // Update current bounding box
    player->rect.x = player->pos.x - player->orgX;
    player->rect.y = player->pos.y - player->orgY;
    player->rect.width = 2* player->orgX;
    player->rect.height = 2* player->orgY;

    // --- PLAYER vs PLAYER RESOLUTION (Fixes Sticking) ---
    if (CheckCollisionRecs(player->rect, otherRect))
    {
        // Calculate overlap on each side
        float overlapLeft = (player->rect.x + player->rect.width) - otherRect.x;
        float overlapRight = (otherRect.x + otherRect.width) - player->rect.x;
        float overlapTop = (player->rect.y + player->rect.height) - otherRect.y;
        float overlapBottom = (otherRect.y + otherRect.height) - player->rect.y;

        // Find smallest overlap magnitude
        float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
        float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

        if (minOverlapX < minOverlapY)
        {
            // Horizontal collision resolution
            if (overlapLeft < overlapRight) { // Simule certain scenario et voir les valeurs
                // Moving right into other player
                player->pos.x -= overlapLeft;
                if (player->velX > 0)
                    player->velX = 0;
            } else {
                // Moving left into other player
                player->pos.x += overlapRight;
                if (player->velX < 0)
                    player->velX = 0;
            }
        }
        else
        {
            // Vertical collision resolution
            if (overlapTop < overlapBottom) {
                // Landing on top of other player
                player->pos.y -= overlapTop;
                if (player->velY > 0) {
                    player->velY = 0;
                    player->jump = false;
                }
            } else{
                // Hitting head on bottom of other player
                player->pos.y += overlapBottom;
                if (player->velY < 0) player->velY = 0;
            }
        }

        // Keep rect updated after positional adjustment
        player->rect.x = player->pos.x - player->orgX;
        player->rect.y = player->pos.y - player->orgY;
    }
}

void DrawPlayer(Player *player, float scale, bool dir)
{
    int sign=1;
    if (dir) sign=-1;
    Rectangle src={0, 0, sign*player->txt.width, player->txt.height};
    Rectangle dest={player->pos.x, player->pos.y, player->txt.width*scale, player->txt.height*scale};
    DrawTexturePro(player->txt, src, dest, (Vector2){player->orgX, player->orgY}, 0.0f, WHITE);

}