#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return INCORRECT;
  }
  int flag = OK;
  int rows = A->rows, columns = A->columns;
  s21_create_matrix(rows, columns, result);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return INCORRECT;
  }
  int flag = OK;
  int res_rows = 0, res_columns = 0;
  if (A->columns != B->rows) {
    flag = CALCULATION_ERROR;
  }
  if (flag == OK) {
    res_rows = A->rows;
    res_columns = B->columns;
    s21_create_matrix(res_rows, res_columns, result);
  }
  for (int i = 0; i < res_rows && flag == OK; i++) {
    for (int j = 0; j < res_columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return flag;
}