#include <check.h>
#include <stdlib.h>

#include "../brick_game/tetris/api.h"
#include "../brick_game/tetris/backend.h"
#include "../gui/cli/frontend.h"

START_TEST(test_game_info_initialization) {
  GameInfo_t game_info = updateCurrentState();
  ck_assert_int_eq(game_info.score, 0);
  ck_assert_int_eq(game_info.level, 1);
  ck_assert_int_eq(game_info.pause, 0);
  ck_assert_ptr_nonnull(game_info.field);
  ck_assert_ptr_nonnull(game_info.next);
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_full_game_info_initialization) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  ck_assert_ptr_nonnull(full_game);
  ck_assert_ptr_nonnull(full_game->game_info);
  ck_assert_int_eq(full_game->fsm_state, Init);

  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_user_input_actions) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  userInput(Left, 0);
  userInput(Right, 0);
  userInput(Up, 0);
  userInput(Down, 0);
  userInput(Action, 0);
  userInput(Pause, 0);
  ck_assert_int_ne(full_game->fsm_state, GameOver);
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_tetramino_operations) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);

  TetraminoType_t type = full_game->next_piece_type;
  copyNextToCurrentTetramino(full_game);
  ck_assert_int_eq(full_game->cur_tetramino.piece_type, type);

  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_movement_functions) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);

  int initial_y = full_game->cur_tetramino.y_coord;
  moveLeft(full_game);
  ck_assert_int_eq(full_game->cur_tetramino.y_coord, initial_y - 1);

  moveRight(full_game);
  ck_assert_int_eq(full_game->cur_tetramino.y_coord, initial_y);
  rotate(full_game);
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_fsm_states) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  full_game->fsm_state = Spawn;
  spawn(full_game);
  ck_assert_int_eq(full_game->fsm_state, Shifting);
  shiftDown(full_game);
  full_game->fsm_state = Attaching;
  attach(full_game);
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_game_control_functions) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  pauseGame(full_game);
  ck_assert_int_eq(full_game->game_info->pause, 1);
  pauseGame(full_game);
  ck_assert_int_eq(full_game->game_info->pause, 0);
  terminateGame(full_game);
}
END_TEST

START_TEST(test_score_and_level_functions) {
  int high_score = checkHightScore();
  ck_assert_int_ge(high_score, 0);

  GameInfo_t game_info;
  game_info.score = 1000;
  game_info.high_score = 500;
  writeHightScore(&game_info);
  ck_assert_int_ge(game_info.high_score, 500);
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_utility_functions) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  double interval = calculateFallInterval(full_game);
  ck_assert_float_gt(interval, 0.0);
  ck_assert_float_lt(interval, 2.0);
  FilledRows_t filled_rows;
  bool has_filled = checkFilledRows(&filled_rows, *full_game);
  ck_assert_int_eq(has_filled, false);
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_valid_inputs) {
  ck_assert_int_eq(handleInput(KEY_UP), Up);
  ck_assert_int_eq(handleInput(KEY_DOWN), Down);
  ck_assert_int_eq(handleInput(KEY_LEFT), Left);
  ck_assert_int_eq(handleInput(KEY_RIGHT), Right);
  ck_assert_int_eq(handleInput(START_BUTTON), Start);
  ck_assert_int_eq(handleInput('S'), Start);
  ck_assert_int_eq(handleInput(PAUSE_BUTTON), Pause);
  ck_assert_int_eq(handleInput(TERMINATE_BUTTON), Terminate);
  ck_assert_int_eq(handleInput(ACTION_BUTTON), Action);
}
END_TEST

START_TEST(test_shift) {
  shift();
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_shift_shifting) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  shift();
  timeout(10);
  full_game->fsm_state = Shifting;
  shift();
  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_remove_single_filled_row) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  FilledRows_t filled_rows;
  filled_rows.count = 1;
  filled_rows.array[0] = 18;
  for (int y = 0; y < FIELD_WIDTH; y++) {
    full_game->game_info->field[18][y] = 1;
  }
  full_game->game_info->field[17][3] = 1;
  full_game->game_info->field[17][7] = 1;
  int initial_score = full_game->game_info->score;
  removeFilledRows(full_game, filled_rows);
  ck_assert_int_eq(full_game->game_info->score, initial_score + 100);
  for (int y = 0; y < FIELD_WIDTH; y++) {
    ck_assert_int_eq(full_game->game_info->field[19][y], 0);
  }
  ck_assert_int_eq(full_game->game_info->field[18][3], 1);
  ck_assert_int_eq(full_game->game_info->field[18][7], 1);

  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_multiple_filled_rows) {
  FullGameInfo_t *full_game = getFullGameInfo(NULL);
  FilledRows_t filled_rows;
  filled_rows.count = 2;
  filled_rows.array[0] = 18;
  filled_rows.array[1] = 19;

  for (int row = 18; row <= 19; row++) {
    for (int y = 0; y < FIELD_WIDTH; y++) {
      full_game->game_info->field[row][y] = 1;
    }
  }
  int initial_score = full_game->game_info->score;
  removeFilledRows(full_game, filled_rows);
  ck_assert_int_eq(full_game->game_info->score, initial_score + 300);
  for (int row = 18; row <= 19; row++) {
    for (int y = 0; y < FIELD_WIDTH; y++) {
      ck_assert_int_eq(full_game->game_info->field[row][y], 0);
    }
  }

  userInput(Terminate, 0);
}
END_TEST

START_TEST(test_shapes) {
  GameInfo_t game_info = updateCurrentState(NULL);
  for (int i = 0; i < 100; i++) {
    TetraminoType_t type = createNextTetramino(&game_info);
    ck_assert_int_ge(type, I);
    ck_assert_int_le(type, Z);
  }
  userInput(Terminate, 0);
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_game_info_initialization);
  tcase_add_test(tc_core, test_full_game_info_initialization);
  tcase_add_test(tc_core, test_user_input_actions);
  tcase_add_test(tc_core, test_tetramino_operations);
  tcase_add_test(tc_core, test_movement_functions);
  tcase_add_test(tc_core, test_fsm_states);
  tcase_add_test(tc_core, test_game_control_functions);
  tcase_add_test(tc_core, test_score_and_level_functions);
  tcase_add_test(tc_core, test_utility_functions);
  tcase_add_test(tc_core, test_valid_inputs);
  tcase_add_test(tc_core, test_shift);
  tcase_add_test(tc_core, test_shift_shifting);
  tcase_add_test(tc_core, test_remove_single_filled_row);
  tcase_add_test(tc_core, test_multiple_filled_rows);
  tcase_add_test(tc_core, test_shapes);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = tetris_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}