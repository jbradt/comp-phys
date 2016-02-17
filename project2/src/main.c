#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

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

double potential(const double r)
{
    return r*r;
}

int main(const int argc, const char** argv)
{
    if (argc < 5) {
        puts("Usage: jacobiSolve MAX_RHO NUM_PTS TOL MAX_ITER");
        return 1;
    }

    double maxRho = atof(argv[1]);
    int matSize = atoi(argv[2]);
    double tol = atof(argv[3]);
    unsigned maxIter = atoi(argv[4]);

    double stepSize = maxRho / matSize;

    // Allocate matrices
    double* mat = calloc(matSize * matSize, sizeof(double));
    if (mat == NULL) return 2;

    double* eigvec = calloc(matSize * matSize, sizeof(double));
    if (eigvec == NULL) {
        free(mat);
        return 2;
    }

    // Fill matrices
    for (size_t i = 0; i < matSize; i++) {
        // Main diagonal elements
        double rho = i * stepSize;
        double pot = potential(rho);
        mat[ind(i,i,matSize)] = (2 / (stepSize * stepSize)) + pot;

        // Upper and lower diagonals
        double offDiagEl = -1 / (stepSize * stepSize);
        if (i < matSize - 1) {
            mat[ind(i,i+1,matSize)] = offDiagEl;
            mat[ind(i+1,i,matSize)] = offDiagEl;
        }

        // Initialize eigvec
        eigvec[ind(i,i,matSize)] = 1;
    }

    jacobiSolve(mat, eigvec, matSize, tol, maxIter);

    printMat(mat, matSize, matSize);

    free(mat);
    free(eigvec);

    return 0;
}
