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
    size_t matSize = (size_t) atoi(argv[2]);
    double tol = atof(argv[3]);
    unsigned maxIter = (unsigned) atoi(argv[4]);

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
        double rho = (i+1) * stepSize;
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

    unsigned itersDone = jacobiSolve(mat, eigvec, matSize, tol, maxIter);
    printf("Finished in %u iterations.\n", itersDone);

    // printMat(mat, matSize, matSize);

    FILE* outfile;

    outfile = fopen("eigval.csv", "w");
    if (outfile != NULL) {
        fprintf(outfile, "rho,result\n");
        for (size_t i = 0; i < matSize; i++) {
            fprintf(outfile, "%0.8e,%0.8e\n", i*stepSize, mat[ind(i,i,matSize)]);
        }
        fclose(outfile);
    }
    else {
        printf("Failed to open output file.\n");
    }

    outfile = fopen("eigvec.csv", "w");
    if (outfile != NULL) {
        for (size_t i = 0; i < matSize; i++) {
            for (size_t j = 0; j < matSize; j++) {
                char term = (j < matSize - 1) ? ',' : '\n';
                fprintf(outfile, "%0.8e%c", eigvec[ind(i,j,matSize)], term);
            }
        }
        fclose(outfile);
    }
    else {
        printf("Failed to open output file.\n");
    }

    free(mat);
    free(eigvec);

    return 0;
}
