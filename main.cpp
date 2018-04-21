#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "alignprint.hpp"

using std::cout;
using std::vector;
using matrix = vector<vector<double>>;

void print(const matrix& m)
{
    for (const auto& r : m)
    {
        for (const auto& e : r)
            cout << format(e) << ' ';
        cout << '\n';
    }
    cout << '\n';
}

int main()
{
    matrix m;

    m.emplace_back();
    for (int i = -10; i < 0; ++i)
        m[0].emplace_back(static_cast<double>(i));

    m.emplace_back();
    for (int i = 0; i < 10; ++i)
        m[1].emplace_back(static_cast<double>(i));

    std::default_random_engine g;
    std::uniform_int_distribution<int> e(-10, 10);
    std::uniform_real_distribution<double> s(-1, 1);

    for (int i = 2; i < 10; ++i)
    {
        m.emplace_back();
        for (int j = 0; j < 10; ++j)
            m[i].emplace_back(s(g) * std::pow(10, e(g)));
    }

    print(m);

    return 0;
}
