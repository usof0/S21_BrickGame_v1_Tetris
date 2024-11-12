#ifndef CLI_H
#define CLI_H
#include "./../../brick_game/tetris/tetris.h"

void initializeInterface();
void renderGame();
void displayInformation(GameInfo_t game_info);
void displayDirections();
void displayStartGame();
void displayPause();
void displayGameOver();
void cleanupInterface();

#endif  // CLI_H
