#include "raylib.h"
#include "game.h"
#include <stdbool.h>

// Staes definitiom
typedef enum GameState{
    STATE_MENU,
    STATE_GAMEPLAY,
    STATE_MODE_SELECT,
    STATE_GAMEOVER,
    STATE_PAUSE
}GameState;

typedef enum GameMode {
    RACE_TO_10,
    RACE_AGAINST_TIME
} GameMode;

int main(void)
{
    int windowX = 1350;
    int windowY = 800;
    int GND=(0.90625*windowY);  // ground


    InitWindow(windowX, windowY, "HABAH_BABAH");
    SetTargetFPS(60);

    GameState currentState= STATE_MENU;
    GameMode selectedMode = RACE_TO_10; // Default

    // Play Button Rectangle (Center screen)
    Rectangle playButton = { 
        (float)windowX / 2 - 100, 
        (float)windowY / 2 - 25, 
        200, 
        50
    };

    //Mode Buttons
    Rectangle mode1Button = { (float)windowX/2 - 220, (float)windowY/2 - 25, 200, 50 };
    Rectangle mode2Button = { (float)windowX/2 + 20,  (float)windowY/2 - 25, 200, 50 };

    InitGame(windowX, windowY); // all initializations

    while (!WindowShouldClose())
    {
        //=====================================//
        //==========UPDATE LOGIC===============//
        //=====================================//
        Vector2 mousePoint = GetMousePosition();
        switch (currentState)
        {
            case STATE_MENU:
            {
                // Option A: Click "Play" button with Mouse
                if (CheckCollisionPointRec(mousePoint, playButton)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        currentState = STATE_MODE_SELECT;
                    }
                }

                // OR
                // Option B: Press ENTER key to start
                if (IsKeyPressed(KEY_ENTER)) {
                    currentState = STATE_MODE_SELECT;
                }
            }
            break;

            case STATE_MODE_SELECT:
            {
                // Mode 1: Best of Three
                if (CheckCollisionPointRec(mousePoint, mode1Button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    selectedMode = RACE_TO_10;
                    StartMatch(selectedMode, windowX, windowY);
                    currentState = STATE_GAMEPLAY; // Launch game
                }

                // Mode 2: Race Against Time
                if (CheckCollisionPointRec(mousePoint, mode2Button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    selectedMode = RACE_AGAINST_TIME;
                    StartMatch(selectedMode, windowX, windowY);
                    currentState = STATE_GAMEPLAY; // Launch game
                }

                // Pressing BACKSPACE goes back to Main Menu
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    currentState = STATE_MENU;
                }
            }
            break;
            case STATE_GAMEPLAY:
            {
                if (IsKeyPressed(KEY_TAB))
                    currentState=STATE_PAUSE;
                bool x=UpdateGame(windowX, windowY); // all events
                if (x)
                {
                    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
                        currentState= STATE_MENU;
                    if(IsKeyPressed(KEY_BACKSPACE))
                        currentState= STATE_MODE_SELECT;
                }
            }
            break;
            case STATE_PAUSE:
            {
                if (IsKeyPressed(KEY_TAB))
                    currentState=STATE_GAMEPLAY;
            }
        }

        //=====================================//
        //============DRAW LOGIC===============//
        //=====================================//
        BeginDrawing();

        ClearBackground(BLACK);

        switch (currentState)
        {
            case STATE_MENU:
            {
                // Draw Title
                DrawText("HABAH BABAH", windowX / 2 - MeasureText("HABAH BABAH", 60) / 2, 80, 60, DARKBLUE);

                bool isHovered = CheckCollisionPointRec(mousePoint, playButton);

                // Draw Button (Changes color on hover)
                DrawRectangleRec(playButton, isHovered ? LIGHTGRAY : GRAY);
                DrawRectangleLinesEx(playButton, 2, DARKBLUE);

                // Draw Button Text
                DrawText("PLAY", playButton.x + (playButton.width / 2) - (MeasureText("PLAY", 20) / 2),
                         playButton.y + (playButton.height / 2) - 10, 20, BLACK);

                // Draw Subtext Prompt
                DrawText("Or Press [ENTER] to Start", 
                         windowX / 2 - MeasureText("Or Press [ENTER] to Start", 18) / 2, 
                         playButton.y + 70, 18, DARKGRAY);
            }
            break;

            case STATE_MODE_SELECT:
            {
                DrawText("SELECT GAME MODE", windowX / 2 - MeasureText("SELECT GAME MODE", 30) / 2, 60, 30, DARKBLUE);

                    // --- Mode 1 Button: Best of 3 ---
                    bool hoverMode1 = CheckCollisionPointRec(mousePoint, mode1Button);
                    DrawRectangleRec(mode1Button, hoverMode1 ? SKYBLUE : LIGHTGRAY);
                    DrawRectangleLinesEx(mode1Button, 2, DARKBLUE);
                    DrawText("First to 10", mode1Button.x + 100 - MeasureText("First to 10", 18)/2, mode1Button.y + 16, 18, BLACK);

                    // --- Mode 2 Button: Race Against Time ---
                    bool hoverMode2 = CheckCollisionPointRec(mousePoint, mode2Button);
                    DrawRectangleRec(mode2Button, hoverMode2 ? SKYBLUE : LIGHTGRAY);
                    DrawRectangleLinesEx(mode2Button, 2, DARKBLUE);
                    DrawText("RACE TIME", mode2Button.x + 100 - MeasureText("RACE TIME", 18)/2, mode2Button.y + 16, 18, BLACK);

                    // Navigation tip
                    DrawText("Press [BACKSPACE] for Main Menu", 
                             windowX / 2 - MeasureText("Press [BACKSPACE] for Main Menu", 16) / 2, 
                             580, 16, GRAY);
            }
            break;
            case STATE_GAMEPLAY:
            {
                
                DrawGame(windowX, windowY); // all drawings
            }
            break;
            case STATE_PAUSE:
            {
                
                DrawGame(windowX, windowY); // all drawings
                DrawRectangle(0, 0, windowX, windowY, (Color){0 , 0, 0, 130});
            }
            break;
        }

        EndDrawing();
    }

    CloseGame(); // all unloadings

    CloseWindow();

    return 0;
}
