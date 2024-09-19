#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <cstring>
#include <iomanip> 
#include <cmath>
#include <string>

#include "Fixed.hpp"

# define NC std::string("\e[0m")
# define RED std::string("\e[1;31m")
# define GREEN std::string("\e[1;32m")
# define YELLOW std::string("\e[1;33m")
# define ORANGE std::string("\e[1;34m")
# define PURPLE std::string("\e[1;35m")
# define BLUE std::string("\e[1;36m")
#define FILE_NAME (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1))

#define LOG(msg) std::cout << "Fichier: " << FILE_NAME << ", Fonction: " << __func__ << " -- " << msg << std::endl


class FileError : public std::exception {

		public :
		virtual ~FileError()  _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {};
		FileError(const std::string &msg) : _message(msg) {}
		virtual const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {return _message.c_str();}
		private :
			const std::string _message;
};

class WrongDataBase : public std::exception {

		public :
		virtual ~WrongDataBase()  _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {};
		WrongDataBase(const std::string &msg) : _message(msg) {}
		virtual const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {return _message.c_str();}
		private :
			const std::string _message;
};

class Fixed;

class BitcoinExchange {

	public:
		BitcoinExchange();
		virtual ~BitcoinExchange();
		void fillData(std::ifstream &data, std::ifstream &base);
		void parsingDate(std::string const &date);
		void parsingValue(std::string const &value);
		void verifDay(long nbrOfDay, long month);
		void printInfo();
		std::map<std::string, Fixed> const &getDataBase() const;

		

	private:
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		void printer(std::string date, float nbrCoin, Fixed &eR);
		std::vector<std::string> _date;
		std::vector<float> _coin;
		std::map<std::string, Fixed> _dataBase;
};


std::ostream &operator<<(std::ostream &oss, const BitcoinExchange &other);
void	btc(const char *filename);
