#pragma once

#include <iostream>
#include <cmath>
#include <sstream>
#include "BitcoinExchange.hpp"

class Fixed
{
	private:

	int 				_fixed_point;
	static const int	_bit_nb = 8;
	int				_precision;

	public:

	Fixed();
	Fixed(const Fixed &fixed);
	Fixed(const int raw);
	Fixed(const float raw);
	~Fixed();
	Fixed 	&operator++();
	Fixed 	operator++(int);
	Fixed 	&operator--();
	Fixed 	operator--(int);
	Fixed	&operator=(const Fixed &other);
	bool	operator>(const Fixed &other) const;
	bool	operator<(const Fixed &other) const ;
	bool	operator>=(const Fixed &other);
	bool	operator<=(const Fixed &other);
	bool	operator==(const Fixed &other);
	bool	operator!=(const Fixed &other);
	Fixed	operator+(const Fixed &other);
	Fixed	operator*(const Fixed &other);
	Fixed	operator/(const Fixed &other);
	Fixed	operator-(const Fixed &other);
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
	int		getPrecision() const;
	float	toFloat(void) const;
	int		toInt(void) const;
	static Fixed	max(Fixed &a, Fixed &b);
	static Fixed	min(Fixed &a, Fixed &b);
	static const Fixed	max(const Fixed &a, const Fixed &b);
	static const Fixed	min(const Fixed &a, const Fixed &b);
};

std::ostream &operator<<(std::ostream &oss, const Fixed &other);
