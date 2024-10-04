#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INVALID_MATRIX 1
#define COMPUTATION_ERROR 2

/**
 * Функция s21_create_matrix создает матрицу с указанным количеством строк и
 * столбцов.
 *
 * @param rows Строки — это количество строк в матрице, которые будут созданы.
 * Он определяет вертикальный размер матрицы.
 * @param columns Столбцы представляют количество столбцов в матрице. Это
 * целочисленное значение, указывающее количество вертикальных элементов в
 * матрице.
 * @param result Параметр result является указателем на структуру matrix_t. Эта
 * структура, вероятно, содержит информацию о матрице, например сами данные
 * матрицы, количество строк и количество столбцов. Функция `s21_create_matrix`
 * инициализирует матрицу указанным количеством строк.
 *
 * @return Функция s21_create_matrix вернет либо INCORRECT_MATRIX, если входные
 * параметры недействительны (строки или столбцы меньше 1, либо результат равен
 * NULL), либо OK, если создание матрицы прошло успешно.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if ((rows < 1 || columns < 1) || (result == NULL)) {
    return INCORRECT_MATRIX;
  }

  double **matrix = calloc(rows, sizeof(double *));

  for (int i = 0; i < rows; i++) {
    matrix[i] = calloc(columns, sizeof(double));
  }

  result->matrix = matrix;
  result->rows = rows;
  result->columns = columns;
  return OK;
}

/**
 * Функция s21_remove_matrix освобождает память, выделенную для матрицы,
 * хранящейся в структуре matrix_t.
 *
 * @param A Параметр «A» является указателем на структуру типа «matrix_t».
 * Структура matrix_t, скорее всего, содержит информацию о матрице, такую как
 * количество строк, столбцов и сами данные матрицы. Функция `s21_remove_matrix`
 * предназначена для освобождения выделенной памяти.
 *
 * @return В предоставленном фрагменте кода функция `s21_remove_matrix` является
 * пустой функцией, что означает, что она не возвращает никакого значения явно.
 * Однако у него есть оператор раннего возврата `if (!A) return;`, который
 * приведет к досрочному выходу из функции, если входной `A` является нулевым
 * указателем. Если условие не выполняется, функция переходит к освобождению
 * памяти, выделенной для
 */
void s21_remove_matrix(matrix_t *A) {
  if (!A) return;
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}

/**
 * Функция `s21_eq_matrix` сравнивает две матрицы на предмет равенства в
 * пределах указанного допуска и возвращает статус успеха или неудачи.
 *
 * @param A Похоже, что предоставленный вами фрагмент кода представляет собой
 * функцию s21_eq_matrix, которая сравнивает две матрицы A и B на равенство.
 * Функция сначала проверяет правильность обеих матриц с помощью функции
 * is_correct_matrix. Если какая-либо из матриц неверна, возвращается `FAILURE
 * @param B Похоже, вы предоставили функцию s21_eq_matrix, которая сравнивает
 * две матрицы A и B на равенство. Функция проверяет, имеют ли матрицы
 * одинаковые размеры и равны ли соответствующие элементы в пределах допуска
 * «1e-7».
 *
 * @return Функция s21_eq_matrix возвращает целочисленное значение: SUCCESS или
 * FAILURE.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (is_correct_matrix(A) != OK || is_correct_matrix(B) != OK) return FAILURE;

  if (A->columns != B->columns || A->rows != B->rows) {
    res = FAILURE;
  }
  for (int i = 0; i < A->rows && res == SUCCESS; i++) {
    for (int j = 0; j < A->columns && res == SUCCESS; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) {
        res = FAILURE;
      }
    }
  }
  return res;
}
/**
 * Функция is_correct_matrix проверяет, действительна ли данная матрица.
 *
 * @param M Указатель на структуру, представляющую матрицу, включающую
 * информацию о количестве строк, столбцов и самих данных матрицы.
 *
 * @return Функция is_correct_matrix возвращает целочисленное значение, которое
 * представляет статус проверки матрицы. Возможные возвращаемые значения:
 * - `ОК`, если матрица правильная
 * - `INCORRECT_MATRIX`, если матрица неверна или NULL
 */
