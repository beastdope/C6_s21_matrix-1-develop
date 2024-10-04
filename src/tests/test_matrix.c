#include <check.h>

#include "../s21_matrix.h"

void s21_init_matrix(double number, matrix_t *A) {
  for (int x = 0; x < A->rows; x += 1) {
    for (int y = 0; y < A->columns; number += 1.0, y += 1)
      A->matrix[x][y] = number;
  }
}

START_TEST(s21_create_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_02) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_03) {
  int res = 0;

  res = s21_create_matrix(3, 4, NULL);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(NULL);
}
END_TEST

START_TEST(s21_create_matrix_04) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_05) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(-6, -5, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_06) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, -5, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_eq_matrix_01) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_02) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_03) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 3, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_04) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_05) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_01) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t X = {0};
  matrix_t Z = {0};

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(1.0, &B);

  s21_sum_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[0][2] = 6.0;
  X.matrix[0][3] = 8.0;
  X.matrix[1][0] = 10.0;
  X.matrix[1][1] = 12.0;
  X.matrix[1][2] = 14.0;
  X.matrix[1][3] = 16.0;
  X.matrix[2][0] = 18.0;
  X.matrix[2][1] = 20.0;
  X.matrix[2][2] = 22.0;
  X.matrix[2][3] = 24.0;
  X.matrix[3][0] = 26.0;
  X.matrix[3][1] = 28.0;
  X.matrix[3][2] = 30.0;
  X.matrix[3][3] = 32.0;

  int res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sum_matrix_02) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t c = {0};

  int res = CALC_ERROR;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(3, 3, &b);

  s21_init_matrix(0, &a);
  s21_init_matrix(0, &b);

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_sub_matrix_01) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t X = {0};
  matrix_t Z = {0};

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(2.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(1.0, &B);

  s21_sub_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 1.0;
  X.matrix[0][1] = 1.0;
  X.matrix[0][2] = 1.0;
  X.matrix[0][3] = 1.0;
  X.matrix[1][0] = 1.0;
  X.matrix[1][1] = 1.0;
  X.matrix[1][2] = 1.0;
  X.matrix[1][3] = 1.0;
  X.matrix[2][0] = 1.0;
  X.matrix[2][1] = 1.0;
  X.matrix[2][2] = 1.0;
  X.matrix[2][3] = 1.0;
  X.matrix[3][0] = 1.0;
  X.matrix[3][1] = 1.0;
  X.matrix[3][2] = 1.0;
  X.matrix[3][3] = 1.0;

  int res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sub_matrix_02) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t c = {0};

  int res = CALC_ERROR;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(3, 3, &b);

  s21_init_matrix(0, &a);
  s21_init_matrix(0, &b);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_sub_matrix_03) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t c = {0};

  int res = CALC_ERROR;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &b);

  s21_init_matrix(INFINITY, &a);
  s21_init_matrix(0, &b);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_mult_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(1.0, &B);

  s21_mult_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 90.0;
  X.matrix[0][1] = 100.0;
  X.matrix[0][2] = 110.0;
  X.matrix[0][3] = 120.0;
  X.matrix[1][0] = 202.0;
  X.matrix[1][1] = 228.0;
  X.matrix[1][2] = 254.0;
  X.matrix[1][3] = 280.0;
  X.matrix[2][0] = 314.0;
  X.matrix[2][1] = 356.0;
  X.matrix[2][2] = 398.0;
  X.matrix[2][3] = 440.0;
  X.matrix[3][0] = 426.0;
  X.matrix[3][1] = 484.0;
  X.matrix[3][2] = 542.0;
  X.matrix[3][3] = 600.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_matrix_02) {
  matrix_t a = {0};
  matrix_t b = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(3, 3, &b);

  s21_init_matrix(0, &a);
  s21_init_matrix(0, &b);

  ck_assert_int_eq(s21_mult_matrix(&a, &b, NULL), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(s21_mult_matrix_03) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t c = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(0, 0, &a);
  s21_create_matrix(3, 3, &b);

  s21_init_matrix(0, &a);
  s21_init_matrix(0, &b);

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_mult_matrix_04) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t c = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(0, 0, &b);

  s21_init_matrix(0, &a);
  s21_init_matrix(0, &b);

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_mult_matrix_05) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t c = {0};

  int res = CALC_ERROR;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(2, 2, &b);

  s21_init_matrix(0, &a);
  s21_init_matrix(0, &b);

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_mult_matrix_06) {
  matrix_t a = {0};
  matrix_t b = {0};
  matrix_t c = {0};

  int res = CALC_ERROR;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &b);

  s21_init_matrix(INFINITY, &a);
  s21_init_matrix(INFINITY, &b);

  ck_assert_int_eq(s21_mult_matrix(&a, &b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_mult_number_01) {
  int res = 0;
  double number = 3.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);

  s21_init_matrix(1.0, &A);

  s21_mult_number(&A, number, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 3.0;
  X.matrix[0][1] = 6.0;
  X.matrix[0][2] = 9.0;
  X.matrix[0][3] = 12.0;
  X.matrix[1][0] = 15.0;
  X.matrix[1][1] = 18.0;
  X.matrix[1][2] = 21.0;
  X.matrix[1][3] = 24.0;
  X.matrix[2][0] = 27.0;
  X.matrix[2][1] = 30.0;
  X.matrix[2][2] = 33.0;
  X.matrix[2][3] = 36.0;
  X.matrix[3][0] = 39.0;
  X.matrix[3][1] = 42.0;
  X.matrix[3][2] = 45.0;
  X.matrix[3][3] = 48.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_03) {
  matrix_t a = {0};
  double b = 1;
  matrix_t c = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(3, 3, &a);

  s21_init_matrix(0, &a);

  ck_assert_int_eq(s21_mult_number(&a, b, NULL), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_mult_number_04) {
  matrix_t a = {0};
  double b = 1;
  matrix_t c = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(0, 0, &a);

  s21_init_matrix(0, &a);

  ck_assert_int_eq(s21_mult_number(&a, b, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_transpose_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t T = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 3, &A);
  s21_init_matrix(1.0, &A);
  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 4.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 5.0;
  B.matrix[2][0] = 3.0;
  B.matrix[2][1] = 6.0;

  res = s21_transpose(&A, &T);
  res = s21_eq_matrix(&T, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&T);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_transpose_02) {
  matrix_t a = {0};
  matrix_t c = {0};

  int check = INCORRECT_MATRIX;
  s21_create_matrix(2, 2, &a);

  s21_init_matrix(0, &a);

  ck_assert_int_eq(s21_transpose(&a, NULL), check);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_transpose_03) {
  const int rows = 1;
  const int cols = 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  s21_init_matrix(1.0, &m);

  matrix_t check = {0};
  s21_create_matrix(cols, rows, &check);
  s21_init_matrix(1.0, &check);
  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&m, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), 1);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_determinant_01) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = -677700.0;
  A.matrix[0][1] = 654.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = -0.00001;

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, -1301.223);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_02) {
  matrix_t a = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(2, 2, &a);

  s21_init_matrix(1, &a);

  ck_assert_int_eq(s21_determinant(&a, NULL), res);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_calc_complements_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = -30.0;
  X.matrix[0][2] = -108.0;
  X.matrix[0][3] = 106.0;
  X.matrix[1][0] = 138.0;
  X.matrix[1][1] = -726.0;
  X.matrix[1][2] = -1137.0;
  X.matrix[1][3] = 1061.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 12.0;
  X.matrix[2][2] = 57.0;
  X.matrix[2][3] = -47.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 6.0;
  X.matrix[3][2] = -75.0;
  X.matrix[3][3] = 57.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_inverse_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 1.0;
  X.matrix[0][2] = 0.0;
  X.matrix[0][3] = 0.0;
  X.matrix[1][0] = -5.0 / 23.0;
  X.matrix[1][1] = -121.0 / 23.0;
  X.matrix[1][2] = 2.0 / 23.0;
  X.matrix[1][3] = 1.0 / 23.0;
  X.matrix[2][0] = -18.0 / 23.0;
  X.matrix[2][1] = -379.0 / 46.0;
  X.matrix[2][2] = 19.0 / 46.0;
  X.matrix[2][3] = -25.0 / 46.0;
  X.matrix[3][0] = 53.0 / 69.0;
  X.matrix[3][1] = 1061.0 / 138.0;
  X.matrix[3][2] = -47.0 / 138.0;
  X.matrix[3][3] = 19.0 / 46.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_inverse_matrix_02) {
  matrix_t a = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(2, 2, &a);

  s21_init_matrix(0, &a);

  ck_assert_int_eq(s21_inverse_matrix(&a, NULL), res);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_inverse_matrix_03) {
  matrix_t a = {0};
  matrix_t c = {0};

  int res = CALC_ERROR;
  s21_create_matrix(3, 2, &a);

  s21_init_matrix(0, &a);

  ck_assert_int_eq(s21_inverse_matrix(&a, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_inverse_matrix_04) {
  matrix_t a = {0};
  matrix_t c = {0};

  int res = CALC_ERROR;
  s21_create_matrix(1, 1, &a);

  s21_init_matrix(0, &a);

  ck_assert_int_eq(s21_inverse_matrix(&a, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
}
END_TEST

START_TEST(s21_inverse_matrix_05) {
  matrix_t a = {0};
  matrix_t c = {0};

  int res = INCORRECT_MATRIX;
  s21_create_matrix(2, 2, &a);

  s21_init_matrix(0, &a);

  ck_assert_int_eq(s21_inverse_matrix(NULL, &c), res);

  s21_remove_matrix(&a);
  s21_remove_matrix(&c);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, s21_create_matrix_01);
  tcase_add_test(tc_core, s21_create_matrix_02);
  tcase_add_test(tc_core, s21_create_matrix_03);
  tcase_add_test(tc_core, s21_create_matrix_04);
  tcase_add_test(tc_core, s21_create_matrix_05);
  tcase_add_test(tc_core, s21_create_matrix_06);
  tcase_add_test(tc_core, s21_eq_matrix_01);
  tcase_add_test(tc_core, s21_eq_matrix_02);
  tcase_add_test(tc_core, s21_eq_matrix_03);
  tcase_add_test(tc_core, s21_eq_matrix_04);
  tcase_add_test(tc_core, s21_eq_matrix_05);
  tcase_add_test(tc_core, s21_sum_matrix_01);
  tcase_add_test(tc_core, s21_sum_matrix_02);
  tcase_add_test(tc_core, s21_sub_matrix_01);
  tcase_add_test(tc_core, s21_sub_matrix_02);
  tcase_add_test(tc_core, s21_sub_matrix_03);
  tcase_add_test(tc_core, s21_mult_matrix_01);
  tcase_add_test(tc_core, s21_mult_matrix_02);
  tcase_add_test(tc_core, s21_mult_matrix_03);
  tcase_add_test(tc_core, s21_mult_matrix_04);
  tcase_add_test(tc_core, s21_mult_matrix_05);
  tcase_add_test(tc_core, s21_mult_matrix_06);
  tcase_add_test(tc_core, s21_mult_number_01);
  tcase_add_test(tc_core, s21_mult_number_03);
  tcase_add_test(tc_core, s21_mult_number_04);
  tcase_add_test(tc_core, s21_transpose_01);
  tcase_add_test(tc_core, s21_transpose_02);
  tcase_add_test(tc_core, s21_transpose_03);
  tcase_add_test(tc_core, s21_determinant_01);
  tcase_add_test(tc_core, s21_determinant_02);
  tcase_add_test(tc_core, s21_calc_complements_01);
  tcase_add_test(tc_core, s21_inverse_matrix_01);
  tcase_add_test(tc_core, s21_inverse_matrix_02);
  tcase_add_test(tc_core, s21_inverse_matrix_03);
  tcase_add_test(tc_core, s21_inverse_matrix_04);
  tcase_add_test(tc_core, s21_inverse_matrix_05);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf ? 1 : 0;
}