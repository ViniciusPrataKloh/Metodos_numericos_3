/*
  *@author Vinícius Prata Klôh
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "matrix.h"

int create_matrix(Matrix *matrix, const int row,
                  const int col, const int square){

  if(square){
    matrix[0].square = (double *) malloc(sizeof(double)*(row*col));
    matrix[0].row = row;
    matrix[0].col = col;
  } else{
    int count = 0;
    matrix[0].rect = (long double *) malloc(sizeof(long double)*(row*col));
    matrix[0].row = row;
    matrix[0].col = col;
    for(count = 0; count < matrix[0].row; count++){
      matrix[0].rect[count] = 0;
    }
  }
  return 0;
}

int set_matrix(Matrix *matrix, const double beta, const double gamma, const double dt, const double dx, const int square){
  int i, j;
  long double x = -1.0;

  if(square){
    for(i = 0; i < matrix[0].col; i++){
      for(j = 0; j < matrix[0].row; j++){
        if(i == j){
          matrix[0].square[(i*matrix[0].col)+j] = gamma;
          if(i < matrix[0].row && j < matrix[0].col){
            matrix[0].square[(i*matrix[0].col)+(j+1)] = -beta;
            matrix[0].square[(i+1)*matrix[0].col+j] = -beta;
          }
        }
        if((i-1) > j || (i+1) < j){
          matrix[0].square[(i*matrix[0].col)+j] = 0.0;
        }
      }
    }
  } else{ /* set matrix b */
    for(i = 0; i < matrix[0].row; i++){
      long double pass = exp(-200*pow(x,2));
      matrix[0].rect[i] = pass;
      x += dx;
    }
  }
  return 0;
}

int print_matrix(Matrix matrix, const int square){
  int i, j;
  int element;

  if(square){
    for(i = 0; i < matrix.col; i++){
      for(j = 0; j < matrix.row; j++){
        element = (i * matrix.col) + j;
        printf("%.2lf  ", matrix.square[element]);
      }
      printf("\n");
    }
  } else{
    for(i = 0; i < matrix.row; i++){
      printf("%Le ", matrix.rect[i]);
    }
    printf("\n");
  }

  return 0;
}


int sum_matrix(const Matrix matrix_1, const Matrix matrix_2, Matrix *matrix_sum){
  int i, j;

  if(matrix_sum[0].col != 1){
    for(i = 0; i < matrix_1.col; i++){
      for(j = 0; j < matrix_1.row; j++){
        matrix_sum[0].square[(i*matrix_1.col)+j] = matrix_1.square[(i*matrix_1.col)+j] + matrix_2.square[(i*matrix_1.col)+j];
      }
    }
  } else{
      for(i = 0; i < matrix_1.row; i++){
        matrix_sum[0].rect[i] = matrix_1.rect[i] + matrix_2.rect[i];
      }
    }

  return 0;
}


int sub_matrix(const Matrix matrix_1, const Matrix matrix_2, Matrix *matrix_sub){
  int i, j;

  if(matrix_sub[0].col != 1){
    for(i = 0; i < matrix_1.col; i++){
      for(j = 0; j < matrix_1.row; j++){
        matrix_sub[0].square[(i*matrix_1.col)+j] = matrix_1.square[(i*matrix_1.col)+j] - matrix_2.square[(i*matrix_1.col)+j];
      }
    }
  } else{
      for(i = 0; i < matrix_1.row; i++){
        matrix_sub[0].rect[i] = matrix_1.rect[i] - matrix_2.rect[i];
      }
    }

  return 0;
}

int mul_matrix(const Matrix matrix_1, const Matrix matrix_2, Matrix *matrix_mul){
  int i, j, k = 0;
  long double sum = 0.0, sum2, sum3, sum4;

  if(matrix_1.row == 1 && matrix_1.col == 1){
    for(i = 0; i < matrix_1.row; i++){
      for(j = 0; j < matrix_2.row; j++){
        matrix_mul[0].rect[j] = matrix_1.rect[i] * matrix_2.rect[j];
      }
      sum = 0.0;
    }
  } else if(matrix_1.col != matrix_2.col){
    for(i = 0; i < matrix_1.col; i++){
      for(j = 0; j < matrix_1.col; j++){
        sum = sum + (matrix_1.square[i*matrix_1.col+j]) * matrix_2.rect[j];
      }
      matrix_mul[0].rect[i] = sum;
      sum = 0.0;
    }
  } else{
      for(i = 0; i < matrix_1.row; i++){
        sum = sum + (matrix_1.rect[i] * matrix_2.rect[i]);
      }
      matrix_mul[0].rect[0] = sum;
    }

  return 0;
}
