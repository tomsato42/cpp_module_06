#include "ScalarConverter.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>

static bool isSpecial(const std::string &s) {
    return (s == "nan" || s == "nanf" ||
            s == "+inf" || s == "-inf" ||
            s == "+inff" || s == "-inff");
}

static Type detectType(const std::string &s) {
    if (isSpecial(s)) return TYPE_SPECIAL;

    if (s.size() == 1 && std::isprint(s[0]) && !std::isdigit(s[0]))
        return TYPE_CHAR;

    const bool hasDot = (s.find('.') != std::string::npos);
    const bool hasF = (s[s.size() - 1] == 'f' || s[s.size() - 1] == 'F');

    if (hasDot && hasF) return TYPE_FLOAT;
    if (hasDot) return TYPE_DOUBLE;

    const size_t start = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    if (s.find_first_not_of("0123456789", start) == std::string::npos)
        return TYPE_INT;

    return TYPE_UNKNOWN;
}

void ScalarConverter::convert(const std::string &input) {
    const Type type = detectType(input);

    char cVal = 0;
    int iVal = 0;
    float fVal = 0.0f;
    double dVal = 0.0;
    bool charImpossible = false;
    bool charNonDisplayable = false;
    bool intImpossible = false;

    switch (type) {
        case TYPE_CHAR:
            cVal = input[0];
            iVal = static_cast<int>(cVal);
            fVal = static_cast<float>(cVal);
            dVal = static_cast<double>(cVal);
            if (!std::isprint(cVal)) charNonDisplayable = true;
            break;

        case TYPE_INT: {
            long tmp = std::strtol(input.c_str(), NULL, 10);
            if (tmp < std::numeric_limits<int>::min() || tmp > std::numeric_limits<int>::max())
                intImpossible = true;
            else
                iVal = static_cast<int>(tmp);

            if (intImpossible) {
                charImpossible = true;
            } else {
                cVal = static_cast<char>(iVal);
                if (iVal < std::numeric_limits<char>::min() || iVal > std::numeric_limits<char>::max())
                    charImpossible = true;
                if (!std::isprint(cVal)) charNonDisplayable = true;
            }
            fVal = static_cast<float>(tmp);
            dVal = static_cast<double>(tmp);
            break;
        }

        case TYPE_FLOAT:
            fVal = std::strtof(input.c_str(), NULL);
            dVal = static_cast<double>(fVal);
            if (std::isnan(fVal) || std::isinf(fVal)) {
                intImpossible = true;
            } else {
                if (fVal < std::numeric_limits<int>::min() || fVal > std::numeric_limits<int>::max()) {
                    intImpossible = true;
                    charImpossible = true;
                } else {
                    iVal = static_cast<int>(fVal);
                    cVal = static_cast<char>(iVal);
                    if (iVal < std::numeric_limits<char>::min() || iVal > std::numeric_limits<char>::max())
                        charImpossible = true;
                    if (!std::isprint(cVal)) charNonDisplayable = true;
                }
            }
            if (intImpossible) {
                charImpossible = true;
            }
            break;

        case TYPE_DOUBLE:
            dVal = std::strtod(input.c_str(), NULL);
            fVal = static_cast<float>(dVal);
            if (std::isnan(dVal) || std::isinf(dVal)) {
                intImpossible = true;
            } else {
                if (dVal < std::numeric_limits<int>::min() || dVal > std::numeric_limits<int>::max()) {
                    intImpossible = true;
                    charImpossible = true;
                } else {
                    iVal = static_cast<int>(dVal);
                    cVal = static_cast<char>(iVal);
                    if (iVal < std::numeric_limits<char>::min() || iVal > std::numeric_limits<char>::max())
                        charImpossible = true;
                    if (!std::isprint(cVal)) charNonDisplayable = true;
                }
            }
            if (intImpossible) {
                charImpossible = true;
            }
            break;

        case TYPE_SPECIAL:
            charImpossible = true;
            intImpossible = true;
            if (input[input.size() - 1] == 'f')
                fVal = std::strtof(input.c_str(), NULL), dVal = static_cast<double>(fVal);
            else
                dVal = std::strtod(input.c_str(), NULL), fVal = static_cast<float>(dVal);
            break;

        default:
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n";
            return;
    }

    std::cout << "char: ";
    if (charImpossible)
        std::cout << "impossible\n";
    else if (charNonDisplayable)
        std::cout << "Non displayable\n";
    else
        std::cout << "'" << cVal << "'\n";

    std::cout << "int: ";
    if (intImpossible)
        std::cout << "impossible\n";
    else
        std::cout << iVal << "\n";

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << fVal << "f\n";
    std::cout << "double: " << dVal << "\n";
}
