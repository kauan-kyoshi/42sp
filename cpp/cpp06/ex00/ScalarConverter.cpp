#include "ScalarConverter.hpp"
#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
    enum LiteralType
    {
        TYPE_INVALID,
        TYPE_CHAR,
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_SPECIAL
    };

    bool isSpecial(const std::string &literal)
    {
        return literal == "nan" || literal == "nanf"
            || literal == "+inf" || literal == "-inf"
            || literal == "+inff" || literal == "-inff";
    }

    bool isDecimal(const std::string &literal, bool requireFloatingMarker)
    {
        std::string::size_type index = 0;
        bool hasDigit = false;
        bool hasPoint = false;
        bool hasExponent = false;

        if (literal.empty())
            return false;
        if (literal[index] == '+' || literal[index] == '-')
            ++index;
        for (; index < literal.length(); ++index)
        {
            if (literal[index] >= '0' && literal[index] <= '9')
                hasDigit = true;
            else if (literal[index] == '.' && !hasPoint)
                hasPoint = true;
            else if ((literal[index] == 'e' || literal[index] == 'E')
                     && !hasExponent && hasDigit)
            {
                hasExponent = true;
                ++index;
                if (index < literal.length()
                    && (literal[index] == '+' || literal[index] == '-'))
                    ++index;
                if (index == literal.length()
                    || literal[index] < '0' || literal[index] > '9')
                    return false;
                for (; index < literal.length(); ++index)
                {
                    if (literal[index] < '0' || literal[index] > '9')
                        return false;
                }
                break;
            }
            else
                return false;
        }
        return hasDigit
            && (!requireFloatingMarker || hasPoint || hasExponent);
    }

    LiteralType detectType(const std::string &literal)
    {
        if (literal.length() == 1
            && !(literal[0] >= '0' && literal[0] <= '9'))
            return TYPE_CHAR;
        if (isSpecial(literal))
            return TYPE_SPECIAL;
        if (literal.length() > 1 && literal[literal.length() - 1] == 'f'
            && isDecimal(literal.substr(0, literal.length() - 1), true))
            return TYPE_FLOAT;
        if (isDecimal(literal, true))
            return TYPE_DOUBLE;
        if (isDecimal(literal, false))
            return TYPE_INT;
        return TYPE_INVALID;
    }

    bool isNan(double value) { return value != value; }

    bool isInfinite(double value)
    {
        return value == std::numeric_limits<double>::infinity()
            || value == -std::numeric_limits<double>::infinity();
    }

    bool parseInt(const std::string &literal, double &value)
    {
        char *end = 0;
        errno = 0;
        long parsed = std::strtol(literal.c_str(), &end, 10);
        if (errno == ERANGE || *end != '\0'
            || parsed < INT_MIN || parsed > INT_MAX)
            return false;
        int actual = static_cast<int>(parsed);
        value = static_cast<double>(actual);
        return true;
    }

    bool parseFloating(const std::string &literal, LiteralType type,
                       double &value)
    {
        std::string source = literal;
        if (type == TYPE_FLOAT)
            source.erase(source.length() - 1);
        char *end = 0;
        errno = 0;
        double parsed = std::strtod(source.c_str(), &end);
        if (errno == ERANGE || *end != '\0')
            return false;
        if (type == TYPE_FLOAT)
        {
            float actual = static_cast<float>(parsed);
            if (!isInfinite(parsed)
                && (actual == std::numeric_limits<float>::infinity()
                    || actual == -std::numeric_limits<float>::infinity()))
                return false;
            value = static_cast<double>(actual);
        }
        else
            value = parsed;
        return true;
    }

    double specialValue(const std::string &literal)
    {
        if (literal == "nan" || literal == "nanf")
            return std::numeric_limits<double>::quiet_NaN();
        if (literal[0] == '-')
            return -std::numeric_limits<double>::infinity();
        return std::numeric_limits<double>::infinity();
    }

    void printChar(double value)
    {
        std::cout << "char: ";
        if (isNan(value) || isInfinite(value)
            || value < CHAR_MIN || value > CHAR_MAX)
            std::cout << "impossível";
        else
        {
            char converted = static_cast<char>(value);
            if (converted < 32 || converted > 126)
                std::cout << "Não exibível";
            else
                std::cout << "'" << converted << "'";
        }
        std::cout << std::endl;
    }

    void printInt(double value)
    {
        std::cout << "int: ";
        if (isNan(value) || isInfinite(value)
            || value < INT_MIN || value > INT_MAX)
            std::cout << "impossível";
        else
            std::cout << static_cast<int>(value);
        std::cout << std::endl;
    }

    std::string formatFloating(double value, int precision)
    {
        std::ostringstream output;
        if (isNan(value))
            return "nan";
        if (value == std::numeric_limits<double>::infinity())
            return "+inf";
        if (value == -std::numeric_limits<double>::infinity())
            return "-inf";
        if (value == std::floor(value)
            && value <= 1000000.0 && value >= -1000000.0)
            output << std::fixed << std::setprecision(1) << value;
        else
            output << std::setprecision(precision) << value;
        return output.str();
    }

    void printFloat(double value)
    {
        std::cout << "float: ";
        if (!isNan(value) && !isInfinite(value)
            && (value > std::numeric_limits<float>::max()
                || value < -std::numeric_limits<float>::max()))
            std::cout << "impossível";
        else
        {
            float converted = static_cast<float>(value);
            std::cout << formatFloating(static_cast<double>(converted),
                                        std::numeric_limits<float>::digits10)
                      << "f";
        }
        std::cout << std::endl;
    }

    void printDouble(double value, int precision)
    {
        std::cout << "double: "
                  << formatFloating(value, precision)
                  << std::endl;
    }
}

void ScalarConverter::convert(const std::string &literal)
{
    LiteralType type = detectType(literal);
    double value = 0.0;
    bool valid = true;

    if (type == TYPE_CHAR)
    {
        char actual = literal[0];
        value = static_cast<double>(actual);
    }
    else if (type == TYPE_INT)
        valid = parseInt(literal, value);
    else if (type == TYPE_FLOAT || type == TYPE_DOUBLE)
        valid = parseFloating(literal, type, value);
    else if (type == TYPE_SPECIAL)
        value = specialValue(literal);
    else
        valid = false;
    if (!valid)
    {
        std::cout << "Erro: literal inválido ou fora dos limites." << std::endl;
        return;
    }
    printChar(value);
    printInt(value);
    printFloat(value);
    if (type == TYPE_FLOAT)
        printDouble(value, std::numeric_limits<float>::digits10);
    else
        printDouble(value, std::numeric_limits<double>::digits10);
}
