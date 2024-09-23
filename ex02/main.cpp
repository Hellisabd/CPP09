#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc < 2)
			throw ParsingError("No Arguments");
		std::string *newStr = new std::string[argc - 1];
		try
		{
			for (int i = 1; i < argc; i++)
				newStr[i - 1] = argv[i];
			PmergeMe::mergeHim(newStr, argc);
			delete[] newStr;
		}
		catch(const std::exception& e)
		{
			delete[] newStr;
			std::cerr << e.what() << std::endl;
		}
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}
}