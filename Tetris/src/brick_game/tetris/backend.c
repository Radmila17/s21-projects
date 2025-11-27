#include "backend.h"

void shift() {
  clock_t last_time = clock();
  FullGameInfo_t *full_game_info = getFullGameInfo(NULL);
  double fall_time = calculateFallInterval(full_game_info);
  if ((double)(last_time - full_game_info->time_stamp) / CLOCKS_PER_SEC >=
      fall_time) {
    if (full_game_info->fsm_state == Shifting ||
        full_game_info->fsm_state == Moving) {
      shiftDown(full_game_info);
    }
    full_game_info->time_stamp = last_time;
  }
}

double calculateFallInterval(FullGameInfo_t *full_game_info) {
  const double fall_times[] = {0.34, 0.32, 0.30, 0.27, 0.24,
                               0.21, 0.17, 0.13, 0.09, 0.05};
  // double fall_time =
  //     pow((0.8 - ((full_game_info->game_info->level - 1) * 0.007)),
  //         full_game_info->game_info->level - 1) -
  //     0.1;
  return fall_times[full_game_info->game_info->level - 1];
}

void spawn(FullGameInfo_t *full_game_info) {
  full_game_info->fsm_state = Spawn;
  if (full_game_info->game_info->pause == false) {
    fillMatrixWithZeros(TETRAMINO_SIZE, TETRAMINO_SIZE,
                        &full_game_info->cur_tetramino.field);
    copyNextToCurrentTetramino(full_game_info);
    full_game_info->cur_tetramino.x_coord = 0;
    full_game_info->cur_tetramino.y_coord = 3;
    if (checkCollision(*full_game_info, full_game_info->cur_tetramino.x_coord,
                       full_game_info->cur_tetramino.y_coord) == ERR) {
      full_game_info->fsm_state = GameOver;
      // full_game_info->game_info->pause = true;
    } else if (checkAttaching(*full_game_info) == OK) {
      full_game_info->fsm_state = Attaching;
      attach(full_game_info);
    } else {
      placeTetraminoOnField(full_game_info);
      full_game_info->fsm_state = Shifting;
    }
    fillMatrixWithZeros(TETRAMINO_SIZE, TETRAMINO_SIZE,
                        &(full_game_info->game_info->next));
    full_game_info->next_piece_type =
        createNextTetramino(full_game_info->game_info);
  }
}

void shiftDown(FullGameInfo_t *full_game_info) {
  full_game_info->fsm_state = Shifting;
  if (full_game_info->game_info->pause == false) {
    clearTetraminoTrail(full_game_info, full_game_info->cur_tetramino.x_coord,
                        full_game_info->cur_tetramino.y_coord);
    if (checkCollision(*full_game_info,
                       full_game_info->cur_tetramino.x_coord + 1,
                       full_game_info->cur_tetramino.y_coord) != ERR) {
      full_game_info->cur_tetramino.x_coord++;
      placeTetraminoOnField(full_game_info);
    } else {
      full_game_info->fsm_state = Attaching;
      attach(full_game_info);
    }
    full_game_info->time_stamp = clock();
  }
}

// void fastShiftDown(FullGameInfo_t *full_game_info) {
//   full_game_info->fsm_state = Shifting;
//   if (full_game_info->game_info->pause == false) {
//     clearTetraminoTrail(full_game_info,
//     full_game_info->cur_tetramino.x_coord,
//                         full_game_info->cur_tetramino.y_coord);
//     while (checkCollision(*full_game_info,
//                           full_game_info->cur_tetramino.x_coord + 1,
//                           full_game_info->cur_tetramino.y_coord) != ERR) {
//       full_game_info->cur_tetramino.x_coord++;
//     }
//     placeTetraminoOnField(full_game_info);
//     full_game_info->fsm_state = Attaching;
//     attach(full_game_info);
//   }
// }

int checkAttaching(FullGameInfo_t full_game_info) {
  int exit_flag = ERR;
  int next_x_coord = full_game_info.cur_tetramino.x_coord + 1;
  if (checkCollision(full_game_info, next_x_coord,
                     full_game_info.cur_tetramino.y_coord) == ERR) {
    exit_flag = OK;
  }
  return exit_flag;
}

