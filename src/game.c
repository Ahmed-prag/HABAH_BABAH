#include "raylib.h"
#include "game.h"
#include "field.h"
#include "player.h"
#include "ball.h"
#include "ball_player.h"
#include<math.h>

static Texture2D fieldTexture;

static float scale; //Scale

static float GND; //ground

static Player player1, player2;

static Ball ball;

static int scorePlayer1 = 0;
static int scorePlayer2 = 0;

static float matchTimer = 60.0f; // Temps de match en secondes
static bool gameOver = false;    // Indique si le temps est écoulé

void InitGame(int windowX, int windowY)
{
    scale = 0.0002 * windowY;  // Calculated wrt player pic and windowY

    GND=(0.90625*windowY);  // ground
    
    // Ball
    InitBall(&ball, windowX, windowY);

    //============Field Texture============//
    fieldTexture = LoadTexture("assets/textures/field.png");

    //================Player===============//
    player1.txt = LoadTexture("assets/textures/player1.png");
    player2.txt = LoadTexture("assets/textures/player2.png");

    player1.pos.x = 0.6f* windowX;
    player2.pos.x = 0.4f*windowX; //position in X

    // Other attributes
    InitPlayer(&player1, GND, scale);
    InitPlayer(&player2, GND, scale);
    
}

void UpdateGame(int windowX, int windowY)
{
    // Si le temps est écoulé, on n'actualise plus le jeu
    if (gameOver)
    {
        return;
    }

    // Décrémentation du chrono
    if (matchTimer > 0.0f)
    {
        matchTimer -= GetFrameTime();
        if (matchTimer <= 0.0f)
        {
            matchTimer = 0.0f;
            gameOver = true; // La partie est terminée !

            // --- REPOINTER LE BALLON AU SOL AU CENTRE ---
            ball.pos.x = windowX / 2.0f;
            ball.pos.y = GND - ball.radius; // Posé pile sur le sol
            ball.velX = 0.0f;
            ball.velY = 0.0f;
            
            // --- REMISE À ZÉRO DES JOUEURS ---
            player1.pos.x = 0.6f * windowX;     // Joueur 1 à sa position de départ
            player2.pos.x = 0.4f * windowX;     // Joueur 2 à sa position de départ
            
            // Remettre les joueurs au sol
            InitPlayer(&player1, GND, scale);
            InitPlayer(&player2, GND, scale);
        }
    }
    Rectangle P1R = player1.rect, P2R=player2.rect; //Player rectangle
    UpdateBall(&ball, windowX, windowY, GND);

    UpdatePlayer( &player1, KEY_LEFT, KEY_RIGHT, KEY_UP, windowX, GND, scale, P2R);
    
    UpdatePlayer( &player2, KEY_A, KEY_D, KEY_W, windowX, GND, scale, P1R);

    //Ball player collision.
    BallPlayerCollision(&ball, &player1);
    BallPlayerCollision(&ball, &player2);

    // Confirm here, the new ball pos.
    ball.pos = ball.next;
    
    //==========player facing===========//
    // Player 1
    if(ball.pos.x<player1.pos.x) player1.dir=false;
    else player1.dir=true;

    //Player 2
    if(ball.pos.x<player2.pos.x) player2.dir=false;
    else player2.dir=true;

    // --- DÉTECTION DU BUT ---
    static int goalScored = 0;
    if (!goalScored)
    {
        goalScored = CheckGoal(&ball, windowX, GND);

        if (goalScored == 1)
        {
            scorePlayer1++;
        }
        else if (goalScored == 2)
        {
            scorePlayer2++;
        }
    }
    if (goalScored != 0)
    {
        static double startTime = 0.0;
        
        // Save the start time when the goal is first detected
        if (startTime == 0.0) 
        {
            startTime = GetTime();
        }

        // Check if 1 second has passed
        if (GetTime() - startTime >= 1.0)
        {
            ResetBall(&ball, windowX, windowY);
            startTime = 0.0; // Reset timer for the next goal
            goalScored=0;
        }
    }

}

void DrawGame(int windowX, int windowY)
{
    // Field decor
    DrawTexture(fieldTexture, 0, 0, WHITE);

    //field outline in fieldd.c
    DrawField(windowX, windowY); // comes after field decor

    // Ball
    DrawBall(&ball);

    //Players
    DrawPlayer(&player1, scale, player1.dir); // for now, true or fasle
    DrawPlayer(&player2, scale, player2.dir);

    // --- FEATURE 005 : Affichage séparé dans le panneau ---
    int fontSize = 75;
    
    // Score Joueur 1 (Rectangle de gauche)
    const char *p1Text = TextFormat("%d", scorePlayer1);
    int p1Width = MeasureText(p1Text, fontSize);
    DrawText(p1Text, (windowX * 0.400f) - (p1Width / 2), 115, fontSize, WHITE);

    // Score Joueur 2 (Rectangle de droite)
    const char *p2Text = TextFormat("%d", scorePlayer2);
    int p2Width = MeasureText(p2Text, fontSize);
    DrawText(p2Text, (windowX * 0.720f) - (p2Width / 2), 115, fontSize, WHITE);

    // Affichage du Timer au centre du panneau
    const char *timerText = TextFormat("%02d", (int)matchTimer);
    int timerWidth = MeasureText(timerText, 90);
    DrawText(timerText, (windowX * 0.58f) - (timerWidth / 2), 125, 40, YELLOW);

    // Message GAME OVER si le temps est écoulé
    if (gameOver)
    {
        const char *overText = "Game  Over";
        int overWidth = MeasureText(overText, 80);
        DrawText(overText, (windowX / 2) - (overWidth / 2), (windowY / 2) - 15, 80, GREEN);
    }
}

void CloseGame(void)
{
    UnloadTexture(fieldTexture);
    UnloadTexture(player1.txt);
    UnloadTexture(player2.txt);
    UnloadTexture(ball.txt);
}