int is_correct_matrix(matrix_t *M) {
  int code = OK;

  if (M == NULL) {
    code = INCORRECT_MATRIX;
  } else if (M->columns < 1 || M->rows < 1 || M->matrix == NULL) {
    code = INCORRECT_MATRIX;
  }
  return code;
}

/**
 * Функция «calc_errors» проверяет правильность входных матриц и возвращает код
 * ошибки, если они несовместимы для расчета.
 *
 * @param A `matrix_t *A` — это указатель на матричную структуру, представляющую
 * матрицу A.
 * @param B матрица_t *B
 * @param result Функцияcalc_errors принимает три параметра: A, B и result,
 * которые являются указателями на структуры matrix_t. В функции сначала
 * проверяется, являются ли «A» и «B» правильными матрицами и не равен ли
 * «result» значению NULL. Если
 *
 * @return Функцияcalc_errors вернет либо INCORRECT_MATRIX, если входные матрицы
 * неверны, либо CALC_ERROR, если размеры матриц A и B не совпадают. Если ни
 * одно из этих условий не выполнено, функция вернет «ОК».
 */
int calc_errors(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_correct_matrix(A) != OK || is_correct_matrix(B) != OK ||
      result == NULL) {
    return INCORRECT_MATRIX;
  }

  int code = OK;

  if (A->rows != B->rows || A->columns != B->columns) {
    code = CALC_ERROR;
  }

  return code;
}
/**
 * Функция s21_sub_matrix поэлементно вычитает две матрицы A и B и сохраняет
 * результат в новой матрице result, обрабатывая случаи ошибок, связанные с
 * размерами матрицы и ошибками вычислений.
 *
 * @param A Похоже, что предоставленный вами фрагмент кода представляет собой
 * функцию s21_sub_matrix, которая вычитает одну матрицу B из другой матрицы A и
 * сохраняет результат в третьей матрице result. Функция сначала проверяет
 * наличие ошибок с помощью функции «calc_errors», а затем приступает к
 * вычитанию.
 * @param B Кажется, вы собирались предоставить некоторую информацию о матрице
 * B, но информация отсутствует. Не могли бы вы предоставить подробную
 * информацию о матрице B, чтобы я мог помочь вам в дальнейшем с функцией
 * `s21_sub_matrix`?
 * @param result Функция `s21_sub_matrix` принимает две входные матрицы `A` и
 * `B` и вычисляет поэлементное вычитание матрицы B из матрицы A. Результат этой
 * операции вычитания сохраняется в матрице `result`.
 *
 * @return Функция `s21_sub_matrix` возвращает целочисленное значение, которое
 * может быть либо `OK`, если операция вычитания прошла успешно без каких-либо
 * ошибок, либо `CALC_ERROR`, если во время операции возникли какие-либо ошибки.
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = calc_errors(A, B, result);
  if (res != OK) {
    return res;
  }

  res = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows && res == OK; i++) {
    for (int j = 0; j < A->columns && res == OK; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      if (isinf(result->matrix[i][j]) || isnan(result->matrix[i][j])) {
        res = CALC_ERROR;
      }
    }
  }
  return res;
}
/**
 * Функция `s21_sum_matrix` вычисляет сумму соответствующих элементов в двух
 * матрицах и сохраняет результат в третьей матрице.
 *
 * @param A A — указатель на первую матрицу, содержащую целочисленные элементы.
 * @param B Функция s21_sum_matrix принимает в качестве параметров три указателя
 * матрицы: A, B и result. В контексте функции «B» представляет одну из входных
 * матриц, которые необходимо добавить к матрице «A» поэлементно, а результатом
 * операции сложения является
 * @param result Функция `s21_sum_matrix` принимает две входные матрицы `A` и
 * `B` и вычисляет сумму соответствующих элементов из этих матриц, сохраняя
 * результат в матрице `result`.
 *
 * @return Функция `s21_sum_matrix` возвращает целочисленное значение. Если
 * вычисление прошло успешно, оно возвращает «ОК». Если во время вычислений
 * возникают какие-либо ошибки, например несовместимые размеры матриц или
 * проблемы с созданием результирующей матрицы, возвращается COMPUTATION_ERROR.
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int rows = A->rows;
  int columns = A->columns;

  if (rows != B->rows || columns != B->columns) {
    return COMPUTATION_ERROR;  // Несовместимые размеры матриц
  }

  if (s21_create_matrix(rows, columns, result) != OK) {
    return COMPUTATION_ERROR;  // Ошибка создания матрицы
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return OK;
}

/**
 * Функция `s21_mult_number` умножает каждый элемент матрицы на заданное число и
 * сохраняет результат в другой матрице.
 *
 * @param A Матрица типа «matrix_t», содержащая значения, которые нужно умножить
 * на заданное число.
 * @param number Параметр «number» в функции «s21_mult_number» представляет
 * значение, на которое будет умножен каждый элемент входной матрицы «A» для
 * получения соответствующего элемента в матрице «result».
 * @param result Функция s21_mult_number принимает в качестве параметров матрицу
 * A, двойное число и указатель на матрицу result. Он умножает каждый элемент
 * матрицы «A» на заданное «число» и сохраняет результат в матрице «результат».
 * Функция
 *
 * @return Функция `s21_mult_number` вернет целочисленное значение. Если входная
 * матрица «A» неверна или если матрица «результата» равна NULL, она вернет код
 * ошибки «INCORRECT_MATRIX». В противном случае он вернет результат функции
 * s21_create_matrix, которая используется для создания новой матрицы для
 * операции умножения.
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (is_correct_matrix(A) != OK || result == NULL) {
    return INCORRECT_MATRIX;
  }

  res = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return res;
}

/**
 * Функция `s21_mult_matrix` выполняет умножение матриц и возвращает код ошибки,
 * если возникают какие-либо проблемы.
 *
 * @param A A — это матрица, представленная структурой matrix_t, содержащей
 * такую информацию, как количество строк, столбцов и элементов матрицы.
 * @param B Кажется, вы собирались предоставить некоторую информацию о матрице
 * B, но информация отсутствует. Не могли бы вы предоставить подробную
 * информацию о матрице B, чтобы я мог помочь вам в дальнейшем с операцией
 * умножения?
 * @param result Функция s21_mult_matrix принимает две входные матрицы «A» и «B»
 * и вычисляет матричное умножение этих двух матриц, сохраняя результат в
 * матрице «result». Функция сначала проверяет, верны ли входные матрицы и не
 * равна ли матрица результата NULL.
 *
 * @return Функция `s21_mult_matrix` возвращает целочисленное значение, которое
 * может быть одним из следующих:
 * - `OK`, если операция умножения матрицы прошла успешно.
 * - INCORRECT_MATRIX, если какая-либо из входных матриц неверна или
 * результирующая матрица равна NULL.
 * - `CALC_ERROR`, если размеры входных матриц не подходят для умножения матриц,
 * или если есть
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_correct_matrix(A) != OK || is_correct_matrix(B) != OK ||
      result == NULL) {
    return INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    return CALC_ERROR;
  }

  res = s21_create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows && res == OK; i++) {
    for (int j = 0; j < B->columns && res == OK; j++) {
      for (int k = 0; k < A->columns && res == OK; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        if (isinf(result->matrix[i][j]) || isnan(result->matrix[i][j])) {
          res = CALC_ERROR;
        }
      }
    }
  }
  return res;
}

/**
 * Функция s21_transpose транспонирует матрицу и обрабатывает особые случаи для
 * матрицы 1x1.
 *
 * @param A A — указатель на матричную структуру, содержащую исходные данные
 * матрицы.
 * @param result Функция s21_transpose принимает два параметра: A, который
 * является указателем на матричную структуру, и result, который также является
 * указателем на матричную структуру. Функция транспонирует матрицу «A» и
 * сохраняет результат в матрице, на которую указывает «result».
 *
 * @return Функция `s21_transpose` возвращает целочисленное значение, которое
 * представляет статус операции. Возможные возвращаемые значения:
 * - `ОК`, если операция прошла успешно
 * - `INCORRECT_MATRIX`, если входная матрица неверна
 * - `2`, если в функции было выполнено определенное условие
 */
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_correct_matrix(A) != OK || result == NULL) res = INCORRECT_MATRIX;

  res = s21_create_matrix(A->columns, A->rows, result);

  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  if ((A->columns == A->rows) && A->rows == 1) {
    if (result->matrix[0][0] != 0) {
      result->matrix[0][0] = 1 / result->matrix[0][0];
    } else {
      res = 2;
    }
  }

  return res;
}