void attach(FullGameInfo_t *full_game_info) {
  full_game_info->fsm_state = Attaching;
  placeTetraminoOnField(full_game_info);
  if (full_game_info->game_info->pause == false) {
    FilledRows_t filled_rows = {0};
    if (checkFilledRows(&filled_rows, *full_game_info) == true) {
      removeFilledRows(full_game_info, filled_rows);
    }
    if (full_game_info->cur_tetramino.x_coord == 0) {
      full_game_info->fsm_state = GameOver;
    } else {
      full_game_info->fsm_state = Spawn;
      spawn(full_game_info);
    }
  }
}

void removeFilledRows(FullGameInfo_t *full_game_info,
                      FilledRows_t filled_rows) {
  for (int array_num = 0; array_num < filled_rows.count; array_num++) {
    for (int y_col = 0; y_col < FIELD_WIDTH; y_col++) {
      int filled_row_num = filled_rows.array[array_num];
      for (int i = filled_row_num; i > 0; i--) {
        full_game_info->game_info->field[i][y_col] =
            full_game_info->game_info->field[i - 1][y_col];
      }
    }
  }
  switch (filled_rows.count) {
    case 1:
      full_game_info->game_info->score += 100;
      break;
    case 2:
      full_game_info->game_info->score += 300;
      break;
    case 3:
      full_game_info->game_info->score += 700;
      break;
    case 4:
      full_game_info->game_info->score += 1500;
      break;
  }
  if (full_game_info->game_info->level < 10) {
    full_game_info->game_info->level =
        full_game_info->game_info->score / 600 + 1;
    if (full_game_info->game_info->level > 10) {
      full_game_info->game_info->level = 10;
    }
    double fall_time = calculateFallInterval(full_game_info);
    full_game_info->game_info->speed = (1 / fall_time) * 60;
  }
  if (full_game_info->game_info->score >
      full_game_info->game_info->high_score) {
    writeHightScore(full_game_info->game_info);
  }
}

// void calculateSpeed( FullGameInfo_t *full_game_info ){
//       double fall_time = calculateFallInterval(full_game_info);
//     full_game_info->game_info->speed = (1 / fall_time) * 60;
// }

void writeHightScore(GameInfo_t *game_info) {
  FILE *fptr = fopen("tetris_high_scores.dat", "wb");  // 7800
  fwrite(&game_info->score, sizeof(int), 1, fptr);
  fclose(fptr);
}

int checkHightScore() {
  FILE *fptr = fopen("tetris_high_scores.dat", "rb");
  int hight_score = 0;
  if (fptr == NULL) {
    fptr = fopen("tetris_high_scores.dat", "wb");
    if (fptr != NULL) {
      fwrite(&hight_score, sizeof(int), 1, fptr);
      fclose(fptr);
    }
  } else {
    fread(&hight_score, sizeof(int), 1, fptr);
    fclose(fptr);
  }
  return hight_score;
}

bool checkFilledRows(FilledRows_t *filled_rows, FullGameInfo_t full_game_info) {
  filled_rows->count = 0;
  bool return_code = false;
  for (int x_row = 0; x_row < FIELD_HEIGHT; x_row++) {
    bool is_filled = true;
    for (int y_col = 0; y_col < FIELD_WIDTH; y_col++) {
      if (full_game_info.game_info->field[x_row][y_col] == 0) {
        is_filled = false;
        y_col = FIELD_WIDTH;
      }
    }
    if (is_filled == true) {
      return_code = true;
      filled_rows->array[filled_rows->count] = x_row;
      filled_rows->count++;
    }
  }
  return return_code;
}

