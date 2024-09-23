#pragma once

#include <iostream>
#include <deque>
#include <list>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <sys/time.h> 


# define NC std::string("\e[0m")
# define RED std::string("\e[1;31m")
# define GREEN std::string("\e[1;32m")
# define YELLOW std::string("\e[1;33m")
# define ORANGE std::string("\e[1;34m")
# define PURPLE std::string("\e[1;35m")
# define BLUE std::string("\e[1;36m")
#define FILE_NAME (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1))

#define LOG(msg) std::cout << "Fichier: " << FILE_NAME << ", Fonction: " << __func__ << " -- " << msg << std::endl

class ParsingError : public std::exception {

public :
virtual ~ParsingError()  _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {};
ParsingError(const std::string &msg) : _message(msg) {}
virtual const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {return _message.c_str();}
private :
	const std::string _message;
};

class PmergeMe {

	public:

		PmergeMe();
		PmergeMe(const PmergeMe& other);
		virtual ~PmergeMe();
		PmergeMe& operator=(const PmergeMe& other);
		void addPairsList();
		void insertPairsList();
		void printPairsList();
		void sortPairsList(std::pair<unsigned int, unsigned int> &pair);
		void addPairsDeque();
		void insertPairsDeque();
		void printPairsDeque();
		void sortPairsDeque(std::pair<unsigned int, unsigned int> &pair);
		void listSolver();
		void binarySearchList(unsigned int toPlace);
		void binarySearchDeque(unsigned int toPlace);
		void dequeSolver();
		void parsing(std::string const &toConvert);
		static void mergeHim(std::string *argv, int argc);


	private:
		std::list<std::pair<unsigned int, unsigned int> > _contOfPairsList;
		std::deque<std::pair<unsigned int, unsigned int> > _contOfPairsDeque;
		std::list<unsigned int> _entryList;
		std::deque<unsigned int> _entryDeque;
		std::list<unsigned int> _list;
		std::deque<unsigned int> _deque;
};