#pragma once

#include <exception>
#include <iostream>
#include <stack>
#include <cstdlib>

# define NC std::string("\e[0m")
# define RED std::string("\e[1;31m")
# define GREEN std::string("\e[1;32m")
# define YELLOW std::string("\e[1;33m")
# define ORANGE std::string("\e[1;34m")
# define PURPLE std::string("\e[1;35m")
# define BLUE std::string("\e[1;36m")
#define FILE_NAME (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1))

// #define LOG(msg) std::cout << "Fichier: " << FILE_NAME << ", Fonction: " << __func__ << " -- " << msg << std::endl

class WrongArgs : public std::exception {

public :
virtual ~WrongArgs()  _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {};
WrongArgs(const std::string &msg) : _message(msg) {}
virtual const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {return _message.c_str();}
private :
	const std::string _message;
};

class ParsingError : public std::exception {

public :
virtual ~ParsingError()  _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {};
ParsingError(const std::string &msg) : _message(msg) {}
ParsingError() : _message("Wrong input in Parsing") {}
virtual const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {return _message.c_str();}
private :
	const std::string _message;
};

class RPN {

	public:
		virtual ~RPN();
		static	void rpn(std::string const &str);



	private:
		RPN(const RPN& other);
		RPN();
		RPN& operator=(const RPN& other);
		void calcul(char op);
		void soustraction();
		void addition();
		void multiplication();
		void division();

		std::stack<long> _stack;
};
