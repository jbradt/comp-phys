#include "jacobi.c"
#include <iostream>
#include <chrono>

int main()
{
    size_t N = 1000;
    double* m = new double[1000*1000];
    size_t p = 0, q = 0;

    auto begin = std::chrono::high_resolution_clock::now();
    offdiag(m, N, &p, &q);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << std::endl;
    delete m;

    return 0;
}
