#include "jacobi.h"
#include "stdio.h"

#define ind(i,j,n) ((n)*(j))+(i)

double offdiag(const double* mat, const size_t matSize, size_t* p, size_t* q)
{
    double max = 0;
    for (size_t i = 0; i < matSize; i++) {
        for (size_t j = i + 1; j < matSize; j++) {
            assert(i != j);
            double mat_ij = fabs(mat[ind(i,j,matSize)]);
            if (mat_ij > max) {
                // printf("mat_ij = %f\n", mat_ij);
                max = mat_ij;
                *p = i;
                *q = j;
            }
        }
    }
    return max;
}

void jacobiRot(double* mat, double* eigvec, const size_t matSize, const size_t p, const size_t q)
{
    assert(p < matSize);
    assert(q < matSize);

    double tau = (mat[ind(q,q,matSize)] - mat[ind(p,p,matSize)]) / (2*mat[ind(p,q,matSize)]);

    double tanth = 0;
    if (tau >= 0) {
        tanth = 1 / (tau + sqrt(1 + tau*tau));
    }
    else {
        tanth = -1 / (-tau + sqrt(1 + tau*tau));
    }
    double costh = 1 / sqrt(1 + tanth * tanth);
    double sinth = tanth * costh;

    double a_pp = mat[ind(p,p,matSize)];
    double a_qq = mat[ind(q,q,matSize)];
    double a_pq = mat[ind(p,q,matSize)];
    assert((mat[ind(q,p,matSize)] - a_pq) < 1e-8);

    mat[ind(p,p,matSize)] = (a_pp * costh * costh) - (2 * a_pq * costh * sinth) + (a_qq * sinth * sinth);
    mat[ind(q,q,matSize)] = (a_qq * costh * costh) + (2 * a_pq * costh * sinth) + (a_pp * sinth * sinth);
    mat[ind(p,q,matSize)] = 0;
    mat[ind(q,p,matSize)] = 0;

    for (size_t i = 0; i < matSize; i++) {
        if (i != p && i != q) {
            double a_ip = mat[ind(i,p,matSize)];
            double a_iq = mat[ind(i,q,matSize)];

            mat[ind(i,p,matSize)] = a_ip * costh - a_iq * sinth;
            mat[ind(p,i,matSize)] = mat[ind(i,p,matSize)];
            mat[ind(i,q,matSize)] = a_iq * costh + a_ip * sinth;
            mat[ind(q,i,matSize)] = mat[ind(i,q,matSize)];
        }

        double r_ip = eigvec[ind(i,p,matSize)];
        double r_iq = eigvec[ind(i,q,matSize)];

        eigvec[ind(i,p,matSize)] = costh * r_ip - sinth * r_iq;
        eigvec[ind(i,q,matSize)] = costh * r_iq + sinth * r_ip;
    }
}

unsigned jacobiSolve(double* mat, double* eigvec, const size_t matSize, const double tol, const unsigned maxIter)
{
    for (unsigned i = 0; i < maxIter; i++) {
        size_t p = 0, q = 0;
        double maxOffdiagEl = offdiag(mat, matSize, &p, &q);
        // printf("p=%lu, q=%lu\n", p, q);
        assert(p != q);
        if(maxOffdiagEl < tol) {
            return i;
        }
        else {
            jacobiRot(mat, eigvec, matSize, p, q);
        }
    }
    return maxIter;
}
