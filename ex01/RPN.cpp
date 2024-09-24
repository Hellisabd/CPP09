#include "RPN.hpp"
#include <stdio.h>

void RPN::soustraction()
{
	int tmp = _stack.top();
	long over = _stackOverflow.top();
	_stack.pop();
	_stackOverflow.pop();
	_stackOverflow.top() = _stackOverflow.top() - over;
	_stack.top() = _stack.top() - tmp;
	if (_stackOverflow.top() != _stack.top())
		throw ParsingError("Overflow detected");
}

void RPN::addition()
{
	int tmp = _stack.top();
	long over = _stackOverflow.top();
	_stack.pop();
	_stackOverflow.pop();
	_stackOverflow.top() = _stackOverflow.top() + over;
	_stack.top() = _stack.top() + tmp;
	if (_stackOverflow.top() != _stack.top())
		throw ParsingError("Overflow detected");
}

void RPN::multiplication()
{
	int tmp = _stack.top();
	long over = _stackOverflow.top();
	_stack.pop();
	_stackOverflow.pop();
	_stackOverflow.top() = _stackOverflow.top() * over;
	_stack.top() = _stack.top() * tmp;
	if (_stackOverflow.top() != _stack.top())
		throw ParsingError("Overflow detected");
}

void RPN::division()
{
	int tmp = _stack.top();
	long over = _stackOverflow.top();
	_stack.pop();
	_stackOverflow.pop();
	_stackOverflow.top() = _stackOverflow.top() / over;
	_stack.top() = _stack.top() / tmp;
	if (_stackOverflow.top() != _stack.top())
		throw ParsingError("Overflow detected");
}

void RPN::calcul(char op)
{
	if (op == '-')
		soustraction();
	if (op == '+')
		addition();
	if (op == '*')
		multiplication();
	if (op == '/')
		division();
}

void RPN::rpn(std::string const &str)
{
	RPN my;
	std::size_t i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') &&
			str[i] != '-' && str[i] != '+'
			&& str[i] != '*' && str[i] != '/')
			throw ParsingError();
		else
			i++;
		if (isblank(str[i]))
			i++;
		else if (str[i] != '\0')
			throw ParsingError();
	}
	i = 0;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
		{
			my._stack.push(atol(str.c_str() + i));
			my._stackOverflow.push(atol(str.c_str() + i));
			if (my._stack.top() > 9)
				throw ParsingError("Input greater than 10 pls do the right thing!");
		}
		if (str[i] == '-' || str[i] == '+'
			|| str[i] == '*' || str[i] == '/')
		{
			if (my._stack.size() < 2)
				throw ParsingError("Wrong input u should have at least 2 numbers befor an operator");
			my.calcul(str[i]);
		}
		i++;
	}
	if (my._stack.size() > 1)
		throw ParsingError("Wrong input missing operator");
	if (my._stack.size() < 1)
		throw ParsingError("Nothing to print missing numbers");
	std::cout << my._stack.top() << std::endl;

}

RPN::RPN()
{
	//LOG(GREEN + "Constructor by Default" + NC);
}

RPN::RPN(const RPN& other)
{
	_stack = other._stack;
	//LOG(BLUE + "Constructor by copy" + NC);
}

RPN	&RPN::operator=(const RPN& other)
{
	//LOG(PURPLE + "Assignation Operator" + NC);
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN()
{
	//LOG(RED + "Destructor by default" + NC);
}
