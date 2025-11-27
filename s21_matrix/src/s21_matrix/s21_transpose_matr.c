#include "../s21_matrix.h"
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    return INCORRECT;
  }
  int res_rows = A->columns;
  int res_columns = A->rows;
  int flag = s21_create_matrix(res_rows, res_columns, result);
  for (int i = 0; i < res_rows && flag == OK; i++) {
    for (int j = 0; j < res_columns; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return flag;
}
