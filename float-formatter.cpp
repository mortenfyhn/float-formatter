#include "float-formatter.hpp"

#include <iostream>  // ios_base::precision
#include <regex>     // std::regex, std::regex_replace
#include <sstream>   // std::ostringstream
#include <string>    // std::string

std::string zeroString(size_t width, bool zero_as_dot);
std::string convertToString(double x, size_t width);
bool isScientific(std::string const& s);
std::string stripScientific(std::string&& s);
std::string shortenScientific(std::string&& s, size_t width);
std::string shortenNonScientific(std::string&& s, size_t width);
std::string eraseDanglingDot(std::string&& s);
std::string padWithSpaces(std::string&& s, size_t width);

std::string format(double x, size_t width, bool zero_as_dot)
{
    if (x == 0.0)
        return zeroString(width, zero_as_dot);

    auto s = convertToString(x, width);

    if (isScientific(s))
    {
        s = stripScientific(std::move(s));
        s = shortenScientific(std::move(s), width);
    }
    else
    {
        s = shortenNonScientific(std::move(s), width);
    }

    s = eraseDanglingDot(std::move(s));
    s = padWithSpaces(std::move(s), width);

    return s;
}

std::string zeroString(size_t width, bool zero_as_dot)
{
    auto const zero_symbol = zero_as_dot ? '.' : '0';
    return std::string(width - 1, ' ') + zero_symbol;
}

std::string convertToString(double x, size_t width)
{
    std::ostringstream ss;
    ss.precision(width);
    ss << x;
    return ss.str();
}

std::string stripScientific(std::string&& s)
{
    // Remove needless characters in scientific notation
    // -1e+06 -> -1e6
    std::regex static const r1(R"((-?\d\.?[1-9]*)0*e\+?(-?)0*([1-9]*))");
    s = std::regex_replace(s, r1, "$1e$2$3");

    // Remove decimal separator when there are no decimals
    // 1.e6 -> 1e6
    std::regex static const r2(R"(([1-9])\.e)");
    s = std::regex_replace(s, r2, "$1e");

    return s;
}

bool isScientific(std::string const& s)
{
    return s.find('e') != std::string::npos;
}

std::string shortenNonScientific(std::string&& s, size_t width)
{
    return s.substr(0, width);
}

std::string shortenScientific(std::string&& s, size_t width)
{
    auto const chars_to_remove = static_cast<int>(s.size() - width);
    if (chars_to_remove < 0)
        return s;

    auto const position_exponent = s.find('e');
    auto const remove_from_position = position_exponent - chars_to_remove;
    return s.erase(remove_from_position, chars_to_remove);
}

std::string eraseDanglingDot(std::string&& s)
{
    std::regex static const r(R"(\.(\D|$))");
    return std::regex_replace(s, r, "$1");
}

std::string padWithSpaces(std::string&& s, size_t width)
{
    s.insert(s.begin(), width - s.size(), ' ');
    return s;
}
