#include "fsm.h"

#include <stdio.h>
#include <stdlib.h>

// Define static objects for the current tetromino
static int current_x, current_y;
static Tetromino_t current_tetromino;

// Tetromino shapes
static const int tetromino_shapes[7][4][4] = {
    // I
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // O
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // T
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // S
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // Z
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // J
    {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    // L
    {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

void getNextShape(TetrominoType_t next, int **shape) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      shape[i][j] = tetromino_shapes[next][i][j];
    }
  }
}

void initCurrentTetromino(TetrominoType_t type) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      current_tetromino.body[i][j] = tetromino_shapes[type][i][j];
    }
  }
  current_tetromino.type = type;
  current_tetromino.rotate_state = 0;
}

void spawnTetromino(GameInfo_t *current_game) {
  current_tetromino.type = current_game->next;
  current_tetromino.rotate_state = 0;
  initCurrentTetromino(current_tetromino.type);
  current_x = FIELD_WIDTH / 2 - 1;
  current_y = 0;
  current_game->next = rand() % 7;
}

void moveTetrominoDown(GameInfo_t *current_game, GameState_t *current_state) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_tetromino.body[i][j]) {
        current_game->field[current_y + i][current_x + j] = 0;
      }
    }
  }
  if (!checkCollision(current_game, current_x, current_y + 1)) {
    current_y++;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (current_tetromino.body[i][j]) {
          current_game->field[current_y + i][current_x + j] = 1;
        }
      }
    }
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (current_tetromino.body[i][j]) {
          current_game->field[current_y + i][current_x + j] = 1;
        }
      }
    }
    *current_state = GAME_ATTACH;
  }
}

void moveTetrominoRight(GameInfo_t *current_game) {  ///////
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_tetromino.body[i][j]) {
        current_game->field[current_y + i][current_x + j] = 0;
      }
    }
  }
  if (!checkCollision(current_game, current_x + 1, current_y)) {
    current_x++;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (current_tetromino.body[i][j]) {
          current_game->field[current_y + i][current_x + j] = 1;
        }
      }
    }
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (current_tetromino.body[i][j]) {
          current_game->field[current_y + i][current_x + j] = 1;
        }
      }
    }
  }
}

void moveTetrominoLeft(GameInfo_t *current_game) {  /////////////
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_tetromino.body[i][j]) {
        current_game->field[current_y + i][current_x + j] = 0;
      }
    }
  }
  if (!checkCollision(current_game, current_x - 1, current_y)) {
    current_x--;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (current_tetromino.body[i][j]) {
          current_game->field[current_y + i][current_x + j] = 1;
        }
      }
    }
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (current_tetromino.body[i][j]) {
          current_game->field[current_y + i][current_x + j] = 1;
        }
      }
    }
  }
}

void rotateTetromino(GameInfo_t *current_game) {
  Tetromino_t temp = current_tetromino;
  if (current_tetromino.type == T || current_tetromino.type == L ||
      current_tetromino.type == J) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        current_tetromino.body[i][j] = temp.body[2 - j][i];
      }
    }
  } else if ((current_tetromino.type == I || current_tetromino.type == S ||
              current_tetromino.type == Z) &&
             current_tetromino.rotate_state % 2 == 0) {
    int a = current_tetromino.type == I ? 4 : 3;
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < a; j++) {
        current_tetromino.body[i][j] = temp.body[a - 1 - j][i];
      }
    }
  } else if ((current_tetromino.type == I || current_tetromino.type == S ||
              current_tetromino.type == Z) &&
             current_tetromino.rotate_state % 2 == 1) {
    int a = current_tetromino.type == I ? 4 : 3;
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < a; j++) {
        current_tetromino.body[i][j] = temp.body[j][a - 1 - i];
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp.body[i][j]) {
        current_game->field[current_y + i][current_x + j] = 0;
      }
    }
  }
  if (checkCollision(current_game, current_x, current_y)) {
    current_tetromino = temp;
  } else {
    current_tetromino.rotate_state += 1;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_tetromino.body[i][j]) {
        current_game->field[current_y + i][current_x + j] = 1;
      }
    }
  }
}

void attachTetromino(GameInfo_t *current_game) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_tetromino.body[i][j]) {
        current_game->field[current_y + i][current_x + j] = 1;
      }
    }
  }
  int rows_damaged = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    if (checkRowComplete(current_game, i)) {
      clearRow(current_game, i);
      rows_damaged++;
    }
  }
  if (rows_damaged > 0) {
    current_game->score += updateScore(rows_damaged);
    updateHighScore(current_game);
    updateLevel(current_game);
    updateSpeed(current_game);
  }
}

bool checkRowComplete(GameInfo_t *current_game, int row) {
  bool return_state = true;
  for (int i = 0; i < FIELD_WIDTH; i++) {
    if (current_game->field[row][i] == 0) {
      return_state = false;
    }
  }
  return return_state;
}

void clearRow(GameInfo_t *current_game, int row) {
  for (int i = row; i > 0; i--) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      current_game->field[i][j] = current_game->field[i - 1][j];
    }
  }
  for (int j = 0; j < FIELD_WIDTH; j++) {
    current_game->field[0][j] = 0;
  }
}

bool checkGameOver(GameInfo_t *current_game) {
  bool return_state = false;
  for (int i = 0; i < FIELD_WIDTH; i++) {
    if (current_game->field[0][i] != 0) {
      return_state = true;
    }
  }
  return return_state;
}

// Function to handle user input during the game
void handleUserInput(GameInfo_t *current_game, GameState_t *current_state,
                     UserAction_t action) {
  switch (action) {
    case ACTION_LEFT:
      moveTetrominoLeft(current_game);
      break;
    case ACTION_RIGHT:
      moveTetrominoRight(current_game);
      break;
    case ACTION_DOWN:
      moveTetrominoDown(current_game, current_state);
      break;
    case ACTION_ACTION:
      rotateTetromino(current_game);
      break;
    default:
      break;
  }
}

// Function to check for collisions
bool checkCollision(GameInfo_t *current_game, int x, int y) {
  bool return_state = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (current_tetromino.body[i][j]) {
        if (y + i >= FIELD_HEIGHT || x + j < 0 || x + j >= FIELD_WIDTH) {
          return_state = true;
        } else if (current_game->field[y + i][x + j]) {
          return_state = true;
        }
      }
    }
  }

  return return_state;
}

int updateScore(int rows_damaged) {
  int score = 0;
  const int scores[4] = {100, 300, 700, 1500};
  if (rows_damaged < 5)
    score = scores[rows_damaged - 1];
  else
    score = 1500;
  return score;
}

void updateHighScore(GameInfo_t *game) {
  if (game == NULL) return;
  int high_score = 0;
  FILE *file;
  file = fopen("db/high_score.txt", "r");
  if (file == NULL) {
    game->high_score = game->score;
  } else {
    if (fscanf(file, "%d", &high_score) != 1) {
      game->high_score = game->score;
    } else {
      game->high_score = high_score > game->score ? high_score : game->score;
    }
    fclose(file);
  }

  file = fopen("db/high_score.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d", game->high_score);
    fclose(file);
  }
}

void updateLevel(GameInfo_t *game) {
  if (game == NULL) return;
  if (game->score >= 600 && game->level < 10) {
    game->level = game->score / 600 + 1;
  }
}

void updateSpeed(GameInfo_t *game) {
  if (game == NULL) return;
  int speed = 0;
  speed = 500 - game->level * 50;
  game->speed = speed;
}
