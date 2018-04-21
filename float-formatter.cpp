#include "float-formatter.hpp"

#include <iostream>  // ios_base::precision
#include <regex>
#include <sstream>  // std::ostringstream
#include <string>

using std::string;

string convertToString(double x, size_t width);
bool isScientific(const string& s);
string stripScientific(string&& s);
string shortenScientific(string&& s, size_t width);
string shortenNonScientific(string&& s, size_t width);
string eraseDanglingDot(string&& s);
string padWithSpaces(string&& s, size_t width);

string format(double x, size_t width)
{
    if (x == 0)
        return string(width - 1, ' ') + '.';

    string s = convertToString(x, width);

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

string convertToString(double x, size_t width)
{
    std::ostringstream ss;
    ss.precision(width);
    ss << x;
    return ss.str();
}

string stripScientific(string&& s)
{
    // Remove needless characters in scientific notation
    // -1e+06 -> -1e6
    static const std::regex r1(R"((-?\d\.?[1-9]*)0*e\+?(-?)0*([1-9]*))");
    s = std::regex_replace(s, r1, "$1e$2$3");

    // Remove decimal separator when there are no decimals
    // 1.e6 -> 1e6
    static const std::regex r2(R"(([1-9])\.e)");
    s = std::regex_replace(s, r2, "$1e");

    return s;
}

bool isScientific(const string& s)
{
    return s.find('e') != string::npos;
}

string shortenNonScientific(string&& s, size_t width)
{
    return s.substr(0, width);
}

string shortenScientific(string&& s, size_t width)
{
    int chars_to_remove = s.size() - width;
    if (chars_to_remove < 0)
        chars_to_remove = 0;
    int position_exponent = s.find('e');
    int remove_from_position = position_exponent - chars_to_remove;
    s.erase(remove_from_position, chars_to_remove);

    return s;
}

string eraseDanglingDot(string&& s)
{
    static const std::regex r(R"(\.(\D|$))");
    s = regex_replace(s, r, "$1");
    return s;
}

string padWithSpaces(string&& s, size_t width)
{
    if (s.size() < width)
        s.insert(s.begin(), width - s.size(), ' ');
    return s;
}
