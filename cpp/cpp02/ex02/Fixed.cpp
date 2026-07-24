#include "Fixed.hpp"
#include <cmath>

const int Fixed::_fractionalBits = 8;

Fixed::Fixed(int rawBits, bool) : _rawBits(rawBits)
{
}

Fixed::Fixed(void) : _rawBits(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other) : _rawBits(other._rawBits)
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed::Fixed(const int value) : _rawBits(value << _fractionalBits)
{
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value) : _rawBits(roundf(value * (1 << _fractionalBits)))
{
	std::cout << "Float constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_rawBits = other._rawBits;
	return *this;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

bool Fixed::operator>(const Fixed& other) const
{
	return _rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed& other) const
{
	return _rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed& other) const
{
	return _rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed& other) const
{
	return _rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed& other) const
{
	return _rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed& other) const
{
	return _rawBits != other._rawBits;
}

Fixed Fixed::operator+(const Fixed& other) const
{
	return Fixed(_rawBits + other._rawBits, true);
}

Fixed Fixed::operator-(const Fixed& other) const
{
	return Fixed(_rawBits - other._rawBits, true);
}

Fixed Fixed::operator*(const Fixed& other) const
{
	long long product = static_cast<long long>(_rawBits) * static_cast<long long>(other._rawBits);
	return Fixed(static_cast<int>(product >> _fractionalBits), true);
}

Fixed Fixed::operator/(const Fixed& other) const
{
	if (other._rawBits == 0)
		return Fixed(0, true);
	long long dividend = static_cast<long long>(_rawBits) << _fractionalBits;
	return Fixed(static_cast<int>(dividend / other._rawBits), true);
}

Fixed& Fixed::operator++(void)
{
	++_rawBits;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed copy(_rawBits, true);
	++(*this);
	return copy;
}

Fixed& Fixed::operator--(void)
{
	--_rawBits;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed copy(_rawBits, true);
	--(*this);
	return copy;
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return _rawBits;
}

void Fixed::setRawBits(int const raw)
{
	_rawBits = raw;
}

float Fixed::toFloat(void) const
{
	return static_cast<float>(_rawBits) / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return _rawBits >> _fractionalBits;
}

Fixed& Fixed::min(Fixed& lhs, Fixed& rhs)
{
	return (lhs < rhs) ? lhs : rhs;
}

const Fixed& Fixed::min(const Fixed& lhs, const Fixed& rhs)
{
	return (lhs < rhs) ? lhs : rhs;
}

Fixed& Fixed::max(Fixed& lhs, Fixed& rhs)
{
	return (lhs > rhs) ? lhs : rhs;
}

const Fixed& Fixed::max(const Fixed& lhs, const Fixed& rhs)
{
	return (lhs > rhs) ? lhs : rhs;
}

std::ostream& operator<<(std::ostream& output, const Fixed& fixed)
{
	output << fixed.toFloat();
	return output;
}
