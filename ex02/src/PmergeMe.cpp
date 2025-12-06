#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	_deque.clear();
	_Dmax.clear();
	_Dmin.clear();
	_Djacobsthal.clear();
	_Dgroups.clear();
	_vect.clear();
	_Vmax.clear();
	_Vmin.clear();
	_Vjacobsthal.clear();
	_Vgroups.clear();
}

PmergeMe::PmergeMe(const PmergeMe & copy) : \
	_deque(copy._deque), \
	_Dmax(copy._Dmax), \
	_Dmin(copy._Dmin), \
	_Djacobsthal(copy._Djacobsthal), \
	_Dgroups(copy._Dgroups), \
	_vect(copy._vect), \
	_Vmax(copy._Vmax), \
	_Vmin(copy._Vmin), \
	_Vjacobsthal(copy._Vjacobsthal), \
	_Vgroups(copy._Vjacobsthal)
{}

PmergeMe & PmergeMe::operator=(const PmergeMe & copy)
{
	if (this != &copy)
	{
		_deque = copy._deque;
		_Dmax = copy._Dmax;
		_Dmin = copy._Dmin;
		_Djacobsthal = copy._Djacobsthal;
		_Dgroups = copy._Dgroups;
		_vect = copy._vect;
		_Vmax = copy._Vmax;
		_Vmin = copy._Vmin;
		_Vjacobsthal = copy._Vjacobsthal;
		_Vgroups = copy._Vjacobsthal;
	}

	return *this;
}

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
            	std::cerr << RED << "Error: has doubles: " << target << NEUTRAL << '\n';
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

	int i = 0;

	if (ac != 2)
	{
		std::cerr << RED << "Error: Too many arguments.\nUsage: ./merge \"positive numbers\"" << NEUTRAL << '\n';
		return false;
	}

    while (is >> value)
	{
		if (value < static_cast<long long int>(INT_MIN) || value > static_cast<long long int>(INT_MAX))
		{
			std::cerr << RED << "Error: OVERFLOW: " << value << NEUTRAL << '\n';
			return false;
		}
		int val = static_cast<int>(value);
		if (val < 0)
		{
			std::cerr << RED << "Error: negative number: " << val << '\n' << NEUTRAL;
			return false;
		}
		this->before[i] = val;
		++i;
	}	

	this->nElem = i;

	if (value < static_cast<long long int>(INT_MIN) || value > static_cast<long long int>(INT_MAX))
	{
		std::cerr << RED << "Error: OVERFLOW: " << value << NEUTRAL << '\n';
		return false;
	}

	if (is.fail() && !is.eof())
	{
		std::cerr << RED << "Error: forbiden characters." << NEUTRAL << '\n';
		return false;
	}

	if (hasDouble(this->before, i))
		return false;
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

