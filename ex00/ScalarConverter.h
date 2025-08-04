#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H
#include <string>

enum Type { TYPE_CHAR, TYPE_INT, TYPE_FLOAT, TYPE_DOUBLE, TYPE_SPECIAL, TYPE_UNKNOWN };

class ScalarConverter {
public:
    static void convert(const std::string &input);

private:
    ScalarConverter();

    ~ScalarConverter();

    ScalarConverter(const ScalarConverter &);

    ScalarConverter &operator=(const ScalarConverter &);
};
#endif // SCALARCONVERTER_H
