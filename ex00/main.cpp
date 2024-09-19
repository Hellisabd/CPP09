#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Invalid Argument" << std::endl;
		return (1);
	}
	try
	{
		btc(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED + e.what() << std::endl << NC;
	}
	
}