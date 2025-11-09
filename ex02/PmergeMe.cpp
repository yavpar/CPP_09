#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

bool PmergeMe::parseNumbers(const std::string & args)
{
    std::istringstream is(args);
    long long int value = 0;
    _deque.clear();

    while (is >> value)
    {
        if (value < INT_MIN || value > INT_MAX)
		{
            std::cerr << RED << "Parse Error 17: OVERFLOW: " << value << NEUTRAL << '\n';
            return false;
        }
    }

	if (is.fail() && !is.eof())
	{
		std::cerr << RED << "Parse Error: 25: forbiden characters." << NEUTRAL << '\n';
		return false;
	}

	return true;
}

bool PmergeMe::mayorThan(int a, int b)
{
	return a > b;
}

