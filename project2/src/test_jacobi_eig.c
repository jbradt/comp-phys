#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "jacobi.h"

#define ind(i,j,n) (n*(j))+(i)

void printMat(const double* mat, const size_t numRows, const size_t numCols)
{
    for (size_t i = 0; i < numRows; i++) {
        for (size_t j = 0; j < numCols; j++) {
            if (j < numCols - 1) {
                printf("% 10.4f  ", mat[ind(i,j,numRows)]);
            }
            else {
                printf("% 10.4f\n", mat[ind(i,j,numRows)]);
            }
        }
    }
}

int main(const int argc, const char** argv)
{
    const size_t matSize = 4;

    // Allocate matrices
    double* mat = calloc(matSize * matSize, sizeof(double));
    if (mat == NULL) return 2;

    double* eigvec = calloc(matSize * matSize, sizeof(double));
    if (eigvec == NULL) {
        free(mat);
        return 2;
    }

    mat[ind(0,0,matSize)] = 1;
    mat[ind(0,1,matSize)] = 2;
    mat[ind(1,0,matSize)] = 2;
    mat[ind(1,1,matSize)] = 3;
    mat[ind(2,2,matSize)] = 4;
    mat[ind(2,3,matSize)] = 6;
    mat[ind(3,3,matSize)] = 5;
    mat[ind(3,2,matSize)] = 6;
    mat[ind(1,2,matSize)] = 7;
    mat[ind(2,1,matSize)] = 7;


    printMat(mat, matSize, matSize);

    // Fill matrices
    for (size_t i = 0; i < matSize; i++) {
        // Initialize eigvec
        eigvec[ind(i,i,matSize)] = 1;
    }

    double tol = 1e-10;
    unsigned maxIter = 10000;
    unsigned itersDone = jacobiSolve(mat, eigvec, matSize, tol, maxIter);
    printf("Finished in %u iterations.\n", itersDone);

    printMat(mat, matSize, matSize);
    printf("Eigenvalues:\n");
    printMat(eigvec, matSize, matSize);

    free(mat);
    free(eigvec);

    return 0;
}
