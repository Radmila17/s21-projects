#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL) {
    return FAILURE;
  }
  int flag = SUCCESS;
  double epsilon = 0.000000001;
  if ((A->rows != B->rows) || (A->columns != B->columns)) {
    flag = FAILURE;
  }
  int rows = A->rows;
  int columns = A->columns;
  for (int i = 0; i < rows && flag == SUCCESS; i++) {
    for (int j = 0; j < columns && flag == SUCCESS; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > epsilon) {
        flag = FAILURE;
      }
    }
  }
  return flag;
}