void placeTetraminoOnField(FullGameInfo_t *full_game_info) {
  int start_x = full_game_info->cur_tetramino.x_coord;
  int start_y = full_game_info->cur_tetramino.y_coord;
  for (int i = 0; i < TETRAMINO_SIZE; i++) {
    for (int j = 0; j < TETRAMINO_SIZE; j++) {
      if (full_game_info->cur_tetramino.field[i][j] == 1) {
        full_game_info->game_info->field[i + start_x][j + start_y] = 1;
      }
    }
  }
}
void clearTetraminoTrail(FullGameInfo_t *full_game_info, int prev_x,
                         int prev_y) {
  for (int i = 0; i < TETRAMINO_SIZE; i++) {
    for (int j = 0; j < TETRAMINO_SIZE; j++) {
      if (full_game_info->cur_tetramino.field[i][j] == 1) {
        full_game_info->game_info->field[i + prev_x][j + prev_y] = 0;
      }
    }
  }
}

int checkCollision(FullGameInfo_t full_game_info, int x_coord, int y_coord) {
  int return_code = OK;
  for (int tetr_x = 0; tetr_x < TETRAMINO_SIZE && return_code == OK; tetr_x++) {
    for (int tetr_y = 0; tetr_y < TETRAMINO_SIZE && return_code == OK;
         tetr_y++) {
      int field_x = tetr_x + x_coord;
      int field_y = tetr_y + y_coord;
      if (full_game_info.cur_tetramino.field[tetr_x][tetr_y] == 1) {
        if (field_x >= FIELD_HEIGHT || field_y >= FIELD_WIDTH || field_y < 0 ||
            full_game_info.game_info->field[field_x][field_y] == 1) {
          return_code = ERR;
        }
      }
    }
  }
  return return_code;
}

void terminateGame(FullGameInfo_t *full_game_info) {
  full_game_info->fsm_state = GameOver;
  if (full_game_info->cur_tetramino.field != NULL) {
    removeMatrix(&(full_game_info->cur_tetramino.field), TETRAMINO_SIZE);
  }
  if (full_game_info->game_info->field != NULL) {
    removeMatrix(&(full_game_info->game_info->field), FIELD_HEIGHT);
  }
  if (full_game_info->game_info->next != NULL) {
    removeMatrix(&(full_game_info->game_info->next), TETRAMINO_SIZE);
  }
  free(full_game_info->game_info);
  free(full_game_info);
}

void pauseGame(FullGameInfo_t *full_game_info) {
  static FSM_t previos_state;
  if (full_game_info->game_info->pause == false) {
    previos_state = full_game_info->fsm_state;
    full_game_info->game_info->pause = true;
    full_game_info->fsm_state = OnPause;
  } else {
    full_game_info->game_info->pause = false;
    full_game_info->fsm_state = previos_state;
    full_game_info->time_stamp = clock();
  }
}

void moveLeft(FullGameInfo_t *full_game_info) {
  if (full_game_info->game_info->pause == false) {
    int next_y = full_game_info->cur_tetramino.y_coord - 1;
    clearTetraminoTrail(full_game_info, full_game_info->cur_tetramino.x_coord,
                        full_game_info->cur_tetramino.y_coord);
    if (checkCollision(*full_game_info, full_game_info->cur_tetramino.x_coord,
                       next_y) != ERR) {
      full_game_info->cur_tetramino.y_coord = next_y;
      full_game_info->fsm_state = Shifting;
    }
    placeTetraminoOnField(full_game_info);
  }
}

void moveRight(FullGameInfo_t *full_game_info) {
  if (full_game_info->game_info->pause == false) {
    int next_y = full_game_info->cur_tetramino.y_coord + 1;
    clearTetraminoTrail(full_game_info, full_game_info->cur_tetramino.x_coord,
                        full_game_info->cur_tetramino.y_coord);
    if (checkCollision(*full_game_info, full_game_info->cur_tetramino.x_coord,
                       next_y) != ERR) {
      full_game_info->cur_tetramino.y_coord = next_y;
      full_game_info->fsm_state = Shifting;
    }
    placeTetraminoOnField(full_game_info);
  }
}

