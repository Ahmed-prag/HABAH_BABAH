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

static GameMode currentMode;
static bool suddenDeath;

static int winningPlayer; // 0 = None, 1 = Player 1, 2 = Player 2
static int scorePlayer1;
static int scorePlayer2;

static int goalScored;
static float matchTimer; // Temps de match en secondes
static bool gameOver;    // Indique si le temps est écoulé

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

    currentMode = RACE_TO_10;
}

void StartMatch(GameMode mode, int windowX, int windowY)
{
    currentMode = mode;
    scorePlayer1 = 0;
    scorePlayer2 = 0;
    winningPlayer = 0;
    gameOver = false;
    matchTimer = 1.0f;
    suddenDeath=false;
    goalScored = 0;

    ResetBall(&ball, windowX, windowY);
    
    player1.pos.x = 0.6f * windowX;
    player2.pos.x = 0.4f * windowX;
    InitPlayer(&player1, GND, scale);
    InitPlayer(&player2, GND, scale);
}

bool UpdateGame(int windowX, int windowY)
{
    // Si le temps est écoulé, on n'actualise plus le jeu
    if (gameOver) return true;

    //===================================================//
    // --- MODE 1: RACE AGAINST TIME (Timer Countdown) ---
    //===================================================//
    if (currentMode == RACE_AGAINST_TIME && !suddenDeath)
    {
        if (matchTimer > 0.0f)
        {
            matchTimer -= GetFrameTime();
            if (matchTimer <= 0.0f)
            {
                matchTimer = 0.0f;
                if(scorePlayer1 == scorePlayer2)
                {
                    suddenDeath=true;
                }
                else{
                    gameOver = true;
                    winningPlayer = (scorePlayer1 > scorePlayer2) ? 1 : ((scorePlayer2 > scorePlayer1) ? 2 : 0);
                }
            }
        }
    }

    //===============================================//
    //=============Ball And player updates===========//
    //===============================================//
    UpdateBall(&ball, windowX, windowY, GND);

    UpdatePlayer(&player1, KEY_LEFT, KEY_RIGHT, KEY_UP, windowX, GND, scale, player2.rect);

    UpdatePlayer(&player2, KEY_A, KEY_D, KEY_W, windowX, GND, scale, player1.rect);
    
    //==============================================//
    //==========Ball player collision===============//
    //==============================================//
    BallPlayerCollision(&ball, &player1);
    BallPlayerCollision(&ball, &player2);

    // Confirm here, the new ball pos
    ball.pos = ball.next;

    //=========Player Direction logic========//
    player1.dir = (ball.pos.x >= player1.pos.x);
    player2.dir = (ball.pos.x >= player2.pos.x);

    //===================================================//
    //=================GOAL DETECTION ===================//
    //===================================================//
    if (!goalScored)
    {
        goalScored = CheckGoal(&ball, windowX, GND);

        if (goalScored == 1) scorePlayer1++;

        else if (goalScored == 2) scorePlayer2++;

        //=========================================//
        //==============Sudden Death===============//
        //=========================================//
        if (suddenDeath && goalScored != 0)
        {
            gameOver=true;
            winningPlayer=goalScored;
        }

        //===============================================//
        //--- MODE 2: RACE TO 10 (First to X points)---/
        //===============================================//
        int x=10;
        if (currentMode == RACE_TO_10)
        {
            if (scorePlayer1 >= x)
            {
                gameOver = true;
                winningPlayer = 1;
            }
            else if (scorePlayer2 >= x)
            {
                gameOver = true;
                winningPlayer = 2;
            }
        }
    }

    //=================================================//
    //============Delay before Ball Respawn============//
    //=================================================//
    if (goalScored != 0 && !gameOver)
    {
        static double startTime = 0.0;

        // Save the start time when the goal is first detected
        if (startTime == 0.0) startTime = GetTime();

        // Check if 1 second has passed
        if (GetTime() - startTime >= 1.0)
        {
            ResetBall(&ball, windowX, windowY);
            startTime = 0.0f;
            goalScored = 0;
        }
    }
    return false;
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
    DrawPlayer(&player1, scale, player1.dir);
    DrawPlayer(&player2, scale, player2.dir);

    // --- FEATURE 005 : Affichage séparé dans le panneau ---
    int fontSize = 75;
    
    // Score Joueur 1 (Rectangle de gauche)
    const char *p1Text = TextFormat("%d", scorePlayer1);
    int p1Width = MeasureText(p1Text, fontSize);
    DrawText(p1Text, (windowX * 0.4f) - (p1Width / 2), 115, fontSize, WHITE);

    // Score Joueur 2 (Rectangle de droite)
    const char *p2Text = TextFormat("%d", scorePlayer2);
    int p2Width = MeasureText(p2Text, fontSize);
    DrawText(p2Text, (windowX * 0.72f) - (p2Width / 2), 115, fontSize, WHITE);

    // Affichage du Timer au centre du panneau
    if(currentMode== RACE_AGAINST_TIME)
    {
        if(suddenDeath) // If sudden death
        {
            const char *sdText = "SUDDEN DEATH! NEXT GOAL WINS";
            int sdWidth = MeasureText(sdText, 30);
            DrawText(sdText, (windowX * 0.44f) - (sdWidth / 4), 35, 30, YELLOW);
        }
        else // Or normal time
        {
            const char *timerText = TextFormat("%02d", (int)matchTimer);
            int timerWidth = MeasureText(timerText, 40);
            DrawText(timerText, (windowX * 0.58f) - (timerWidth / 2), 125, 40, YELLOW);
        }
        
    }

    else
    {
        DrawText("FIRST TO 10", (windowX * 0.56f) - (MeasureText("FIRST TO 2", 20) / 2), 135, 20, YELLOW);
    }

    //Goaaal! banner
    if(goalScored !=0 && !gameOver)
    {
        static int fontSize=90;
        const char *goalText = "GOAAAAL!";
        int goalWidth = MeasureText(goalText, fontSize);
        DrawText(goalText, (windowX / 2) - (goalWidth / 2), (windowY / 2) - 45, fontSize, GOLD);
        static int rise=0;
        if(!rise){
            fontSize+=5;
            if(fontSize>=90)
                rise=1;
        }
        else {
            fontSize-=5;
            if(fontSize <=30)
                rise=0;
        }
    }

    // Message GAME OVER si le temps est écoulé
    if (gameOver)
    {
        DrawRectangle(0, 0, windowX, windowY, (Color){0,0,0,128});
        const char *overText = "Game  Over";
        int overWidth = MeasureText(overText, 80);
        DrawText(overText, (windowX / 2) - (overWidth / 2), (windowY / 4) - 15, 80, GREEN);
        
        const char *winnerText = (winningPlayer == 1) ? "PLAYER 1 WINS!" : 
                                 (winningPlayer == 2) ? "PLAYER 2 WINS!" : "DRAW!";
        int txtWidth = MeasureText(winnerText, 60);
        DrawText(winnerText, (windowX / 2) - (txtWidth / 2), (windowY / 2) - 30, 60, GREEN);
        DrawText("Press ENTER to go back to Menu", windowX/3, windowY/1.5, 30, WHITE);
        DrawText("Press BACKSPACE to go back to Mode Select", windowX/3.4f, windowY/1.2, 30, WHITE);
    }
    DrawText("TAB to toggle pause", 10, 10, 20, BLACK);
}

void CloseGame(void)
{
    UnloadTexture(fieldTexture);
    UnloadTexture(player1.txt);
    UnloadTexture(player2.txt);
    UnloadTexture(ball.txt);
}