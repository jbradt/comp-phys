#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "jacobi.h"
#include <armadillo>

TEST_CASE("offdiag function finds max")
{
    arma::mat data (10, 10, arma::fill::eye);
    size_t p = 0;
    size_t q = 0;

    SECTION("Finds one large offdiagonal element")
    {
        data(0, 9) = 10;
        data(9, 0) = 10;

        double maxElem = offdiag(data.memptr(), data.n_rows, &p, &q);

        CHECK(maxElem == Approx(10));
        CHECK(p == 0);
        CHECK(q == 9);
    }

    SECTION("Picks largest of two offdiagonal elements")
    {
        data(0, 9) = 10;
        data(9, 0) = 10;
        data(0, 5) = 5;
        data(5, 0) = 5;

        double maxElem = offdiag(data.memptr(), data.n_rows, &p, &q);

        CHECK(maxElem == Approx(10));
        CHECK(p == 0);
        CHECK(q == 9);
    }

    SECTION("Doesn't pick a diagonal element when the diagonal is larger")
    {
        data(0, 9) = 10;
        data(9, 0) = 10;
        data.diag().fill(100);

        double maxElem = offdiag(data.memptr(), data.n_rows, &p, &q);

        CHECK(maxElem == Approx(10));
        CHECK(p == 0);
        CHECK(q == 9);
    }
}

TEST_CASE("offdiag function fails gracefully when all elements are zero.")
{
    arma::mat data (10, 10, arma::fill::eye);
    size_t p = 0;
    size_t q = 0;

    double maxElem = offdiag(data.memptr(), data.n_rows, &p, &q);

    SECTION("Returned max is negative")
    {
        REQUIRE(maxElem < 0);
    }

    SECTION("Indices are unchanged")
    {
        REQUIRE(p == 0);
        REQUIRE(q == 0);
    }
}

TEST_CASE("Solver works on 2x2")
{
    arma::mat m = {{3, 2},
                   {2, 2}};
    arma::mat eigvec (2, 2, arma::fill::eye);

    jacobiSolve(m.memptr(), eigvec.memptr(), 2, 1e-8, 10000);
    arma::vec d = m.diag();
    arma::vec true_eigval = {4.56155281, 0.43844719};
    arma::mat true_eigvec = {{ 0.78820544, -0.61541221},
                             { 0.61541221,  0.78820544}};

    CHECK(arma::accu(arma::abs(true_eigval - d)) < 1e-4);

    CHECK(arma::accu(arma::abs(true_eigvec - eigvec)) < 1e-4);
}

TEST_CASE("Solver works on 4x4")
{
    arma::mat m = {{3, 1, 4, 2},
                   {1, 8, 4, 5},
                   {4, 4, 1, 0},
                   {2, 5, 0, 6}};
    arma::mat eigvec (4, 4, arma::fill::eye);

    jacobiSolve(m.memptr(), eigvec.memptr(), 4, 1e-8, 10000);
    arma::vec eigval = m.diag();
    arma::vec true_eigval = {13.8188408 ,  -3.48194743,   4.71305192,   2.95005472};
    arma::mat true_eigvec = {{ 0.28352526,  0.49582989, -0.65550258,  0.49404708},
                             { 0.72820838,  0.34065926,  0.13637853, -0.57884775},
                             { 0.31570207, -0.7465408 , -0.55924244, -0.17394522},
                             { 0.53819902, -0.28421968,  0.48884064,  0.62497666}};

    arma::uvec calcSortIdx = arma::sort_index(eigval);
    eigval = true_eigval(calcSortIdx);
    eigvec = true_eigvec(calcSortIdx);

    arma::uvec trueSortIdx = arma::sort_index(true_eigval);
    true_eigval = true_eigval(calcSortIdx);
    true_eigvec = true_eigvec(calcSortIdx);

    CAPTURE(true_eigval);
    CAPTURE(m.diag());
    CHECK(arma::accu(arma::abs(true_eigval - eigval)) < 1e-4);
    CHECK(arma::accu(arma::abs(true_eigvec - eigvec)) < 1e-4);
}
