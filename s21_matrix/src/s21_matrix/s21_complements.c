#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows < 1) {
    return INCORRECT;
  }
  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }
  double res_element = 0, sign = 1;
  matrix_t mini_matrix = {0};
  int flag = 0;
  flag = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < result->rows && flag == OK; i++) {
    for (int j = 0; j < result->columns; j++) {
      if ((i + j) % 2 != 0)
        sign = -1;
      else
        sign = 1;
      res_element = 0;
      s21_find_minor(A, &mini_matrix, i, j);
      if (result->rows == 2 && result->columns == 2) {
        res_element = mini_matrix.matrix[0][0];
      } else if (A->rows == 1) {
        res_element = 1;
      } else {
        s21_determinant(&mini_matrix, &res_element);
      }
      result->matrix[i][j] = res_element * sign;
      s21_remove_matrix(&mini_matrix);
    }
  }
  return flag;
}

int s21_find_minor(matrix_t *A, matrix_t *mini_matrix, int i_mat, int j_mat) {
  if (A == NULL || mini_matrix == NULL || A->rows <= 0 || A->columns <= 0 ||
      A->rows != A->columns) {
    return INCORRECT;
  }
  int res_columns = A->columns - 1;
  int res_rows = A->rows - 1;
  int i_res = 0;
  int flag = s21_create_matrix(res_rows, res_columns, mini_matrix);
  for (int i = 0; i < A->rows; i++) {
    int j_res = 0;
    if (i != i_mat) {
      for (int j = 0; j < A->columns; j++) {
        if (j != j_mat) {
          mini_matrix->matrix[i_res][j_res] = A->matrix[i][j];
          j_res++;
        }
      }
      i_res++;
    }
  }
  return flag;
}