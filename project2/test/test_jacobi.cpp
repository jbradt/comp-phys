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
