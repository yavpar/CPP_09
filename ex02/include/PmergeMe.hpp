#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include <climits>

# define BLUE "\033[1;34m"
# define RED "\033[1;31m"
# define MARRON "\033[1;33m"
# define GREEN "\033[1;32m"
# define MAGENTA "\033[1;35m"
# define NEUTRAL "\033[0m" 
# define MAX_ELEMENTS 4000
#define _DEBUG 0

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe & copy);
		PmergeMe & operator=(const PmergeMe & copy);
		~PmergeMe();

	//variables
		std::deque<int> _deque;
		std::deque<int> _Dmax;
		std::deque<int> _Dmin;
		std::deque<int> _Djacobsthal;
		std::deque<int> _Dgroups;
	
		std::vector<int> _vect;
		std::vector<int> _Vmax;
		std::vector<int> _Vmin;
		std::vector<int> _Vjacobsthal;
		std::vector<int> _Vgroups;

		int nElem;
		int before[MAX_ELEMENTS];
		int after[MAX_ELEMENTS];
	// member fonctions
		// for parse
		bool hasDouble(int *n, int size);
		bool parseNumbers( char ** args, int ac);
		static bool mayorThan(int a, int b);
		std::size_t adjust_group_size(std::size_t gSize, std::size_t offset, std::size_t pSize);

		// for vector algorithm
		void insertSorted(std::vector<int> & container, int value);
		void separateMinMax(std::vector<int> & container, std::vector<int> & mins, std::vector<int> & maxs);
		int min_value_idx(std::vector<int> & data);
		bool createStack(const std::string & s, std::vector<int> & _stack);
		void printStack(std::vector<int> & container) const;
		void generate_jacobsthal_groups(const std::vector<int> & jacob, std::vector<int> & groups, std::size_t total_mins);
		void generate_jacobsthal_sequence(const std::vector<int> & mins, std::vector<int> & jacob);
		void insert_sorted_desc_iter(std::vector<int> & container, int value);
		void push_min(std::vector<int> &sorted, const std::vector<int> &pending, const std::vector<int> &grJacobsthal);
		void bump_positions(std::vector<int> &pos, std::size_t ins_index);
		std::size_t insert_one_min(std::vector<int> & sorted, int value_to_insert, std::size_t max_pos_index);
		void init_positions(std::vector<int> & sorted, std::vector<int> &  pos);


		// for deque algorithm

		void insertSorted(std::deque<int> & container, int value);
		void separateMinMax(std::deque<int> & container, std::deque<int> & mins, std::deque<int> & maxs);
		int min_value_idx(std::deque<int> & data);
		bool createStack(const std::string & s, std::deque<int> & _stack);
		void printStack(std::deque<int> & container) const;
		void generate_jacobsthal_groups(const std::deque<int> & jacob, std::deque<int> & groups, std::size_t total_mins);
		void generate_jacobsthal_sequence(const std::deque<int> & mins, std::deque<int> & jacob);
		void insert_sorted_desc_iter(std::deque<int> & container, int value);
		void push_min(std::deque<int> &sorted, const std::deque<int> &pending, const std::deque<int> &grJacobsthal);
		void bump_positions(std::deque<int> &pos, std::size_t ins_index);
		std::size_t insert_one_min(std::deque<int> & sorted, int value_to_insert, std::size_t max_pos_index);
		void init_positions(std::deque<int> & sorted, std::deque<int> &  pos);

};

#endif
