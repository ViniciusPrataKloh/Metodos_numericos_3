/*
  *@author Vinícius Prata Klôh
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

/*
  auxiliar functions
*/
int residuo_calculator(const Matrix b, const Matrix a, const Matrix x, Matrix *residue,
                       const int k){
  int count = 0;

  Matrix ax;
  create_matrix(&ax, b.row, b.col, 0);  // ix1
  mul_matrix(a, x, &ax);
  sub_matrix(b, ax, residue);

  free(ax.rect);
  return 0;
}

int direction_calculator(const Matrix residue_i, const Matrix residue_ii,
                         const Matrix alpha, Matrix *direction){

  int count = 0;
  Matrix alpha_p;
  create_matrix(&alpha_p, residue_i.row, residue_i.col, 0);  // ix1
  mul_matrix(alpha, residue_i, &alpha_p);
  sum_matrix(residue_ii, alpha_p, direction);

  free(alpha_p.rect);
  return 0;
}

int lambda_calculator(const Matrix residue, const Matrix direction,
                      const Matrix a, Matrix *lambda, const int k){

  Matrix rr, ar, rar;
  create_matrix(&rr, 1, 1, 0);                      // 1x1
  create_matrix(&ar, residue.row, residue.col, 0);  // ix1
  create_matrix(&rar, 1, 1, 0);                     // 1x1

  if(k > 0){
    Matrix rr_ii;
    create_matrix(&rr_ii, 1, 1, 0);                 // 1x1
    mul_matrix(residue, residue, &rr);
    mul_matrix(a, direction, &ar);
    mul_matrix(direction, ar, &rar);
    free(rr_ii.rect);
  } else{
      mul_matrix(residue, residue, &rr);
      mul_matrix(a, residue, &ar);
      mul_matrix(residue, ar, &rar);
  }
  lambda[0].rect[0] = rr.rect[0] / rar.rect[0];

  free(rr.rect);
  free(ar.rect);
  free(rar.rect);
  return 0;
}

int alpha_calculator(const Matrix residue_i, const Matrix residue_ii, Matrix *alpha){

  int count = 0.0;
  Matrix rr_i, rr_ii;
  create_matrix(&rr_i, 1, 1, 0);    // 1x1
  create_matrix(&rr_ii, 1, 1, 0);   // 1x1

  mul_matrix(residue_i, residue_i, &rr_i);
  mul_matrix(residue_ii, residue_ii, &rr_ii);

  alpha[0].rect[0] = (rr_ii.rect[0] / rr_i.rect[0]);

  free(rr_i.rect);
  free(rr_ii.rect);
  return 0;
}

int aprox_calculator(const Matrix xi, const Matrix lambda, const Matrix residue,
                     Matrix *xii){

  Matrix lambda_r, aux;
  int count;
  create_matrix(&lambda_r, residue.row, residue.col, 0);  // 4x1
  create_matrix(&aux, residue.row, residue.col, 0);       // 4x1
  mul_matrix(lambda, residue, &lambda_r);
  sum_matrix(xi, lambda_r, &aux);

  for(count = 0; count < aux.row; count++){
    xii[0].rect[count] = aux.rect[count];
  }

  free(lambda_r.rect);
  free(aux.rect);
  return 0;
}

int check_error(const Matrix xi, const Matrix xii, const long double tol){

  int count = 0;
  long double error = 0.0, max = 0.0;
  for(count = 0; count < xi.row; count++){
    error = (xii.rect[count] - xi.rect[count]) / xi.rect[count];
    if(error > max)
      max = error;
  }
  if(max >= tol)
    return 1;
  return 0;
}
/*
  end auxiliar functions
*/


/*
  Conjugate Gradient function
*/
int cg_method(const Matrix a, const Matrix b, Matrix *x,
              const int iter_max, const long double tol){

  int count = 0;
  int count2 = 0;
  long double error = 0.0;
  Matrix residue_i, residue_ii, direction, xii, lambda, alpha;

  create_matrix(&residue_i, b.row, b.col, 0);     // ix1
  create_matrix(&residue_ii, b.row, b.col, 0);    // ix1
  create_matrix(&direction, b.row, b.col, 0);     // ix1
  create_matrix(&xii, b.row, b.col, 0);           // ix1
  create_matrix(&lambda, 1, 1, 0);                // 1x1
  create_matrix(&alpha, 1, 1, 0);                 // 1x1

  do{
    if(count > 0){  /* For k > 0 */
      count2 = 0.0;
      residuo_calculator(b, a, *x, &residue_ii, count);               /* New residue */
      alpha_calculator(residue_i, residue_ii, &alpha);                /* Alpha */
      direction_calculator(residue_i, residue_ii, alpha, &direction); /* New direction */
      lambda_calculator(residue_ii, direction, a, &lambda, count);    /* Lambda */
      aprox_calculator(*x, lambda, direction, &xii);                  /* Aprox */
    }  else{  /* For k = 0 */
      residuo_calculator(b, a, *x, &residue_i, count);                /* Residue */
      lambda_calculator(residue_i, direction, a, &lambda, count);     /* Lambda */
      aprox_calculator(*x, lambda, residue_i, &xii);                  /* Aprox */
    }
    if(!check_error(*x, xii, tol)){   /* check error */
      for(count2 = 0; count2 <= xii.row; count2++){
        x[0].rect[count2] = xii.rect[count2];
      }
      count++;
      return 0;
    }
    for(count2 = 0; count2 <= xii.row; count2++){
      x[0].rect[count2] = xii.rect[count2];
    }
    count++;
  } while(count <= iter_max);

  return 0;
}
/*
  end Conjugate Gradient function
*/
