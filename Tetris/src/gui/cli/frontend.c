#include "frontend.h"

void gameLoop() {
  GameInfo_t game_info = updateCurrentState();
  drawField(game_info);
  int exit_flag = 0;
  while (exit_flag == 0) {
    bool hold = FALSE;
    timeout(1);
    int c = getch();
    UserAction_t action = handleInput(c);
    if (c != ERR) {
      userInput(action, hold);
    }
    if (action == Terminate) {
      exit_flag = 1;
    } else {
      game_info = updateCurrentState();
      drawField(game_info);
    }
  }
}

void drawField(GameInfo_t game_info) {
  clear();
  mvprintw(0, 0, " ");
  for (int y = 0; y < 10; y++) {
    printw("---");
  }
  for (int x = 0; x < 20; x++) {
    mvprintw(x + 1, 0, "|");
    for (int y = 0; y < 10; y++) {
      if (game_info.field[x][y] == 1) {
        printw("[X]");
      } else {
        printw(" . ");
      }
    }
    printw("|");
  }
  mvprintw(21, 0, " ");
  for (int x = 0; x < 10; x++) {
    printw("---");
  }
  drawInformationBlock(game_info);
  refresh();
}

bool isInitStateOfGame(GameInfo_t game_info) {
  bool return_flag = true;
  for (int x = 0; x < 20; x++) {
    for (int y = 0; y < 10; y++) {
      if (game_info.field[x][y] != 0) {
        return_flag = false;
      }
    }
  }
  return return_flag;
}

bool isGameOver(GameInfo_t game_info, clock_t* last_blocked_time) {
  bool return_flag = false;
  bool top_blocked = false;
  static bool prev_check_line = false;
  if (isLineEmpty(game_info, 0) == false) {
    top_blocked = true;
    prev_check_line = true;
  } else {
    for (int y = 3; y < 7; y++) {
      if (game_info.field[1][y] != 0 && getNextTetraminoHight(game_info) > 1 &&
          prev_check_line == false) {
        top_blocked = true;
      }
    }
    prev_check_line = false;
  }

  if (top_blocked) {
    if (*last_blocked_time == 0) {
      *last_blocked_time = clock();
    } else {
      double seconds = (double)(clock() - *last_blocked_time) / CLOCKS_PER_SEC;
      if (seconds > 1) {
        return_flag = true;
      }
    }
  } else {
    *last_blocked_time = 0;
  }
  return return_flag;
}

int getNextTetraminoHight(GameInfo_t game_info) {
  int hight = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_info.next[i][j] != 0) {
        hight++;
        j = 4;
      }
    }
  }
  return hight;
}

bool isLineEmpty(GameInfo_t game_info, int line) {
  bool return_flag = true;
  for (int j = 0; j < 10 && return_flag == true; j++) {
    if (game_info.field[line][j] != 0) {
      return_flag = false;
    }
  }
  return return_flag;
}

void drawNext(GameInfo_t game_info) {
  int info_y = 35;
  for (int x = 0; x < 4; x++) {
    mvprintw(9 + x, info_y, " ");
    for (int y = 0; y < 4; y++) {
      if (game_info.next[x][y] != 0) {
        printw("[X]");
      } else {
        printw("   ");
      }
    }
  }
}
void drawInformationBlock(GameInfo_t game_info) {
  int info_y = 35;
  static clock_t last_blocked_time = 0;
  mvprintw(2, info_y, "Score:    %d", game_info.score);
  mvprintw(3, info_y, "High score:  %d", game_info.high_score);
  mvprintw(4, info_y, "Speed: %d", game_info.speed);
  mvprintw(5, info_y, "Level: %d", game_info.level);
  mvprintw(6, info_y, "-------------");
  mvprintw(7, info_y, "Next:");
  drawNext(game_info);
  if (isGameOver(game_info, &last_blocked_time) == true) {
    attron(A_BOLD | A_COLOR | A_STANDOUT);
    mvprintw(13, info_y, "GAME OVER");
    attroff(A_BOLD | A_COLOR | A_STANDOUT);
    mvprintw(16, info_y, "or press 'S' to restart");
  } else if (game_info.pause == 1) {
    attron(A_BOLD | A_COLOR | A_STANDOUT);
    mvprintw(13, info_y, "ON PAUSE");
    attroff(A_BOLD | A_COLOR | A_STANDOUT);
    mvprintw(16, info_y, "Press 'P' to continue");
  } else if (isInitStateOfGame(game_info) == 1) {
    attron(A_BOLD | A_COLOR | A_STANDOUT);
    mvprintw(13, info_y, "PRESS 'S' TO START");
    attroff(A_BOLD | A_COLOR | A_STANDOUT);
  } else {
    mvprintw(16, info_y, "Press 'P' to pause");
  }
  mvprintw(15, info_y, "Press 'ESC' to quit the game");
  if (game_info.score > game_info.high_score) {
    attron(A_BOLD);
    mvprintw(18, info_y, "YOU BROKE THE RECORD!");
    attroff(A_BOLD);
  }
}