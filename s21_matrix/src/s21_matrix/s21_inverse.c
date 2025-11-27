#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || result == NULL || A->rows < 1) {
    return INCORRECT;
  }
  int flag = OK;
  double determinant = 0.0;
  s21_determinant(A, &determinant);
  if ((fabs(determinant) == 0) || A->rows != A->columns)
    flag = CALCULATION_ERROR;
  else {
    if (A->rows == 1) {
      double one_element = 1 / determinant;
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = one_element;
    } else {
      matrix_t compl_mat = {0};
      s21_calc_complements(A, &compl_mat);
      matrix_t transpose_mat = {0};
      s21_transpose(&compl_mat, &transpose_mat);
      s21_remove_matrix(&compl_mat);
      double number = 1.000000 / determinant;
      s21_mult_number(&transpose_mat, number, result);
      s21_remove_matrix(&transpose_mat);
    }
    // s21_print_matrix(*result);
  }
  return flag;
}