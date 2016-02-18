#ifndef JACOBI_H
#define JACOBI_H

#include <stdlib.h>
#include <math.h>
#include <assert.h>

double offdiag(const double* mat, const size_t matSize, size_t* p, size_t* q);
void jacobiRot(double* mat, double* eigvec, const size_t matSize, const size_t p, const size_t q);
unsigned jacobiSolve(double* mat, double* eigvec, const size_t matSize, const double tol, const unsigned maxIter);

#endif /* end of include guard: JACOBI_H */
