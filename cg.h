/*
  *@author Vinícius Prata Klôh
*/


#ifndef CG_H
#define CG_H 1

/*
  auxiliar functions
*/
int residuo_calculator(const Matrix b, const Matrix a, const Matrix x, Matrix *residue,
                       const int k);
int lambda_calculator(const Matrix residue, const Matrix direction,
                      const Matrix a, Matrix *lambda, const int k);
int alpha_calculator(const Matrix residue_i, const Matrix residue_ii,
                     const Matrix_ii, Matrix *alpha);
int aprox_calculator(const Matrix xi, const Matrix lambda, const Matrix residue,
                     Matrix *xii);
int check_error(const Matrix xi, const Matrix xii, const long double tol);
/*
  end auxiliar functions
*/


/*
  Conjugate Gradient function
*/
int cg_method(const Matrix a, const Matrix b, Matrix *x,
              const int iter_max, const long double tol);
/*
  end Conjugate Gradient function
*/

#endif /* CG_H 1 */
