#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return INCORRECT;
  }
  int flag = OK;
  if ((A->rows != B->rows) || (A->columns != B->columns)) {
    flag = CALCULATION_ERROR;
  } else {
    int rows = A->rows;
    int columns = A->columns;
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return INCORRECT;
  }
  int flag = OK;
  if ((A->rows != B->rows) || (A->columns != B->columns)) {
    flag = CALCULATION_ERROR;
  } else {
    int rows = A->rows;
    int columns = A->columns;
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return flag;
}
