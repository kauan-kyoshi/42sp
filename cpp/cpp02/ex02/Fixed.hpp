#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	int				_rawBits;
	static const int	_fractionalBits;
	Fixed(int rawBits, bool);

public:
	Fixed(void);
	Fixed(const Fixed& other);
	Fixed(const int value);
	Fixed(const float value);
	Fixed& operator=(const Fixed& other);
	~Fixed(void);

	bool	operator>(const Fixed& other) const;
	bool	operator<(const Fixed& other) const;
	bool	operator>=(const Fixed& other) const;
	bool	operator<=(const Fixed& other) const;
	bool	operator==(const Fixed& other) const;
	bool	operator!=(const Fixed& other) const;

	Fixed	operator+(const Fixed& other) const;
	Fixed	operator-(const Fixed& other) const;
	Fixed	operator*(const Fixed& other) const;
	Fixed	operator/(const Fixed& other) const;

	Fixed& operator++(void);
	Fixed operator++(int);
	Fixed& operator--(void);
	Fixed operator--(int);

	int	getRawBits(void) const;
	void	setRawBits(int const raw);
	float	toFloat(void) const;
	int	toInt(void) const;

	static Fixed& min(Fixed& lhs, Fixed& rhs);
	static const Fixed& min(const Fixed& lhs, const Fixed& rhs);
	static Fixed& max(Fixed& lhs, Fixed& rhs);
	static const Fixed& max(const Fixed& lhs, const Fixed& rhs);
};

std::ostream& operator<<(std::ostream& output, const Fixed& fixed);

#endif