/**
 * Функция `s21_calc_complements` вычисляет матрицу сомножителей для заданной
 * квадратной матрицы.
 *
 * @param A Функция s21_calc_complements принимает в качестве параметров два
 * указателя матрицы: A и result. Матрица «А» имеет тип «matrix_t» и
 * используется для вычислений, а матрица «результат» также имеет тип «matrix_t»
 * и используется для хранения
 * @param result Функция s21_calc_complements принимает два параметра: A,
 * который является указателем на матрицу, и result, который также является
 * указателем на матрицу. Функция вычисляет матрицу дополнения матрицы «A» и
 * сохраняет результат в матрице, на которую указывает «result».
 *
 * @return Функция s21_calc_complements возвращает значение, хранящееся в
 * переменной res, которое равно либо 2, либо является результатом вызова
 * функции s21_create_matrix.
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (is_correct_matrix(A) != OK || result == NULL) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALC_ERROR;

  int res = 2;
  if ((A->rows == A->columns) && (A->rows > 1)) {
    res = s21_create_matrix(A->columns, A->rows, result);
    if (A->rows != 1) {
      matrix_t local = {0};

      s21_create_matrix(A->rows, A->rows, &local);
      for (int i = 0, x = 0; x < A->rows; x += 1) {
        for (int j = 0; j < A->columns; j += 1) {
          get_minor(A->matrix, local.matrix, x, j, A->rows);
          i = ((x + j) % 2 == 0) ? 1 : (-1);
          result->matrix[x][j] = i * get_determinant(&local, A->rows - 1);
        }
      }
      s21_remove_matrix(&local);
    } else {
      result->matrix[0][0] = 1;
    }
  }
  return res;
}
/**
 * Функция s21_determinant вычисляет определитель квадратной матрицы и сохраняет
 * результат в двойном указателе.
 *
 * @param A A — указатель на структуру, представляющую матрицу. Структура
 * содержит информацию о матрице, такую как количество строк и столбцов, а также
 * двумерный массив, представляющий элементы матрицы.
 * @param result Параметр result в функции s21_determinant является указателем
 * на двойное значение. Этот указатель используется для хранения результата
 * вычисления определителя, выполненного внутри функции.
 *
 * @return Функция `s21_determinant` вернет одно из следующих значений:
 * - INCORRECT_MATRIX, если входная матрица неверна или указатель результата
 * равен NULL.
 * - `CALC_ERROR`, если количество столбцов не равно количеству строк в матрице
 * - `OK`, если вычисление определителя прошло успешно
 */
