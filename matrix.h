/*
  *@author Vinícius Prata Klôh
*/

#ifndef MATRIX_H
#define MATRIX_H 1

struct matrix{
   double *square;
   long double *rect;
   int row;
   int col;
};typedef struct matrix Matrix;

/*
  functions
*/
int create_matrix(Matrix *matrix, const int row, const int col, const int square);
int set_matrix(Matrix *matrix, const double beta, const double gamma,
               const double dt, const double dx, const int square);
int print_matrix(Matrix matrix, const int square);
int sum_matrix(const Matrix matrix_1, const Matrix matrix_2, Matrix *matrix_sum);
int sub_matrix(const Matrix matrix_1, const Matrix matrix_2, Matrix *matrix_sum);
int mul_matrix(const Matrix matrix_1, const Matrix matrix_2, Matrix *matrix_sum);

/*
  end functions
*/


#endif /* PP_UTILS_H 1 */
