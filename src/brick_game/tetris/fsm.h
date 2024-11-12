#ifndef FSM_H
#define FSM_H

#include "tetris.h"

void getNextShape(TetrominoType_t next, int **shape);
void initCurrentTetromino(TetrominoType_t type);
void spawnTetromino(GameInfo_t *current_game);
void moveTetrominoDown(GameInfo_t *current_game, GameState_t *current_state);
void moveTetrominoLeft(GameInfo_t *current_game);
void moveTetrominoRight(GameInfo_t *current_game);
void rotateTetromino(GameInfo_t *current_game);
void attachTetromino(GameInfo_t *current_game);
bool checkRowComplete(GameInfo_t *current_game, int row);
void clearRow(GameInfo_t *current_game, int row);
bool checkGameOver(GameInfo_t *current_game);
void handleUserInput(GameInfo_t *current_game, GameState_t *current_state,
                     UserAction_t action);
bool checkCollision(GameInfo_t *current_game, int x, int y);
int updateScore(int rows_damaged);
void updateHighScore(GameInfo_t *game);
void updateLevel(GameInfo_t *game);
void updateSpeed(GameInfo_t *game);

#endif  // FSM_H