int s21_determinant(matrix_t *A, double *result) {
  if (is_correct_matrix(A) != OK || result == NULL) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALC_ERROR;
  if (A->rows == 1)
    *result = A->matrix[0][0];
  else
    *result = get_determinant(A, A->rows);
  return OK;
}

/**
 * Функция вычисляет определитель матрицы, используя рекурсию и миноры.
 *
 * @param A Функция get_determinant вычисляет определитель квадратной матрицы.
 * Параметр «A» является указателем на структуру «matrix_t», которая содержит
 * данные матрицы. Данные матрицы хранятся в двумерном массиве «matrix» внутри
 * структуры «matrix_t».
 * @param size Параметр size в функции get_determinant представляет размер
 * квадратной матрицы, для которой вы хотите вычислить определитель. Это
 * целочисленное значение, указывающее количество строк или столбцов в
 * квадратной матрице.
 *
 * @return определитель матрицы, представленный входными данными `matrix_t *A`
 * размера `size`.
 */
double get_determinant(matrix_t *A, int size) {
  if (size == 1) return A->matrix[0][0];

  matrix_t local = {0};
  double result = 0;

  s21_create_matrix(size, size, &local);
  for (int i = 1, j = 0; j < size; j += 1, i *= (-1)) {
    get_minor(A->matrix, local.matrix, 0, j, size);
    result += i * A->matrix[0][j] * get_determinant(&local, size - 1);
  }

  s21_remove_matrix(&local);
  return result;
}

