#include "player.h"

void UpdatePlayer(Player *player, KeyboardKey left,
                  KeyboardKey right, KeyboardKey jump,
                  int windowX, float ground, float scale)
{
    if(IsKeyDown(left)) // move left
    {
        player->x -= player->velX;
        player->velX += 0.1f; // accelerate

        if(player->velX > 6)
            player->velX = 6; // max for now
    }
    else if(IsKeyDown(right)) // move right
    {
        player->x += player->velX;
        player->velX += 0.1f;

        if(player->velX > 6)
            player->velX = 6;
    }
    else
    {
        player->velX = 1; // reset
    }

    if(IsKeyPressed(jump) && !player->jump)
    {
        player->velY = player->jp;
        player->jump = true;
    }

    if(player->jump)
    {
        player->y += player->velY;
        player->velY += player->g;

        if(player->y > ground - (player->txt.height *scale))
        {
            player->y = ground - (player->txt.height * scale);
            player->velY = 0;
            player->jump = false;
        }
    }

    if(player->x < 0)
        player->x = 0;

    if(player->x > windowX - player->txt.width* scale)
        player->x = windowX - player->txt.width *scale;
}

void DrawPlayer(Player *player, float scale, bool dir)
{
    int sign=1;
    if (dir) sign=-1;
    Rectangle src={0, 0, sign*player->txt.width, player->txt.height};
    Rectangle dest={player->x, player->y, player->txt.width*scale, player->txt.height*scale};
    DrawTexturePro(player->txt, src, dest, (Vector2){0, 0}, 0.0f, WHITE);

}