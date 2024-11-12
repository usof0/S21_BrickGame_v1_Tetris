#include <ncurses.h>
#include <stdbool.h>
// #include <stdlib.h>

#include "../../brick_game/tetris/tetris.h"
#include "cli.h"

int main(void) {
  initializeInterface();
  initializeGame();
  setState(GAME_START);

  bool running = true;
  while (running) {
    int ch = '\0';
    ch = getch();

    switch (ch) {
      case 27:  // esc
        running = false;
        // freeMemory();
        break;
      case 'r':
      case 'R':
        userInput(ACTION_ACTION, false);
        break;
      case KEY_LEFT:
        userInput(ACTION_LEFT, false);
        break;
      case KEY_RIGHT:
        userInput(ACTION_RIGHT, false);
        break;
      case KEY_DOWN:
        userInput(ACTION_DOWN, false);
        break;
      case ' ':
        userInput(ACTION_PAUSE, false);
        break;
      case '\n':
        userInput(ACTION_START, false);
        break;

      case 'q':
      case 'Q':
        userInput(ACTION_TERMINATE, false);
        break;
      default:
        break;
    }
    renderGame();
  }
  freeMemory();

  cleanupInterface();
  return 0;
}