/**
 * Функция get_minor извлекает второстепенную матрицу из заданной матрицы,
 * исключая указанную строку и столбец.
 *
 * @param A A — указатель на двумерный массив типа double.
 * @param local Параметр local — это указатель на двумерный массив типа double.
 * Он представляет собой матрицу, в которой будет храниться второстепенная
 * матрица после ее извлечения из исходной матрицы `A`.
 * @param new_row Параметр new_row в функции get_minor представляет индекс
 * строки элемента, для которого вы хотите найти минор в матрице A. Функция
 * создаст новую матрицу «local», которая является младшей по отношению к
 * матрице «A», исключив строку «new_row».
 * @param new_col Параметр new_col в функции get_minor представляет индекс
 * столбца элемента, для которого вы хотите найти минор матрицы A. Минор матрицы
 * получается путем удаления строки и столбца, содержащих этот элемент.
 * @param size Параметр size в функции get_minor представляет размер квадратной
 * матрицы A. Он указывает количество строк и столбцов в матрице, поскольку это
 * квадратная матрица.
 */
void get_minor(double **A, double **local, int new_row, int new_col, int size) {
  for (int row = 0, x = 0; row < size; row += 1) {
    for (int col = 0, y = 0; col < size; col += 1) {
      if (row != new_row && col != new_col) {
        local[x][y++] = A[row][col];
        if (y == size - 1) {
          y = 0;
          x++;
        }
      }
    }
  }
}

/**
 * Функция `s21_inverse_matrix` вычисляет обратную матрицу, если она существует.
 *
 * @param A A — указатель на матричную структуру, представляющую входную
 * матрицу, для которой необходимо вычислить обратную матрицу.
 * @param result Параметр result в функции s21_inverse_matrix является
 * указателем на структуру matrix_t, в которой будет сохранена обратная входная
 * матрица A в случае успешного вычисления.
 *
 * @return Функция `s21_inverse_matrix` возвращает целочисленное значение,
 * которое может быть одним из следующих:
 * - `ОК`, если операция прошла успешно
 * - `INCORRECT_MATRIX`, если входная матрица неверна
 * - `CALC_ERROR` если при расчете произошла ошибка
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_correct_matrix(A) != OK || result == NULL) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALC_ERROR;

  double det = 0;
  int res = OK;
  res = s21_determinant(A, &det);

  if (res == OK && det == 0) {
    res = CALC_ERROR;
  }
  if (res == OK && A->rows == 1) {
    res = s21_create_matrix(A->rows, A->columns, result);
    result->matrix[0][0] = 1 / A->matrix[0][0];
  } else if (res == OK) {
    matrix_t first = {0};
    matrix_t second = {0};
    res = s21_calc_complements(A, &first);
    if (res == OK) {
      res = s21_transpose(&first, &second);
    }
    if (res == OK) {
      res = s21_mult_number(&second, 1 / det, result);
    }

    s21_remove_matrix(&first);
    s21_remove_matrix(&second);
  }

  return res;
}

/**
 * Функция print_matrix печатает элементы матрицы построчно.
 *
 * @param A Похоже, функция print_matrix предназначена для печати элементов
 * матрицы, хранящейся в структуре matrix_t. Структура matrix_t, скорее всего,
 * содержит информацию о количестве строк, столбцов и самих элементов матрицы.
 */
void print_matrix(matrix_t *A) {
  int rows = A->rows;
  int columns = A->columns;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%f ", A->matrix[i][j]);
    }
    printf("\n");
  }
}
