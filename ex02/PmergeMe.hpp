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

struct CompareIndice
{
	const std::deque<int> & data;
	CompareIndice (const std::deque<int> &d) : data(d) {}
	bool operator()(int a, int b) const
	{
		if (a != b)
			return (data[a] < data[b]);
		return (a < b);
	}
};

class PmergeMe
{
	private:
		PmergeMe(const PmergeMe & copy);
		PmergeMe & operator=(const PmergeMe & copy);

	public:
		PmergeMe();
		~PmergeMe();
		std::deque<int> _deque;
		std::deque<int> _Dmax;
		std::deque<int> _Dmin;
		std::deque<int> _Djacobsthal;
		std::deque<int> _Dgroups;

		std::vector<int> _vect;
		std::vector<int> _Vmax;
		std::vector<int> _Vmin;
		std::vector<int> _Vjacobsthal;
		std::deque<int> _Vgroups;

	// member fonctions
		bool parseNumbers(const std::string & args);

		template <typename A>
		void insertSorted(A & container, int value);

		template <typename T>
		void separateMinMax(T & container, T & mins, T & maxs);

		template <typename C>
		int max_value_idx(C & data);
		
		template <typename T>
		bool createStack(const std::string & s, T & _stack);

		template <typename T>
		void printStack(T & container) const;

		template <typename C, typename D>
		void generate_jacobsthal_groups(const C & jacob, D & groups);

		template <typename A, typename B>
		void generate_jacobsthal_sequence(const A & mins, B & jacob);

		template <typename C>
		void insert_sorted_desc_iter(C & container, int value);
		
		template <typename Cont>
		void push_min(Cont &sorted, const Cont &pending, const Cont &grJacobsthal);

		static bool mayorThan(int a, int b);
};

#include "FonctTemplate.tpp"

#endif
