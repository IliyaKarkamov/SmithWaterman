#include <smith_waterman_utils/matrix.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("basic matrix test")
{
    sw::Matrix<int> m(10, 15);

    REQUIRE(m.rows() == 10);
    REQUIRE(m.columns() == 15);

    fill(m, 5);

    for (auto i = 0u; i < m.rows(); ++i)
        for (auto j = 0u; j < m.columns(); ++j)
            REQUIRE(m(i, j) == 5);

    m(0, 0) = 1;
    REQUIRE(m(0, 0) == 1);
}