void rotate(FullGameInfo_t *full_game_info) {
  if (full_game_info->game_info->pause == false &&
      full_game_info->cur_tetramino.piece_type != O) {
    int **temp_matrix;
    allocateMatrix(TETRAMINO_SIZE, TETRAMINO_SIZE, &temp_matrix);
    for (int i = 0; i < TETRAMINO_SIZE; i++) {
      for (int j = 0; j < TETRAMINO_SIZE; j++) {
        temp_matrix[i][j] = full_game_info->cur_tetramino.field[i][j];
      }
    }
    bool clockwise = true;
    clearTetraminoTrail(full_game_info, full_game_info->cur_tetramino.x_coord,
                        full_game_info->cur_tetramino.y_coord);
    rotateFigure(full_game_info, clockwise, temp_matrix);
    if (checkCollision(*full_game_info, full_game_info->cur_tetramino.x_coord,
                       full_game_info->cur_tetramino.y_coord) == OK) {
      placeTetraminoOnField(full_game_info);
    } else {
      clockwise = false;
      rotateFigure(full_game_info, clockwise, temp_matrix);
      placeTetraminoOnField(full_game_info);
    }
    removeMatrix(&temp_matrix, TETRAMINO_SIZE);
  }
}

void rotateFigure(FullGameInfo_t *full_game_info, bool clockwise,
                  int **temp_matrix) {
  for (int i = 0; i < TETRAMINO_SIZE; i++) {
    for (int j = 0; j < TETRAMINO_SIZE; j++) {
      if (clockwise == true) {
        full_game_info->cur_tetramino.field[j][i] =
            temp_matrix[TETRAMINO_SIZE - i - 1][j];
      } else {
        full_game_info->cur_tetramino.field[i][j] = temp_matrix[i][j];
      }
    }
  }
  normilizeTetraminoOffset(full_game_info);
}

void normilizeTetraminoOffset(FullGameInfo_t *full_game_info) {
  int count_empty_x = 0;
  int count_empty_y = 0;
  int exit_flag = 0;
  bool is_empty_x = true;
  for (int i = 0; i < TETRAMINO_SIZE && is_empty_x == true; i++) {
    for (int j = 0; j < TETRAMINO_SIZE && is_empty_x == true; j++) {
      if (full_game_info->cur_tetramino.field[i][j] != 0) {
        is_empty_x = false;
        count_empty_x = i;
      }
    }
  }
  bool is_empty_y = true;
  for (int j = 0; j < TETRAMINO_SIZE && is_empty_y == true; j++) {
    for (int i = 0; i < TETRAMINO_SIZE && is_empty_y == true; i++) {
      if (full_game_info->cur_tetramino.field[i][j] != 0) {
        is_empty_y = false;
        count_empty_y = j;
      }
    }
  }
  if (count_empty_x == 0 && count_empty_y == 0) {
    exit_flag = 1;
  }
  if (exit_flag == 0) {
    int temp[TETRAMINO_SIZE][TETRAMINO_SIZE] = {0};

    for (int i = count_empty_x; i < TETRAMINO_SIZE; i++) {
      for (int j = count_empty_y; j < TETRAMINO_SIZE; j++) {
        temp[i - count_empty_x][j - count_empty_y] =
            full_game_info->cur_tetramino.field[i][j];
      }
    }
    for (int i = 0; i < TETRAMINO_SIZE; i++) {
      for (int j = 0; j < TETRAMINO_SIZE; j++) {
        full_game_info->cur_tetramino.field[i][j] = temp[i][j];
      }
    }
  }
}

TetraminoType_t createNextTetramino(GameInfo_t *game_info) {
  fillMatrixWithZeros(4, 4, &game_info->next);
  TetraminoType_t type = rand() % 7;
  if (type == I) {
    game_info->next[0][0] = game_info->next[0][1] = game_info->next[0][2] =
        game_info->next[0][3] = 1;
  } else if (type == L) {
    game_info->next[0][0] = game_info->next[1][0] = game_info->next[1][1] =
        game_info->next[1][2] = 1;
  } else if (type == J) {
    game_info->next[0][2] = game_info->next[1][2] = game_info->next[1][1] =
        game_info->next[1][0] = 1;
  } else if (type == O) {
    game_info->next[0][0] = game_info->next[0][1] = game_info->next[1][0] =
        game_info->next[1][1] = 1;
  } else if (type == Z) {
    game_info->next[0][0] = game_info->next[0][1] = game_info->next[1][1] =
        game_info->next[1][2] = 1;
  } else if (type == S) {
    game_info->next[0][2] = game_info->next[0][1] = game_info->next[1][1] =
        game_info->next[1][0] = 1;
  } else if (type == T) {
    game_info->next[0][1] = game_info->next[1][0] = game_info->next[1][1] =
        game_info->next[1][2] = 1;
  }
  return type;
}

