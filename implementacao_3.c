#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrix.h"
#include "cg.h"

FILE *pfile_all = NULL;
FILE *pfile_dt = NULL;

/* Open the output file */
int openFile(const char name){
  pfile_all = fopen(name, "a");
  if(pfile_all == NULL)
    return 1;
  return 0;
}

/* Close the output file */
int closeFile(FILE *file){
  if(file == NULL)
    return 1;
  fclose(file);
  return 0;
}

/* Concat the name for the output files */
int concatName(char* file, const double dt){
  char aux[20];
  sprintf(aux, "%.1f", dt);
  strcat(file, aux);
  strcat(file, ".dat");
}

/* Time loop */
int time_loop(Matrix a, Matrix *b, Matrix *xi,
              const double t_max, const double dt,
              const double dx, double alpha, double beta,
              const long double tol, const int iter_max){

  int count_time, count_space, count;
  Matrix xii;
  float actual_time = 0.0;
  float space = -1.0;
  long double element;
  create_matrix(&xii, xi[0].row, 1, 0);

  pfile_all = fopen("output.dat", "a");
  if(!pfile_all)
    return 1;

  fprintf(pfile_all, "# time \t space \t x \n");

  while(actual_time <= 1.1){
    char file_dt[20] = "";
    concatName(file_dt, actual_time);
    pfile_dt = fopen(file_dt, "a");
    if(!pfile_dt)
      return 1;

    /* Iterative loop using the Conjugate Gradient method */
    cg_method(a, *b, xi, iter_max, tol);

          /* Explicit */
    /*
    for(count_space = 1; count_space < b[0].row - 1; count_space++){
      xi[0].rect[count_space] = (beta*b[0].rect[count_space-1]) - alpha*b[0].rect[count_space] + beta*b[0].rect[count_space+1];
    }
    */

    for(count_space = 0; count_space < xi[0].row; count_space++){
      fprintf(pfile_dt, "%f \t %f \t %Le \n", actual_time, space, xi[0].rect[count_space]);
      fprintf(pfile_all, "%f \t %f \t %Le \n", actual_time, space, xi[0].rect[count_space]);
      space += dx;
    }
    for(count = 0; count < xi[0].row; count++){
      b[0].rect[count] = xi[0].rect[count];
    }
    actual_time += dt;
    space = -1.0;
    fprintf(pfile_all, "\n");
    closeFile(pfile_dt);
  }
  closeFile(pfile_all);

  return 0;
}

/*
  main functions
*/
//int main(int argc, char *argv[]){
int main(){
  //int row = atoi(argv[1]);
  //int col = atoi(argv[2]);
  int row = 400, col = 400;
  double t_max = 1.0, x_max;
  int iter_max = 100;
  long double tol = 0.00001;
  double dt = 0.05, dx = 0.005;
  double d = 0.01, r = 0.3;
  double beta = (dt*d) / (dx*dx);
  double gamma = 1 + (2*beta) - (dt*r);
  //double alpha = 1 + (dt*r) - 2*beta;
  double alpha = -1 - (dt*r) + (2*beta);
  printf("\n beta: %.5lf, gamma: %.5lf, alpha: %.5lf \n", beta, gamma, alpha);

  Matrix a;
  Matrix b;
  Matrix x;
  Matrix xi;

  create_matrix(&a, row, col, 1);
  create_matrix(&b, row, 1, 0);
  create_matrix(&x, row, 1, 0);
  create_matrix(&xi, row, 1, 0);

  set_matrix(&a, beta, gamma, dt, dx, 1);
  set_matrix(&b, beta, gamma, dt, dx, 0);

  /* Call the time loop function*/
  time_loop(a, &b, &x, t_max, dt, dx, alpha, beta, tol, iter_max);

  free(a.square);
  free(x.rect);
  free(xi.rect);
  free(b.rect);
  return 0;
}
