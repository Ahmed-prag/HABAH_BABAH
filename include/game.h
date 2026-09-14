#ifndef GAME_H
#define GAME_H

typedef enum GameMode {
    RACE_TO_10,
    RACE_AGAINST_TIME
} GameMode;

void InitGame(int windowX, int windowY);
void StartMatch(GameMode mode, int windowX, int windowY); // Reset game & set mode
bool UpdateGame(int windowX, int windowY);
void DrawGame(int windowX, int windowY);
void CloseGame(void);

#endif