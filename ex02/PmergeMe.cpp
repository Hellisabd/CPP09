#include "PmergeMe.hpp"

void	PmergeMe::printPairsList()
{
	int i = 0;
	for (std::list<std::pair<unsigned int, unsigned int> >::iterator it = _contOfPairsList.begin(); it != _contOfPairsList.end(); ++it)
	{
		// std::cout << GREEN + "thats the pair[" << i << "] : first->" << it->first << " | second->" << it->second << NC << std::endl; 
		i++;
	}
}

void PmergeMe::binarySearchList(unsigned int toPlace)
{
	unsigned int right = *(--_list.end());
	unsigned int left = *(_list.begin());
	std::list<unsigned int>::iterator it = _list.begin();
	if (toPlace > right)
		_list.insert(_list.end(), toPlace);
	else if (toPlace < left)
		_list.insert(_list.begin(), toPlace);
	else
	{
		while (left < right)
		{
			unsigned int middle = left + (right - left) / 2;
			if (toPlace < middle)
				right = middle;
			if (toPlace >= middle)
				left = middle + 1;
		}
		while (it != _list.end() && *it < left)
			++it;
		_list.insert(it, toPlace);
	}

}

PmergeMe::PmergeMe()
{
	LOG(GREEN + "Constructor by Default" + NC);
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	_entryList = other._entryList;
	_deque = other._deque;
	LOG(BLUE + "Constructor by copy" + NC);
}

PmergeMe	&PmergeMe::operator=(const PmergeMe& other)
{
	LOG(PURPLE + "Assignation Operator" + NC);
	if (this != &other) {

	}
	return *this;
}

void PmergeMe::sortPairsList(std::pair<unsigned int, unsigned int> &pair)
{
	if (pair.second < pair.first)
		std::swap(pair.second, pair.first);
	if (_contOfPairsList.back().first > pair.first)
	{
		std::swap(_contOfPairsList.back().first, pair.first);
		std::swap(_contOfPairsList.back().second, pair.second);
	}
}

void PmergeMe::addPairsList()
{
	for (std::list<unsigned int>::iterator it = _entryList.begin(); it != _entryList.end(); ++it)
	{
		std::pair<unsigned int, unsigned int> pair;
		pair.first = *it;
			++it;
		if (it == _entryList.end())
			--it;
		pair.second = *it;
		sortPairsList(pair);
		_contOfPairsList.push_back(pair);
	}
}

void PmergeMe::insertPairsList()
{
	for (std::list<std::pair<unsigned int, unsigned int> >::iterator it = _contOfPairsList.begin(); it != _contOfPairsList.end(); ++it)
	{
		if (_list.empty())
			_list.push_back(it->first);
		else
		{
			std::list<unsigned int>::iterator insert = _list.begin();
			while (insert != _list.end() && it->first > *insert)
				++insert;
			_list.insert(insert, it->first);
		}
	}
	for (std::list<std::pair<unsigned int, unsigned int> >::iterator it = _contOfPairsList.begin(); it != _contOfPairsList.end(); ++it)
	{
		if (it->first != it->second)
		{
			binarySearchList(it->second);
		}
	}
}

void PmergeMe::listSolver()
{
	addPairsList();
	// printPairsList();
	insertPairsList();	
}

void PmergeMe::dequeSolver()
{
	addPairsDeque();
	// printPairsDeque();
	insertPairsDeque();
}


void PmergeMe::parsing(std::string const &toConvert)
{
	if (atol(toConvert.c_str()) > INT_MAX || atol(toConvert.c_str()) < 0)
		throw ParsingError("Wrong input integer overflow or input input than 0");
	_entryList.push_back(atoi(toConvert.c_str()));
	_entryDeque.push_back(atoi(toConvert.c_str()));
	for (std::list<unsigned int>::iterator it = _entryList.begin(); it != _entryList.end(); ++it)
	{
		for (std::list<unsigned int>::iterator comp = _entryList.begin(); comp != _entryList.end(); ++comp)
		{
			if (comp == it)
				;
			else if (*comp == *it)
				throw ParsingError("Doublon found");
		}
	}
}

