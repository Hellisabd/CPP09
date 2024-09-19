#include "Fixed.hpp"

Fixed::Fixed() : _fixed_point(0), _precision(0)
{
}

Fixed::Fixed(const Fixed &fixed)
{
	*this = fixed;
}

Fixed::~Fixed()
{
}

Fixed::Fixed(const int raw) : _fixed_point(raw << _bit_nb), _precision(0)
{
}

Fixed::Fixed(const float raw)
{
	std::stringstream ss;
	ss << raw;
	std::string strraw = ss.str();
	std::size_t pos = strraw.find('.');
	if (pos == std::string::npos)
		_precision = 0;
	_precision = strraw.length() - pos;
	if (_precision > 2)
		_precision = 2;
	_fixed_point = (static_cast<int>(roundf(raw * (1 << _bit_nb))));
}

Fixed &Fixed::operator=(const Fixed &other)
{
	if (this != &other)
	{
		this->_fixed_point = other.getRawBits();
		_precision = other.getPrecision();
	}
	return *this;
}

Fixed &Fixed::operator--()
{
	--_fixed_point;
	return (*this);
}

Fixed &Fixed::operator++()
{
	++_fixed_point;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	++_fixed_point;
	return temp;
}

Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	--_fixed_point;
	return temp;
}

std::ostream &operator<<(std::ostream &oss, const Fixed &other)
{
	oss << other.toFloat();
	return oss;
}

int	Fixed::getRawBits() const
{
	return (_fixed_point);
}

void	Fixed::setRawBits(int const raw)
{
	_fixed_point = raw;
}

int Fixed::getPrecision() const
{
	return _precision;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_fixed_point) / (1 << _bit_nb));
}

int	Fixed::toInt(void) const
{
	return (static_cast<int>(_fixed_point >> _bit_nb));
}

bool	Fixed::operator>(const Fixed &other) const
{
	if (_fixed_point > other.getRawBits())
		return (true);
	return (false);
}

bool	Fixed::operator<(const Fixed &other) const
{
	if (_fixed_point < other.getRawBits())
		return (true);
	return (false);
}

bool	Fixed::operator>=(const Fixed &other)
{
	if (_fixed_point >= other.getRawBits())
		return (true);
	return (false);
}

bool	Fixed::operator<=(const Fixed &other)
{
	if (_fixed_point <= other.getRawBits())
		return (true);
	return (false);
}

bool	Fixed::operator==(const Fixed &other)
{
	if (_fixed_point == other.getRawBits())
		return (true);
	return (false);
}

bool	Fixed::operator!=(const Fixed &other)
{
	if (_fixed_point != other.getRawBits())
		return (true);
	return (false);
}

Fixed	Fixed::operator+(const Fixed &other)
{
	Fixed nouveau;

	nouveau.setRawBits(_fixed_point + other.getRawBits());
	return (nouveau);
}

Fixed	Fixed::operator-(const Fixed &other)
{
	Fixed nouveau;

	nouveau.setRawBits(_fixed_point - other.getRawBits());
	return (nouveau);
}

Fixed	Fixed::operator*(const Fixed &other)
{
	Fixed nouveau;

	nouveau.setRawBits((_fixed_point * other.getRawBits()) >> _bit_nb);
	return (nouveau);
}

Fixed	Fixed::operator/(const Fixed &other)
{
	Fixed nouveau;

	nouveau.setRawBits(((_fixed_point << _bit_nb) / other.getRawBits()));

	return (nouveau);
}

Fixed	Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

Fixed	Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

const Fixed	Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

const Fixed	Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}
