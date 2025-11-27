#include "api.h"

#include "backend.h"
UserAction_t handleInput(int c) {
  UserAction_t user_action = Up;
  if (c != ERR) {       //-1
    if (c == KEY_UP) {  // 0403
      user_action = Up;
    } else if (c == START_BUTTON || c == 'S') {  // 115
      user_action = Start;
    } else if (c == PAUSE_BUTTON) {  // 112
      user_action = Pause;
    } else if (c == TERMINATE_BUTTON) {  // 27
      user_action = Terminate;
    } else if (c == KEY_LEFT) {  // 0404
      user_action = Left;
    } else if (c == KEY_RIGHT) {  // 0405
      user_action = Right;
    } else if (c == KEY_UP) {  // 0403
      user_action = Up;
    } else if (c == KEY_DOWN) {  // 0402
      user_action = Down;
    } else if (c == ACTION_BUTTON) {  // 32
      user_action = Action;
    }
  } else {
    shift();
  }
  return user_action;
}

GameInfo_t updateCurrentState() {
  FullGameInfo_t* full_game_info = getFullGameInfo(NULL);
  return *(full_game_info->game_info);
}

void userInput(UserAction_t action, bool hold) {
  FullGameInfo_t* full_game_info = getFullGameInfo(NULL);
  if (hold == true) {
    printf("fkjsfdoijfd\n");
  }
  GameFunc fsm_table[7][8] = {
      {spawn, pauseGame, terminateGame, spawn, spawn, NULL, spawn,
       spawn},  // Init
      {NULL, pauseGame, terminateGame, moveLeft, moveRight, NULL, shiftDown,
       rotate},  // spawn
      {NULL, pauseGame, terminateGame, moveLeft, moveRight, NULL, shiftDown,
       rotate},  // shift
      {NULL, pauseGame, terminateGame, moveLeft, moveRight, NULL, shiftDown,
       rotate},                                                        // move
      {NULL, pauseGame, terminateGame, NULL, NULL, NULL, NULL, NULL},  // rotate
      {NULL, pauseGame, terminateGame, NULL, NULL, NULL, NULL,
       NULL},  // game over
      {initNewGame, NULL, terminateGame, NULL, NULL, NULL, NULL, NULL},
  };

  GameFunc fsm_func = fsm_table[full_game_info->fsm_state][action];
  if (fsm_func != NULL) {
    fsm_func(full_game_info);
  }
};
