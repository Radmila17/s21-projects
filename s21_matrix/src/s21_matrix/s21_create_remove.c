#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    return INCORRECT;
  }
  int flag = OK;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    flag = INCORRECT;
  } else {
    for (int i = 0; i < rows && flag == 0; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        result->rows = i;
        s21_remove_matrix(result);
        flag = INCORRECT;
      }
      result->rows = rows;
      result->columns = columns;
    }
  }
  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}

void s21_filling_matrix(matrix_t *result, double start, double step) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = start;
      start += step;
    }
  }
}
/*
void s21_print_matrix(matrix_t result) {
  int rows = result.rows;
  int columns = result.columns;
  printf("\n");
  printf("Matrix:\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%f ", result.matrix[i][j]);
    }
    printf("\n");
  }
}
*/