int allocateMatrix(int rows, int columns, int ***result) {
  int flag = OK;
  *result = (int **)calloc(rows, sizeof(int *));
  if (*result != NULL) {
    for (int i = 0; i < rows && flag == OK; i++) {
      (*result)[i] = (int *)calloc(columns, sizeof(int));
      if ((*result)[i] == NULL) {
        removeMatrix(result, rows);
        flag = ERR;
      }
    }
  } else {
    flag = ERR;
  }
  return flag;
}

void removeMatrix(int ***matrix, int rows) {
  if (*matrix != NULL) {
    for (int i = 0; i < rows; i++) {
      free((*matrix)[i]);
      (*matrix)[i] = NULL;
    }
    free(*matrix);
    *matrix = NULL;
  }
}

void copyNextToCurrentTetramino(FullGameInfo_t *full_game_info) {
  if (full_game_info->game_info->next != NULL &&
      (full_game_info->cur_tetramino.field != NULL)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        full_game_info->cur_tetramino.field[i][j] =
            full_game_info->game_info->next[i][j];
      }
    }
    full_game_info->cur_tetramino.piece_type = full_game_info->next_piece_type;
  }
}

void fillMatrixWithZeros(int rows, int columns, int ***matrix) {
  if (*matrix != NULL) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        (*matrix)[i][j] = 0;
      }
    }
  }
}

FullGameInfo_t *initializeFullGameInfo(FullGameInfo_t *full_game_info) {
  if (full_game_info == NULL) {
    full_game_info = calloc(1, sizeof(FullGameInfo_t));
  }
  full_game_info->fsm_state = Init;
  full_game_info->time_stamp = clock();
  full_game_info->game_info = initGameInfo(full_game_info->game_info);
  if (full_game_info->cur_tetramino.field == NULL) {
    allocateMatrix(4, 4, &(full_game_info->cur_tetramino.field));
  }
  fillMatrixWithZeros(TETRAMINO_SIZE, TETRAMINO_SIZE,
                      &(full_game_info->cur_tetramino.field));
  full_game_info->next_piece_type =
      createNextTetramino(full_game_info->game_info);
  return full_game_info;
}

GameInfo_t *initGameInfo(GameInfo_t *game_info) {
  if (game_info == NULL) {
    game_info = calloc(1, sizeof(GameInfo_t));
  }
  (*game_info).score = 0;
  game_info->high_score = checkHightScore();
  (*game_info).level = 1;
  game_info->speed = 176;
  (*game_info).pause = false;
  if (game_info->field == NULL) {
    allocateMatrix(FIELD_HEIGHT, FIELD_WIDTH, &(game_info->field));
  }
  if (game_info->next == NULL) {
    allocateMatrix(TETRAMINO_SIZE, TETRAMINO_SIZE, &(game_info->next));
  }

  fillMatrixWithZeros(FIELD_HEIGHT, FIELD_WIDTH, &(game_info->field));
  fillMatrixWithZeros(TETRAMINO_SIZE, TETRAMINO_SIZE, &(game_info->next));
  return game_info;
}

FullGameInfo_t *getFullGameInfo(FullGameInfo_t *current_full_game_info) {
  static FullGameInfo_t *full_game_info;
  if (full_game_info == NULL) {
    full_game_info = initializeFullGameInfo(full_game_info);
  }
  if (current_full_game_info != NULL) {
    full_game_info = current_full_game_info;
  }
  return full_game_info;
}
void initNewGame(FullGameInfo_t *full_game_info) {
  initializeFullGameInfo(full_game_info);
}
