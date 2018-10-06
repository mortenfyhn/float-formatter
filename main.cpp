#include <iostream>
#include <vector>

#include "float-formatter.hpp"

using Matrix = std::vector<std::vector<double>>;

Matrix generateMatrix()
{
    Matrix matrix;

    // Make a square matrix of zeros.
    for (auto row = 0; row < 4; ++row)
    {
        matrix.emplace_back();
        for (auto col = 0; col < 4; ++col)
        {
            matrix[row].emplace_back();
        }
    }

    // Set ones on the diagonal.
    for (auto i = 0; i < 4; ++i)
        matrix[i][i] = 1;

    // Set some illustration values in the upper diagonal.
    matrix[1][0] = 1.2;
    matrix[2][0] = 10.0 / 9.0;
    matrix[3][0] = 1.23e11;
    matrix[2][1] = -2.34e22;
    matrix[3][1] = 3.45e-33;
    matrix[3][2] = -4.56e-44;

    return matrix;
}

template <typename Formatter> void print(Matrix const& matrix, Formatter format)
{
    for (auto const& row : matrix)
    {
        std::cout << "  ";
        for (auto const& value : row)
        {
            std::cout << format(value) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main()
{
    auto const matrix = generateMatrix();

    std::cout << "Printed with operator<<():\n";
    print(matrix, [](double x) { return x; });

    std::cout << "Printed with formatter:\n";
    print(matrix, [](double x) { return format(x, 6, true); });
}
