#include "tests.h"

#include <stdlib.h>

#include "./../brick_game/tetris/tetris.h"

START_TEST(tetris_base_test1) {
  initializeGame();
  //   GameInfo_t game = updateCurrentState();
  userInput(ACTION_START, false);
  userInput(ACTION_DOWN, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_ACTION, false);
  userInput(ACTION_ACTION, false);
  userInput(ACTION_ACTION, false);
  userInput(ACTION_ACTION, false);
  userInput(ACTION_PAUSE, false);
  userInput(ACTION_PAUSE, false);
  userInput(ACTION_DOWN, false);
  for (int i = 0; i < 20; i++) {
    userInput(ACTION_DOWN, false);
  }

  userInput(ACTION_TERMINATE, false);

  freeMemory();
}
END_TEST

START_TEST(tetris_base_test2) {
  initializeGame();
  userInput(ACTION_START, false);
  GameInfo_t game = updateCurrentState();
  if (game.next != O) {
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
  }
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_DOWN, true);

  userInput(ACTION_TERMINATE, false);

  freeMemory();
}

START_TEST(tetris_base_test3) {
  initializeGame();
  userInput(ACTION_START, false);
  GameInfo_t game = updateCurrentState();
  if (game.next != O) {
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
  }
  rotateTetromino(&game);
  game = updateCurrentState();
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_DOWN, true);
  rotateTetromino(&game);
  game = updateCurrentState();
  for (int i = 0; i < 12; i++) {
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_DOWN, true);
  }
  rotateTetromino(&game);
  game = updateCurrentState();

  userInput(ACTION_TERMINATE, false);

  freeMemory();
}
END_TEST

START_TEST(tetris_base_test4) {
  initializeGame();
  userInput(ACTION_START, false);
  GameInfo_t game = updateCurrentState();
  if (game.next != O) {
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
  }
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_DOWN, true);
  for (int i = 0; i < 10; i++) {
    game.field[19][i] = 1;
  }
  setState(GAME_ATTACH);
  rotateTetromino(&game);
  game = updateCurrentState();
  setState(GAME_SHIFTING);
  rotateTetromino(&game);
  game = updateCurrentState();

  userInput(ACTION_TERMINATE, false);

  freeMemory();
}
END_TEST

START_TEST(tetris_base_test5) {
  initializeGame();
  userInput(ACTION_START, false);
  GameInfo_t game = updateCurrentState();
  if (game.next != O) {
    userInput(ACTION_ACTION, false);
  }
  int **next = (int **)calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    next[i] = (int *)calloc(4, sizeof(int));
  }
  getNextBlock(next);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (next[i][j]) {
        userInput(ACTION_ACTION, false);
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    free(next[i]);
  }
  free(next);
  GameState_t state = getCurrentState();
  if (state != GAME_SHIFTING) {
    userInput(ACTION_ACTION, false);
  }

  for (int i = 0; i < 10; i++) {
    game.field[19][i] = 1;
  }
  attachTetromino(&game);

  userInput(ACTION_TERMINATE, false);

  freeMemory();
}
END_TEST

START_TEST(tetris_base_test6) {
  initializeGame();
  userInput(ACTION_START, false);
  GameInfo_t game = updateCurrentState();
  if (game.next != O) {
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
    userInput(ACTION_ACTION, false);
  }
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_LEFT, false);
  userInput(ACTION_DOWN, true);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_RIGHT, false);
  userInput(ACTION_DOWN, true);
  for (int i = 0; i < 10; i++) {
    game.field[19][i] = 1;
    game.field[18][i] = 1;
    game.field[17][i] = 1;
  }
  checkGameOver(&game);
  attachTetromino(&game);

  userInput(ACTION_TERMINATE, false);

  freeMemory();
}
END_TEST

Suite *suite_tetris_base() {
  Suite *s = suite_create("suite_tetris_base");
  TCase *tc = tcase_create("tetris_base_tc");

  tcase_add_test(tc, tetris_base_test1);
  tcase_add_test(tc, tetris_base_test2);
  tcase_add_test(tc, tetris_base_test3);
  tcase_add_test(tc, tetris_base_test4);
  tcase_add_test(tc, tetris_base_test5);
  tcase_add_test(tc, tetris_base_test6);

  suite_add_tcase(s, tc);
  return s;
}