#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private:
	int				_rawBits;
	static const int	_fractionalBits;

public:
	Fixed(void);
	Fixed(const Fixed& other);
	Fixed(const int value);
	Fixed(const float value);
	Fixed& operator=(const Fixed& other);
	~Fixed(void);

	int	getRawBits(void) const;
	void	setRawBits(int const raw);
	float	toFloat(void) const;
	int	toInt(void) const;
};

std::ostream& operator<<(std::ostream& output, const Fixed& fixed);

#endif
