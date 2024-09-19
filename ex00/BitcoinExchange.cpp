#include "BitcoinExchange.hpp"

void	BitcoinExchange::verifDay(long nbrOfDay, long month)
{
	if (month == 1 || month == 3 || month == 5
		|| month == 7  || month == 8  || month == 10 
		|| month == 12)
	{
		if (nbrOfDay > 31 || nbrOfDay < 1)
			throw WrongDataBase("Wrong input for a day");
	}
	else if (month == 2)
	{
		if (nbrOfDay > 28 || nbrOfDay < 1)
			throw WrongDataBase("Wrong input for a day");
	}
	else
	{
		if (nbrOfDay > 30 || nbrOfDay < 1)
			throw WrongDataBase("Wrong input for a day");
	}
}


void BitcoinExchange::parsingDate(std::string const &date)
{
	long month;
	std::size_t i = 0;
	while (i < 4)
	{
		if (date[i] < '0' || date[i] > '9')
		{
			throw WrongDataBase("Wrong Character found in year");
		}
		i++;
	}
	if (date[i] != '-')
		throw WrongDataBase("Wrong Character found between year and month");
	else
		i++;
	month = atol(date.c_str() + i);
	if (month < 0 || month > 12)
		throw WrongDataBase("Month incorrect");
	else
		i += 2;
	if (date[i] != '-')
		throw WrongDataBase("Wrong Character found between day and month");
	else
		i++;
	verifDay(atol(date.c_str() + i), month);
}

void BitcoinExchange::parsingValue(std::string const &value)
{
	std::size_t i = 0;
	int dot = 0;
	while (i < value.size())
	{
		while (isspace(value[i]))
			i++;
		if (value[i] == '-' || value[i] == '+')
			i++;
		if (value[i] != '.' && (value[i] < '0' || value[i] > '9'))
			throw WrongDataBase("Input error in value");
		if (value[i] == '.')
			dot++;
		if (dot == 2)
		{
			// std::cout << GREEN + "error in value : " << value << NC << std::endl;
			throw WrongDataBase("Input error in value too much dot");
		}
		i++;
	}
}

void BitcoinExchange::fillData(std::ifstream &data, std::ifstream &base)
{
	std::string line;
	std::getline(data, line);
	std::getline(base, line);
	while (!data.eof())
	{
		std::getline(data, line);
		// std::cout << "line to split : " << line << std::endl;
		std::size_t i = line.find('|');
		if (i == line.npos)
		{
			_date.push_back(line);
			_coin.push_back(0);
		}
		else
		{
			std::string date = line.substr(0,  i - 1);
			std::string value = line.substr(i + 1, line.size());
			// std::cout <<  RED + "date : " << date << NC << std::endl;
			// std::cout <<  BLUE + "value : " << value << NC << std::endl;
			// parsingDate(date);
			_date.push_back(date);
			_coin.push_back((float)atof(value.c_str()));
		}
	}
	data.close();
	while (!base.eof())
	{
		std::string line;
		std::getline(base, line);
		// std::cout << "line to split : " << line << std::endl;
		std::size_t i = line.find(',');
		std::string date = line.substr(0, i);
		std::string value = line.substr(i + 1, line.size());
		// std::cout <<  RED + "date : " << date << NC << std::endl;
		// std::cout <<  BLUE + "value : " << value << NC << std::endl;
		_dataBase[date] = Fixed((float)atof(value.c_str()));
	}
	// std::cout << "size : " << _dataBase.size() << std::endl;
}

void BitcoinExchange::printer(std::string date, float nbrCoin, Fixed &eR)
{
	parsingDate(date);
	if (nbrCoin > 1000)
		throw WrongDataBase("Error: too large a number");
	if (nbrCoin < 0)
		throw WrongDataBase("Error: not a positive number");
	float res = eR.toFloat() * nbrCoin;
	std::cout << "taux :: " << eR.toFloat() << std::endl;
	std::cout << GREEN << date << " => " << nbrCoin << " = " << std::setprecision(eR.getPrecision()) << res << NC << std::endl;
}


void BitcoinExchange::printInfo()
{
	std::vector<float>::iterator fit = _coin.begin();
	for (std::vector<std::string>::iterator it = _date.begin();\
											 it != _date.end(); ++it)
	{
		std::map<std::string, Fixed>::iterator comp = _dataBase.begin();
		while (comp != _dataBase.end() && *it > comp->first)
			comp++;
		if (comp != _dataBase.end())
		{
			try
			{
				printer(*it, *fit, comp->second);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		fit++;
	}
}

std::map<std::string, Fixed> const &BitcoinExchange::getDataBase() const
{
	return _dataBase;
}

std::ostream &operator<<(std::ostream &oss, const BitcoinExchange &other)
{
	(void)other;
	// oss << "DATA\n---------------------------------" << std::endl;
	// for (std::map<std::string, Fixed>::const_iterator it = other.getDataBase().begin(); it != other.getDataBase().end(); it++)
	// {
	// 	oss << PURPLE << "KEY :" << BLUE <<  it->first << NC << "  |  " + PURPLE << "VALUE : " << BLUE << it->second << NC << std::endl; 
	// }
	oss << "ENTRY\n---------------------------------" << std::endl;
	// for (std::map<std::string, Fixed>::const_iterator it = other.getEntry().begin(); it != other.getEntry().end(); it++)
	// {
	// 	oss << PURPLE << "KEY :" << BLUE <<  it->first << NC << "  |  " + PURPLE << "VALUE : " << BLUE << it->second << NC << std::endl;
	// }
	return oss;
}

void btc(const char *fname)
{
	BitcoinExchange dataBase;
	std::string filename = fname;
	std::ifstream inputfile(filename.c_str());
	if (!inputfile.is_open())
		throw FileError("Can't open input File");
	std::ifstream data("data.csv");
	if (!inputfile.is_open())
		throw FileError("Can't open the Data file");
	dataBase.fillData(inputfile, data);
	dataBase.printInfo();
}

BitcoinExchange::BitcoinExchange()
{
	LOG(GREEN + "Constructor by Default" + NC);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	(void)other;
	LOG(BLUE + "Constructor by copy" + NC);
}


BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange& other)
{
	LOG(PURPLE + "Assignation Operator" + NC);
	if (this != &other) {

	}
	return *this;
}


BitcoinExchange::~BitcoinExchange()
{
	LOG(RED + "Destructor by default" + NC);
}