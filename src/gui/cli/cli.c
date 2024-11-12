#include "cli.h"

#include <ncurses.h>
#include <stdlib.h>

// #include "./../../brick_game/tetris/fsm.h"

// Initialize the ncurses interface
void initializeInterface(void) {
  initscr();
  noecho();
  cbreak();
  timeout(500);
  keypad(stdscr, TRUE);
  curs_set(FALSE);
  start_color();
}

void renderGame() {
  GameInfo_t game_info = updateCurrentState();
  timeout(game_info.speed);
  clear();

  ///////////// display game field
  for (int i = 1; i < FIELD_HEIGHT + 1; i++) {
    mvprintw(i, 1, "|");
    mvprintw(i, (FIELD_WIDTH + 1) * 2, "|");
    mvprintw(i, FIELD_WIDTH * 2 + 17, "|");
  }
  for (int j = 1; j < FIELD_WIDTH * 2 + 18; j++) {
    mvprintw(0, j, "_");
    mvprintw(21, j, "-");
  }
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (game_info.field[i][j]) {
        mvprintw(i + 1, (j + 1) * 2, "[]");
        attroff(COLOR_PAIR(2));
      } else {
        mvprintw(i + 1, (j + 1) * 2, " .");
      }
    }
  }
  if (game_info.pause) displayPause();
  if (getCurrentState() == GAME_OVER) displayGameOver(game_info);
  if (getCurrentState() == GAME_START) displayStartGame();
  displayInformation(game_info);
  displayDirections();
}

void displayInformation(GameInfo_t game_info) {
  //////////// display next block
  int **next = (int **)calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    next[i] = (int *)calloc(4, sizeof(int));
  }
  getNextBlock(next);
  mvprintw(1, 23, "-----next-----");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (next[i][j]) {
        mvprintw(i + 3, (j + 13) * 2, "[]");
        attroff(COLOR_PAIR(2));
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    free(next[i]);
  }
  free(next);
  mvprintw(7, 23, "--------------");
  mvprintw(9, 12 * 2, "level: %d", game_info.level);
  mvprintw(11, 12 * 2, "speed: 1/%d", game_info.speed);
  mvprintw(13, 12 * 2, "score: %d", game_info.score);
  mvprintw(15, 12 * 2, "high score");
  mvprintw(17, 12 * 2, ": %d", game_info.high_score);
  mvprintw(18, 23, "----control---");
  mvprintw(19, 23, "  R & Arrows  ");
  mvprintw(20, 23, "     keys     ");
}

void displayDirections() {
  mvprintw(1, 39, "============Directions===========");
  mvprintw(3, 39, " Start new game ---> Enter       ");
  mvprintw(4, 39, " End the game -----> Q         ");
  mvprintw(5, 39, " Pause the game ---> Spase       ");
  mvprintw(6, 39, " Move left --------> Left arrow  ");
  mvprintw(7, 39, " Move right -------> Right arrow ");
  mvprintw(8, 39, " Accelerate -------> Down arrow  ");
  mvprintw(9, 39, " Rotate the piece -> R           ");
  mvprintw(10, 39, " Quit -------------> ESC          ");
}

void displayStartGame() {
  mvprintw(7, 5, "               ");
  mvprintw(8, 5, "     press     ");
  mvprintw(9, 5, "    'Enter'    ");
  mvprintw(10, 5, " to start game ");
  mvprintw(12, 5, "    or 'Q'     ");
  mvprintw(13, 5, "   to quit!    ");
  mvprintw(14, 5, "               ");
  mvprintw(11, 5, "               ");
}

void displayPause() {
  mvprintw(7, 5, "               ");
  mvprintw(8, 5, "     press     ");
  mvprintw(9, 5, "    'spase'    ");
  mvprintw(10, 5, "  to continue  ");
  mvprintw(11, 5, "               ");
}

void displayGameOver(GameInfo_t game) {
  mvprintw(7, 5, "               ");
  mvprintw(8, 5, "  Game Over!   ");
  mvprintw(9, 5, "  Score: %d  ", game.score);
  mvprintw(10, 5, "  Level: %d     ", game.level);
  mvprintw(11, 5, "               ");
}
// Cleanup the ncurses interface
void cleanupInterface(void) { endwin(); }
