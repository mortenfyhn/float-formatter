#include "catch/catch.hpp"
#include "float-formatter.hpp"

#include <cmath>
#include <iostream>
#include <regex>
#include <string>

TEST_CASE("Integers that don't need scientific notation")
{
    REQUIRE(format(1) == "     1");
    REQUIRE(format(10) == "    10");
    REQUIRE(format(1e2) == "   100");
    REQUIRE(format(1e3) == "  1000");
    REQUIRE(format(1e4) == " 10000");
    REQUIRE(format(1e5) == "100000");
    REQUIRE(format(-1) == "    -1");
    REQUIRE(format(-10) == "   -10");
    REQUIRE(format(-1e2) == "  -100");
    REQUIRE(format(-1e3) == " -1000");
    REQUIRE(format(-1e4) == "-10000");

    REQUIRE(format(1e7, 8) == "10000000");
    REQUIRE(format(-1e6, 8) == "-1000000");
}

TEST_CASE("Integers that need scientific notation")
{
    REQUIRE(format(1e6) == "   1e6");
    REQUIRE(format(1e-6) == "  1e-6");
    REQUIRE(format(-1e6) == "  -1e6");
    REQUIRE(format(-1e-6) == " -1e-6");

    REQUIRE(format(1e8, 8) == "     1e8");
    REQUIRE(format(1e-8, 8) == "    1e-8");
    REQUIRE(format(-1e8, 8) == "    -1e8");
    REQUIRE(format(-1e-8, 8) == "   -1e-8");
}

TEST_CASE("Floats that don't need scientific notation")
{
    REQUIRE(format(0.5) == "   0.5");
    REQUIRE(format(123.45) == "123.45");
    REQUIRE(format(12.340) == " 12.34");
    REQUIRE(format(-1.2) == "  -1.2");
    REQUIRE(format(-1.200000) == "  -1.2");
    REQUIRE(format(123.456789) == "123.45");
    REQUIRE(format(123.456789, 8) == "123.4567");
    REQUIRE(format(-1680.1) == " -1680");
}

TEST_CASE("Floats that need scientific notation")
{
    REQUIRE(format(1.2e6) == " 1.2e6");
    REQUIRE(format(-1.2e6) == "-1.2e6");
    REQUIRE(format(1.234e6) == "1.23e6");
    REQUIRE(format(-1.234e-6) == " -1e-6");
}

TEST_CASE("Zero should be a dot")
{
    REQUIRE(format(0) == "     .");
    REQUIRE(format(0, 8) == "       .");
}

TEST_CASE("Check invariants with random input")
{
    std::default_random_engine generator(0);
    std::uniform_real_distribution<double> significand(-1, 1);
    std::uniform_int_distribution<int> exponent(-150, 150);
    std::uniform_int_distribution<int> width(6, 20);
    std::regex r(R"(\.[\D|$])");

    const int iterations = 1e3;
    for (int i = 0; i < iterations; ++i)
    {
        double s = significand(generator);
        int e = exponent(generator);
        int w = width(generator);
        double value = s * std::pow(10, e);

        std::string value_as_string = format(value, w);
        REQUIRE(value_as_string.size() == w);
        REQUIRE(!std::regex_search(value_as_string, r));
    }
}
