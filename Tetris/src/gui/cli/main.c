

#include "frontend.h"

// int main(void) {
//   // init()
//   // startGame()
//   // return
// }

// void startGame() {
//   // init game info
//   // start gameloop
// }

//......

int main(void) {
  initscr();
  curs_set(0);
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  srand(time(NULL));
  nodelay(stdscr, TRUE);
  gameLoop();
  endwin();
  return 0;
}