void PmergeMe::mergeHim(std::string *argv, int argc)
{
	PmergeMe my;

	for (int i = 1; i < argc; i++)
		my.parsing(argv[i - 1]);



	// OUTPUT FOR LIST
	std::cout << "Before : ";
	for (std::list<unsigned int>::iterator it = my._entryList.begin();
											it != my._entryList.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout  << std::endl;
	struct timeval liststart, listend;
	struct timeval dequestart, dequeend;
	gettimeofday(&liststart, NULL);
	my.listSolver();
	gettimeofday(&listend, NULL);
	long long listseconds = listend.tv_sec - liststart.tv_sec;
	long long listmicro = listend.tv_usec - liststart.tv_usec;
	if (listmicro < 0) {
        listseconds -= 1;
        listmicro += 1000000;
    }
	std::cout << "After : ";
	for (std::list<unsigned int>::iterator it = my._list.begin();
											it != my._list.end(); ++it)
		std::cout << *it << " ";
	std::cout  << std::endl;
	gettimeofday(&dequestart, NULL);
	my.dequeSolver();
	gettimeofday(&dequeend, NULL);
	long long dequeseconds = dequeend.tv_sec - dequestart.tv_sec;
	long long dequemicro = dequeend.tv_usec - dequestart.tv_usec;
	if (dequemicro < 0) {
        dequeseconds -= 1;
        dequemicro += 1000000;
    }

	std::cout<< "Time to process a range of " << my._entryList.size() << " elements with std::list :" << (listseconds * 1000000LL + listmicro) <<  " microsec" << std::endl;
	std::cout<< "Time to process a range of " << my._entryDeque.size() << " elements with std::deque :" << (dequeseconds * 1000000LL + dequemicro) << " microsec" << std::endl;



	// OUTPUT FOR DEQUE
	// std::cout << "Before : ";
	// for (std::deque<unsigned int>::iterator it = my._entryDeque.begin();
	// 										it != my._entryDeque.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout  << std::endl;
	// my.listSolver();
	// my.dequeSolver();
	// std::cout << "After : ";
	// for (std::deque<unsigned int>::iterator it = my._deque.begin();
	// 										it != my._deque.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout  << std::endl;
}

PmergeMe::~PmergeMe()
{
	LOG(RED + "Destructor by default" + NC);
}


void	PmergeMe::printPairsDeque()
{
	int i = 0;
	for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = _contOfPairsDeque.begin(); it != _contOfPairsDeque.end(); ++it)
	{
		// std::cout << GREEN + "thats the pair[" << i << "] : first->" << it->first << " | second->" << it->second << NC << std::endl; 
		i++;
	}
}

void PmergeMe::binarySearchDeque(unsigned int toPlace)
{
	unsigned int right = *(--_deque.end());
	unsigned int left = *(_deque.begin());
	std::deque<unsigned int>::iterator it = _deque.begin();
	if (toPlace > right)
		_deque.insert(_deque.end(), toPlace);
	else if (toPlace < left)
		_deque.insert(_deque.begin(), toPlace);
	else
	{
		while (left < right)
		{
			unsigned int middle = left + (right - left) / 2;
			if (toPlace < middle)
				right = middle;
			if (toPlace >= middle)
				left = middle + 1;
		}
		while (it != _deque.end() && *it < left)
			++it;
		_deque.insert(it, toPlace);
	}

}

void PmergeMe::sortPairsDeque(std::pair<unsigned int, unsigned int> &pair)
{
	if (pair.second < pair.first)
		std::swap(pair.second, pair.first);
	if (!_contOfPairsDeque.empty() && _contOfPairsDeque.back().first > pair.first)
	{
		std::swap(_contOfPairsDeque.back().first, pair.first);
		std::swap(_contOfPairsDeque.back().second, pair.second);
	}
}

void PmergeMe::addPairsDeque()
{
	for (std::deque<unsigned int>::iterator it = _entryDeque.begin(); it != _entryDeque.end(); ++it)
	{
		std::pair<unsigned int, unsigned int> pair;
		pair.first = *it;
			++it;
		if (_entryDeque.size() > 2 && it == _entryDeque.end())
			--it;
		pair.second = *it;
		sortPairsDeque(pair);
		_contOfPairsDeque.push_back(pair);
	}
}

void PmergeMe::insertPairsDeque()
{
	for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = _contOfPairsDeque.begin(); it != _contOfPairsDeque.end(); ++it)
	{
		if (_deque.empty())
			_deque.push_back(it->first);
		else
		{
			std::deque<unsigned int>::iterator insert = _deque.begin();
			while (insert != _deque.end() && it->first > *insert)
				++insert;
			_deque.insert(insert, it->first);
		}
	}
	for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = _contOfPairsDeque.begin(); it != _contOfPairsDeque.end(); ++it)
	{
		if (it->first != it->second)
		{
			binarySearchDeque(it->second);
		}
	}
}