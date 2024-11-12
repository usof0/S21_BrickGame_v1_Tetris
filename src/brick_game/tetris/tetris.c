#include "tetris.h"

#include <stdlib.h>

#include "fsm.h"

// Define static objects for the game state
static GameInfo_t current_game;
static GameState_t current_state;

GameState_t getCurrentState() { return current_state; }

// this function is used for testing
void setState(GameState_t new_state) { current_state = new_state; }

void initializeGame() {
  current_game.field = (int **)calloc(FIELD_HEIGHT, sizeof(int *));
  current_game.score = 0;
  current_game.high_score = 0;
  current_game.level = 1;
  current_game.speed = 500;
  current_game.pause = false;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    current_game.field[i] = (int *)calloc(FIELD_WIDTH, sizeof(int));
  }

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      current_game.field[i][j] = 0;
    }
  }
  current_game.next = rand() % 7;
  initCurrentTetromino(current_game.next);
  updateHighScore(&current_game);
}

void userInput(UserAction_t action, bool hold) {
  switch (action) {
    case ACTION_START:
      initializeGame();
      current_state = GAME_SPAWN;

      break;
    case ACTION_PAUSE:
      current_game.pause = !current_game.pause;
      break;
    case ACTION_TERMINATE:
      current_state = GAME_START;
      break;
    case ACTION_LEFT:
    case ACTION_RIGHT:
    case ACTION_DOWN:
    case ACTION_ACTION:
      if (hold == false) {
        current_state = GAME_SHIFTING;
        if (!current_game.pause) {
          handleUserInput(&current_game, &current_state, action);
        }
        current_state = GAME_MOVE;
        break;
      }
      for (int i = 0; i < 3; i++) {
        current_state = GAME_SHIFTING;
        if (!current_game.pause) {
          handleUserInput(&current_game, &current_state, action);
        }
        current_state = GAME_MOVE;
      }
      break;
    default:
      break;
  }
}

GameInfo_t updateCurrentState() {
  if (!current_game.pause) {
    switch (current_state) {
      case GAME_SPAWN:
        spawnTetromino(&current_game);
        current_state = GAME_MOVE;
        break;
      case GAME_MOVE:
        moveTetrominoDown(&current_game, &current_state);
        break;
      case GAME_ATTACH:
        attachTetromino(&current_game);
        if (checkGameOver(&current_game)) {
          current_state = GAME_OVER;
        } else {
          current_state = GAME_SPAWN;
        }
        break;

      default:
        break;
    }
  }
  return current_game;
}

void getNextBlock(int **shape) { getNextShape(current_game.next, shape); }

void freeMemory() {
  if (current_game.field == NULL) return;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(current_game.field[i]);
  }
  free(current_game.field);
}
