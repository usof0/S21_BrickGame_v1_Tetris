#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>

// Define the size of the game field
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

// Define the types of tetrominoes (Tetris pieces)
typedef enum { I = 0, O, T, S, Z, J, L } TetrominoType_t;

typedef struct {
  TetrominoType_t type;
  int body[4][4];
  int rotate_state;
} Tetromino_t;

// Define possible game states
typedef enum {
  GAME_START,
  GAME_SPAWN,
  GAME_SHIFTING,
  GAME_MOVE,
  GAME_ATTACH,
  GAME_OVER
} GameState_t;

// Define possible user actions
typedef enum {
  ACTION_START,
  ACTION_PAUSE,
  ACTION_TERMINATE,
  ACTION_LEFT,
  ACTION_RIGHT,
  ACTION_DOWN,
  ACTION_ACTION  // For rotating pieces
} UserAction_t;

// Structure representing the game field
typedef struct {
  int **field;
  TetrominoType_t next;
  int score;
  int high_score;
  int level;
  int speed;
  bool pause;
} GameInfo_t;

// void startGame();
GameState_t getCurrentState();
void setState(GameState_t new_state);
void initializeGame();
void freeMemory();
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);
void getNextBlock(int **shape);

#include "fsm.h"

#endif  // TETRIS_H
