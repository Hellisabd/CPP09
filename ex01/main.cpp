#include "RPN.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw WrongArgs("Wrong numbers of arguments");
		RPN::rpn(argv[1]);
		RPN::rpn("8 9 * 9 - 9 - 9 - 4 - 1 +");
		RPN::rpn("7 7 * 7 -");
		RPN::rpn("1 2 * 2 / 2 * 2 4 - +");
		RPN::rpn("(1 + 1");
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}
}