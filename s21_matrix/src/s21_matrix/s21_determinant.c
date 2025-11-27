#include "../s21_matrix.h"

double s21_find_determinant(matrix_t *mini_matrix) {
  double mini_determinant = 0.0;
  if (mini_matrix->rows == 1.0) {
    mini_determinant = mini_matrix->matrix[0][0];
  } else if (mini_matrix->rows == 0.0) {
    mini_determinant = 1.0;
  } else {
    mini_determinant = mini_matrix->matrix[0][0] * mini_matrix->matrix[1][1] -
                       mini_matrix->matrix[0][1] * mini_matrix->matrix[1][0];
  }

  return mini_determinant;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || result == NULL || A->rows < 0 || A->columns < 0) {
    return INCORRECT;
  }
  *result = 0.0;
  int flag = OK;
  if (A->rows != A->columns) {
    flag = CALCULATION_ERROR;
  } else if (A->columns <= 2) {
    *result = s21_find_determinant(A);
  } else {
    matrix_t mini_matrix = {0};
    int i = 0;
    for (int j = 0; j < A->columns && flag == OK; j++) {
      flag = s21_find_minor(A, &mini_matrix, i, j);
      double sign = ((i + j) % 2) != 0 ? -1.0 : 1.0;
      if (mini_matrix.rows == 2 && mini_matrix.columns == 2 && flag == OK) {
        double minor = s21_find_determinant(&mini_matrix);
        *result += A->matrix[i][j] * minor * sign;
        s21_remove_matrix(&mini_matrix);
      } else {
        double mini_determinant = 0;
        s21_determinant(&mini_matrix, &mini_determinant);
        *result += sign * A->matrix[i][j] * mini_determinant;
        s21_remove_matrix(&mini_matrix);
      }
    }
  }
  return flag;
}