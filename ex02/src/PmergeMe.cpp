#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

bool PmergeMe::hasDouble(int *n, int size)
{
	int k = 0;

	while (k < size)
	{
		int j = k + 1;
		int target = *(n + k);
		for (; j < size; j++)
		{
			if (target == *(n + j))
			{
            	std::cerr << RED << "Parse Error 19: doubles: " << target << " " << *(n + j) << NEUTRAL << '\n';
				return true;
			}
		}
		++k;
	}
	return false;
}

bool PmergeMe::parseNumbers( char ** args, int ac)
{
	(void)ac;
	std::string input(args[1]);
    std::istringstream is(input);
    long long int value = 0;
    _deque.clear();

	int n[1024];
	int i = 0;
    while (is >> value)
    {
		//std::cerr << RED << "Parse i = " << i << NEUTRAL << '\n';
        if (value < INT_MIN || value > INT_MAX)
		{
            std::cerr << RED << "Parse Error 17: OVERFLOW: " << value << NEUTRAL << '\n';
            return false;
        }
		int val = static_cast<int>(value);
		*(n + i) = val;
		++i;
    }

	if (is.fail() && !is.eof())
	{
		std::cerr << RED << "Parse Error: 25: forbiden characters." << NEUTRAL << '\n';
		return false;
	}

	if (hasDouble(n, i))
	{
		std::cerr << RED << "Parse Error: 57: Doubles!" << NEUTRAL << '\n';
		return false;
	}
	return true;
}

bool PmergeMe::mayorThan(int a, int b)
{
	return a < b;
}

std::size_t PmergeMe::adjust_group_size(std::size_t gSize, std::size_t offset, std::size_t pSize)
{
	std::size_t remaining = pSize - offset;

	if (gSize > remaining)
		gSize = remaining;

	return gSize;
}
